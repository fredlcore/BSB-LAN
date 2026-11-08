#!/usr/bin/env python3
"""Inspect locally supplied OZW APW descriptions and a catalog, without bus I/O.

This experimental reader recognizes the observed OBST/OBEN serialization. It
preserves original byte offsets and does not treat static descriptions as proof
that a real controller accepts a query or write.
"""
from __future__ import annotations

import argparse
import collections
import dataclasses
import gzip
import hashlib
import json
import math
from pathlib import Path
import re
import sqlite3
import struct
import sys


class FormatError(ValueError):
    """A file does not satisfy the supported observed serialization layout."""


@dataclasses.dataclass
class Object:
    object_id: int
    class_name: str
    start: int
    body_start: int
    body_end: int = 0
    end: int = 0
    children: list[Object] = dataclasses.field(default_factory=list)
    parts: list[tuple[int, bytes]] = dataclasses.field(default_factory=list)

    def descendants(self):
        for child in self.children:
            yield child
            yield from child.descendants()


CLASS_NAME = re.compile(rb"COzw[A-Za-z0-9_]+(?=\x00\x00\x00\x04OBST)")
TAG = re.compile(rb"\x00\x00\x00\x04(OBST|OBEN)")
VALUE_PREFIXES = ("COzwVal", "COzwLVal", "COzwLString")
VALUE_CLASS = re.compile(r"COzw(?:Val[A-Z]|LVal[A-Z]|LString)")
HANDLER_CLASSES = {"COzwDpVhValAnalog", "COzwDpVhValB", "COzwDpVhValM",
                   "COzwDpVhValDate", "COzwDpVhValTOD", "COzwDpVhAnyString"}


def parse_apw(data: bytes) -> list[Object]:
    """Return bounded objects; reject ambiguous/malformed nesting, never repair it."""
    classes = {}
    definitions = {}
    for match in CLASS_NAME.finditer(data):
        if match.start() < 12:
            raise FormatError("class definition has no complete object prefix")
        start = match.start() - 12
        oid, cid, length = struct.unpack_from(">III", data, start)
        if length != len(match.group()) or cid in classes:
            raise FormatError("invalid class-name length or duplicate class definition")
        classes[cid] = match.group().decode("ascii")
        definitions[match.end() + 4] = (start, oid, cid)
    if not classes:
        raise FormatError("no supported class definitions")
    stack = []
    objects = []
    object_ids = set()
    for match in TAG.finditer(data):
        tagpos = match.start() + 4
        if match.group(1) == b"OBST":
            if tagpos in definitions:
                start, oid, cid = definitions[tagpos]
            else:
                start = tagpos - 12
                if start < 0:
                    raise FormatError("object prefix precedes file")
                oid, cid = struct.unpack_from(">II", data, start)
            if cid not in classes or oid in object_ids:
                raise FormatError("unknown class reference or duplicate object definition")
            if stack and start < stack[-1].body_start:
                raise FormatError("child object overlaps parent header")
            node = Object(oid, classes[cid], start, match.end())
            object_ids.add(oid)
            if stack:
                stack[-1].children.append(node)
            stack.append(node)
            objects.append(node)
        else:
            if not stack:
                raise FormatError("unmatched OBEN")
            node = stack.pop()
            node.body_end = match.start()
            node.end = match.end()
            cursor = node.body_start
            for child in node.children:
                if not cursor <= child.start <= child.end <= node.body_end:
                    raise FormatError("overlapping or out-of-bounds child object")
                node.parts.append((cursor, data[cursor:child.start]))
                cursor = child.end
            node.parts.append((cursor, data[cursor:node.body_end]))
    if stack:
        raise FormatError("unterminated object")
    if not objects:
        raise FormatError("no objects")
    # The supported layout should not silently ignore unframed literal markers.
    if data.count(b"OBST") != len(objects) or data.count(b"OBEN") != len(objects):
        raise FormatError("unframed tag occurrence: unsupported/ambiguous payload")
    return objects


