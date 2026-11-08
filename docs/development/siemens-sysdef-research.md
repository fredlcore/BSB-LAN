# Inspecting locally supplied Siemens system definitions

The optional `tools/siemens_sysdef.py` script examines offline OZW device
descriptions. It has no network or heating-bus implementation. It never sends
telegrams, installs a system definition, or generates firmware automatically.

The input files must be obtained separately. This repository should contain the
reader, synthetic tests, and a small independently verified findings table; it
does not need a vendor archive, the full translation catalog, or extracted APW
files. Generated corpus files contain catalog text and should remain local.

## Observed package layout

The investigated `OZW672_Systemdefinition_V02.37.1.zip` has SHA-256
`1ba27ab37cb9ca9db9b2de6243ef7395807029d324a35a1fe3dabed566fa398e`.
It contains a supported-device report PDF and a file ending in `.sysdef2`.
The latter is an ordinary, unencrypted 7-Zip container, despite its extension.
Its member inventory includes:

- `sysdef/catalog/lpb.sdf`: SQLite 3 database, including message, enum, type,
  range, and unit catalogs. The extension does not imply SQL Server Compact.
- `sysdef/dd/*.apw`: binary device descriptions.
- `sysdef/deviceicons/*.png`: device icons.
- A version marker.

The tested package has 782 APW descriptions and 782 icons. The descriptions
occupy 224,474,524 uncompressed bytes. Only device descriptions and the SQLite
catalog are required by the script. A 7-Zip installation can extract them
locally; do not execute an updater to inspect these files.

## Run the reader

Python 3.10 or later, with its standard library, is sufficient. After extracting
the package locally:

```sh
python tools/siemens_sysdef.py \
  --profiles /local/sysdef/dd \
  --catalog /local/sysdef/catalog/lpb.sdf \
  --output /local/results/device-points.jsonl.gz \
  --summary /local/results/summary.json
```

The paths are examples; choose local paths. The script refuses to overwrite an
existing output or summary. `--language 1` selects English catalog labels and
`--language 2` selects German. It opens the SQLite source read-only and enables
SQLite's `query_only` setting. A `.gz` output is streamed as one JSON profile
record per line, so a large corpus need not be kept in memory at once.
An optional filename filter such as `--pattern 'D0016*.apw'` narrows a local
research run without changing or deleting the complete extracted corpus.

Run tests with:

```sh
python -m unittest discover -s tests -p test_siemens_sysdef.py
```

The fixtures are created in memory and contain no vendor data.

## APW structural observations

The reader supports the observed serialization, rather than claiming a complete
vendor format specification:

1. Integers in the identified object headers are big-endian.
2. A newly encountered class definition has an object ID, class ID, a 32-bit
   byte length, and an ASCII class name such as `COzwFLN_DP`.
3. Subsequent instances can refer to the same class ID without repeating its
   name. Object definitions have unique IDs; arbitrary primitive values inside
   their bodies are not interpreted as new objects.
4. The four-byte strings `OBST` and `OBEN`, each preceded by a big-endian length
   of four, delimit nested object bodies.
5. The reader retains each object's original file offset and separates its
   own data from nested objects. Invalid class lengths, unknown references,
   duplicate definitions, overlapping objects, unbalanced delimiters, and
   unframed marker occurrences cause an explicit profile failure. It does not
   attempt to repair or skip damaged bytes.

For `COzwFLN_DP`, the tested layout has a 12-byte tail. Its first 32-bit field
contains the observed class/object address. For example, `00 05 06 0f` becomes
the LPB query candidate `05 00 06 0f`. The following two fields remain raw
`raw_access_word` and `raw_final_word`. A value of one frequently accompanies
settings, but this is not proof that a controller accepts writes.
Some instances reuse a previously defined scalar handler: the body has a
four-byte handler reference followed by the 12-byte tail. Supported scalar
handlers similarly have a nine-byte prefix followed by an inline value object
or a four-byte reference to a previously defined value. The reader resolves
only these bounded, class-checked reference positions, not arbitrary integers
in object payloads.

For `COzwBlock_DP`, the reader retains the complete direct header, the address
field at header bytes 4 through 7, and each `COzwCommObjField` tail. A two-byte
field tail is reported as a candidate byte offset into the raw block. A block
does not automatically have the validity prefix used by scalar replies.

## Catalog links and type metadata

For supported value classes, a `COzwCustomAttributes` object is followed by
the value object's common metadata. The first two bytes link to
`MessageSetID=2`, `MessageRowID=<value>` in the message catalog. The long
display label uses `MessageIndex=1`; labels are joined in the requested language.

The common metadata has a variable-length UTF-8 reference string, whose length
is the 32-bit field at byte 16. With an empty reference, the common portion ends
at byte 28. A nonempty reference shifts subsequent fields by its byte length.
The reference is preserved as a candidate identifier; it is not assumed to be
the controller panel number without verification.

