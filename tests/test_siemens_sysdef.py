"""Synthetic fixtures exercise parser boundaries without shipping vendor files."""
import importlib.util
import json
from pathlib import Path
import struct
import sys
import unittest

MODULE = Path(__file__).resolve().parents[1] / 'tools' / 'siemens_sysdef.py'
spec = importlib.util.spec_from_file_location('siemens_sysdef', MODULE)
sysdef = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = sysdef
spec.loader.exec_module(sysdef)

START = struct.pack('>I',4) + b'OBST'
END = struct.pack('>I',4) + b'OBEN'

def obj(oid,cid,name,body):
    head = struct.pack('>II',oid,cid)
    if name:
        encoded=name.encode('ascii')
        head += struct.pack('>I',len(encoded)) + encoded
    return head + START + body + END

class FakeCatalog:
    labels={207:'Room switching differential',238:'Contact Q1'}
    def unit(self,unit):
        return [{'UnitID':unit,'UnitCatalogID':1,'Slope':1/64}] if unit==7 else []
    def enum(self,set_id):
        return []

class ParserTests(unittest.TestCase):
    def test_nested_objects_keep_exact_original_offsets(self):
        child=obj(1,1,'COzwChild',b'abc')
        data=obj(0,0,'COzwRoot',b'pre'+child+b'post')
        root,leaf=sysdef.parse_apw(data)
        self.assertEqual(root.end,len(data))
        self.assertEqual(data[leaf.body_start:leaf.body_end],b'abc')
        self.assertEqual([raw for _,raw in root.parts],[b'pre',b'post'])

    def test_reused_class_reference_does_not_require_repeated_name(self):
        child=obj(1,0,None,b'abc')
        nodes=sysdef.parse_apw(obj(0,0,'COzwRoot',child))
        self.assertEqual([n.class_name for n in nodes],['COzwRoot','COzwRoot'])

    def test_missing_end_is_rejected(self):
        with self.assertRaisesRegex(sysdef.FormatError,'unterminated'):
            sysdef.parse_apw(obj(0,0,'COzwRoot',b'')[:-8])

    def test_unknown_class_reference_is_rejected(self):
        child=obj(1,99,None,b'abc')
        with self.assertRaisesRegex(sysdef.FormatError,'unknown class'):
            sysdef.parse_apw(obj(0,0,'COzwRoot',child))

    def test_forged_class_length_is_rejected(self):
        data=bytearray(obj(0,0,'COzwRoot',b''))
        struct.pack_into('>I',data,8,1000)
        with self.assertRaisesRegex(sysdef.FormatError,'class-name length'):
            sysdef.parse_apw(bytes(data))

    def test_duplicate_object_definition_is_rejected(self):
        child=obj(0,1,'COzwChild',b'')
        with self.assertRaisesRegex(sysdef.FormatError,'duplicate object'):
            sysdef.parse_apw(obj(0,0,'COzwRoot',child))

    def test_unframed_tag_payload_is_explicitly_unsupported(self):
        with self.assertRaisesRegex(sysdef.FormatError,'unframed tag'):
            sysdef.parse_apw(obj(0,0,'COzwRoot',b'literal OBST text'))

    def test_fln_candidate_uses_bounded_address_and_keeps_raw_access(self):
        attrs=obj(3,3,'COzwCustomAttributes',b'\0'*4)
        metadata=struct.pack('>H',207)+b'\0'*26+struct.pack('>Hd',7,1.0)
        value=obj(2,2,'COzwValI16',attrs+metadata)
        handler=obj(1,1,'COzwDpVhValAnalog',bytes.fromhex('000000020200000001')+value)
        data=obj(0,0,'COzwFLN_DP',handler+struct.pack('>III',0x05060f,1,0))
        points,limits=sysdef.points_from_objects(sysdef.parse_apw(data),FakeCatalog())
        self.assertEqual(limits,{})
        self.assertEqual(points[0]['coid_candidate'],'0500060F')
        self.assertEqual(points[0]['label_row'],207)
        self.assertEqual(points[0]['raw_access_word'],1)
        self.assertNotIn('writable',points[0])
        self.assertEqual(points[0]['numeric_metadata_candidate']['unit_id'],7)

    def test_nonstandard_fln_tail_is_counted_and_not_guessed(self):
        data=obj(0,0,'COzwFLN_DP',b'\0'*11)
        points,limits=sysdef.points_from_objects(sysdef.parse_apw(data),FakeCatalog())
        self.assertEqual(points,[])
        self.assertEqual(limits,{'unsupported_FLN_tail_length':1})

    def test_shared_value_and_handler_references_are_resolved_by_defined_id(self):
        attrs=obj(2,2,'COzwCustomAttributes',b'\0'*4)
        metadata=struct.pack('>H',207)+b'\0'*26+struct.pack('>Hd',7,1.0)
        value=obj(1,1,'COzwValI16',attrs+metadata)
        prefix=bytes.fromhex('000000020200000001')
        handler=obj(3,3,'COzwDpVhValAnalog',prefix+struct.pack('>I',1)+b'\0'*12)
        dp=obj(4,4,'COzwFLN_DP',struct.pack('>IIII',3,0x05060f,1,0))
        data=obj(0,0,'COzwRoot',value+handler+dp)
        points,limits=sysdef.points_from_objects(sysdef.parse_apw(data),FakeCatalog())
        self.assertEqual(limits,{})
        self.assertEqual(points[0]['label_row'],207)
        self.assertEqual(points[0]['handler_reference']['handler_object_id'],3)
        self.assertEqual(points[0]['value_reference']['value_object_id'],1)

    def test_variable_length_reference_shifts_units_and_nonfinite_default_is_preserved(self):
        attrs=obj(1,1,'COzwCustomAttributes',b'\0'*4)
        common=struct.pack('>H',207)+b'\0'*14+struct.pack('>I',3)+b'721'+b'\0'*8
        metadata=common+struct.pack('>Hd',7,float('nan'))
        data=obj(0,0,'COzwValI16',attrs+metadata)
        value=sysdef.parse_apw(data)[0]
        result=sysdef.value_metadata(value,FakeCatalog())
        self.assertEqual(result['parameter_reference_candidate'],'721')
        self.assertEqual(result['numeric_metadata_candidate']['unit_id'],7)
        self.assertEqual(result['numeric_metadata_candidate']['default_double_candidate'],'nan')
        json.dumps(result,allow_nan=False)

    def test_inline_numeric_limits_keep_raw_values_and_bound_kind(self):
        attrs=obj(1,1,'COzwCustomAttributes',b'\0'*4)
        metadata=struct.pack('>H',207)+b'\0'*26+struct.pack('>Hd',7,64.0)
        lower=obj(2,2,'COzwFloatLimit',struct.pack('>IdI',0,32.0,0xffffffff))
        upper=obj(3,2,None,struct.pack('>IdI',1,256.0,0xffffffff))
        data=obj(0,0,'COzwValI16',attrs+metadata+lower+upper)
        result=sysdef.value_metadata(sysdef.parse_apw(data)[0],FakeCatalog())
        limits=result['numeric_metadata_candidate']['inline_limits']
        self.assertEqual([x['bound_kind_candidate'] for x in limits],['lower','upper'])
        self.assertEqual([x['raw_value_double_candidate'] for x in limits],[32.0,256.0])

    def test_raw_block_byte_offset_is_preserved_without_validity_adjustment(self):
        attrs=obj(4,4,'COzwCustomAttributes',b'\0'*4)
        value=obj(3,3,'COzwValB',attrs+struct.pack('>H',238)+b'\0'*36)
        handler=obj(2,2,'COzwDpVhValB',value)
        field=obj(1,1,'COzwCommObjField',handler+b'\x00\x02')
        header=struct.pack('>II',0xffffffff,0x050488)+b'\0'*15
        data=obj(0,0,'COzwBlock_DP',header+field)
        points,_=sysdef.points_from_objects(sysdef.parse_apw(data),FakeCatalog())
        self.assertEqual(points[0]['coid_candidate'],'05000488')
        self.assertEqual(points[0]['block_byte_offset_candidate'],2)
        self.assertEqual(points[0]['field_tail_hex'],'0002')

if __name__=='__main__':
    unittest.main()