class Catalog:
    """Read the supplied offline SQLite file in read-only mode; no arbitrary SQL."""
    def __init__(self, path: Path, language: int):
        self.path = path.resolve()
        self.sha256 = hashlib.sha256(self.path.read_bytes()).hexdigest()
        self.db = sqlite3.connect(self.path.as_uri() + "?mode=ro", uri=True)
        self.db.execute("PRAGMA query_only=ON")
        self.language = language
        self.labels = dict(self.db.execute(
            "SELECT MessageRowID, Message FROM Message WHERE MessageSetID=2 "
            "AND MessageIndex=1 AND LanguageCode=?", (language,)))
        self.enum_cache = {}
        self.unit_cache = {}

    def enum(self, set_id):
        if set_id not in self.enum_cache:
            rows = self.db.execute(
                "SELECT MessageRowID, Message FROM Message WHERE MessageSetID=? "
                "AND LanguageCode=? AND MessageIndex=1 ORDER BY MessageRowID",
                (set_id, self.language))
            self.enum_cache[set_id] = [{"row_id":r[0], "text":r[1]} for r in rows]
        return self.enum_cache[set_id]

    def unit(self, unit_id):
        if unit_id not in self.unit_cache:
            self.db.row_factory = sqlite3.Row
            rows = self.db.execute("SELECT * FROM ValueUnit WHERE UnitID=?", (unit_id,))
            self.unit_cache[unit_id] = [dict(r) for r in rows]
            self.db.row_factory = None
        return self.unit_cache[unit_id]

    def close(self):
        self.db.close()


def value_metadata(value: Object, catalog: Catalog, by_id=None):
    attrs = next((c for c in value.children
                  if c.class_name == "COzwCustomAttributes"), None)
    part = next(((off,raw) for off,raw in value.parts
                 if attrs and off == attrs.end), None)
    if part is None and by_id is not None and value.parts:
        offset, raw = value.parts[0]
        if offset == value.body_start and len(raw) >= 6:
            referenced = by_id.get(int.from_bytes(raw[:4], "big"))
            if referenced and referenced.class_name == "COzwCustomAttributes":
                part = (offset + 4, raw[4:])
    if part is None or len(part[1]) < 2:
        return None
    offset, raw = part
    row = int.from_bytes(raw[:2], "big")
    result = {"label_row":row, "label":catalog.labels.get(row),
              "value_class":value.class_name, "metadata_offset":offset,
              "metadata_hex":raw.hex()}
    common_end = None
    if len(raw) >= 28:
        reference_length = int.from_bytes(raw[16:20], "big")
        if reference_length <= len(raw)-28:
            common_end = 28 + reference_length
            reference = raw[20:20+reference_length]
            result["parameter_reference_candidate"] = reference.decode("utf-8", errors="replace")
            result["parameter_reference_hex"] = reference.hex()
        # Deliberately raw: permission/feature flag semantics are not established.
        result["raw_common_fields"] = {
            "mask_at_10":raw[10:12].hex(), "flags_at_12":raw[12:16].hex(),
            "reference_length_at_16":raw[16:20].hex(),
            "fields_after_reference_hex":raw[20+reference_length:common_end].hex() if common_end is not None else None}
    if common_end is not None and value.class_name in ("COzwValI8", "COzwValI16", "COzwValI32") and len(raw) >= common_end+10:
        unit = int.from_bytes(raw[common_end:common_end+2], "big")
        default = struct.unpack_from(">d", raw, common_end+2)[0]
        result["numeric_metadata_candidate"] = {
            "unit_id":unit, "catalog_records":catalog.unit(unit),
            "default_double_candidate":default if math.isfinite(default) else str(default),
            "default_double_hex":raw[common_end+2:common_end+10].hex(),
            "confidence":"observed-layout inference; confirm before generating firmware types"}
        limits=[]
        for child in value.children:
            if child.class_name != "COzwFloatLimit":
                continue
            limit_raw=b"".join(part for _,part in child.parts)
            record={"object_offset":child.start,"body_offset":child.body_start,
                    "raw_hex":limit_raw.hex(),"has_nested_objects":bool(child.children)}
            if not child.children and len(limit_raw)==16:
                kind=int.from_bytes(limit_raw[:4],"big")
                limit=struct.unpack_from(">d",limit_raw,4)[0]
                record.update({"bound_kind_candidate":{0:"lower",1:"upper"}.get(kind),
                               "raw_bound_kind":kind,
                               "raw_value_double_candidate":limit if math.isfinite(limit) else str(limit),
                               "raw_tail":limit_raw[12:].hex()})
            limits.append(record)
        result["numeric_metadata_candidate"]["inline_limits"] = limits
    if common_end is not None and value.class_name == "COzwValB" and len(raw) >= common_end+10:
        set_id = int.from_bytes(raw[common_end:common_end+2], "big")
        result["enum_metadata_candidate"] = {
            "message_set_id":set_id, "catalog_rows":catalog.enum(set_id),
            "confidence":"observed-layout inference; rows are not wire values"}
    if common_end is not None and value.class_name in ("COzwValME8", "COzwValME16") and len(raw) >= common_end+22:
        set_id = int.from_bytes(raw[common_end+12:common_end+14], "big")
        result["enum_metadata_candidate"] = {
            "message_set_id":set_id, "catalog_rows":catalog.enum(set_id),
            "confidence":"observed-layout inference; rows are not wire values"}
    return result