Known numeric value classes have a candidate unit ID immediately after this
common portion, followed by a big-endian double. Nonfinite doubles are retained
as strings alongside their exact eight original bytes, rather than causing an
entire profile to be discarded. Unit scaling is recorded from `ValueUnit`,
including its catalog ID, resolution, slope, and intercept. Multiple catalog
records are retained rather than choosing one silently. The interpretation is
an observed-layout inference and must be checked before creating firmware
definitions.
Inline `COzwFloatLimit` objects retain original offsets and bytes. The observed
16-byte form has a lower/upper selector, a raw numeric bound, and a trailing
reference field. For the RVA43 room differential, the two raw limits are 32
and 256, which the unit scaling converts to 0.5 and 4.0 K. Zero is outside the
active numeric range; this alone does not identify a disabled-value encoding.

Boolean and enumerated value classes also contain candidate message-set links.
The exporter includes the matching catalog rows. Message row IDs are **not**
wire values. An enum with rows numbered 1 through 5 can describe wire values
0 through 4; boolean wire values can be `00` and `ff`. Validate the encoding
against the exact value class and actual frames.

Common masks and flags remain hexadecimal fields. Their permission, feature,
or validity meanings have not been fully established. The exporter deliberately
does not turn them into writable/read-only declarations.

## Independently checked RVA43 findings

These are observations from one real family-22 controller and supporting
manufacturer descriptions, not a compatibility guarantee for all variants:

| Function | LPB CoID | Interpretation checked on the device |
| --- | --- | --- |
| Room switching differential, Eurocontrol K panel 67 | `0500060F` | Scalar `00 00 40` means 1.0 K: valid flag `00`, signed value `0040`, slope 1/64. |
| Heating-curve adaptation, panel 71 | `0500060B` | Scalar `00 ff`: valid and enabled. |
| Pump contact Q1 | `05000488` | Eight-byte raw relay block; third byte (zero-based offset 2) is contact Q1. `ff` matched a running pump. |
| Controller operating mode | `05000074` | Value 4 matched manual operation shown at the controller. |
| Room influence, panel 65, and OEM gain KORR | `05000603` | Enabled read `00 04`; after changing panel 65 from 1 to 0, disabled read `01 04`. Gain 4 remains unchanged. |

Panel 65 was resolved with a controlled change at the actual controller. Before
the user changed that panel setting from 1 to 0, the same query returned
`00 04`; immediately afterwards it returned `01 04`. The numeric byte remained
4. The manufacturer label identifies the gain, while the scalar validity/enable
state also reflects whether room influence is enabled. This is a shared object,
not a separately exposed scalar boolean. No remote SET representation for panel
65 was tested, so its write encoding remains unverified.

### Separately verified setting writes on that controller

Read and write prefixes must be distinguished. The following payloads were
verified after the initial read-only investigation; they are not universal
instructions for every device in the package:

- For `0500060F`, SET payload `01 00 40` preserves an active value of 1.0 K.
  SET payload `05 00 40` disables the setting while retaining its raw numeric
  component. The controller acknowledged it; an independent read returned
  `01 00 40`, whose read validity flag indicates the disabled state.
- The ordinary disabled prefix `00` was rejected for this setting. A confirmed
  BSB-LAN `VT_TEMP_N` representation uses disabled prefix `05`. This does not
  establish every other active prefix or nullable-value encoding.
- For `0500060B`, SET payload `01 00` was acknowledged and read back as `00 00`
  (adaptation off).

These observations support a family-specific definition and tests. They do not
justify making all extracted numeric datapoints writable or guessing a sentinel.

The scalar functions were found under the `05` address class. Previously tried
modern heating-circuit candidates under `2d` returned error 07. The old room
switching differential also uses object `060f`, rather than modern `0614`.
Controller panel numbers are not raw LPB CoIDs.

The tested device did not identify itself as an exact package profile. Profiles
`D0016680.apw` and `D0016682.apw` supplied useful independent address evidence,
but only the actual successful reads establish support on that controller.
Do not force the entire device to a different family or variant merely to make
these definitions visible.

## Review boundaries

- Keep successful device observations separate from static candidates.
- Preserve source hashes and offsets, and include representative synthetic
  parser tests and compact sanitized frames when submitting a change.
- Verify existing definitions for duplicate CoIDs and family-specific meanings
  before adding entries. Some labels describe OEM parameters, not the similarly
  named user-facing setting.
- A live read does not prove a safe write encoding. Disabled-value sentinels,
  scalar validity flags, and block layouts require separate verification.
- No separate panel-65 boolean was identified by the initial static search in
  21 family-22 descriptions. A subsequent controlled panel change established
  that its state is carried by the validity/enable byte of `05000603`. Searching
  only for a label or a numeric zero/one would have missed this relationship.
- This reader is a research aid. Unknown value handlers, unsupported tail
  lengths, and parsing failures are listed in its summary and must not be
  treated as absent datapoints.
