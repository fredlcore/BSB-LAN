"""Exercise real RVA decode/SET code with recorded payloads and malformed input."""
import re
import unittest

from source_harness import ROOT, between, compile_and_run


class LegacyRvaRegression(unittest.TestCase):
    def test_decoded_state_is_normalized_and_preserves_frames(self):
        printing = (ROOT / "BSB_LAN/include/print_telegram.h").read_text(encoding="utf-8")
        decoder = "case VT_ENABLE_STATE:" + between(printing, "case VT_ENABLE_STATE:", "case VT_CUSTOM_ENUM:")
        gain_decoder = "case VT_CUSTOM_BYTE:" + between(printing, "case VT_CUSTOM_BYTE:", "case VT_CUSTOM_BIT:")
        header = (ROOT / "BSB_LAN/include/legacy_rva.h").as_posix()
        language = (ROOT / "BSB_LAN/localization/LANG_EN.h").as_posix()
        compile_and_run(r'''
#include <stdio.h>
#include <string.h>
#include <string>
#include "''' + language + r'''"
#include "''' + header + r'''"
typedef uint8_t byte;
enum { VT_ENABLE_STATE, VT_RAW_ONOFF, VT_CUSTOM_BYTE };
#define pgm_read_byte_far(p) (*reinterpret_cast<const unsigned char *>(p))
struct Bus { int getPl_start() const { return 13; } } instance, *bus=&instance;
struct Decoded { uint8_t type; uint32_t flags; const char *enumstr; uint16_t enumstr_len;
                 char value[32]; int error; } decodedTelegram;
static void printENUM(const char *, uint16_t, uint16_t value, int) {
  snprintf(decodedTelegram.value,sizeof(decodedTelegram.value),"%u",value);
}
static void printToDebug(const char *) {}
static const char *printError(int) { return "error"; }
static void SerialPrintData(byte *) {}
static void undefinedValueToBuffer(char *out) { strcpy(out,"---"); }
static void decode(byte *msg, int data_len) {
  switch(decodedTelegram.type) { ''' + decoder + gain_decoder + r''' }
}
#define CHECK(c) do { if(!(c)) { fprintf(stderr,"line %d: %s\n",__LINE__,#c);return 1;} } while(0)
int main() {
  byte frame[40]={};
  frame[13]=0; frame[14]=4;
  decodedTelegram.type=VT_ENABLE_STATE;
  decode(frame,2); CHECK(std::string(decodedTelegram.value)=="1" && !decodedTelegram.error);
  frame[13]=1;
  decode(frame,2); CHECK(std::string(decodedTelegram.value)=="0" && frame[14]==4);
  frame[14]=15;
  decode(frame,2); CHECK(std::string(decodedTelegram.value)=="0"); // gain is independent
  frame[13]=2;
  decode(frame,2); CHECK(decodedTelegram.error==256 && std::string(decodedTelegram.value)=="---");
  decodedTelegram.error=0;
  decode(frame,1); CHECK(decodedTelegram.error==256); // truncated scalar cannot look like off

  decodedTelegram={}; decodedTelegram.type=VT_CUSTOM_BYTE;
  decodedTelegram.enumstr=RVA_GAIN_BYTE; decodedTelegram.enumstr_len=sizeof(RVA_GAIN_BYTE);
  frame[13]=1; frame[14]=4;
  decode(frame,2); CHECK(std::string(decodedTelegram.value)=="4" && !decodedTelegram.error);
  decode(frame,1); CHECK(decodedTelegram.error==256); // missing retained gain is not a checksum byte

  memset(frame,0,sizeof(frame));
  decodedTelegram={}; decodedTelegram.type=VT_RAW_ONOFF;
  decodedTelegram.flags=(2u<<16)|(1u<<20);
  frame[15]=0xFF;
  const std::string original(reinterpret_cast<char*>(frame),sizeof(frame));
  decode(frame,8); CHECK(std::string(decodedTelegram.value)=="1" && !decodedTelegram.error);
  CHECK(std::string(reinterpret_cast<char*>(frame),sizeof(frame))==original);
  frame[15]=0; frame[16]=0xFF;
  decode(frame,8); CHECK(std::string(decodedTelegram.value)=="0"); // Q3 does not become Q1
  decode(frame,3); CHECK(decodedTelegram.error==256); // no partial raw block
  decodedTelegram.error=0; frame[15]=2;
  decode(frame,8); CHECK(decodedTelegram.error==256); // unknown boolean is not silently false
  decodedTelegram.error=0; decodedTelegram.flags=(8u<<16)|(1u<<20);
  decode(frame,8); CHECK(decodedTelegram.error==256); // no out-of-bounds field
  return 0;
}
''')

    def test_verified_set_ranges_and_disable_payload(self):
        sketch = (ROOT / "BSB_LAN/BSB_LAN.ino").read_text(encoding="utf-8")
        encode = "case VT_TEMP:\n    case VT_TEMP_N:" + between(
            sketch, "case VT_TEMP:\n    case VT_TEMP_N:", "    // Schedule data")
        preserve = "// In case of disable value," + between(sketch, "  // In case of disable value,", "  // Send a message to PC hardware serial port")
        header = (ROOT / "BSB_LAN/include/legacy_rva.h").as_posix()
        language = (ROOT / "BSB_LAN/localization/LANG_EN.h").as_posix()
        compile_and_run(r'''
#include <stdio.h>
#include <initializer_list>
#include "''' + language + r'''"
#include "''' + header + r'''"
enum { VT_TEMP, VT_TEMP_N, VT_ENUM };
#define FL_SPECIAL_INF 16
#define FL_DISABLE_05 1024
#define TYPE_ANS 7
struct Decoded { int type; int enable_byte; double operand; uint8_t payload[3]; int payload_length; int error; int msg_type; } decodedTelegram;
struct Command { uint32_t flags; } commands[]={{0}};
static const Command *active_cmdtbl=commands;
static void printlnToDebug(const char *) {}
static bool query_failure=false;
static void query(float) { // response shaped exactly as an actual differential read
  decodedTelegram.payload[0]=0; decodedTelegram.payload[1]=0; decodedTelegram.payload[2]=0x40;
  decodedTelegram.payload_length=3; decodedTelegram.enable_byte=1;
  decodedTelegram.error=query_failure ? 261 : 0; decodedTelegram.msg_type=TYPE_ANS;
}
static bool make_payload(const char *val, uint32_t dev_flags, uint8_t *param) {
  const bool setcmd=true; const int i=0; const float line=760; const int param_len=3;
  decodedTelegram.type=VT_TEMP; decodedTelegram.operand=64; decodedTelegram.enable_byte=1;
  switch(decodedTelegram.type) { ''' + encode + r''' }
  ''' + preserve + r'''
  return true;
}
#define CHECK(c) do { if(!(c)) { fprintf(stderr,"line %d: %s\n",__LINE__,#c);return 1;} } while(0)
int main() {
  const uint32_t diff=0x0500060F, adaptation=0x0500060B;
  for(const char *v:{"0.5","1","4.0","---",""}) CHECK(legacyRvaSettingValid(1,22,254,diff,v,true));
  for(const char *v:{"0","4.5","nan","inf","1junk","--","0,5"}) CHECK(!legacyRvaSettingValid(1,22,254,diff,v,true));
  CHECK(!legacyRvaSettingValid(1,22,254,diff,"1",false));
  CHECK(legacyRvaSettingValid(1,22,254,adaptation,"0",true));
  CHECK(legacyRvaSettingValid(1,22,254,adaptation,"1",true));
  CHECK(!legacyRvaSettingValid(1,22,254,adaptation,"2",true));
  CHECK(!legacyRvaSettingValid(1,22,254,adaptation,"garbage",true));
  CHECK(legacyRvaSettingValid(1,22,253,diff,"0",true)); // no policy change for untested variants
  CHECK(legacyRvaSettingValid(0,22,254,diff,"0",true)); // LPB-only validation
  uint8_t p[3]={};
  CHECK(make_payload("---",FL_DISABLE_05,p)); CHECK(p[0]==5 && p[1]==0 && p[2]==0x40);
  CHECK(make_payload("1",FL_DISABLE_05,p)); CHECK(p[0]==1 && p[1]==0 && p[2]==0x40);
  CHECK(make_payload("0.5",FL_DISABLE_05,p)); CHECK(p[0]==1 && p[1]==0 && p[2]==0x20);
  CHECK(make_payload("---",0,p)); CHECK(p[0]==0 && p[2]==0x40); // original disable behavior
  query_failure=true; CHECK(!make_payload("---",FL_DISABLE_05,p)); // no SET after a failed fresh query
  return 0;
}
''')

    def test_default_profile_is_scoped_and_unverified_writes_are_readonly(self):
        default = (ROOT / "BSB_LAN/BSB_LAN_custom_defs.h.default").read_text(encoding="utf-8")
        rows = [line for line in default.splitlines() if line.startswith("{") and "DEV_022_254" in line]
        self.assertEqual(len(rows), 6)
        for number in ("700", "750", "750.1", "8730"):
            matching = [r for r in rows if re.search(r",\s*" + re.escape(number) + r"\s*,", r)]
            self.assertEqual(len(matching), 1)
            self.assertIn("FL_RONLY", matching[0])
        difference = next(r for r in rows if "760," in r)
        self.assertIn("VT_TEMP,", difference)  # active byte 01, not unverified 06
        self.assertIn("FL_DISABLE_05", difference)
        self.assertIn("FL_ENUM_2_1", next(r for r in rows if "8730," in r))
        defs = (ROOT / "BSB_LAN/BSB_LAN_defs.h").read_text(encoding="utf-8")
        self.assertIn("VT_UNKNOWN,\n  // Append new types", defs)
        enum = defs.split("}vt_type_t;", 1)[0].rsplit("typedef enum{", 1)[1]
        enum = re.sub(r"//[^\n]*|/\*.*?\*/", "", enum, flags=re.S)
        self.assertEqual(re.findall(r"\bVT_[A-Z0-9_]+\b", enum),
                         re.findall(r"^\{(VT_[A-Z0-9_]+),", defs, re.M))
        sketch = (ROOT / "BSB_LAN/BSB_LAN.ino").read_text(encoding="utf-8")
        self.assertIn("legacyRvaSettingValid(bus->getBusType(), my_dev_fam, my_dev_var, c, val, setcmd)", sketch)

    def test_m_profile_is_readonly_and_keeps_legacy_scaling(self):
        default = (ROOT / "BSB_LAN/BSB_LAN_custom_defs.h.default").read_text(encoding="utf-8")
        rows = [r for r in default.splitlines() if r.startswith("{") and "DEV_023_254" in r]
        self.assertEqual(len(rows), 23)
        for row in rows:
            self.assertIn("FL_RONLY", row)
            self.assertNotIn("DEFAULT_FLAG", row)
            self.assertNotIn("FL_DISABLE_05", row)
        by_number = {float(r.split(",")[2]): r for r in rows}
        self.assertIn("VT_BYTE2", by_number[720])  # 00 1C = 14.0, not a modern 1.4 slope
        self.assertIn("VT_MINUTES_SHORT", by_number[830.1])
        self.assertIn("FL_ENUM_2_1", by_number[8730])
        self.assertIn("FL_ENUM_0_1", by_number[8731])
        self.assertIn("FL_ENUM_1_1", by_number[8732])
        self.assertIn("0x0500051E", by_number[8740])
        self.assertIn("0x05000667", by_number[8744])
        # Newly added translations also participate in the language undef/fallback cycle.
        for language in ("EN", "DE", "C"):
            source = (ROOT / f"BSB_LAN/localization/LANG_{language}.h").read_text(encoding="utf-8")
            undef = (ROOT / f"BSB_LAN/localization/UNDEF_LANG_{language}.h").read_text(encoding="utf-8")
            for name in re.findall(r"^#define (RVA_\w+_TEXT) ", source, re.M):
                self.assertIn("#undef " + name, undef)

    def test_production_lookup_selects_profile_without_overriding_other_devices(self):
        sketch = (ROOT / "BSB_LAN/BSB_LAN.ino").read_text(encoding="utf-8")
        # Execute the production search for ordinary programs; virtual sensor
        # translation above it is outside this profile's program-number range.
        search = between(sketch, "  int line_dd = roundf(line * 10);", "float get_next_prognr(")
        search = "  int line_dd = roundf(line * 10);" + search
        default = (ROOT / "BSB_LAN/BSB_LAN_custom_defs.h.default").read_text(encoding="utf-8")
        rows = [r for r in default.splitlines() if r.startswith("{") and
                ("DEV_022_254" in r or "DEV_023_254" in r or
                 re.search(r",\s*710\s*,", r))]
        standard_strings = "\n".join(f'const char {name}[]="{name}";' for name in
                                     sorted(set(re.findall(r"\bSTR\d+\b", "\n".join(rows)))))
        value_types = ",".join(sorted(set(re.findall(r"\bVT_\w+\b", "\n".join(rows)))))
        header = (ROOT / "BSB_LAN/include/legacy_rva.h").as_posix()
        language = (ROOT / "BSB_LAN/localization/LANG_EN.h").as_posix()
        rows.insert(0, '{0x2D3D0572,VT_ENUM,700,"generic mode",0,nullptr,0,255,255},')
        rows.insert(next(i for i,r in enumerate(rows) if "760," in r),
                    '{0x2D3D0614,VT_TEMP,760,"generic limit",0,nullptr,0,255,255},')
        compile_and_run(r'''
#include <stdio.h>
#include "''' + language + r'''"
#include "''' + header + r'''"
enum { ''' + value_types + r''' };
#define FL_RONLY 1
#define FL_NO_CMD 4
#define FL_DISABLE_05 1024
#define FL_ENUM_2_1 ((2u<<16)|(1u<<20))
#define FL_ENUM_0_1 ((0u<<16)|(1u<<20))
#define FL_ENUM_1_1 ((1u<<16)|(1u<<20))
#define DEFAULT_FLAG 0
#define DEV_022_254 22,254
#define DEV_023_254 23,254
#define DEV_FAM(...) 255
#define DEV_VAR(...) 255
#define DEV_ALL 255,255
#define CMD_END 0xFFFFFFFFu
#define DEVELOPER_DEBUG 2
static int verbose=0;
static void printFmtToDebug(const char *,...) {}
const char ENUM_ONOFF[]={0,' ','O','f','f',0,1,' ','O','n',0};
''' + standard_strings + r'''
struct cmd_t { uint32_t cmd; uint8_t type; float line; const char *desc; uint16_t enumstr_len;
               const char *enumstr; uint32_t flags; uint8_t dev_fam; uint8_t dev_var; };
const cmd_t table[]={
''' + '\n'.join(rows) + r'''
{CMD_END,VT_ENUM,65535,"end",0,nullptr,0,255,255}
};
static const cmd_t *active_cmdtbl=table;
static uint16_t active_cmdtbl_size=sizeof(table)/sizeof(table[0]);
static uint8_t my_dev_fam=22,my_dev_var=254;
static int findLine(float line) {
  uint8_t found=0; int i=-1,save_i=0; uint32_t c; float l;
''' + search + r'''
#define CHECK(c) do { if(!(c)) { fprintf(stderr,"line %d: %s\n",__LINE__,#c);return 1;} } while(0)
int main() {
  CHECK(table[findLine(700)].cmd==0x05000074);
  CHECK(table[findLine(700)].enumstr==RVA_MODE_ENUM);
  CHECK(table[findLine(700)].enumstr_len==sizeof(RVA_MODE_ENUM));
  CHECK(table[findLine(760)].cmd==0x0500060F);
  CHECK(table[findLine(750.1)].type==VT_ENABLE_STATE);
  CHECK(table[findLine(750.1)].flags & FL_RONLY);
  CHECK(table[findLine(8730)].type==VT_RAW_ONOFF);
  CHECK(table[findLine(710)].cmd==0x2D3D058E); // K keeps its existing generic row
  CHECK(findLine(8743)==-1);
  my_dev_fam=23;
  CHECK(table[findLine(700)].cmd==0x05000074);
  CHECK(table[findLine(700)].enumstr==RVA_M_MODE_ENUM);
  CHECK(table[findLine(700)].enumstr_len==sizeof(RVA_M_MODE_ENUM));
  // Firmware enum entries have a binary code followed by a space and text.
  // Locate code 4 using the table's byte size, not strlen(table).
  bool continuous_found=false;
  for(size_t n=0;n+2<sizeof(RVA_M_MODE_ENUM);++n) {
    if((unsigned char)RVA_M_MODE_ENUM[n]==4 && RVA_M_MODE_ENUM[n+1]==' ')
      continuous_found=strcmp(RVA_M_MODE_ENUM+n+2,"Continuous operation")==0;
  }
  CHECK(continuous_found);
  CHECK(table[findLine(710)].cmd==0x05000458);
  CHECK(table[findLine(710)].flags & FL_RONLY);
  CHECK(table[findLine(726)].flags & FL_RONLY);
  CHECK(table[findLine(760)].flags==FL_RONLY);
  CHECK(table[findLine(8730)].flags==(FL_RONLY|FL_ENUM_2_1));
  CHECK(table[findLine(8731)].flags==(FL_RONLY|FL_ENUM_0_1));
  CHECK(table[findLine(8732)].flags==(FL_RONLY|FL_ENUM_1_1));
  CHECK(table[findLine(8740)].cmd==0x0500051E);
  CHECK(table[findLine(8743)].cmd==0x05000464);
  my_dev_var=253;
  CHECK(table[findLine(710)].cmd==0x2D3D058E && findLine(8731)==-1);
  my_dev_fam=90;my_dev_var=239;
  CHECK(table[findLine(700)].cmd==0x2D3D0572);
  CHECK(table[findLine(760)].cmd==0x2D3D0614);
  CHECK(findLine(750.1)==-1 && findLine(8730)==-1);
  my_dev_fam=22;my_dev_var=253;
  CHECK(table[findLine(700)].cmd==0x2D3D0572 && findLine(750.1)==-1);
  return 0;
}
''')


if __name__ == "__main__":
    unittest.main()