def points_from_objects(objects: list[Object], catalog: Catalog):
    points = []
    limitations = collections.Counter()
    by_id = {node.object_id:node for node in objects}

    def handler_value(handler):
        # The observed scalar-handler prefix is nine bytes, followed by an
        # inline value object or a four-byte reference to a defined value.
        if handler.class_name not in HANDLER_CLASSES:
            return None, None
        inline = next((v for v in handler.children if VALUE_CLASS.match(v.class_name)), None)
        if inline is not None and inline.start == handler.body_start+9:
            return inline, None
        if handler.parts:
            offset,raw=handler.parts[0]
            if offset == handler.body_start and len(raw) >= 13:
                reference=int.from_bytes(raw[9:13], "big")
                value=by_id.get(reference)
                if value and VALUE_CLASS.match(value.class_name):
                    return value, {"value_object_id":reference,"reference_offset":offset+9}
        return None, None

    for node in objects:
        if node.class_name == "COzwFLN_DP":
            offset, raw = node.parts[-1]
            handler = node.children[0] if node.children else None
            handler_ref = None
            if len(raw) == 16 and not node.children:
                reference=int.from_bytes(raw[:4], "big")
                candidate=by_id.get(reference)
                if candidate and candidate.class_name in HANDLER_CLASSES:
                    handler=candidate
                    handler_ref={"handler_object_id":reference,"reference_offset":offset}
                    offset += 4
                    raw=raw[4:]
            if len(raw) != 12:
                limitations["unsupported_FLN_tail_length"] += 1
                continue
            if handler is None:
                limitations["FLN_without_inline_handler"] += 1
                continue
            value,value_ref = handler_value(handler)
            md = value_metadata(value, catalog, by_id) if value else None
            if md is None:
                limitations["FLN_without_supported_value_metadata"] += 1
                continue
            address, access_word, final_word = struct.unpack(">III", raw)
            point = {**md, "object_class":node.class_name,
                     "object_id":node.object_id, "object_offset":node.start,
                     "address_offset":offset, "address_field_hex":raw[:4].hex(),
                     "raw_access_word":access_word, "raw_final_word":final_word,
                     "address_encoding":"24-bit class/object field; namespace expansion is a candidate"}
            if handler_ref:
                point["handler_reference"] = handler_ref
            if value_ref:
                point["value_reference"] = value_ref
            if address <= 0xffffff:
                point["coid_candidate"] = f"{address >> 16:02X}00{address & 65535:04X}"
            else:
                point["coid_candidate"] = None
                limitations["address_exceeds_observed_24_bit_layout"] += 1
            points.append(point)
        elif node.class_name == "COzwBlock_DP":
            first = node.parts[0]
            block_raw = first[1]
            address = int.from_bytes(block_raw[4:8], "big") if len(block_raw) >= 8 else None
            for field in node.children:
                for value in field.descendants():
                    if not VALUE_CLASS.match(value.class_name):
                        continue
                    md = value_metadata(value, catalog, by_id)
                    if md is None:
                        continue
                    tail_offset, tail = field.parts[-1]
                    point = {**md, "object_class":node.class_name,
                             "object_id":node.object_id, "object_offset":node.start,
                             "block_header_offset":first[0], "block_header_hex":block_raw.hex(),
                             "block_address_field_hex":block_raw[4:8].hex(),
                             "coid_candidate":f"{address >> 16:02X}00{address & 65535:04X}" if address is not None and address <= 0xffffff else None,
                             "field_object_offset":field.start,
                             "field_tail_offset":tail_offset,"field_tail_hex":tail.hex()}
                    if len(tail) == 2:
                        point["block_byte_offset_candidate"] = int.from_bytes(tail, "big")
                    points.append(point)
    return points, dict(limitations)


def inspect_profile(path: Path, catalog: Catalog):
    data = path.read_bytes()
    objects = parse_apw(data)
    points, limitations = points_from_objects(objects, catalog)
    return {"profile":path.name, "sha256":hashlib.sha256(data).hexdigest(),
            "bytes":len(data),"object_count":len(objects),"point_count":len(points),
            "class_counts":dict(collections.Counter(n.class_name for n in objects)),
            "limitations":limitations,"points":points}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profiles", type=Path, required=True,
                        help="directory containing locally extracted .apw files")
    parser.add_argument("--catalog", type=Path, required=True,
                        help="locally extracted SQLite catalog, opened read-only")
    parser.add_argument("--output", type=Path, required=True,
                        help="local .jsonl or .jsonl.gz; may contain proprietary catalog text")
    parser.add_argument("--summary", type=Path, required=True)
    parser.add_argument("--language", type=int, default=1, help="catalog language ID (1 English, 2 German)")
    parser.add_argument("--pattern", default="*.apw", help="optional profile filename glob, e.g. D0016*.apw")
    args = parser.parse_args(argv)
    files = sorted(args.profiles.glob(args.pattern))
    if not files:
        parser.error("no .apw files in --profiles directory")
    if args.output.exists() or args.summary.exists():
        parser.error("output and summary must be new paths; existing files are never overwritten")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.summary.parent.mkdir(parents=True, exist_ok=True)
    catalog = Catalog(args.catalog, args.language)
    summary = {"format":"experimental OZW APW structural reader v1", "catalog_sha256":catalog.sha256,
               "language_id":args.language,"profiles_discovered":len(files),"profiles_parsed":0,
               "point_records":0,"objects":0,"failures":[],"limitation_counts":{},
               "coverage_limits":["Static descriptions do not verify live query/write support.",
                   "Metadata offsets and class-derived layouts are experimental; raw fields retained.",
                   "Permission masks and access words remain raw, not writable/read-only declarations.",
                   "Catalog enum row IDs are not automatically mapped to wire enum values.",
                   "No archive download, device access, firmware generation or flashing is performed.",
                   "Generated local outputs can contain proprietary catalog text; do not publish them wholesale."]}
    totals = collections.Counter()
    opener = gzip.open if args.output.name.endswith(".gz") else open
    try:
        with opener(args.output, "wt", encoding="utf-8") as stream:
            for index,path in enumerate(files, 1):
                try:
                    result = inspect_profile(path, catalog)
                    stream.write(json.dumps(result, ensure_ascii=False, allow_nan=False)+"\n")
                    summary["profiles_parsed"] += 1
                    summary["point_records"] += result["point_count"]
                    summary["objects"] += result["object_count"]
                    totals.update(result["limitations"])
                except (FormatError, ValueError, struct.error) as error:
                    summary["failures"].append({"profile":path.name,"error":str(error),
                        "sha256":hashlib.sha256(path.read_bytes()).hexdigest()})
                if index % 50 == 0 or index == len(files):
                    print(json.dumps({"processed":index,"total":len(files),
                        "parsed":summary["profiles_parsed"],"failures":len(summary["failures"])}), flush=True)
    finally:
        catalog.close()
        summary["limitation_counts"] = dict(totals)
        args.summary.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    return 1 if summary["failures"] else 0


if __name__ == "__main__":
    sys.exit(main())
