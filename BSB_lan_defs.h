/****************************************************/
/* DEFINITIONS and TYPEDEFS                         */
/****************************************************/

#if defined(__SAM3X8E__)
#undef uint_farptr_t
#define uint_farptr_t const char*
#endif

#ifndef LANG
#define LANG EN
#endif

#ifdef DebugTelnet
#define DebugOutput telnetClient
#else
#define DebugOutput Serial
#endif

#include "localization/LANG_DE.h"
#include "localization/UNDEF_LANG_EN.h"
#include "localization/LANG_EN.h"
#define xstr(x) #x
#define str(x) xstr(x)
#define sub(x) x
#define FILE1 str(sub(localization/UNDEF_LANG_)LANG.h)
#define FILE2 str(sub(localization/LANG_)LANG.h)
#include FILE1
#include FILE2

#if defined(__SAM3X8E__)
#define PROGMEM_LATE 
#define PROGMEM_LATEST
#else
#define PROGMEM_LATE __attribute__ (( __section__(".fini1") ))
#define PROGMEM_LATEST __attribute__ (( __section__(".fini1") ))
#endif

/* telegram types */
#define TYPE_QINF 0x01 // request info telegram
#define TYPE_INF  0x02 // send info telegram
#define TYPE_SET  0x03 // set parameter
#define TYPE_ACK  0x04 // acknowledge set parameter
#define TYPE_NACK 0x05 // do not acknowledge set parameter
#define TYPE_QUR  0x06 // query parameter
#define TYPE_ANS  0x07 // answer query
#define TYPE_ERR  0x08 // error
#define TYPE_QRV  0x0F // query  reset value
#define TYPE_ARV  0x10 // answer reset value
#define TYPE_IQ1  0x12 // internal query type 1 (still undecoded)
#define TYPE_IA1  0x13 // internal answer type 1 (still undecoded)
#define TYPE_IQ2  0x14 // internal query type 2 (still undecoded)
#define TYPE_IA2  0x15 // internal answer type 2 (still undecoded)

/* telegram addresses */
#define ADDR_HEIZ  0x00
#define ADDR_EM1   0x03
#define ADDR_EM2   0x04
#define ADDR_RGT1  0x06
#define ADDR_RGT2  0x07
#define ADDR_CNTR  0x08
#define ADDR_DISP  0x0A
#define ADDR_SRVC  0x0B
#define ADDR_OZW   0x31
#define ADDR_FE    0x32
#define ADDR_LAN   0x42
#define ADDR_ALL   0x7F

#define BUS_BSB 0
#define BUS_LPB 1
#define BUS_PPS 2

/* special command ids */
#define CMD_UNKNOWN 0x00000000u
#define CMD_END     0xffffffffu
#define FL_RONLY    1
#define FL_NO_CMD   2
#define FL_OEM      5    // Known OEM parameters are set to read-only by default. If you want to have general write-access (not recommended!) to OEM parameters, set FL_OEM to 4.
#define FL_SPECIAL_INF  8 // Flag to distinguish between INF telegrams that reverse first two bytes (like room temperature) and those who don't (like outside temperature)

/* heating systems */

#define DEV_021_ALL  21,255 // RVL470
#define DEV_023_ALL  23,255 // Grünenwald RVA46.531/109
#define DEV_028_ALL  28,255 // Brötje SOB26 / LPB
#define DEV_029_ALL  29,255 // Grünenwald RVA63.280/109
#define DEV_036_ALL  36,255 // RVL472
#define DEV_049_ALL  49,255 // Weishaupt WRS-CPU-B1
#define DEV_050_ALL  50,255 // Weishaupt
#define DEV_052_ALL  52,255 // Weishaupt WRS-BE
#define DEV_059_ALL  59,255 // Weishaupt WRS-CPU-B3
#define DEV_064_ALL  64,255 // Brötje WGB 2 (über OCI420)
#define DEV_076_ALL  76,255 // RVA63.244/160
#define DEV_085_ALL  85,255 // Elco Aquatop 8es
#define DEV_090_ALL  90,255 // RVS43.222 SSR C
#define DEV_091_ALL  91,255 // AVS75.390 Erweiterungsmodul (EWM)
#define DEV_092_ALL  92,255 // AVS37.294/100 (Bedienteil von Brötje EcoTherm WGB 20 E)
#define DEV_094_ALL  94,255 // QAA75.611/101
#define DEV_095_ALL  95,255 // Brötje LogoBloc Unit L-UB 25C
#define DEV_096_ALL  96,255 // Brötje NovoCondens SOB 22C, 26C
#define DEV_097_100  97,100 // Brötje WGB 20 C
#define DEV_097_ALL  97,255 // Elco Thision S 17.1, Brötje WBS 14D
#define DEV_098_ALL  98,255 // Brötje Ecotherm Plus WGB Pro Evo 20C, EcoCondens BBS Pro EVO 15 C
#define DEV_103_ALL  103,255 // CTC 380 IC
#define DEV_107_ALL  107,255 // RVS43.222-Z1
#define DEV_108_ALL  108,255 // Brötje Sensotherm BSW-K
#define DEV_108_100  108,100 // Brötje BSW 8K
#define DEV_108_160  108,160 // Elco AEROTOP T07-16 mit Logon B WP 61
#define DEV_108_169  108,169 // Wärmepumpe CTA Optiheat 1-18es RVS61.843D/169
#define DEV_116_ALL  116,255 // Brötje ISR-SSR B
#define DEV_118_ALL  118,255 // AVS37.394/136 (Bedieneinheit von Thision S 17.1)
#define DEV_119_ALL  119,255 // Waterstage WP 5kw
#define DEV_123_ALL  123,255 // Brötje EcoTherm Kompakt WMS 24
#define DEV_133_ALL  133,255 // QAA75.910/349
#define DEV_136_ALL  136,255 // AVS75.391/109
#define DEV_137_ALL  137,255 // AGU2.550 Mischer-ClipIn
#define DEV_138_ALL  138,255 // Brötje BOB
#define DEV_162_ALL  162,255 // Brötje WGB 15 E, WGB-S 17/20E, WBS 22 E
#define DEV_163_ALL  163,255 // Brötje WGB Evo 20 H
#define DEV_164_ALL  164,255 // AVS37.295/309 Olymp WHS-500 Luft-/Wasser-Wärmepumpe
#define DEV_165_ALL  165,255 // Funkempfänger FE ISR Plus AVS71.411/349
#define DEV_170_ALL  170,255 // Fujitsu Waterstage WSYK160DC9
#define DEV_171_ALL  171,255 // Bösch PEO Wood Pellet RVS43.344/146
#define DEV_172_ALL  172,255 // SensoTherm BLW Split B (RVS21.826F/200)
#define DEV_184_ALL  184,255 // OZW672.01
#define DEV_186_ALL  186,255 // AVS75.370/109
#define DEV_188_ALL  188,255 // AVS37.296/141
#define DEV_195_ALL  195,255 // MHG Procon E 25 HS
#define DEV_195_002  195,2   // ELCO Thision S Plus 19 (LMS14.111B109)
#define DEV_203_ALL  203,255 // Elco Thision 13 Plus
#define DEV_205_ALL  205,255 // Brötje Sensotherm BLW 15 B
#define DEV_206_ALL  206,255 // AVS74.261/109
#define DEV_211_ALL  211,255 // Fujitsu Waterstage WSYP100DG6 (Gerätevariante: 127, Geräteidentifikation: RVS21.831F/127)
#define DEV_ALL      255,255 // All devices
#define DEV_NONE     0,0

/*
typedef struct {
  uint8_t    dev_family;             // Gerätefamilie
  uint32_t   dev_bit_id;             // Bitmuster
} device_table;

PROGMEM_LATE const device_table dev_tbl[]={
//{1,   DEV_LPB},
{28,  DEV_028_ALL},
{85,  DEV_085_ALL},
{50,  DEV_050_ALL},
{97,  DEV_097_ALL},
{90,  DEV_090_ALL},
{95,  DEV_095_ALL},
{96,  DEV_096_ALL},
{98,  DEV_098_ALL},
{103, DEV_103_ALL},
{107, DEV_107_ALL},
{108, DEV_108_ALL},
{116, DEV_116_ALL},
{138, DEV_138_ALL},
{162, DEV_162_ALL},
{163, DEV_163_ALL},
{170, DEV_170_ALL},
{203, DEV_203_ALL},
{205, DEV_205_ALL},
{211, DEV_211_ALL},
{255, DEV_NONE},
};
*/

// Menu Categories
typedef enum{
  CAT_DATUMZEIT,
  CAT_BEDIENEINHEIT,
  CAT_FUNK,
  CAT_ZEITPROG_HK1,
  CAT_ZEITPROG_HK2,
  CAT_ZEITPROG_HKP,
  CAT_ZEITPROG_TWW,
  CAT_ZEITPROG_5,
  CAT_FERIEN_HK1,
  CAT_FERIEN_HK2,
  CAT_FERIEN_HKP,
  CAT_HK1,
  CAT_KUEHL1,
  CAT_HK2,
  CAT_HKP,
  CAT_TW,
  CAT_HXPUMPE,
  CAT_SCHWIMMBAD,
  CAT_VORREGLERPUMPE,
  CAT_KESSEL,
  CAT_SITHERM,
  CAT_WAERMEPUMPE,
  CAT_ENERGIEZAEHLER,
  CAT_KASKADE,
  CAT_ZUSATZERZEUGER,
  CAT_SOLAR,
  CAT_FESTSTOFFKESSEL,
  CAT_PUFFERSPEICHER,
  CAT_TWSPEICHER,
  CAT_DRUCHLERHITZER,
  CAT_KONFIG,
  CAT_LPB,
  CAT_FEHLER,
  CAT_WARTUNG,
  CAT_MODULE,
  CAT_IOTEST,
  CAT_STATUS,
  CAT_DIAG_KASKADE,
  CAT_DIAG_ERZEUGER,
  CAT_DIAG_VERBRAUCHER,
  CAT_FEUERUNGSAUTOMAT,
  CAT_USER_DEFINED,
  CAT_PPS,
  CAT_UNKNOWN
}category_t;

/* Parameter types */
typedef enum{
  VT_BIT,               //  2 Byte - 1 enable 0x01 / value
  VT_BYTE,              //  2 Byte - 1 enable 0x01 / value
  VT_CLOSEDOPEN,        //  2 Byte - 1 enable 0x01 / 0=Offen 1=Geschlossen Choice
  VT_DAYS,              //  2 Byte - 1 enable 0x01 / day
  VT_ENUM,              //* 2 Byte - 1 enable 0x01 / value        Choice
  VT_GRADIENT_SHORT,    //  2 Byte - 1 enable / value min/K
  VT_HOURS_SHORT,       //  2 Byte - 1 enable 0x01 / hours        Int08
  VT_LPBADDR,           //* 2 Byte - 1 enable / adr/seg           READ-ONLY
  VT_MINUTES_SHORT,     //  2 Byte - 1 enable 0x06 / minutes      Int08S
  VT_MONTHS,            //  2 Byte - 1 enable 0x06 / months       Int08S
  VT_ONOFF,             //  2 Byte - 1 enable 0x01 / 0=Aus  1=An (auch 0xff=An)
//  VT_MANUAUTO,          //  2 Byte - 1 enable 0x01 / 0=Automatisch  1=Manuell //FUJITSU
//  VT_BLOCKEDREL,        //  2 Byte - 1 enable 0x01 / 0=Gesperrt  1=Freigegeben //FUJITSU
  VT_PERCENT,           //  2 Byte - 1 enable 0x06 / percent
  VT_PERCENT5,          //  2 Byte - 1 enable 0x01 / value/2
  VT_PRESSURE,          //  2 Byte - 1 enable 0x01 / bar/10.0     READ-ONLY
  VT_SECONDS_SHORT,     //  2 Byte - 1 enable / seconds
  VT_SECONDS_SHORT4,    //  2 Byte - 1 enable 0x01 / value/4 (signed?)
  VT_SECONDS_SHORT5,    //  2 Byte - 1 enable 0x01 / value/5 (signed?)
  VT_TEMP_SHORT,        //  2 Byte - 1 enable 0x01 / value
  VT_TEMP_SHORT5,       //  2 Byte - 1 enable 0x01 / value/2 (signed)
  VT_TEMP_SHORT5_US,    //  2 Byte - 1 enable 0x01 / value/2 (unsigned)
  VT_TEMP_SHORT64,      //  2 Byte - 1 enable 0x01 / value/64 (signed)
  VT_TEMP_PER_MIN,      //  2 Byte - 1 enable 0x06 / value
  VT_VOLTAGE,           //  2 Byte - 1 enable / volt z.B. 2.9V
  VT_VOLTAGEONOFF,      //  2 Byte - 1 enable / volt 0V (0x00) or 230V (0xFF)
  VT_WEEKDAY,           //  2 Byte - 1 enable 0x01 / weekday (1=Mo..7=So)
  VT_YESNO,             //  2 Byte - 1 enable 0x01 / 0=Nein 1=Ja (auch 0xff=Ja)
  VT_CURRENT,           //  3 Byte - 1 enable / value/100 uA
  VT_CURRENT1000,       //  3 Byte - 1 enable / value/1000 uA
  VT_DAYS_WORD,         //  3 Byte - 1 enable / day
  VT_ERRORCODE,         //  3 Byte - 1 enable / value READ-ONLY
  VT_FP1,               //  3 Byte - 1 enable / value/10 READ-ONLY
  VT_FP02,              //  3 Byte - 1 enable 0x01 / value/50
  VT_GRADIENT,          //  3 Byte - 1 enable / value min/K
  VT_INTEGRAL,          //  3 Byte - 1 enable / value Kmin
  VT_MONTHS_WORD,       //  3 Byte - 1 enable 0x06 / months
  VT_HOUR_MINUTES,      //  3 Byte - 1 enable 0x06 / hh mm
  VT_HOURS_WORD,        //  3 Byte - 1 enable 0x06 / hours
  VT_MINUTES_WORD,      //  3 Byte - 1 enable 0x06 / minutes
  VT_MINUTES_WORD10,    //  3 Byte - 1 enable 0x06 / minutes / 10
  VT_PERCENT_WORD1,     //  3 Byte - 1 enable / percent
  VT_PERCENT_WORD,      //  3 Byte - 1 enable / percent/2
  VT_PERCENT_100,       //  3 Byte - 1 enable / percent/100
  VT_POWER_WORD,        //  3 Byte - 1 enable / value/10 kW
  VT_ENERGY_WORD,       //  3 Byte - 1 enable / value/10 kWh
  VT_ENERGY_CONTENT,    //  3 Byte - 1 enable / value/10 kWh/m³
  VT_PRESSURE_WORD,     //  3 Byte - 1 enable / bar/10.0
  VT_PRESSURE_1000,     //  3 Byte - 1 enable / bar/1000.0
  VT_PROPVAL,           //  3 Byte - 1 enable / value/16
  VT_SECONDS_WORD,      //  3 Byte - 1 enable / seconds
  VT_SECONDS_WORD5,     //  3 Byte - 1 enable / seconds / 2
  VT_SPEED,             //  3 Byte - 1 enable / value * 50 rpm
  VT_SPEED2,            //  3 Byte - 1 enable / rpm
  VT_TEMP,              //  3 Byte - 1 enable / value/64
  VT_TEMP_WORD,         //  3 Byte - 1 enable / value
  VT_TEMP_WORD5_US,     //  3 Byte - 1 enable / value / 2
  VT_CELMIN,            //  3 Byte - 1 enable / value
  VT_LITERPERHOUR,      //  3 Byte - 1 enable / value
  VT_LITERPERMIN,       //  3 Byte - 1 enable / value / 10
  VT_UINT,              //  3 Byte - 1 enable 0x06 / value
  VT_UINT5,             //  3 Byte - 1 enable / value * 5
  VT_UINT10,            //  3 Byte - 1 enable / value / 10
  VT_SINT,              //  3 Byte - 1 enable 0x06 / value
  VT_SINT1000,          //  3 Byte - 1 enable value / 1000
  VT_PPS_TIME,          //  4 Byte
  VT_DWORD,             //  5 Byte - 1 enable 0x06 / value
  VT_HOURS,             //  5 Byte - 1 enable / seconds/3600
  VT_MINUTES,           //  5 Byte - 1 enable 0x01 / seconds/60
  VT_POWER,             //  5 Byte - 1 enable / value/10 kW
  VT_POWER100,          //  5 Byte - 1 enable / value/100 kW
  VT_ENERGY10,          //  5 Byte - 1 enable / value/10 kWh
  VT_ENERGY,            //  5 Byte - 1 enable / value/1 kWh
  VT_UINT100,           //  5 Byte - 1 enable / value / 100
  VT_DATETIME,          //* 9 Byte - 1 enable 0x01 / year+1900 month day weekday hour min sec
  VT_SUMMERPERIOD,      //* 9 Byte - no flag? 1 enable / byte 2/3 month/year
  VT_VACATIONPROG,      //* 9 Byte - 1 enable 0x06 / byte 2/3 month/year
  VT_TIMEPROG,          //*12 Byte - no flag / 1_ein 1_aus 2_ein 2_aus 3_ein 3_aus (jeweils SS:MM)
  VT_STRING,            //* x Byte - 1 enable / string
  VT_CUSTOM_ENUM,       //* x Byte - 1 Byte Position, 1 Byte Parameter-Wert, Space, Text
  VT_CUSTOM_BYTE,       //* x Byte - 1 Byte Position, 1 Byte Länge Parameter, Space (!) (nötig für Erkennung)
  VT_UNKNOWN
}vt_type_t;

const char U_MONTHS[] PROGMEM = UNIT_MONTHS_TEXT;
const char U_DAYS[] PROGMEM = UNIT_DAYS_TEXT;
const char U_HOUR[] PROGMEM = UNIT_HOUR_TEXT;
const char U_MIN[] PROGMEM = UNIT_MIN_TEXT;
const char U_SEC[] PROGMEM = UNIT_SEC_TEXT;
const char U_DEG[] PROGMEM = UNIT_DEG_TEXT;
const char U_PERC[] PROGMEM = UNIT_PERC_TEXT;
const char U_RPM[] PROGMEM = UNIT_RPM_TEXT;
const char U_KW[] PROGMEM = UNIT_KW_TEXT;
const char U_KWH[] PROGMEM = UNIT_KWH_TEXT;
const char U_KWHM3[] PROGMEM = UNIT_KWHM3_TEXT;
const char U_CURR[] PROGMEM = UNIT_CURR_TEXT;
const char U_BAR[] PROGMEM = UNIT_BAR_TEXT;
const char U_VOLT[] PROGMEM = UNIT_VOLT_TEXT;
const char U_GRADIENT[] PROGMEM = UNIT_GRADIENT_TEXT;
const char U_GRADIENTKS[] PROGMEM = UNIT_GRADIENTKS_TEXT;
const char U_TEMP_PER_MIN[] PROGMEM = UNIT_TEMP_PER_MIN_TEXT;
const char U_INTEGRAL[] PROGMEM = UNIT_INTEGRAL_TEXT;
const char U_CEL_MIN[] PROGMEM = UNIT_CEL_MIN_TEXT;
const char U_LITERPERHOUR[] PROGMEM = UNIT_LITERPERHOUR_TEXT;
const char U_LITERPERMIN[] PROGMEM = UNIT_LITERPERMIN_TEXT;
const char U_NONE[] PROGMEM = "";

typedef struct {
  uint32_t    cmd;                 // the command or fieldID
  uint8_t     category;            // the menu category
  uint8_t     type;                // the message type
  uint16_t    line;                // parameter number
  const char *desc;                // description test
  uint16_t    enumstr_len;         // sizeof enum
  const char *enumstr;             // enum string
  uint8_t     flags;               // e.g. FL_RONLY
  uint8_t     dev_fam;             // device family
  uint8_t     dev_var;             // device variant
//  uint32_t    devices;           // e.g. DEV_ALL, DEV_097_ALL, DEV_162_ALL+DEV_163_ALL, DEV_ALL-DEV_097_ALL
} cmd_t;

typedef struct {
  uint8_t   type;             // message type (e.g. VT_TEMP)
  float     operand;          // both for divisors as well as factors (1/divisor)
  uint8_t   data_type;        // Value, String, Date...
  uint8_t   precision;        // decimal places
  const char   *unit;
  uint8_t unit_len;
} units;

typedef enum {
  DT_VALS,    // plain value
  DT_ENUM,    // value (8/16 Bit) followed by space followed by text
  DT_BITS,    // bit value followed by bitmask followed by text
  DT_WDAY,    // weekday
  DT_HHMM,    // hour:minute
  DT_DTTM,    // date and time
  DT_DDMM,    // day and month
  DT_STRN,    // string
  DT_DWHM     // PPS time (day of week, hour:minute)
} dt_types_t;

PROGMEM_LATE const units optbl[]={
{VT_BIT,            1.0,    DT_BITS, 0,  U_NONE, sizeof(U_NONE)},
{VT_BYTE,           1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_CLOSEDOPEN,     1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_DAYS,           1.0,    DT_VALS, 0,  U_DAYS, sizeof(U_DAYS)},
{VT_ENUM,           1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_GRADIENT_SHORT, 1.0,    DT_VALS, 0,  U_GRADIENT, sizeof(U_GRADIENT)},
{VT_HOURS_SHORT,    1.0,    DT_VALS, 0,  U_HOUR, sizeof(U_HOUR)},
{VT_LPBADDR,        1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_MINUTES_SHORT,  1.0,    DT_VALS, 0,  U_MIN, sizeof(U_MIN)},
{VT_MONTHS,         1.0,    DT_VALS, 0,  U_MONTHS, sizeof(U_MONTHS)},
{VT_ONOFF,          1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_PERCENT,        1.0,    DT_VALS, 0,  U_PERC, sizeof(U_PERC)},
{VT_PERCENT5,       2.0,    DT_VALS, 0,  U_PERC, sizeof(U_PERC)},
{VT_PRESSURE,       10.0,   DT_VALS, 1,  U_BAR, sizeof(U_BAR)},
{VT_SECONDS_SHORT,  1.0,    DT_VALS, 0,  U_SEC, sizeof(U_SEC)},
{VT_SECONDS_SHORT4, 4.0,    DT_VALS, 1,  U_SEC, sizeof(U_SEC)},
{VT_SECONDS_SHORT5, 5.0,    DT_VALS, 1,  U_SEC, sizeof(U_SEC)},
{VT_TEMP_SHORT,     1.0,    DT_VALS, 0,  U_DEG, sizeof(U_DEG)},
{VT_TEMP_SHORT5,    2.0,    DT_VALS, 1,  U_DEG, sizeof(U_DEG)},
{VT_TEMP_SHORT5_US, 2.0,    DT_VALS, 1,  U_DEG, sizeof(U_DEG)},
{VT_TEMP_SHORT64,   64.0,   DT_VALS, 5,  U_GRADIENTKS, sizeof(U_GRADIENTKS)},
{VT_TEMP_PER_MIN,   1.0,    DT_VALS, 0,  U_TEMP_PER_MIN, sizeof(U_TEMP_PER_MIN)},
{VT_VOLTAGE,        10.0,   DT_VALS, 1,  U_VOLT, sizeof(U_VOLT)},
{VT_VOLTAGEONOFF,   1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_WEEKDAY,        1.0,    DT_WDAY, 0,  U_NONE, sizeof(U_NONE)},
{VT_YESNO,          1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_CURRENT,        100.0,  DT_VALS, 2,  U_CURR, sizeof(U_CURR)},
{VT_CURRENT1000,    1000.0, DT_VALS, 2,  U_CURR, sizeof(U_CURR)},
{VT_DAYS_WORD,      1.0,    DT_VALS, 0,  U_DAYS, sizeof(U_DAYS)},
{VT_ERRORCODE,      1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_FP1,            10.0,   DT_VALS, 1,  U_NONE, sizeof(U_NONE)},
{VT_FP02,           50.0,   DT_VALS, 2,  U_NONE, sizeof(U_NONE)},
{VT_GRADIENT,       1.0,    DT_VALS, 0,  U_GRADIENT, sizeof(U_GRADIENT)},
{VT_INTEGRAL,       1.0,    DT_VALS, 0,  U_INTEGRAL, sizeof(U_INTEGRAL)},
{VT_MONTHS_WORD,    1.0,    DT_VALS, 0,  U_MONTHS, sizeof(U_MONTHS)},
{VT_HOUR_MINUTES,   1.0,    DT_HHMM, 0,  U_NONE, sizeof(U_NONE)},
{VT_HOURS_WORD,     1.0,    DT_VALS, 0,  U_HOUR, sizeof(U_HOUR)},
{VT_MINUTES_WORD,   1.0,    DT_VALS, 0,  U_MIN, sizeof(U_MIN)},
{VT_MINUTES_WORD10, 0.1,    DT_VALS, 0,  U_MIN, sizeof(U_MIN)},
{VT_PERCENT_WORD1,  1.0,    DT_VALS, 1,  U_PERC, sizeof(U_PERC)},
{VT_PERCENT_WORD,   2.0,    DT_VALS, 1,  U_PERC, sizeof(U_PERC)},
{VT_PERCENT_100,    100.0,  DT_VALS, 1,  U_PERC, sizeof(U_PERC)},
{VT_POWER_WORD,     10.0,   DT_VALS, 1,  U_KW, sizeof(U_KW)},
{VT_ENERGY_WORD,    10.0,   DT_VALS, 1,  U_KWH, sizeof(U_KWH)},
{VT_ENERGY_CONTENT, 10.0,   DT_VALS, 1,  U_KWHM3, sizeof(U_KWHM3)},
{VT_PRESSURE_WORD,  10.0,   DT_VALS, 1,  U_BAR, sizeof(U_BAR)},
{VT_PRESSURE_1000,  1000.0, DT_VALS, 1,  U_BAR, sizeof(U_BAR)},
{VT_PROPVAL,        16.0,   DT_VALS, 2,  U_NONE, sizeof(U_NONE)},
{VT_SECONDS_WORD,   1.0,    DT_VALS, 0,  U_SEC, sizeof(U_SEC)},
{VT_SECONDS_WORD5,  2.0,    DT_VALS, 0,  U_SEC, sizeof(U_SEC)},
{VT_SPEED,          0.02,   DT_VALS, 0,  U_RPM, sizeof(U_RPM)},
{VT_SPEED2,         1.0,    DT_VALS, 0,  U_RPM, sizeof(U_RPM)},
{VT_TEMP,           64.0,   DT_VALS, 1,  U_DEG, sizeof(U_DEG)},
{VT_TEMP_WORD,      1.0,    DT_VALS, 1,  U_DEG, sizeof(U_DEG)},
{VT_TEMP_WORD5_US,  2.0,    DT_VALS, 1,  U_DEG, sizeof(U_DEG)},
{VT_CELMIN,         1.0,    DT_VALS, 1,  U_CEL_MIN, sizeof(U_CEL_MIN)},
{VT_LITERPERHOUR,   1.0,    DT_VALS, 0,  U_LITERPERHOUR, sizeof(U_LITERPERHOUR)},
{VT_LITERPERMIN,    10.0,   DT_VALS, 1,  U_LITERPERMIN, sizeof(U_LITERPERMIN)},
{VT_UINT,           1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_UINT5,          5.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_UINT10,         10.0,   DT_VALS, 1,  U_NONE, sizeof(U_NONE)},
{VT_SINT,           1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_SINT1000,       1000,   DT_VALS, 3,  U_NONE, sizeof(U_NONE)},
{VT_PPS_TIME,       1.0,    DT_DWHM, 0,  U_NONE, sizeof(U_NONE)},
{VT_DWORD,          1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_HOURS,          3600.0, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR)},
{VT_MINUTES,        60.0,   DT_VALS, 0,  U_MIN, sizeof(U_MIN)},
{VT_POWER,          10.0,   DT_VALS, 1,  U_KW, sizeof(U_KW)},
{VT_POWER100,       100.0,  DT_VALS, 2,  U_KW, sizeof(U_KW)},
{VT_ENERGY10,       10.0,   DT_VALS, 1,  U_KWH, sizeof(U_KWH)},
{VT_ENERGY,         1.0,    DT_VALS, 0,  U_KWH, sizeof(U_KWH)},
{VT_UINT100,        100.0,  DT_VALS, 2,  U_NONE, sizeof(U_NONE)},
{VT_DATETIME,       1.0,    DT_DTTM, 0,  U_NONE, sizeof(U_NONE)},
{VT_SUMMERPERIOD,   1.0,    DT_DDMM, 0,  U_NONE, sizeof(U_NONE)},
{VT_VACATIONPROG,   1.0,    DT_DDMM, 0,  U_NONE, sizeof(U_NONE)},
{VT_TIMEPROG,       1.0,    DT_DTTM, 0,  U_NONE, sizeof(U_NONE)},
{VT_STRING,         1.0,    DT_STRN, 0,  U_NONE, sizeof(U_NONE)},
{VT_CUSTOM_ENUM,    1.0,    DT_ENUM, 0,  U_NONE, sizeof(U_NONE)},
{VT_CUSTOM_BYTE,    1.0,    DT_VALS, 0,  U_NONE, sizeof(U_NONE)},
{VT_STRING,         1.0,    DT_STRN, 0,  U_NONE, sizeof(U_NONE)},
{VT_UNKNOWN,        1.0,    DT_VALS, 1,  U_NONE, sizeof(U_NONE)},
};

/****************************************************/
/* PROGMEM TABLES and STRINGS                       */
/****************************************************/
// Menue Kategorien
const char ENUM_CAT[] PROGMEM_LATEST = {
"\x00 " ENUM_CAT_00_TEXT "\0"
"\x01 " ENUM_CAT_01_TEXT "\0"
"\x02 " ENUM_CAT_02_TEXT "\0"
"\x03 " ENUM_CAT_03_TEXT "\0"
"\x04 " ENUM_CAT_04_TEXT "\0"
"\x05 " ENUM_CAT_05_TEXT "\0"
"\x06 " ENUM_CAT_06_TEXT "\0"
"\x07 " ENUM_CAT_07_TEXT "\0"
"\x08 " ENUM_CAT_08_TEXT "\0"
"\x09 " ENUM_CAT_09_TEXT "\0"
"\x0a " ENUM_CAT_0a_TEXT "\0"
"\x0b " ENUM_CAT_0b_TEXT "\0"
"\x0c " ENUM_CAT_0c_TEXT "\0"
"\x0d " ENUM_CAT_0d_TEXT "\0"
"\x0e " ENUM_CAT_0e_TEXT "\0"
"\x0f " ENUM_CAT_0f_TEXT "\0"
"\x10 " ENUM_CAT_10_TEXT "\0"
"\x11 " ENUM_CAT_11_TEXT "\0"
"\x12 " ENUM_CAT_12_TEXT "\0"
"\x13 " ENUM_CAT_13_TEXT "\0"
"\x14 " ENUM_CAT_14_TEXT "\0"
"\x15 " ENUM_CAT_15_TEXT "\0"
"\x16 " ENUM_CAT_16_TEXT "\0"
"\x17 " ENUM_CAT_17_TEXT "\0"
"\x18 " ENUM_CAT_18_TEXT "\0"
"\x19 " ENUM_CAT_19_TEXT "\0"
"\x1a " ENUM_CAT_1a_TEXT "\0"
"\x1b " ENUM_CAT_1b_TEXT "\0"
"\x1c " ENUM_CAT_1c_TEXT "\0"
"\x1d " ENUM_CAT_1d_TEXT "\0"
"\x1e " ENUM_CAT_1e_TEXT "\0"
"\x1f " ENUM_CAT_1f_TEXT "\0"
"\x20 " ENUM_CAT_20_TEXT "\0"
"\x21 " ENUM_CAT_21_TEXT "\0"
"\x22 " ENUM_CAT_22_TEXT "\0"
"\x23 " ENUM_CAT_23_TEXT "\0"
"\x24 " ENUM_CAT_24_TEXT "\0"
"\x25 " ENUM_CAT_25_TEXT "\0"
"\x26 " ENUM_CAT_26_TEXT "\0"
"\x27 " ENUM_CAT_27_TEXT "\0"
"\x28 " ENUM_CAT_28_TEXT "\0"
"\x29 " ENUM_CAT_29_TEXT "\0"
"\x2a " ENUM_CAT_2a_TEXT "\0"
"\x2b " ENUM_CAT_2b_TEXT
};

const uint16_t ENUM_CAT_NR[] PROGMEM_LATEST = {
  0, 6,
  20, 70,
  120, 140,
  500, 516,
  520, 536,
  540, 556,
  560, 576,
  600, 616,
  632, 648,
  649, 665,
  666, 682,
  700, 900,
  901, 969,
  1000, 1200,
  1300, 1500,
  1600, 1680,
  2008, 2051,
  2055, 2080,
  2110, 2150,
  2200, 2551,
  2700, 2732,
  2785, 3010,
  3095, 3267,
  3510, 3590,
  3700, 3723,
  3810, 3887,
  4102, 4141,
  4708, 4813,
  5010, 5131,
  5400, 5544,
  5700, 6421,
  6600, 6650,
  6705, 6996,
  7001, 7254,
  7300, 7500,
  7700, 7999,
  8000, 8099,
  8100, 8150,
  8300, 8570,
  8700, 9075,
  9500, 9627,
  10000, 14999,
  15000, 15067
};

 /* Menue Strings */
const char STR0[] PROGMEM = STR0_TEXT;
const char STR1[] PROGMEM = STR1_TEXT;
const char STR2[] PROGMEM = STR2_TEXT;
const char STR3[] PROGMEM = STR3_TEXT;
const char STR5[] PROGMEM = STR5_TEXT;
const char STR6[] PROGMEM = STR6_TEXT;
const char STR20[] PROGMEM = STR20_TEXT;
const char STR21[] PROGMEM = STR21_TEXT;
const char STR22[] PROGMEM = STR22_TEXT;
const char STR23[] PROGMEM = STR23_TEXT;
const char STR25[] PROGMEM = STR25_TEXT;
const char STR26[] PROGMEM = STR26_TEXT;
const char STR27[] PROGMEM = STR27_TEXT;
const char STR28[] PROGMEM = STR28_TEXT;
const char STR29[] PROGMEM = STR29_TEXT;
const char STR30[] PROGMEM = STR30_TEXT;
const char STR31[] PROGMEM = STR31_TEXT;
const char STR40[] PROGMEM = STR40_TEXT;
const char STR42[] PROGMEM = STR42_TEXT;
const char STR42_2[] PROGMEM = STR42_2_TEXT;
const char STR44[] PROGMEM = STR44_TEXT;
const char STR46[] PROGMEM = STR46_TEXT;
const char STR48[] PROGMEM = STR48_TEXT;
const char STR54[] PROGMEM = STR54_TEXT;
const char STR70[] PROGMEM = STR70_TEXT;
const char STR71[] PROGMEM = STR71_TEXT;
const char STR120[] PROGMEM = STR120_TEXT;
const char STR121[] PROGMEM = STR121_TEXT;
const char STR130[] PROGMEM = STR130_TEXT;
const char STR131[] PROGMEM = STR131_TEXT;
const char STR132[] PROGMEM = STR132_TEXT;
const char STR133[] PROGMEM = STR133_TEXT;
const char STR134[] PROGMEM = STR134_TEXT;
const char STR135[] PROGMEM = STR135_TEXT;
const char STR136[] PROGMEM = STR136_TEXT;
const char STR137[] PROGMEM = STR137_TEXT;
const char STR138[] PROGMEM = STR138_TEXT;
const char STR140[] PROGMEM = STR140_TEXT;
const char STR500[] PROGMEM = STR500_TEXT;
const char STR501[] PROGMEM = STR501_TEXT;
const char STR502[] PROGMEM = STR502_TEXT;
const char STR503[] PROGMEM = STR503_TEXT;
const char STR504[] PROGMEM = STR504_TEXT;
const char STR505[] PROGMEM = STR505_TEXT;
const char STR506[] PROGMEM = STR506_TEXT;

const char STR516[] PROGMEM = STR516_TEXT;

#define STR520 STR500
#define STR521 STR501
#define STR522 STR502
#define STR523 STR503
#define STR524 STR504
#define STR525 STR505
#define STR526 STR506
#define STR536 STR516

#define STR540 STR500
#define STR541 STR501
#define STR542 STR502
#define STR543 STR503
#define STR544 STR504
#define STR545 STR505
#define STR546 STR506
#define STR556 STR516

#define STR560 STR500
#define STR561 STR501
#define STR562 STR502
#define STR563 STR503
#define STR564 STR504
#define STR565 STR505
#define STR566 STR506
#define STR576 STR516

#define STR600 STR500
#define STR601 STR501
#define STR602 STR502
#define STR603 STR503
#define STR604 STR504
#define STR605 STR505
#define STR606 STR506
#define STR616 STR516

/* Die Zeilennummern 632-682 entsprechen nicht den Zeilennummern im Bedienteil,
 * sondern wurden künstlich hinzugefügt */
const char STR632[] PROGMEM = STR632_TEXT;
const char STR633[] PROGMEM = STR633_TEXT;
const char STR634[] PROGMEM = STR634_TEXT;
const char STR635[] PROGMEM = STR635_TEXT;
const char STR636[] PROGMEM = STR636_TEXT;
const char STR637[] PROGMEM = STR637_TEXT;
const char STR638[] PROGMEM = STR638_TEXT;
const char STR639[] PROGMEM = STR639_TEXT;
const char STR640[] PROGMEM = STR640_TEXT;
const char STR641[] PROGMEM = STR641_TEXT;
const char STR642[] PROGMEM = STR642_TEXT;
const char STR643[] PROGMEM = STR643_TEXT;
const char STR644[] PROGMEM = STR644_TEXT;
const char STR645[] PROGMEM = STR645_TEXT;
const char STR646[] PROGMEM = STR646_TEXT;
const char STR647[] PROGMEM = STR647_TEXT;
const char STR648[] PROGMEM = STR648_TEXT;

#define STR649 STR632
#define STR650 STR633
#define STR651 STR634
#define STR652 STR635
#define STR653 STR636
#define STR654 STR637
#define STR655 STR638
#define STR656 STR639
#define STR657 STR640
#define STR658 STR641
#define STR659 STR642
#define STR660 STR643
#define STR661 STR644
#define STR662 STR645
#define STR663 STR646
#define STR664 STR647
#define STR665 STR648

#define STR666 STR632
#define STR667 STR633
#define STR668 STR634
#define STR669 STR635
#define STR670 STR636
#define STR671 STR637
#define STR672 STR638
#define STR673 STR639
#define STR674 STR640
#define STR675 STR641
#define STR676 STR642
#define STR677 STR643
#define STR678 STR644
#define STR679 STR645
#define STR680 STR646
#define STR681 STR647
#define STR682 STR648

/*
#define STR641 STR500
#define STR642 STR642
#define STR643 STR643
#define STR648 STR648
#define STR651 STR500
#define STR652 STR642
#define STR653 STR643
#define STR658 STR648
#define STR661 STR500
#define STR662 STR642
#define STR663 STR643
#define STR668 STR648
*/

// Heizkreis 1
const char STR700[] PROGMEM = STR700_TEXT;
const char STR701[] PROGMEM = STR701_TEXT;
#define STR702 STR701
#define STR703 STR702
const char STR709[] PROGMEM = STR709_TEXT;
const char STR710[] PROGMEM = STR710_TEXT;
const char STR711[] PROGMEM = STR711_TEXT;
const char STR712[] PROGMEM = STR712_TEXT;
const char STR714[] PROGMEM = STR714_TEXT;
const char STR720[] PROGMEM = STR720_TEXT;
const char STR721[] PROGMEM = STR721_TEXT;
const char STR726[] PROGMEM = STR726_TEXT;
const char STR730[] PROGMEM = STR730_TEXT;
const char STR732[] PROGMEM = STR732_TEXT;
const char STR733[] PROGMEM = STR733_TEXT;
const char STR734[] PROGMEM = STR734_TEXT;
const char STR740[] PROGMEM = STR740_TEXT;
const char STR741[] PROGMEM = STR741_TEXT;
const char STR742[] PROGMEM = STR742_TEXT;
const char STR744[] PROGMEM = STR744_TEXT;
const char STR750[] PROGMEM = STR750_TEXT;
const char STR760[] PROGMEM = STR760_TEXT;
const char STR761[] PROGMEM = STR761_TEXT;
const char STR770[] PROGMEM = STR770_TEXT;
const char STR780[] PROGMEM = STR780_TEXT;
const char STR781[] PROGMEM = STR781_TEXT;
const char STR790[] PROGMEM = STR790_TEXT;
const char STR791[] PROGMEM = STR791_TEXT;
const char STR794[] PROGMEM = STR794_TEXT;
const char STR800[] PROGMEM = STR800_TEXT;
const char STR801[] PROGMEM = STR801_TEXT;
const char STR809[] PROGMEM = STR809_TEXT;
const char STR810[] PROGMEM = STR810_TEXT;
const char STR820[] PROGMEM = STR820_TEXT;
const char STR830[] PROGMEM = STR830_TEXT;
const char STR831[] PROGMEM = STR831_TEXT;
const char STR832[] PROGMEM = STR832_TEXT;
const char STR833[] PROGMEM = STR833_TEXT;
const char STR834[] PROGMEM = STR834_TEXT;
const char STR835[] PROGMEM = STR835_TEXT;
const char STR836[] PROGMEM = STR836_TEXT;
const char STR850[] PROGMEM = STR850_TEXT;
const char STR851[] PROGMEM = STR851_TEXT;
const char STR855[] PROGMEM = STR855_TEXT;
const char STR856[] PROGMEM = STR856_TEXT;
const char STR857[] PROGMEM = STR857_TEXT;
const char STR861[] PROGMEM = STR861_TEXT;
const char STR864[] PROGMEM = STR864_TEXT;
const char STR870[] PROGMEM = STR870_TEXT;
const char STR872[] PROGMEM = STR872_TEXT;
const char STR880[] PROGMEM = STR880_TEXT;
const char STR882[] PROGMEM = STR882_TEXT;
const char STR883[] PROGMEM = STR883_TEXT;
const char STR884[] PROGMEM = STR884_TEXT;
const char STR885[] PROGMEM = STR885_TEXT;
const char STR886[] PROGMEM = STR886_TEXT;
const char STR887[] PROGMEM = STR887_TEXT;
const char STR888[] PROGMEM = STR888_TEXT;
const char STR888_2[] PROGMEM = STR888_2_TEXT;
const char STR890[] PROGMEM = STR890_TEXT;
const char STR894[] PROGMEM = STR894_TEXT;
const char STR895[] PROGMEM = STR895_TEXT;
const char STR898[] PROGMEM = STR898_TEXT;

// Einstellungen Kühlkreis 1
#define STR900 STR700
#define STR901 STR701
#define STR902 STR710
#define STR903 STR712
const char STR904[] PROGMEM = STR904_TEXT;
#define STR905 STR709
const char STR907[] PROGMEM = STR907_TEXT;
const char STR908[] PROGMEM = STR908_TEXT;
const char STR909[] PROGMEM = STR909_TEXT;
const char STR912[] PROGMEM = STR912_TEXT;
const char STR913[] PROGMEM = STR913_TEXT;
const char STR914[] PROGMEM = STR914_TEXT;
const char STR918[] PROGMEM = STR918_TEXT;
const char STR919[] PROGMEM = STR919_TEXT;
const char STR920[] PROGMEM = STR920_TEXT;
const char STR923[] PROGMEM = STR923_TEXT;
const char STR924[] PROGMEM = STR924_TEXT;
#define STR928 STR750
#define STR932 STR760
const char STR933[] PROGMEM = STR933_TEXT;
const char STR937[] PROGMEM = STR937_TEXT;
#define STR938 STR831
#define STR939 STR832
#define STR940 STR833
#define STR941 STR834
#define STR942 STR835
#define STR943 STR836
const char STR945[] PROGMEM = STR945_TEXT;
const char STR946[] PROGMEM = STR946_TEXT;
const char STR947[] PROGMEM = STR947_TEXT;
const char STR948[] PROGMEM = STR948_TEXT;
const char STR950[] PROGMEM = STR950_TEXT;
#define STR962 STR870
const char STR963[] PROGMEM = STR963_TEXT;
#define STR969 STR900

// Einstellungen Heizkreis 2
#define STR1000 STR700
#define STR1001 STR710
#define STR1010 STR710
#define STR1011 STR711
#define STR1012 STR712
#define STR1014 STR714
#define STR1020 STR720
#define STR1021 STR721
#define STR1026 STR726
const char STR1030[] PROGMEM = STR1030_TEXT;
#define STR1032 STR732
#define STR1040 STR740
#define STR1041 STR741
const char STR1042[] PROGMEM = STR1042_TEXT;
#define STR1050 STR750
#define STR1060 STR760
#define STR1070 STR770
#define STR1080 STR780
#define STR1081 STR781
#define STR1090 STR790
#define STR1091 STR791
#define STR1100 STR800
#define STR1101 STR801
const char STR1109[] PROGMEM = STR1109_TEXT;
#define STR1110 STR810
#define STR1120 STR820
#define STR1130 STR830
#define STR1131 STR831
#define STR1132 STR832
#define STR1133 STR833
#define STR1134 STR834
#define STR1135 STR835
#define STR1136 STR836
const char STR1150[] PROGMEM = STR1150_TEXT;
const char STR1151[] PROGMEM = STR1151_TEXT;
const char STR1155[] PROGMEM = STR1155_TEXT;
const char STR1156[] PROGMEM = STR1156_TEXT;
const char STR1157[] PROGMEM = STR1157_TEXT;
#define STR1161 STR861
#define STR1164 STR864
#define STR1170 STR870
#define STR1172 STR872
const char STR1180[] PROGMEM = STR1180_TEXT;
#define STR1182 STR882
#define STR1183 STR883
#define STR1200 STR900

// Heizkreis 3/P
#define STR1300 STR700
#define STR1301 STR701
#define STR1310 STR710
#define STR1311 STR711
#define STR1312 STR712
#define STR1314 STR714
#define STR1320 STR720
#define STR1321 STR721
#define STR1326 STR726
#define STR1330 STR730
#define STR1332 STR732
#define STR1340 STR740
#define STR1341 STR741
#define STR1350 STR750
#define STR1360 STR760
#define STR1370 STR770
#define STR1380 STR780
#define STR1381 STR781
#define STR1390 STR790
#define STR1391 STR791
#define STR1400 STR1100
#define STR1401 STR801
#define STR1410 STR810
#define STR1420 STR820
#define STR1430 STR830
#define STR1431 STR831
#define STR1432 STR832
#define STR1433 STR833
#define STR1434 STR834
#define STR1435 STR835
#define STR1436 STR836
#define STR1450 STR1150
#define STR1451 STR1151
#define STR1455 STR1155
#define STR1456 STR1156
#define STR1457 STR1157
#define STR1461 STR861
#define STR1464 STR864
#define STR1470 STR870
#define STR1472 STR872
#define STR1482 STR882
#define STR1483 STR883
#define STR1500 STR900

// Trinkwasser
const char STR1600[] PROGMEM = STR1600_TEXT;
const char STR1601[] PROGMEM = STR1601_TEXT;
const char STR1602[] PROGMEM = STR1602_TEXT;
const char STR1610[] PROGMEM = STR1610_TEXT;
const char STR1612[] PROGMEM = STR1612_TEXT;
const char STR1614[] PROGMEM = STR1614_TEXT;
const char STR1620[] PROGMEM = STR1620_TEXT;
const char STR1630[] PROGMEM = STR1630_TEXT;
const char STR1640[] PROGMEM = STR1640_TEXT;
const char STR1641[] PROGMEM = STR1641_TEXT;
const char STR1642[] PROGMEM = STR1642_TEXT;
const char STR1644[] PROGMEM = STR1644_TEXT;
const char STR1645[] PROGMEM = STR1645_TEXT;
const char STR1646[] PROGMEM = STR1646_TEXT;
const char STR1647[] PROGMEM = STR1647_TEXT;
const char STR1660[] PROGMEM = STR1660_TEXT;
const char STR1661[] PROGMEM = STR1661_TEXT;
const char STR1663[] PROGMEM = STR1663_TEXT;
const char STR1680[] PROGMEM = STR1680_TEXT;

// Hx Pumpe
const char STR2008[] PROGMEM = STR2008_TEXT;
const char STR2010[] PROGMEM = STR2010_TEXT;
const char STR2012[] PROGMEM = STR2012_TEXT;
const char STR2014[] PROGMEM = STR2014_TEXT;
const char STR2015[] PROGMEM = STR2015_TEXT;
const char STR2033[] PROGMEM = STR2033_TEXT;
const char STR2035[] PROGMEM = STR2035_TEXT;
const char STR2037[] PROGMEM = STR2037_TEXT;
const char STR2039[] PROGMEM = STR2039_TEXT;
const char STR2040[] PROGMEM = STR2040_TEXT;
const char STR2044[] PROGMEM = STR2044_TEXT;
const char STR2046[] PROGMEM = STR2046_TEXT;
const char STR2048[] PROGMEM = STR2048_TEXT;
const char STR2050[] PROGMEM = STR2050_TEXT;
const char STR2051[] PROGMEM = STR2051_TEXT;

// Schwimmbad
const char STR2055[] PROGMEM = STR2055_TEXT;
const char STR2056[] PROGMEM = STR2056_TEXT;
const char STR2065[] PROGMEM = STR2065_TEXT;
const char STR2070[] PROGMEM = STR2070_TEXT;
const char STR2080[] PROGMEM = STR2080_TEXT;

// Vorregler/Zubringerpumpe
#define STR2110 STR740
#define STR2111 STR741
const char STR2112[] PROGMEM = STR2112_TEXT;
#define STR2130 STR830
#define STR2131 STR831
#define STR2132 STR832
#define STR2133 STR833
#define STR2134 STR834
#define STR2135 STR835
#define STR2136 STR836
const char STR2150[] PROGMEM = STR2150_TEXT;

// Kessel
#define STR2200 STR700
const char STR2201[] PROGMEM = STR2201_TEXT;
const char STR2203[] PROGMEM = STR2203_TEXT;
const char STR2204[] PROGMEM = STR2204_TEXT;
const char STR2205[] PROGMEM = STR2205_TEXT;
const char STR2206[] PROGMEM = STR2206_TEXT;
const char STR2208[] PROGMEM = STR2208_TEXT;
const char STR2210[] PROGMEM = STR2210_TEXT;
const char STR2211[] PROGMEM = STR2211_TEXT;
const char STR2212[] PROGMEM = STR2212_TEXT;
const char STR2213[] PROGMEM = STR2213_TEXT;
const char STR2214[] PROGMEM = STR2214_TEXT;
const char STR2215[] PROGMEM = STR2215_TEXT;
const char STR2220[] PROGMEM = STR2220_TEXT;
const char STR2221[] PROGMEM = STR2221_TEXT;
const char STR2222[] PROGMEM = STR2222_TEXT;
const char STR2232[] PROGMEM = STR2232_TEXT;
const char STR2233[] PROGMEM = STR2233_TEXT;
const char STR2234[] PROGMEM = STR2234_TEXT;
const char STR2235[] PROGMEM = STR2235_TEXT;
const char STR2236[] PROGMEM = STR2236_TEXT;
const char STR2237[] PROGMEM = STR2237_TEXT;
const char STR2238[] PROGMEM = STR2238_TEXT;
const char STR2240[] PROGMEM = STR2240_TEXT;
const char STR2241[] PROGMEM = STR2241_TEXT;
const char STR2243[] PROGMEM = STR2243_TEXT;
const char STR2245[] PROGMEM = STR2245_TEXT;
const char STR2250[] PROGMEM = STR2250_TEXT;
const char STR2253[] PROGMEM = STR2253_TEXT;
const char STR2260[] PROGMEM = STR2260_TEXT;
const char STR2261[] PROGMEM = STR2261_TEXT;
const char STR2262[] PROGMEM = STR2262_TEXT;
const char STR2270[] PROGMEM = STR2270_TEXT;
const char STR2271[] PROGMEM = STR2271_TEXT;
const char STR2272[] PROGMEM = STR2272_TEXT;
#define STR2282 STR834
#define STR2283 STR835
#define STR2284 STR836
const char STR2285[] PROGMEM = STR2285_TEXT;
const char STR2290[] PROGMEM = STR2290_TEXT;
const char STR2291[] PROGMEM = STR2291_TEXT;
const char STR2300[] PROGMEM = STR2300_TEXT;
const char STR2301[] PROGMEM = STR2301_TEXT;
const char STR2305[] PROGMEM = STR2305_TEXT;
const char STR2310[] PROGMEM = STR2310_TEXT;
const char STR2315[] PROGMEM = STR2315_TEXT;
const char STR2316[] PROGMEM = STR2316_TEXT;
const char STR2317[] PROGMEM = STR2317_TEXT;
const char STR2320[] PROGMEM = STR2320_TEXT;
const char STR2321[] PROGMEM = STR2321_TEXT;
#define STR2322 STR882
#define STR2323 STR883
const char STR2324[] PROGMEM = STR2324_TEXT;
const char STR2325[] PROGMEM = STR2325_TEXT;
const char STR2326[] PROGMEM = STR2326_TEXT;
const char STR2330[] PROGMEM = STR2330_TEXT;
const char STR2331[] PROGMEM = STR2331_TEXT;
const char STR2334[] PROGMEM = STR2334_TEXT;
const char STR2335[] PROGMEM = STR2335_TEXT;
const char STR2340[] PROGMEM = STR2340_TEXT;
const char STR2440[] PROGMEM = STR2440_TEXT;
const char STR2441[] PROGMEM = STR2441_TEXT;
const char STR2441_2[] PROGMEM = STR2441_2_TEXT;
const char STR2442[] PROGMEM = STR2442_TEXT;
const char STR2442_2[] PROGMEM = STR2442_2_TEXT;
const char STR2443[] PROGMEM = STR2443_TEXT;
const char STR2443_2[] PROGMEM = STR2443_2_TEXT;
const char STR2444[] PROGMEM = STR2444_TEXT;
const char STR2444_2[] PROGMEM = STR2444_2_TEXT;
const char STR2444_3[] PROGMEM = STR2444_3_TEXT;
const char STR2445[] PROGMEM = STR2445_TEXT;
const char STR2445_2[] PROGMEM = STR2445_2_TEXT;
const char STR2446[] PROGMEM = STR2446_TEXT;
const char STR2450[] PROGMEM = STR2450_TEXT;
const char STR2451[] PROGMEM = STR2451_TEXT;
#define STR2452 STR2245
const char STR2452_2[] PROGMEM = STR2452_2_TEXT;
const char STR2452_3[] PROGMEM = STR2452_3_TEXT;
const char STR2453[] PROGMEM = STR2453_TEXT;
const char STR2454[] PROGMEM = STR2454_TEXT;
const char STR2455[] PROGMEM = STR2455_TEXT;
const char STR2456[] PROGMEM = STR2456_TEXT;
const char STR2457[] PROGMEM = STR2457_TEXT;
const char STR2459[] PROGMEM = STR2459_TEXT;
const char STR2460[] PROGMEM = STR2460_TEXT;
const char STR2461[] PROGMEM = STR2461_TEXT;
const char STR2462[] PROGMEM = STR2462_TEXT;
const char STR2463[] PROGMEM = STR2463_TEXT;
const char STR2464[] PROGMEM = STR2464_TEXT;
const char STR2465[] PROGMEM = STR2465_TEXT;
const char STR2466[] PROGMEM = STR2466_TEXT;
const char STR2467[] PROGMEM = STR2467_TEXT;
const char STR2470[] PROGMEM = STR2470_TEXT;
const char STR2471[] PROGMEM = STR2471_TEXT;
const char STR2472[] PROGMEM = STR2472_TEXT;
const char STR2473[] PROGMEM = STR2473_TEXT;
const char STR2474[] PROGMEM = STR2474_TEXT;
const char STR2476[] PROGMEM = STR2476_TEXT;
const char STR2477[] PROGMEM = STR2477_TEXT;
const char STR2478[] PROGMEM = STR2478_TEXT;
#define STR2479 STR2478
const char STR2480[] PROGMEM = STR2480_TEXT;
const char STR2490[] PROGMEM = STR2490_TEXT;
const char STR2491[] PROGMEM = STR2491_TEXT;
const char STR2492[] PROGMEM = STR2492_TEXT;
const char STR2494[] PROGMEM = STR2494_TEXT;
const char STR2495[] PROGMEM = STR2495_TEXT;
const char STR2496[] PROGMEM = STR2496_TEXT;
const char STR2500[] PROGMEM = STR2500_TEXT;
const char STR2502[] PROGMEM = STR2502_TEXT;
const char STR2504[] PROGMEM = STR2504_TEXT;
const char STR2510[] PROGMEM = STR2510_TEXT;
const char STR2511[] PROGMEM = STR2511_TEXT;
const char STR2512[] PROGMEM = STR2512_TEXT;
const char STR2521[] PROGMEM = STR2521_TEXT;
const char STR2522[] PROGMEM = STR2522_TEXT;
const char STR2527[] PROGMEM = STR2527_TEXT;
const char STR2528[] PROGMEM = STR2528_TEXT;
const char STR2531[] PROGMEM = STR2531_TEXT;
const char STR2540[] PROGMEM = STR2540_TEXT;
const char STR2543[] PROGMEM = STR2543_TEXT;
const char STR2550[] PROGMEM = STR2550_TEXT;
const char STR2551[] PROGMEM = STR2551_TEXT;
const char STR2560[] PROGMEM = STR2560_TEXT;
const char STR2630[] PROGMEM = STR2630_TEXT;
const char STR2655[] PROGMEM = STR2655_TEXT;
const char STR2656[] PROGMEM = STR2656_TEXT;
const char STR2657[] PROGMEM = STR2657_TEXT;
const char STR2662[] PROGMEM = STR2662_TEXT;
const char STR2663[] PROGMEM = STR2663_TEXT;
#define STR2670 STR2478

//Sitherm Pro
const char STR2700[] PROGMEM = STR2700_TEXT;
const char STR2700_2[] PROGMEM = STR2700_2_TEXT;
const char STR2702[] PROGMEM = STR2702_TEXT;
const char STR2702_2[] PROGMEM = STR2702_2_TEXT;
const char STR2703[] PROGMEM = STR2703_TEXT;
const char STR2703_2[] PROGMEM = STR2703_2_TEXT;
const char STR2704[] PROGMEM = STR2704_TEXT;
const char STR2705[] PROGMEM = STR2705_TEXT;
const char STR2705_2[] PROGMEM = STR2705_2_TEXT;
const char STR2706[] PROGMEM = STR2706_TEXT;
const char STR2720[] PROGMEM = STR2720_TEXT;
const char STR2721[] PROGMEM = STR2721_TEXT;
const char STR2727[] PROGMEM = STR2727_TEXT;
const char STR2730[] PROGMEM = STR2730_TEXT;
#define STR2731 STR2702_2
#define STR2732 STR2703_2
const char STR2741[] PROGMEM = STR2741_TEXT;
const char STR2742[] PROGMEM = STR2742_TEXT;
const char STR2743[] PROGMEM = STR2743_TEXT;
const char STR2744[] PROGMEM = STR2744_TEXT;
const char STR2745[] PROGMEM = STR2745_TEXT;
#define STR2749 STR2703
const char STR2750[] PROGMEM = STR2750_TEXT;
const char STR2751[] PROGMEM = STR2751_TEXT;
const char STR2752[] PROGMEM = STR2752_TEXT;
const char STR2753[] PROGMEM = STR2753_TEXT;

// Wärmepumpe
const char STR2776[] PROGMEM = STR2776_TEXT;
const char STR2777[] PROGMEM = STR2777_TEXT;
const char STR2778[] PROGMEM = STR2778_TEXT;
const char STR2779[] PROGMEM = STR2779_TEXT;
const char STR2785[] PROGMEM = STR2785_TEXT;
const char STR2786[] PROGMEM = STR2786_TEXT;
const char STR2787[] PROGMEM = STR2787_TEXT;
const char STR2789[] PROGMEM = STR2789_TEXT;
const char STR2790[] PROGMEM = STR2790_TEXT;
#define STR2792 STR882
#define STR2793 STR883
#define STR2794 STR2324
#define STR2795 STR2325
#define STR2796 STR2326
const char STR2799[] PROGMEM = STR2799_TEXT;
const char STR2800[] PROGMEM = STR2800_TEXT;
const char STR2801[] PROGMEM = STR2801_TEXT;
const char STR2802[] PROGMEM = STR2802_TEXT;
const char STR2803[] PROGMEM = STR2803_TEXT;
const char STR2804[] PROGMEM = STR2804_TEXT;
const char STR2805[] PROGMEM = STR2805_TEXT;
const char STR2806[] PROGMEM = STR2806_TEXT;
const char STR2807[] PROGMEM = STR2807_TEXT;
const char STR2809[] PROGMEM = STR2809_TEXT;
const char STR2810[] PROGMEM = STR2810_TEXT;
const char STR2811[] PROGMEM = STR2811_TEXT;
const char STR2812[] PROGMEM = STR2812_TEXT;
const char STR2813[] PROGMEM = STR2813_TEXT;
const char STR2814[] PROGMEM = STR2814_TEXT;
const char STR2815[] PROGMEM = STR2815_TEXT;
const char STR2816[] PROGMEM = STR2816_TEXT;
const char STR2817[] PROGMEM = STR2817_TEXT;
const char STR2818[] PROGMEM = STR2818_TEXT;
const char STR2819[] PROGMEM = STR2819_TEXT;
const char STR2820[] PROGMEM = STR2820_TEXT;
const char STR2821[] PROGMEM = STR2821_TEXT;
const char STR2822[] PROGMEM = STR2822_TEXT;
const char STR2823[] PROGMEM = STR2823_TEXT;
const char STR2824[] PROGMEM = STR2824_TEXT;
const char STR2825[] PROGMEM = STR2825_TEXT;
const char STR2826[] PROGMEM = STR2826_TEXT;
const char STR2827[] PROGMEM = STR2827_TEXT;
const char STR2829[] PROGMEM = STR2829_TEXT;
const char STR2830[] PROGMEM = STR2830_TEXT;
const char STR2835[] PROGMEM = STR2835_TEXT;
const char STR2836[] PROGMEM = STR2836_TEXT;
const char STR2837[] PROGMEM = STR2837_TEXT;
const char STR2838[] PROGMEM = STR2838_TEXT;
const char STR2839[] PROGMEM = STR2839_TEXT;
const char STR2840[] PROGMEM = STR2840_TEXT;
const char STR2841[] PROGMEM = STR2841_TEXT;
const char STR2842[] PROGMEM = STR2842_TEXT;
const char STR2843[] PROGMEM = STR2843_TEXT;
const char STR2844[] PROGMEM = STR2844_TEXT;
const char STR2845[] PROGMEM = STR2845_TEXT;
const char STR2846[] PROGMEM = STR2846_TEXT;
const char STR2847[] PROGMEM = STR2847_TEXT;
const char STR2848[] PROGMEM = STR2848_TEXT;
const char STR2849[] PROGMEM = STR2849_TEXT;
const char STR2850[] PROGMEM = STR2850_TEXT;
const char STR2851[] PROGMEM = STR2851_TEXT;
const char STR2852[] PROGMEM = STR2852_TEXT;
const char STR2853[] PROGMEM = STR2853_TEXT;
const char STR2854[] PROGMEM = STR2854_TEXT;
const char STR2860[] PROGMEM = STR2860_TEXT;
const char STR2861[] PROGMEM = STR2861_TEXT;
const char STR2862[] PROGMEM = STR2862_TEXT;
const char STR2863[] PROGMEM = STR2863_TEXT;
const char STR2864[] PROGMEM = STR2864_TEXT;
const char STR2865[] PROGMEM = STR2865_TEXT;
const char STR2867[] PROGMEM = STR2867_TEXT;
#define STR2868 STR2330
const char STR2870[] PROGMEM = STR2870_TEXT;
const char STR2871[] PROGMEM = STR2871_TEXT;
const char STR2873[] PROGMEM = STR2873_TEXT;
const char STR2874[] PROGMEM = STR2874_TEXT;
const char STR2875[] PROGMEM = STR2875_TEXT;
const char STR2878[] PROGMEM = STR2878_TEXT;
const char STR2879[] PROGMEM = STR2879_TEXT;
const char STR2880[] PROGMEM = STR2880_TEXT;
const char STR2881[] PROGMEM = STR2881_TEXT;
const char STR2882[] PROGMEM = STR2882_TEXT;
const char STR2883[] PROGMEM = STR2883_TEXT;
const char STR2884[] PROGMEM = STR2884_TEXT;
const char STR2886[] PROGMEM = STR2886_TEXT;
const char STR2889[] PROGMEM = STR2889_TEXT;
const char STR2893[] PROGMEM = STR2893_TEXT;
const char STR2894[] PROGMEM = STR2894_TEXT;
const char STR2895[] PROGMEM = STR2895_TEXT;
const char STR2896[] PROGMEM = STR2896_TEXT;
const char STR2898[] PROGMEM = STR2898_TEXT;
const char STR2899[] PROGMEM = STR2899_TEXT;
const char STR2903[] PROGMEM = STR2903_TEXT;
const char STR2904[] PROGMEM = STR2904_TEXT;
const char STR2908[] PROGMEM = STR2908_TEXT;
#define STR2909 STR2203
const char STR2910[] PROGMEM = STR2910_TEXT;
const char STR2911[] PROGMEM = STR2911_TEXT;
#define STR2912 STR2208
const char STR2916[] PROGMEM = STR2916_TEXT;
const char STR2920[] PROGMEM = STR2920_TEXT;
const char STR2922[] PROGMEM = STR2922_TEXT;
const char STR2923[] PROGMEM = STR2923_TEXT;
const char STR2941[] PROGMEM = STR2941_TEXT;
const char STR2951[] PROGMEM = STR2951_TEXT;
const char STR2952[] PROGMEM = STR2952_TEXT;
const char STR2954[] PROGMEM = STR2954_TEXT;
const char STR2963[] PROGMEM = STR2963_TEXT;
const char STR2964[] PROGMEM = STR2964_TEXT;
const char STR2965[] PROGMEM = STR2965_TEXT;
const char STR2966[] PROGMEM = STR2966_TEXT;
const char STR2970[] PROGMEM = STR2970_TEXT;
const char STR3000[] PROGMEM = STR3000_TEXT;
const char STR3002[] PROGMEM = STR3002_TEXT;
const char STR3004[] PROGMEM = STR3004_TEXT;
const char STR3006[] PROGMEM = STR3006_TEXT;
const char STR3007[] PROGMEM = STR3007_TEXT;
const char STR3008[] PROGMEM = STR3008_TEXT;
const char STR3009[] PROGMEM = STR3009_TEXT;
const char STR3010[] PROGMEM = STR3010_TEXT;
const char STR3011[] PROGMEM = STR3011_TEXT;
const char STR3012[] PROGMEM = STR3012_TEXT;
const char STR3014[] PROGMEM = STR3014_TEXT;
const char STR3025[] PROGMEM = STR3025_TEXT;
const char STR3026[] PROGMEM = STR3026_TEXT;
const char STR3027[] PROGMEM = STR3027_TEXT;
const char STR3028[] PROGMEM = STR3028_TEXT;
const char STR3029[] PROGMEM = STR3029_TEXT;

// Energiezähler (Fujitsu Waterstage)
const char STR3090[] PROGMEM = STR3090_TEXT;
const char STR3092[] PROGMEM = STR3092_TEXT;
const char STR3093[] PROGMEM = STR3093_TEXT;
const char STR3094[] PROGMEM = STR3094_TEXT;
const char STR3095[] PROGMEM = STR3095_TEXT;
const char STR3097[] PROGMEM = STR3097_TEXT;
const char STR3098[] PROGMEM = STR3098_TEXT;
const char STR3100[] PROGMEM = STR3100_TEXT;
const char STR3102[] PROGMEM = STR3102_TEXT;
const char STR3103[] PROGMEM = STR3103_TEXT;
const char STR3104[] PROGMEM = STR3104_TEXT;
const char STR3106[] PROGMEM = STR3106_TEXT;
const char STR3108[] PROGMEM = STR3108_TEXT;
const char STR3109[] PROGMEM = STR3109_TEXT;
const char STR3110[] PROGMEM = STR3110_TEXT;
const char STR3113[] PROGMEM = STR3113_TEXT;
const char STR3116[] PROGMEM = STR3116_TEXT;
const char STR3119[] PROGMEM = STR3119_TEXT;
const char STR3121[] PROGMEM = STR3121_TEXT;
const char STR3122[] PROGMEM = STR3122_TEXT;
const char STR3123[] PROGMEM = STR3123_TEXT;
const char STR3124[] PROGMEM = STR3124_TEXT;
const char STR3125[] PROGMEM = STR3125_TEXT;
const char STR3126[] PROGMEM = STR3126_TEXT;
const char STR3128[] PROGMEM = STR3128_TEXT;
const char STR3129[] PROGMEM = STR3129_TEXT;
const char STR3130[] PROGMEM = STR3130_TEXT;
const char STR3131[] PROGMEM = STR3131_TEXT;
const char STR3132[] PROGMEM = STR3132_TEXT;
const char STR3133[] PROGMEM = STR3133_TEXT;
const char STR3135[] PROGMEM = STR3135_TEXT;
const char STR3136[] PROGMEM = STR3136_TEXT;
const char STR3137[] PROGMEM = STR3137_TEXT;
const char STR3138[] PROGMEM = STR3138_TEXT;
const char STR3139[] PROGMEM = STR3139_TEXT;
const char STR3140[] PROGMEM = STR3140_TEXT;
const char STR3142[] PROGMEM = STR3142_TEXT;
const char STR3143[] PROGMEM = STR3143_TEXT;
const char STR3144[] PROGMEM = STR3144_TEXT;
const char STR3145[] PROGMEM = STR3145_TEXT;
const char STR3146[] PROGMEM = STR3146_TEXT;
const char STR3147[] PROGMEM = STR3147_TEXT;
const char STR3149[] PROGMEM = STR3149_TEXT;
const char STR3150[] PROGMEM = STR3150_TEXT;
const char STR3151[] PROGMEM = STR3151_TEXT;
const char STR3152[] PROGMEM = STR3152_TEXT;
const char STR3153[] PROGMEM = STR3153_TEXT;
const char STR3154[] PROGMEM = STR3154_TEXT;
const char STR3156[] PROGMEM = STR3156_TEXT;
const char STR3157[] PROGMEM = STR3157_TEXT;
const char STR3158[] PROGMEM = STR3158_TEXT;
const char STR3159[] PROGMEM = STR3159_TEXT;
const char STR3160[] PROGMEM = STR3160_TEXT;
const char STR3161[] PROGMEM = STR3161_TEXT;
const char STR3163[] PROGMEM = STR3163_TEXT;
const char STR3164[] PROGMEM = STR3164_TEXT;
const char STR3165[] PROGMEM = STR3165_TEXT;
const char STR3166[] PROGMEM = STR3166_TEXT;
const char STR3167[] PROGMEM = STR3167_TEXT;
const char STR3168[] PROGMEM = STR3168_TEXT;
const char STR3170[] PROGMEM = STR3170_TEXT;
const char STR3171[] PROGMEM = STR3171_TEXT;
const char STR3172[] PROGMEM = STR3172_TEXT;
const char STR3173[] PROGMEM = STR3173_TEXT;
const char STR3174[] PROGMEM = STR3174_TEXT;
const char STR3175[] PROGMEM = STR3175_TEXT;
const char STR3177[] PROGMEM = STR3177_TEXT;
const char STR3178[] PROGMEM = STR3178_TEXT;
const char STR3179[] PROGMEM = STR3179_TEXT;
const char STR3180[] PROGMEM = STR3180_TEXT;
const char STR3181[] PROGMEM = STR3181_TEXT;
const char STR3182[] PROGMEM = STR3182_TEXT;
const char STR3184[] PROGMEM = STR3184_TEXT;
const char STR3185[] PROGMEM = STR3185_TEXT;
const char STR3186[] PROGMEM = STR3186_TEXT;
const char STR3187[] PROGMEM = STR3187_TEXT;
const char STR3188[] PROGMEM = STR3188_TEXT;
const char STR3189[] PROGMEM = STR3189_TEXT;
const char STR3190[] PROGMEM = STR3190_TEXT;
const char STR3192[] PROGMEM = STR3192_TEXT;
const char STR3264[] PROGMEM = STR3264_TEXT;
const char STR3265[] PROGMEM = STR3265_TEXT;
const char STR3266[] PROGMEM = STR3266_TEXT;
const char STR3267[] PROGMEM = STR3267_TEXT;

// 3500 Kaskade
const char STR3510[] PROGMEM = STR3510_TEXT;
const char STR3511[] PROGMEM = STR3511_TEXT;
const char STR3512[] PROGMEM = STR3512_TEXT;
const char STR3530[] PROGMEM = STR3530_TEXT;
const char STR3531[] PROGMEM = STR3531_TEXT;
const char STR3532[] PROGMEM = STR3532_TEXT;
const char STR3533[] PROGMEM = STR3533_TEXT;
const char STR3534[] PROGMEM = STR3534_TEXT;
const char STR3540[] PROGMEM = STR3540_TEXT;
const char STR3541[] PROGMEM = STR3541_TEXT;
const char STR3544[] PROGMEM = STR3544_TEXT;
const char STR3550[] PROGMEM = STR3550_TEXT;
#define STR3560 STR2270
#define STR3561 STR2271
#define STR3562 STR2272
#define STR3570 STR834
#define STR3571 STR835
#define STR3572 STR836
const char STR3590[] PROGMEM = STR3590_TEXT;

// 3700 Zusatzerzeuger
#define STR3700 STR2203
#define STR3701 STR2204
const char STR3705[] PROGMEM = STR3705_TEXT;
const char STR3720[] PROGMEM = STR3720_TEXT;
const char STR3722[] PROGMEM = STR3722_TEXT;
const char STR3723[] PROGMEM = STR3723_TEXT;

// 3800 Solar
const char STR3810[] PROGMEM = STR3810_TEXT;
const char STR3811[] PROGMEM = STR3811_TEXT;
const char STR3812[] PROGMEM = STR3812_TEXT;
const char STR3813[] PROGMEM = STR3813_TEXT;
const char STR3814[] PROGMEM = STR3814_TEXT;
const char STR3815[] PROGMEM = STR3815_TEXT;
const char STR3816[] PROGMEM = STR3816_TEXT;
const char STR3817[] PROGMEM = STR3817_TEXT;
const char STR3818[] PROGMEM = STR3818_TEXT;
const char STR3822[] PROGMEM = STR3822_TEXT;
const char STR3825[] PROGMEM = STR3825_TEXT;
const char STR3826[] PROGMEM = STR3826_TEXT;
const char STR3827[] PROGMEM = STR3827_TEXT;
const char STR3828[] PROGMEM = STR3828_TEXT;
const char STR3830[] PROGMEM = STR3830_TEXT;
const char STR3831[] PROGMEM = STR3831_TEXT;
const char STR3832[] PROGMEM = STR3832_TEXT;
const char STR3833[] PROGMEM = STR3833_TEXT;
const char STR3834[] PROGMEM = STR3834_TEXT;
const char STR3840[] PROGMEM = STR3840_TEXT;
const char STR3850[] PROGMEM = STR3850_TEXT;
const char STR3860[] PROGMEM = STR3860_TEXT;
#define STR3870 STR882
#define STR3871 STR883
#define STR3872 STR835
#define STR3873 STR836
const char STR3880[] PROGMEM = STR3880_TEXT;
const char STR3881[] PROGMEM = STR3881_TEXT;
const char STR3884[] PROGMEM = STR3884_TEXT;
const char STR3887[] PROGMEM = STR3887_TEXT;

// 4100 Feststoffkessel
const char STR4102[] PROGMEM = STR4102_TEXT;
const char STR4103[] PROGMEM = STR4103_TEXT;
#define STR4110 STR2210
#define STR4112 STR2212
#define STR4114 STR2315
#define STR4130 STR3810
#define STR4131 STR3811
const char STR4133[] PROGMEM = STR4133_TEXT;
const char STR4134[] PROGMEM = STR4134_TEXT;
const char STR4135[] PROGMEM = STR4135_TEXT;
const char STR4136[] PROGMEM = STR4136_TEXT;
const char STR4137[] PROGMEM = STR4137_TEXT;
const char STR4138[] PROGMEM = STR4138_TEXT;
#define STR4140 STR2250
const char STR4141[] PROGMEM = STR4141_TEXT;
#define STR4153 STR2270
const char STR4158[] PROGMEM = STR4158_TEXT;
#define STR4163 STR834
#define STR4164 STR835
#define STR4165 STR836
#define STR4170 STR2300
const char STR4190[] PROGMEM = STR4190_TEXT;
const char STR4192[] PROGMEM = STR4192_TEXT;
#define STR4201 STR882
#define STR4202 STR883
#define STR4203 STR2324
#define STR4204 STR2325

// 4700 Pufferspeicher
const char STR4708[] PROGMEM = STR4708_TEXT;
const char STR4709[] PROGMEM = STR4709_TEXT;
const char STR4710[] PROGMEM = STR4710_TEXT;
const char STR4711[] PROGMEM = STR4711_TEXT;
const char STR4712[] PROGMEM = STR4712_TEXT;
const char STR4720[] PROGMEM = STR4720_TEXT;
const char STR4721[] PROGMEM = STR4721_TEXT;
const char STR4722[] PROGMEM = STR4722_TEXT;
const char STR4724[] PROGMEM = STR4724_TEXT;
const char STR4739[] PROGMEM = STR4739_TEXT;
const char STR4740[] PROGMEM = STR4740_TEXT;
const char STR4743[] PROGMEM = STR4743_TEXT;
const char STR4744[] PROGMEM = STR4744_TEXT;
const char STR4746[] PROGMEM = STR4746_TEXT;
const char STR4750[] PROGMEM = STR4750_TEXT;
const char STR4751[] PROGMEM = STR4751_TEXT;
const char STR4755[] PROGMEM = STR4755_TEXT;
const char STR4756[] PROGMEM = STR4756_TEXT;
const char STR4757[] PROGMEM = STR4757_TEXT;
const char STR4760[] PROGMEM = STR4760_TEXT;
const char STR4761[] PROGMEM = STR4761_TEXT;
#define STR4783 STR2080
const char STR4790[] PROGMEM = STR4790_TEXT;
const char STR4791[] PROGMEM = STR4791_TEXT;
const char STR4795[] PROGMEM = STR4795_TEXT;
const char STR4796[] PROGMEM = STR4796_TEXT;
#define STR4810 STR2208
const char STR4811[] PROGMEM = STR4811_TEXT;
const char STR4813[] PROGMEM = STR4813_TEXT;
// 5000 Trinkwasserspeicher
const char STR5010[] PROGMEM = STR5010_TEXT;
const char STR5011[] PROGMEM = STR5011_TEXT;
const char STR5019[] PROGMEM = STR5019_TEXT;
const char STR5020[] PROGMEM = STR5020_TEXT;
const char STR5021[] PROGMEM = STR5021_TEXT;
const char STR5022[] PROGMEM = STR5022_TEXT;
const char STR5022_2[] PROGMEM = STR5022_2_TEXT;
const char STR5024[] PROGMEM = STR5024_TEXT;
const char STR5025[] PROGMEM = STR5025_TEXT;
const char STR5026[] PROGMEM = STR5026_TEXT;
const char STR5027[] PROGMEM = STR5027_TEXT;
const char STR5028[] PROGMEM = STR5028_TEXT;
const char STR5029[] PROGMEM = STR5029_TEXT;
const char STR5030[] PROGMEM = STR5030_TEXT;
const char STR5040[] PROGMEM = STR5040_TEXT;
const char STR5050[] PROGMEM = STR5050_TEXT;
const char STR5051[] PROGMEM = STR5051_TEXT;
const char STR5055[] PROGMEM = STR5055_TEXT;
const char STR5056[] PROGMEM = STR5056_TEXT;
const char STR5057[] PROGMEM = STR5057_TEXT;
const char STR5060[] PROGMEM = STR5060_TEXT;
const char STR5061[] PROGMEM = STR5061_TEXT;
const char STR5062[] PROGMEM = STR5062_TEXT;
const char STR5070[] PROGMEM = STR5070_TEXT;
const char STR5071[] PROGMEM = STR5071_TEXT;
const char STR5085[] PROGMEM = STR5085_TEXT;
const char STR5090[] PROGMEM = STR5090_TEXT;
const char STR5092[] PROGMEM = STR5092_TEXT;
const char STR5093[] PROGMEM = STR5093_TEXT;
const char STR5100[] PROGMEM = STR5100_TEXT;
const char STR5101[] PROGMEM = STR5101_TEXT;
const char STR5102[] PROGMEM = STR5102_TEXT;
#define STR5103 STR2324
#define STR5104 STR2325
#define STR5105 STR2326
const char STR5108[] PROGMEM = STR5108_TEXT;
const char STR5109[] PROGMEM = STR5109_TEXT;
#define STR5120 STR830
#define STR5124 STR834
#define STR5125 STR835
#define STR5126 STR836
const char STR5130[] PROGMEM = STR5130_TEXT;
const char STR5131[] PROGMEM = STR5131_TEXT;
const char STR5139[] PROGMEM = STR5139_TEXT;
const char STR5140[] PROGMEM = STR5140_TEXT;
const char STR5141[] PROGMEM = STR5141_TEXT;
const char STR5142[] PROGMEM = STR5142_TEXT;
const char STR5146[] PROGMEM = STR5146_TEXT;
const char STR5148[] PROGMEM = STR5148_TEXT;
const char STR5151[] PROGMEM = STR5151_TEXT;

// 5400 Trinkwasser Durchlauferhitzer
#define STR5400 STR710
const char STR5406[] PROGMEM = STR5406_TEXT;
const char STR5420[] PROGMEM = STR5420_TEXT;
const char STR5430[] PROGMEM = STR5430_TEXT;
const char STR5431[] PROGMEM = STR5431_TEXT;
const char STR5432[] PROGMEM = STR5432_TEXT;
const char STR5433[] PROGMEM = STR5433_TEXT;
const char STR5434[] PROGMEM = STR5434_TEXT;
const char STR5435[] PROGMEM = STR5435_TEXT;
const char STR5450[] PROGMEM = STR5450_TEXT;
const char STR5451[] PROGMEM = STR5451_TEXT;
const char STR5452[] PROGMEM = STR5452_TEXT;
const char STR5453[] PROGMEM = STR5453_TEXT;
const char STR5454[] PROGMEM = STR5454_TEXT;
const char STR5455[] PROGMEM = STR5455_TEXT;
const char STR5456[] PROGMEM = STR5456_TEXT;
const char STR5480[] PROGMEM = STR5480_TEXT;
const char STR5481[] PROGMEM = STR5481_TEXT;
const char STR5482[] PROGMEM = STR5482_TEXT;
const char STR5483[] PROGMEM = STR5483_TEXT;
const char STR5486[] PROGMEM = STR5486_TEXT;
const char STR5487[] PROGMEM = STR5487_TEXT;
const char STR5488[] PROGMEM = STR5488_TEXT;
#define STR5530 STR882
#define STR5544 STR834
#define STR5545 STR835
#define STR5546 STR836
#define STR5547 STR2285
// Konfiguration
const char STR5700[] PROGMEM = STR5700_TEXT;
const char STR5701[] PROGMEM = STR5701_TEXT;
const char STR5710[] PROGMEM = STR5710_TEXT;
const char STR5711[] PROGMEM = STR5711_TEXT;
const char STR5712[] PROGMEM = STR5712_TEXT;
const char STR5715[] PROGMEM = STR5715_TEXT;
const char STR5721[] PROGMEM = STR5721_TEXT;
const char STR5730[] PROGMEM = STR5730_TEXT;
const char STR5731[] PROGMEM = STR5731_TEXT;
const char STR5732[] PROGMEM = STR5732_TEXT;
const char STR5733[] PROGMEM = STR5733_TEXT;
const char STR5734[] PROGMEM = STR5734_TEXT;
const char STR5736[] PROGMEM = STR5736_TEXT;
// const char STR5737[] PROGMEM = "Wirksinn TWW Umlenkventil";
const char STR5740[] PROGMEM = STR5740_TEXT;
#define STR5760 STR2150
const char STR5761[] PROGMEM = STR5761_TEXT;
const char STR5770[] PROGMEM = STR5770_TEXT;
const char STR5772[] PROGMEM = STR5772_TEXT;
const char STR5774[] PROGMEM = STR5774_TEXT;
const char STR5800[] PROGMEM = STR5800_TEXT;
const char STR5806[] PROGMEM = STR5806_TEXT;
const char STR5807[] PROGMEM = STR5807_TEXT;
const char STR5810[] PROGMEM = STR5810_TEXT;
const char STR5811[] PROGMEM = STR5811_TEXT;
const char STR5813[] PROGMEM = STR5813_TEXT;
const char STR5840[] PROGMEM = STR5840_TEXT;
const char STR5841[] PROGMEM = STR5841_TEXT;
const char STR5870[] PROGMEM = STR5870_TEXT;
const char STR5890[] PROGMEM = STR5890_TEXT;
const char STR5890_2[] PROGMEM = STR5890_2_TEXT;
const char STR5891[] PROGMEM = STR5891_TEXT;
const char STR5891_2[] PROGMEM = STR5891_2_TEXT;
const char STR5892[] PROGMEM = STR5892_TEXT;
const char STR5894[] PROGMEM = STR5894_TEXT;
const char STR5895[] PROGMEM = STR5895_TEXT;
const char STR5896[] PROGMEM = STR5896_TEXT;
const char STR5902[] PROGMEM = STR5902_TEXT;
const char STR5904[] PROGMEM = STR5904_TEXT;
const char STR5908[] PROGMEM = STR5908_TEXT;
const char STR5909[] PROGMEM = STR5909_TEXT;
const char STR5920[] PROGMEM = STR5920_TEXT;
const char STR5921[] PROGMEM = STR5921_TEXT;
const char STR5922[] PROGMEM = STR5922_TEXT;
const char STR5923[] PROGMEM = STR5923_TEXT;
const char STR5924[] PROGMEM = STR5924_TEXT;
const char STR5926[] PROGMEM = STR5926_TEXT;
const char STR5927[] PROGMEM = STR5927_TEXT;
const char STR5928[] PROGMEM = STR5928_TEXT;
const char STR5930[] PROGMEM = STR5930_TEXT;
const char STR5931[] PROGMEM = STR5931_TEXT;
const char STR5932[] PROGMEM = STR5932_TEXT;
const char STR5933[] PROGMEM = STR5933_TEXT;
const char STR5934[] PROGMEM = STR5934_TEXT;
const char STR5941[] PROGMEM = STR5941_TEXT;
const char STR5942[] PROGMEM = STR5942_TEXT;
const char STR5950[] PROGMEM = STR5950_TEXT;
const char STR5951[] PROGMEM = STR5951_TEXT;
const char STR5952[] PROGMEM = STR5952_TEXT;
const char STR5953[] PROGMEM = STR5953_TEXT;
const char STR5954[] PROGMEM = STR5954_TEXT;
const char STR5954_2[] PROGMEM = STR5954_2_TEXT;
const char STR5955[] PROGMEM = STR5955_TEXT;
const char STR5956[] PROGMEM = STR5956_TEXT;
const char STR5956_2[] PROGMEM = STR5956_2_TEXT;
const char STR5957_2[] PROGMEM = STR5957_2_TEXT;
#define STR5957_3 STR5950
const char STR5960_2[] PROGMEM = STR5960_2_TEXT;
const char STR5961_2[] PROGMEM = STR5961_2_TEXT;
const char STR5962_2[] PROGMEM = STR5962_2_TEXT;
const char STR5963_2[] PROGMEM = STR5963_2_TEXT;
const char STR5964_2[] PROGMEM = STR5964_2_TEXT;
const char STR5957[] PROGMEM = STR5957_TEXT;
const char STR5960[] PROGMEM = STR5960_TEXT;
const char STR5961[] PROGMEM = STR5961_TEXT;
const char STR5962[] PROGMEM = STR5962_TEXT;
const char STR5963[] PROGMEM = STR5963_TEXT;
const char STR5964[] PROGMEM = STR5964_TEXT;
const char STR5965[] PROGMEM = STR5965_TEXT;
const char STR5966[] PROGMEM = STR5966_TEXT;
const char STR5970[] PROGMEM = STR5970_TEXT;
const char STR5970_2[] PROGMEM = STR5970_2_TEXT;
const char STR5971[] PROGMEM = STR5971_TEXT;
const char STR5971_2[] PROGMEM = STR5971_2_TEXT;
const char STR5973[] PROGMEM = STR5973_TEXT;
const char STR5975[] PROGMEM = STR5975_TEXT;
const char STR5976[] PROGMEM = STR5976_TEXT;
const char STR5977[] PROGMEM = STR5977_TEXT;
const char STR5978[] PROGMEM = STR5978_TEXT;
const char STR5978_2[] PROGMEM = STR5978_2_TEXT;
const char STR5980[] PROGMEM = STR5980_TEXT;
const char STR5981[] PROGMEM = STR5981_TEXT;
const char STR5982[] PROGMEM = STR5982_TEXT;
const char STR5983[] PROGMEM = STR5983_TEXT;
const char STR5984[] PROGMEM = STR5984_TEXT;
const char STR5985[] PROGMEM = STR5985_TEXT;
const char STR5986[] PROGMEM = STR5986_TEXT;
const char STR5987[] PROGMEM = STR5987_TEXT;
const char STR5988[] PROGMEM = STR5988_TEXT;
const char STR5989[] PROGMEM = STR5989_TEXT;
const char STR5990[] PROGMEM = STR5990_TEXT;
const char STR5992[] PROGMEM = STR5992_TEXT;
const char STR6014[] PROGMEM = STR6014_TEXT;
const char STR6015[] PROGMEM = STR6015_TEXT;
const char STR6020[] PROGMEM = STR6020_TEXT;
const char STR6021[] PROGMEM = STR6021_TEXT;
const char STR6030[] PROGMEM = STR6030_TEXT;
const char STR6031[] PROGMEM = STR6031_TEXT;
const char STR6032[] PROGMEM = STR6032_TEXT;
const char STR6033[] PROGMEM = STR6033_TEXT;
const char STR6034[] PROGMEM = STR6034_TEXT;
const char STR6035[] PROGMEM = STR6035_TEXT;
const char STR6040[] PROGMEM = STR6040_TEXT;
const char STR6041[] PROGMEM = STR6041_TEXT;
const char STR6042[] PROGMEM = STR6042_TEXT;
const char STR6043[] PROGMEM = STR6043_TEXT;
#define STR6046 STR5960_2
#define STR6047 STR5961_2
#define STR6048 STR5962_2
const char STR6048_2[] PROGMEM = STR6048_2_TEXT;
#define STR6049 STR5963_2
#define STR6050 STR5964_2
const char STR6050_2[] PROGMEM = STR6050_2_TEXT;
const char STR6051[] PROGMEM = STR6051_TEXT;
const char STR6052[] PROGMEM = STR6052_TEXT;
const char STR6070[] PROGMEM = STR6070_TEXT;
const char STR6071[] PROGMEM = STR6071_TEXT;
const char STR6072[] PROGMEM = STR6072_TEXT;
const char STR6075[] PROGMEM = STR6075_TEXT;
const char STR6085[] PROGMEM = STR6085_TEXT;
const char STR6089[] PROGMEM = STR6089_TEXT;
const char STR6092[] PROGMEM = STR6092_TEXT;
const char STR6097[] PROGMEM = STR6097_TEXT;
const char STR6098[] PROGMEM = STR6098_TEXT;
const char STR6099[] PROGMEM = STR6099_TEXT;
const char STR6100[] PROGMEM = STR6100_TEXT;
const char STR6101[] PROGMEM = STR6101_TEXT;
const char STR6102[] PROGMEM = STR6102_TEXT;
const char STR6110[] PROGMEM = STR6110_TEXT;
const char STR6112[] PROGMEM = STR6112_TEXT;
const char STR6116[] PROGMEM = STR6116_TEXT;
const char STR6117[] PROGMEM = STR6117_TEXT;
const char STR6118[] PROGMEM = STR6118_TEXT;
const char STR6120[] PROGMEM = STR6120_TEXT;
const char STR6127[] PROGMEM = STR6127_TEXT;
const char STR6128[] PROGMEM = STR6128_TEXT;
const char STR6129[] PROGMEM = STR6129_TEXT;
#define STR6130 STR2012
const char STR6131[] PROGMEM = STR6131_TEXT;
#define STR6134 STR2037
const char STR6135[] PROGMEM = STR6135_TEXT;
const char STR6136[] PROGMEM = STR6136_TEXT;
const char STR6137[] PROGMEM = STR6137_TEXT;
const char STR6138[] PROGMEM = STR6138_TEXT;
const char STR6140[] PROGMEM = STR6140_TEXT;
const char STR6141[] PROGMEM = STR6141_TEXT;
const char STR6142[] PROGMEM = STR6142_TEXT;
const char STR6143[] PROGMEM = STR6143_TEXT;
const char STR6144[] PROGMEM = STR6144_TEXT;
const char STR6145[] PROGMEM = STR6145_TEXT;
const char STR6146[] PROGMEM = STR6146_TEXT;
const char STR6148[] PROGMEM = STR6148_TEXT;
const char STR6150[] PROGMEM = STR6150_TEXT;
const char STR6151[] PROGMEM = STR6151_TEXT;
const char STR6152[] PROGMEM = STR6152_TEXT;
const char STR6180[] PROGMEM = STR6180_TEXT;
const char STR6181[] PROGMEM = STR6181_TEXT;
const char STR6182[] PROGMEM = STR6182_TEXT;
const char STR6200[] PROGMEM = STR6200_TEXT;
const char STR6201[] PROGMEM = STR6201_TEXT;
const char STR6204[] PROGMEM = STR6204_TEXT;
const char STR6205[] PROGMEM = STR6205_TEXT;
const char STR6212[] PROGMEM = STR6212_TEXT;
const char STR6213[] PROGMEM = STR6213_TEXT;
const char STR6215[] PROGMEM = STR6215_TEXT;
const char STR6217[] PROGMEM = STR6217_TEXT;
const char STR6220[] PROGMEM = STR6220_TEXT;
const char STR6221[] PROGMEM = STR6221_TEXT;
const char STR6222[] PROGMEM = STR6222_TEXT;
const char STR6223[] PROGMEM = STR6223_TEXT;
const char STR6224[] PROGMEM = STR6224_TEXT;
const char STR6225[] PROGMEM = STR6225_TEXT;
const char STR6226[] PROGMEM = STR6226_TEXT;
const char STR6227[] PROGMEM = STR6227_TEXT;
const char STR6228[] PROGMEM = STR6228_TEXT;
const char STR6229[] PROGMEM = STR6229_TEXT;
const char STR6230[] PROGMEM = STR6230_TEXT;
const char STR6230_2[] PROGMEM = STR6230_2_TEXT;
const char STR6231[] PROGMEM = STR6231_TEXT;
const char STR6232[] PROGMEM = STR6232_TEXT;
const char STR6233[] PROGMEM = STR6233_TEXT;
const char STR6234[] PROGMEM = STR6234_TEXT;
const char STR6235[] PROGMEM = STR6235_TEXT;
const char STR6236[] PROGMEM = STR6236_TEXT;
const char STR6240[] PROGMEM = STR6240_TEXT;
const char STR6250[] PROGMEM = STR6250_TEXT;
const char STR6260[] PROGMEM = STR6260_TEXT;
const char STR6270[] PROGMEM = STR6270_TEXT;
const char STR6270_2[] PROGMEM = STR6270_2_TEXT;
const char STR6271[] PROGMEM = STR6271_TEXT;
const char STR6272[] PROGMEM = STR6272_TEXT;
const char STR6273[] PROGMEM = STR6273_TEXT;
const char STR6280[] PROGMEM = STR6280_TEXT;
const char STR6290[] PROGMEM = STR6290_TEXT;
const char STR6300[] PROGMEM = STR6300_TEXT;
const char STR6300_2[] PROGMEM = STR6300_2_TEXT;
const char STR6310[] PROGMEM = STR6310_TEXT;
const char STR6330[] PROGMEM = STR6330_TEXT;
const char STR6375[] PROGMEM = STR6375_TEXT;
const char STR6420[] PROGMEM = STR6420_TEXT;
const char STR6421[] PROGMEM = STR6421_TEXT;

const char STR6486[] PROGMEM = STR6486_TEXT;
const char STR6487[] PROGMEM = STR6487_TEXT;
const char STR6488[] PROGMEM = STR6488_TEXT;
const char STR6489[] PROGMEM = STR6489_TEXT;
const char STR6490[] PROGMEM = STR6490_TEXT;
const char STR6491[] PROGMEM = STR6491_TEXT;
const char STR6492[] PROGMEM = STR6492_TEXT;
const char STR6493[] PROGMEM = STR6493_TEXT;
const char STR6494[] PROGMEM = STR6494_TEXT;
const char STR6495[] PROGMEM = STR6495_TEXT;
const char STR6496[] PROGMEM = STR6496_TEXT;
const char STR6497[] PROGMEM = STR6497_TEXT;
const char STR6498[] PROGMEM = STR6498_TEXT;


// LPB-System
const char STR6600[] PROGMEM = STR6600_TEXT;
const char STR6601[] PROGMEM = STR6601_TEXT;
const char STR6604[] PROGMEM = STR6604_TEXT;
const char STR6605[] PROGMEM = STR6605_TEXT;
const char STR6606[] PROGMEM = STR6606_TEXT;
const char STR6610[] PROGMEM = STR6610_TEXT;
const char STR6612[] PROGMEM = STR6612_TEXT;
const char STR6620[] PROGMEM = STR6620_TEXT;
const char STR6621[] PROGMEM = STR6621_TEXT;
#define STR6623 STR900
const char STR6624[] PROGMEM = STR6624_TEXT;
const char STR6625[] PROGMEM = STR6625_TEXT;
const char STR6627[] PROGMEM = STR6627_TEXT;
const char STR6630[] PROGMEM = STR6630_TEXT;
const char STR6631[] PROGMEM = STR6631_TEXT;
const char STR6632[] PROGMEM = STR6632_TEXT;
const char STR6640[] PROGMEM = STR6640_TEXT;
const char STR6650[] PROGMEM = STR6650_TEXT;
const char STR6699[] PROGMEM = STR6699_TEXT;

// Fehler
const char STR6705[] PROGMEM = STR6705_TEXT;
const char STR6706[] PROGMEM = STR6706_TEXT;
const char STR6710[] PROGMEM = STR6710_TEXT;
const char STR6711[] PROGMEM = STR6711_TEXT;
const char STR6740[] PROGMEM = STR6740_TEXT;
const char STR6741[] PROGMEM = STR6741_TEXT;
const char STR6742[] PROGMEM = STR6742_TEXT;
const char STR6743[] PROGMEM = STR6743_TEXT;
const char STR6745[] PROGMEM = STR6745_TEXT;
const char STR6746[] PROGMEM = STR6746_TEXT;
const char STR6747[] PROGMEM = STR6747_TEXT;

// THISION Fehlerparameter
const char STR6800_2[] PROGMEM = STR6800_2_TEXT;
const char STR6801_2[] PROGMEM = STR6801_2_TEXT;
const char STR6805_2[] PROGMEM = STR6805_2_TEXT;
const char STR6806_2[] PROGMEM = STR6806_2_TEXT;
const char STR6810_2[] PROGMEM = STR6810_2_TEXT;
const char STR6811_2[] PROGMEM = STR6811_2_TEXT;
const char STR6813_2[] PROGMEM = STR6813_2_TEXT;
const char STR6815_2[] PROGMEM = STR6815_2_TEXT;
const char STR6816_2[] PROGMEM = STR6816_2_TEXT;
const char STR6820_2[] PROGMEM = STR6820_2_TEXT;
const char STR6821[] PROGMEM = STR6821_TEXT;
const char STR6823_2[] PROGMEM = STR6823_2_TEXT;
const char STR6825[] PROGMEM = STR6825_TEXT;
const char STR6826[] PROGMEM = STR6826_TEXT;
const char STR6830[] PROGMEM = STR6830_TEXT;
const char STR6831[] PROGMEM = STR6831_TEXT;
const char STR6833_2[] PROGMEM = STR6833_2_TEXT;
const char STR6835[] PROGMEM = STR6835_TEXT;
const char STR6836[] PROGMEM = STR6836_TEXT;
const char STR6840_2[] PROGMEM = STR6840_2_TEXT;
const char STR6843_2[] PROGMEM = STR6843_2_TEXT;
const char STR6845[] PROGMEM = STR6845_TEXT;
const char STR6846[] PROGMEM = STR6846_TEXT;
const char STR6855[] PROGMEM = STR6855_TEXT;
const char STR6856[] PROGMEM = STR6856_TEXT;
const char STR6865[] PROGMEM = STR6865_TEXT;
const char STR6866[] PROGMEM = STR6866_TEXT;
const char STR6875[] PROGMEM = STR6875_TEXT;
const char STR6876[] PROGMEM = STR6876_TEXT;
const char STR6885[] PROGMEM = STR6885_TEXT;
const char STR6886[] PROGMEM = STR6886_TEXT;
const char STR6895[] PROGMEM = STR6895_TEXT;
const char STR6896[] PROGMEM = STR6896_TEXT;
const char STR6905[] PROGMEM = STR6905_TEXT;
const char STR6906[] PROGMEM = STR6906_TEXT;
const char STR6915[] PROGMEM = STR6915_TEXT;
const char STR6916[] PROGMEM = STR6916_TEXT;
const char STR6925[] PROGMEM = STR6925_TEXT;
const char STR6926[] PROGMEM = STR6926_TEXT;
const char STR6935[] PROGMEM = STR6935_TEXT;
const char STR6936[] PROGMEM = STR6936_TEXT;
const char STR6945[] PROGMEM = STR6945_TEXT;
const char STR6946[] PROGMEM = STR6946_TEXT;
const char STR6955[] PROGMEM = STR6955_TEXT;
const char STR6956[] PROGMEM = STR6956_TEXT;
const char STR6965[] PROGMEM = STR6965_TEXT;
const char STR6966[] PROGMEM = STR6966_TEXT;
const char STR6975[] PROGMEM = STR6975_TEXT;
const char STR6976[] PROGMEM = STR6976_TEXT;
const char STR6985[] PROGMEM = STR6985_TEXT;
const char STR6986[] PROGMEM = STR6986_TEXT;
const char STR6995[] PROGMEM = STR6995_TEXT;
const char STR6996[] PROGMEM = STR6996_TEXT;

#define STR6803_2 STR6801_2
#define STR6813_2 STR6810_2
#define STR6823 STR6820_2
#define STR6833 STR6830
#define STR6840 STR6808
#define STR6843 STR6840
#define STR6841 STR6809
#define STR6850 STR6810
#define STR6851 STR6811
#define STR6860 STR6812
#define STR6861 STR6813
#define STR6870 STR6814
#define STR6871 STR6815
#define STR6880 STR6816
#define STR6881 STR6817
#define STR6890 STR6818
#define STR6891 STR6819

// übrige Fehlerparameter
const char STR6800[] PROGMEM = STR6800_TEXT;
const char STR6801[] PROGMEM = STR6801_TEXT;
const char STR6802[] PROGMEM = STR6802_TEXT;
const char STR6803[] PROGMEM = STR6803_TEXT;
const char STR6804[] PROGMEM = STR6804_TEXT;
const char STR6805[] PROGMEM = STR6805_TEXT;
const char STR6806[] PROGMEM = STR6806_TEXT;
const char STR6807[] PROGMEM = STR6807_TEXT;
const char STR6808[] PROGMEM = STR6808_TEXT;
const char STR6809[] PROGMEM = STR6809_TEXT;
const char STR6810[] PROGMEM = STR6810_TEXT;
const char STR6811[] PROGMEM = STR6811_TEXT;
const char STR6812[] PROGMEM = STR6812_TEXT;
const char STR6813[] PROGMEM = STR6813_TEXT;
const char STR6814[] PROGMEM = STR6814_TEXT;
const char STR6815[] PROGMEM = STR6815_TEXT;
const char STR6816[] PROGMEM = STR6816_TEXT;
const char STR6817[] PROGMEM = STR6817_TEXT;
const char STR6818[] PROGMEM = STR6818_TEXT;
const char STR6819[] PROGMEM = STR6819_TEXT;
const char STR6900[] PROGMEM = STR6900_TEXT;
const char STR6901[] PROGMEM = STR6901_TEXT;
const char STR6910[] PROGMEM = STR6910_TEXT;
const char STR6911[] PROGMEM = STR6911_TEXT;
const char STR6920[] PROGMEM = STR6920_TEXT;
const char STR6921[] PROGMEM = STR6921_TEXT;
const char STR6930[] PROGMEM = STR6930_TEXT;
const char STR6931[] PROGMEM = STR6931_TEXT;
const char STR6940[] PROGMEM = STR6940_TEXT;
const char STR6941[] PROGMEM = STR6941_TEXT;
const char STR6950[] PROGMEM = STR6950_TEXT;
const char STR6951[] PROGMEM = STR6951_TEXT;
const char STR6960[] PROGMEM = STR6960_TEXT;
const char STR6961[] PROGMEM = STR6961_TEXT;
const char STR6970[] PROGMEM = STR6970_TEXT;
const char STR6971[] PROGMEM = STR6971_TEXT;
const char STR6980[] PROGMEM = STR6980_TEXT;
const char STR6981[] PROGMEM = STR6981_TEXT;
const char STR6990[] PROGMEM = STR6990_TEXT;
const char STR6991[] PROGMEM = STR6991_TEXT;
const char STR6820[] PROGMEM = STR6820_TEXT;

// Wartung / Sonderbetrieb
const char STR7001[] PROGMEM = STR7001_TEXT;
const char STR7007[] PROGMEM = STR7007_TEXT;
const char STR7010[] PROGMEM = STR7010_TEXT;
const char STR7011[] PROGMEM = STR7011_TEXT;
const char STR7012[] PROGMEM = STR7012_TEXT;
const char STR7040[] PROGMEM = STR7040_TEXT;
const char STR7041[] PROGMEM = STR7041_TEXT;
const char STR7042[] PROGMEM = STR7042_TEXT;
const char STR7043[] PROGMEM = STR7043_TEXT;
const char STR7044[] PROGMEM = STR7044_TEXT;
const char STR7045[] PROGMEM = STR7045_TEXT;
const char STR7046[] PROGMEM = STR7046_TEXT;
const char STR7050[] PROGMEM = STR7050_TEXT;
const char STR7051[] PROGMEM = STR7051_TEXT;
const char STR7053[] PROGMEM = STR7053_TEXT;
const char STR7054[] PROGMEM = STR7054_TEXT;
const char STR7056[] PROGMEM = STR7056_TEXT;
const char STR7070[] PROGMEM = STR7070_TEXT;
const char STR7071[] PROGMEM = STR7071_TEXT;
const char STR7072[] PROGMEM = STR7072_TEXT;
const char STR7073[] PROGMEM = STR7073_TEXT;
const char STR7074[] PROGMEM = STR7074_TEXT;
const char STR7075[] PROGMEM = STR7075_TEXT;
const char STR7076[] PROGMEM = STR7076_TEXT;
const char STR7077[] PROGMEM = STR7077_TEXT;
const char STR7078[] PROGMEM = STR7078_TEXT;
const char STR7079[] PROGMEM = STR7079_TEXT;
const char STR7080[] PROGMEM = STR7080_TEXT;
const char STR7081[] PROGMEM = STR7081_TEXT;
const char STR7082[] PROGMEM = STR7082_TEXT;
const char STR7083[] PROGMEM = STR7083_TEXT;
const char STR7090[] PROGMEM = STR7090_TEXT;
const char STR7091[] PROGMEM = STR7091_TEXT;
const char STR7092[] PROGMEM = STR7092_TEXT;
const char STR7093[] PROGMEM = STR7093_TEXT;
const char STR7119[] PROGMEM = STR7119_TEXT;
const char STR7120[] PROGMEM = STR7120_TEXT;
const char STR7130[] PROGMEM = STR7130_TEXT;
const char STR7131[] PROGMEM = STR7131_TEXT;
const char STR7140[] PROGMEM = STR7140_TEXT;
const char STR7141[] PROGMEM = STR7141_TEXT;
const char STR7142[] PROGMEM = STR7142_TEXT;
const char STR7143[] PROGMEM = STR7143_TEXT;
const char STR7145[] PROGMEM = STR7145_TEXT;
const char STR7146[] PROGMEM = STR7146_TEXT;
const char STR7147[] PROGMEM = STR7147_TEXT;
const char STR7150[] PROGMEM = STR7150_TEXT;
const char STR7152[] PROGMEM = STR7152_TEXT;
const char STR7160[] PROGMEM = STR7160_TEXT;
const char STR7166[] PROGMEM = STR7166_TEXT;
const char STR7170[] PROGMEM = STR7170_TEXT;
const char STR7181[] PROGMEM = STR7181_TEXT;
const char STR7183[] PROGMEM = STR7183_TEXT;
const char STR7250[] PROGMEM = STR7250_TEXT;
const char STR7251[] PROGMEM = STR7251_TEXT;
const char STR7252[] PROGMEM = STR7252_TEXT;
const char STR7253[] PROGMEM = STR7253_TEXT;

// Konfiguration Erweit'module
const char STR7311[] PROGMEM = STR7311_TEXT;
#define STR7376 STR6033
#define STR7377 STR6034
#define STR7378 STR6035
const char STR7386[] PROGMEM = STR7386_TEXT;
const char STR7387[] PROGMEM = STR7387_TEXT;
const char STR7396[] PROGMEM = STR7396_TEXT;
const char STR7399[] PROGMEM = STR7399_TEXT;
const char STR7400[] PROGMEM = STR7400_TEXT;
const char STR7401[] PROGMEM = STR7401_TEXT;
const char STR7402[] PROGMEM = STR7402_TEXT;
const char STR7423[] PROGMEM = STR7423_TEXT;
const char STR7425[] PROGMEM = STR7425_TEXT;
const char STR7430[] PROGMEM = STR7430_TEXT;
const char STR7432[] PROGMEM = STR7432_TEXT;

// Ein-/Ausgangstest
const char STR7700[] PROGMEM = STR7700_TEXT;
const char STR7705[] PROGMEM = STR7705_TEXT;
const char STR7708[] PROGMEM = STR7708_TEXT;
const char STR7710[] PROGMEM = STR7710_TEXT;
const char STR7711[] PROGMEM = STR7711_TEXT;
const char STR7712[] PROGMEM = STR7712_TEXT;
const char STR7713[] PROGMEM = STR7713_TEXT;
const char STR7714[] PROGMEM = STR7714_TEXT;
const char STR7716[] PROGMEM = STR7716_TEXT;
const char STR7719[] PROGMEM = STR7719_TEXT;
const char STR7720[] PROGMEM = STR7720_TEXT;
const char STR7721[] PROGMEM = STR7721_TEXT;
const char STR7722[] PROGMEM = STR7722_TEXT;
const char STR7723[] PROGMEM = STR7723_TEXT;
const char STR7724[] PROGMEM = STR7724_TEXT;
const char STR7725[] PROGMEM = STR7725_TEXT;
const char STR7730[] PROGMEM = STR7730_TEXT;
const char STR7732[] PROGMEM = STR7732_TEXT;
const char STR7734[] PROGMEM = STR7734_TEXT;
const char STR7750[] PROGMEM = STR7750_TEXT;
const char STR7760[] PROGMEM = STR7760_TEXT;
const char STR7770[] PROGMEM = STR7770_TEXT;
const char STR7771[] PROGMEM = STR7771_TEXT;
const char STR7772[] PROGMEM = STR7772_TEXT;
const char STR7775[] PROGMEM = STR7775_TEXT;
const char STR7777[] PROGMEM = STR7777_TEXT;
const char STR7784[] PROGMEM = STR7784_TEXT;
const char STR7785[] PROGMEM = STR7785_TEXT;
const char STR7785_2[] PROGMEM = STR7785_2_TEXT;
const char STR7786[] PROGMEM = STR7786_TEXT;
const char STR7787[] PROGMEM = STR7787_TEXT;
const char STR7787_2[] PROGMEM = STR7787_2_TEXT;
const char STR7809[] PROGMEM = STR7809_TEXT;
const char STR7820[] PROGMEM = STR7820_TEXT;
const char STR7821[] PROGMEM = STR7821_TEXT;
const char STR7822[] PROGMEM = STR7822_TEXT;
const char STR7823[] PROGMEM = STR7823_TEXT;
const char STR7824[] PROGMEM = STR7824_TEXT;
const char STR7830[] PROGMEM = STR7830_TEXT;
const char STR7831[] PROGMEM = STR7831_TEXT;
const char STR7832[] PROGMEM = STR7832_TEXT;
const char STR7833[] PROGMEM = STR7833_TEXT;
const char STR7840[] PROGMEM = STR7840_TEXT;
const char STR7841[] PROGMEM = STR7841_TEXT;
const char STR7844[] PROGMEM = STR7844_TEXT;
const char STR7845[] PROGMEM = STR7845_TEXT;
const char STR7846[] PROGMEM = STR7846_TEXT;
const char STR7847[] PROGMEM = STR7847_TEXT;
const char STR7848[] PROGMEM = STR7848_TEXT;
const char STR7849[] PROGMEM = STR7849_TEXT;
const char STR7854[] PROGMEM = STR7854_TEXT;
const char STR7855[] PROGMEM = STR7855_TEXT;
const char STR7858[] PROGMEM = STR7858_TEXT;
const char STR7860[] PROGMEM = STR7860_TEXT;
const char STR7865[] PROGMEM = STR7865_TEXT;
const char STR7870[] PROGMEM = STR7870_TEXT;
const char STR7872[] PROGMEM = STR7872_TEXT;
const char STR7881[] PROGMEM = STR7881_TEXT;
const char STR7884[] PROGMEM = STR7884_TEXT;
const char STR7889[] PROGMEM = STR7889_TEXT;
const char STR7890[] PROGMEM = STR7890_TEXT;
const char STR7891[] PROGMEM = STR7891_TEXT;
const char STR7911[] PROGMEM = STR7911_TEXT;
const char STR7912[] PROGMEM = STR7912_TEXT;
const char STR7913[] PROGMEM = STR7913_TEXT;
const char STR7914[] PROGMEM = STR7914_TEXT;
const char STR7915[] PROGMEM = STR7915_TEXT;
const char STR7916[] PROGMEM = STR7916_TEXT;
const char STR7917[] PROGMEM = STR7917_TEXT;
const char STR7950[] PROGMEM = STR7950_TEXT;
const char STR7951[] PROGMEM = STR7951_TEXT;
const char STR7952[] PROGMEM = STR7952_TEXT;
const char STR7973[] PROGMEM = STR7973_TEXT;
const char STR7974[] PROGMEM = STR7974_TEXT;
const char STR7975[] PROGMEM = STR7975_TEXT;
const char STR7976[] PROGMEM = STR7976_TEXT;
const char STR7977[] PROGMEM = STR7977_TEXT;
const char STR7978[] PROGMEM = STR7978_TEXT;
const char STR7996[] PROGMEM = STR7996_TEXT;
const char STR7999[] PROGMEM = STR7999_TEXT;

// Status
const char STR8000[] PROGMEM = STR8000_TEXT;
const char STR8001[] PROGMEM = STR8001_TEXT;
const char STR8002[] PROGMEM = STR8002_TEXT;
const char STR8003[] PROGMEM = STR8003_TEXT;
const char STR8004[] PROGMEM = STR8004_TEXT;
const char STR8005[] PROGMEM = STR8005_TEXT;
const char STR8006[] PROGMEM = STR8006_TEXT;
const char STR8007[] PROGMEM = STR8007_TEXT;
const char STR8008[] PROGMEM = STR8008_TEXT;
const char STR8009[] PROGMEM = STR8009_TEXT;
const char STR8010[] PROGMEM = STR8010_TEXT;
const char STR8011[] PROGMEM = STR8011_TEXT;
const char STR8022[] PROGMEM = STR8022_TEXT;
const char STR8023[] PROGMEM = STR8023_TEXT;
const char STR8025[] PROGMEM = STR8025_TEXT;
const char STR8050[] PROGMEM = STR8050_TEXT;
const char STR8051[] PROGMEM = STR8051_TEXT;
const char STR8052[] PROGMEM = STR8052_TEXT;
const char STR8053[] PROGMEM = STR8053_TEXT;
const char STR8054[] PROGMEM = STR8054_TEXT;
const char STR8055[] PROGMEM = STR8055_TEXT;
const char STR8056[] PROGMEM = STR8056_TEXT;
const char STR8057[] PROGMEM = STR8057_TEXT;
const char STR8058[] PROGMEM = STR8058_TEXT;
const char STR8059[] PROGMEM = STR8059_TEXT;
const char STR8060[] PROGMEM = STR8060_TEXT;
const char STR8061[] PROGMEM = STR8061_TEXT;
const char STR8062[] PROGMEM = STR8062_TEXT;
const char STR8063[] PROGMEM = STR8063_TEXT;
const char STR8064[] PROGMEM = STR8064_TEXT;
const char STR8065[] PROGMEM = STR8065_TEXT;
const char STR8066[] PROGMEM = STR8066_TEXT;
const char STR8067[] PROGMEM = STR8067_TEXT;
const char STR8068[] PROGMEM = STR8068_TEXT;
#define STR8069 STR8067

const char STR8099[] PROGMEM = STR8099_TEXT;

// Diagnose Kaskade
const char STR8100[] PROGMEM = STR8100_TEXT;
const char STR8102[] PROGMEM = STR8102_TEXT;
const char STR8104[] PROGMEM = STR8104_TEXT;
const char STR8106[] PROGMEM = STR8106_TEXT;
const char STR8108[] PROGMEM = STR8108_TEXT;
const char STR8110[] PROGMEM = STR8110_TEXT;
const char STR8112[] PROGMEM = STR8112_TEXT;
const char STR8114[] PROGMEM = STR8114_TEXT;
const char STR8116[] PROGMEM = STR8116_TEXT;
const char STR8118[] PROGMEM = STR8118_TEXT;
const char STR8120[] PROGMEM = STR8120_TEXT;
const char STR8122[] PROGMEM = STR8122_TEXT;
const char STR8124[] PROGMEM = STR8124_TEXT;
const char STR8126[] PROGMEM = STR8126_TEXT;
const char STR8128[] PROGMEM = STR8128_TEXT;
const char STR8130[] PROGMEM = STR8130_TEXT;
const char STR8138[] PROGMEM = STR8138_TEXT;
const char STR8139[] PROGMEM = STR8139_TEXT;
const char STR8140[] PROGMEM = STR8140_TEXT;
const char STR8141[] PROGMEM = STR8141_TEXT;
const char STR8150[] PROGMEM = STR8150_TEXT;
const char STR8199[] PROGMEM = STR8199_TEXT;

// 8300 Diagnose Erzeuger
const char STR8300[] PROGMEM = STR8300_TEXT;
const char STR8301[] PROGMEM = STR8301_TEXT;
const char STR8302[] PROGMEM = STR8302_TEXT;
const char STR8303[] PROGMEM = STR8303_TEXT;
const char STR8304[] PROGMEM = STR8304_TEXT;
const char STR8308[] PROGMEM = STR8308_TEXT;
const char STR8310[] PROGMEM = STR8310_TEXT;
const char STR8311[] PROGMEM = STR8311_TEXT;
const char STR8312[] PROGMEM = STR8312_TEXT;
const char STR8313[] PROGMEM = STR8313_TEXT;
const char STR8314[] PROGMEM = STR8314_TEXT;
const char STR8315[] PROGMEM = STR8315_TEXT;
const char STR8316[] PROGMEM = STR8316_TEXT;
const char STR8318[] PROGMEM = STR8318_TEXT;
const char STR8319[] PROGMEM = STR8319_TEXT;
const char STR8320[] PROGMEM = STR8320_TEXT;
const char STR8321[] PROGMEM = STR8321_TEXT;
const char STR8323[] PROGMEM = STR8323_TEXT;
const char STR8324[] PROGMEM = STR8324_TEXT;
const char STR8325[] PROGMEM = STR8325_TEXT;
const char STR8325_2[] PROGMEM = STR8325_2_TEXT;
const char STR8326[] PROGMEM = STR8326_TEXT;
const char STR8327[] PROGMEM = STR8327_TEXT;
const char STR8328[] PROGMEM = STR8328_TEXT;
#define STR8329 STR2730
const char STR8330[] PROGMEM = STR8330_TEXT;
const char STR8331[] PROGMEM = STR8331_TEXT;
const char STR8332[] PROGMEM = STR8332_TEXT;
const char STR8333[] PROGMEM = STR8333_TEXT;
const char STR8336[] PROGMEM = STR8336_TEXT;
const char STR8337[] PROGMEM = STR8337_TEXT;
const char STR8338[] PROGMEM = STR8338_TEXT;
const char STR8339[] PROGMEM = STR8339_TEXT;
const char STR8340[] PROGMEM = STR8340_TEXT;
const char STR8378[] PROGMEM = STR8378_TEXT;
const char STR8379[] PROGMEM = STR8379_TEXT;
const char STR8380[] PROGMEM = STR8380_TEXT;
const char STR8381[] PROGMEM = STR8381_TEXT;
const char STR8382[] PROGMEM = STR8382_TEXT;
const char STR8383[] PROGMEM = STR8383_TEXT;
const char STR8390[] PROGMEM = STR8390_TEXT;
const char STR8395[] PROGMEM = STR8395_TEXT;
const char STR8396[] PROGMEM = STR8396_TEXT;
const char STR8397[] PROGMEM = STR8397_TEXT;
const char STR8398[] PROGMEM = STR8398_TEXT;
const char STR8400[] PROGMEM = STR8400_TEXT;
const char STR8401[] PROGMEM = STR8401_TEXT;
const char STR8402[] PROGMEM = STR8402_TEXT;
const char STR8403[] PROGMEM = STR8403_TEXT;
const char STR8404[] PROGMEM = STR8404_TEXT;
const char STR8405[] PROGMEM = STR8405_TEXT;
const char STR8406[] PROGMEM = STR8406_TEXT;
const char STR8407[] PROGMEM = STR8407_TEXT;
const char STR8408[] PROGMEM = STR8408_TEXT;
const char STR8410[] PROGMEM = STR8410_TEXT;
const char STR8411[] PROGMEM = STR8411_TEXT;
const char STR8412[] PROGMEM = STR8412_TEXT;
const char STR8413[] PROGMEM = STR8413_TEXT;
const char STR8414[] PROGMEM = STR8414_TEXT;
const char STR8415[] PROGMEM = STR8415_TEXT;
const char STR8416[] PROGMEM = STR8416_TEXT;
const char STR8417[] PROGMEM = STR8417_TEXT;
const char STR8420[] PROGMEM = STR8420_TEXT;
const char STR8423[] PROGMEM = STR8423_TEXT;
const char STR8424[] PROGMEM = STR8424_TEXT;
const char STR8425[] PROGMEM = STR8425_TEXT;
const char STR8426[] PROGMEM = STR8426_TEXT;
const char STR8427[] PROGMEM = STR8427_TEXT;
const char STR8428[] PROGMEM = STR8428_TEXT;
const char STR8429[] PROGMEM = STR8429_TEXT;
const char STR8430[] PROGMEM = STR8430_TEXT;
const char STR8431[] PROGMEM = STR8431_TEXT;
const char STR8434[] PROGMEM = STR8434_TEXT;
const char STR8435[] PROGMEM = STR8435_TEXT;
const char STR8435_1[] PROGMEM = STR8435_1_TEXT;
const char STR8436[] PROGMEM = STR8436_TEXT;
const char STR8436_1[] PROGMEM = STR8436_1_TEXT;
const char STR8437[] PROGMEM = STR8437_TEXT;
const char STR8438[] PROGMEM = STR8438_TEXT;
const char STR8440[] PROGMEM = STR8440_TEXT;
const char STR8441[] PROGMEM = STR8441_TEXT;
const char STR8442[] PROGMEM = STR8442_TEXT;
const char STR8443[] PROGMEM = STR8443_TEXT;
const char STR8444[] PROGMEM = STR8444_TEXT;
const char STR8446[] PROGMEM = STR8446_TEXT;
const char STR8448[] PROGMEM = STR8448_TEXT;
const char STR8449[] PROGMEM = STR8449_TEXT;
const char STR8450[] PROGMEM = STR8450_TEXT;
const char STR8451[] PROGMEM = STR8451_TEXT;
const char STR8452[] PROGMEM = STR8452_TEXT;
const char STR8453[] PROGMEM = STR8453_TEXT;
const char STR8454[] PROGMEM = STR8454_TEXT;
const char STR8455[] PROGMEM = STR8455_TEXT;
const char STR8456[] PROGMEM = STR8456_TEXT;
const char STR8457[] PROGMEM = STR8457_TEXT;
const char STR8458[] PROGMEM = STR8458_TEXT;
const char STR8460[] PROGMEM = STR8460_TEXT;
const char STR8461[] PROGMEM = STR8461_TEXT;
const char STR8462[] PROGMEM = STR8462_TEXT;
const char STR8463[] PROGMEM = STR8463_TEXT;
// Kommt auch noch ein Telegramm 0x593D1779, könnte Verdampfungsdruck E in bar sein oder vertauscht mit dem oben
const char STR8464[] PROGMEM = STR8464_TEXT;
// Kommt auch noch ein Telegramm 0x593D17AC, könnte Überhitzungssollwert E in °C sein oder vertauscht mit dem oben
const char STR8465[] PROGMEM = STR8465_TEXT;
const char STR8466[] PROGMEM = STR8466_TEXT;
const char STR8467[] PROGMEM = STR8467_TEXT;
const char STR8469[] PROGMEM = STR8469_TEXT;
const char STR8470[] PROGMEM = STR8470_TEXT;
const char STR8471[] PROGMEM = STR8471_TEXT;
const char STR8475[] PROGMEM = STR8475_TEXT;
const char STR8477[] PROGMEM = STR8477_TEXT;
const char STR8478[] PROGMEM = STR8478_TEXT;
const char STR8480[] PROGMEM = STR8480_TEXT;
const char STR8481[] PROGMEM = STR8481_TEXT;
const char STR8482[] PROGMEM = STR8482_TEXT;
const char STR8485[] PROGMEM = STR8485_TEXT;
const char STR8487[] PROGMEM = STR8487_TEXT;
// Diagnose Erzeuger - Solar
const char STR8499[] PROGMEM = STR8499_TEXT;
const char STR8499_2[] PROGMEM = STR8499_2_TEXT;
const char STR8501[] PROGMEM = STR8501_TEXT;
const char STR8502[] PROGMEM = STR8502_TEXT;
const char STR8505[] PROGMEM = STR8505_TEXT;
const char STR8506[] PROGMEM = STR8506_TEXT;
const char STR8507[] PROGMEM = STR8507_TEXT;
const char STR8508[] PROGMEM = STR8508_TEXT;
const char STR8510[] PROGMEM = STR8510_TEXT;
const char STR8511[] PROGMEM = STR8511_TEXT;
const char STR8512[] PROGMEM = STR8512_TEXT;
const char STR8513[] PROGMEM = STR8513_TEXT;
const char STR8513_2[] PROGMEM = STR8513_2_TEXT;
const char STR8514[] PROGMEM = STR8514_TEXT;
const char STR8515[] PROGMEM = STR8515_TEXT;
const char STR8519[] PROGMEM = STR8519_TEXT;
const char STR8520[] PROGMEM = STR8520_TEXT;
const char STR8521[] PROGMEM = STR8521_TEXT;
const char STR8526[] PROGMEM = STR8526_TEXT;
const char STR8527[] PROGMEM = STR8527_TEXT;
const char STR8530[] PROGMEM = STR8530_TEXT;
const char STR8531[] PROGMEM = STR8531_TEXT;
const char STR8532[] PROGMEM = STR8532_TEXT;
const char STR8543[] PROGMEM = STR8543_TEXT;
const char STR8547[] PROGMEM = STR8547_TEXT;
const char STR8548[] PROGMEM = STR8548_TEXT;
const char STR8549[] PROGMEM = STR8549_TEXT;
const char STR8550[] PROGMEM = STR8550_TEXT;
const char STR8551[] PROGMEM = STR8551_TEXT;
const char STR8552[] PROGMEM = STR8552_TEXT;
const char STR8559[] PROGMEM = STR8559_TEXT;
const char STR8560[] PROGMEM = STR8560_TEXT;
const char STR8568[] PROGMEM = STR8568_TEXT;
const char STR8570[] PROGMEM = STR8570_TEXT;
#define STR8585 STR8319
const char STR8586[] PROGMEM = STR8586_TEXT;

// Diagnose Verbraucher
const char STR8700[] PROGMEM = STR8700_TEXT;
const char STR8701[] PROGMEM = STR8701_TEXT;
const char STR8702[] PROGMEM = STR8702_TEXT;
const char STR8703[] PROGMEM = STR8703_TEXT;
const char STR8704[] PROGMEM = STR8704_TEXT;
const char STR8705[] PROGMEM = STR8705_TEXT;
const char STR8720[] PROGMEM = STR8720_TEXT;
const char STR8721[] PROGMEM = STR8721_TEXT;
const char STR8722[] PROGMEM = STR8722_TEXT;
const char STR8730[] PROGMEM = STR8730_TEXT;
const char STR8731[] PROGMEM = STR8731_TEXT;
const char STR8732[] PROGMEM = STR8732_TEXT;
const char STR8735[] PROGMEM = STR8735_TEXT;
const char STR8740[] PROGMEM = STR8740_TEXT;
const char STR8741[] PROGMEM = STR8741_TEXT;
const char STR8742[] PROGMEM = STR8742_TEXT;
const char STR8743[] PROGMEM = STR8743_TEXT;
const char STR8744[] PROGMEM = STR8744_TEXT;
const char STR8749[] PROGMEM = STR8749_TEXT;
const char STR8750[] PROGMEM = STR8750_TEXT;
const char STR8751[] PROGMEM = STR8751_TEXT;
const char STR8752[] PROGMEM = STR8752_TEXT;
const char STR8753[] PROGMEM = STR8753_TEXT;
const char STR8754[] PROGMEM = STR8754_TEXT;
const char STR8756[] PROGMEM = STR8756_TEXT;
const char STR8757[] PROGMEM = STR8757_TEXT;
const char STR8760[] PROGMEM = STR8760_TEXT;
const char STR8761[] PROGMEM = STR8761_TEXT;
const char STR8762[] PROGMEM = STR8762_TEXT;
const char STR8765[] PROGMEM = STR8765_TEXT;
const char STR8770[] PROGMEM = STR8770_TEXT;
const char STR8771[] PROGMEM = STR8771_TEXT;
const char STR8772[] PROGMEM = STR8772_TEXT;
const char STR8773[] PROGMEM = STR8773_TEXT;
const char STR8774[] PROGMEM = STR8774_TEXT;
const char STR8779[] PROGMEM = STR8779_TEXT;
const char STR8790[] PROGMEM = STR8790_TEXT;
const char STR8791[] PROGMEM = STR8791_TEXT;
const char STR8792[] PROGMEM = STR8792_TEXT;
const char STR8795[] PROGMEM = STR8795_TEXT;
const char STR8800[] PROGMEM = STR8800_TEXT;
const char STR8801[] PROGMEM = STR8801_TEXT;
const char STR8802[] PROGMEM = STR8802_TEXT;
const char STR8803[] PROGMEM = STR8803_TEXT;
const char STR8804[] PROGMEM = STR8804_TEXT;
const char STR8809[] PROGMEM = STR8809_TEXT;
const char STR8820[] PROGMEM = STR8820_TEXT;
const char STR8821[] PROGMEM = STR8821_TEXT;
const char STR8825[] PROGMEM = STR8825_TEXT;
const char STR8826[] PROGMEM = STR8826_TEXT;
const char STR8827[] PROGMEM = STR8827_TEXT;
const char STR8830[] PROGMEM = STR8830_TEXT;
const char STR8831[] PROGMEM = STR8831_TEXT;
const char STR8832[] PROGMEM = STR8832_TEXT;
const char STR8835[] PROGMEM = STR8835_TEXT;
const char STR8836[] PROGMEM = STR8836_TEXT;
const char STR8840[] PROGMEM = STR8840_TEXT;
const char STR8841[] PROGMEM = STR8841_TEXT;
const char STR8842[] PROGMEM = STR8842_TEXT;
const char STR8843[] PROGMEM = STR8843_TEXT;
const char STR8850[] PROGMEM = STR8850_TEXT;
const char STR8851[] PROGMEM = STR8851_TEXT;
const char STR8852[] PROGMEM = STR8852_TEXT;
const char STR8853[] PROGMEM = STR8853_TEXT;
const char STR8860[] PROGMEM = STR8860_TEXT;
const char STR8875[] PROGMEM = STR8875_TEXT;
const char STR8885[] PROGMEM = STR8885_TEXT;
const char STR8895[] PROGMEM = STR8895_TEXT;
const char STR8900[] PROGMEM = STR8900_TEXT;
const char STR8901[] PROGMEM = STR8901_TEXT;
const char STR8930[] PROGMEM = STR8930_TEXT;
const char STR8931[] PROGMEM = STR8931_TEXT;
const char STR8950[] PROGMEM = STR8950_TEXT;
const char STR8951[] PROGMEM = STR8951_TEXT;
const char STR8952[] PROGMEM = STR8952_TEXT;
const char STR8957[] PROGMEM = STR8957_TEXT;
const char STR8962[] PROGMEM = STR8962_TEXT;
const char STR8970[] PROGMEM = STR8970_TEXT;
const char STR8980[] PROGMEM = STR8980_TEXT;
const char STR8981[] PROGMEM = STR8981_TEXT;
const char STR8982[] PROGMEM = STR8982_TEXT;
const char STR8983[] PROGMEM = STR8983_TEXT;
const char STR8984[] PROGMEM = STR8984_TEXT;
const char STR8990[] PROGMEM = STR8990_TEXT;
const char STR8991[] PROGMEM = STR8991_TEXT;
const char STR9000[] PROGMEM = STR9000_TEXT;
const char STR9001[] PROGMEM = STR9001_TEXT;
const char STR9004[] PROGMEM = STR9004_TEXT;
const char STR9005[] PROGMEM = STR9005_TEXT;
const char STR9006[] PROGMEM = STR9006_TEXT;
const char STR9009[] PROGMEM = STR9009_TEXT;
#define STR9031 STR5890
#define STR9032 STR5891
#define STR9033 STR5892
#define STR9034 STR5894
#define STR9035 STR5895
#define STR9036 STR5896
const char STR9037[] PROGMEM = STR9037_TEXT;
const char STR9038[] PROGMEM = STR9038_TEXT;
#define STR9050 STR6030
#define STR9051 STR6031
#define STR9052 STR6032
#define STR9053 STR6033
#define STR9054 STR6034
#define STR9055 STR6035
const char STR9056[] PROGMEM = STR9056_TEXT;
const char STR9057[] PROGMEM = STR9057_TEXT;
const char STR9058[] PROGMEM = STR9058_TEXT;
const char STR9071[] PROGMEM = STR9071_TEXT;
const char STR9072[] PROGMEM = STR9072_TEXT;
const char STR9073[] PROGMEM = STR9073_TEXT;
const char STR9074[] PROGMEM = STR9074_TEXT;
const char STR9075[] PROGMEM = STR9075_TEXT;

// Feuerungsautomat
const char STR9500[] PROGMEM = STR9500_TEXT;
const char STR9502[] PROGMEM = STR9502_TEXT;
const char STR9504[] PROGMEM = STR9504_TEXT;
const char STR9504_2[] PROGMEM = STR9504_2_TEXT;
const char STR9510[] PROGMEM = STR9510_TEXT;
const char STR9512[] PROGMEM = STR9512_TEXT;
const char STR9512_2[] PROGMEM = STR9512_2_TEXT;
const char STR9520[] PROGMEM = STR9520_TEXT;
const char STR9522[] PROGMEM = STR9522_TEXT;
const char STR9524[] PROGMEM = STR9524_TEXT;
const char STR9524_2[] PROGMEM = STR9524_2_TEXT;
const char STR9526[] PROGMEM = STR9526_TEXT;
const char STR9527[] PROGMEM = STR9527_TEXT;
const char STR9529[] PROGMEM = STR9529_TEXT;
const char STR9529_2[] PROGMEM = STR9529_2_TEXT;
const char STR9531[] PROGMEM = STR9531_TEXT;
const char STR9534[] PROGMEM = STR9534_TEXT;
const char STR9540[] PROGMEM = STR9540_TEXT;
const char STR9542[] PROGMEM = STR9542_TEXT;
const char STR9550[] PROGMEM = STR9550_TEXT;
const char STR9551[] PROGMEM = STR9551_TEXT;
const char STR9560[] PROGMEM = STR9560_TEXT;
const char STR9563[] PROGMEM = STR9563_TEXT;
const char STR9615[] PROGMEM = STR9615_TEXT;
const char STR9626[] PROGMEM = STR9626_TEXT;
const char STR9627[] PROGMEM = STR9627_TEXT;
const char STR9650[] PROGMEM = STR9650_TEXT;
const char STR9652[] PROGMEM = STR9652_TEXT;


/* User-defined command numbers */
const char STR10000[] PROGMEM = STR10000_TEXT;
#define STR10001 STR8770
#define STR10002 STR8800

const char STR10100[] PROGMEM = STR10100_TEXT;
const char STR10101[] PROGMEM = STR10101_TEXT;
const char STR10102[] PROGMEM = STR10102_TEXT;
const char STR10103[] PROGMEM = STR10103_TEXT;
const char STR10104[] PROGMEM = STR10104_TEXT;

const char STR10200[] PROGMEM = STR10200_TEXT;

const char STR15004[] PROGMEM = STR15004_TEXT;
const char STR15009[] PROGMEM = STR15009_TEXT;
const char STR15011[] PROGMEM = STR15011_TEXT;
const char STR15012[] PROGMEM = STR15012_TEXT;
const char STR15019[] PROGMEM = STR15019_TEXT;
const char STR15020[] PROGMEM = STR15020_TEXT;
const char STR15021[] PROGMEM = STR15021_TEXT;
const char STR15022[] PROGMEM = STR15022_TEXT;
const char STR15023[] PROGMEM = STR15023_TEXT;
const char STR15024[] PROGMEM = STR15024_TEXT;
const char STR15025[] PROGMEM = STR15025_TEXT;
const char STR15026[] PROGMEM = STR15026_TEXT;
const char STR15027[] PROGMEM = STR15027_TEXT;
const char STR15028[] PROGMEM = STR15028_TEXT;
const char STR15029[] PROGMEM = STR15029_TEXT;
const char STR15030[] PROGMEM = STR15030_TEXT;
const char STR15031[] PROGMEM = STR15031_TEXT;
const char STR15032[] PROGMEM = STR15032_TEXT;
const char STR15033[] PROGMEM = STR15033_TEXT;
const char STR15034[] PROGMEM = STR15034_TEXT;
const char STR15035[] PROGMEM = STR15035_TEXT;
const char STR15036[] PROGMEM = STR15036_TEXT;
const char STR15037[] PROGMEM = STR15037_TEXT;
const char STR15038[] PROGMEM = STR15038_TEXT;
const char STR15039[] PROGMEM = STR15039_TEXT;
const char STR15040[] PROGMEM = STR15040_TEXT;
const char STR15041[] PROGMEM = STR15041_TEXT;
const char STR15042[] PROGMEM = STR15042_TEXT;
const char STR15043[] PROGMEM = STR15043_TEXT;
const char STR15044[] PROGMEM = STR15044_TEXT;
const char STR15045[] PROGMEM = STR15045_TEXT;
const char STR15046[] PROGMEM = STR15046_TEXT;
const char STR15047[] PROGMEM = STR15047_TEXT;
const char STR15048[] PROGMEM = STR15048_TEXT;
const char STR15049[] PROGMEM = STR15049_TEXT;
const char STR15050[] PROGMEM = STR15050_TEXT;
const char STR15051[] PROGMEM = STR15051_TEXT;
const char STR15052[] PROGMEM = STR15052_TEXT;
const char STR15053[] PROGMEM = STR15053_TEXT;
const char STR15054[] PROGMEM = STR15054_TEXT;
const char STR15055[] PROGMEM = STR15055_TEXT;
const char STR15056[] PROGMEM = STR15056_TEXT;
const char STR15057[] PROGMEM = STR15057_TEXT;
const char STR15058[] PROGMEM = STR15058_TEXT;
const char STR15059[] PROGMEM = STR15059_TEXT;
const char STR15060[] PROGMEM = STR15060_TEXT;
const char STR15061[] PROGMEM = STR15061_TEXT;
const char STR15062[] PROGMEM = STR15062_TEXT;
const char STR15064[] PROGMEM = STR15064_TEXT;
const char STR15065[] PROGMEM = STR15065_TEXT;
const char STR15066[] PROGMEM = STR15066_TEXT;
const char STR15067[] PROGMEM = STR15067_TEXT;

// A catch-all description string for unrecognised command codes
const char STR99999[] PROGMEM = STR99999_TEXT;

#define ENUM42_00_TEXT ENUM_CAT_0b_TEXT
#define ENUM47_01_TEXT ENUM_CAT_0b_TEXT
#define ENUM48_01_TEXT ENUM_CAT_0b_TEXT
#define ENUM48_02_TEXT ENUM_CAT_0d_TEXT
#define ENUM700_02_TEXT ENUM648_01_TEXT
#define ENUM780_00_TEXT MENU_TEXT_OFF
#define ENUM850_00_TEXT ENUM780_00_TEXT
#define ENUM861_00_TEXT ENUM780_00_TEXT
#define ENUM898_00_TEXT ENUM700_00_TEXT
#define ENUM898_01_TEXT ENUM648_01_TEXT
#define ENUM898_02_TEXT ENUM700_03_TEXT
#define ENUM900_00_TEXT ENUM48_00_TEXT
#define ENUM900_01_TEXT ENUM700_00_TEXT
#define ENUM900_02_TEXT ENUM648_01_TEXT
#define ENUM900_03_TEXT ENUM700_03_TEXT
#define ENUM900_04_TEXT ENUM700_01_TEXT
#define ENUM900_2_00_TEXT ENUM700_00_TEXT
#define ENUM900_2_01_TEXT ENUM648_01_TEXT
#define ENUM900_2_03_TEXT ENUM700_03_TEXT
#define ENUM900_2_04_TEXT ENUM700_01_TEXT
#define ENUM1000_00_TEXT ENUM700_00_TEXT
#define ENUM1000_01_TEXT ENUM700_01_TEXT
#define ENUM1000_02_TEXT ENUM648_01_TEXT
#define ENUM1000_03_TEXT ENUM700_03_TEXT
#define ENUM1300_00_TEXT ENUM700_00_TEXT
#define ENUM1300_01_TEXT ENUM700_01_TEXT
#define ENUM1300_02_TEXT ENUM648_01_TEXT
#define ENUM1300_03_TEXT ENUM700_03_TEXT
#define ENUM1600_00_TEXT ENUM780_00_TEXT
#define ENUM1600_01_TEXT MENU_TEXT_ON
#define ENUM1620_2_00_TEXT ENUM1620_00_TEXT
#define ENUM1620_2_01_TEXT ENUM1620_01_TEXT
#define ENUM1620_2_04_TEXT ENUM1620_02_TEXT
#define ENUM1630_04_TEXT ENUM780_00_TEXT
#define ENUM1640_00_TEXT ENUM780_00_TEXT
#define ENUM1660_01_TEXT ENUM_CAT_05_TEXT
#define ENUM1660_03_TEXT ENUM1620_02_TEXT
#define ENUM1660_04_TEXT ENUM_CAT_07_TEXT
#define ENUM1680_00_TEXT ENUM48_00_TEXT
#define ENUM1680_01_TEXT ENUM780_00_TEXT
#define ENUM1680_02_TEXT ENUM1600_01_TEXT
#define ENUM2132_00_TEXT ENUM832_00_TEXT
#define ENUM2132_01_TEXT ENUM832_01_TEXT
#define ENUM2200_01_TEXT ENUM700_01_TEXT
#define ENUM2205_00_TEXT ENUM780_00_TEXT
#define ENUM2205_02_TEXT ENUM1600_01_TEXT
#define ENUM2305_2_01_TEXT ENUM2305_00_TEXT
#define ENUM2305_2_02_TEXT ENUM2305_01_TEXT
#define ENUM2320_00_TEXT ENUM48_00_TEXT
#define ENUM2320_03_TEXT ENUM880_02_TEXT
#define ENUM2450_00_TEXT ENUM780_00_TEXT
#define ENUM2450_01_TEXT ENUM2305_00_TEXT
#define ENUM2450_03_TEXT ENUM2305_01_TEXT
#define ENUM2500_00_TEXT ENUM2480_00_TEXT
#define ENUM2500_01_TEXT ENUM2480_ff_TEXT
#define ENUM2740_00_TEXT MENU_TEXT_NO
#define ENUM2706_03_TEXT ENUM2206_01_TEXT
#define ENUM2749_00_TEXT ENUM2740_00_TEXT
#define ENUM2801_01_TEXT ENUM5040_02_TEXT
#define ENUM2920_00_TEXT ENUM2706_00_TEXT
#define ENUM3095_00_TEXT ENUM48_00_TEXT
#define ENUM3100_00_TEXT ENUM48_00_TEXT
#define ENUM3100_01_TEXT ENUM3095_01_TEXT
#define ENUM3100_02_TEXT ENUM3095_05_TEXT
#define ENUM3100_03_TEXT ENUM3095_06_TEXT
#define ENUM3100_04_TEXT ENUM3095_07_TEXT
#define ENUM3100_05_TEXT ENUM3095_08_TEXT
#define ENUM3100_06_TEXT ENUM3095_09_TEXT
#define ENUM3100_07_TEXT ENUM3095_0a_TEXT
#define ENUM3100_08_TEXT ENUM3095_0b_TEXT
#define ENUM3100_09_TEXT ENUM3095_0c_TEXT
#define ENUM3100_0a_TEXT ENUM3095_0d_TEXT
#define ENUM3102_00_TEXT ENUM48_00_TEXT
#define ENUM3102_01_TEXT ENUM3092_00_TEXT
#define ENUM3109_00_TEXT ENUM48_00_TEXT
#define ENUM3192_03_TEXT ENUM3109_03_TEXT
#define ENUM3541_00_TEXT ENUM48_00_TEXT
#define ENUM3822_00_TEXT ENUM1630_02_TEXT
#define ENUM3822_01_TEXT ENUM_CAT_1c_TEXT
#define ENUM3822_02_TEXT ENUM_CAT_1b_TEXT
#define ENUM3880_01_TEXT ENUM1630_02_TEXT
#define ENUM3887_01_TEXT ENUM1630_02_TEXT
#define ENUM3887_02_TEXT ENUM3092_00_TEXT
#define ENUM4134_00_TEXT ENUM48_00_TEXT
#define ENUM4137_00_TEXT ENUM48_00_TEXT
#define ENUM4720_00_TEXT ENUM48_00_TEXT
#define ENUM4757_00_TEXT ENUM780_00_TEXT
#define ENUM4757_02_TEXT ENUM861_02_TEXT
#define ENUM4795_01_TEXT ENUM4720_01_TEXT
#define ENUM4810_00_TEXT ENUM780_00_TEXT
#define ENUM4810_01_TEXT ENUM861_01_TEXT
#define ENUM4810_02_TEXT ENUM861_02_TEXT
#define ENUM4813_01_TEXT ENUM4720_01_TEXT
#define ENUM5040_00_TEXT ENUM780_00_TEXT
#define ENUM5040_01_TEXT ENUM861_02_TEXT
#define ENUM5057_00_TEXT ENUM780_00_TEXT
#define ENUM5057_01_TEXT ENUM4757_01_TEXT
#define ENUM5057_02_TEXT ENUM861_02_TEXT
#define ENUM5060_02_TEXT ENUM4757_01_TEXT
#define ENUM5060_03_TEXT ENUM861_02_TEXT
#define ENUM5061_01_TEXT ENUM1620_00_TEXT
#define ENUM5061_02_TEXT ENUM1660_02_TEXT
#define ENUM5061_03_TEXT ENUM1620_02_TEXT
#define ENUM5130_00_TEXT ENUM861_02_TEXT
#define ENUM5131_00_TEXT ENUM4133_01_TEXT
#define ENUM5131_01_TEXT ENUM4133_02_TEXT
#define ENUM5711_00_TEXT ENUM780_00_TEXT
#define ENUM5715_00_TEXT ENUM780_00_TEXT
#define ENUM5734_02_TEXT ENUM_CAT_0f_TEXT
#define ENUM5760_01_TEXT ENUM2150_01_TEXT
#define ENUM5840_01_TEXT ENUM5731_01_TEXT
#define ENUM5840_02_TEXT ENUM5731_02_TEXT
#define ENUM5841_01_TEXT ENUM48_03_TEXT
#define ENUM5841_02_TEXT ENUM_CAT_1c_TEXT
#define ENUM5841_03_TEXT ENUM_CAT_1b_TEXT
#define ENUM5890_00_TEXT ENUM1630_02_TEXT
#define ENUM5890_23_TEXT STR5731_TEXT
#define ENUM5895_00_TEXT ENUM1630_02_TEXT
#define ENUM5895_01_TEXT ENUM5890_21_TEXT
#define ENUM5895_09_TEXT ENUM5890_01_TEXT
#define ENUM5895_0a_TEXT ENUM5890_02_TEXT
#define ENUM5895_0c_TEXT ENUM5890_03_TEXT
#define ENUM5895_0d_TEXT ENUM5890_04_TEXT
#define ENUM5895_0e_TEXT ENUM5890_05_TEXT
#define ENUM5895_0f_TEXT ENUM5890_06_TEXT
#define ENUM5895_10_TEXT ENUM5890_07_TEXT
#define ENUM5895_14_TEXT ENUM5890_0b_TEXT
#define ENUM5895_15_TEXT ENUM5890_0c_TEXT
#define ENUM5895_16_TEXT ENUM5890_0d_TEXT
#define ENUM5895_17_TEXT ENUM5890_0f_TEXT
#define ENUM5895_18_TEXT ENUM5890_10_TEXT
#define ENUM5895_19_TEXT ENUM5890_11_TEXT
#define ENUM5895_1b_TEXT ENUM5890_13_TEXT
#define ENUM5895_1c_TEXT ENUM5890_14_TEXT
#define ENUM5895_1d_TEXT ENUM5890_15_TEXT
#define ENUM5895_1e_TEXT ENUM5890_16_TEXT
#define ENUM5895_1f_TEXT ENUM5890_17_TEXT
#define ENUM5895_21_TEXT ENUM5895_08_TEXT
#define ENUM5895_26_TEXT ENUM5890_19_TEXT
#define ENUM5895_27_TEXT ENUM5890_1a_TEXT
#define ENUM5895_28_TEXT ENUM5890_1b_TEXT
#define ENUM5895_29_TEXT ENUM5890_1c_TEXT
#define ENUM5895_2a_TEXT ENUM5890_1d_TEXT
#define ENUM5920_02_TEXT ENUM5890_2_0b_TEXT
#define ENUM5920_11_TEXT ENUM5890_1b_TEXT
#define ENUM5930_00_TEXT ENUM1630_02_TEXT
#define ENUM5930_01_TEXT ENUM4133_02_TEXT
#define ENUM5930_05_TEXT ENUM4133_03_TEXT
#define ENUM5930_06_TEXT ENUM4133_04_TEXT
#define ENUM5950_00_TEXT ENUM1630_02_TEXT
#define ENUM5950_2_00_TEXT ENUM5890_2_00_TEXT
#define ENUM5950_2_03_TEXT ENUM5920_07_TEXT
#define ENUM5950_2_08_TEXT ENUM5950_06_TEXT
#define ENUM5950_3_02_TEXT ENUM5950_02_TEXT
#define ENUM5950_3_03_TEXT ENUM5950_03_TEXT
#define ENUM5950_3_04_TEXT ENUM5950_04_TEXT
#define ENUM5950_3_05_TEXT ENUM5950_05_TEXT
#define ENUM5950_3_06_TEXT ENUM5950_06_TEXT
#define ENUM5950_3_07_TEXT ENUM5950_07_TEXT
#define ENUM5950_3_08_TEXT ENUM5950_08_TEXT
#define ENUM5950_3_09_TEXT ENUM5950_0d_TEXT
#define ENUM5950_4_00_TEXT ENUM48_00_TEXT
#define ENUM5950_4_03_TEXT ENUM5950_02_TEXT
#define ENUM5950_4_04_TEXT ENUM5950_03_TEXT
#define ENUM5950_4_05_TEXT ENUM5950_04_TEXT
#define ENUM5950_4_07_TEXT ENUM5950_06_TEXT
#define ENUM5950_4_08_TEXT ENUM5950_07_TEXT
#define ENUM5950_4_0c_TEXT ENUM5950_09_TEXT
#define ENUM5950_4_1d_TEXT ENUM2480_00_TEXT
#define ENUM5950_5_02_TEXT ENUM5950_02_TEXT
#define ENUM5950_5_03_TEXT ENUM5950_03_TEXT
#define ENUM5950_5_04_TEXT ENUM5950_04_TEXT
#define ENUM5950_5_05_TEXT ENUM5950_05_TEXT
#define ENUM5950_5_06_TEXT ENUM5950_06_TEXT
#define ENUM5950_5_07_TEXT ENUM5950_07_TEXT
#define ENUM5950_5_08_TEXT ENUM5950_08_TEXT
#define ENUM5950_5_09_TEXT ENUM5950_09_TEXT
#define ENUM5950_5_0a_TEXT ENUM5950_0a_TEXT
#define ENUM5950_5_0b_TEXT ENUM5950_0b_TEXT
#define ENUM5950_5_0c_TEXT ENUM5950_0c_TEXT
#define ENUM5950_5_0e_TEXT ENUM5950_0d_TEXT
#define ENUM5950_7_01_TEXT ENUM5950_2_01_TEXT
#define ENUM5950_7_02_TEXT ENUM5950_2_02_TEXT
#define ENUM5950_7_03_TEXT ENUM5920_07_TEXT
#define ENUM5957_2_00_TEXT ENUM5957_01_TEXT
#define ENUM5957_2_01_TEXT ENUM5957_02_TEXT
#define ENUM5957_2_03_TEXT ENUM5950_6_03_TEXT
#define ENUM5960_3_02_TEXT ENUM5950_6_03_TEXT
#define ENUM5970_00_TEXT ENUM1630_02_TEXT
#define ENUM5973_00_TEXT ENUM5890_2_00_TEXT
#define ENUM5973_01_TEXT ENUM5950_2_01_TEXT
#define ENUM5973_02_TEXT ENUM5950_2_02_TEXT
#define ENUM5973_03_TEXT ENUM5920_07_TEXT
#define ENUM5973_07_TEXT ENUM5950_2_07_TEXT
#define ENUM5973_08_TEXT ENUM5950_06_TEXT
#define ENUM5973_09_TEXT ENUM5950_2_09_TEXT
#define ENUM5978_00_TEXT ENUM5731_00_TEXT
#define ENUM5980_00_TEXT ENUM48_00_TEXT
#define ENUM5980_0f_TEXT ENUM5950_07_TEXT
#define ENUM5980_16_TEXT ENUM5950_02_TEXT
#define ENUM5982_02_TEXT ENUM5950_06_TEXT
#define ENUM5982_03_TEXT ENUM5950_07_TEXT
#define ENUM5988_00_TEXT ENUM48_00_TEXT
#define ENUM5988_01_TEXT ENUM5980_01_TEXT
#define ENUM5988_02_TEXT ENUM5980_02_TEXT
#define ENUM5988_03_TEXT ENUM5980_03_TEXT
#define ENUM5988_04_TEXT ENUM5980_04_TEXT
#define ENUM5988_05_TEXT ENUM5980_05_TEXT
#define ENUM5988_06_TEXT ENUM5980_06_TEXT
#define ENUM5988_07_TEXT ENUM5980_07_TEXT
#define ENUM5988_08_TEXT ENUM5980_08_TEXT
#define ENUM5988_09_TEXT ENUM5980_09_TEXT
#define ENUM5988_0a_TEXT ENUM5980_0a_TEXT
#define ENUM5988_0b_TEXT ENUM5980_0b_TEXT
#define ENUM5988_0c_TEXT ENUM5980_0c_TEXT
#define ENUM5988_0d_TEXT ENUM5950_07_TEXT
#define ENUM6014_00_TEXT ENUM48_00_TEXT
#define ENUM6014_01_TEXT ENUM_CAT_0b_TEXT
#define ENUM6014_05_TEXT ENUM_CAT_1d_TEXT
#define ENUM6020_00_TEXT ENUM5890_2_00_TEXT
#define ENUM6020_02_TEXT ENUM_CAT_0d_TEXT
#define ENUM6020_03_TEXT ENUM6014_02_TEXT
#define ENUM6020_05_TEXT ENUM6014_03_TEXT
#define ENUM6020_06_TEXT ENUM6014_04_TEXT
#define ENUM6020_07_TEXT ENUM_CAT_1d_TEXT
#define ENUM6020_08_TEXT ENUM6014_06_TEXT
#define ENUM6030_00_TEXT ENUM1630_02_TEXT
#define ENUM6030_01_TEXT ENUM5890_21_TEXT
#define ENUM6030_02_TEXT ENUM5895_02_TEXT
#define ENUM6030_03_TEXT ENUM5895_03_TEXT
#define ENUM6030_04_TEXT ENUM5895_04_TEXT
#define ENUM6030_05_TEXT ENUM5895_05_TEXT
#define ENUM6030_08_TEXT ENUM5895_08_TEXT
#define ENUM6030_09_TEXT ENUM5890_01_TEXT
#define ENUM6030_0a_TEXT ENUM5890_02_TEXT
#define ENUM6030_0b_TEXT ENUM5895_0b_TEXT
#define ENUM6030_0c_TEXT ENUM5890_03_TEXT
#define ENUM6030_0d_TEXT ENUM5890_04_TEXT
#define ENUM6030_0e_TEXT ENUM5890_05_TEXT
#define ENUM6030_0f_TEXT ENUM5890_06_TEXT
#define ENUM6030_10_TEXT ENUM5890_07_TEXT
#define ENUM6030_11_TEXT ENUM5895_11_TEXT
#define ENUM6030_12_TEXT ENUM5895_12_TEXT
#define ENUM6030_13_TEXT ENUM5895_13_TEXT
#define ENUM6030_14_TEXT ENUM5890_0b_TEXT
#define ENUM6030_15_TEXT ENUM5890_0c_TEXT
#define ENUM6030_16_TEXT ENUM5890_0d_TEXT
#define ENUM6030_17_TEXT ENUM5890_0e_TEXT
#define ENUM6030_18_TEXT ENUM5890_0f_TEXT
#define ENUM6030_19_TEXT ENUM5890_10_TEXT
#define ENUM6030_1a_TEXT ENUM5890_11_TEXT
#define ENUM6030_1b_TEXT ENUM5890_12_TEXT
#define ENUM6030_1c_TEXT ENUM5890_13_TEXT
#define ENUM6030_1e_TEXT ENUM5890_15_TEXT
#define ENUM6030_1f_TEXT ENUM5890_16_TEXT
#define ENUM6030_20_TEXT ENUM5890_17_TEXT
#define ENUM6030_21_TEXT ENUM5895_20_TEXT
#define ENUM6030_22_TEXT ENUM5895_08_TEXT
#define ENUM6030_23_TEXT ENUM5895_22_TEXT
#define ENUM6030_25_TEXT ENUM5895_24_TEXT
#define ENUM6030_26_TEXT ENUM5895_25_TEXT
#define ENUM6030_27_TEXT ENUM5890_19_TEXT
#define ENUM6030_28_TEXT ENUM5890_1a_TEXT
#define ENUM6030_29_TEXT ENUM5890_1b_TEXT
#define ENUM6030_2a_TEXT ENUM5890_1c_TEXT
#define ENUM6030_2b_TEXT ENUM5890_1d_TEXT
#define ENUM6030_2c_TEXT ENUM5895_2b_TEXT
#define ENUM6030_2d_TEXT ENUM5895_2c_TEXT
#define ENUM6030_2e_TEXT ENUM5895_2d_TEXT
#define ENUM6040_00_TEXT ENUM1630_02_TEXT
#define ENUM6040_01_TEXT ENUM4133_02_TEXT
#define ENUM6040_02_TEXT ENUM5930_02_TEXT
#define ENUM6040_04_TEXT ENUM5930_04_TEXT
#define ENUM6040_05_TEXT ENUM4133_03_TEXT
#define ENUM6040_06_TEXT ENUM4133_04_TEXT
#define ENUM6040_07_TEXT ENUM5930_07_TEXT
#define ENUM6040_08_TEXT ENUM5930_08_TEXT
#define ENUM6040_09_TEXT ENUM5930_09_TEXT
#define ENUM6040_0a_TEXT ENUM5930_0a_TEXT
#define ENUM6040_0b_TEXT ENUM5930_0b_TEXT
#define ENUM6040_0c_TEXT ENUM5930_0c_TEXT
#define ENUM6040_0d_TEXT ENUM5930_0d_TEXT
#define ENUM6040_0e_TEXT ENUM5930_0e_TEXT
#define ENUM6040_0f_TEXT ENUM5930_0f_TEXT
#define ENUM6040_10_TEXT ENUM5930_10_TEXT
#define ENUM6040_11_TEXT ENUM5930_11_TEXT
#define ENUM6070_00_TEXT ENUM2320_02_TEXT
#define ENUM6085_00_TEXT ENUM48_00_TEXT
#define ENUM6085_01_TEXT ENUM5890_05_TEXT
#define ENUM6085_04_TEXT ENUM5890_21_TEXT
#define ENUM6085_07_TEXT ENUM5890_03_TEXT
#define ENUM6131_00_TEXT ENUM780_00_TEXT
#define ENUM6131_01_TEXT ENUM2205_01_TEXT
#define ENUM6131_02_TEXT ENUM1600_01_TEXT
#define ENUM6136_03_TEXT ENUM_CAT_07_TEXT
#define ENUM6148_00_TEXT ENUM48_00_TEXT
#define ENUM6272_00_TEXT ENUM1630_02_TEXT
#define ENUM6272_06_TEXT ENUM4133_04_TEXT
#define ENUM6272_07_TEXT ENUM5930_07_TEXT
#define ENUM6272_08_TEXT ENUM5930_08_TEXT
#define ENUM6272_09_TEXT ENUM5930_09_TEXT
#define ENUM6272_0B_TEXT ENUM5930_0b_TEXT
#define ENUM6272_0C_TEXT ENUM5930_0c_TEXT
#define ENUM6272_0D_TEXT ENUM5930_0d_TEXT
#define ENUM6272_0E_TEXT ENUM5930_0e_TEXT
#define ENUM6272_18_TEXT ENUM4133_01_TEXT
#define ENUM6375_00_TEXT ENUM1630_02_TEXT
#define ENUM6375_02_TEXT ENUM5895_04_TEXT
#define ENUM6375_03_TEXT ENUM5895_05_TEXT
#define ENUM6375_04_TEXT ENUM5895_06_TEXT
#define ENUM6375_05_TEXT ENUM5895_07_TEXT
#define ENUM6375_06_TEXT ENUM5895_08_TEXT
#define ENUM6375_07_TEXT ENUM5890_0d_TEXT
#define ENUM6375_08_TEXT ENUM5890_19_TEXT
#define ENUM6375_09_TEXT ENUM5890_0e_TEXT
#define ENUM6375_0a_TEXT ENUM5890_02_TEXT
#define ENUM6375_0b_TEXT ENUM5890_01_TEXT
#define ENUM6375_0c_TEXT ENUM5890_1a_TEXT
#define ENUM6375_0d_TEXT ENUM5890_1c_TEXT
#define ENUM6375_0e_TEXT ENUM5890_1b_TEXT
#define ENUM6375_0f_TEXT ENUM5890_03_TEXT
#define ENUM6375_10_TEXT ENUM5890_15_TEXT
#define ENUM6375_12_TEXT ENUM5890_13_TEXT
#define ENUM6375_13_TEXT ENUM5890_14_TEXT
#define ENUM6375_14_TEXT ENUM5895_0b_TEXT
#define ENUM6375_18_TEXT ENUM6085_06_TEXT
#define ENUM6375_19_TEXT ENUM5895_11_TEXT
#define ENUM6375_1a_TEXT ENUM5895_12_TEXT
#define ENUM6375_1d_TEXT ENUM5895_25_TEXT
#define ENUM6375_1e_TEXT ENUM5890_1d_TEXT
#define ENUM6375_1f_TEXT ENUM5895_2b_TEXT
#define ENUM6375_20_TEXT ENUM5890_07_TEXT
#define ENUM6375_21_TEXT ENUM5890_10_TEXT
#define ENUM6375_22_TEXT ENUM5890_21_TEXT
#define ENUM6375_23_TEXT ENUM5895_02_TEXT
#define ENUM6375_25_TEXT ENUM5895_24_TEXT
#define ENUM6375_26_TEXT ENUM5895_2c_TEXT
#define ENUM6375_29_TEXT ENUM6085_05_TEXT
#define ENUM6375_2b_TEXT ENUM6375_28_TEXT
#define ENUM6375_2c_TEXT ENUM6375_28_TEXT
#define ENUM6375_32_TEXT ENUM5890_0f_TEXT
#define ENUM6375_33_TEXT ENUM5890_17_TEXT
#define ENUM6420_00_TEXT ENUM5700_05_TEXT
#define ENUM6420_06_TEXT ENUM5700_05_TEXT
#define ENUM6420_07_TEXT ENUM5700_05_TEXT
#define ENUM6420_08_TEXT ENUM5700_05_TEXT
#define ENUM6420_09_TEXT ENUM5700_05_TEXT
#define ENUM6420_0a_TEXT ENUM5700_05_TEXT
#define ENUM6420_0c_TEXT ENUM5700_05_TEXT
#define ENUM6420_0d_TEXT ENUM5700_05_TEXT
#define ENUM6604_00_TEXT ENUM780_00_TEXT
#define ENUM6604_01_TEXT ENUM5040_02_TEXT
#define ENUM6620_ff_TEXT ENUM6620_01_TEXT
#define ENUM6621_ff_TEXT ENUM6621_01_TEXT
#define ENUM6623_00_TEXT ENUM6621_00_TEXT
#define ENUM6623_01_TEXT ENUM6621_01_TEXT
#define ENUM6624_00_TEXT ENUM6621_00_TEXT
#define ENUM6624_01_TEXT ENUM6620_00_TEXT
#define ENUM6630_01_TEXT ENUM861_02_TEXT
#define ENUM6630_02_TEXT ENUM5040_02_TEXT
#define ENUM6631_00_TEXT ENUM780_00_TEXT
#define ENUM6631_01_TEXT ENUM2205_01_TEXT
#define ENUM6631_02_TEXT ENUM1600_01_TEXT
#define ENUM6670_00_TEXT ENUM2320_02_TEXT
#define ENUM6670_01_TEXT ENUM6070_01_TEXT
#define ENUM6670_02_TEXT ENUM6070_02_TEXT
#define ENUM6706_00_TEXT ENUM2206_01_TEXT
#define ENUM6706_01_TEXT ENUM2480_00_TEXT
#define ENUM6706_63_TEXT ENUM2480_ff_TEXT
#define ENUM6706_0a_TEXT ENUM861_01_TEXT
#define ENUM7142_01_TEXT ENUM850_05_TEXT
#define ENUM7142_02_TEXT ENUM5040_02_TEXT
#define ENUM7147_00_TEXT ENUM48_00_TEXT
#define ENUM7376_00_TEXT ENUM1630_02_TEXT
#define ENUM7376_01_TEXT ENUM5890_01_TEXT
#define ENUM7376_02_TEXT ENUM5890_02_TEXT
#define ENUM7376_03_TEXT ENUM5890_03_TEXT
#define ENUM7376_05_TEXT ENUM5890_05_TEXT
#define ENUM7376_06_TEXT ENUM5890_06_TEXT
#define ENUM7376_07_TEXT ENUM5890_07_TEXT
#define ENUM7376_08_TEXT ENUM5890_08_TEXT
#define ENUM7376_09_TEXT ENUM5890_09_TEXT
#define ENUM7376_0a_TEXT ENUM5890_0a_TEXT
#define ENUM7376_0b_TEXT ENUM5890_0b_TEXT
#define ENUM7376_0c_TEXT ENUM5890_0c_TEXT
#define ENUM7376_0d_TEXT ENUM5890_0d_TEXT
#define ENUM7376_0e_TEXT ENUM5890_0e_TEXT
#define ENUM7376_0f_TEXT ENUM5890_0f_TEXT
#define ENUM7376_10_TEXT ENUM5890_10_TEXT
#define ENUM7376_11_TEXT ENUM5890_11_TEXT
#define ENUM7376_12_TEXT ENUM5890_12_TEXT
#define ENUM7376_13_TEXT ENUM5890_13_TEXT
#define ENUM7376_14_TEXT ENUM5890_14_TEXT
#define ENUM7376_15_TEXT ENUM5890_15_TEXT
#define ENUM7376_16_TEXT ENUM5890_16_TEXT
#define ENUM7376_17_TEXT ENUM5890_17_TEXT
#define ENUM7376_19_TEXT ENUM5890_19_TEXT
#define ENUM7376_1a_TEXT ENUM5890_1a_TEXT
#define ENUM7376_1b_TEXT ENUM5890_1b_TEXT
#define ENUM7376_1c_TEXT ENUM5890_1c_TEXT
#define ENUM7376_1d_TEXT ENUM5890_1d_TEXT
#define ENUM7376_21_TEXT ENUM5890_21_TEXT
#define ENUM7376_28_TEXT ENUM5890_28_TEXT
#define ENUM7376_29_TEXT ENUM5890_29_TEXT
#define ENUM7700_02_TEXT ENUM6040_03_TEXT
#define ENUM7700_03_TEXT ENUM6040_03_TEXT
#define ENUM7700_04_TEXT ENUM6085_02_TEXT
#define ENUM7999_00_TEXT ENUM48_00_TEXT
#define ENUM8000_00_TEXT ENUM6040_03_TEXT
#define ENUM8000_18_TEXT ENUM780_00_TEXT
#define ENUM8003_00_TEXT ENUM6040_03_TEXT
#define ENUM8003_03_TEXT ENUM8000_03_TEXT
#define ENUM8003_04_TEXT ENUM8000_04_TEXT
#define ENUM8003_11_TEXT ENUM8000_11_TEXT
#define ENUM8003_18_TEXT ENUM8000_17_TEXT
#define ENUM8003_19_TEXT ENUM780_00_TEXT
#define ENUM8004_00_TEXT ENUM6040_03_TEXT
#define ENUM8005_00_TEXT ENUM6040_03_TEXT
#define ENUM8005_03_TEXT ENUM8000_03_TEXT
#define ENUM8005_04_TEXT ENUM8000_04_TEXT
#define ENUM8005_0a_TEXT ENUM2706_00_TEXT
#define ENUM8005_0f_TEXT ENUM2920_01_TEXT
#define ENUM8005_11_TEXT ENUM8000_11_TEXT
#define ENUM8005_12_TEXT ENUM130_01_TEXT
#define ENUM8005_13_TEXT ENUM2920_01_TEXT
#define ENUM8005_17_TEXT ENUM8000_16_TEXT
#define ENUM8005_18_TEXT ENUM8000_17_TEXT
#define ENUM8005_19_TEXT ENUM780_00_TEXT
#define ENUM8006_00_TEXT ENUM6040_03_TEXT
#define ENUM8006_02_TEXT ENUM8005_02_TEXT
#define ENUM8006_0A_TEXT ENUM2706_00_TEXT
#define ENUM8006_11_TEXT ENUM8000_11_TEXT
#define ENUM8006_18_TEXT ENUM8000_17_TEXT
#define ENUM8006_19_TEXT ENUM780_00_TEXT
#define ENUM8006_89_TEXT ENUM861_01_TEXT
#define ENUM8006_b0_TEXT ENUM8005_b0_TEXT
#define ENUM8006_c6_TEXT ENUM8005_c6_TEXT
#define ENUM8007_00_TEXT ENUM6040_03_TEXT
#define ENUM8007_04_TEXT ENUM8000_04_TEXT
#define ENUM8007_02_TEXT ENUM8005_02_TEXT
#define ENUM8007_35_TEXT ENUM8003_35_TEXT
#define ENUM8007_38_TEXT ENUM8000_38_TEXT
#define ENUM8007_3b_TEXT ENUM8005_3b_TEXT
#define ENUM8008_00_TEXT ENUM6040_03_TEXT
#define ENUM8008_02_TEXT ENUM8005_02_TEXT
#define ENUM8008_04_TEXT ENUM8000_04_TEXT
#define ENUM8008_08_TEXT ENUM8005_08_TEXT
#define ENUM8008_09_TEXT ENUM8005_09_TEXT
#define ENUM8008_0a_TEXT ENUM2706_00_TEXT
#define ENUM8008_0b_TEXT ENUM8005_0b_TEXT
#define ENUM8008_0c_TEXT ENUM8005_0c_TEXT
#define ENUM8008_11_TEXT ENUM8000_11_TEXT
#define ENUM8008_12_TEXT ENUM130_01_TEXT
#define ENUM8008_13_TEXT ENUM2920_01_TEXT
#define ENUM8008_14_TEXT ENUM8005_14_TEXT
#define ENUM8008_15_TEXT ENUM8005_15_TEXT
#define ENUM8008_16_TEXT ENUM8005_16_TEXT
#define ENUM8008_17_TEXT ENUM8000_16_TEXT
#define ENUM8008_18_TEXT ENUM8000_17_TEXT
#define ENUM8008_19_TEXT ENUM780_00_TEXT
#define ENUM8008_38_TEXT ENUM8000_38_TEXT
#define ENUM8008_3a_TEXT ENUM8007_3a_TEXT
#define ENUM8008_3b_TEXT ENUM8005_3b_TEXT
#define ENUM8008_a6_TEXT ENUM8005_a6_TEXT
#define ENUM8008_a7_TEXT ENUM8005_a7_TEXT
#define ENUM8008_a8_TEXT ENUM8005_a8_TEXT
#define ENUM8008_a9_TEXT ENUM8005_a9_TEXT
#define ENUM8008_aa_TEXT ENUM8005_aa_TEXT
#define ENUM8008_ab_TEXT ENUM8005_ab_TEXT
#define ENUM8009_2_00_TEXT ENUM6040_03_TEXT
#define ENUM8009_2_01_TEXT ENUM2480_ff_TEXT
#define ENUM8009_2_02_TEXT ENUM2480_00_TEXT
#define ENUM8009_2_04_TEXT ENUM130_01_TEXT
#define ENUM8009_2_09_TEXT ENUM8009_09_TEXT
#define ENUM8009_2_12_TEXT ENUM130_01_TEXT
#define ENUM8009_2_D8_TEXT ENUM2206_01_TEXT
#define ENUM8009_00_TEXT ENUM8009_2_00_TEXT
#define ENUM8009_01_TEXT ENUM2480_ff_TEXT
#define ENUM8009_02_TEXT ENUM2480_00_TEXT
#define ENUM8009_09_TEXT ENUM6706_16_TEXT 
#define ENUM8009_12_TEXT ENUM130_01_TEXT
#define ENUM8009_D6_TEXT ENUM8009_2_D6_TEXT
#define ENUM8009_DA_TEXT ENUM8009_2_DA_TEXT
#define ENUM8009_D7_TEXT ENUM8009_2_D7_TEXT
#define ENUM8009_D8_TEXT ENUM2206_01_TEXT
#define ENUM8009_D9_TEXT ENUM8009_2_D9_TEXT
#define ENUM8009_DB_TEXT ENUM8009_2_DB_TEXT
#define ENUM8010_00_TEXT ENUM6040_03_TEXT
#define ENUM8010_18_TEXT ENUM8000_17_TEXT
#define ENUM8010_35_TEXT ENUM8003_35_TEXT
#define ENUM8010_42_TEXT ENUM8003_42_TEXT
#define ENUM8010_43_TEXT ENUM8003_43_TEXT
#define ENUM8010_45_TEXT ENUM8003_45_TEXT
#define ENUM8010_46_TEXT ENUM8003_46_TEXT
#define ENUM8010_47_TEXT ENUM8003_47_TEXT
#define ENUM8010_4b_TEXT ENUM8003_4b_TEXT
#define ENUM8010_4d_TEXT ENUM8003_4d_TEXT
#define ENUM8010_51_TEXT ENUM8003_51_TEXT
#define ENUM8010_68_TEXT ENUM8000_68_TEXT
#define ENUM8011_00_TEXT ENUM6040_03_TEXT
#define ENUM8011_02_TEXT ENUM8005_02_TEXT
#define ENUM8011_04_TEXT ENUM8000_04_TEXT
#define ENUM8011_4c_TEXT ENUM8010_4c_TEXT
#define ENUM8011_6a_TEXT ENUM8000_6a_TEXT
#define ENUM8011_6e_TEXT ENUM8000_6e_TEXT
#define ENUM8011_89_TEXT ENUM861_01_TEXT
#define ENUM8022_00_TEXT ENUM6040_03_TEXT
#define ENUM8100_00_TEXT ENUM130_00_TEXT
#define ENUM8100_02_TEXT ENUM8000_04_TEXT
#define ENUM8100_04_TEXT ENUM8005_07_TEXT
#define ENUM8100_08_TEXT ENUM2920_01_TEXT
#define ENUM8304_00_TEXT ENUM780_00_TEXT
#define ENUM8304_01_TEXT ENUM1600_01_TEXT
#define ENUM8304_ff_TEXT ENUM1600_01_TEXT
#define ENUM8304_01_00_TEXT ENUM5890_2_00_TEXT
#define ENUM8749_01_TEXT ENUM2320_01_TEXT
#define ENUM15010_00_TEXT ENUM5040_02_TEXT
#define ENUM15010_01_TEXT ENUM850_05_TEXT
#define ENUM15010_02_TEXT ENUM780_00_TEXT
#define ENUM_ERROR_4d_TEXT ENUM_ERROR_49_TEXT
#define ENUM_ERROR_01_51_TEXT ENUM_ERROR_01_4a_TEXT
#define ENUM_ERROR_01_81_TEXT ENUM8006_f6_TEXT
#define ENUM_SWCODE_6e_TEXT ENUM_ERROR_a1_TEXT
#define ENUM_SWCODE_01_03_TEXT ENUM_ERROR_99_TEXT
#define ENUM_SWCODE_02_09_TEXT ENUM_ERROR_8c_TEXT
#define ENUM_SWCODE_02_5a_TEXT ENUM_ERROR_b8_TEXT

#define WEEKDAY_MON_TEXT STR500_TEXT
#define WEEKDAY_TUE_TEXT STR501_TEXT
#define WEEKDAY_WED_TEXT STR502_TEXT
#define WEEKDAY_THU_TEXT STR503_TEXT
#define WEEKDAY_FRI_TEXT STR504_TEXT
#define WEEKDAY_SAT_TEXT STR505_TEXT
#define WEEKDAY_SUN_TEXT STR506_TEXT

/* ENUM tables */
const char ENUM20[] PROGMEM_LATEST = { // numerical values are hypothetical
"\x01 " "?" ENUM20_01_TEXT "\0"
"\x02 " "?" ENUM20_02_TEXT "\0"
"\x03 " "?" ENUM20_03_TEXT "\0"
"\x04 " "?" ENUM20_04_TEXT "\0"
"\x05 " "?" ENUM20_05_TEXT "\0"
"\x06 " "?" ENUM20_06_TEXT "\0"
"\x07 " "?" ENUM20_07_TEXT "\0"
"\x08 " "?" ENUM20_08_TEXT
};
// numerical values are hypothetical
const char ENUM22[] PROGMEM_LATEST = {
"\x01 " ENUM22_01_TEXT "\0"
"\x02 " ENUM22_02_TEXT
};
const char ENUM23[] PROGMEM_LATEST = {
"\x00 " "?" ENUM23_00_TEXT "\0"
"\x01 " "?" ENUM23_01_TEXT
};
const char ENUM28[] PROGMEM_LATEST = {
"\x01 " ENUM28_01_TEXT "\0"
"\x02 " ENUM28_02_TEXT
};
const char ENUM29[] PROGMEM_LATEST = {
"\x01 " ENUM29_01_TEXT "\0"
"\x02 " ENUM29_02_TEXT
};
const char ENUM40[] PROGMEM_LATEST = {
"\x00 " "?" ENUM40_00_TEXT "\0"
"\x01 " "?" ENUM40_01_TEXT "\0"
"\x02 " "?" ENUM40_02_TEXT "\0"
"\x03 " "?" ENUM40_03_TEXT "\0"
"\x04 " "?" ENUM40_04_TEXT "\0"
"\x05 " ENUM40_05_TEXT
};
const char ENUM42[] PROGMEM_LATEST = {	// numerical values are hypothetical
"\x00 " "?" ENUM42_00_TEXT "\0"
"\x01 " "?" ENUM42_01_TEXT "\0"
"\x02 " "?" ENUM42_02_TEXT "\0"
"\x03 " "?" ENUM42_03_TEXT
};
const char ENUM44[] PROGMEM_LATEST = {
"\x01 " ENUM44_01_TEXT "\0"
"\x02 " ENUM44_02_TEXT
};
#define ENUM46 ENUM44
const char ENUM47[] PROGMEM_LATEST = {  // NovoCondens WOB20C / WOB25C
"\x01 " "?" ENUM47_01_TEXT "\0"
"\x02 " "?" ENUM47_02_TEXT
};
// Nur am Raumgerät sichtbar, numerical values are hypothetical
const char ENUM48[] PROGMEM_LATEST = {
"\x00 " "?" ENUM48_00_TEXT "\0"
"\x01 " "?" ENUM48_01_TEXT "\0"
"\x02 " "?" ENUM48_02_TEXT "\0"
"\x03 " "?" ENUM48_03_TEXT
};

const char ENUM130[] PROGMEM_LATEST = {
"\x00 " ENUM130_00_TEXT "\0"
"\x01 " ENUM130_01_TEXT "\0"
"\x02 " "?" ENUM130_02_TEXT "\0"
"\x03 " "?" ENUM130_03_TEXT
};
#define ENUM131 ENUM130
#define ENUM132 ENUM130
#define ENUM133 ENUM130
#define ENUM134 ENUM130
#define ENUM135 ENUM130
#define ENUM136 ENUM130
#define ENUM137 ENUM130
#define ENUM138 ENUM130

/*
const char ENUM648[] PROGMEM_LATEST = {
"\x00 " ENUM648_00_TEXT "\0"
"\x01 " ENUM648_01_TEXT
};
#define ENUM658 ENUM648
#define ENUM668 ENUM648
*/

const char ENUM648[] PROGMEM_LATEST = {
"\x00 " ENUM648_00_TEXT "\0"
"\x01 " ENUM648_01_TEXT
};
#define ENUM665 ENUM648
#define ENUM682 ENUM648

const char ENUM700[] PROGMEM_LATEST = {
"\x00 " ENUM700_00_TEXT "\0"
"\x01 " ENUM700_01_TEXT "\0"
"\x02 " ENUM700_02_TEXT "\0"
"\x03 " ENUM700_03_TEXT
};

// Parameters 702 and 703 are virtual Weishaupt parameters based on one and the same command ID, using new data type VT_CUSTOM_ENUM

const char ENUM702[] PROGMEM_LATEST = {
"\x00\x00 " ENUM702_00_TEXT "\0"
"\x00\x01 " ENUM702_01_TEXT "\0"
"\x00\x02 " ENUM702_02_TEXT "\0"
"\x00\x03 " ENUM702_03_TEXT "\0"
"\x00\x04 " ENUM702_04_TEXT "\0"
"\x00\x05 " ENUM702_05_TEXT "\0"
"\x00\x06 " ENUM702_06_TEXT
};

const char ENUM703[] PROGMEM_LATEST = {
"\x01\x00 " ENUM703_00_TEXT "\0"
"\x01\x01 " ENUM703_01_TEXT
};

const char ENUM780[] PROGMEM_LATEST = {
"\x00 " ENUM780_00_TEXT "\0"
"\x01 " ENUM780_01_TEXT "\0"
"\x02 " ENUM780_02_TEXT
};
const char ENUM832[] PROGMEM_LATEST = {
"\x00 " ENUM832_00_TEXT "\0"
"\x01 " ENUM832_01_TEXT
};
const char ENUM850[] PROGMEM_LATEST = {
"\x00 " ENUM850_00_TEXT "\0"
"\x01 " ENUM850_01_TEXT "\0"
"\x02 " ENUM850_02_TEXT "\0"
"\x03 " ENUM850_03_TEXT "\0"
"\x04 " ENUM850_04_TEXT "\0"
"\x05 " ENUM850_05_TEXT
};
const char ENUM861[] PROGMEM_LATEST = {
"\x00 " ENUM861_00_TEXT "\0"
"\x01 " ENUM861_01_TEXT "\0"
"\x02 " ENUM861_02_TEXT
};
const char ENUM880[] PROGMEM_LATEST = {
"\x00 " ENUM880_00_TEXT "\0"
"\x01 " ENUM880_01_TEXT "\0"
"\x02 " ENUM880_02_TEXT
};
const char ENUM898[] PROGMEM_LATEST = {
"\x00 " ENUM898_00_TEXT "\0"
"\x01 " ENUM898_01_TEXT "\0"
"\x02 " ENUM898_02_TEXT
};

const char ENUM900[] PROGMEM_LATEST = {
"\x00 " ENUM900_00_TEXT "\0"
"\x01 " ENUM900_01_TEXT "\0"
"\x02 " ENUM900_02_TEXT "\0"
"\x03 " ENUM900_03_TEXT "\0"
"\x04 " ENUM900_04_TEXT
};
const char ENUM900_2[] PROGMEM_LATEST = {
"\x00 " ENUM900_2_00_TEXT "\0"
"\x01 " ENUM900_2_01_TEXT "\0"
"\x03 " ENUM900_2_03_TEXT "\0"
"\x04 " ENUM900_2_04_TEXT
};

const char ENUM1000[] PROGMEM_LATEST = {
"\x00 " ENUM1000_00_TEXT "\0"
"\x01 " ENUM1000_01_TEXT "\0"
"\x02 " ENUM1000_02_TEXT "\0"
"\x03 " ENUM1000_03_TEXT
};

#define ENUM1080 ENUM780         // Schnellabsenkung HK2
#define ENUM1132 ENUM832         // Antrieb Typ HK2
#define ENUM1150 ENUM850         // Estrichfunktion HK2
#define ENUM1161 ENUM861         // Übertemperaturabnahme HK2
#define ENUM1200 ENUM900         // Betriebsartumschaltung HK2
#define ENUM1200_2 ENUM900_2         // Betriebsartumschaltung HK2

#define ENUM1180 ENUM880

const char ENUM1300[] PROGMEM_LATEST = {
"\x00 " ENUM1300_00_TEXT "\0"
"\x01 " ENUM1300_01_TEXT "\0"
"\x02 " ENUM1300_02_TEXT "\0"
"\x03 " ENUM1300_03_TEXT
};
#define ENUM1350 ENUM850
#define ENUM1380 ENUM780
#define ENUM1450 ENUM850

#define ENUM1461 ENUM861         // Uebertemperaturabnahme HK P/3
#define ENUM1500 ENUM900         // Betriebsartumschaltung HK P/3
#define ENUM1500_2 ENUM900_2         // Betriebsartumschaltung HK P/3

const char ENUM1600[] PROGMEM_LATEST = {
"\x00 " ENUM1600_00_TEXT "\0"
"\x01 " ENUM1600_01_TEXT "\0"
"\x02 " ENUM1600_02_TEXT
};

const char ENUM1602[] PROGMEM_LATEST = {
"\x00\x02 " ENUM1602_00_02_TEXT "\0"
"\x02\x02 " ENUM1602_02_02_TEXT "\0"
"\x00\x04 " ENUM1602_00_04_TEXT "\0"
"\x04\x04 " ENUM1602_04_04_TEXT "\0"
"\x00\x08 " ENUM1602_00_08_TEXT "\0"
"\x08\x08 " ENUM1602_08_08_TEXT
};

const char ENUM1620[] PROGMEM_LATEST = {
"\x00 " ENUM1620_00_TEXT "\0"
"\x01 " ENUM1620_01_TEXT "\0"
"\x02 " ENUM1620_02_TEXT
};
const char ENUM1620_2[] PROGMEM_LATEST = {
"\x00 " ENUM1620_2_00_TEXT "\0"
"\x01 " ENUM1620_2_01_TEXT "\0"
"\x04 " ENUM1620_2_04_TEXT
};
const char ENUM1630[] PROGMEM_LATEST = {
"\x00 " ENUM1630_00_TEXT "\0"
"\x01 " ENUM1630_01_TEXT "\0"
"\x02 " ENUM1630_02_TEXT "\0"
"\x03 " ENUM1630_03_TEXT "\0"
"\x04 " ENUM1630_04_TEXT
};
const char ENUM1640[] PROGMEM_LATEST = {
"\x00 " ENUM1640_00_TEXT "\0"
"\x01 " ENUM1640_01_TEXT "\0"
"\x02 " ENUM1640_02_TEXT
};
const char ENUM1660[] PROGMEM_LATEST = {
"\x01 " ENUM1660_01_TEXT "\0"
"\x02 " ENUM1660_02_TEXT "\0"
"\x03 " ENUM1660_03_TEXT "\0"
"\x04 " ENUM1660_04_TEXT
};
const char ENUM1680[] PROGMEM_LATEST = {
"\x00 " ENUM1680_00_TEXT "\0"
"\x01 " ENUM1680_01_TEXT "\0"
"\x02 " ENUM1680_02_TEXT
};

// Vorregler/Zubringerpumpe

const char ENUM2132[] PROGMEM_LATEST = {  // ENUM values hypothetical
"\x00 " ENUM2132_00_TEXT "\0"
"\x01 " ENUM2132_01_TEXT
};

const char ENUM2150[] PROGMEM_LATEST = {  // ENUM values hypothetical
"\x00 " ENUM2150_00_TEXT "\0"
"\x01 " ENUM2150_01_TEXT
};

// Kessel
const char ENUM2200[] PROGMEM_LATEST = {
"\x00 " ENUM2200_00_TEXT "\0"
"\x01 " ENUM2200_01_TEXT "\0"
"\x02 " ENUM2200_02_TEXT
};
const char ENUM2205[] PROGMEM_LATEST = {
"\x00 " ENUM2205_00_TEXT "\0"
"\x01 " ENUM2205_01_TEXT "\0"
"\x02 " ENUM2205_02_TEXT
};
const char ENUM2206[] PROGMEM_LATEST = {
"\x00 " ENUM2206_00_TEXT "\0"
"\x01 " ENUM2206_01_TEXT
};
const char ENUM2291[] PROGMEM_LATEST = {
"\x00 " ENUM2291_00_TEXT "\0"
"\x01 " ENUM2291_01_TEXT
};

const char ENUM2305[] PROGMEM_LATEST = {
"\x00 " ENUM2305_00_TEXT "\0"
"\x01 " ENUM2305_01_TEXT
};

const char ENUM2305_2[] PROGMEM_LATEST = {
"\x01 " ENUM2305_2_01_TEXT "\0"
"\x02 " ENUM2305_2_02_TEXT
};

const char ENUM2320[] PROGMEM_LATEST = {
"\x00 " ENUM2320_00_TEXT "\0"
"\x01 " ENUM2320_01_TEXT "\0"
"\x02 " ENUM2320_02_TEXT "\0"
"\x03 " ENUM2320_03_TEXT "\0"
"\x04 " ENUM2320_04_TEXT
};

const char ENUM2450[] PROGMEM_LATEST = {
"\x00 " ENUM2450_00_TEXT "\0"
"\x01 " ENUM2450_01_TEXT "\0"
"\x02 " ENUM2450_02_TEXT "\0"
"\x03 " ENUM2450_03_TEXT
};

const char ENUM2480[] PROGMEM_LATEST = {
"\x00 " ENUM2480_00_TEXT "\0"
"\xff " ENUM2480_ff_TEXT
};

const char ENUM2500[] PROGMEM_LATEST = {
"\x00 " ENUM2500_00_TEXT "\0"
"\x01 " ENUM2500_01_TEXT
};

// Sitherm Pro
const char ENUM2706[] PROGMEM_LATEST = {
"\x00 " ENUM2706_00_TEXT "\0"
"\x01 " ENUM2706_01_TEXT "\0"
"\x02 " ENUM2706_02_TEXT "\0"
"\x03 " ENUM2706_03_TEXT "\0"                     // verifiziert an WMS (LP)
"\x04 " ENUM2706_04_TEXT "\0"
"\x05 " ENUM2706_05_TEXT "\0"
"\x06 " ENUM2706_06_TEXT "\0"
"\x07 " ENUM2706_07_TEXT "\0"                  // verifiziert an WMS (LP)
"\x08 " ENUM2706_08_TEXT "\0"              // verifiziert an WMS (LP)
"\x09 " ENUM2706_09_TEXT "\0"                      // verifiziert an WMS (LP)
"\x0a " ENUM2706_0a_TEXT "\0"
"\x0b " ENUM2706_0b_TEXT "\0"
"\x0c " ENUM2706_0c_TEXT "\0"
"\x0d " ENUM2706_0d_TEXT "\0"
"\x12 " ENUM2706_12_TEXT        // verifiziert an WMS (LP)
}; // todo Hinweis: x03, x07, x08, x12 sind definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2721[] PROGMEM_LATEST = {
"\x01 " ENUM2721_01_TEXT "\0"
"\x02 " ENUM2721_02_TEXT
}; // todo Hinweis: x01 Erdgas ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2727[] PROGMEM_LATEST = {
"\x01 " ENUM2727_01_TEXT "\0"
"\x02 " ENUM2727_02_TEXT "\0"
"\x03 " ENUM2727_03_TEXT
};

const char ENUM2740[] PROGMEM_LATEST = {
"\x00 " ENUM2740_00_TEXT "\0"
"\x01 " ENUM2740_01_TEXT "\0"
"\x02 " ENUM2740_02_TEXT "\0"
"\x03 " ENUM2740_03_TEXT "\0"
"\x04 " ENUM2740_04_TEXT "\0"
"\x05 " ENUM2740_05_TEXT "\0"
"\x06 " ENUM2740_06_TEXT "\0"
"\x07 " ENUM2740_07_TEXT "\0"
"\x08 " ENUM2740_08_TEXT "\0"
"\x09 " ENUM2740_09_TEXT
}; // todo Hinweis: x00 Nein ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2749[] PROGMEM_LATEST = {
"\x00 " ENUM2749_00_TEXT "\0"
"\x01 " ENUM2749_01_TEXT "\0"
"\x02 " ENUM2749_02_TEXT
}; // todo Hinweis: x00 Nein ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM2801[] PROGMEM_LATEST = {
"\x01 " ENUM2801_01_TEXT "\0"
"\x02 " ENUM2801_02_TEXT "\0"
"\x03 " ENUM2801_03_TEXT
};

const char ENUM2880[] PROGMEM_LATEST = {
"\x02 " ENUM2880_02_TEXT
};

// ProgNr 2920 "Bei EW Sperre" FUJITSU
const char ENUM2920[] PROGMEM_LATEST = {
"\x00 " ENUM2920_00_TEXT "\0"
"\x01 " ENUM2920_01_TEXT
};

// Energiezähler

// "Durchflussmessung Wärme"
const char ENUM3090[] PROGMEM_LATEST = {
"\x00 " ENUM3090_00_TEXT
};

const char ENUM3092[] PROGMEM_LATEST = {
"\x00 " ENUM3092_00_TEXT
};

const char ENUM3095[] PROGMEM_LATEST = {
"\x00 " ENUM3095_00_TEXT "\0"
"\x01 " ENUM3095_01_TEXT "\0"
"\x02 " ENUM3095_02_TEXT "\0"
"\x03 " ENUM3095_03_TEXT "\0"
"\x04 " ENUM3095_04_TEXT "\0"
"\x05 " ENUM3095_05_TEXT "\0"
"\x06 " ENUM3095_06_TEXT "\0"
"\x07 " ENUM3095_07_TEXT "\0"
"\x08 " ENUM3095_08_TEXT "\0"
"\x09 " ENUM3095_09_TEXT "\0"
"\x0a " ENUM3095_0a_TEXT "\0"
"\x0b " ENUM3095_0b_TEXT "\0"
"\x0c " ENUM3095_0c_TEXT "\0"
"\x0d " ENUM3095_0d_TEXT
};
// "Impulszählung Energie"
const char ENUM3100[] PROGMEM_LATEST = {
"\x00 " ENUM3100_00_TEXT "\0"
"\x01 " ENUM3100_01_TEXT "\0"
"\x02 " ENUM3100_02_TEXT "\0"
"\x03 " ENUM3100_03_TEXT "\0"
"\x04 " ENUM3100_04_TEXT "\0"
"\x05 " ENUM3100_05_TEXT "\0"
"\x06 " ENUM3100_06_TEXT "\0"
"\x07 " ENUM3100_07_TEXT "\0"
"\x08 " ENUM3100_08_TEXT "\0"
"\x09 " ENUM3100_09_TEXT "\0"
"\x0a " ENUM3100_0a_TEXT
};
// "Impulseinheit Energie"
const char ENUM3102[] PROGMEM_LATEST = {
"\x00 " ENUM3102_00_TEXT "\0"
"\x01 " ENUM3102_01_TEXT "\0"
"\x02 " ENUM3102_02_TEXT
};
// "Zählung Intern Elektro Vorl’"
const char ENUM3109[] PROGMEM_LATEST = {
"\x00 " ENUM3109_00_TEXT "\0"
"\x01 " ENUM3109_01_TEXT "\0"
"\x02 " ENUM3109_02_TEXT "\0"
"\x03 " ENUM3109_03_TEXT
};

const char ENUM3192[] PROGMEM_LATEST = {
"\x03 " ENUM3192_03_TEXT
};

// Kaskade
const char ENUM3510[] PROGMEM_LATEST = {  // numerical values are hypothetical
"\x01 " ENUM3510_01_TEXT "\0"
"\x02 " ENUM3510_02_TEXT "\0"
"\x03 " ENUM3510_03_TEXT
};
const char ENUM3541[] PROGMEM_LATEST = {  // numerical values are hypothetical
"\x00 " ENUM3541_00_TEXT "\0"
"\x01 " ENUM3541_01_TEXT "\0"
"\x02 " ENUM3541_02_TEXT "\0"
"\x03 " ENUM3541_03_TEXT
};
const char ENUM3544[] PROGMEM_LATEST = {  // numerical values are hypothetical
"\x01 " ENUM3544_01_TEXT "\0"
"\x02 " ENUM3544_02_TEXT "\0"
"\x03 " ENUM3544_03_TEXT "\0"
"\x04 " ENUM3544_04_TEXT "\0"
"\x05 " ENUM3544_05_TEXT "\0"
"\x06 " ENUM3544_06_TEXT "\0"
"\x07 " ENUM3544_07_TEXT "\0"
"\x08 " ENUM3544_08_TEXT "\0"
"\x09 " ENUM3544_09_TEXT "\0"
"\x0a " ENUM3544_0a_TEXT "\0"
"\x0b " ENUM3544_0b_TEXT "\0"
"\x0c " ENUM3544_0c_TEXT "\0"
"\x0d " ENUM3544_0d_TEXT "\0"
"\x0e " ENUM3544_0e_TEXT "\0"
"\x0f " ENUM3544_0f_TEXT "\0"
"\x10 " ENUM3544_10_TEXT
};

// Solar
const char ENUM3822[] PROGMEM_LATEST = {
"\x00 " ENUM3822_00_TEXT "\0"
"\x01 " ENUM3822_01_TEXT "\0"
"\x02 " ENUM3822_02_TEXT
};
const char ENUM3880[] PROGMEM_LATEST = {
"\x01 " ENUM3880_01_TEXT "\0"
"\x02 " ENUM3880_02_TEXT "\0"
"\x03 " ENUM3880_03_TEXT "\0"
"\x04 " ENUM3880_04_TEXT
};
const char ENUM3887[] PROGMEM_LATEST = {
"\x01 " ENUM3887_01_TEXT "\0"
"\x02 " ENUM3887_02_TEXT "\0"
"\x03 " ENUM3887_03_TEXT
};

// Feststoffkessel
const char ENUM4133[] PROGMEM_LATEST = {
"\x01 " ENUM4133_01_TEXT "\0"
"\x02 " ENUM4133_02_TEXT "\0"
"\x03 " ENUM4133_03_TEXT "\0"
"\x04 " ENUM4133_04_TEXT "\0"
"\x05 " ENUM4133_05_TEXT "\0"
"\x06 " ENUM4133_06_TEXT
};

const char ENUM4134[] PROGMEM_LATEST = {
"\x00 " ENUM4134_00_TEXT "\0"
"\x01 " "?" ENUM4134_01_TEXT "\0"
"\x02 " "?" ENUM4134_02_TEXT "\0"
"\x03 " "?" ENUM4134_03_TEXT
}; // todo Hinweis: x00 Keine ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM4135[] PROGMEM_LATEST = {
"\x01 " ENUM4135_01_TEXT "\0"
"\x02 " "?" ENUM4135_02_TEXT "\0"
"\x03 " "?" ENUM4135_03_TEXT
}; // todo Hinweis: x01 Speichertemperatur ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM4137[] PROGMEM_LATEST = {
"\x00 " "?" ENUM4137_00_TEXT "\0"
"\x01 " ENUM4137_01_TEXT "\0"
"\x02 " "?" ENUM4137_02_TEXT "\0"
"\x03 " "?" ENUM4137_03_TEXT
}; // todo Hinweis: x01 Mit B4 ist definitiv richtig. Die anderen muessen noch verifiziert werden.

#define ENUM4138 ENUM4135

const char ENUM4192[] PROGMEM_LATEST = {
"\x00 " ENUM4192_00_TEXT "\0"
"\x01 " ENUM4192_01_TEXT
};

// Pufferspeicher
const char ENUM4720[] PROGMEM_LATEST = {
"\x00 " ENUM4720_00_TEXT "\0"
"\x01 " ENUM4720_01_TEXT "\0"
"\x02 " ENUM4720_02_TEXT
};
const char ENUM4757[] PROGMEM_LATEST = {
"\x00 " ENUM4757_00_TEXT "\0"
"\x01 " ENUM4757_01_TEXT "\0"
"\x02 " ENUM4757_02_TEXT
};
const char ENUM4795[] PROGMEM_LATEST = {
"\x01 " ENUM4795_01_TEXT "\0"
"\x02 " ENUM4795_02_TEXT "\0"
"\x03 " ENUM4795_03_TEXT
};
const char ENUM4796[] PROGMEM_LATEST = {
"\x01 " ENUM4796_01_TEXT "\0"
"\x02 " ENUM4796_02_TEXT
};
const char ENUM4810[] PROGMEM_LATEST = {
"\x00 " ENUM4810_00_TEXT "\0"
"\x01 " ENUM4810_01_TEXT "\0"
"\x02 " ENUM4810_02_TEXT
};
const char ENUM4813[] PROGMEM_LATEST = {
"\x01 " ENUM4813_01_TEXT "\0"
"\x02 " ENUM4813_02_TEXT
};
// Trinkwasserspeicher
const char ENUM5010[] PROGMEM_LATEST = {
"\x00 " ENUM5010_00_TEXT "\0"
"\xff " ENUM5010_ff_TEXT
};
const char ENUM5022[] PROGMEM_LATEST = {
"\x01 " ENUM5022_01_TEXT "\0"
"\x02 " ENUM5022_02_TEXT "\0"
"\x03 " ENUM5022_03_TEXT
};
const char ENUM5022_2[] PROGMEM_LATEST = {
"\x01 " ENUM5022_2_01_TEXT "\0"
"\x02 " ENUM5022_2_02_TEXT "\0"
"\x03 " ENUM5022_2_03_TEXT "\0"
"\x04 " ENUM5022_2_04_TEXT "\0"
"\x05 " ENUM5022_2_05_TEXT
};
const char ENUM5040[] PROGMEM_LATEST = {
"\x00 " ENUM5040_00_TEXT "\0"
"\x01 " ENUM5040_01_TEXT "\0"
"\x02 " ENUM5040_02_TEXT
};
const char ENUM5057[] PROGMEM_LATEST = {
"\x00 " ENUM5057_00_TEXT "\0"
"\x01 " ENUM5057_01_TEXT "\0"
"\x02 " ENUM5057_02_TEXT
};
const char ENUM5060[] PROGMEM_LATEST = {
"\x01 " ENUM5060_01_TEXT "\0"
"\x02 " ENUM5060_02_TEXT "\0"
"\x03 " ENUM5060_03_TEXT
};
const char ENUM5061[] PROGMEM_LATEST = {
"\x01 " ENUM5061_01_TEXT "\0"
"\x02 " ENUM5061_02_TEXT "\0"
"\x03 " ENUM5061_03_TEXT
};
const char ENUM5062[] PROGMEM_LATEST = {
"\x01 " ENUM5062_01_TEXT "\0"
"\x02 " ENUM5062_02_TEXT
};
const char ENUM5130[] PROGMEM_LATEST = {
"\x00 " ENUM5130_00_TEXT "\0"
"\x01 " ENUM5130_01_TEXT
};
const char ENUM5130_2[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_OFF "\0"
"\x01 " ENUM5130_00_TEXT "\0"
"\x02 " ENUM5130_01_TEXT
};
const char ENUM5131[] PROGMEM_LATEST = {
"\x00 " ENUM5131_00_TEXT "\0"
"\x01 " ENUM5131_01_TEXT
};
const char ENUM5131_2[] PROGMEM_LATEST = {
"\x01 " ENUM5131_00_TEXT "\0"
"\x02 " ENUM5131_01_TEXT
};
// Konfiguration
const char ENUM5700[] PROGMEM_LATEST = { //FUJITSU
"\x01 " ENUM5700_01_TEXT "\0"
"\x02 " ENUM5700_02_TEXT "\0"
"\x03 " ENUM5700_03_TEXT "\0"
"\x04 " ENUM5700_04_TEXT "\0"
"\x05 " ENUM5700_05_TEXT
};
const char ENUM5711[] PROGMEM_LATEST = { //FUJITSU
"\x00 " ENUM5711_00_TEXT "\0"
"\x01 " ENUM5711_01_TEXT "\0"
"\x02 " ENUM5711_02_TEXT
};

const char ENUM5712[] PROGMEM_LATEST = {
"\x01 " ENUM5712_01_TEXT "\0"
"\x02 " ENUM5712_02_TEXT "\0"
"\x03 " ENUM5712_03_TEXT
};

const char ENUM5715[] PROGMEM_LATEST = {
"\x00 " ENUM5715_00_TEXT "\0"
"\x01 " ENUM5715_01_TEXT "\0"
"\x03 " ENUM5715_03_TEXT
};

const char ENUM5730[] PROGMEM_LATEST = {
"\x00 " ENUM5730_00_TEXT "\0"
"\x01 " ENUM5730_01_TEXT
};
const char ENUM5731[] PROGMEM_LATEST = {
"\x00 " ENUM5731_00_TEXT "\0"
"\x01 " ENUM5731_01_TEXT "\0"
"\x02 " ENUM5731_02_TEXT
};
const char ENUM5734[] PROGMEM_LATEST = {
"\x00 " ENUM5734_00_TEXT "\0"
"\x01 " ENUM5734_01_TEXT "\0"
"\x02 " ENUM5734_02_TEXT
};
const char ENUM5760[] PROGMEM_LATEST = {
"\x00 " ENUM5760_00_TEXT "\0"
"\x01 " ENUM5760_01_TEXT
};

const char ENUM5761[] PROGMEM_LATEST = {
"\x01\x01 " ENUM5761_01_01_TEXT "\0"
"\x02\x02 " ENUM5761_02_02_TEXT "\0"
"\x04\x04 " ENUM5761_04_04_TEXT "\0"
"\x08\x08 " ENUM5761_08_08_TEXT
};

const char ENUM5770[] PROGMEM_LATEST = {
"\x00 " ENUM5770_00_TEXT "\0"
"\x01 " ENUM5770_01_TEXT "\0"
"\x02 " ENUM5770_02_TEXT "\0"
"\x03 " ENUM5770_03_TEXT "\0"
"\x04 " ENUM5770_04_TEXT "\0"
"\x05 " ENUM5770_05_TEXT
};

const char ENUM5774[] PROGMEM_LATEST = {
"\x00 " ENUM5774_00_TEXT "\0"
"\xFF " ENUM5774_ff_TEXT 
};

const char ENUM5806[] PROGMEM_LATEST = { //FUJITSU
"\x01 " ENUM5806_01_TEXT "\0"
"\x02 " ENUM5806_02_TEXT "\0"
"\x03 " ENUM5806_03_TEXT "\0"
"\x04 " ENUM5806_04_TEXT
};
const char ENUM5840[] PROGMEM_LATEST = {
//"\x00 " ENUM5840_00_TEXT "\0"   -- O does not exits
"\x01 " ENUM5840_01_TEXT "\0"
"\x02 " ENUM5840_02_TEXT
};
const char ENUM5841[] PROGMEM_LATEST = {
"\x01 " ENUM5841_01_TEXT "\0"
"\x02 " ENUM5841_02_TEXT "\0"
"\x03 " ENUM5841_03_TEXT
};

// Konfiguration - Relaisausgang QX1
const char ENUM5890[] PROGMEM_LATEST = {
"\x00 " ENUM5890_00_TEXT "\0"
"\x01 " ENUM5890_01_TEXT "\0"
"\x02 " ENUM5890_02_TEXT "\0"
"\x03 " ENUM5890_03_TEXT "\0"
"\x04 " ENUM5890_04_TEXT "\0"
"\x05 " ENUM5890_05_TEXT "\0"
"\x06 " ENUM5890_06_TEXT "\0"
"\x07 " ENUM5890_07_TEXT "\0"
"\x08 " ENUM5890_08_TEXT "\0"
"\x09 " ENUM5890_09_TEXT "\0"
"\x0a " ENUM5890_0a_TEXT "\0"
"\x0b " ENUM5890_0b_TEXT "\0"
"\x0c " ENUM5890_0c_TEXT "\0"
"\x0d " ENUM5890_0d_TEXT "\0"
"\x0e " ENUM5890_0e_TEXT "\0"
"\x0f " ENUM5890_0f_TEXT "\0"
"\x10 " ENUM5890_10_TEXT "\0"
"\x11 " ENUM5890_11_TEXT "\0"
"\x12 " ENUM5890_12_TEXT "\0"
"\x13 " ENUM5890_13_TEXT "\0"
"\x14 " ENUM5890_14_TEXT "\0"
"\x15 " ENUM5890_15_TEXT "\0"
"\x16 " ENUM5890_16_TEXT "\0"
"\x17 " ENUM5890_17_TEXT "\0"
"\x18 " ENUM5890_18_TEXT "\0"
"\x19 " ENUM5890_19_TEXT "\0"
"\x1a " ENUM5890_1a_TEXT "\0"
"\x1b " ENUM5890_1b_TEXT "\0"
"\x1c " ENUM5890_1c_TEXT "\0"
"\x1d " ENUM5890_1d_TEXT "\0"
"\x21 " ENUM5890_21_TEXT "\0"
"\x23 " ENUM5890_23_TEXT "\0"
"\x28 " ENUM5890_28_TEXT "\0"
"\x29 " ENUM5890_29_TEXT
};

const char ENUM5890_2[] PROGMEM_LATEST = {
"\x00 " ENUM5890_2_00_TEXT "\0"
"\x01 " ENUM5890_2_01_TEXT "\0"
"\x02 " ENUM5890_2_02_TEXT "\0"
"\x03 " ENUM5890_2_03_TEXT "\0"
"\x04 " ENUM5890_2_04_TEXT "\0"
"\x05 " ENUM5890_2_05_TEXT "\0"
"\x06 " ENUM5890_2_06_TEXT "\0"
"\x07 " ENUM5890_2_07_TEXT "\0"
"\x08 " ENUM5890_2_08_TEXT "\0"
"\x09 " ENUM5890_2_09_TEXT "\0"
"\x0a " ENUM5890_2_0a_TEXT "\0"
"\x0b " ENUM5890_2_0b_TEXT
};

#define ENUM5891 ENUM5890               // Relaisausgang QX2
#define ENUM5892 ENUM5890               // Relaisausgang QX3
#define ENUM5894 ENUM5890               // Relaisausgang QX4
#define ENUM5902 ENUM5890               // Relaisausgang QX21
#define ENUM5904 ENUM5890               // Relaisausgang QX23
#define ENUM5908 ENUM5890               // Relaisausgang QX3-Mod
/* Possibly the same as 5890:
#define ENUM5909 ENUM5890               // Relaisausgang QX4-Mod
*/
// The numerical values are undocumented in the Broetje Systemhandbuch
// Values here are hypothetical.
const char ENUM5895[] PROGMEM_LATEST = {        // Relaisausgang QX5
"\x00 " "?" ENUM5895_00_TEXT "\0"
"\x01 " "?" ENUM5895_01_TEXT "\0"
"\x02 " "?" ENUM5895_02_TEXT "\0"
"\x03 " "?" ENUM5895_03_TEXT "\0"
"\x04 " "?" ENUM5895_04_TEXT "\0"
"\x05 " "?" ENUM5895_05_TEXT "\0"
"\x06 " "?" ENUM5895_06_TEXT "\0"
"\x07 " "?" ENUM5895_07_TEXT "\0"
"\x08 " "?" ENUM5895_08_TEXT "\0"
"\x09 " "?" ENUM5895_09_TEXT "\0"
"\x0a " "?" ENUM5895_0a_TEXT "\0"
"\x0b " "?" ENUM5895_0b_TEXT "\0"
"\x0c " "?" ENUM5895_0c_TEXT "\0"
"\x0d " "?" ENUM5895_0d_TEXT "\0"
"\x0e " "?" ENUM5895_0e_TEXT "\0"
"\x0f " "?" ENUM5895_0f_TEXT "\0"
"\x10 " "?" ENUM5895_10_TEXT "\0"
"\x11 " "?" ENUM5895_11_TEXT "\0"
"\x12 " "?" ENUM5895_12_TEXT "\0"
"\x13 " "?" ENUM5895_13_TEXT "\0"
"\x14 " "?" ENUM5895_14_TEXT "\0"
"\x15 " "?" ENUM5895_15_TEXT "\0"
"\x16 " "?" ENUM5895_16_TEXT "\0"
"\x17 " "?" ENUM5895_17_TEXT "\0"
"\x18 " "?" ENUM5895_18_TEXT "\0"
"\x19 " "?" ENUM5895_19_TEXT "\0"
"\x1a " "?" ENUM5895_1a_TEXT "\0"
"\x1b " "?" ENUM5895_1b_TEXT "\0"
"\x1c " "?" ENUM5895_1c_TEXT "\0"
"\x1d " "?" ENUM5895_1d_TEXT "\0"
"\x1e " "?" ENUM5895_1e_TEXT "\0"
"\x1f " "?" ENUM5895_1f_TEXT "\0"
"\x20 " "?" ENUM5895_20_TEXT "\0"
"\x21 " "?" ENUM5895_21_TEXT "\0"
"\x22 " "?" ENUM5895_22_TEXT "\0"
"\x23 " "?" ENUM5895_23_TEXT "\0"
"\x24 " "?" ENUM5895_24_TEXT "\0"
"\x25 " "?" ENUM5895_25_TEXT "\0"
"\x26 " "?" ENUM5895_26_TEXT "\0"
"\x27 " "?" ENUM5895_27_TEXT "\0"
"\x28 " "?" ENUM5895_28_TEXT "\0"
"\x29 " "?" ENUM5895_29_TEXT "\0"
"\x2a " "?" ENUM5895_2a_TEXT "\0"
"\x2b " "?" ENUM5895_2b_TEXT "\0"
"\x2c " "?" ENUM5895_2c_TEXT "\0"
"\x2d " "?" ENUM5895_2d_TEXT
};

// Konfiguration - Thision 5922 Relaisausgang 1 RelCl
const char ENUM5920[] PROGMEM_LATEST = {
"\x00 " ENUM5920_00_TEXT "\0"
"\x01 " ENUM5920_01_TEXT "\0"
"\x02 " ENUM5920_02_TEXT "\0"
"\x03 " ENUM5920_03_TEXT "\0"
"\x04 " ENUM5920_04_TEXT "\0"
"\x05 " ENUM5920_05_TEXT "\0"
"\x06 " ENUM5920_06_TEXT "\0"
"\x07 " ENUM5920_07_TEXT "\0"
"\x08 " ENUM5920_08_TEXT "\0"
"\x09 " ENUM5920_09_TEXT "\0"
"\x0a " ENUM5920_0a_TEXT "\0"
"\x0b " ENUM5920_0b_TEXT "\0"
"\x0c " ENUM5920_0c_TEXT "\0"
"\x0d " ENUM5920_0d_TEXT "\0"
"\x0e " ENUM5920_0e_TEXT "\0"
"\x0f " ENUM5920_0f_TEXT "\0"
"\x10 " ENUM5920_10_TEXT "\0"
"\x11 " ENUM5920_11_TEXT
};
#define ENUM5922 ENUM5920               // Thision 5923 Relaisausgang 2 RelCl
#define ENUM5923 ENUM5920               // Thision 5923 Relaisausgang 2 RelCl
#define ENUM5924 ENUM5920               // Thision 5924 Relaisausgang 3 RelCl
#define ENUM5926 ENUM5920               // Thision 5926 Relaisausgang 1 SolCl
#define ENUM5927 ENUM5920               // Thision 5927 Relaisausgang 2 SolCl
#define ENUM5928 ENUM5920               // Thision 5928 Relaisausgang 3 SolCl

// Konfiguration - Fuehlereingang BX1
const char ENUM5930[] PROGMEM_LATEST = {
"\x00 " ENUM5930_00_TEXT "\0"
"\x01 " ENUM5930_01_TEXT "\0"
"\x02 " ENUM5930_02_TEXT "\0"
"\x03 " ENUM5930_03_TEXT "\0"
"\x04 " ENUM5930_04_TEXT "\0"
"\x05 " ENUM5930_05_TEXT "\0"
"\x06 " ENUM5930_06_TEXT "\0"
"\x07 " ENUM5930_07_TEXT "\0"
"\x08 " ENUM5930_08_TEXT "\0"
"\x09 " ENUM5930_09_TEXT "\0"
"\x0a " ENUM5930_0a_TEXT "\0"
"\x0b " ENUM5930_0b_TEXT "\0"
"\x0c " ENUM5930_0c_TEXT "\0"
"\x0d " ENUM5930_0d_TEXT "\0"
"\x0e " ENUM5930_0e_TEXT "\0"
"\x0f " ENUM5930_0f_TEXT "\0"
"\x10 " ENUM5930_10_TEXT "\0"
"\x11 " ENUM5930_11_TEXT
};

#define ENUM5931 ENUM5930               // Konfiguration - Fühlereingang BX 2
#define ENUM5932 ENUM5930               // Konfiguration - Fühlereingang BX 3
#define ENUM5933 ENUM5930               // Konfiguration - Fühlereingang BX 4
#define ENUM5941 ENUM5930               // Konfiguration - Fühlereingang BX21
#define ENUM5942 ENUM5930               // Konfiguration - Fühlereingang BX22


// Konfiguration - Funktion Eingang H1 (LOGON B)
const char ENUM5950[] PROGMEM_LATEST = {
"\x00 " ENUM5950_00_TEXT "\0"
"\x01 " ENUM5950_01_TEXT "\0"
"\x02 " ENUM5950_02_TEXT "\0"
"\x03 " ENUM5950_03_TEXT "\0"
"\x04 " ENUM5950_04_TEXT "\0"
"\x05 " ENUM5950_05_TEXT "\0"
"\x06 " ENUM5950_06_TEXT "\0"
"\x07 " ENUM5950_07_TEXT "\0"
"\x08 " ENUM5950_08_TEXT "\0"
"\x09 " ENUM5950_09_TEXT "\0"
"\x0a " ENUM5950_0a_TEXT "\0"
"\x0b " ENUM5950_0b_TEXT "\0"
"\x0c " ENUM5950_0c_TEXT "\0"
"\x0d " ENUM5950_0d_TEXT "\0"
"\x0e " ENUM5950_0e_TEXT
};

// Konfiguration - Funktion Eingang H1 THISION
const char ENUM5950_2[] PROGMEM_LATEST = {
"\x00 " ENUM5950_2_00_TEXT "\0"
"\x01 " ENUM5950_2_01_TEXT "\0"
"\x02 " ENUM5950_2_02_TEXT "\0"
"\x03 " ENUM5950_2_03_TEXT "\0"
"\x07 " ENUM5950_2_07_TEXT "\0"
"\x08 " ENUM5950_2_08_TEXT "\0"
"\x09 " ENUM5950_2_09_TEXT
};

// Konfiguration - Funktion Eingang H1 Brötje
const char ENUM5950_3[] PROGMEM_LATEST = {
"\x01 " ENUM5950_3_01_TEXT "\0"
"\x02 " ENUM5950_3_02_TEXT "\0"
"\x03 " ENUM5950_3_03_TEXT "\0"
"\x04 " ENUM5950_3_04_TEXT "\0"
"\x05 " ENUM5950_3_05_TEXT "\0"
"\x06 " ENUM5950_3_06_TEXT "\0"
"\x07 " ENUM5950_3_07_TEXT "\0"
"\x08 " ENUM5950_3_08_TEXT "\0"
"\x09 " ENUM5950_3_09_TEXT
};

// Konfiguration - Funktion Eingang H1 Brötje BOB
const char ENUM5950_4[] PROGMEM_LATEST = {
"\x00 " ENUM5950_4_00_TEXT "\0"
"\x01 " ENUM5950_4_01_TEXT "\0"
"\x02 " ENUM5950_4_02_TEXT "\0"
"\x03 " ENUM5950_4_03_TEXT "\0"
"\x04 " ENUM5950_4_04_TEXT "\0"
"\x05 " ENUM5950_4_05_TEXT "\0"
"\x06 " ENUM5950_4_06_TEXT "\0"
"\x07 " ENUM5950_4_07_TEXT "\0"
"\x08 " ENUM5950_4_08_TEXT "\0"
"\x09 " ENUM5950_4_09_TEXT "\0"
"\x0a " ENUM5950_4_0a_TEXT "\0"
"\x0b " ENUM5950_4_0b_TEXT "\0"
"\x0c " ENUM5950_4_0c_TEXT "\0"
"\x0d " ENUM5950_4_0d_TEXT "\0"
"\x0e " ENUM5950_4_0e_TEXT "\0"
"\x0f " ENUM5950_4_0f_TEXT "\0"
"\x10 " ENUM5950_4_10_TEXT "\0"
"\x11 " ENUM5950_4_11_TEXT "\0"
"\x12 " ENUM5950_4_12_TEXT "\0"
"\x13 " ENUM5950_4_13_TEXT "\0"
"\x14 " ENUM5950_4_14_TEXT "\0"
"\x16 " ENUM5950_4_16_TEXT "\0"
"\x17 " ENUM5950_4_17_TEXT "\0"
"\x18 " ENUM5950_4_18_TEXT "\0"
"\x1d " ENUM5950_4_1d_TEXT "\0"
"\x1e " ENUM5950_4_1e_TEXT "\0"
"\x32 " ENUM5950_4_32_TEXT "\0"
"\x33 " ENUM5950_4_33_TEXT "\0"
"\x34 " ENUM5950_4_34_TEXT "\0"
"\x38 " ENUM5950_4_38_TEXT
};

const char ENUM5950_5[] PROGMEM_LATEST = {
"\x01 " ENUM5950_5_01_TEXT "\0"
"\x02 " ENUM5950_5_02_TEXT "\0"
"\x03 " ENUM5950_5_03_TEXT "\0"
"\x04 " ENUM5950_5_04_TEXT "\0"
"\x05 " ENUM5950_5_05_TEXT "\0"
"\x06 " ENUM5950_5_06_TEXT "\0"
"\x07 " ENUM5950_5_07_TEXT "\0"
"\x08 " ENUM5950_5_08_TEXT "\0"
"\x09 " ENUM5950_5_09_TEXT "\0"
"\x0a " ENUM5950_5_0a_TEXT "\0"
"\x0b " ENUM5950_5_0b_TEXT "\0"
"\x0c " ENUM5950_5_0c_TEXT "\0"
"\x0d " ENUM5950_5_0d_TEXT "\0"
"\x0e " ENUM5950_5_0e_TEXT "\0"
"\x0f " ENUM5950_5_0f_TEXT "\0"
"\x11 " ENUM5950_5_11_TEXT "\0"
"\x12 Raumtemperatur 10V"};

// Konfiguration - Funktion Eingang H1 RVA63.244
const char ENUM5950_6[] PROGMEM_LATEST = {
"\x00 " ENUM5950_6_00_TEXT "\0"
"\x01 " ENUM5950_6_01_TEXT "\0"
"\x02 " ENUM5950_6_02_TEXT "\0"
"\x03 " ENUM5950_6_03_TEXT "\0"
"\x04 " ENUM5950_6_04_TEXT
};

// Konfiguration - Funktion Eingang H1 LMU64
const char ENUM5950_7[] PROGMEM_LATEST = {
"\x00 " ENUM5950_7_00_TEXT "\0"
"\x01 " ENUM5950_7_01_TEXT "\0"
"\x02 " ENUM5950_7_02_TEXT "\0"
"\x03 " ENUM5950_7_03_TEXT
};

const char ENUM5951[] PROGMEM_LATEST = {
"\x00 " ENUM5951_00_TEXT "\0"
"\x01 " ENUM5951_01_TEXT
};

// Konfiguration - 5957 BA-Umschaltung HK's+TWW
const char ENUM5957[] PROGMEM_LATEST = {
"\x01 " ENUM5957_01_TEXT "\0"
"\x02 " ENUM5957_02_TEXT "\0"
"\x03 " ENUM5957_03_TEXT "\0"
"\x04 " ENUM5957_04_TEXT
};

const char ENUM5957_2[] PROGMEM_LATEST = {
"\x00 " ENUM5957_2_00_TEXT "\0"
"\x01 " ENUM5957_2_01_TEXT "\0"
"\x02 " ENUM5957_2_02_TEXT "\0"
"\x03 " ENUM5957_2_03_TEXT "\0"
"\x04 " ENUM5957_2_04_TEXT
};

#define ENUM5960 ENUM5950               // Konfiguration - Funktion Eingang H3
#define ENUM5960_2 ENUM5950_2           // Konfiguration - Funktion Eingang H3

const char ENUM5960_3[] PROGMEM_LATEST = {
"\x00 " ENUM5960_3_00_TEXT "\0"
"\x01 " ENUM5960_3_01_TEXT "\0"
"\x02 " ENUM5960_3_02_TEXT "\0"
"\x03 " ENUM5960_3_03_TEXT "\0"
};

const char ENUM5960_4[] PROGMEM_LATEST = {
"\x00 " ENUM5960_4_00_TEXT
};

#define ENUM5961 ENUM5951               // Konfiguration - Wirksinn Kontakt H3
#define ENUM5961_2 ENUM5951             // Konfiguration - Wirksinn Kontakt H3

// Konfiguration - Thision 5970 Konfig Raumthermostat 1
const char ENUM5970[] PROGMEM_LATEST = {
"\x00 " ENUM5970_00_TEXT "\0"
"\x01 " ENUM5970_01_TEXT "\0"
"\x02 " ENUM5970_02_TEXT "\0"
"\x03 " ENUM5970_03_TEXT "\0"
"\x04 " ENUM5970_04_TEXT
};
#define ENUM5970_2 ENUM5950_4

#define ENUM5971 ENUM5970               // Thision 5971 Konfig Raumthermostat 2
#define ENUM5971_2 ENUM5951

// Konfiguration - Thision 5973 Funktion Eingang RelCl
const char ENUM5973[] PROGMEM_LATEST = {
"\x00 " ENUM5973_00_TEXT "\0"
"\x01 " ENUM5973_01_TEXT "\0"
"\x02 " ENUM5973_02_TEXT "\0"
"\x03 " ENUM5973_03_TEXT "\0"
"\x04 " ENUM5973_04_TEXT "\0"
"\x05 " ENUM5973_05_TEXT "\0"
"\x06 " ENUM5973_06_TEXT "\0"
"\x07 " ENUM5973_07_TEXT "\0"
"\x08 " ENUM5973_08_TEXT "\0"
"\x09 " ENUM5973_09_TEXT "\0"
"\x0b " ENUM5973_0b_TEXT
};

#define ENUM5977_2 ENUM5970_2

// Konfiguration - Thision 5978 Funktion Eingang SolCl
const char ENUM5978[] PROGMEM_LATEST = {
"\x00 " ENUM5978_00_TEXT "\0"
"\x0a " ENUM5978_0a_TEXT
};

#define ENUM5978_2 ENUM5971_2

// 5980 Konfiguration - Funktion Eingang EX1
// The System-Handbuch does not document numerical values.
const char ENUM5980[] PROGMEM_LATEST = {
"\x00 " ENUM5980_00_TEXT "\0"
"\x01 " ENUM5980_01_TEXT "\0"
"\x02 " ENUM5980_02_TEXT "\0"
"\x03 " "?" ENUM5980_03_TEXT "\0"
"\x04 " "?" ENUM5980_04_TEXT "\0"
"\x05 " "?" ENUM5980_05_TEXT "\0"
"\x06 " "?" ENUM5980_06_TEXT "\0"
"\x07 " "?" ENUM5980_07_TEXT "\0"
"\x08 " "?" ENUM5980_08_TEXT "\0"
"\x09 " "?" ENUM5980_09_TEXT "\0"
"\x0a " "?" ENUM5980_0a_TEXT "\0"
"\x0b " "?" ENUM5980_0b_TEXT "\0"
"\x0c " "?" ENUM5980_0c_TEXT "\0"
"\x0f " ENUM5980_0f_TEXT "\0"
"\x10 " "?" ENUM5980_10_TEXT "\0"
"\x11 " "?" ENUM5980_11_TEXT "\0"
"\x12 " "?" ENUM5980_12_TEXT "\0"
"\x13 " "?" ENUM5980_13_TEXT "\0"
"\x14 " "?" ENUM5980_14_TEXT "\0"
"\x15 " "?" ENUM5980_15_TEXT "\0"
"\x16 " "?" ENUM5980_16_TEXT "\0"
"\x1a " ENUM5980_1a_TEXT
};

#define ENUM5981 ENUM5951               // Konfiguration - Wirksinn Eingang EX1

// Konfiguration - Funktion Eingang EX2
const char ENUM5982[] PROGMEM_LATEST = {
"\x01 " ENUM5982_01_TEXT "\0"
"\x02 " ENUM5982_02_TEXT "\0"
"\x03 " ENUM5982_03_TEXT "\0"
"\x04 " ENUM5982_04_TEXT "\0"
"\x05 Übertemperaturableitung"};

#define ENUM5983 ENUM5951               // Konfiguration - Wirksinn Eingang EX2
#define ENUM5984 ENUM5980               // Konfiguration - 5984 Funktion Eingang EX3
#define ENUM5985 ENUM5951               // Konfiguration - Wirksinn Eingang EX3
#define ENUM5986 ENUM5980               // Konfiguration - 5986 Funktion Eingang EX4
#define ENUM5987 ENUM5951               // Konfiguration - Wirksinn Eingang EX4
#define ENUM5989 ENUM5951               // Konfiguration - Wirksinn Eingang EX5

// Konfiguration - 5988 Funktion Eingang EX5
// The System-Handbuch does not document numerical values.
// !FIXME! Values here are hypothetical.
const char ENUM5988[] PROGMEM_LATEST = {
"\x00 " "?" ENUM5988_00_TEXT "\0"
"\x01 " "?" ENUM5988_01_TEXT "\0"
"\x02 " "?" ENUM5988_02_TEXT "\0"
"\x03 " "?" ENUM5988_03_TEXT "\0"
"\x04 " "?" ENUM5988_04_TEXT "\0"
"\x05 " "?" ENUM5988_05_TEXT "\0"
"\x06 " "?" ENUM5988_06_TEXT "\0"
"\x07 " "?" ENUM5988_07_TEXT "\0"
"\x08 " "?" ENUM5988_08_TEXT "\0"
"\x09 " "?" ENUM5988_09_TEXT "\0"
"\x0a " "?" ENUM5988_0a_TEXT "\0"
"\x0b " "?" ENUM5988_0b_TEXT "\0"
"\x0c " "?" ENUM5988_0c_TEXT "\0"
"\x0d " "?" ENUM5988_0d_TEXT "\0"
"\x0e " "?" ENUM5988_0e_TEXT "\0"
"\x0f " "?" ENUM5988_0f_TEXT "\0"
"\x10 " "?" ENUM5988_10_TEXT
};
#define ENUM5990 ENUM5988           // Konfiguration - 5990 Funktion Eingang EX6
#define ENUM5992 ENUM5988           // Konfiguration - 5992 Funktion Eingang EX7

// Konfiguration - Funktion Mischergruppe 1
const char ENUM6014[] PROGMEM_LATEST = {
"\x00 " ENUM6014_00_TEXT "\0"
"\x01 " ENUM6014_01_TEXT "\0"
"\x02 " ENUM6014_02_TEXT "\0"           // ISR-SSR Solarsystemregler Handbuch
"\x03 " ENUM6014_03_TEXT "\0"
"\x04 " ENUM6014_04_TEXT "\0"
"\x05 " ENUM6014_05_TEXT "\0"
"\x06 " ENUM6014_06_TEXT
};
#define ENUM6015 ENUM6014           // Konfiguration - 6015 Funktion Mischergruppe 2

// Konfiguration - Funktion Erweiterungsmodul 1
const char ENUM6020[] PROGMEM_LATEST = {
"\x00 " ENUM6020_00_TEXT "\0"
"\x01 " ENUM6020_01_TEXT "\0"
"\x02 " ENUM6020_02_TEXT "\0"
"\x03 " ENUM6020_03_TEXT "\0"
"\x04 " ENUM6020_04_TEXT "\0"
"\x05 " ENUM6020_05_TEXT "\0"
"\x06 " ENUM6020_06_TEXT "\0"
"\x07 " ENUM6020_07_TEXT "\0"
"\x08 " ENUM6020_08_TEXT
};
#define ENUM6021 ENUM6020           // Konfiguration - Funktion Erweiterungsmodul 2


// The predominant reason why this ProgNr (6030) has been included is the mention of
// Solarstellglied Puffer and Solarstellglied Schwimmbad. My search for these
// names lead me here.  It seems that Relaisausgang QX21 is (a) unused and
// (b) not supported in all installations. (comment by miwi)

// Konfiguration - Relaisausgang QX21
// The Broetje System-Handbuch ISR Plus does not document numerical values;
// inserting hypothetical values.
// !FIXME! !TODO! Figure out the real numerical values.
const char ENUM6030[] PROGMEM_LATEST = {
"\x00 " ENUM6030_00_TEXT "\0"                           // with all controllers, confirmed
"\x01 " "?" ENUM6030_01_TEXT "\0"          // with      BSW,BLW
"\x02 " "?" ENUM6030_02_TEXT "\0"       // with      BSW,BLW
"\x03 " "?" ENUM6030_03_TEXT "\0"           // with      BSW
"\x04 " "?" ENUM6030_04_TEXT "\0"        // with      BSW,BLW
"\x05 " "?" ENUM6030_05_TEXT "\0"         // with      BSW,BLW
"\x06 " "?" ENUM6030_06_TEXT "\0"   // with      BSW,BLW
"\x07 " "?" ENUM6030_07_TEXT "\0"   // with      BSW,BLW
"\x08 " "?" ENUM6030_08_TEXT "\0"   // with      BSW,BLW
"\x09 " "?" ENUM6030_09_TEXT "\0"           // with      BSW,BLW, BCA,        Kessel L,TE,SOB
"\x0a " "?" ENUM6030_0a_TEXT "\0"          // with SSR, BSW,BLW, BCA,        Kessel L,TE,SOB
"\x0b " "?" ENUM6030_0b_TEXT "\0"      // with SSR, BSW,BLW
"\x0c " "?" ENUM6030_0c_TEXT "\0"              // with SSR, BSW,BLW,             Kessel L,TE,SOB
"\x0d " "?" ENUM6030_0d_TEXT "\0"                   // all controllers
"\x0e " "?" ENUM6030_0e_TEXT "\0"                 // with SSR, BSW,     BCA,        Kessel L,TE,SOB
"\x0f " "?" ENUM6030_0f_TEXT "\0"                // with SSR, BSW,BLW, BCA, ZR1/2, Kessel L,TE,SOB
"\x10 " "?" ENUM6030_10_TEXT "\0"               // with all controllers
"\x11 " "?" ENUM6030_11_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x12 " "?" ENUM6030_12_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x13 " "?" ENUM6030_13_TEXT "\0"         // with SSR, BSW,     BCA, ZR1/2, Kessel L,TE,SOB
"\x14 " "?" ENUM6030_14_TEXT "\0"         // with all controllers
"\x15 " "?" ENUM6030_15_TEXT "\0"                   // with all controllers
"\x16 " "?" ENUM6030_16_TEXT "\0"             // with all controllers
"\x17 " "?" ENUM6030_17_TEXT "\0"         // with SSR, BSW,                 Kessel L,TE,SOB
"\x18 " "?" ENUM6030_18_TEXT "\0"       // with SSR, BSW,BLW, BCA
"\x19 " "?" ENUM6030_19_TEXT "\0"             // with SSR, BSW           ZR1/2
"\x1a " "?" ENUM6030_1a_TEXT "\0"       // with SSR, BSW
"\x1b " "?" ENUM6030_1b_TEXT "\0"    // with SSR, BSW,BLW
"\x1c " "?" ENUM6030_1c_TEXT "\0"      // with SSR, BSW,BLW
"\x1d " "?" ENUM6030_1d_TEXT "\0" // with SSR, BSW,BLW
"\x1e " "?" ENUM6030_1e_TEXT "\0"           // with SSR, BSW
"\x1f " "?" ENUM6030_1f_TEXT "\0"                   // with      BSW,BLW
"\x20 " "?" ENUM6030_20_TEXT "\0"                // with      BSW,     BCA
"\x21 " "?" ENUM6030_21_TEXT "\0"        // with      BSW,BLW,      ZR1/2
"\x22 " "?" ENUM6030_22_TEXT "\0"   // with      BSW
"\x23 " "?" ENUM6030_23_TEXT "\0"                 // with      BSW,BLW
"\x24 " "?" ENUM6030_24_TEXT "\0"                 // with      BSW
"\x25 " "?" ENUM6030_25_TEXT "\0"            // with SSR, BSW,BLW
"\x26 " "?" ENUM6030_26_TEXT "\0"            // with SSR, BSW,BLW       ZR1/2
"\x27 " "?" ENUM6030_27_TEXT "\0"              // with SSR, BSW,BLW, BCA
"\x28 " "?" ENUM6030_28_TEXT "\0"        // with SSR, BSW
"\x29 " "?" ENUM6030_29_TEXT "\0"        // with BSW,          BCA
"\x2a " "?" ENUM6030_2a_TEXT "\0"      // with SSR, BSW,     BCA
"\x2b " "?" ENUM6030_2b_TEXT "\0"           // with      BSW,BLW  BCA, ZR1/2
"\x2c " "?" ENUM6030_2c_TEXT "\0"           // with      BSW,BLW       ZR1/2
"\x2d " "?" ENUM6030_2d_TEXT "\0"           // with          BLW
"\x2e " "?" ENUM6030_2e_TEXT    // with          BLW
};

#define ENUM6031 ENUM6030
#define ENUM6032 ENUM6030
#define ENUM6033 ENUM6030     // Relaisausgang QX21 Modul 2 / identity with 6030: analogous guess
#define ENUM6034 ENUM6030     // Relaisausgang QX22 Modul 2 / identity with 6030: analogous guess
#define ENUM6035 ENUM6030     // Relaisausgang QX23 Modul 2 / identity with 6030: analogous guess

// Konfiguration - 6040 Fühlereingang BX21
const char ENUM6040[] PROGMEM_LATEST = {
"\x00 " ENUM6040_00_TEXT "\0"
"\x01 " ENUM6040_01_TEXT "\0"
"\x02 " ENUM6040_02_TEXT "\0"
"\x03 " ENUM6040_03_TEXT "\0"
"\x04 " ENUM6040_04_TEXT "\0"
"\x05 " ENUM6040_05_TEXT "\0"
"\x06 " ENUM6040_06_TEXT "\0"
"\x07 " ENUM6040_07_TEXT "\0"
"\x08 " ENUM6040_08_TEXT "\0"
"\x09 " ENUM6040_09_TEXT "\0"
"\x0a " ENUM6040_0a_TEXT "\0"
"\x0b " ENUM6040_0b_TEXT "\0"
"\x0c " ENUM6040_0c_TEXT "\0"
"\x0d " ENUM6040_0d_TEXT "\0"
"\x0e " ENUM6040_0e_TEXT "\0"
"\x0f " ENUM6040_0f_TEXT "\0"
"\x10 " ENUM6040_10_TEXT "\0"
"\x11 " ENUM6040_11_TEXT
};
#define ENUM6041 ENUM6040	// Konfiguration - 6041 Fühlereingang BX22
#define ENUM6042 ENUM6040 // Fühlereingang BX21 Modul 2 / identity with 6040: analogous guess
#define ENUM6043 ENUM6040 // Fühlereingang BX22 Modul 2 / identity with 6040: analogous guess
#define ENUM6046 ENUM5950	// Konfiguration - Funktion Eingang H2
#define ENUM6046_2 ENUM5977_2  // Konfiguration - Funktion Kontakt H2 EM1
#define ENUM6047 ENUM5951	// Konfiguration - Wirksinn Kontakt H2
#define ENUM6047_2 ENUM5978_2  // Konfiguration - Wirksinn Eingang H2 EM1
// Konfiguration - 6070 Funktion Ausgang UX
const char ENUM6070[] PROGMEM_LATEST = {
"\x00 " ENUM6070_00_TEXT "\0"
"\x01 " ENUM6070_01_TEXT "\0"
"\x02 " ENUM6070_02_TEXT
};
// Konfiguration - 6071 Signallogik Ausgang UX
const char ENUM6071[] PROGMEM_LATEST = {
"\x00 " ENUM6071_00_TEXT "\0"
"\x01 " ENUM6071_01_TEXT
};

const char ENUM6085[] PROGMEM_LATEST = {
"\x00 " ENUM6085_00_TEXT "\0"
"\x01 " ENUM6085_01_TEXT "\0"
"\x02 " ENUM6085_02_TEXT "\0"
"\x04 " ENUM6085_04_TEXT "\0"
"\x05 " ENUM6085_05_TEXT "\0"
"\x06 " ENUM6085_06_TEXT "\0"
"\x07 " ENUM6085_07_TEXT
};

// Konfiguration - Fühlertyp Kollektor
const char ENUM6097[] PROGMEM_LATEST = {
"\x01 " ENUM6097_01_TEXT "\0"
"\x02 " ENUM6097_02_TEXT
};
#define ENUM6101 ENUM6097           // Fühlertyp Abgastemperatur

// Konfiguration - Wärm'anfo bei Ökobetrieb AUS| EIN Trinkwasser | ein
const char ENUM6131[] PROGMEM_LATEST = {
"\x00 " ENUM6131_00_TEXT "\0"
"\x01 " ENUM6131_01_TEXT "\0"
"\x02 " ENUM6131_02_TEXT
};

const char ENUM6136[] PROGMEM_LATEST = {
"\x01 " ENUM6136_01_TEXT "\0"
"\x02 " ENUM6136_02_TEXT "\0"
"\x03 " ENUM6136_03_TEXT
};

const char ENUM6148[] PROGMEM_LATEST = {
"\x00 " ENUM6148_00_TEXT
};

const char ENUM6236[] PROGMEM_LATEST = {
"\x06\x04 "
};

// Konfiguration - KonfigRG0

const char ENUM6230[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6230_00_01_TEXT "\0"
"\x01\x01 " ENUM6230_01_01_TEXT "\0"
"\x00\x02 " ENUM6230_00_02_TEXT "\0"
"\x02\x02 " ENUM6230_02_02_TEXT "\0"
"\x00\x04 " ENUM6230_00_04_TEXT "\0"
"\x04\x04 " ENUM6230_04_04_TEXT "\0"
"\x00\x08 " ENUM6230_00_08_TEXT "\0"
"\x08\x08 " ENUM6230_08_08_TEXT "\0"
"\x00\x10 " ENUM6230_00_10_TEXT "\0"
"\x10\x10 " ENUM6230_10_10_TEXT "\0"
"\x00\x20 " ENUM6230_00_20_TEXT "\0"
"\x20\x20 " ENUM6230_20_20_TEXT "\0"
"\x00\x40 " ENUM6230_00_40_TEXT "\0"
"\x40\x40 " ENUM6230_40_40_TEXT
};

// Konfiguration - KonfigRG1

const char ENUM6240[] PROGMEM_LATEST = {
"\x00\x03 " ENUM6240_00_03_TEXT "\0"
"\x01\x03 " ENUM6240_01_03_TEXT "\0"
"\x02\x03 " ENUM6240_02_03_TEXT "\0"
"\x00\x04 " ENUM6240_00_04_TEXT "\0"
"\x04\x04 " ENUM6240_04_04_TEXT "\0"
"\x00\x08 " ENUM6240_00_08_TEXT "\0"
"\x08\x08 " ENUM6240_08_08_TEXT "\0"
"\x00\x10 " ENUM6240_00_10_TEXT "\0"
"\x10\x10 " ENUM6240_10_10_TEXT "\0"
"\x00\x20 " ENUM6240_00_20_TEXT "\0"
"\x20\x20 " ENUM6240_20_20_TEXT "\0"
"\x00\x80 " ENUM6240_00_80_TEXT "\0"
"\x80\x80 " ENUM6240_80_80_TEXT
};

// Konfiguration - KonfigRG2

const char ENUM6250[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6250_00_01_TEXT "\0"
"\x01\x01 " ENUM6250_01_01_TEXT "\0"
"\x00\x02 " ENUM6250_00_02_TEXT "\0"
"\x02\x02 " ENUM6250_02_02_TEXT "\0"
"\x00\x0B " ENUM6250_00_0B_TEXT "\0"
"\x04\x0B " ENUM6250_04_0B_TEXT "\0"
"\x08\x0B " ENUM6250_08_0B_TEXT "\0"
"\x00\x30 " ENUM6250_00_30_TEXT "\0"
"\x10\x30 " ENUM6250_10_30_TEXT "\0"
"\x20\x30 " ENUM6250_20_30_TEXT
};

// Konfiguration - KonfigRG3

const char ENUM6260[] PROGMEM_LATEST = {
"\x01\x1F " ENUM6260_01_1F_TEXT "\0"
"\x02\x1F " ENUM6260_02_1F_TEXT "\0"
"\x03\x1F " ENUM6260_03_1F_TEXT "\0"
"\x04\x1F " ENUM6260_04_1F_TEXT "\0"
"\x05\x1F " ENUM6260_05_1F_TEXT "\0"
"\x06\x1F " ENUM6260_06_1F_TEXT "\0"
"\x07\x1F " ENUM6260_07_1F_TEXT "\0"
"\x00\x20 " ENUM6260_00_20_TEXT "\0"
"\x20\x20 " ENUM6260_20_20_TEXT "\0"
"\x00\x40 " ENUM6260_00_40_TEXT "\0"
"\x40\x40 " ENUM6260_40_40_TEXT "\0"
"\x00\x80 " ENUM6260_00_80_TEXT "\0"
"\x80\x80 " ENUM6260_80_80_TEXT
};

// Konfiguration - KonfigRG4

const char ENUM6270[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6270_00_01_TEXT "\0"
"\x01\x01 " ENUM6270_01_01_TEXT "\0"
"\x00\x02 " ENUM6270_00_02_TEXT "\0"
"\x02\x02 " ENUM6270_02_02_TEXT "\0"
"\x00\x04 " ENUM6270_00_04_TEXT "\0"
"\x04\x04 " ENUM6270_04_04_TEXT "\0"
"\x00\xE0 " ENUM6270_00_E0_TEXT "\0"
"\x20\xE0 " ENUM6270_20_E0_TEXT "\0"
"\x40\xE0 " ENUM6270_40_E0_TEXT "\0"
"\x60\xE0 " ENUM6270_60_E0_TEXT
};

const char ENUM6272[] PROGMEM_LATEST = {
"\x00 " ENUM6272_00_TEXT "\0"
"\x06 " ENUM6272_06_TEXT "\0"
"\x07 " ENUM6272_07_TEXT "\0"
"\x08 " ENUM6272_08_TEXT "\0"
"\x09 " ENUM6272_09_TEXT "\0"
"\x0B " ENUM6272_0B_TEXT "\0"
"\x0C " ENUM6272_0C_TEXT "\0"
"\x0D " ENUM6272_0D_TEXT "\0"
"\x0E " ENUM6272_0E_TEXT "\0"
"\x15 " ENUM6272_15_TEXT "\0"
"\x18 " ENUM6272_18_TEXT "\0"
};

// Konfiguration - KonfigRG5

const char ENUM6280[] PROGMEM_LATEST = {
"\x00\x03 " ENUM6280_00_03_TEXT "\0"
"\x01\x03 " ENUM6280_01_03_TEXT "\0"
"\x02\x03 " ENUM6280_02_03_TEXT "\0"
"\x03\x03 " ENUM6280_03_03_TEXT "\0"
"\x00\x04 " ENUM6280_00_04_TEXT "\0"
"\x04\x04 " ENUM6280_04_04_TEXT "\0"
"\x00\xF8 " ENUM6280_00_F8_TEXT
};

// Konfiguration - KonfigRG6

const char ENUM6290[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6290_00_01_TEXT "\0"
"\x01\x01 " ENUM6290_01_01_TEXT "\0"
"\x00\x02 " ENUM6290_00_02_TEXT "\0"
"\x02\x02 " ENUM6290_02_02_TEXT "\0"
"\x00\x04 " ENUM6290_00_04_TEXT "\0"
"\x04\x04 " ENUM6290_04_04_TEXT "\0"
"\x00\x08 " ENUM6290_00_08_TEXT "\0"
"\x08\x08 " ENUM6290_08_08_TEXT "\0"
"\x00\x20 " ENUM6290_00_20_TEXT "\0"
"\x20\x20 " ENUM6290_20_20_TEXT "\0"
"\x00\x40 " ENUM6290_00_40_TEXT "\0"
"\x40\x40 " ENUM6290_40_40_TEXT "\0"
"\x00\x80 " ENUM6290_00_80_TEXT "\0"
"\x80\x80 " ENUM6290_80_80_TEXT
};

// Konfiguration - KonfigRG7

const char ENUM6300[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6300_00_01_TEXT "\0"
"\x01\x01 " ENUM6300_01_01_TEXT "\0"
"\x00\x02 " ENUM6300_00_02_TEXT "\0"
"\x02\x02 " ENUM6300_02_02_TEXT "\0"
"\x00\x04 " ENUM6300_00_04_TEXT "\0"
"\x04\x04 " ENUM6300_04_04_TEXT "\0"
"\x00\x18 " ENUM6300_00_18_TEXT "\0"
"\x08\x18 " ENUM6300_08_18_TEXT "\0"
"\x10\x18 " ENUM6300_10_18_TEXT "\0"
"\x00\x20 " ENUM6300_00_20_TEXT "\0"
"\x20\x20 " ENUM6300_20_20_TEXT "\0"
"\x00\x40 " ENUM6300_00_40_TEXT "\0"
"\x40\x40 " ENUM6300_40_40_TEXT "\0"
"\x00\x80 " ENUM6300_00_80_TEXT "\0"
"\x80\x80 " ENUM6300_80_80_TEXT
};

// Konfiguration - KonfigRG8

const char ENUM6310[] PROGMEM_LATEST = {
"\x00\x0F " ENUM6310_00_0F_TEXT "\0"
"\x01\x0F " ENUM6310_01_0F_TEXT "\0"
"\x02\x0F " ENUM6310_02_0F_TEXT "\0"
"\x00\x10 " ENUM6310_00_10_TEXT "\0"
"\x10\x10 " ENUM6310_10_10_TEXT "\0"
"\x00\x20 " ENUM6310_00_20_TEXT "\0"
"\x20\x20 " ENUM6310_20_20_TEXT "\0"
"\x00\x40 " ENUM6310_00_40_TEXT "\0"
"\x40\x40 " ENUM6310_40_40_TEXT
};

// Konfiguration - KonfigRG10

const char ENUM6330[] PROGMEM_LATEST = {
"\x00\x01 " ENUM6330_00_01_TEXT "\0"
"\x01\x01 " ENUM6330_01_01_TEXT "\0"
"\x00\x02 " ENUM6330_00_02_TEXT "\0"
"\x02\x02 " ENUM6330_02_02_TEXT "\0"
"\x00\x04 " ENUM6330_00_04_TEXT "\0"
"\x04\x04 " ENUM6330_04_04_TEXT "\0"
"\x00\x08 " ENUM6330_00_08_TEXT "\0"
"\x08\x08 " ENUM6330_08_08_TEXT "\0"
"\x00\x10 " ENUM6330_00_10_TEXT "\0"
"\x10\x10 " ENUM6330_10_10_TEXT "\0"
"\x00\x20 " ENUM6330_00_20_TEXT "\0"
"\x20\x20 " ENUM6330_20_20_TEXT "\0"
"\x00\x40 " ENUM6330_00_40_TEXT "\0"
"\x40\x40 " ENUM6330_40_40_TEXT
};

// Konfiguration - Relaisausgang QX35  //FUJITSU
const char ENUM6375[] PROGMEM_LATEST = {
"\x00 " ENUM6375_00_TEXT "\0"
"\x02 " ENUM6375_02_TEXT "\0"
"\x03 " ENUM6375_03_TEXT "\0"
"\x04 " ENUM6375_04_TEXT "\0"
"\x05 " ENUM6375_05_TEXT "\0"
"\x06 " ENUM6375_06_TEXT "\0"
"\x07 " ENUM6375_07_TEXT "\0"
"\x08 " ENUM6375_08_TEXT "\0"
"\x09 " ENUM6375_09_TEXT "\0"
"\x0a " ENUM6375_0a_TEXT "\0"
"\x0b " ENUM6375_0b_TEXT "\0"
"\x0c " ENUM6375_0c_TEXT "\0"
"\x0d " ENUM6375_0d_TEXT "\0"
"\x0e " ENUM6375_0e_TEXT "\0"
"\x0f " ENUM6375_0f_TEXT "\0"
"\x10 " ENUM6375_10_TEXT "\0"
"\x11 " ENUM6375_11_TEXT "\0"
"\x12 " ENUM6375_12_TEXT "\0"
"\x13 " ENUM6375_13_TEXT "\0"
"\x14 " ENUM6375_14_TEXT "\0"
"\x15 " ENUM6375_15_TEXT "\0"
"\x16 " ENUM6375_16_TEXT "\0"
"\x17 " ENUM6375_17_TEXT "\0"
"\x18 " ENUM6375_18_TEXT "\0"
"\x19 " ENUM6375_19_TEXT "\0"
"\x1a " ENUM6375_1a_TEXT "\0"
"\x1b " ENUM6375_1b_TEXT "\0"
"\x1c " ENUM6375_1c_TEXT "\0"
"\x1d " ENUM6375_1d_TEXT "\0"
"\x1e " ENUM6375_1e_TEXT "\0"
"\x1f " ENUM6375_1f_TEXT "\0"
"\x20 " ENUM6375_20_TEXT "\0"
"\x21 " ENUM6375_21_TEXT "\0"
"\x22 " ENUM6375_22_TEXT "\0"
"\x23 " ENUM6375_23_TEXT "\0"
"\x24 " ENUM6375_24_TEXT "\0"
"\x25 " ENUM6375_25_TEXT "\0"
"\x26 " ENUM6375_26_TEXT "\0"
"\x27 " ENUM6375_27_TEXT "\0"
"\x28 " ENUM6375_28_TEXT "\0"
"\x29 " ENUM6375_29_TEXT "\0"
"\x2a " ENUM6375_2a_TEXT "\0"
"\x2b " ENUM6375_2b_TEXT "\0"
"\x2c " ENUM6375_2c_TEXT "\0"
"\x2d " ENUM6375_2d_TEXT "\0"
"\x2e " ENUM6375_2e_TEXT "\0"
"\x2f " ENUM6375_2f_TEXT "\0"
"\x30 " ENUM6375_30_TEXT "\0"
"\x31 " ENUM6375_31_TEXT "\0"
"\x32 " ENUM6375_32_TEXT "\0"
"\x33 " ENUM6375_33_TEXT "\0"
"\x34 " ENUM6375_34_TEXT "\0"
"\x35 " ENUM6375_35_TEXT "\0"
"\x36 " ENUM6375_36_TEXT "\0"
"\x37 " ENUM6375_37_TEXT "\0"
"\x38 " ENUM6375_38_TEXT "\0"
"\x39 " ENUM6375_39_TEXT "\0"
"\x3a " ENUM6375_3a_TEXT "\0"
"\x3b " ENUM6375_3b_TEXT "\0"
"\x3c " ENUM6375_3c_TEXT
};

// Konfiguration - Funktion Eingang H33  //FUJITSU
const char ENUM6420[] PROGMEM_LATEST = {
"\x00 " ENUM6420_00_TEXT "\0"
"\x01 " ENUM6420_01_TEXT "\0"
"\x02 " ENUM6420_02_TEXT "\0"
"\x03 " ENUM6420_03_TEXT "\0"
"\x04 " ENUM6420_04_TEXT "\0"
"\x05 " ENUM6420_05_TEXT "\0"
"\x06 " ENUM6420_06_TEXT "\0"
"\x07 " ENUM6420_07_TEXT "\0"
"\x08 " ENUM6420_08_TEXT "\0"
"\x09 " ENUM6420_09_TEXT "\0"
"\x0a " ENUM6420_0a_TEXT "\0"
"\x0b " ENUM6420_0b_TEXT "\0"
"\x0c " ENUM6420_0c_TEXT "\0"
"\x0d " ENUM6420_0d_TEXT
};

#define ENUM6421 ENUM5951               // Konfiguration - Wirksinn Kontakt H33 //FUJITSU

// LPB   - Busspeisung Funktion
const char ENUM6604[] PROGMEM_LATEST = {
"\x00 " ENUM6604_00_TEXT "\0"
"\x01 " ENUM6604_01_TEXT
};

// LPB   - LPBKonfig0

const char ENUM6606[] PROGMEM_LATEST = {
"\x00\x03 " ENUM6606_00_03_TEXT "\0"
"\x01\x03 " ENUM6606_01_03_TEXT "\0"
"\x02\x03 " ENUM6606_02_03_TEXT "\0"
"\x03\x03 " ENUM6606_03_03_TEXT "\0"
"\x00\x04 " ENUM6606_00_04_TEXT "\0"
"\x04\x04 " ENUM6606_04_04_TEXT "\0"
"\x00\x08 " ENUM6606_00_08_TEXT "\0"
"\x08\x08 " ENUM6606_08_08_TEXT "\0"
"\x00\x10 " ENUM6606_00_10_TEXT "\0"
"\x10\x10 " ENUM6606_10_10_TEXT "\0"
"\x00\x60 " ENUM6606_00_60_TEXT "\0"
"\x20\x60 " ENUM6606_20_60_TEXT "\0"
"\x40\x60 " ENUM6606_40_60_TEXT "\0"
"\x00\x80 " ENUM6606_00_80_TEXT "\0"
"\x80\x80 " ENUM6606_80_80_TEXT
};

// LPB   - Wirkbereich Umschaltungen
const char ENUM6620[] PROGMEM_LATEST = {
"\x00 " ENUM6620_00_TEXT "\0"
"\x01 " ENUM6620_01_TEXT "\0"
"\xff " ENUM6620_ff_TEXT
};

// LPB   - Sommerumschaltung
const char ENUM6621[] PROGMEM_LATEST = {
"\x00 " ENUM6621_00_TEXT "\0"
"\x01 " ENUM6621_01_TEXT "\0"
"\xff " ENUM6621_ff_TEXT
};

const char ENUM6623[] PROGMEM_LATEST = {
"\x00 " ENUM6623_00_TEXT "\0"
"\x01 " ENUM6623_01_TEXT
};

const char ENUM6624[] PROGMEM_LATEST = { // numerical values are hypothetical
"\x00 " ENUM6624_00_TEXT "\0"
"\x01 " ENUM6624_01_TEXT
};

// LPB   - Trinkwasserzuordnung
// Texts in the ACS Programm: "Eigener Regler", "Alle Regler im eigenen Segment", "Alle Regler im Verbund"
const char ENUM6625[] PROGMEM_LATEST = {
"\x00 " ENUM6625_00_TEXT "\0"
"\x01 " ENUM6625_01_TEXT "\0"
"\x02 " ENUM6625_02_TEXT
};

#define ENUM6627 ENUM6623

const char ENUM6630[] PROGMEM_LATEST = { // numerical values are hypothetical
"\x01 " ENUM6630_01_TEXT "\0"
"\x02 " ENUM6630_02_TEXT
};

const char ENUM6631[] PROGMEM_LATEST = {	// numerical values are hypothetical
"\x00 " ENUM6631_00_TEXT "\0"
"\x01 " ENUM6631_01_TEXT "\0"
"\x02 " ENUM6631_02_TEXT
};

// LPB   - Uhrbetrieb
const char ENUM6640[] PROGMEM_LATEST = {
"\x00 " ENUM6640_00_TEXT "\0"
"\x01 " ENUM6640_01_TEXT "\0"
"\x02 " ENUM6640_02_TEXT "\0"
"\x03 " ENUM6640_03_TEXT
};

// FA Phase
const char ENUM6706[] PROGMEM_LATEST = {
"\x01 " ENUM6706_01_TEXT "\0"
"\x02 " ENUM6706_02_TEXT "\0"
"\x00 " ENUM6706_00_TEXT "\0"
"\x03 " ENUM6706_03_TEXT "\0"
"\x04 " ENUM6706_04_TEXT "\0"
"\x05 " ENUM6706_05_TEXT "\0"
"\x06 " ENUM6706_06_TEXT "\0"
"\x07 " ENUM6706_07_TEXT "\0"
"\x0a " ENUM6706_0a_TEXT "\0"
"\x0b " ENUM6706_0b_TEXT "\0"
"\x0c " ENUM6706_0c_TEXT "\0"
"\x14 " ENUM6706_14_TEXT "\0"
"\x15 " ENUM6706_15_TEXT "\0"
"\x16 " ENUM6706_16_TEXT "\0"
"\x63 " ENUM6706_63_TEXT
};

// !TODO! ProgNo 6670 is not defined elsewhere
const char ENUM6670[] PROGMEM_LATEST = {
"\x00 " ENUM6670_00_TEXT "\0"
"\x01 " ENUM6670_01_TEXT "\0"
"\x02 " ENUM6670_02_TEXT
};

#define ENUM7119 ENUM2920    // ProgNr 7119 "Ökofunktion" FUJITSU

const char ENUM7131[] PROGMEM_LATEST = {
"\x01 " ENUM7131_01_TEXT "\0"         // ENUM-Wert überprüfen!
"\x02 " ENUM7131_02_TEXT "\0"
"\x03 " ENUM7131_03_TEXT  // ENUM-Wert überprüfen!
};

const char ENUM7142[] PROGMEM_LATEST = {
"\x01 " ENUM7142_01_TEXT "\0"
"\x02 " ENUM7142_02_TEXT
};

const char ENUM7147[] PROGMEM_LATEST = {
"\x00 " ENUM7147_00_TEXT "\0"
"\x01 " ENUM7147_01_TEXT "\0"
"\x02 " ENUM7147_02_TEXT "\0"
"\x03 " ENUM7147_03_TEXT "\0"
"\x04 " ENUM7147_04_TEXT
}; // todo Hinweis: x00 Keine ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM7252[] PROGMEM_LATEST = {
"\x00 " ENUM7252_00_TEXT "\0"
"\x01 " ENUM7252_01_TEXT "\0"
"\x02 " ENUM7252_02_TEXT
};

// Konfiguration Erweit'module - Relaisausgang QX21 Modul 2
const char ENUM7376[] PROGMEM_LATEST = {
"\x00 " ENUM7376_00_TEXT "\0"
"\x01 " ENUM7376_01_TEXT "\0"
"\x02 " ENUM7376_02_TEXT "\0"
"\x03 " ENUM7376_03_TEXT "\0"
"\x04 " ENUM7376_04_TEXT "\0"
"\x05 " ENUM7376_05_TEXT "\0"
"\x06 " ENUM7376_06_TEXT "\0"
"\x07 " ENUM7376_07_TEXT "\0"
"\x08 " ENUM7376_08_TEXT "\0"
"\x09 " ENUM7376_09_TEXT "\0"
"\x0a " ENUM7376_0a_TEXT "\0"
"\x0b " ENUM7376_0b_TEXT "\0"
"\x0c " ENUM7376_0c_TEXT "\0"
"\x0d " ENUM7376_0d_TEXT "\0"
"\x0e " ENUM7376_0e_TEXT "\0"
"\x0f " ENUM7376_0f_TEXT "\0"
"\x10 " ENUM7376_10_TEXT "\0"
"\x11 " ENUM7376_11_TEXT "\0"
"\x12 " ENUM7376_12_TEXT "\0"
"\x13 " ENUM7376_13_TEXT "\0"
"\x14 " ENUM7376_14_TEXT "\0"
"\x15 " ENUM7376_15_TEXT "\0"
"\x16 " ENUM7376_16_TEXT "\0"
"\x17 " ENUM7376_17_TEXT "\0"
"\x19 " ENUM7376_19_TEXT "\0"
"\x1a " ENUM7376_1a_TEXT "\0"
"\x1b " ENUM7376_1b_TEXT "\0"
"\x1c " ENUM7376_1c_TEXT "\0"
"\x1d " ENUM7376_1d_TEXT "\0"
"\x21 " ENUM7376_21_TEXT "\0"
"\x28 " ENUM7376_28_TEXT "\0"
"\x29 " ENUM7376_29_TEXT };


const char ENUM7425[] PROGMEM_LATEST = {
"\x00 " ENUM7425_00_TEXT "\0"
"\x01 " ENUM7425_01_TEXT
};

// Ein-/Ausgangstest - Relaistest
const char ENUM7700[] PROGMEM_LATEST = {
"\x00 " ENUM7700_00_TEXT "\0"
"\x01 " ENUM7700_01_TEXT "\0"
"\x02 " ENUM7700_02_TEXT "\0"
"\x03 " ENUM7700_03_TEXT "\0"
"\x04 " ENUM7700_04_TEXT "\0"
"\x05 " ENUM7700_05_TEXT "\0"
"\x06 " ENUM7700_06_TEXT "\0"
"\x07 " ENUM7700_07_TEXT "\0"
"\x08 " ENUM7700_08_TEXT "\0"
"\x09 " ENUM7700_09_TEXT "\0"
"\x0a " ENUM7700_0a_TEXT "\0"
"\x0b " ENUM7700_0b_TEXT "\0"
"\x0c " ENUM7700_0c_TEXT "\0"
"\x0d " ENUM7700_0d_TEXT "\0"
"\x0e " ENUM7700_0e_TEXT "\0"
"\x0f " ENUM7700_0f_TEXT "\0"
"\x10 " ENUM7700_10_TEXT "\0"
"\x11 " ENUM7700_11_TEXT "\0"
"\x12 " ENUM7700_12_TEXT "\0"
"\x13 " ENUM7700_13_TEXT "\0"
"\x14 " ENUM7700_14_TEXT
};

const char ENUM7700_2[] PROGMEM_LATEST = {
"\x00 " ENUM7700_2_00_TEXT "\0"
"\x01 " ENUM7700_2_01_TEXT "\0"
"\x02 " ENUM7700_2_02_TEXT "\0"
"\x03 " ENUM7700_2_03_TEXT "\0"
"\x04 " ENUM7700_2_04_TEXT "\0"
"\x05 " ENUM7700_2_05_TEXT "\0"
"\x06 " ENUM7700_2_06_TEXT "\0"
"\x07 " ENUM7700_2_07_TEXT "\0"
"\x08 " ENUM7700_2_08_TEXT "\0"
"\x09 " ENUM7700_2_09_TEXT
};

//Eingangssignal H33  //FUJITSU
const char ENUM7999[] PROGMEM_LATEST = {
"\x00 " ENUM7999_00_TEXT "\0"
"\x01 " ENUM7999_01_TEXT "\0"
"\x02 " "?" ENUM7999_02_TEXT "\0"
"\x03 " "?" ENUM7999_03_TEXT "\0"
"\x04 " "?" ENUM7999_04_TEXT
};

// Status Heizkreis 1, 2, 3
const char ENUM8000[] PROGMEM_LATEST = {
"\x00 " ENUM8000_00_TEXT "\0"
"\x03 " ENUM8000_03_TEXT "\0"
"\x04 " ENUM8000_04_TEXT "\0"
"\x11 " ENUM8000_11_TEXT "\0"
"\x16 " ENUM8000_16_TEXT "\0"
"\x17 " ENUM8000_17_TEXT "\0"
"\x18 " ENUM8000_18_TEXT "\0"
"\x38 " ENUM8000_38_TEXT "\0"
"\x65 " ENUM8000_65_TEXT "\0"
"\x66 " ENUM8000_66_TEXT "\0"
"\x67 " ENUM8000_67_TEXT "\0"
"\x68 " ENUM8000_68_TEXT "\0"
"\x69 " ENUM8000_69_TEXT "\0"
"\x6a " ENUM8000_6a_TEXT "\0"
"\x6b " ENUM8000_6b_TEXT "\0"
"\x6c " ENUM8000_6c_TEXT "\0"
"\x6d " ENUM8000_6d_TEXT "\0"
"\x6e " ENUM8000_6e_TEXT "\0"
"\x6f " ENUM8000_6f_TEXT "\0"
"\x70 " ENUM8000_70_TEXT "\0"
"\x71 " ENUM8000_71_TEXT "\0"
"\x72 " ENUM8000_72_TEXT "\0"
"\x73 " ENUM8000_73_TEXT "\0"
"\x74 " ENUM8000_74_TEXT "\0"
"\x75 " ENUM8000_75_TEXT "\0"
"\x76 " ENUM8000_76_TEXT "\0"
"\x77 " ENUM8000_77_TEXT "\0"
"\x78 " ENUM8000_78_TEXT "\0"
"\x79 " ENUM8000_79_TEXT "\0"
"\x7a " ENUM8000_7a_TEXT};

#define ENUM8001 ENUM8000               // Status - Status Heizkreis 2
#define ENUM8002 ENUM8000               // Status - Status Heizkreis P/3


//Status Trinkwasser
const char ENUM8003[] PROGMEM_LATEST = {
"\x00 " ENUM8003_00_TEXT "\0"
"\x03 " ENUM8003_03_TEXT "\0"
"\x04 " ENUM8003_04_TEXT "\0"
"\x11 " ENUM8003_11_TEXT "\0"
"\x18 " ENUM8003_18_TEXT "\0"
"\x19 " ENUM8003_19_TEXT "\0"
"\x35 " ENUM8003_35_TEXT "\0"
"\x42 " ENUM8003_42_TEXT "\0"
"\x43 " ENUM8003_43_TEXT "\0"
"\x45 " ENUM8003_45_TEXT "\0"
"\x46 " ENUM8003_46_TEXT "\0"
"\x47 " ENUM8003_47_TEXT "\0"
"\x4b " ENUM8003_4b_TEXT "\0"
"\x4d " ENUM8003_4d_TEXT "\0"
"\x4e " ENUM8003_4e_TEXT "\0"
"\x4f " ENUM8003_4f_TEXT "\0"
"\x50 " ENUM8003_50_TEXT "\0"
"\x51 " ENUM8003_51_TEXT "\0"
"\x52 " ENUM8003_52_TEXT "\0"
"\x53 " ENUM8003_53_TEXT "\0"
"\x54 " ENUM8003_54_TEXT "\0"
"\x55 " ENUM8003_55_TEXT "\0"
"\x56 " ENUM8003_56_TEXT "\0"
"\x57 " ENUM8003_57_TEXT "\0"
"\x58 " ENUM8003_58_TEXT "\0"
"\x59 " ENUM8003_59_TEXT "\0"
"\x5a " ENUM8003_5a_TEXT "\0"
"\x5b " ENUM8003_5b_TEXT "\0"
"\x5c " ENUM8003_5c_TEXT "\0"
"\x5d " ENUM8003_5d_TEXT "\0"
"\x5e " ENUM8003_5e_TEXT "\0"
"\x5f " ENUM8003_5f_TEXT "\0"
"\x60 " ENUM8003_60_TEXT "\0"
"\x61 " ENUM8003_61_TEXT "\0"
"\x62 " ENUM8003_62_TEXT "\0"
"\x63 " ENUM8003_63_TEXT "\0"
"\x64 " ENUM8003_64_TEXT "\0"
"\xc7 " ENUM8003_c7_TEXT "\0"
"\xc8 " ENUM8003_c8_TEXT "\0"
"\xc9 " ENUM8003_c9_TEXT
};

//Status Kühlkreis 1  //FUJITSU
const char ENUM8004[] PROGMEM_LATEST = {
"\x00 " ENUM8004_00_TEXT "\0"
"\x8A " ENUM8004_8A_TEXT
};

//Status Kessel
const char ENUM8005[] PROGMEM_LATEST = {
"\x00 " ENUM8005_00_TEXT "\0"
"\x01 " ENUM8005_01_TEXT "\0"
"\x02 " ENUM8005_02_TEXT "\0"
"\x03 " ENUM8005_03_TEXT "\0"
"\x04 " ENUM8005_04_TEXT "\0"
"\x05 " ENUM8005_05_TEXT "\0"
"\x06 " ENUM8005_06_TEXT "\0"
"\x07 " ENUM8005_07_TEXT "\0"
"\x08 " ENUM8005_08_TEXT "\0"
"\x09 " ENUM8005_09_TEXT "\0"
"\x0a " ENUM8005_0a_TEXT "\0"
"\x0b " ENUM8005_0b_TEXT "\0"
"\x0c " ENUM8005_0c_TEXT "\0"
"\x0d " ENUM8005_0d_TEXT "\0"
"\x0e " ENUM8005_0e_TEXT "\0"
"\x0f " ENUM8005_0f_TEXT "\0"
"\x10 " ENUM8005_10_TEXT "\0"
"\x11 " ENUM8005_11_TEXT "\0"
"\x12 " ENUM8005_12_TEXT "\0"
"\x13 " ENUM8005_13_TEXT "\0"
"\x14 " ENUM8005_14_TEXT "\0"
"\x15 " ENUM8005_15_TEXT "\0"
"\x16 " ENUM8005_16_TEXT "\0"
"\x17 " ENUM8005_17_TEXT "\0"
"\x18 " ENUM8005_18_TEXT "\0"
"\x19 " ENUM8005_19_TEXT "\0"
"\x3b " ENUM8005_3b_TEXT "\0"
"\x7b " ENUM8005_7b_TEXT "\0"
"\xa6 " ENUM8005_a6_TEXT "\0"
"\xa7 " ENUM8005_a7_TEXT "\0"
"\xa8 " ENUM8005_a8_TEXT "\0"
"\xa9 " ENUM8005_a9_TEXT "\0"
"\xaa " ENUM8005_aa_TEXT "\0"
"\xab " ENUM8005_ab_TEXT "\0"
"\xac " ENUM8005_ac_TEXT "\0"
"\xad " ENUM8005_ad_TEXT "\0"
"\xae " ENUM8005_ae_TEXT "\0"
"\xaf " ENUM8005_af_TEXT "\0"
"\xb0 " ENUM8005_b0_TEXT "\0"
"\xc6 " ENUM8005_c6_TEXT
};

//Status Waermepumpe  //FUJITSU
const char ENUM8006[] PROGMEM_LATEST = {
"\x00 " ENUM8006_00_TEXT "\0"
"\x02 " ENUM8006_02_TEXT "\0"
"\x0A " ENUM8006_0A_TEXT "\0"      //10
"\x11 " ENUM8006_11_TEXT "\0"      //17
"\x17 " ENUM8006_17_TEXT "\0"
"\x18 " ENUM8006_18_TEXT "\0"      //24
"\x19 " ENUM8006_19_TEXT "\0"      //25
"\x1a " ENUM8006_1a_TEXT "\0"
"\x1b " ENUM8006_1b_TEXT "\0"      //27
"\x1d " ENUM8006_1d_TEXT "\0"      //29
"\x1e " ENUM8006_1e_TEXT "\0"      //30
"\x1f " ENUM8006_1f_TEXT "\0"      //31
"\x20 " ENUM8006_20_TEXT "\0"      //32
"\x21 " ENUM8006_21_TEXT "\0"      //33
"\x22 " ENUM8006_22_TEXT "\0"      //34
"\x23 " ENUM8006_23_TEXT "\0"
"\x24 " ENUM8006_24_TEXT "\0"      //36
"\x25 " ENUM8006_25_TEXT "\0"      //37
"\x26 " ENUM8006_26_TEXT "\0"
"\x27 " ENUM8006_27_TEXT "\0"      //39
"\x28 " ENUM8006_28_TEXT "\0"      //40
"\x29 " ENUM8006_29_TEXT "\0"      //41
"\x2a " ENUM8006_2a_TEXT "\0"      //42
"\x2b " ENUM8006_2b_TEXT "\0"      //43
"\x2c " ENUM8006_2c_TEXT "\0"      //44
"\x2d " ENUM8006_2d_TEXT "\0"      //45
"\x2e " ENUM8006_2e_TEXT "\0"
"\x2f " ENUM8006_2f_TEXT "\0"      //47
"\x30 " ENUM8006_30_TEXT "\0"      //48
"\x31 " ENUM8006_31_TEXT "\0"
"\x32 " ENUM8006_32_TEXT "\0"
"\x33 " ENUM8006_33_TEXT "\0"      //51
"\x7d " ENUM8006_7d_TEXT "\0"
"\x7e " ENUM8006_7e_TEXT "\0"      //126
"\x7f " ENUM8006_7f_TEXT "\0"      //127
"\x80 " ENUM8006_80_TEXT "\0"      //128
"\x81 " ENUM8006_81_TEXT "\0"      //129
"\x82 " ENUM8006_82_TEXT "\0"      //130
"\x89 " ENUM8006_89_TEXT "\0"      //137
"\x8b " ENUM8006_8b_TEXT "\0"      //139
"\x91 " ENUM8006_91_TEXT "\0"      //145
"\xb0 " ENUM8006_b0_TEXT "\0"
"\xb4 " ENUM8006_b4_TEXT "\0"      //180
"\xb5 " ENUM8006_b5_TEXT "\0"      //181
"\xb6 " ENUM8006_b6_TEXT "\0"      //182
"\xb7 " ENUM8006_b7_TEXT "\0"      //183
"\xb8 " ENUM8006_b8_TEXT "\0"      //184
"\xb9 " ENUM8006_b9_TEXT "\0"      //185
"\xba " ENUM8006_ba_TEXT "\0"      //186
"\xbb " ENUM8006_bb_TEXT "\0"      //187
"\xbc " ENUM8006_bc_TEXT "\0"      //188
"\xbd " ENUM8006_bd_TEXT "\0"      //189
"\xbe " ENUM8006_be_TEXT "\0"      //190
"\xbf " ENUM8006_bf_TEXT "\0"      //191
"\xc0 " ENUM8006_c0_TEXT "\0"      //192
"\xc1 " ENUM8006_c1_TEXT "\0"      //193
"\xc2 " ENUM8006_c2_TEXT "\0"      //194
"\xc3 " ENUM8006_c3_TEXT "\0"      //195
"\xc4 " ENUM8006_c4_TEXT "\0"      //196
"\xc5 " ENUM8006_c5_TEXT "\0"      //197
"\xc6 " ENUM8006_c6_TEXT "\0"      //198
"\xcf " ENUM8006_cf_TEXT "\0"      //207
"\xd0 " ENUM8006_d0_TEXT "\0"      //208
"\xd1 " ENUM8006_d1_TEXT "\0"      //209
"\xd2 " ENUM8006_d2_TEXT "\0"      //210
"\xeb " ENUM8006_eb_TEXT "\0"
"\xf2 " ENUM8006_f2_TEXT "\0"      //242
"\xf6 " ENUM8006_f6_TEXT "\0"      //246
"\xfe " ENUM8006_fe_TEXT "\0"      //254
"\x01\x00 " ENUM8006_01_00_TEXT "\0"      //256
"\x01\x01 " ENUM8006_01_01_TEXT "\0"      //257
"\x01\x02 " ENUM8006_01_02_TEXT "\0"      //258
"\x01\x03 " ENUM8006_01_03_TEXT "\0"      //259
"\x01\x04 " ENUM8006_01_04_TEXT "\0"      //260
"\x01\x05 " ENUM8006_01_05_TEXT "\0"      //261
"\x01\x06 " ENUM8006_01_06_TEXT "\0"      //262
"\x01\x07 " ENUM8006_01_07_TEXT "\0"      //263
"\x01\x08 " ENUM8006_01_08_TEXT "\0"      //264
"\x01\x09 " ENUM8006_01_09_TEXT "\0"      //265
"\x01\x0a " ENUM8006_01_0a_TEXT "\0"      //266
"\x01\x0b " ENUM8006_01_0b_TEXT "\0"      //267
"\x01\x0c " ENUM8006_01_0c_TEXT "\0"      //268
"\x01\x0d " ENUM8006_01_0d_TEXT "\0"      //269
"\x01\x0e " ENUM8006_01_0e_TEXT      //270
};


//Status Solar
const char ENUM8007[] PROGMEM_LATEST = {
"\x00 " ENUM8007_00_TEXT "\0"
"\x04 " ENUM8007_04_TEXT "\0"
"\x02 " ENUM8007_02_TEXT "\0"
"\x34 " ENUM8007_34_TEXT "\0"
"\x35 " ENUM8007_35_TEXT "\0"
"\x36 " ENUM8007_36_TEXT "\0"
"\x37 " ENUM8007_37_TEXT "\0"
"\x38 " ENUM8007_38_TEXT "\0"
"\x39 " ENUM8007_39_TEXT "\0"
"\x3a " ENUM8007_3a_TEXT "\0"
"\x3b " ENUM8007_3b_TEXT "\0"
"\x3c " ENUM8007_3c_TEXT "\0"
"\x3d " ENUM8007_3d_TEXT "\0"
"\x3e " ENUM8007_3e_TEXT "\0"
"\x3f " ENUM8007_3f_TEXT "\0"
"\x97 " ENUM8007_97_TEXT "\0"
"\x98 " ENUM8007_98_TEXT "\0"
"\x99 " ENUM8007_99_TEXT "\0"
"\x9a " ENUM8007_9a_TEXT
};


//Status Feststoffkessel
const char ENUM8008[] PROGMEM_LATEST = {
"\x00 " ENUM8008_00_TEXT "\0"
"\x02 " ENUM8008_02_TEXT "\0"
"\x04 " ENUM8008_04_TEXT "\0"
"\x08 " ENUM8008_08_TEXT "\0"
"\x09 " ENUM8008_09_TEXT "\0"
"\x0a " ENUM8008_0a_TEXT "\0"
"\x0b " ENUM8008_0b_TEXT "\0"
"\x0c " ENUM8008_0c_TEXT "\0"
"\x0d " ENUM8008_0d_TEXT "\0"
"\x0e " ENUM8008_0e_TEXT "\0"
"\x11 " ENUM8008_11_TEXT "\0"
"\x12 " ENUM8008_12_TEXT "\0"
"\x13 " ENUM8008_13_TEXT "\0"
"\x14 " ENUM8008_14_TEXT "\0"
"\x15 " ENUM8008_15_TEXT "\0"
"\x16 " ENUM8008_16_TEXT "\0"
"\x17 " ENUM8008_17_TEXT "\0"
"\x18 " ENUM8008_18_TEXT "\0"
"\x19 " ENUM8008_19_TEXT "\0"
"\x38 " ENUM8008_38_TEXT "\0"
"\x3a " ENUM8008_3a_TEXT "\0"
"\x3b " ENUM8008_3b_TEXT "\0"
"\x8d " ENUM8008_8d_TEXT "\0"
"\xa3 " ENUM8008_a3_TEXT "\0"
"\xa6 " ENUM8008_a6_TEXT "\0"
"\xa7 " ENUM8008_a7_TEXT "\0"
"\xa8 " ENUM8008_a8_TEXT "\0"
"\xa9 " ENUM8008_a9_TEXT "\0"
"\xaa " ENUM8008_aa_TEXT "\0"
"\xab " ENUM8008_ab_TEXT "\0"
"\xf1 " ENUM8008_f1_TEXT
};

// Status Brenner
// Text messages are taken from Installationshandbuch NovoCondens WOB 20-25
// The enum numerical values with question marks are unknown and are placeholders
// !TODO! Determine the enum numerical values

// Thision
const char ENUM8009_2[] PROGMEM_LATEST = {
"\x00 " "?" ENUM8009_2_00_TEXT "\0" // !TODO! "no text" is only an analogous deduction
"\x01 " "?" ENUM8009_2_01_TEXT "\0"        // !TODO! enum value is hypothetical
"\x02 " "?" ENUM8009_2_02_TEXT "\0"   // !TODO! enum value is hypothetical
"\x04 " ENUM8009_2_04_TEXT "\0"
"\x12 " ENUM8009_2_12_TEXT "\0"
"\xD6 " "?" ENUM8009_2_D6_TEXT "\0"
"\xDA " "?" ENUM8009_2_DA_TEXT "\0"
"\xD7 " "?" ENUM8009_2_D7_TEXT "\0"
"\xD8 " ENUM8009_2_D8_TEXT "\0"
"\x09 " "?" ENUM8009_2_09_TEXT "\0" // !TODO! enum value is hypothetical
"\xD9 " "?" ENUM8009_2_D9_TEXT "\0"
"\xDB " "?" ENUM8009_2_DB_TEXT
};

// Brötje BSW / WMS / WMC
const char ENUM8009[] PROGMEM_LATEST = {
"\x00 " "?" ENUM8009_00_TEXT "\0" // !TODO! "no text" is only an analogous deduction
"\x01 " "?" ENUM8009_01_TEXT "\0"        // !TODO! enum value is hypothetical
"\x02 " "?" ENUM8009_02_TEXT "\0"   // !TODO! enum value is hypothetical
"\x12 " ENUM8009_12_TEXT "\0"           // verifiziert an WMS (LP)
"\xD6 " ENUM8009_D6_TEXT "\0"
"\xDA " ENUM8009_DA_TEXT "\0"
"\xD7 " ENUM8009_D7_TEXT "\0"     // verifiziert an WMS (LP)
"\xD8 " ENUM8009_D8_TEXT "\0"              // verifiziert an WMS (LP)
"\x09 " "?" ENUM8009_09_TEXT "\0" // !TODO! enum value is hypothetical
"\xD9 " ENUM8009_D9_TEXT "\0"
"\xDB " ENUM8009_DB_TEXT "\0"
"\xE0 " ENUM8009_E0_TEXT "\0"               // verifiziert an WMS (LP)
"\xE1 " ENUM8009_E1_TEXT         // verifiziert an WMS (LP)
};

//Status Pufferspeicher
const char ENUM8010[] PROGMEM_LATEST = {
"\x00 " ENUM8010_00_TEXT "\0"
"\x18 " ENUM8010_18_TEXT "\0"
"\x33 " ENUM8010_33_TEXT "\0"
"\x35 " ENUM8010_35_TEXT "\0"
"\x40 " ENUM8010_40_TEXT "\0"
"\x41 " ENUM8010_41_TEXT "\0"
"\x42 " ENUM8010_42_TEXT "\0"
"\x43 " ENUM8010_43_TEXT "\0"
"\x44 " ENUM8010_44_TEXT "\0"
"\x45 " ENUM8010_45_TEXT "\0"
"\x46 " ENUM8010_46_TEXT "\0"
"\x47 " ENUM8010_47_TEXT "\0"
"\x48 " ENUM8010_48_TEXT "\0"
"\x49 " ENUM8010_49_TEXT "\0"
"\x4a " ENUM8010_4a_TEXT "\0"
"\x4b " ENUM8010_4b_TEXT "\0"
"\x4c " ENUM8010_4c_TEXT "\0"
"\x4d " ENUM8010_4d_TEXT "\0"
"\x51 " ENUM8010_51_TEXT "\0"
"\x68 " ENUM8010_68_TEXT "\0"
"\x7c " ENUM8010_7c_TEXT "\0"
"\x83 " ENUM8010_83_TEXT "\0"
"\x87 " ENUM8010_87_TEXT "\0"
"\x8e " ENUM8010_8e_TEXT "\0"
"\x8f " ENUM8010_8f_TEXT "\0"
"\x93 " ENUM8010_93_TEXT "\0"
"\xa4 " ENUM8010_a4_TEXT "\0"
"\xa5 " ENUM8010_a5_TEXT "\0"
"\xca " ENUM8010_ca_TEXT "\0"
"\xcb " ENUM8010_cb_TEXT "\0"
"\xf4 " ENUM8010_f4_TEXT
};

// Status Schwimmbad
const char ENUM8011[] PROGMEM_LATEST = {
"\x00 " ENUM8011_00_TEXT "\0"
"\x02 " ENUM8011_02_TEXT "\0"
"\x04 " ENUM8011_04_TEXT "\0"
"\x4c " ENUM8011_4c_TEXT "\0"
"\x6a " ENUM8011_6a_TEXT "\0"
"\x6e " ENUM8011_6e_TEXT "\0"
"\x89 " ENUM8011_89_TEXT "\0"
"\x9b " ENUM8011_9b_TEXT "\0"
"\x9c " ENUM8011_9c_TEXT "\0"
"\x9d " ENUM8011_9d_TEXT "\0"
"\x9e " ENUM8011_9e_TEXT "\0"
"\x9f " ENUM8011_9f_TEXT "\0"
"\xa0 " ENUM8011_a0_TEXT "\0"
"\xa1 " ENUM8011_a1_TEXT "\0"
"\xa2 " ENUM8011_a2_TEXT
};

//Status Zusatzerzeuger  //FUJITSU
const char ENUM8022[] PROGMEM_LATEST = {
"\x00 " ENUM8022_00_TEXT
};

#define ENUM8051 ENUM8006               // Status - Status Historie 1
#define ENUM8053 ENUM8051               // Status - Status Historie 2
#define ENUM8055 ENUM8051               // Status - Status Historie 3
#define ENUM8057 ENUM8051               // Status - Status Historie 4
#define ENUM8059 ENUM8051               // Status - Status Historie 5
#define ENUM8061 ENUM8051               // Status - Status Historie 6
#define ENUM8063 ENUM8051               // Status - Status Historie 7
#define ENUM8065 ENUM8051               // Status - Status Historie 8
#define ENUM8067 ENUM8051               // Status - Status Historie 9
#define ENUM8069 ENUM8051               // Status - Status Historie 10

#define ENUM8099 ENUM8006               // Status - Hauptdisplay. Achtung! 8099 kann zukünftig direkt von einem Hersteller vergeben werden, dann muss dieser Parameter "umziehen"...

// Diagnose Kaskade
const char ENUM8100[] PROGMEM_LATEST = { // numerical values are hypothetical
"\x00 " "?" ENUM8100_00_TEXT "\0"
"\x01 " "?" ENUM8100_01_TEXT "\0"
"\x02 " "?" ENUM8100_02_TEXT "\0"
"\x03 " "?" ENUM8100_03_TEXT "\0"
"\x04 " "?" ENUM8100_04_TEXT "\0"
"\x05 " "?" ENUM8100_05_TEXT "\0"
"\x06 " "?" ENUM8100_06_TEXT "\0"
"\x07 " "?" ENUM8100_07_TEXT "\0"
"\x08 " "?" ENUM8100_08_TEXT
};
#define ENUM8102 ENUM8100
#define ENUM8104 ENUM8100
#define ENUM8106 ENUM8100
#define ENUM8108 ENUM8100
#define ENUM8110 ENUM8100
#define ENUM8112 ENUM8100
#define ENUM8114 ENUM8100
#define ENUM8116 ENUM8100
#define ENUM8118 ENUM8100
#define ENUM8120 ENUM8100
#define ENUM8122 ENUM8100
#define ENUM8124 ENUM8100
#define ENUM8126 ENUM8100
#define ENUM8128 ENUM8100
#define ENUM8130 ENUM8100

// Diagnose Erzeuger - 8304 Kesselpumpe Q1
// NovoCondens WOB 20-25
// !TODO! Collect the other possible values (probably 0=Aus, 1=Ein, 255=Ein)
const char ENUM8304[] PROGMEM_LATEST = {
"\x00 " ENUM8304_00_TEXT "\0"    // precision guesswork
"\x01 " ENUM8304_01_TEXT "\0"    // precision guesswork
"\xff " ENUM8304_ff_TEXT "\0"    // vom LCD abgelesen (Python code)
"\x01\x00 " ENUM8304_01_00_TEXT
};

const char ENUM8313[] PROGMEM_LATEST = {
"\x01 " ENUM8313_01_TEXT "\0"               // verifiziert an WMS (LP)
"\x02 " ENUM8313_02_TEXT "\0"
"\x03 " ENUM8313_03_TEXT "\0"
"\x04 " ENUM8313_04_TEXT "\0"
"\x05 " ENUM8313_05_TEXT "\0"
"\x06 " ENUM8313_06_TEXT
}; // todo Hinweis: x01 ist definitiv richtig. Die anderen muessen noch verifiziert werden.

const char ENUM8390[] PROGMEM_LATEST = {
"\x01 " ENUM8390_01_TEXT "\0"
"\x02 " ENUM8390_02_TEXT "\0"
"\x03 " ENUM8390_03_TEXT "\0"        // verifiziert an WMS (LP)
"\x04 " ENUM8390_04_TEXT "\0"        // verifiziert an WMS (LP)
"\x05 " ENUM8390_05_TEXT "\0"
"\x06 " ENUM8390_06_TEXT "\0"
"\x07 " ENUM8390_07_TEXT "\0"
"\x08 " ENUM8390_08_TEXT "\0"
"\x09 " ENUM8390_09_TEXT "\0"
"\x0a " ENUM8390_0a_TEXT "\0"
"\x0b " ENUM8390_0b_TEXT "\0"
"\x0c " ENUM8390_0c_TEXT "\0"
"\x0d " ENUM8390_0d_TEXT "\0"        // verifiziert an WMS (LP)
"\x0e " ENUM8390_0e_TEXT "\0"
"\x0f " ENUM8390_0f_TEXT "\0"
"\x10 " ENUM8390_10_TEXT "\0"        // verifiziert an WMS (LP)
"\x11 " ENUM8390_11_TEXT "\0"
"\x12 " ENUM8390_12_TEXT "\0"
"\x13 " ENUM8390_13_TEXT "\0"
"\x14 " ENUM8390_14_TEXT "\0"
"\x15 " ENUM8390_15_TEXT "\0"
"\x16 " ENUM8390_16_TEXT "\0"
"\x17 " ENUM8390_17_TEXT "\0"
"\x18 " ENUM8390_18_TEXT           // verifiziert an WMS (LP)
};

// Diagnose Verbraucher 8749 Raumthermostat 1
// Texts taken from manual
const char ENUM8749[] PROGMEM_LATEST = {     // numerical values unverified
"\x00 " ENUM8749_00_TEXT "\0"
"\x01 " ENUM8749_01_TEXT
};
#define ENUM8779 ENUM8749  // 8779 Raumthermostat 2

// PPS Betriebsart
const char ENUM15010[] PROGMEM_LATEST = {
"\x00 " ENUM15010_00_TEXT "\0"
"\x01 " ENUM15010_01_TEXT "\0"
"\x02 " ENUM15010_02_TEXT
};

const char ENUM15062[] PROGMEM_LATEST = {
"\x52 " ENUM15062_52_TEXT "\0"
"\x53 " ENUM15062_53_TEXT
};

const char ENUM15063[] PROGMEM_LATEST = {
"\x00\x01 " ENUM702_04_TEXT "\0"
"\x01\x01 " ENUM702_04_TEXT "\0"
"\x00\x02 " ENUM15063_00_02_TEXT "\0"
"\x02\x02 " ENUM15063_02_02_TEXT "\0"
"\x00\x04 " ENUM702_04_TEXT "\0"
"\x04\x04 " ENUM702_04_TEXT "\0"
"\x00\x08 " ENUM15063_00_08_TEXT "\0"
"\x08\x08 " ENUM15063_08_08_TEXT "\0"
"\x00\x10 " ENUM15063_00_10_TEXT "\0"
"\x10\x10 " ENUM15063_10_10_TEXT
};

/* SPECIAL ENUM tables */
//Fehlercodes
const char ENUM_ERROR[] PROGMEM_LATEST = {
"\x00 " ENUM_ERROR_00_TEXT "\0"
"\x0a " ENUM_ERROR_0a_TEXT "\0"
"\x14 " ENUM_ERROR_14_TEXT "\0"
"\x19 " ENUM_ERROR_19_TEXT "\0"
"\x1a " ENUM_ERROR_1a_TEXT "\0"
"\x1c " ENUM_ERROR_1c_TEXT "\0"
"\x1e " ENUM_ERROR_1e_TEXT "\0"
"\x1f " ENUM_ERROR_1f_TEXT "\0"
"\x20 " ENUM_ERROR_20_TEXT "\0"
"\x26 " ENUM_ERROR_26_TEXT "\0"
"\x28 " ENUM_ERROR_28_TEXT "\0"
"\x2e " ENUM_ERROR_2e_TEXT "\0"
"\x2f " ENUM_ERROR_2f_TEXT "\0"
"\x32 " ENUM_ERROR_32_TEXT "\0"
"\x34 " ENUM_ERROR_34_TEXT "\0"
"\x36 " ENUM_ERROR_36_TEXT "\0"
"\x39 " ENUM_ERROR_39_TEXT "\0"
"\x3c " ENUM_ERROR_3c_TEXT "\0"
"\x41 " ENUM_ERROR_41_TEXT "\0"
"\x44 " ENUM_ERROR_44_TEXT "\0"
"\x46 " ENUM_ERROR_46_TEXT "\0"
"\x47 " ENUM_ERROR_47_TEXT "\0"
"\x48 " ENUM_ERROR_48_TEXT "\0"
"\x49 " ENUM_ERROR_49_TEXT "\0"
"\x4a " ENUM_ERROR_4a_TEXT "\0"
"\x4d " ENUM_ERROR_4d_TEXT "\0"
"\x51 " ENUM_ERROR_51_TEXT "\0"
"\x52 " ENUM_ERROR_52_TEXT "\0"
"\x53 " ENUM_ERROR_53_TEXT "\0"
"\x54 " ENUM_ERROR_54_TEXT "\0"
"\x55 " ENUM_ERROR_55_TEXT "\0"
"\x58 " ENUM_ERROR_58_TEXT "\0"
"\x5b " ENUM_ERROR_5b_TEXT "\0"
"\x5c " ENUM_ERROR_5c_TEXT "\0"
"\x5f " ENUM_ERROR_5f_TEXT "\0"
"\x62 " ENUM_ERROR_62_TEXT "\0"
"\x63 " ENUM_ERROR_63_TEXT "\0"
"\x64 " ENUM_ERROR_64_TEXT "\0"
"\x66 " ENUM_ERROR_66_TEXT "\0"
"\x69 " ENUM_ERROR_69_TEXT "\0"
"\x6d " ENUM_ERROR_6d_TEXT "\0"
"\x6e " ENUM_ERROR_6e_TEXT "\0"
"\x6f " ENUM_ERROR_6f_TEXT "\0"
"\x74 " ENUM_ERROR_74_TEXT "\0"
"\x75 " ENUM_ERROR_75_TEXT "\0"
"\x76 " ENUM_ERROR_76_TEXT "\0"
"\x77 " ENUM_ERROR_77_TEXT "\0"
"\x79 " ENUM_ERROR_79_TEXT "\0"
"\x7a " ENUM_ERROR_7a_TEXT "\0"
"\x7e " ENUM_ERROR_7e_TEXT "\0"
"\x7f " ENUM_ERROR_7f_TEXT "\0"
"\x80 " ENUM_ERROR_80_TEXT "\0"
"\x81 " ENUM_ERROR_81_TEXT "\0"
"\x83 " ENUM_ERROR_83_TEXT "\0"
"\x84 " ENUM_ERROR_84_TEXT "\0"
"\x85 " ENUM_ERROR_85_TEXT "\0"
"\x8c " ENUM_ERROR_8c_TEXT "\0"
"\x92 " ENUM_ERROR_92_TEXT "\0"
"\x94 " ENUM_ERROR_94_TEXT "\0"
"\x97 " ENUM_ERROR_97_TEXT "\0"
"\x98 " ENUM_ERROR_98_TEXT "\0"
"\x99 " ENUM_ERROR_99_TEXT "\0"
"\x9a " ENUM_ERROR_9a_TEXT "\0"
"\xa0 " ENUM_ERROR_a0_TEXT "\0"
"\xa1 " ENUM_ERROR_a1_TEXT "\0"
"\xa2 " ENUM_ERROR_a2_TEXT "\0"
"\xa3 " ENUM_ERROR_a3_TEXT "\0"
"\xa4 " ENUM_ERROR_a4_TEXT "\0"
"\xa6 " ENUM_ERROR_a6_TEXT "\0"
"\xab " ENUM_ERROR_ab_TEXT "\0"
"\xac " ENUM_ERROR_ac_TEXT "\0"
"\xad " ENUM_ERROR_ad_TEXT "\0"
"\xae " ENUM_ERROR_ae_TEXT "\0"
"\xb0 " ENUM_ERROR_b0_TEXT "\0"
"\xb1 " ENUM_ERROR_b1_TEXT "\0"
"\xb2 " ENUM_ERROR_b2_TEXT "\0"
"\xb3 " ENUM_ERROR_b3_TEXT "\0"
"\xb4 " ENUM_ERROR_b4_TEXT "\0"
"\xb5 " ENUM_ERROR_b5_TEXT "\0"
"\xb6 " ENUM_ERROR_b6_TEXT "\0"
"\xb7 " ENUM_ERROR_b7_TEXT "\0"
"\xb8 " ENUM_ERROR_b8_TEXT "\0"
"\xb9 " ENUM_ERROR_b9_TEXT "\0"
"\xb3 " ENUM_ERROR_be_TEXT "\0"
"\xbf " ENUM_ERROR_bf_TEXT "\0"
"\xc0 " ENUM_ERROR_c0_TEXT "\0"
"\xc1 " ENUM_ERROR_c1_TEXT "\0"
"\xcf " ENUM_ERROR_cf_TEXT "\0"
"\xd9 " ENUM_ERROR_d9_TEXT "\0"
"\xda " ENUM_ERROR_da_TEXT "\0"
"\xde " ENUM_ERROR_de_TEXT "\0"
"\xf1 " ENUM_ERROR_f1_TEXT "\0"
"\xf2 " ENUM_ERROR_f2_TEXT "\0"
"\xf3 " ENUM_ERROR_f3_TEXT "\0"
"\x01\x04 " ENUM_ERROR_01_04_TEXT "\0"
"\x01\x0e " ENUM_ERROR_01_0e_TEXT "\0"
"\x01\x3d " ENUM_ERROR_01_3d_TEXT "\0"
"\x01\x40 " ENUM_ERROR_01_40_TEXT "\0"
"\x01\x41 " ENUM_ERROR_01_41_TEXT "\0"
"\x01\x42 " ENUM_ERROR_01_42_TEXT "\0"
"\x01\x43 " ENUM_ERROR_01_43_TEXT "\0"
"\x01\x44 " ENUM_ERROR_01_44_TEXT "\0"
"\x01\x45 " ENUM_ERROR_01_45_TEXT "\0"
"\x01\x46 " ENUM_ERROR_01_46_TEXT "\0"
"\x01\x47 " ENUM_ERROR_01_47_TEXT "\0"
"\x01\x48 " ENUM_ERROR_01_48_TEXT "\0"
"\x01\x49 " ENUM_ERROR_01_49_TEXT "\0"
"\x01\x4a " ENUM_ERROR_01_4a_TEXT "\0"
"\x01\x4b " ENUM_ERROR_01_4b_TEXT "\0"
"\x01\x4c " ENUM_ERROR_01_4c_TEXT "\0"
"\x01\x4d " ENUM_ERROR_01_4d_TEXT "\0"
"\x01\x4e " ENUM_ERROR_01_4e_TEXT "\0"
"\x01\x4f " ENUM_ERROR_01_4f_TEXT "\0"
"\x01\x50 " ENUM_ERROR_01_50_TEXT "\0"
"\x01\x51 " ENUM_ERROR_01_51_TEXT "\0"
"\x01\x52 " ENUM_ERROR_01_52_TEXT "\0"
"\x01\x53 " ENUM_ERROR_01_53_TEXT "\0"
"\x01\x54 " ENUM_ERROR_01_54_TEXT "\0"
"\x01\x55 " ENUM_ERROR_01_55_TEXT "\0"
"\x01\x56 " ENUM_ERROR_01_56_TEXT "\0"
"\x01\x57 " ENUM_ERROR_01_57_TEXT "\0"
"\x01\x58 " ENUM_ERROR_01_58_TEXT "\0"
"\x01\x59 " ENUM_ERROR_01_59_TEXT "\0"
"\x01\x5a " ENUM_ERROR_01_5a_TEXT "\0"
"\x01\x5b " ENUM_ERROR_01_5b_TEXT "\0"
"\x01\x5c " ENUM_ERROR_01_5c_TEXT "\0"
"\x01\x5d " ENUM_ERROR_01_5d_TEXT "\0"
"\x01\x5e " ENUM_ERROR_01_5e_TEXT "\0"
"\x01\x5f " ENUM_ERROR_01_5f_TEXT "\0"
"\x01\x60 " ENUM_ERROR_01_60_TEXT "\0"
"\x01\x61 " ENUM_ERROR_01_61_TEXT "\0"
"\x01\x65 " ENUM_ERROR_01_65_TEXT "\0"
"\x01\x6e " ENUM_ERROR_01_6e_TEXT "\0"
"\x01\x6f " ENUM_ERROR_01_6f_TEXT "\0"
"\x01\x72 " ENUM_ERROR_01_72_TEXT "\0"  //FUJITSU
"\x01\x73 " ENUM_ERROR_01_73_TEXT "\0"
"\x01\x74 " ENUM_ERROR_01_74_TEXT "\0"
"\x01\x75 " ENUM_ERROR_01_75_TEXT "\0"
"\x01\x7a " ENUM_ERROR_01_7a_TEXT "\0"
"\x01\x7e " ENUM_ERROR_01_7e_TEXT "\0"
"\x01\x80 " ENUM_ERROR_01_80_TEXT "\0"
"\x01\x81 " ENUM_ERROR_01_81_TEXT "\0"
"\x01\x82 " ENUM_ERROR_01_82_TEXT "\0"
"\x01\x83 " ENUM_ERROR_01_83_TEXT "\0"
"\x01\xab " ENUM_ERROR_01_ab_TEXT "\0"
"\x01\xb0 " ENUM_ERROR_01_b0_TEXT
};

const char ENUM_SWCODE[] PROGMEM_LATEST = {
"\x11 " ENUM_SWCODE_11_TEXT "\0"
"\x53 " ENUM_SWCODE_53_TEXT "\0"
"\x5f " ENUM_SWCODE_5f_TEXT "\0"
"\x60 " ENUM_SWCODE_60_TEXT "\0"
"\x61 " ENUM_SWCODE_61_TEXT "\0"
"\x69 " ENUM_SWCODE_69_TEXT "\0"
"\x6e " ENUM_SWCODE_6e_TEXT "\0"
"\x73 " ENUM_SWCODE_73_TEXT "\0"
"\x81 " ENUM_SWCODE_81_TEXT "\0"
"\xa2 " ENUM_SWCODE_a2_TEXT "\0"
"\xa8 " ENUM_SWCODE_a8_TEXT "\0"
"\xa9 " ENUM_SWCODE_a9_TEXT "\0"
"\xaa " ENUM_SWCODE_aa_TEXT "\0"
"\x01\x03 " ENUM_SWCODE_01_03_TEXT "\0"
"\x01\x19 " ENUM_SWCODE_01_19_TEXT "\0"
"\x01\x20 " ENUM_SWCODE_01_20_TEXT "\0"
"\x01\x45 " ENUM_SWCODE_01_45_TEXT "\0"
"\x01\xa6 " ENUM_SWCODE_01_a6_TEXT "\0"
"\x01\xaa " ENUM_SWCODE_01_aa_TEXT "\0"
"\x01\xb1 " ENUM_SWCODE_01_b1_TEXT "\0"
"\x01\xc5 " ENUM_SWCODE_01_c5_TEXT "\0"
"\x01\xc7 " ENUM_SWCODE_01_c7_TEXT "\0"
"\x01\xc8 " ENUM_SWCODE_01_c8_TEXT "\0"
"\x01\xc9 " ENUM_SWCODE_01_c9_TEXT "\0"
"\x01\xca " ENUM_SWCODE_01_ca_TEXT "\0"
"\x01\xcb " ENUM_SWCODE_01_cb_TEXT "\0"
"\x01\xcc " ENUM_SWCODE_01_cc_TEXT "\0"
"\x01\xcd " ENUM_SWCODE_01_cd_TEXT "\0"
"\x01\xd6 " ENUM_SWCODE_01_d6_TEXT "\0"
"\x01\xe3 " ENUM_SWCODE_01_e3_TEXT "\0"
"\x01\xef " ENUM_SWCODE_01_ef_TEXT "\0"
"\x01\xf1 " ENUM_SWCODE_01_f1_TEXT "\0"
"\x02\x04 " ENUM_SWCODE_02_04_TEXT "\0"
"\x02\x06 " ENUM_SWCODE_02_06_TEXT "\0"
"\x02\x07 " ENUM_SWCODE_02_07_TEXT "\0"
"\x02\x08 " ENUM_SWCODE_02_08_TEXT "\0"
"\x02\x09 " ENUM_SWCODE_02_09_TEXT "\0"
"\x02\x1b " ENUM_SWCODE_02_1b_TEXT "\0"
"\x02\x24 " ENUM_SWCODE_02_24_TEXT "\0"
"\x02\x26 " ENUM_SWCODE_02_26_TEXT "\0"
"\x02\x28 " ENUM_SWCODE_02_28_TEXT "\0"
"\x02\x30 " ENUM_SWCODE_02_30_TEXT "\0"
"\x02\x31 " ENUM_SWCODE_02_31_TEXT "\0"
"\x02\x32 " ENUM_SWCODE_02_32_TEXT "\0"
"\x02\x33 " ENUM_SWCODE_02_33_TEXT "\0"
"\x02\x3d " ENUM_SWCODE_02_3d_TEXT "\0"
"\x02\x5a " ENUM_SWCODE_02_5a_TEXT "\0"
"\x02\x5f " ENUM_SWCODE_02_5f_TEXT "\0"
"\x02\x60 " ENUM_SWCODE_02_60_TEXT "\0"
"\x02\x6c " ENUM_SWCODE_02_6c_TEXT "\0"
"\x02\x6d " ENUM_SWCODE_02_6d_TEXT "\0"
"\x02\x6e " ENUM_SWCODE_02_6e_TEXT "\0"
"\x02\x7d " ENUM_SWCODE_02_7d_TEXT
};

// Wartungs-Codes
const char ENUM_WARTUNG[] PROGMEM_LATEST = {
"\x01 " ENUM_WARTUNG_01_TEXT "\0"
"\x02 " ENUM_WARTUNG_02_TEXT "\0"
"\x03 " ENUM_WARTUNG_03_TEXT "\0"
"\x05 " ENUM_WARTUNG_05_TEXT "\0"
"\x12 " ENUM_WARTUNG_12_TEXT "\0"
"\x0a " ENUM_WARTUNG_0a_TEXT "\0"
"\x15 " ENUM_WARTUNG_15_TEXT "\0"
"\x16 " ENUM_WARTUNG_16_TEXT
};

// Sonderbetriebs-Codes
const char ENUM_SONDERBETRIEB[] PROGMEM_LATEST = {
"\x01\x2d " ENUM_SONDERBETRIEB_01_2d_TEXT "\0"
"\x01\x2e " ENUM_SONDERBETRIEB_01_2e_TEXT "\0"
"\x01\x2f " ENUM_SONDERBETRIEB_01_2f_TEXT "\0"
"\x01\x35 " ENUM_SONDERBETRIEB_01_35_TEXT "\0"
"\x01\x36 " ENUM_SONDERBETRIEB_01_36_TEXT
};

// Sonderbetriebs-Codes
const char ENUM_WEEKDAY[] PROGMEM_LATEST = {
"\x01 " ENUM_WEEKDAY_01_TEXT "\0"
"\x02 " ENUM_WEEKDAY_02_TEXT "\0"
"\x03 " ENUM_WEEKDAY_03_TEXT "\0"
"\x04 " ENUM_WEEKDAY_04_TEXT "\0"
"\x05 " ENUM_WEEKDAY_05_TEXT "\0"
"\x06 " ENUM_WEEKDAY_06_TEXT "\0"
"\x07 " ENUM_WEEKDAY_07_TEXT
};

/*
 * Bei der Änderung des Komfortsollwertes durch einfaches Drehen des Rades
 * werden anscheinend die Grenzwerte abgefragt:
HEIZ->DISP ANS  710 11 - Heizkreis 1 - Komfortsollwert 20.00 &deg;C
HEIZ->DISP ANS      2D3D05A5 00 08 C0 (35.0°C)
DC 80 0A 0E 07 2D 3D 05 A5 00 08 C0 3F 7B
HEIZ->DISP ANS  712 11 - Heizkreis 1 - Reduziertsollwert 15.00 &deg;C
*/

/* **********************/
/* global command table */
/* **********************/

PROGMEM_LATE const cmd_t cmdtbl1[]={
// Uhrzeit und Datum
{0x053D000B,  CAT_DATUMZEIT,        VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum
{0x0505000B,  CAT_DATUMZEIT,        VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x0500006C,  CAT_DATUMZEIT,        VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x053D006C,  CAT_DATUMZEIT,        VT_DATETIME,      0,     STR0,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ ] - Uhrzeit und Datum   // gleiche Funktion mit anderer CommandID
{0x053D006C,  CAT_DATUMZEIT,        VT_DATETIME,      1,     STR1,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Uhrzeit und Datum - Stunden/Minuten
{0x053D006C,  CAT_DATUMZEIT,        VT_DATETIME,      2,     STR2,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt:MM ] - Uhrzeit und Datum - Tag/Monat
{0x053D006C,  CAT_DATUMZEIT,        VT_DATETIME,      3,     STR3,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [jjjj ] - Uhrzeit und Datum - Jahr

// Sommerzeit scheint im DISP gehandelt zu werden
// Bei Anzeige werden keine Werte abgefragt. Bei Änderung wird ein INF geschickt.
// Sommerzeit Beginn 25.3. DISP->ALL  INF      0500009E 00 FF 03 19 FF FF FF FF 16
// Sommerzeit Ende 25.11. DISP->ALL  INF      0500009D 00 FF 0B 19 FF FF FF FF 16
{0x053D009E,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_021_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_023_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_028_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_029_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_036_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_049_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_050_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_052_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_059_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_090_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_092_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_094_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_076_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D04B3,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  5,     STR5,     0,                    NULL,         DEFAULT_FLAG, DEV_118_ALL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x053D009D,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_021_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_023_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_028_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_029_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_036_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_049_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_050_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_052_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_059_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_090_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_092_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_094_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_076_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat
{0x053D04B2,  CAT_DATUMZEIT,        VT_SUMMERPERIOD,  6,     STR6,     0,                    NULL,         DEFAULT_FLAG, DEV_118_ALL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat


// nur Bedienteil -> keine Kommunikation über BSB
{0x053D0BC3,  CAT_BEDIENEINHEIT,    VT_ENUM,          20,    STR20,    sizeof(ENUM20),       ENUM20,       DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Sprachauswahl
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_ONOFF,         21,    STR21,    0,                    NULL,         FL_RONLY, DEV_ALL}, // [0] - Bedieneinheit - Anzeige Sonderbetrieb
{0x053D0BCA,  CAT_BEDIENEINHEIT,    VT_ENUM,          22,    STR22,    sizeof(ENUM22),       ENUM22,       DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Info
{0x053D0BC9,  CAT_BEDIENEINHEIT,    VT_ENUM,          23,    STR23,    sizeof(ENUM23),       ENUM23,       DEFAULT_FLAG, DEV_ALL}, // Fehleranzeige Code | Code und Text
{0x053D081E,  CAT_BEDIENEINHEIT,    VT_BYTE,          25,    STR25,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anzeigekontrast
{0x053D0BB9,  CAT_BEDIENEINHEIT,    VT_ONOFF,         26,    STR26,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Sperre Bedienung
{0x053D0BC8,  CAT_BEDIENEINHEIT,    VT_ONOFF,         27,    STR27,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Sperre Programmierung
{0x053D0BC8,  CAT_BEDIENEINHEIT,    VT_ENUM,          28,    STR28,    sizeof(ENUM28),       ENUM28,       DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Bedieneinheit Direktverstellung
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_ENUM,          29,    STR29,    sizeof(ENUM29),       ENUM29,       DEFAULT_FLAG, DEV_ALL}, // [0] - Einheiten °C,bar oder °F,PSI
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_YESNO,         30,    STR30,    0,                    NULL,         FL_RONLY, DEV_ALL}, // Bedieneinheit Grundeinstellung sichern
{0x053D08C3,  CAT_BEDIENEINHEIT,    VT_YESNO,         31,    STR31,    0,                    NULL,         FL_RONLY, DEV_ALL}, // Bedieneinheit Grundeinstellung aktivieren
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_ENUM,          40,    STR40,    sizeof(ENUM40),       ENUM40,       DEFAULT_FLAG, DEV_ALL}, // Einsatz als
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_ENUM,          42,    STR42,    sizeof(ENUM42),       ENUM42,       DEFAULT_FLAG, DEV_ALL}, // Zuordnung Raumgerät 1
{0x190505A3,  CAT_BEDIENEINHEIT,    VT_BYTE,          42,    STR42_2,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Wirkung eines RG auf die Heizkreise
{0x053D0BC5,  CAT_BEDIENEINHEIT,    VT_ENUM,          44,    STR44,    sizeof(ENUM44),       ENUM44,       DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Bedienung HK 2
{0x05050BC6,  CAT_BEDIENEINHEIT,    VT_ENUM,          46,    STR46,    sizeof(ENUM46),       ENUM46,       DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Bedienung HK P
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_ENUM,          48,    STR48,    sizeof(ENUM48),       ENUM48,       DEFAULT_FLAG, DEV_ALL}, // Wirkung Präsenztaste
{CMD_UNKNOWN, CAT_BEDIENEINHEIT,    VT_UNKNOWN,       54,    STR54,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Korrektur Raumfühler
{0x053D000E,  CAT_BEDIENEINHEIT,    VT_FP1,           70,    STR70,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Bedieneinheit - Geraete-Version Bedienteil
{0x053D0078,  CAT_BEDIENEINHEIT,    VT_UNKNOWN,       71,    STR71,    0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Raumgerät-Typ (logged via OZW671 on LMU64)

// Funk
{CMD_UNKNOWN, CAT_FUNK,             VT_YESNO,         120,   STR120,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Binding
{CMD_UNKNOWN, CAT_FUNK,             VT_ONOFF,         121,   STR121,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Testmode
{0x053D0966,  CAT_FUNK,             VT_ENUM,          130,   STR130,   sizeof(ENUM130),      ENUM130,      DEFAULT_FLAG, DEV_ALL}, // Raumgerät 1 Status
{0x053D0967,  CAT_FUNK,             VT_ENUM,          131,   STR131,   sizeof(ENUM131),      ENUM131,      DEFAULT_FLAG, DEV_ALL}, // Raumgerät 2 Status
{0x053D0968,  CAT_FUNK,             VT_ENUM,          132,   STR132,   sizeof(ENUM132),      ENUM132,      DEFAULT_FLAG, DEV_ALL}, // Raumgerät P Status
{0x053D096E,  CAT_FUNK,             VT_ENUM,          133,   STR133,   sizeof(ENUM133),      ENUM133,      DEFAULT_FLAG, DEV_ALL}, // Außenfühler P Status
{0x053D0993,  CAT_FUNK,             VT_ENUM,          134,   STR134,   sizeof(ENUM134),      ENUM134,      DEFAULT_FLAG, DEV_ALL}, // Repeater P Status
{0x053D096A,  CAT_FUNK,             VT_ENUM,          135,   STR135,   sizeof(ENUM135),      ENUM135,      DEFAULT_FLAG, DEV_ALL}, // Bediengerät 1 Status
{0x053D096C,  CAT_FUNK,             VT_ENUM,          136,   STR136,   sizeof(ENUM136),      ENUM136,      DEFAULT_FLAG, DEV_ALL}, // Bediengerät 1 Status
{0x053D096D,  CAT_FUNK,             VT_ENUM,          137,   STR137,   sizeof(ENUM137),      ENUM137,      DEFAULT_FLAG, DEV_ALL}, // Bediengerät P Status
{0x053D096B,  CAT_FUNK,             VT_ENUM,          138,   STR138,   sizeof(ENUM138),      ENUM138,      DEFAULT_FLAG, DEV_ALL}, // Servicegerät Status
{0x053D05E4,  CAT_FUNK,             VT_YESNO,         140,   STR140,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Alle Geräte löschen


// Zeitprogramm Heizkreis 1
// HEIZ->DISP ANS 500 Vorwahl  05 00 15 00 98 00 18 00 98 00 18 00
// set Mo 1. Heizphase 05:10  -> DISP->HEIZ SET 3D050A8C 05 0A 15 00 80 00 00 00 80 00 00 00
// set Mo 1. Heizphase 05:00  -> DISP->HEIZ SET 3D050A8C 05 00 15 00 80 00 00 00 80 00 00 00
// Für jeden Wochentag können 3 Phasen gesetzt werden. Die Kombinationen Mo-Fr, Mo-So, Sa - So werden nur auf dem Bedienteil angezeigt.
// 8C = Mo .. 92 = So
// virtuelle Zeilen
{0x053D0A8C,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      500,   STR500,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm Heizkreis 1 - Vorwahl
{0x213D0A8C,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      500,   STR500,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm Heizkreis 1 - Vorwahl - logged on OCI700 via LPB
{0x053D0A8D,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      501,   STR501,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Ein
{0x213D0A8D,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      501,   STR501,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Ein - logged on OCI700 via LPB
{0x053D0A8E,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      502,   STR502,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Aus
{0x213D0A8E,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      502,   STR502,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Aus - logged on OCI700 via LPB
{0x053D0A8F,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      503,   STR503,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Ein
{0x213D0A8F,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      503,   STR503,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Ein - logged on OCI700 via LPB
{0x053D0A90,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      504,   STR504,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Aus
{0x213D0A90,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      504,   STR504,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Aus - logged on OCI700 via LPB
{0x053D0A91,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      505,   STR505,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Ein
{0x213D0A91,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      505,   STR505,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Ein - logged on OCI700 via LPB
{0x053D0A92,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      506,   STR506,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Aus
{0x213D0A92,  CAT_ZEITPROG_HK1,     VT_TIMEPROG,      506,   STR506,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Aus - logged on OCI700 via LPB
{0x053D05B2,  CAT_ZEITPROG_HK1,     VT_YESNO,         516,   STR516,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm Heizkreis 1 - Standardwerte
{0x213D05B2,  CAT_ZEITPROG_HK1,     VT_YESNO,         516,   STR516,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm Heizkreis 1 - Standardwerte - logged on OCI700 via LPB
// Zeitprogramm Heizkreis 2
// virtuelle Zeilen
{0x063D0A8C,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      520,   STR520,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm Heizkreis 2 - Vorwahl
{0x223D0A8C,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      520,   STR520,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm Heizkreis 2 - Vorwahl - logged on OCI700 via LPB
{0x063D0A8D,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      521,   STR521,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Ein
{0x223D0A8D,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      521,   STR521,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Ein - logged on OCI700 via LPB
{0x063D0A8E,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      522,   STR522,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Aus
{0x223D0A8E,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      522,   STR522,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Aus - logged on OCI700 via LPB
{0x063D0A8F,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      523,   STR523,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Ein
{0x223D0A8F,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      523,   STR523,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Ein - logged on OCI700 via LPB
{0x063D0A90,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      524,   STR524,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Aus
{0x223D0A90,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      524,   STR524,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Aus - logged on OCI700 via LPB
{0x063D0A91,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      525,   STR525,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Ein
{0x223D0A91,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      525,   STR525,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Ein - logged on OCI700 via LPB
{0x063D0A92,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      526,   STR526,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Aus
{0x223D0A92,  CAT_ZEITPROG_HK2,     VT_TIMEPROG,      526,   STR526,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Aus - logged on OCI700 via LPB
// Thision 535 Tag kopieren auf
{0x063D05B2,  CAT_ZEITPROG_HK2,     VT_YESNO,         536,   STR536,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm Heizkreis 2 - Standardwerte
{0x223D05B2,  CAT_ZEITPROG_HK2,     VT_YESNO,         536,   STR536,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm Heizkreis 2 - Standardwerte - logged on OCI700 via LPB

// Zeitprogramm 3/HKP
// virtuelle Zeilen
{0x073D0A8C,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      540,   STR540,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 3 HKP - Vorwahl
{0x053D0A8C,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      540,   STR540,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm 3 HKP - Vorwahl - logged on OCI700 via LPB
{0x073D0A8D,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      541,   STR541,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Ein
{0x053D0A8D,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      541,   STR541,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Ein - logged on OCI700 via LPB
{0x073D0A8E,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      542,   STR542,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Aus
{0x053D0A8E,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      542,   STR542,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Aus - logged on OCI700 via LPB
{0x073D0A8F,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      543,   STR543,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Ein
{0x053D0A8F,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      543,   STR543,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Ein - logged on OCI700 via LPB
{0x073D0A90,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      544,   STR544,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Aus
{0x053D0A90,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      544,   STR544,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Aus - logged on OCI700 via LPB
{0x073D0A91,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      545,   STR545,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Ein
{0x053D0A91,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      545,   STR545,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Ein - logged on OCI700 via LPB
{0x073D0A92,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      546,   STR546,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Aus
{0x053D0A92,  CAT_ZEITPROG_HKP,     VT_TIMEPROG,      546,   STR546,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Aus - logged on OCI700 via LPB
// Thision 555 Tag kopieren auf
{0x073D05B2,  CAT_ZEITPROG_HKP,     VT_YESNO,         556,   STR556,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 3 HKP - Standardwerte
{0x053D05B2,  CAT_ZEITPROG_HKP,     VT_YESNO,         556,   STR556,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm 3 HKP - Standardwerte - logged on OCI700 via LPB

// Zeitprogramm 4/TWW
{0x053D0AA0,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      560,   STR560,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 4 TWW - Vorwahl
{0x253D0AA0,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      560,   STR560,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm 4 TWW - Vorwahl - logged on OCI700 via LPB
{0x053D0AA1,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      561,   STR561,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Ein
{0x253D0AA1,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      561,   STR561,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Ein - logged on OCI700 via LPB
{0x053D0AA2,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      562,   STR562,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Aus
{0x253D0AA2,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      562,   STR562,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Aus - logged on OCI700 via LPB
{0x053D0AA3,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      563,   STR563,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Ein
{0x253D0AA3,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      563,   STR563,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Ein - logged on OCI700 via LPB
{0x053D0AA4,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      564,   STR564,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Aus
{0x253D0AA4,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      564,   STR564,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Aus - logged on OCI700 via LPB
{0x053D0AA5,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      565,   STR565,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Ein
{0x253D0AA5,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      565,   STR565,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Ein - logged on OCI700 via LPB
{0x053D0AA6,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      566,   STR566,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Aus
{0x253D0AA6,  CAT_ZEITPROG_TWW,     VT_TIMEPROG,      566,   STR566,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Aus - logged on OCI700 via LPB
// Thision 575 Tag kopieren auf
{0x053D05B3,  CAT_ZEITPROG_TWW,     VT_YESNO,         576,   STR576,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 4 TWW - Standardwerte
{0x253D05B3,  CAT_ZEITPROG_TWW,     VT_YESNO,         576,   STR576,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Zeitprogramm 4 TWW - Standardwerte

// Zeitprogramm 5
// {0x053D0AB3,  CAT_ZEITPROG_5,       VT_TIMEPROG,      600,   STR600,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 5 - Vorwahl / TODO: check hypothetical CommandID
{0x053D0AB4,  CAT_ZEITPROG_5,       VT_TIMEPROG,      600,   STR600,   0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // [hh:mm ] - Zeitprogramm 5 - Vorwahl
{0x053D0AB4,  CAT_ZEITPROG_5,       VT_TIMEPROG,      601,   STR601,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 1. Phase Ein
{0x053D0AB5,  CAT_ZEITPROG_5,       VT_TIMEPROG,      602,   STR602,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 1. Phase Aus
{0x053D0AB6,  CAT_ZEITPROG_5,       VT_TIMEPROG,      603,   STR603,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 2. Phase Ein
{0x053D0AB7,  CAT_ZEITPROG_5,       VT_TIMEPROG,      604,   STR604,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 2. Phase Aus
{0x053D0AB8,  CAT_ZEITPROG_5,       VT_TIMEPROG,      605,   STR605,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 3. Phase Ein
{0x053D0AB9,  CAT_ZEITPROG_5,       VT_TIMEPROG,      606,   STR606,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 3. Phase Aus
{0x053D0ABA,  CAT_ZEITPROG_5,       VT_YESNO,         616,   STR616,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Zeitprogramm 5 - Standardwerte
{0x053D082B,  CAT_ZEITPROG_5,       VT_YESNO,         616,   STR616,   0,                    NULL,         DEFAULT_FLAG, DEV_090_ALL}, // [0] - Zeitprogramm 5 - Standardwerte
{0x053D082B,  CAT_ZEITPROG_5,       VT_YESNO,         616,   STR616,   0,                    NULL,         DEFAULT_FLAG, DEV_119_ALL}, // [0] - Zeitprogramm 5 - Standardwerte
{0x053D082B,  CAT_ZEITPROG_5,       VT_YESNO,         616,   STR616,   0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // [0] - Zeitprogramm 5 - Standardwerte


// Es gibt 8 Perioden c4..d3 (jeweils Beginn/Ende).
// Zeile 641 dient nur zur Vorwahl der Perioden auf dem Bedienteil.
// Die Parameter scheinen VT_DATETIME ähnlich zu sein.
// 1. Byte:
// Bei RX 00=enabled 01=disabled
// Bei TX 06=enable 05=disable
// byte 3 Monat
// byte 4 Tag
// byte 17=0x17
// alle anderen Bytes sind 0
// z.B.:
// DISP->HEIZ SET      3D0509C6 06 00 02 0A 00 00 00 00 17
// Periode 2 Ende: DC 80 0A 14 07 05 3D 09 C6 01 00 01 01 00 00 00 00 17 0C 38

// Ferien Heizkreis 1
// virtuelle Zeilen
{0x053D09C4,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  632,   STR632,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 1 Beginn Tag/Monat
{0x053D09C5,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  633,   STR633,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 1 Ende Tag/Monat
{0x053D09C6,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  634,   STR634,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 2 Beginn Tag/Monat
{0x053D09C7,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  635,   STR635,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 2 Ende Tag/Monat
{0x053D09C8,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  636,   STR636,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 3 Beginn Tag/Monat
{0x053D09C9,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  637,   STR637,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 3 Ende Tag/Monat
{0x053D09CA,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  638,   STR638,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 4 Beginn Tag/Monat
{0x053D09CB,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  639,   STR639,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 4 Ende Tag/Monat
{0x053D09CC,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  640,   STR640,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 5 Beginn Tag/Monat
{0x053D09CD,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  641,   STR641,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 5 Ende Tag/Monat
{0x053D09CE,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  642,   STR642,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Beginn Tag/Monat
{0x213D09C4,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  642,   STR642,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Beginn Tag/Monat - logged on OCI700 via LPB
{0x053D09CF,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  643,   STR643,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Ende Tag/Monat
{0x213D09C5,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  643,   STR643,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Ende Tag/Monat - logged on OCI700 via LPB
{0x053D09D0,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  644,   STR644,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 7 Beginn Tag/Monat
{0x053D09D1,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  645,   STR645,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 7 Ende Tag/Monat
{0x053D09D2,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  646,   STR646,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 8 Beginn Tag/Monat
{0x053D09D3,  CAT_FERIEN_HK1,       VT_VACATIONPROG,  647,   STR647,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 8 Ende Tag/Monat
{0x2D3D04C2,  CAT_FERIEN_HK1,       VT_ENUM,          648,   STR648,   sizeof(ENUM648),      ENUM648,      DEFAULT_FLAG, DEV_ALL}, // [0] - Ferienheizkreis 1 - Betriebsniveau
// Ferien Heizkreis 2
// virtuelle Zeilen
{0x063D09C4,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  649,   STR649,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 1 Beginn Tag/Monat
{0x063D09C5,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  650,   STR650,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 1 Ende Tag/Monat
{0x063D09C6,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  651,   STR651,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 2 Beginn Tag/Monat
{0x063D09C7,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  652,   STR652,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 2 Ende Tag/Monat
{0x220509C4,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  652,   STR652,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 2 Ende Tag/Monat - logged on OCI700 via LPB
{0x063D09C8,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  653,   STR653,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 3 Beginn Tag/Monat
{0x220509C5,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  653,   STR653,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 3 Beginn Tag/Monat - logged on OCI700 via LPB
{0x063D09C9,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  654,   STR654,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 3 Ende Tag/Monat
{0x063D09CA,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  655,   STR655,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 4 Beginn Tag/Monat
{0x063D09CB,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  656,   STR656,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 4 Ende Tag/Monat
{0x063D09CC,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  657,   STR657,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 5 Beginn Tag/Monat
{0x063D09CD,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  658,   STR658,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 5 Ende Tag/Monat
{0x063D09CE,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  659,   STR659,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 6 Beginn Tag/Monat
{0x063D09CF,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  660,   STR660,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 6 Ende Tag/Monat
{0x063D09D0,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  661,   STR661,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 7 Beginn Tag/Monat
{0x063D09D1,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  662,   STR662,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 7 Ende Tag/Monat
{0x063D09D2,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  663,   STR663,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 8 Beginn Tag/Monat
{0x063D09D3,  CAT_FERIEN_HK2,       VT_VACATIONPROG,  664,   STR664,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 8 Ende Tag/Monat
{0x2E3D04C2,  CAT_FERIEN_HK2,       VT_ENUM,          665,   STR665,   sizeof(ENUM665),      ENUM665,      DEFAULT_FLAG, DEV_ALL}, // [0] - Ferienheizkreis 2 - Betriebsniveau
// Ferien Heizkreis P
// virtuelle Zeilen
{0x073D09C4,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  666,   STR666,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 1 Beginn Tag/Monat
{0x073D09C5,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  667,   STR667,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 1 Ende Tag/Monat
{0x073D09C6,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  668,   STR668,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 2 Beginn Tag/Monat
{0x073D09C7,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  669,   STR669,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 2 Ende Tag/Monat
{0x073D09C8,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  670,   STR670,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 3 Beginn Tag/Monat
{0x073D09C9,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  671,   STR671,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 3 Ende Tag/Monat
{0x073D09CA,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  672,   STR672,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 4 Beginn Tag/Monat
{0x073D09CB,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  673,   STR673,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 4 Ende Tag/Monat
{0x073D09CC,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  674,   STR674,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 5 Beginn Tag/Monat
{0x073D09CD,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  675,   STR675,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 5 Ende Tag/Monat
{0x073D09CE,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  676,   STR676,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 6 Beginn Tag/Monat
{0x073D09CF,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  677,   STR677,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 6 Ende Tag/Monat
{0x073D09D0,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  678,   STR678,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 7 Beginn Tag/Monat
{0x073D09D1,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  679,   STR679,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 7 Ende Tag/Monat
{0x073D09D2,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  680,   STR680,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 8 Beginn Tag/Monat
{0x073D09D3,  CAT_FERIEN_HKP,       VT_VACATIONPROG,  681,   STR681,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [tt.MM ] - Ferienheizkreis P - Periode 8 Ende Tag/Monat
{0x2F3D04C2,  CAT_FERIEN_HKP,       VT_ENUM,          682,   STR682,   sizeof(ENUM682),      ENUM682,      DEFAULT_FLAG, DEV_ALL}, // [0] - Ferienheizkreis P - Betriebsniveau



// Einstellungen Heizkreis 1
{0x2D3D0574,  CAT_HK1,              VT_ENUM,          700,   STR700,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x053D0074,  CAT_HK1,              VT_ENUM,          700,   STR700,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_021_ALL}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x053D0074,  CAT_HK1,              VT_ENUM,          700,   STR700,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_023_ALL}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x053D0074,  CAT_HK1,              VT_ENUM,          700,   STR700,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_036_ALL}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x053D0074,  CAT_HK1,              VT_ENUM,          700,   STR700,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_064_ALL}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x2D3D0572,  CAT_HK1,              VT_ONOFF,         701,   STR701,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 1 - Präsenztaste (Absenkmodus bis zum nächsten BA-Wechsel laut Zeitplan) ***(virtuelle Zeile)***
{0x2D3D020D,  CAT_HK1,              VT_CUSTOM_ENUM,   702,   STR702,   sizeof(ENUM702),      ENUM702,      DEFAULT_FLAG, DEV_ALL}, // Virtueller Parameter: Weishaupt Betriebsart-Wahlschalter (Erstes Payload Byte)
{0x2D3D020D,  CAT_HK1,              VT_CUSTOM_ENUM,   703,   STR703,   sizeof(ENUM703),      ENUM703,      DEFAULT_FLAG, DEV_ALL}, // Virtueller Parameter: Weishaupt Betriebsart-Wahlschalter (Zweites Payload Byte)
{0x393D2F80,  CAT_HK1,              VT_TEMP_SHORT5,   709,   STR709,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert Min
{0x2D3D058E,  CAT_HK1,              VT_TEMP,          710,   STR710,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert
//HEIZ->DISP ANS      2D3D05A5 00 08 C0 (35.0°C)
// line not in menue!
// virtuelle Zeile

{0x2D3D05A5,  CAT_HK1,              VT_TEMP,          711,   STR711,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max
{0x393D2F81,  CAT_HK1,              VT_TEMP_SHORT5,   711,   STR711,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max
{0x2D3D0590,  CAT_HK1,              VT_TEMP,          712,   STR712,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Reduziertsollwert
{0x2D3D0592,  CAT_HK1,              VT_TEMP,          714,   STR714,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Frostschutzsollwert
{0x2D3D05A5,  CAT_HK1,              VT_TEMP,          716,   STR711,   0,                    NULL,         DEFAULT_FLAG, DEV_170_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max //FUJITSU
{0x2D3D05A5,  CAT_HK1,              VT_TEMP,          716,   STR711,   0,                    NULL,         DEFAULT_FLAG, DEV_119_ALL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max //FUJITSU
{0x2D3D05F6,  CAT_HK1,              VT_FP02,          720,   STR720,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 1 - Kennlinie Steilheit
{0x2D3D05F6,  CAT_HK1,              VT_BYTE,          720,   STR720,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Heizkreis 1 - Kennlinie Steilheit
{0x2D3D0610,  CAT_HK1,              VT_TEMP,          721,   STR721,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Kennlinie Verschiebung
{0x2D3D0610,  CAT_HK1,              VT_TEMP_SHORT5,   721,   STR721,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 1 - Kennlinie Verschiebung
{0x2D3D060B,  CAT_HK1,              VT_ONOFF,         726,   STR726,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [] - Heizkreis 1 - Kennlinie Adaption
{0x2D3D05FD,  CAT_HK1,              VT_TEMP,          730,   STR730,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Sommer-/ Winterheizgrenze
{0x393D05FD,  CAT_HK1,              VT_TEMP_SHORT,    730,   STR730,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 1 - Sommer-/ Winterheizgrenze
// Parameter below is from Elco Thision S 17.1 (devcie family 97) via OCI. So far no possibility to detect presence of OCI and react to different command IDs from OCI420 vis-a-vis direct BSB connection.
// {0x393D05FD,  CAT_HK1,              VT_TEMP,          730,   STR730,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 1 - Sommer-/ Winterheizgrenze
{0x2D3D0640,  CAT_HK1,              VT_TEMP,          732,   STR732,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Tagesheizgrenze
{0x053D1214,  CAT_HK1,              VT_YESNO,         733,   STR733,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Verlängerung Tagesheizgrenze
{0x393D2F89,  CAT_HK1,              VT_TEMP_SHORT5_US,734,   STR734,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Raumsollabsenkung mit Schaltuhr
{0x213D0663,  CAT_HK1,              VT_TEMP,          740,   STR740,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Vorlaufsollwert Minimum
{0x213D0662,  CAT_HK1,              VT_TEMP,          741,   STR741,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Vorlaufsollwert Maximum
{0x213D0A88,  CAT_HK1,              VT_TEMP,          742,   STR742,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Vorlaufsollwert Raumthermostat HK1, also used by Brötje IDA and FE ISR Plus
{0x2D3D0D85,  CAT_HK1,              VT_PERCENT,       744,   STR744,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [% ] - Heizkreis 1 - Soll Einschaltverh R'stat
{0x2D3D0603,  CAT_HK1,              VT_PERCENT,       750,   STR750,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [% ] - Heizkreis 1 - Raumeinfluss
{0x2D3D0614,  CAT_HK1,              VT_TEMP,          760,   STR760,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Raumtemperaturbegrenzung
{0x053D0C9D,  CAT_HK1,              VT_PERCENT,       761,   STR761,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [% ] - Heizkreis 1 - Heizgrenze Raumregler
{0x2D3D0602,  CAT_HK1,              VT_TEMP,          770,   STR770,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Schnellaufheizung
{0x2D3D05E8,  CAT_HK1,              VT_ENUM,          780,   STR780,   sizeof(ENUM780),      ENUM780,      DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 1 - Schnellabsenkung
{0x2D3D05FB,  CAT_HK1,              VT_BYTE,          781,   STR781,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 1 - Schnellabsenkung Faktor
{0x2D3D0607,  CAT_HK1,              VT_MINUTES,       790,   STR790,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [Min ] - Heizkreis 1 - Einschalt-Optimierung Max.
{0x2D3D0609,  CAT_HK1,              VT_MINUTES,       791,   STR791,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [Min ] - Heizkreis 1 - Ausschalt-Optimierung Max.
{0x2D3D0609,  CAT_HK1,              VT_GRADIENT,      794,   STR794,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min/K ] - Heizkreis 1 - Aufheizgradient
{0x2D3D059E,  CAT_HK1,              VT_TEMP,          800,   STR800,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Reduziert-Anhebung Begin
{0x2D3D059D,  CAT_HK1,              VT_TEMP,          801,   STR801,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Reduziert-Anhebung Ende
{CMD_UNKNOWN, CAT_HK1,              VT_YESNO,         809,   STR809,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Pumpendauerlauf HK1
{0x213D063A,  CAT_HK1,              VT_YESNO,         810,   STR810,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anlagenfrostschutz HK-Pumpe
{0x213D0674,  CAT_HK1,              VT_ONOFF,         820,   STR820,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - Heizkreis 1 - Überhitzschutz Pumpenkreis
{0x213D065D,  CAT_HK1,              VT_TEMP,          830,   STR830,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Mischerüberhöhung
{0x213D0654,  CAT_HK1,              VT_ENUM,          832,   STR832,   sizeof(ENUM832),      ENUM832,      FL_RONLY, DEV_ALL}, // - Antrieb Typ
{0x213D065C,  CAT_HK1,              VT_TEMP,          833,   STR833,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // - Schaltdifferenz 2-Punkt
{0x213D065A,  CAT_HK1,              VT_SECONDS_WORD,  834,   STR834,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ s ] - Antrieb Laufzeit
{0x213D0658,  CAT_HK1,              VT_TEMP,          835,   STR835,   0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Heizkreis 1 - Mischer P-Band Xp
{0x213D0659,  CAT_HK1,              VT_SECONDS_WORD,  836,   STR836,   0,                    NULL,         FL_OEM, DEV_ALL}, // [ s ] - Mischer Nachstellzeit Tn
{0x2D3D067B,  CAT_HK1,              VT_ENUM,          850,   STR850,   sizeof(ENUM850),      ENUM850,      DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 1 - Estrichfunktion
{0x2D3D068A,  CAT_HK1,              VT_TEMP,          851,   STR851,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Estrich Sollwert manuell
{0x2D3D067D,  CAT_HK1,              VT_TEMP,       	  855,   STR855,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 1 - Vorlauf-Sollwert Estrich Austrocknung
{0x2D3D067C,  CAT_HK1,              VT_DAYS,          856,   STR856,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ Tag ] - Heizkreis 1 - Estrich-Austrocknung Tag
{0x2D3D0DF2,  CAT_HK1,              VT_BYTE,          856,   STR856,   0,                    NULL,         DEFAULT_FLAG, DEV_170_ALL}, // [ Tag ] - Heizkreis 1 - Estrich Tag aktuell //FUJITSU
{0x2D3D0DF2,  CAT_HK1,              VT_DAYS,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_090_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_107_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_138_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_170_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_171_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt //FUJITSU
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt
{0x213D0B43,  CAT_HK1,              VT_BYTE,          857,   STR857,   0,                    NULL,         DEFAULT_FLAG, DEV_211_ALL}, // [ Tage ] - Heizkreis 1 - Estrich Tage erfüllt
{0x213D08C9,  CAT_HK1,              VT_ENUM,          861,   STR861,   sizeof(ENUM861),      ENUM861,      DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 1 - Übertemperaturabnahme
{0x213D065E,  CAT_HK1,              VT_PERCENT,       864,   STR864,   0,                    NULL,         FL_RONLY, DEV_ALL}, // Sperrsignalverstärkung
{0x2D3D07C4,  CAT_HK1,              VT_YESNO,         870,   STR870,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 1 - Mit Pufferspeicher
{0x2D3D07C5,  CAT_HK1,              VT_YESNO,         872,   STR872,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 1 - Mit Vorregler/Zubring`pumpe
{0x213D04AD,  CAT_HK1,              VT_ENUM,          880,   STR880,   sizeof(ENUM880),      ENUM880,      DEFAULT_FLAG, DEV_ALL}, // HK1 Pumpe Drehzahlreduktion
{0x213D04AB,  CAT_HK1,              VT_PERCENT,       882,   STR882,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum // todo die ID gibt es, aber sie gehoert nicht zu diesem Parameter
{0x053D115E,  CAT_HK1,              VT_PERCENT,       882,   STR882,   0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // [%] - Heizkreis 1 - Pumpendrehzahl Minimum
{0x213D04AA,  CAT_HK1,              VT_PERCENT,       883,   STR883,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum
{0x053D115F,  CAT_HK1,              VT_PERCENT,       883,   STR883,   0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // [%] - Heizkreis 1 - Pumpendrehzahl Maximum
{0x113D2F95,  CAT_HK1,              VT_BYTE,          884,   STR884,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 884 Drehzahlstufe Ausleg'punkt [1-50 9-13kW=16 17-25kW=19 35-50kW=24]
{0x113D304F,  CAT_HK1,              VT_PERCENT5,      885,   STR885,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 885 Pumpe-PWM Minimum [%]
{0x113D04AB,  CAT_HK1,              VT_PERCENT,       885,   STR885,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 885 Pumpe-PWM Minimum [%] - logged on OCI700 via LPB
{0x193D2F88,  CAT_HK1,              VT_TEMP_SHORT,    886,   STR886,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 886 Norm Aussentemperatur [°C]
{0x053D3050,  CAT_HK1,              VT_TEMP_SHORT5_US,887,   STR887,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 887 Vorlaufsoll NormAussentemp [°C]
{0x393D2F82,  CAT_HK1,              VT_TEMP_WORD5_US, 887,   STR887,   0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 887 Vorlaufsoll NormAussentemp [°C] - logged on OCI700 via LPB
{0x253D2FE5,  CAT_HK1,              VT_PERCENT_WORD1, 888,   STR888,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 888 dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_108_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_138_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_170_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_171_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_172_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_205_ALL}, // dt Überhöhungsfaktor [%]
{0x213D0E38,  CAT_HK1,              VT_PERCENT,       888,   STR888_2, 0,                    NULL,         DEFAULT_FLAG, DEV_211_ALL}, // dt Überhöhungsfaktor [%]
{0x213D10C2,  CAT_HK1,              VT_YESNO,         890,   STR890,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // WOB20C/WOB25C Vorl'sollwertkorr Drehz'reg HK1
{0x193D2F8A,  CAT_HK1,              VT_TEMP_SHORT5,   894,   STR894,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 894 dt Spreizung Norm Aussent. [°C]
{0x193D2F8B,  CAT_HK1,              VT_TEMP_SHORT5,   895,   STR895,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 895 dt Spreizung Maximum [°C]
{0x053D0DD4,  CAT_HK1,              VT_ENUM,          898,   STR898,   sizeof(ENUM898),      ENUM898,      DEFAULT_FLAG, DEV_ALL}, // Betriebsniveauumschaltung
{0x053D07BE,  CAT_HK1,              VT_ENUM,          900,   STR900,   sizeof(ENUM900),      ENUM900,      DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 1 - Betriebsartumschaltung
{0x053D07BE,  CAT_HK1,              VT_ENUM,          900,   STR900,   sizeof(ENUM900_2),    ENUM900_2,    DEFAULT_FLAG, DEV_096_ALL}, // [0] - Heizkreis 1 - Betriebsartumschaltung

// Kühlkreis 1
{0x653D0A26,  CAT_KUEHL1,           VT_ENUM,          901,   STR901,   sizeof(ENUM700),      ENUM700,      DEFAULT_FLAG, DEV_ALL}, // Betriebsart
{0x653D0A1A,  CAT_KUEHL1,           VT_TEMP,          902,   STR902,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Komfortsollwert
{0x653D1943,  CAT_KUEHL1,           VT_TEMP,          903,   STR903,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Reduziertsollwert
{0x653D0A80,  CAT_KUEHL1,           VT_TEMP,          904,   STR904,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Raumtemperatur Schutzsollwert Kühlkreis 1
{0x653D1944,  CAT_KUEHL1,           VT_TEMP,          905,   STR905,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Komfortsollwert Minimum
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       907,   STR907,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe
{0x653D0A20,  CAT_KUEHL1,           VT_TEMP,          908,   STR908,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufsollwert bei TA 25 °C
{0x653D0A21,  CAT_KUEHL1,           VT_TEMP,          909,   STR909,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufsollwert bei TA 35 °C
{0x653D0A22,  CAT_KUEHL1,           VT_TEMP,          912,   STR912,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kühlgrenze bei TA
{0x693D0A75,  CAT_KUEHL1,           VT_HOURS_SHORT,   913,   STR913,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sperrdauer nach Heizende
{0x653D1940,  CAT_KUEHL1,           VT_TEMP,          914,   STR914,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Tageskühlgrenze
{0x653D0A25,  CAT_KUEHL1,           VT_TEMP,          918,   STR918,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sommerkomp Beginn bei TA
{0x653D0A24,  CAT_KUEHL1,           VT_TEMP,          919,   STR919,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sommerkomp Ende bei TA
{0x653D0A1B,  CAT_KUEHL1,           VT_TEMP,          920,   STR920,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sommerkomp Sollw’anhebung
{CMD_UNKNOWN, CAT_KUEHL1,           VT_TEMP,          923,   STR923,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufsollwert Min bei TA 25 °C
{0x653D0A1F,  CAT_KUEHL1,           VT_TEMP,          924,   STR924,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufsollwert Min bei TA 35 °C
{0x653D0A27,  CAT_KUEHL1,           VT_PERCENT,       928,   STR928,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Raumeinfluss
{0x653D0A23,  CAT_KUEHL1,           VT_TEMP,          932,   STR932,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Raumtemperaturbegrenzung
{0x653D0B6F,  CAT_KUEHL1,           VT_PERCENT,       933,   STR933,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kühlgrenze Raumregler
{0x693D0A70,  CAT_KUEHL1,           VT_ONOFF,         937,   STR937,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anl'frostschutz KK-Pumpe
{0x693D0B65,  CAT_KUEHL1,           VT_TEMP,          938,   STR938,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mischerunterkühlung
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       939,   STR939,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Antrieb Typ
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       940,   STR940,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdifferenz 2-Punkt
{0x693D0A7D,  CAT_KUEHL1,           VT_SECONDS_WORD,  941,   STR941,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Antrieb Laufzeit
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       942,   STR942,   0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer P-Band Xp
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       943,   STR943,   0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x053D0D15,  CAT_KUEHL1,           VT_UNKNOWN,       945,   STR945,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mischventil im Heizbetrieb
{0x053D0D15,  CAT_KUEHL1,           VT_UNKNOWN,       946,   STR946,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sperrdauer Taupunktwächt
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       947,   STR947,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufsollw’anhebung Hygro
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       948,   STR948,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorl'anhebung Beginn bei r. F.
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       950,   STR950,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlauftemp'diff Taupunkt
{CMD_UNKNOWN, CAT_KUEHL1,           VT_UNKNOWN,       962,   STR962,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mit Pufferspeicher
{0x653D0B69,  CAT_KUEHL1,           VT_ONOFF,         963,   STR963,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mit Vorregler/Zubring'pumpe
{0x053D0B7A,  CAT_KUEHL1,           VT_ONOFF,         969,   STR969,   0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Betriebsartumschaltung

// Heizkreis 2
{0x2E3D0574,  CAT_HK2,              VT_ENUM,          1000,  STR1000,  sizeof(ENUM1000),     ENUM1000,     DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 2 - Betriebsart ***(virtuelle Zeile)***
{0x2E3E0572,  CAT_HK2,              VT_ONOFF,         1001,  STR1001,  0,                    0,            DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 2 - Präsenztaste (Absenkmodus bis zum nächsten BA-Wechsel laut Zeitplan) ***(virtuelle Zeile)***
{0x2E3D0572,  CAT_HK2,              VT_ONOFF,         1001,  STR1001,  0,                    0,            DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 2 - Präsenztaste (Absenkmodus bis zum nächsten BA-Wechsel laut Zeitplan) ***(virtuelle Zeile)***
{0x2E3D058E,  CAT_HK2,              VT_TEMP,          1010,  STR1010,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Komfortsollwert
// line not in menue!
// virtuelle Zeile
{0x2E3D05A5,  CAT_HK2,              VT_TEMP,          1011,  STR1011,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 - Komfortsollwert Max
{0x2E3D0590,  CAT_HK2,              VT_TEMP,          1012,  STR1012,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziertsollwert
{0x2E3D0592,  CAT_HK2,              VT_TEMP,          1014,  STR1014,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Frostschutzsollwert
{0x2E3D05F6,  CAT_HK2,              VT_FP02,          1020,  STR1020,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Steilheit
{0x2E3D05F6,  CAT_HK2,              VT_BYTE,          1020,  STR1020,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Steilheit
{0x2E3D0610,  CAT_HK2,              VT_TEMP,          1021,  STR1021,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Verschiebung
{0x2E3D0610,  CAT_HK2,              VT_TEMP_SHORT5,   1021,  STR1021,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Verschiebung
{0x2E3D060B,  CAT_HK2,              VT_ONOFF,         1026,  STR1026,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Adaption
{0x2E3D05FD,  CAT_HK2,              VT_TEMP,          1030,  STR1030,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Sommer-/ Winterheizgrenze
{0x2E3D05FD,  CAT_HK2,              VT_TEMP_SHORT,    1030,  STR1030,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Sommer-/ Winterheizgrenze
{0x2E3D0640,  CAT_HK2,              VT_TEMP,          1032,  STR1032,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Tagesheizgrenze
{0x223D0663,  CAT_HK2,              VT_TEMP,          1040,  STR1040,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Vorlaufsollwert Minimum
{0x223D0662,  CAT_HK2,              VT_TEMP,          1041,  STR1041,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Vorlaufsollwert Maximum
{0x223D0A88,  CAT_HK2,              VT_TEMP,          1042,  STR1042,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Vorlaufsollwert Raumthermostat // Command ID tbc
{0x2E3D0603,  CAT_HK2,              VT_PERCENT,       1050,  STR1050,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [% ] - Heizkreis 2 (nur wenn aktiviert) - Raumeinfluss
{0x2E3D0614,  CAT_HK2,              VT_TEMP,          1060,  STR1060,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Raumtemperaturbegrenzung
{0x2E3D0602,  CAT_HK2,              VT_TEMP,          1070,  STR1070,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Schnellaufheizung
{0x2E3D05E8,  CAT_HK2,              VT_ENUM,          1080,  STR1080,  sizeof(ENUM1080),     ENUM1080,     DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 2 (nur wenn aktiviert) - Schnellabsenkung
{0x2E3D05FB,  CAT_HK2,              VT_BYTE,          1081,  STR1081,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 2 (nur wenn aktiviert) - Schnellabsenkung Faktor
{0x2E3D0607,  CAT_HK2,              VT_MINUTES,       1090,  STR1090,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min] - Heizkreis 2 (nur wenn aktiviert) - Einschalt-Optimierung Max.
{0x2E3D0609,  CAT_HK2,              VT_MINUTES,       1091,  STR1091,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min] - Heizkreis 2 (nur wenn aktiviert) - Ausschalt-Optimierung Max.
{0x2E3D059E,  CAT_HK2,              VT_TEMP,          1100,  STR1100,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziert-Anhebung Begin
{0x2E3D059D,  CAT_HK2,              VT_TEMP,          1101,  STR1101,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziert-Anhebung Ende
{CMD_UNKNOWN, CAT_HK2,              VT_YESNO,         1109,  STR1109,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 - Pumpendauerlauf HK2
{0x223D063A,  CAT_HK2,              VT_YESNO,         1110,  STR1110,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anlagenfrostschutz HK-Pumpe
{0x223D0674,  CAT_HK2,              VT_ONOFF,         1120,  STR1120,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - Heizkreis 2 (nur wenn aktiviert) - Überhitzschutz Pumpenkreis
{0x223D065D,  CAT_HK2,              VT_TEMP,          1130,  STR1130,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Mischerüberhöhung
{0x223D065D,  CAT_HK2,              VT_TEMP_WORD5_US, 1130,  STR1130,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Mischerüberhöhung - logged on OCI700 via LPB
{0x223D0654,  CAT_HK2,              VT_ENUM,          1132,  STR1132,  sizeof(ENUM1132),     ENUM1132,     DEFAULT_FLAG, DEV_ALL}, // Antrieb Typ
{0x223D065C,  CAT_HK2,              VT_TEMP,          1133,  STR1133,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiffernez 2-Punkt
{0x223D065A,  CAT_HK2,              VT_SECONDS_WORD,  1134,  STR1134,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 1134 Antrieb Laufzeit [s]
{0x2E3D065A,  CAT_HK2,              VT_SECONDS_WORD,  1134,  STR1134,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 1134 Antrieb Laufzeit [s] - logged on OCI700 via LPB
{0x223D0658,  CAT_HK2,              VT_TEMP,          1135,  STR1135,  0,                    NULL,         FL_OEM, DEV_ALL}, // TODO Thision 1135 Mischer P-Band XP [K]
{0x223D0659,  CAT_HK2,              VT_SECONDS_WORD,  1136,  STR1136,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x2E3D067B,  CAT_HK2,              VT_ENUM,          1150,  STR1150,  sizeof(ENUM1150),     ENUM1150,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Estrichfunktion
{0x2E3D068A,  CAT_HK2,              VT_TEMP,          1151,  STR1151,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Estrich sollwert manuell
{0x2E3D067D,  CAT_HK2,              VT_TEMP,          1155,  STR1155,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 1155 Estrich Sollwert aktuell [Tage]
{0x2E3D067C,  CAT_HK2,              VT_DAYS,          1156,  STR1156,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Estrich Tag aktuell
{0x2E3D0DF2,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Estrich Tag erfüllt
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_090_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_107_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_123_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_138_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_162_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_163_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_171_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_195_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software
{0x223D0B43,  CAT_HK2,              VT_DAYS,          1157,  STR1157,  0,                    NULL,         FL_RONLY, DEV_203_ALL}, // Estrich Tag erfüllt? logged from ACS700 diagnosis software

{0x223D08C9,  CAT_HK2,              VT_ENUM,          1161,  STR1161,  sizeof(ENUM1161),     ENUM1161,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Übertemperaturabnahme
{0x223D065E,  CAT_HK2,              VT_PERCENT,       1164,  STR1164,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Sperrsignalverstärkung
{0x2E3D07C4,  CAT_HK2,              VT_YESNO,         1170,  STR1170,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Mit Pufferspeicher
{0x2E3D07C5,  CAT_HK2,              VT_YESNO,         1172,  STR1172,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Mit Vorregler/Zubring`pumpe
{0x223D04AD,  CAT_HK2,              VT_ENUM,          1180,  STR1180,  sizeof(ENUM1180),     ENUM1180,     DEFAULT_FLAG, DEV_ALL}, // HK2 Pumpe Drehzahlreduktion
{0x223D04AB,  CAT_HK2,              VT_PERCENT,       1182,  STR1182,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum
{0x223D04AA,  CAT_HK2,              VT_PERCENT,       1183,  STR1183,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum
{0x063D07BE,  CAT_HK2,              VT_ENUM,          1200,  STR1200,  sizeof(ENUM1200),     ENUM1200,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Betriebsartumschaltung
{0x063D07BE,  CAT_HK2,              VT_ENUM,          1200,  STR1200,  sizeof(ENUM1200_2),   ENUM1200_2,   DEFAULT_FLAG, DEV_096_ALL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Betriebsartumschaltung

// Einstellungen Heizkreis P/3, only visible when Heizkreis P exists
{0x2F3D0574,  CAT_HKP,              VT_ENUM,          1300,  STR1300,  sizeof(ENUM1300),     ENUM1300,     DEFAULT_FLAG, DEV_ALL}, // Betriebsart
{0x2F3D0572,  CAT_HKP,              VT_ONOFF,         1301,  STR1301,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 3/P - Präsenztaste (Absenkmodus bis zum nächsten BA-Wechsel laut Zeitplan) ***(virtuelle Zeile)***
{0x2F3D058E,  CAT_HKP,              VT_TEMP,          1310,  STR1310,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Komfortsollwert
{0x2F3D05A5,  CAT_HKP,              VT_TEMP,          1311,  STR1311,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P - Komfortsollwert Max
{0x2F3D0590,  CAT_HKP,              VT_TEMP,          1312,  STR1312,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziertsollwert
{0x2F3D0592,  CAT_HKP,              VT_TEMP,          1314,  STR1314,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Frostschutzsollwert
{0x2F3D05F6,  CAT_HKP,              VT_FP02,          1320,  STR1320,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Steilheit
{0x2F3D0610,  CAT_HKP,              VT_TEMP,          1321,  STR1321,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Verschiebung
{0x2F3D060B,  CAT_HKP,              VT_ONOFF,         1326,  STR1326,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Adaption
{0x2F3D05FD,  CAT_HKP,              VT_TEMP,          1330,  STR1330,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Sommer-/ Winterheizgrenze
{0x2F3D0640,  CAT_HKP,              VT_TEMP,          1332,  STR1332,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Tagesheizgrenze
{0x233D0663,  CAT_HKP,              VT_TEMP,          1340,  STR1340,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Vorlaufsollwert Minimum
{0x233D0662,  CAT_HKP,              VT_TEMP,          1341,  STR1341,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Vorlaufsollwert Maximum
{0x233D0A88,  CAT_HKP,              VT_PERCENT,       1350,  STR1350,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [% ] - Heizkreis 3/P (nur wenn aktiviert) - Raumeinfluss
{0x2F3D0614,  CAT_HKP,              VT_TEMP   ,       1360,  STR1360,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Raumtemperaturbegrenzung
{0x2F3D0602,  CAT_HKP,              VT_TEMP,          1370,  STR1370,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Schnellaufheizung
{0x2F3D05E8,  CAT_HKP,              VT_ENUM,          1380,  STR1380,  sizeof(ENUM1380),     ENUM1380,     DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 3/P (nur wenn aktiviert) - Schnellabsenkung
{0x2F3D05FB,  CAT_HKP,              VT_BYTE,          1381,  STR1381,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Heizkreis 3/P (nur wenn aktiviert) - Schnellabsenkung Faktor
{0x2F3D0607,  CAT_HKP,              VT_MINUTES,       1390,  STR1390,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min] - Heizkreis 3/P (nur wenn aktiviert) - Einschalt-Optimierung Max.
{0x2F3D0609,  CAT_HKP,              VT_MINUTES,       1391,  STR1391,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min] - Heizkreis 3/P (nur wenn aktiviert) - Ausschalt-Optimierung Max.
{0x2F3D059E,  CAT_HKP,              VT_TEMP,          1400,  STR1400,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziert-Anhebung Begin
{0x2F3D059D,  CAT_HKP,              VT_TEMP,          1401,  STR1401,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziert-Anhebung Ende
{0x233D063A,  CAT_HKP,              VT_YESNO,         1410,  STR1410,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anlagenfrostschutz HK-Pumpe
{0x233D0674,  CAT_HKP,              VT_ONOFF,         1420,  STR1420,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - Heizkreis 3/P (nur wenn aktiviert) - Überhitzschutz Pumpenkreis
{0x233D065D,  CAT_HKP,              VT_TEMP,          1430,  STR1430,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Mischerüberhöhung
{0x233D065C,  CAT_HKP,              VT_TEMP,          1433,  STR1433,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiffernez 2-Punkt
{0x233D065A,  CAT_HKP,              VT_SECONDS_WORD,  1434,  STR1434,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Antrieb Laufzeit HKP
{0x2F3D065A,  CAT_HKP,              VT_SECONDS_WORD,  1434,  STR1434,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 1134 Antrieb Laufzeit [s] - logged on OCI700 via LPB
{0x233D0658,  CAT_HKP,              VT_TEMP,          1435,  STR1435,  0,                    NULL,         FL_OEM, DEV_ALL}, // TODO Thision 1135 Mischer P-Band XP [K]
{0x233D0659,  CAT_HKP,              VT_SECONDS_WORD,  1436,  STR1436,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x2F3D067B,  CAT_HKP,              VT_ENUM,          1450,  STR1450,  sizeof(ENUM1450),     ENUM1450,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Estrichfunktion
{0x2F3D068A,  CAT_HKP,              VT_TEMP,          1451,  STR1451,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Estrich sollwert manuell
{0x2F3D067D,  CAT_HKP,              VT_TEMP,          1455,  STR1455,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Estrich Sollwert aktuell
{0x2F3D067C,  CAT_HKP,              VT_DAYS,          1456,  STR1456,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Estrich Tag aktuell
{0x233D0DF2,  CAT_HKP,              VT_BYTE,          1457,  STR1457,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Estrich Tag erfüllt
{0x233D08C9,  CAT_HKP,              VT_ENUM,          1461,  STR1461,  sizeof(ENUM1461),     ENUM1461,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Übertemperaturabnahme
{0x233D065E,  CAT_HKP,              VT_PERCENT,       1464,  STR1464,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Sperrsignalverstärkung
{0x2F3D07C4,  CAT_HKP,              VT_YESNO,         1470,  STR1470,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Mit Pufferspeicher
{0x2F3D07C5,  CAT_HKP,              VT_YESNO,         1472,  STR1472,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Mit Vorregler/Zubring`pumpe
{0x233D04AB,  CAT_HKP,              VT_PERCENT,       1482,  STR1482,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum
{0x233D04AA,  CAT_HKP,              VT_PERCENT,       1483,  STR1483,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum
{0x073D07BE,  CAT_HKP,              VT_ENUM,          1500,  STR1500,  sizeof(ENUM1500),     ENUM1500,     DEFAULT_FLAG, DEV_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Betriebsartumschaltung
{0x073D07BE,  CAT_HKP,              VT_ENUM,          1500,  STR1500,  sizeof(ENUM1500_2),   ENUM1500_2,   DEFAULT_FLAG, DEV_096_ALL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Betriebsartumschaltung

// Einstellungen Trinkwasser
{0x313D0571,  CAT_TW,               VT_ENUM,          1600,  STR1600,  sizeof(ENUM1600),     ENUM1600,     DEFAULT_FLAG, DEV_ALL}, // [-] - Trinkwasser - Trinkwasserbetrieb Ein/Aus ***(virtuelle Zeile)***
{0x253D1158,  CAT_TW,               VT_ENUM,          1600,  STR1600,  sizeof(ENUM1600),     ENUM1600,     DEFAULT_FLAG, DEV_211_ALL}, // [-] - Trinkwasser - Trinkwasserbetrieb Ein/Aus ***(virtuelle Zeile)***
{0x313D0573,  CAT_TW,               VT_ONOFF,         1601,  STR1601,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Trinkwasser - Manueller Push Ein/Aus ***(virtuelle Zeile)***
{0x313D0212,  CAT_TW,               VT_BIT,           1602,  STR1602,  sizeof(ENUM1602),     ENUM1602,     DEFAULT_FLAG, DEV_ALL}, // Status Trinkwasserbereitung
{0x31000212,  CAT_TW,               VT_BIT,           1602,  STR1602,  sizeof(ENUM1602),     ENUM1602,     DEFAULT_FLAG, DEV_ALL}, // Status Trinkwasserbereitung
{0x313D06B9,  CAT_TW,               VT_TEMP,          1610,  STR1610,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser - Nennsollwert
{0x313D06BA,  CAT_TW,               VT_TEMP,          1612,  STR1612,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser - Reduziertsollwert
{0x313D06B8,  CAT_TW,               VT_TEMP,          1614,  STR1614,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Trinkwasser - Nennsollwert Maximum
{0x253D0722,  CAT_TW,               VT_ENUM,          1620,  STR1620,  sizeof(ENUM1620),     ENUM1620,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Freigabe
{0x253D0722,  CAT_TW,               VT_ENUM,          1620,  STR1620,  sizeof(ENUM1620_2),   ENUM1620_2,   DEFAULT_FLAG, DEV_108_ALL}, // [0] - Trinkwasser - Freigabe
{0x313D0721,  CAT_TW,               VT_ENUM,          1630,  STR1630,  sizeof(ENUM1630),     ENUM1630,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Ladevorgang
{0x313D0759,  CAT_TW,               VT_ENUM,          1640,  STR1640,  sizeof(ENUM1640),     ENUM1640,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Legionellenfunktion
{0x313D0738,  CAT_TW,               VT_DAYS,          1641,  STR1641,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [Tage ] - Trinkwasser - Legionellenfkt. Periodisch
{0x313D075E,  CAT_TW,               VT_ENUM,          1642,  STR1642,  sizeof(ENUM_WEEKDAY), ENUM_WEEKDAY, DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Legionellenfkt. Wochentag
{0x313D075A,  CAT_TW,               VT_HOUR_MINUTES,  1644,  STR1644,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [hh:mm ] - Trinkwasser - Legionellenfkt. Zeitpunkt
{0x313D06BC,  CAT_TW,               VT_TEMP,          1645,  STR1645,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser - Legionellenfkt. Sollwert
{0x113D06BC,  CAT_TW,               VT_TEMP,          1645,  STR1645,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Trinkwasser - Legionellenfkt. Sollwert - logged on OCI700 via LPB
{0x313D0496,  CAT_TW,               VT_MINUTES_WORD,  1646,  STR1646,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [min] - Trinkwasser - Legionellenfkt. Verweildauer
{0x313D08AB,  CAT_TW,               VT_ONOFF,         1647,  STR1647,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Legionellenfkt. Zirk`pumpe
{0x253D072E,  CAT_TW,               VT_ENUM,          1660,  STR1660,  sizeof(ENUM1660),     ENUM1660,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Zirkulationspumpe Freigabe
{0x253D0689,  CAT_TW,               VT_ONOFF,         1661,  STR1661,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser - Zirk`pumpe Taktbetrieb
{0x253D077E,  CAT_TW,               VT_TEMP,          1663,  STR1663,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser - Zirkulations Sollwert
{0x053D0E84,  CAT_TW,               VT_ENUM,          1680,  STR1680,  sizeof(ENUM1680),     ENUM1680,     DEFAULT_FLAG, DEV_ALL}, // Betriebsartumschaltung

// Hx-Pumpe
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2008,  STR2008,  0,                    NULL,         FL_OEM, DEV_ALL}, // H1 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_ONOFF,         2010,  STR2010,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - H1/H3-Pumpe (nur wenn aktiviert) - H1 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2012,  STR2012,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - H1/H3-Pumpe (nur wenn aktiviert) - H1 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2014,  STR2014,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - H1/H3-Pumpe (nur wenn aktiviert) - H1 Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_UNKNOWN,       2015,  STR2015,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H1 Kälteanforderung
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2033,  STR2033,  0,                    NULL,         FL_OEM, DEV_ALL}, // H2 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_ONOFF,         2035,  STR2035,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H2 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2037,  STR2037,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H2 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2039,  STR2039,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H2 Vorregler / Zubring'pumpe
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_UNKNOWN,       2040,  STR2040,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H2 Kälteanforderung
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2044,  STR2044,  0,                    NULL,         FL_OEM, DEV_ALL}, // H3 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_ONOFF,         2046,  STR2046,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - H1/H3-Pumpe (nur wenn aktiviert) - H3 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2048,  STR2048,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - H1/H3-Pumpe (nur wenn aktiviert) - H3 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_YESNO,         2050,  STR2050,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - H1/H3-Pumpe (nur wenn aktiviert) - H3 Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HXPUMPE,          VT_UNKNOWN,       2051,  STR2051,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // H3 Kälteanforderung

// Schwimmbad
{0x493D0555,  CAT_SCHWIMMBAD,       VT_TEMP,          2055,  STR2055,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwert Solarbeheizung
{CMD_UNKNOWN, CAT_SCHWIMMBAD,       VT_UNKNOWN,       2056,  STR2056,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwert Erzeugerbeheizung
{CMD_UNKNOWN, CAT_SCHWIMMBAD,       VT_YESNO,         2065,  STR2065,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ladevorrang Solar
{CMD_UNKNOWN, CAT_SCHWIMMBAD,       VT_UNKNOWN,       2070,  STR2070,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schwimmbadtemp Maximum
{CMD_UNKNOWN, CAT_SCHWIMMBAD,       VT_YESNO,         2080,  STR2080,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mit Solareinbindung

// Vorregler/Zubringerpumpe
{0x1D3D079D,  CAT_VORREGLERPUMPE,   VT_TEMP,          2110,  STR2110,  0,                    NULL,         FL_OEM, DEV_ALL}, // Vorlaufsollwert Minimum
{0x1D3D07BC,  CAT_VORREGLERPUMPE,   VT_TEMP,          2111,  STR2111,  0,                    NULL,         FL_OEM, DEV_ALL}, // Vorlaufsollwert Maximum
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2112,  STR2112,  0,                    NULL,         FL_OEM, DEV_ALL}, // Vorlaufsollwert Kühlen Min
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2130,  STR2130,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischerüberhöhung
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2131,  STR2131,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischerunterkühlung
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_ENUM,          2132,  STR2132,  sizeof(ENUM2132),     ENUM2132,     FL_OEM, DEV_ALL}, // Antrieb Typ
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2133,  STR2133,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schaltdifferenz 2-Punkt
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2134,  STR2134,  0,                    NULL,         FL_OEM, DEV_ALL}, // Antrieb Laufzeit
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2135,  STR2135,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer P-Band Xp
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_UNKNOWN,       2136,  STR2136,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{CMD_UNKNOWN, CAT_VORREGLERPUMPE,   VT_ENUM,          2150,  STR2150,  sizeof(ENUM2150),     ENUM2150,     DEFAULT_FLAG, DEV_ALL}, // Vorregler/Zubringerpumpe

// Kessel
{0x0D3D0949,  CAT_KESSEL,           VT_ENUM,          2200,  STR2200,  sizeof(ENUM2200),     ENUM2200,     FL_OEM, DEV_ALL}, // Kessel - Betriebsart
{0x0D3D08D3,  CAT_KESSEL,           VT_ONOFF,         2201,  STR2201,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2201 Erzeugersperre [Ein/Aus]
{0x113D04D3,  CAT_KESSEL,           VT_TEMP,          2203,  STR2203,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe unter Außentemp
{0x113D11F3,  CAT_KESSEL,           VT_TEMP,          2204,  STR2204,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe über Außentemp
{0x053D0D16,  CAT_KESSEL,           VT_ENUM,          2205,  STR2205,  sizeof(ENUM2205),     ENUM2205,     DEFAULT_FLAG, DEV_ALL}, // Bei Ökobetrieb
{0x053D0236,  CAT_KESSEL,           VT_ENUM,          2206,  STR2206,  sizeof(ENUM2206),     ENUM2206,     DEFAULT_FLAG, DEV_ALL}, // Kessel - Standby/Betrieb
{0x113D0B50,  CAT_KESSEL,           VT_ONOFF,         2208,  STR2208,  0,                    NULL,         FL_OEM, DEV_ALL}, // Durchladung Pufferspeicher (EIN/AUS)
{0x0D3D092C,  CAT_KESSEL,           VT_TEMP,          2210,  STR2210,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Kessel - Sollwert Minimum
// Parameter below is from Elco Thision S 17.1 (devcie family 97) via OCI. So far no possibility to detect presence of OCI and react to different command IDs from OCI420 vis-a-vis direct BSB connection.
//{0x2D3D092C,  CAT_KESSEL,           VT_TEMP_WORD5_US, 2210,  STR2210,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Kessel - Sollwert Minimum - logged on OCI700 via LPB
{0x193D0663,  CAT_KESSEL,           VT_TEMP_WORD5_US, 2210,  STR2210,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Kessel - Sollwert Minimum - logged on LMU64 via OCI700
{0x0D3D092D,  CAT_KESSEL,           VT_TEMP,          2211,  STR2211,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Sollwert Minimum OEM
{0x0D3D092B,  CAT_KESSEL,           VT_TEMP,          2212,  STR2212,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Kessel - Sollwert maximum
// Parameter below is from Elco Thision S 17.1 (devcie family 97) via OCI. So far no possibility to detect presence of OCI and react to different command IDs from OCI420 vis-a-vis direct BSB connection.
//{0x093D0952,  CAT_KESSEL,           VT_TEMP_WORD5_US, 2212,  STR2212,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Kessel - Sollwert maximum - logged on OCI700 via LPB
{0x193D0662,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2212,  STR2212,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Kessel - Sollwert maximum - logged on LMU64 via OCI700
{0x053D08F3,  CAT_KESSEL,           VT_TEMP,          2213,  STR2213,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Sollwert Maximum OEM
// command with same command id as line 2270
{0x0D3D08EB,  CAT_KESSEL,           VT_TEMP,          2214,  STR2214,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2214 Sollwert Handbetrieb [°C]
{0x11052F87,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2215,  STR2215,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Max. Regeldiff. ohne Abbruch der Mindestpause (von LMU64 Parameter 517/113)
{0x0D3D0932,  CAT_KESSEL,           VT_UINT,          2220,  STR2220,  0,                    NULL,         FL_OEM, DEV_ALL}, // Freigabeintegral Stufe 2 °Cmin[0-500]
{0x0D3D0933,  CAT_KESSEL,           VT_UINT,          2221,  STR2221,  0,                    NULL,         FL_OEM, DEV_ALL}, // Rückstellintegral Stufe 2 °Cmin[0-500]
{0x0D3D08BE,  CAT_KESSEL,           VT_SECONDS_SHORT, 2222,  STR2222,  0,                    NULL,         FL_OEM, DEV_ALL}, // Zwangseinschaltung Stufe 2
{0x113D08F6,  CAT_KESSEL,           VT_SECONDS_WORD5, 2232,  STR2232,  0,                    NULL,         FL_OEM, DEV_ALL}, // Klappenantrieb Laufzeit
{0x113D08F5,  CAT_KESSEL,           VT_TEMP,          2233,  STR2233,  0,                    NULL,         FL_OEM, DEV_ALL}, // Klappenantrieb P-Band Xp
{0x113D08F7,  CAT_KESSEL,           VT_SECONDS_WORD,  2234,  STR2234,  0,                    NULL,         FL_OEM, DEV_ALL}, // Klappenantrieb Nach'zeit Tn
{0x113D08F8,  CAT_KESSEL,           VT_SECONDS_SHORT4,2235,  STR2235,  0,                    NULL,         FL_OEM, DEV_ALL}, // Klappenantrieb Vorh'zeit Tv
{0x113D10C4,  CAT_KESSEL,           VT_TEMP,          2236,  STR2236,  0,                    NULL,         FL_OEM, DEV_ALL}, // P-Band Xp Trinkwasser
{0x113D10C5,  CAT_KESSEL,           VT_SECONDS_WORD,  2237,  STR2237,  0,                    NULL,         FL_OEM, DEV_ALL}, // Nachstellzeit (Tn) Trinkwasser
{0x113D10C6,  CAT_KESSEL,           VT_SECONDS_SHORT, 2238,  STR2238,  0,                    NULL,         FL_OEM, DEV_ALL}, // Vorhaltezeit (Tv) Trinkwasser
{0x0D3D0928,  CAT_KESSEL,           VT_TEMP,          2240,  STR2240,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schaltdifferenz Kessel
{0x0D3D0939,  CAT_KESSEL,           VT_MINUTES_SHORT, 2241,  STR2241,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel Brennerlaufzeit Minimum
{0x39050939,  CAT_KESSEL,           VT_SECONDS_WORD,  2241,  STR2241,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel Brennerlaufzeit Minimum
{0x053D0C02,  CAT_KESSEL,           VT_MINUTES_WORD,  2243,  STR2243,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brennpausenzeit Minimum
{0x053D2F87,  CAT_KESSEL,           VT_TEMP,          2245,  STR2245,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // SD Brennerpause
{0x113D0BCC,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpennachlaufzeit
{0x113D0BCC,  CAT_KESSEL,           VT_MINUTES_WORD,  2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_064_ALL}, // Pumpennachlaufzeit
{0x113D11A4,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_123_ALL}, // [ min] Kessel - Pumpennachlaufzeit
{0x113D11A4,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_162_ALL}, // [ min] Kessel - Pumpennachlaufzeit
{0x113D11A4,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_163_ALL}, // [ min] Kessel - Pumpennachlaufzeit
{0x113D11A4,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_195_ALL}, // [ min] Kessel - Pumpennachlaufzeit
{0x113D11A4,  CAT_KESSEL,           VT_MINUTES_SHORT, 2250,  STR2250,  0,                    NULL,         FL_OEM, DEV_203_ALL}, // [ min] Kessel - Pumpennachlaufzeit
{0x113D0F85,  CAT_KESSEL,           VT_MINUTES_SHORT, 2253,  STR2253,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpennachlaufzeit n. TWW-Betrieb
{0x053D08FE,  CAT_KESSEL,           VT_ONOFF,         2260,  STR2260,  0,                    NULL,         FL_OEM, DEV_ALL}, // Anfahrentlast Verbraucher
{0x113D093A,  CAT_KESSEL,           VT_ONOFF,         2261,  STR2261,  0,                    NULL,         FL_OEM, DEV_ALL}, // Anfahrentlast Kesselpumpe
{0x053D0437,  CAT_KESSEL,           VT_ONOFF,         2262,  STR2262,  0,                    NULL,         FL_OEM, DEV_ALL}, // Einschaltoptimierung
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_021_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_036_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_049_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_050_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_090_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_096_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0908,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x0D3D08EB,  CAT_KESSEL,           VT_TEMP,          2270,  STR2270,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Kessel - Rücklaufsollwert Minimum
{0x053D0549,  CAT_KESSEL,           VT_TEMP,          2271,  STR2271,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Rücklaufsollwert Min OEM
{0x053D08FD,  CAT_KESSEL,           VT_ONOFF,         2272,  STR2272,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Rückl'einfluss Verbraucher
{0x053D090C,  CAT_KESSEL,           VT_SECONDS_WORD,  2282,  STR2282,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel - Antrieb Laufzeit
{0x053D090A,  CAT_KESSEL,           VT_TEMP,          2283,  STR2283,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Mischer P-Band Xp
{0x053D090B,  CAT_KESSEL,           VT_SECONDS_WORD,  2284,  STR2284,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel - Mischer Nachstellzeit
{0x053D095E,  CAT_KESSEL,           VT_SECONDS_SHORT4,2285,  STR2285,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel - Mischer Vorhaltezeit Tv
{0x113D0946,  CAT_KESSEL,           VT_TEMP,          2290,  STR2290,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Kessel - Schaltdiff Bypasspumpe
{0x113D0947,  CAT_KESSEL,           VT_ENUM,          2291,  STR2291,  sizeof(ENUM2291),     ENUM2291,     FL_OEM, DEV_ALL}, // Schaltdiff Bypasspumpe
{0x113D063C,  CAT_KESSEL,           VT_ONOFF,         2300,  STR2300,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kessel - Anl'frostschutz Kess'pumpe (an/aus)
{0x053D1182,  CAT_KESSEL,           VT_ONOFF,         2301,  STR2301,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kesselpumpe bei Erzeugersperre
{0x053D1258,  CAT_KESSEL,           VT_ENUM,          2305,  STR2305,  sizeof(ENUM2305),     ENUM2305,     DEFAULT_FLAG, DEV_ALL}, // Wirkung Erzeugersperre
{0x053D1258,  CAT_KESSEL,           VT_ENUM,          2305,  STR2305,  sizeof(ENUM2305_2),   ENUM2305_2,   DEFAULT_FLAG, DEV_123_ALL}, // [] Kessel - Wirkung Erzeugersperre
{0x053D1258,  CAT_KESSEL,           VT_ENUM,          2305,  STR2305,  sizeof(ENUM2305_2),   ENUM2305_2,   DEFAULT_FLAG, DEV_195_ALL}, // [] Kessel - Wirkung Erzeugersperre
{0x053D08F2,  CAT_KESSEL,           VT_ONOFF,         2310,  STR2310,  0,                    NULL,         FL_OEM, DEV_ALL}, // TR-Funktion
{0x113D0B5F,  CAT_KESSEL,           VT_TEMP,          2315,  STR2315,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temperaturhub Minimum
{0x113D0B60,  CAT_KESSEL,           VT_TEMP,          2316,  STR2316,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temperaturhub maximum
{0x053D0F84,  CAT_KESSEL,           VT_TEMP,          2317,  STR2317,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Temperaturhub nenn
{0x053D10F7,  CAT_KESSEL,           VT_ENUM,          2320,  STR2320,  sizeof(ENUM2320),     ENUM2320,     FL_RONLY, DEV_ALL}, // Pumpenmodulation
{0x053D10DF,  CAT_KESSEL,           VT_PERCENT,       2321,  STR2321,  0,                    NULL,         FL_OEM, DEV_ALL}, // Anlaufdrehzahl Kesselpumpe (%)
{0x113D0AEF,  CAT_KESSEL,           VT_PERCENT,       2322,  STR2322,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpendrehzahl minimum (%)
{0x053D1160,  CAT_KESSEL,           VT_PERCENT,       2322,  STR2322,  0,                    NULL,         FL_OEM, DEV_123_ALL}, // [%] Kessel - Pumpendrehzahl Minimum
{0x113D0AF0,  CAT_KESSEL,           VT_PERCENT,       2323,  STR2323,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpendrehzahl maximum (%)
{0x053D1161,  CAT_KESSEL,           VT_PERCENT,       2323,  STR2323,  0,                    NULL,         FL_OEM, DEV_123_ALL}, // [%] Kessel - Pumpendrehzahl maximum
{0x113D0B62,  CAT_KESSEL,           VT_TEMP,          2324,  STR2324,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl P-Band Xp
{0x113D0B63,  CAT_KESSEL,           VT_SECONDS_WORD,  2325,  STR2325,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Nachstellzeit Tn
{0x113D0D13,  CAT_KESSEL,           VT_SECONDS_SHORT4,2326,  STR2326,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Vorhaltezeit Tv
{0x053D2EF0,  CAT_KESSEL,           VT_POWER_WORD,    2330,  STR2330,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Leistung Nenn
{0x053D2F70,  CAT_KESSEL,           VT_POWER_WORD,    2331,  STR2331,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Leistung Grundstufe
{0x053D10F4,  CAT_KESSEL,           VT_PERCENT_100,   2334,  STR2334,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Leistung bei Pumpendrehz. min
{0x053D10F5,  CAT_KESSEL,           VT_PERCENT_100,   2335,  STR2335,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Leistung bei Pumpendrehz. max
{0x053D0B5D,  CAT_KESSEL,           VT_HOURS_WORD,    2340,  STR2340,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Auto Erz’folge 2 x 1 Kaskade

{0x093D2F98,  CAT_KESSEL,           VT_PERCENT,       2440,  STR2440,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2440 Gebläse-PWM Hz Maximum [%]
{0x0D3D2F94,  CAT_KESSEL,           VT_SPEED,         2441,  STR2441,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2441 Gebläsedrehzahl Hz Maximum
{0x093D120F,  CAT_KESSEL,           VT_POWER_WORD,    2441,  STR2441_2,0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Gebläseleistung Heizen Max
{0x093D120F,  CAT_KESSEL,           VT_POWER_WORD,    2441,  STR2441_2,0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Gebläseleistung Heizen Max
{0x093D120F,  CAT_KESSEL,           VT_POWER_WORD,    2441,  STR2441_2,0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Gebläseleistung Heizen Max
{0x093D120F,  CAT_KESSEL,           VT_POWER_WORD,    2441,  STR2441_2,0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Gebläseleistung Heizen Max
{0x093D120F,  CAT_KESSEL,           VT_POWER_WORD,    2441,  STR2441_2,0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Gebläseleistung Heizen Max
{0x193D2FBF,  CAT_KESSEL,           VT_PERCENT,       2442,  STR2442,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2442 Gebläse-PWM Reglerverzögerung [%]
{0x093D1211,  CAT_KESSEL,           VT_POWER_WORD,    2442,  STR2442_2,0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Gebl'leistung Durchladen Max
{0x093D1211,  CAT_KESSEL,           VT_POWER_WORD,    2442,  STR2442_2,0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Gebl'leistung Durchladen Max
{0x093D1211,  CAT_KESSEL,           VT_POWER_WORD,    2442,  STR2442_2,0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Gebl'leistung Durchladen Max
{0x093D1211,  CAT_KESSEL,           VT_POWER_WORD,    2442,  STR2442_2,0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Gebl'leistung Durchladen Max
{0x093D1211,  CAT_KESSEL,           VT_POWER_WORD,    2442,  STR2442_2,0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Gebl'leistung Durchladen Max
{0x2D3D2FD4,  CAT_KESSEL,           VT_PERCENT,       2443,  STR2443,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Brötje 2443 Gebläse-PWM Startwert DLH
{0x2E3D2FD4,  CAT_KESSEL,           VT_PERCENT,       2443,  STR2443,  0,                    NULL,         FL_RONLY, DEV_064_ALL}, // Brötje 2443 Gebläse-PWM Startwert DLH - logged on OCI700 via LPB
{0x093D1213,  CAT_KESSEL,           VT_POWER_WORD,    2443,  STR2443_2,0,                    NULL,         FL_RONLY, DEV_123_ALL}, // Gebl'leistung Startwert DLH
{0x093D1213,  CAT_KESSEL,           VT_POWER_WORD,    2443,  STR2443_2,0,                    NULL,         FL_RONLY, DEV_162_ALL}, // Gebl'leistung Startwert DLH
{0x093D1213,  CAT_KESSEL,           VT_POWER_WORD,    2443,  STR2443_2,0,                    NULL,         FL_RONLY, DEV_163_ALL}, // Gebl'leistung Startwert DLH
{0x093D1213,  CAT_KESSEL,           VT_POWER_WORD,    2443,  STR2443_2,0,                    NULL,         FL_RONLY, DEV_195_ALL}, // Gebl'leistung Startwert DLH
{0x093D1213,  CAT_KESSEL,           VT_POWER_WORD,    2443,  STR2443_2,0,                    NULL,         FL_RONLY, DEV_203_ALL}, // Gebl'leistung Startwert DLH
{0x093D2F99,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2444 Leistung Minimum [kW]
{0x093D1212,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_2,0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Gebläseleistung TWW Max
{0x093D1212,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_2,0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Gebläseleistung TWW Max
{0x093D1212,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_2,0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Gebläseleistung TWW Max
{0x093D1212,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_2,0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Gebläseleistung TWW Max
{0x093D1212,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_2,0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Gebläseleistung TWW Max
{0x093D1215,  CAT_KESSEL,           VT_POWER_WORD,    2444,  STR2444_3,0,                    NULL,         DEFAULT_FLAG, DEV_195_002}, // Gebläsedrehzahl TWW Max
{0x093D3066,  CAT_KESSEL,           VT_POWER,         2445,  STR2445,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2445 Leistung Nenn [kW]
{0x223D2EF0,  CAT_KESSEL,           VT_POWER_WORD,    2445,  STR2445,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 2444 Leistung Minimum [kW]
{0x053D1123,  CAT_KESSEL,           VT_ONOFF,         2445,  STR2445_2,0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Gebl'abschaltung Heizbetrieb
{0x053D1123,  CAT_KESSEL,           VT_ONOFF,         2445,  STR2445_2,0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Gebl'abschaltung Heizbetrieb
{0x053D1123,  CAT_KESSEL,           VT_ONOFF,         2445,  STR2445_2,0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Gebl'abschaltung Heizbetrieb
{0x053D1123,  CAT_KESSEL,           VT_ONOFF,         2445,  STR2445_2,0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Gebl'abschaltung Heizbetrieb
{0x053D1123,  CAT_KESSEL,           VT_ONOFF,         2445,  STR2445_2,0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Gebl'abschaltung Heizbetrieb
{0x053D3076,  CAT_KESSEL,           VT_SECONDS_SHORT, 2446,  STR2446,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Brötje 2446 Gebläseabschaltverzögerung
{0x053D0F7E,  CAT_KESSEL,           VT_ENUM,          2450,  STR2450,  sizeof(ENUM2450),     ENUM2450,     DEFAULT_FLAG, DEV_ALL}, // Reglerverzögerung
{0x093D2F9A,  CAT_KESSEL,           VT_SECONDS_WORD,  2451,  STR2451,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2451 Brennerpausenzeit Minimum [s]
{0x113D2F87,  CAT_KESSEL,           VT_TEMP_WORD,     2452,  STR2452,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2452 SD Brennerpause
{0x113D2F87,  CAT_KESSEL,           VT_TEMP_WORD5_US, 2452,  STR2452,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Brötje 2452 SD Brennerpause - logged on OCI700 via LPB
{0x093D1210,  CAT_KESSEL,           VT_POWER_WORD,    2452,  STR2452_2,0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Reglerverzög' Gebl'leistung
{0x093D1210,  CAT_KESSEL,           VT_POWER_WORD,    2452,  STR2452_2,0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Reglerverzög' Gebl'leistung
{0x093D1210,  CAT_KESSEL,           VT_POWER_WORD,    2452,  STR2452_2,0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Reglerverzög' Gebl'leistung
{0x093D1210,  CAT_KESSEL,           VT_POWER_WORD,    2452,  STR2452_2,0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Reglerverzög' Gebl'leistung
{0x093D1210,  CAT_KESSEL,           VT_POWER_WORD,    2452,  STR2452_2,0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Reglerverzög' Gebl'leistung
{0x093D0F7F,  CAT_KESSEL,           VT_SPEED2,        2452,  STR2452_3,0,                    NULL,         DEFAULT_FLAG, DEV_195_002}, // Reglerverzög' Drehzahl
{0x2D3D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x053D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x053D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x053D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x053D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x053D2F9B,  CAT_KESSEL,           VT_SECONDS_WORD,  2453,  STR2453,  0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Brötje 2453 Reglerverzögerung Dauer
{0x213D2F8C,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x223D2F8C,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Brötje 2454 Schaltdifferenz Kessel - logged on OCI700 via LPB
{0x113D0E08,  CAT_KESSEL,           VT_TEMP,          2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x113D0E08,  CAT_KESSEL,           VT_TEMP,          2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x113D0E08,  CAT_KESSEL,           VT_TEMP,          2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x113D0E08,  CAT_KESSEL,           VT_TEMP,          2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x113D0E08,  CAT_KESSEL,           VT_TEMP,          2454,  STR2454,  0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Brötje 2454 Schaltdifferenz Kessel
{0x213D2F8D,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x223D2F8D,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min - logged on OCI700 via LPB
{0x113D0E09,  CAT_KESSEL,           VT_TEMP,          2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x113D0E09,  CAT_KESSEL,           VT_TEMP,          2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x113D0E09,  CAT_KESSEL,           VT_TEMP,          2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x113D0E09,  CAT_KESSEL,           VT_TEMP,          2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x113D0E09,  CAT_KESSEL,           VT_TEMP,          2455,  STR2455,  0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Brötje 2455 Schaltdiff Kessel Aus Min
{0x213D2F8E,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x223D2F8E,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max - logged on OCI700 via LPB
{0x113D0E0A,  CAT_KESSEL,           VT_TEMP,          2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x113D0E0A,  CAT_KESSEL,           VT_TEMP,          2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x113D0E0A,  CAT_KESSEL,           VT_TEMP,          2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_163_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x113D0E0A,  CAT_KESSEL,           VT_TEMP,          2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_195_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x113D0E0A,  CAT_KESSEL,           VT_TEMP,          2456,  STR2456,  0,                    NULL,         DEFAULT_FLAG, DEV_203_ALL}, // Brötje 2456 Schaltdiff Kessel Aus Max
{0x113D0E0A,  CAT_KESSEL,           VT_MINUTES_SHORT, 2457,  STR2457,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einschwingzeit HK's
{0x0D3D2FBA,  CAT_KESSEL,           VT_SECONDS_SHORT, 2459,  STR2459,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2459 Sperrzeit dynam Schaltdiff [s]
{0x113D0E05,  CAT_KESSEL,           VT_TEMP,          2460,  STR2460,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiff Ein TWW
{0x113D0E06,  CAT_KESSEL,           VT_TEMP,          2461,  STR2461,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiff Aus Min TWW
{0x113D0E07,  CAT_KESSEL,           VT_TEMP,          2462,  STR2462,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiff Aus Max TWW
{0x113D0E0B,  CAT_KESSEL,           VT_MINUTES_SHORT, 2463,  STR2463,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einschwingzeit TWW
{0x053D17BC,  CAT_KESSEL,           VT_SECONDS_WORD,  2470,  STR2470,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [s] Kessel - Verz' Wärmeanfo Sonderbet
{0x113D3051,  CAT_KESSEL,           VT_MINUTES_SHORT, 2471,  STR2471,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2471 Pumpennachlaufzeit HK's [min]
{0x113D0BCC,  CAT_KESSEL,           VT_MINUTES_WORD,  2471,  STR2471,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 2471 Pumpennachlaufzeit HK's [min] - logged on OCI700 via LPB
{0x113D2F86,  CAT_KESSEL,           VT_TEMP,          2472,  STR2472,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2472 Pumpennachlauftemp TWW
{0x113D2F86,  CAT_KESSEL,           VT_TEMP_WORD5_US, 2472,  STR2472,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Brötje 2472 Pumpennachlauftemp TWW - logged on OCI700 via LPB
{0x053D0FEB,  CAT_KESSEL,           VT_ENUM,          2480,  STR2480,  sizeof(ENUM2480),     ENUM2480,     DEFAULT_FLAG, DEV_ALL}, // [enum] Kessel - Statisch' Drucküberw Absch'
{0x053D0FE9,  CAT_KESSEL,           VT_ENUM,          2500,  STR2500,  sizeof(ENUM2500),     ENUM2500,     DEFAULT_FLAG, DEV_ALL}, // Druckschalter Abschaltung
{0x093D2F84,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2521,  STR2521,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2521 Frostschutz Einschalttemp
{0x093D2F85,  CAT_KESSEL,           VT_TEMP_SHORT5_US,2522,  STR2522,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Brötje 2522 Frostschutz Ausschalttemp
{0x113D2FA9,  CAT_KESSEL,           VT_PROPVAL,       2540,  STR2540,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2540 Proportionalbeiwert Kp TWW [0..9.9375]
{0x113D2FAA,  CAT_KESSEL,           VT_PROPVAL,       2543,  STR2543,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 2543 Proportionalbeiwert Kp HK's [0..9.9375]
{0x053D1A79,  CAT_KESSEL,           VT_ONOFF,         2550,  STR2550,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [] - Kessel - Gasenergiezählung
{0x053D1A82,  CAT_KESSEL,           VT_SINT1000,      2551,  STR2551,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [] - Kessel - Gasenergiezähl Korrektur
{0x093D1ADF,  CAT_KESSEL,           VT_SECONDS_SHORT, 2560,  STR2560,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abschaltverz Abgasklappe
{0x113D0CC3,  CAT_KESSEL,           VT_ONOFF,         2630,  STR2630,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Auto Entlüftungsfunktion
{0x113D3079,  CAT_KESSEL,           VT_SECONDS_SHORT, 2655,  STR2655,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ein'dauer Entlüftung
{0x113D307A,  CAT_KESSEL,           VT_SECONDS_SHORT, 2656,  STR2656,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Aus'dauer Entlüftung
{0x113D307B,  CAT_KESSEL,           VT_BYTE,          2657,  STR2657,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anzahl Wiederholungen
{0x113D0F98,  CAT_KESSEL,           VT_SECONDS_SHORT, 2662,  STR2662,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Entlüft'dauer Heizkreis
{0x113D0F99,  CAT_KESSEL,           VT_SECONDS_SHORT, 2663,  STR2663,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Entlüft'dauer Trinkwasser

//Sitherm Pro
{0x093D303A,  CAT_SITHERM,           VT_UINT,         2700,  STR2700,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ergebnis letzter Drifttest
{0x093D0F31,  CAT_SITHERM,           VT_CURRENT,      2700,  STR2700_2,0,                    NULL,         FL_RONLY, DEV_123_ALL}, // Ion'strom gefiltert
{0x093D0F31,  CAT_SITHERM,           VT_CURRENT,      2700,  STR2700_2,0,                    NULL,         FL_RONLY, DEV_162_ALL}, // Ion'strom gefiltert
{0x093D0F31,  CAT_SITHERM,           VT_CURRENT,      2700,  STR2700_2,0,                    NULL,         FL_RONLY, DEV_163_ALL}, // Ion'strom gefiltert
{0x093D0F31,  CAT_SITHERM,           VT_CURRENT,      2700,  STR2700_2,0,                    NULL,         FL_RONLY, DEV_195_ALL}, // Ion'strom gefiltert
{0x093D0F31,  CAT_SITHERM,           VT_CURRENT,      2700,  STR2700_2,0,                    NULL,         FL_RONLY, DEV_203_ALL}, // Ion'strom gefiltert
{0x093D301E,  CAT_SITHERM,           VT_YESNO,        2702,  STR2702,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Auslösen neuer Drifttest Ja/Nein
{0x053D3042,  CAT_SITHERM,           VT_SINT,         2702,  STR2702_2,0,                    NULL,         FL_RONLY, DEV_123_ALL}, // Position Schrittmotor // todo VT_SINT verifizieren
{0x053D3042,  CAT_SITHERM,           VT_SINT,         2702,  STR2702_2,0,                    NULL,         FL_RONLY, DEV_162_ALL}, // Position Schrittmotor // todo VT_SINT verifizieren
{0x053D3042,  CAT_SITHERM,           VT_SINT,         2702,  STR2702_2,0,                    NULL,         FL_RONLY, DEV_163_ALL}, // Position Schrittmotor // todo VT_SINT verifizieren
{0x053D3042,  CAT_SITHERM,           VT_SINT,         2702,  STR2702_2,0,                    NULL,         FL_RONLY, DEV_195_ALL}, // Position Schrittmotor // todo VT_SINT verifizieren
{0x053D3042,  CAT_SITHERM,           VT_SINT,         2702,  STR2702_2,0,                    NULL,         FL_RONLY, DEV_203_ALL}, // Position Schrittmotor // todo VT_SINT verifizieren
{0x093D301F,  CAT_SITHERM,           VT_YESNO,        2703,  STR2703,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Reset Drifttest Ja/Nein
{0x053D3043,  CAT_SITHERM,           VT_SINT,         2703,  STR2703_2,0,                    NULL,         FL_RONLY, DEV_123_ALL}, // Lernwert Gasqualität  // todo VT_SINT verifizieren
{0x053D3043,  CAT_SITHERM,           VT_SINT,         2703,  STR2703_2,0,                    NULL,         FL_RONLY, DEV_162_ALL}, // Lernwert Gasqualität  // todo VT_SINT verifizieren
{0x053D3043,  CAT_SITHERM,           VT_SINT,         2703,  STR2703_2,0,                    NULL,         FL_RONLY, DEV_163_ALL}, // Lernwert Gasqualität  // todo VT_SINT verifizieren
{0x053D3043,  CAT_SITHERM,           VT_SINT,         2703,  STR2703_2,0,                    NULL,         FL_RONLY, DEV_195_ALL}, // Lernwert Gasqualität  // todo VT_SINT verifizieren
{0x053D3043,  CAT_SITHERM,           VT_SINT,         2703,  STR2703_2,0,                    NULL,         FL_RONLY, DEV_203_ALL}, // Lernwert Gasqualität  // todo VT_SINT verifizieren
{0x093D303B,  CAT_SITHERM,           VT_SINT,         2704,  STR2704,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Untergrenze Drifttest Störung
{0x093D303C,  CAT_SITHERM,           VT_SINT,         2705,  STR2705,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Obergrenze Drifttest Störung
{0x093D0F26,  CAT_SITHERM,           VT_SINT,         2705,  STR2705_2,0,                    NULL,         FL_RONLY, DEV_123_ALL}, // R-Wert
{0x093D0F26,  CAT_SITHERM,           VT_SINT,         2705,  STR2705_2,0,                    NULL,         FL_RONLY, DEV_162_ALL}, // R-Wert
{0x093D0F26,  CAT_SITHERM,           VT_SINT,         2705,  STR2705_2,0,                    NULL,         FL_RONLY, DEV_163_ALL}, // R-Wert
{0x093D0F26,  CAT_SITHERM,           VT_SINT,         2705,  STR2705_2,0,                    NULL,         FL_RONLY, DEV_195_ALL}, // R-Wert
{0x093D0F26,  CAT_SITHERM,           VT_SINT,         2705,  STR2705_2,0,                    NULL,         FL_RONLY, DEV_203_ALL}, // R-Wert
{0x093D0F62,  CAT_SITHERM,           VT_ENUM,         2706,  STR2706,  sizeof(ENUM2706),     ENUM2706,     FL_RONLY, DEV_ALL},     // Betriebsphase
{0x053D3020,  CAT_SITHERM,           VT_ONOFF,        2720,  STR2720,  0,                    NULL,         FL_RONLY, DEV_ALL},     // Freigabe Einstellung Gasart
{0x053D3041,  CAT_SITHERM,           VT_ENUM,         2721,  STR2721,  sizeof(ENUM2721),     ENUM2721,     FL_RONLY, DEV_ALL},     // Gasart
{0x093D3077,  CAT_SITHERM,           VT_ENUM,         2727,  STR2727,  sizeof(ENUM2727),     ENUM2727,     DEFAULT_FLAG, DEV_ALL}, // Zünd und Überwach'bereich
{0x153D2FF0,  CAT_SITHERM,           VT_CURRENT,      2730,  STR2730,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ionisationsstrom uA -> Gleiche ID wie STR8329
{0x153D2FF0,  CAT_SITHERM,           VT_CURRENT,      2730,  STR2730,  0,                    NULL,         FL_NO_CMD, DEV_097_ALL}, // No command
{0x153D2FF0,  CAT_SITHERM,           VT_CURRENT,      2730,  STR2730,  0,                    NULL,         FL_NO_CMD, DEV_123_ALL}, //No command
{0x093D3042,  CAT_SITHERM,           VT_UINT,         2731,  STR2731,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Position Schrittmotor
{0x093D3043,  CAT_SITHERM,           VT_SINT,         2732,  STR2732,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Lernwert Gasqualität
{0x093D1A10,  CAT_SITHERM,           VT_ENUM,         2740,  STR2702,  sizeof(ENUM2740),     ENUM2740,     DEFAULT_FLAG, DEV_ALL}, // Auslösen Drifttest
{0x093D1A11,  CAT_SITHERM,           VT_BYTE,         2741,  STR2741,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // ADA Punkt Nr
{0x093D1A13,  CAT_SITHERM,           VT_CURRENT,      2742,  STR2742,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Filterwert
{0x093D1A14,  CAT_SITHERM,           VT_CURRENT,      2743,  STR2743,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Korrektur
{0x093D1A15,  CAT_SITHERM,           VT_UINT100,      2744,  STR2744,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA vergangene Zeit
{0x093D1A12,  CAT_SITHERM,           VT_CURRENT,      2745,  STR2745,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Ergebnis // todo dies ist eigentlich Teil 2 von Parameter 2741. 2741 legt den ADA Punkt fest (1...7), dessen Wert dann unter dieser 0xID abgefragt werden kann.
{0x093D1A16,  CAT_SITHERM,           VT_ENUM,         2749,  STR2749,  sizeof(ENUM2749),     ENUM2749,     DEFAULT_FLAG, DEV_ALL}, // Reset Drifttest
{0x093D0F63,  CAT_SITHERM,           VT_BYTE,         2750,  STR2750,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Anstehende Drifttests
{0x093D1A17,  CAT_SITHERM,           VT_HOURS_WORD,   2751,  STR2751,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Zeitintervall 1
{0x093D1A18,  CAT_SITHERM,           VT_HOURS_WORD,   2752,  STR2752,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Zeitintervall 2
{0x093D1A19,  CAT_SITHERM,           VT_HOURS_WORD,   2753,  STR2753,  0,                    NULL,         FL_RONLY, DEV_ALL}, // ADA Zeitintervall 3

// Wärmepumpe
{0x593D1AB2,  CAT_WAERMEPUMPE,      VT_PERCENT,       2776,  STR2776,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pump'drehzahl Min bei TWW
{0x593D1AB3,  CAT_WAERMEPUMPE,      VT_PERCENT,       2777,  STR2777,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pump'drehzahl Max bei TWW
{0x593D1AB4,  CAT_WAERMEPUMPE,      VT_PERCENT,       2778,  STR2778,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pump'drehzahl Min Kühlbetr
{0x593D1AB5,  CAT_WAERMEPUMPE,      VT_PERCENT,       2779,  STR2779,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pump'drehzahl Max Kühlbetr 

//OEM
{0x593D186C,  CAT_WAERMEPUMPE,      VT_TEMP,          2785,  STR2785,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Max Kondensationstemp
{0x593D186E,  CAT_WAERMEPUMPE,      VT_TEMP,          2786,  STR2786,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Max Kondensationstemp SD
{0x593D186D,  CAT_WAERMEPUMPE,      VT_TEMP,          2787,  STR2787,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Max Kondens'temp Reduktion
//end OEM
{0x593D1788,  CAT_WAERMEPUMPE,      VT_ONOFF,         2789,  STR2789,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kondensatorpumpe bei TWW
{0x593D1676,  CAT_WAERMEPUMPE,      VT_TEMP_SHORT,    2790,  STR2790,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Modulation Kondensatorpumpe // Temp'Spreizung Kondensator
{0x593D1675,  CAT_WAERMEPUMPE,      VT_PERCENT,       2792,  STR2792,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum
{0x113D04AB,  CAT_WAERMEPUMPE,      VT_PERCENT,       2792,  STR2792,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Pumpendrehzahl Minimum
{0x593D1674,  CAT_WAERMEPUMPE,      VT_PERCENT,       2793,  STR2793,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum
//OEM
{0x593D166C,  CAT_WAERMEPUMPE,      VT_TEMP,          2794, STR2794,   0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl P-Band Xp
{0x593D166B,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2795, STR2795,   0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Nachstellzeit Tn
{0x593D166A,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT4,2796, STR2796,   0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Vorhaltezeit Tv
{0x593D166E,  CAT_WAERMEPUMPE,      VT_TEMP,          2799, STR2799,   0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpensollw'reduktion
//end OEM
{0x593D05CC,  CAT_WAERMEPUMPE,      VT_ONOFF,         2800,  STR2800,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Frostschutz Kondens’pumpe
{0x593D05CD,  CAT_WAERMEPUMPE,      VT_ENUM,          2801,  STR2801,  sizeof(ENUM2801),     ENUM2801,     FL_OEM,       DEV_ALL}, // Steuerung Kondens’pumpe // Temperaturanforderung
{0x593D18A0,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2802,  STR2802,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufzeit Kondens’pumpe
{0x593D18A1,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2803,  STR2803,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Nachlaufzeit Kondens’pumpe
{0x593D05CB,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2803,  STR2803,  0,                    NULL,         DEFAULT_FLAG, DEV_108_160}, // Nachlaufzeit Kondens’pumpe
{0x593D05CB,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2803,  STR2803,  0,                    NULL,         DEFAULT_FLAG, DEV_108_169}, // Nachlaufzeit Kondens’pumpe
{0x593D05CB,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2803,  STR2803,  0,                    NULL,         DEFAULT_FLAG, DEV_119_ALL}, // Nachlaufzeit Kondens’pumpe //FUJITSU
{0x593D05CB,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2803,  STR2803,  0,                    NULL,         DEFAULT_FLAG, DEV_170_ALL}, // Nachlaufzeit Kondenscpumpe //FUJITSU
{0x593D166D,  CAT_WAERMEPUMPE,      VT_TEMP,          2804,  STR2804,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Max Temp’spreizung Konden
{0x593D05BD,  CAT_WAERMEPUMPE,      VT_TEMP,          2805,  STR2805,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Soll Temp’Spreizung Kondens
{0x593D05BE,  CAT_WAERMEPUMPE,      VT_TEMP,          2806,  STR2806,  0,                    NULL,         FL_OEM, DEV_ALL}, // Max Abweich Spreiz Kondens
{0x593D0DED,  CAT_WAERMEPUMPE,      VT_TEMP,          2807,  STR2807,  0,                    NULL,         FL_OEM, DEV_ALL}, // Min Kondens’spreiz TWW
{0x593D0B89,  CAT_WAERMEPUMPE,      VT_TEMP,          2809,  STR2809,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temperatur Frost-Alarm
{0x593D1787,  CAT_WAERMEPUMPE,      VT_TEMP,          2810,  STR2810,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kondensatorfrostschutz
{0x593D1893,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2811,  STR2811,  0,                    NULL,         FL_OEM, DEV_ALL}, // Nachlauf Kond’frostschutz
{0x593D0B8A,  CAT_WAERMEPUMPE,      VT_TEMP_WORD,     2812,  STR2812,  0,                    NULL,         FL_OEM, DEV_ALL}, // Einsatzgrenze TA Min Luft
{0x593D0CF0,  CAT_WAERMEPUMPE,      VT_TEMP_WORD,     2813,  STR2813,  0,                    NULL,         FL_OEM, DEV_ALL}, // Einsatzgrenze TA Max Luft
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_TEMP,          2815,  STR2815,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Quellentemp Min Wasser
{0x593D05AE,  CAT_WAERMEPUMPE,      VT_TEMP,          2816,  STR2816,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Quellentemp Min Sole
{0x593D05BC,  CAT_WAERMEPUMPE,      VT_TEMP,          2817,  STR2817,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiff Quellenschutz
{0x593D05AF,  CAT_WAERMEPUMPE,      VT_TEMP,          2818,  STR2818,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Erhöhung Quellenschutztemp Min Estrich
{0x593D18A2,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2819,  STR2819,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Vorlaufzeit Quelle
{0x593D18A3,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2820,  STR2820,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Nachlaufzeit Quelle
{0x593D05B4,  CAT_WAERMEPUMPE,      VT_MINUTES_WORD,  2821,  STR2821,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Quellen-Anlaufzeit Maximum
{0x593D05B5,  CAT_WAERMEPUMPE,      VT_HOURS_WORD,    2822,  STR2822,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zeit Begr Quelletemp Min Sole
{0x593D17B6,  CAT_WAERMEPUMPE,      VT_MINUTES_WORD,  2827,  STR2827,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zeit Begr Quelletemp
{0x593D178C,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2839,  STR2839,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zeit Begr Quelletemp
{0x593D05C1,  CAT_WAERMEPUMPE,      VT_TEMP,          2840,  STR2840,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdiff Rücklauftemp
{0x593D0B8B,  CAT_WAERMEPUMPE,      VT_YESNO,         2841,  STR2841,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verd'laufzeit min einhalten
{0x593D04F1,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2842,  STR2842,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verdichterlaufzeit Minimum
{0x593D04F2,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2843,  STR2843,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verdichtersillstandszeit Min //FUJITSU
{0x593D05CF,  CAT_WAERMEPUMPE,      VT_TEMP,          2844,  STR2844,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ausschalttemp. max //FUJITSU
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2845,  STR2845,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Reduktion Ausschaltemp Max
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2846,  STR2846,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Heissgastemp Max
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2852,  STR2852,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // ND-Verzögerung beim Start
{0x593D0495,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2862,  STR2862,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sperrzeit Stufe/Mod //FUJITSU
{0x593D0493,  CAT_WAERMEPUMPE,      VT_INTEGRAL,      2863,  STR2863,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabeintegr Stufe2/Mod
{0x593D0494,  CAT_WAERMEPUMPE,      VT_INTEGRAL,      2864,  STR2864,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Rückstellintegr Stufe2/Mod
{0x593D0BA2,  CAT_WAERMEPUMPE,      VT_PERCENT,       2870,  STR2870,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verdichtungsmodulation Max.
{0x593D0BA3,  CAT_WAERMEPUMPE,      VT_PERCENT,       2871,  STR2871,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verdichtungsmodulation Min.
{0x593D14B4,  CAT_WAERMEPUMPE,      VT_SECONDS_WORD,  2873,  STR2873,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verdichtermod Laufzeit //FUJITSU
{0x593D0BB5,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2873,  STR2873,  0,                    NULL,         DEFAULT_FLAG, DEV_108_160}, // Verdichtermod Laufzeit
{0x593D0BB5,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2873,  STR2873,  0,                    NULL,         DEFAULT_FLAG, DEV_119_ALL}, // Verdichtermod Laufzeit
{0x053D0D00,  CAT_WAERMEPUMPE,      VT_ENUM,          2880,  STR2880,  sizeof(ENUM2880),     ENUM2880,     DEFAULT_FLAG, DEV_ALL}, // Verwendung Elektro-Vorlauf
{0x053D0D01,  CAT_WAERMEPUMPE,      VT_MINUTES,       2881,  STR2881,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sperrzeit Elektro-Vorlauf
{0x053D0D01,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2881,  STR2881,  0,                    NULL,         FL_OEM, DEV_186_ALL}, // Sperrzeit Elektro-Vorlauf
{0x053D0D02,  CAT_WAERMEPUMPE,      VT_UINT,          2882,  STR2882,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabeintegr. Elektro-Vorl °Cmin[0-500] //FUJITSU
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2883,  STR2883,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Rückstellintegr. Elektro-Vorl
{0x593D0D2E,  CAT_WAERMEPUMPE,      VT_TEMP,          2884,  STR2884,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freig Elektro-Vorl unter TA //FUJITSU
{0x593D0436,  CAT_WAERMEPUMPE,      VT_ONOFF,         2886,  STR2886,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kompensation Wärmedefizit //FUJITSU
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2893,  STR2893,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Anzahl TWW-Ladeversuche
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2894,  STR2894,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verzögerung Drehstr'fehler
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2895,  STR2895,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verzögerung Ström'wächter
{0x593D0CEA,  CAT_WAERMEPUMPE,      VT_TEMP,          2910,  STR2910,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe oberhalb TA
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2911,  STR2911,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Für Pufferzwangsladung
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       2912,  STR2912,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Durchladung Pufferspeicher
{0x593D12F3,  CAT_WAERMEPUMPE,      VT_TEMP,          2916,  STR2916,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwert WP Max TWW //FUJITSU
{0x593D0DF3,  CAT_WAERMEPUMPE,      VT_ENUM,          2920,  STR2920,  sizeof(ENUM2920),     ENUM2920,     DEFAULT_FLAG, DEV_ALL}, // Bei EW Sperre //FUJITSU
{0x593D08D5,  CAT_WAERMEPUMPE,      VT_TEMP,          2951,  STR2951,  0,                    NULL,         FL_OEM, DEV_ALL}, // Abtaufreigabe unterhalb TA
{0x593D08D6,  CAT_WAERMEPUMPE,      VT_TEMP,          2952,  STR2952,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schaltdifferenz Abtauen
{0x593D08D8,  CAT_WAERMEPUMPE,      VT_TEMP,          2954,  STR2954,  0,                    NULL,         FL_OEM, DEV_ALL}, // Verdampfertemp Abtau-Ende
{0x593D08DC,  CAT_WAERMEPUMPE,      VT_MINUTES_WORD,  2963,  STR2963,  0,                    NULL,         FL_OEM, DEV_ALL}, // Dauer bis Zwangsabtauen
{0x593D08DD,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2964,  STR2964,  0,                    NULL,         FL_OEM, DEV_ALL}, // Abtaudauer Maximal
{0x593D08DE,  CAT_WAERMEPUMPE,      VT_MINUTES_SHORT, 2965,  STR2965,  0,                    NULL,         FL_OEM, DEV_ALL}, // Abtropfdauer Verdampfer
{0x593D08DF,  CAT_WAERMEPUMPE,      VT_SECONDS_SHORT, 2966,  STR2966,  0,                    NULL,         FL_OEM, DEV_ALL}, // Abkühldauer Verdampfer
{0x593D0CF1,  CAT_WAERMEPUMPE,      VT_TEMP,          3002,  STR3002,  0,                    NULL,         FL_OEM, DEV_ALL}, // Quellentemp min Kühlbetrieb
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       3006,  STR3006,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Während Verdichterbetrieb
{CMD_UNKNOWN, CAT_WAERMEPUMPE,      VT_UNKNOWN,       3007,  STR3007,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Im passiven Kühlbetrieb
{0x593D0CF3,  CAT_WAERMEPUMPE,      VT_PERCENT,       3010,  STR3010,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehz max V'lator/Q'Pump
{0x593D0CF4,  CAT_WAERMEPUMPE,      VT_PERCENT,       3011,  STR3011,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehz min V'lator/Q'Pump
{0x593D1795,  CAT_WAERMEPUMPE,      VT_PERCENT,       3025,  STR3025,  0,                    NULL,         FL_OEM, DEV_ALL}, // Silent Mode Drehzahl Max
{0x593D17A8,  CAT_WAERMEPUMPE,      VT_HOUR_MINUTES,  3026,  STR3026,  0,                    NULL,         FL_OEM, DEV_ALL}, // Silent Mode Ein
{0x593D17A9,  CAT_WAERMEPUMPE,      VT_HOUR_MINUTES,  3027,  STR3027,  0,                    NULL,         FL_OEM, DEV_ALL}, // Silent Mode Aus
{0x593D1796,  CAT_WAERMEPUMPE,      VT_TEMP,          3028,  STR3028,  0,                    NULL,         FL_OEM, DEV_ALL}, // Silent'M Drehz'anheb Beginn
{0x593D1797,  CAT_WAERMEPUMPE,      VT_TEMP,          3029,  STR3029,  0,                    NULL,         FL_OEM, DEV_ALL}, // Silent'M Drehz'anheb Ende

// Energiezähler (Fujitsu Waterstage)
{0x053D1088,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3090,  STR3090,  sizeof(ENUM3090),     ENUM3090,     DEFAULT_FLAG, DEV_ALL}, // Impulszählung Wärme
{0x053D1089,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3092,  STR3092,  sizeof(ENUM3092),     ENUM3092,     DEFAULT_FLAG, DEV_ALL}, // Impulseinheit Wärme
{0x053D108A,  CAT_ENERGIEZAEHLER,   VT_UINT,          3093,  STR3093,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Impulswert Wärme Zähler
{0x053D108B,  CAT_ENERGIEZAEHLER,   VT_UINT,          3094,  STR3094,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Impulswert Wärme Nenner
{0x053D12B7,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3095,  STR3095,  sizeof(ENUM3095),     ENUM3095,     DEFAULT_FLAG, DEV_ALL}, // Durchflussmessung Wärme
{0x053D108C,  CAT_ENERGIEZAEHLER,   VT_LITERPERHOUR,  3097,  STR3097,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Durchfluss Heizen
{0x053D108D,  CAT_ENERGIEZAEHLER,   VT_LITERPERHOUR,  3098,  STR3098,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Durchfluss Trinkwasser
{0x053D108E,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3100,  STR3100,  sizeof(ENUM3100),     ENUM3100,     DEFAULT_FLAG, DEV_ALL}, // Impulszählung Energie
{0x053D108F,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3102,  STR3102,  sizeof(ENUM3102),     ENUM3102,     DEFAULT_FLAG, DEV_ALL}, // Impulseinheit Energie
{0x053D1090,  CAT_ENERGIEZAEHLER,   VT_UINT,          3103,  STR3103,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Impulswert Energie Zähler
{0x053D1091,  CAT_ENERGIEZAEHLER,   VT_UINT,          3104,  STR3104,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Impulswert Energie Nenner
{0x053D1092,  CAT_ENERGIEZAEHLER,   VT_ENERGY_CONTENT,3106,  STR3106,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Mittlerer Gasenergieinhalt
{0x053D1092,  CAT_ENERGIEZAEHLER,   VT_POWER_WORD,    3108,  STR3108,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Elektrische Quellenleistung
{0x053D12B8,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3109,  STR3109,  sizeof(ENUM3109),     ENUM3109,     DEFAULT_FLAG, DEV_ALL}, // Zählung Intern Elektro Vorl’
{0x053D10B3,  CAT_ENERGIEZAEHLER,   VT_STRING,        3110,  STR3110,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegebene Wärme
{0x053D10B4,  CAT_ENERGIEZAEHLER,   VT_STRING,        3113,  STR3113,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Eingesetzte Energie
{0x053D1083,  CAT_ENERGIEZAEHLER,   VT_UINT100,       3116,  STR3116,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Arbeitszahl
{0x053D1080,  CAT_ENERGIEZAEHLER,   VT_UNKNOWN,       3119,  STR3119,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Stichtag Jahresarbeitszahl Tag / Monat // 30.06. wird als 00 FF 06 1E FF FF FF FF 17 codiert, 3.+4. Byte enthalten Monat und Tag
{0x053D1721,  CAT_ENERGIEZAEHLER,   VT_STRING,        3121,  STR3121,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 1
{0x053D172B,  CAT_ENERGIEZAEHLER,   VT_STRING,        3122,  STR3122,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 1
{0x053D1983,  CAT_ENERGIEZAEHLER,   VT_STRING,        3123,  STR3123,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 1
{0x053D1735,  CAT_ENERGIEZAEHLER,   VT_STRING,        3124,  STR3124,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 1
{0x053D173F,  CAT_ENERGIEZAEHLER,   VT_STRING,        3125,  STR3125,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 1
{0x053D198D,  CAT_ENERGIEZAEHLER,   VT_STRING,        3126,  STR3126,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 1
{0x053D1722,  CAT_ENERGIEZAEHLER,   VT_STRING,        3128,  STR3128,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 2
{0x053D172C,  CAT_ENERGIEZAEHLER,   VT_STRING,        3129,  STR3129,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 2
{0x053D1984,  CAT_ENERGIEZAEHLER,   VT_STRING,        3130,  STR3130,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 2
{0x053D1736,  CAT_ENERGIEZAEHLER,   VT_STRING,        3131,  STR3131,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 2
{0x053D1740,  CAT_ENERGIEZAEHLER,   VT_STRING,        3132,  STR3132,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 2
{0x053D198E,  CAT_ENERGIEZAEHLER,   VT_STRING,        3133,  STR3133,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 2
{0x053D1723,  CAT_ENERGIEZAEHLER,   VT_STRING,        3135,  STR3135,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 3
{0x053D172D,  CAT_ENERGIEZAEHLER,   VT_STRING,        3136,  STR3136,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 3
{0x053D1985,  CAT_ENERGIEZAEHLER,   VT_STRING,        3137,  STR3137,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 3
{0x053D1737,  CAT_ENERGIEZAEHLER,   VT_STRING,        3138,  STR3138,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 3
{0x053D1741,  CAT_ENERGIEZAEHLER,   VT_STRING,        3139,  STR3139,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 3
{0x053D198F,  CAT_ENERGIEZAEHLER,   VT_STRING,        3140,  STR3140,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 3
{0x053D1724,  CAT_ENERGIEZAEHLER,   VT_STRING,        3142,  STR3142,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 4
{0x053D172E,  CAT_ENERGIEZAEHLER,   VT_STRING,        3143,  STR3143,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 4
{0x053D1986,  CAT_ENERGIEZAEHLER,   VT_STRING,        3144,  STR3144,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 4
{0x053D1738,  CAT_ENERGIEZAEHLER,   VT_STRING,        3145,  STR3145,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 4
{0x053D1742,  CAT_ENERGIEZAEHLER,   VT_STRING,        3146,  STR3146,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 4
{0x053D1990,  CAT_ENERGIEZAEHLER,   VT_STRING,        3147,  STR3147,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 4
{0x053D1725,  CAT_ENERGIEZAEHLER,   VT_STRING,        3149,  STR3149,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 5
{0x053D172F,  CAT_ENERGIEZAEHLER,   VT_STRING,        3150,  STR3150,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 5
{0x053D1987,  CAT_ENERGIEZAEHLER,   VT_STRING,        3151,  STR3151,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 5
{0x053D1739,  CAT_ENERGIEZAEHLER,   VT_STRING,        3152,  STR3152,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 5
{0x053D1743,  CAT_ENERGIEZAEHLER,   VT_STRING,        3153,  STR3153,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 5
{0x053D1991,  CAT_ENERGIEZAEHLER,   VT_STRING,        3154,  STR3154,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 5
{0x053D1726,  CAT_ENERGIEZAEHLER,   VT_STRING,        3156,  STR3156,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 6
{0x053D1730,  CAT_ENERGIEZAEHLER,   VT_STRING,        3157,  STR3157,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 6
{0x053D1988,  CAT_ENERGIEZAEHLER,   VT_STRING,        3158,  STR3158,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 6
{0x053D173A,  CAT_ENERGIEZAEHLER,   VT_STRING,        3159,  STR3159,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 6
{0x053D1744,  CAT_ENERGIEZAEHLER,   VT_STRING,        3160,  STR3160,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 6
{0x053D1992,  CAT_ENERGIEZAEHLER,   VT_STRING,        3161,  STR3161,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 6
{0x053D1727,  CAT_ENERGIEZAEHLER,   VT_STRING,        3163,  STR3163,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 7
{0x053D1731,  CAT_ENERGIEZAEHLER,   VT_STRING,        3164,  STR3164,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 7
{0x053D1989,  CAT_ENERGIEZAEHLER,   VT_STRING,        3165,  STR3165,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 7
{0x053D173B,  CAT_ENERGIEZAEHLER,   VT_STRING,        3166,  STR3166,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 7
{0x053D1745,  CAT_ENERGIEZAEHLER,   VT_STRING,        3167,  STR3167,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 7
{0x053D1993,  CAT_ENERGIEZAEHLER,   VT_STRING,        3168,  STR3168,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 7
{0x053D1728,  CAT_ENERGIEZAEHLER,   VT_STRING,        3170,  STR3170,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 8
{0x053D1732,  CAT_ENERGIEZAEHLER,   VT_STRING,        3171,  STR3171,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 8
{0x053D198A,  CAT_ENERGIEZAEHLER,   VT_STRING,        3172,  STR3172,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 8
{0x053D173C,  CAT_ENERGIEZAEHLER,   VT_STRING,        3173,  STR3173,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 8
{0x053D1746,  CAT_ENERGIEZAEHLER,   VT_STRING,        3174,  STR3174,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 8
{0x053D1994,  CAT_ENERGIEZAEHLER,   VT_STRING,        3175,  STR3175,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 8
{0x053D1729,  CAT_ENERGIEZAEHLER,   VT_STRING,        3177,  STR3177,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 9
{0x053D1733,  CAT_ENERGIEZAEHLER,   VT_STRING,        3178,  STR3178,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 9
{0x053D198B,  CAT_ENERGIEZAEHLER,   VT_STRING,        3179,  STR3179,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 9
{0x053D173D,  CAT_ENERGIEZAEHLER,   VT_STRING,        3180,  STR3180,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 9
{0x053D1747,  CAT_ENERGIEZAEHLER,   VT_STRING,        3181,  STR3181,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 9
{0x053D1995,  CAT_ENERGIEZAEHLER,   VT_STRING,        3182,  STR3182,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 9
{0x053D172A,  CAT_ENERGIEZAEHLER,   VT_STRING,        3184,  STR3184,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme Heizen 10
{0x053D1734,  CAT_ENERGIEZAEHLER,   VT_STRING,        3185,  STR3185,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Wärme TWW 10
{0x053D198C,  CAT_ENERGIEZAEHLER,   VT_STRING,        3186,  STR3186,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Abgegeb’ Kälte 10
{0x053D173E,  CAT_ENERGIEZAEHLER,   VT_STRING,        3187,  STR3187,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Heizen 10
{0x053D1748,  CAT_ENERGIEZAEHLER,   VT_STRING,        3188,  STR3188,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie TWW 10
{0x053D1996,  CAT_ENERGIEZAEHLER,   VT_STRING,        3189,  STR3189,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einges’ Energie Kühlen 10
{0x053D1087,  CAT_ENERGIEZAEHLER,   VT_YESNO,         3190,  STR3190,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Reset Stichtagspeicher
{0x053D12C0,  CAT_ENERGIEZAEHLER,   VT_ENUM,          3192,  STR3192,  sizeof(ENUM3192),     ENUM3192,     DEFAULT_FLAG, DEV_ALL}, // Zählung intern Elektro TWW
{0x053D19BA,  CAT_ENERGIEZAEHLER,   VT_UNKNOWN,       3264,  STR3264,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Energiepreis HT
{0x053D19BB,  CAT_ENERGIEZAEHLER,   VT_UNKNOWN,       3265,  STR3265,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Energiepreis NT/SG-Wunsch
{0x053D19BC,  CAT_ENERGIEZAEHLER,   VT_UNKNOWN,       3266,  STR3266,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Energiepreis SG-Zwang
{0x053D19BD,  CAT_ENERGIEZAEHLER,   VT_UNKNOWN,       3267,  STR3267,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Energiepreis Alternativ Erz";

// Kaskade
{0x153D0842,  CAT_KASKADE,          VT_ENUM,          3510,  STR3510,  sizeof(ENUM3510),     ENUM3510,     FL_OEM, DEV_ALL}, // Führungsstrategie
{0x153D0843,  CAT_KASKADE,          VT_PERCENT,       3511,  STR3511,  0,                    NULL,         FL_OEM, DEV_ALL}, // Leistungsband Minimum
{0x153D0844,  CAT_KASKADE,          VT_PERCENT,       3512,  STR3512,  0,                    NULL,         FL_OEM, DEV_ALL}, // Leistungsband Maximum
{0x0D3D0942,  CAT_KASKADE,          VT_CELMIN,     3530,  STR3530,  0,                    NULL,         FL_OEM, DEV_ALL}, // Freigabeintegral Erz’folge
{0x0D3D0943,  CAT_KASKADE,          VT_CELMIN,     3531,  STR3531,  0,                    NULL,         FL_OEM, DEV_ALL}, // Rückstellintegral Erz’folge
{0x053D0830,  CAT_KASKADE,          VT_SECONDS_WORD,  3532,  STR3532,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Wiedereinschaltsperre
{0x053D0831,  CAT_KASKADE,          VT_MINUTES_SHORT, 3533,  STR3533,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Zuschaltverzögerung
{0x053D0832,  CAT_KASKADE,          VT_SECONDS_WORD,  3534,  STR3534,  0,                    NULL,         FL_OEM, DEV_ALL}, // Zwangszeit Grundstufe
{0x053D0833,  CAT_KASKADE,          VT_HOURS_WORD,    3540,  STR3540,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Auto Erz’folge Umschaltung
{0x053D084E,  CAT_KASKADE,          VT_ENUM,          3541,  STR3541,  sizeof(ENUM3541),     ENUM3541,     DEFAULT_FLAG, DEV_ALL}, // Auto Erz’folge Ausgrenzung
{0x053D083B,  CAT_KASKADE,          VT_ENUM,          3544,  STR3544,  sizeof(ENUM3544),     ENUM3544,     DEFAULT_FLAG, DEV_ALL}, // Führender Erzeuger
{0x153D0B3C,  CAT_KASKADE,          VT_ONOFF,         3550,  STR3550,  0,                    NULL,         FL_OEM, DEV_ALL}, // Anfahrentlast Kaskad'pumpe
{0x153D0B3A,  CAT_KASKADE,          VT_TEMP,          3560,  STR3560,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Rücklaufsollwert Minimum
{0x153D0B3B,  CAT_KASKADE,          VT_TEMP,          3561,  STR3561,  0,                    NULL,         FL_OEM, DEV_ALL}, // Rücklaufsollwert Min OEM
{0x153D0B40,  CAT_KASKADE,          VT_ONOFF,         3562,  STR3562,  0,                    NULL,         FL_OEM, DEV_ALL}, // Rückl'einfluss Verbraucher
{0x153D0B3F,  CAT_KASKADE,          VT_SECONDS_WORD,  3570,  STR3570,  0,                    NULL,         FL_OEM, DEV_ALL}, // Antrieb Laufzeit
{0x153D0B3D,  CAT_KASKADE,          VT_TEMP,          3571,  STR3571,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer P-Band Xp
{0x153D0B3E,  CAT_KASKADE,          VT_SECONDS_WORD,  3572,  STR3572,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x053D0846,  CAT_KASKADE,          VT_TEMP,          3590,  STR3590,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Temp’spreizung Minimum

// Zusatzerzeuger
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3700,  STR3700,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe unter Außentemp
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3701,  STR3701,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Freigabe über Außentemp
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3705,  STR3705,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Nachlaufzeit
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3720,  STR3720,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltintegral
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3722,  STR3722,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schaltdifferenz Aus
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER,   VT_UNKNOWN,       3723,  STR3723,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sperrzeit

// Solar
{0x493D085D,  CAT_SOLAR,            VT_TEMP,          3810,  STR3810,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Temperaturdifferenz Ein
{0x193D085D,  CAT_SOLAR,            VT_TEMP_SHORT5_US,3810,  STR3810,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Temperaturdifferenz Ein - logged on OCI700 via LPB
{0x493D085C,  CAT_SOLAR,            VT_TEMP,          3811,  STR3811,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Temperaturdifferenz Aus
{0x313D085C,  CAT_SOLAR,            VT_TEMP_SHORT5_US,3811,  STR3811,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Temperaturdifferenz Aus - logged on OCI700 via LPB
{0x493D085A,  CAT_SOLAR,            VT_TEMP,          3812,  STR3812,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Ladetemp Min TWW-Speicher
{0x253D085A,  CAT_SOLAR,            VT_TEMP,          3812,  STR3812,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Ladetemp Min TWW-Speicher - logged on OCI700 via LPB
{0x493D0ADC,  CAT_SOLAR,            VT_TEMP,          3813,  STR3813,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temp’diff EIN Puffer
{0x493D0ADD,  CAT_SOLAR,            VT_TEMP,          3814,  STR3814,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temp’diff AUS Puffer
{0x493D0A07,  CAT_SOLAR,            VT_TEMP,          3815,  STR3815,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Ladetemp Min Puffer
{0x493D0ADE,  CAT_SOLAR,            VT_TEMP,          3816,  STR3816,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temp'differenz EIN Sch'bad
{0x493D0ADF,  CAT_SOLAR,            VT_TEMP,          3817,  STR3817,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temp'differenz AUS Sch'bad
{0x493D0AE7,  CAT_SOLAR,            VT_TEMP,          3818,  STR3818,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ladetemp Min Schwimmbad
{0x493D0AE3,  CAT_SOLAR,            VT_ENUM,          3822,  STR3822,  sizeof(ENUM3822),     ENUM3822,     DEFAULT_FLAG, DEV_ALL}, // Ladevorrang Speicher
{0x493D0AE0,  CAT_SOLAR,            VT_MINUTES_SHORT, 3825,  STR3825,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ladezeit relativer Vorrang
{0x493D0AE1,  CAT_SOLAR,            VT_MINUTES_SHORT, 3826,  STR3826,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Wartezeit relativer Vorrang
{0x493D0AE2,  CAT_SOLAR,            VT_MINUTES_SHORT, 3827,  STR3827,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Wartezeit Parallelbetrieb
{0x493D0AEE,  CAT_SOLAR,            VT_SECONDS_WORD,  3828,  STR3828,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Verzögerung Sekundärpumpe
{0x493D0716,  CAT_SOLAR,            VT_MINUTES_SHORT, 3830,  STR3830,  0,                    NULL,         FL_OEM, DEV_ALL}, // [min ] - Solar (nur wenn aktiviert) - Kollektorstartfunktion
{0x493D0719,  CAT_SOLAR,            VT_SECONDS_SHORT, 3831,  STR3831,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ sec ] - Solar (nur wenn aktiviert) - Mindestlaufzeit Kollek`pumpe
{0x223D3015,  CAT_SOLAR,            VT_SECONDS_SHORT, 3831,  STR3831,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [ sec ] - Solar (nur wenn aktiviert) - Mindestlaufzeit Kollek`pumpe - logged on OCI700 via LPB
{0x493D0AE4,  CAT_SOLAR,            VT_HOUR_MINUTES,  3832,  STR3832,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kollektorstartfunktion Ein
{0x493D0AE5,  CAT_SOLAR,            VT_HOUR_MINUTES,  3833,  STR3833,  0,                    NULL,         FL_OEM, DEV_ALL}, // Kollektorstartfunktion Aus
{0x493D0B12,  CAT_SOLAR,            VT_GRADIENT_SHORT,3834,  STR3834,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kollektorstartfkt Gradient
{0x493D0860,  CAT_SOLAR,            VT_TEMP,          3840,  STR3840,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Kollektor Frostschutz
{0x0D3D0860,  CAT_SOLAR,            VT_TEMP,          3840,  STR3840,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Kollektor Frostschutz - logged on OCI700 via LPB
{0x493D0865,  CAT_SOLAR,            VT_TEMP,          3850,  STR3850,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Kollektorüberhitzschutz
{0x113D0865,  CAT_SOLAR,            VT_TEMP,          3850,  STR3850,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Kollektorüberhitzschutz - logged on OCI700 via LPB
{0x493D0551,  CAT_SOLAR,            VT_TEMP,          3860,  STR3860,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Verdampfung Waermetaeger
{0x113D0551,  CAT_SOLAR,            VT_TEMP,          3860,  STR3860,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Solar (nur wenn aktiviert) - Verdampfung Waermetaeger - logged on OCI700 via LPB
{0x493D04B1,  CAT_SOLAR,            VT_PERCENT,       3870,  STR3870,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum
{0x493D04B0,  CAT_SOLAR,            VT_PERCENT,       3871,  STR3871,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum
{0x493D0AEC,  CAT_SOLAR,            VT_TEMP,          3872,  STR3872,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl P-Band Xp
{0x493D0AED,  CAT_SOLAR,            VT_SECONDS_WORD,  3873,  STR3873,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Nachstellzeit Tn
{0x493D0509,  CAT_SOLAR,            VT_ENUM,          3880,  STR3880,  sizeof(ENUM3880),     ENUM3880,     DEFAULT_FLAG, DEV_ALL}, // Frostschutzmittel
{0x493D050A,  CAT_SOLAR,            VT_PERCENT,       3881,  STR3881,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Frost'mittel Konzentration
{0x493D050C,  CAT_SOLAR,            VT_UINT,          3884,  STR3884,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendurchfluss
{0x053D0F93,  CAT_SOLAR,            VT_ENUM,          3887,  STR3887,  sizeof(ENUM3887),     ENUM3887,     DEFAULT_FLAG, DEV_ALL}, // Impulseinheit Ertrag

// Feststoffkessel
{0x513D088A,  CAT_FESTSTOFFKESSEL,  VT_ONOFF,         4102,  STR4102,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Feststoffkessel (nur wenn aktiviert) - Sperrt andere Erzeuger
{0x513D11CA,  CAT_FESTSTOFFKESSEL,  VT_ONOFF,         4103,  STR4103,  0,                    NULL,         FL_OEM, DEV_ALL}, // [0] - Feststoffkessel (nur wenn aktiviert) - Ladepriorität TWW Speicher
{0x513D0885,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4110,  STR4110,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Sollwert Minimum
{0x513D0B0C,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4112,  STR4112,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Maximaler Feststoffkessel-Sollwert
{0x513D0886,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4114,  STR4114,  0,                    NULL,         FL_OEM, DEV_ALL}, // Temperaturhub Minimum
{0x513D0887,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4130,  STR4130,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Temperaturdifferenz Ein
{0x513D0A04,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4131,  STR4131,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Temperaturdifferenz Aus
{0x513D0A06,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4133,  STR4133,  sizeof(ENUM4133),     ENUM4133,     DEFAULT_FLAG, DEV_ALL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Vergleichstempertatur
{0x513D11D1,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4134,  STR4134,  sizeof(ENUM4134),     ENUM4134,     FL_OEM, DEV_ALL}, // TWW-Speicheranbindung
{0x513D11C8,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4135,  STR4135,  sizeof(ENUM4135),     ENUM4135,     FL_OEM, DEV_ALL}, // Kesselsollwert TWW-Ladung
{0x053D11D2,  CAT_FESTSTOFFKESSEL,  VT_YESNO,         4136,  STR4136,  0,                    NULL,         FL_OEM, DEV_ALL}, // Trinkwasserladung mit Q3
{0x513D11D0,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4137,  STR4137,  sizeof(ENUM4137),     ENUM4137,     FL_OEM, DEV_ALL}, // Pufferspeicheranbindung
{0x513D11C9,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4138,  STR4138,  sizeof(ENUM4138),     ENUM4138,     FL_OEM, DEV_ALL}, // Kesselsollwert Pufferladung
{0x513D089D,  CAT_FESTSTOFFKESSEL,  VT_MINUTES_SHORT, 4140,  STR4140,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpennachlaufzeit
{0x513D0A05,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4141,  STR4141,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Übertemperaturableitung
{0x513D0884,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4153,  STR4153,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Rücklaufsollwert Minimum
{0x513D11C7,  CAT_FESTSTOFFKESSEL,  VT_ONOFF,         4158,  STR4158,  0,                    NULL,         FL_OEM, DEV_ALL}, // Vorl'einfluss Rückl'regelung
{0x513D087E,  CAT_FESTSTOFFKESSEL,  VT_SECONDS_WORD,  4163,  STR4163,  0,                    NULL,         FL_OEM, DEV_ALL}, // Antrieb Laufzeit
{0x513D0880,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4164,  STR4164,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer P-Band Xp
{0x513D087F,  CAT_FESTSTOFFKESSEL,  VT_SECONDS_WORD,  4165,  STR4165,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x513D063B,  CAT_FESTSTOFFKESSEL,  VT_ONOFF,         4170,  STR4170,  0,                    NULL,         FL_OEM, DEV_ALL}, // Anl'frostschutz Kess'pumpe
{0x513D089E,  CAT_FESTSTOFFKESSEL,  VT_MINUTES_SHORT, 4190,  STR4190,  0,                    NULL,         FL_OEM, DEV_ALL}, // Restwärmefkt Dauer Max
{0x513D066E,  CAT_FESTSTOFFKESSEL,  VT_ENUM,          4192,  STR4192,  sizeof(ENUM4192),     ENUM4192,     FL_OEM, DEV_ALL}, // Restwärmefkt Auslösung
{0x513D089F,  CAT_FESTSTOFFKESSEL,  VT_PERCENT,       4201,  STR4201,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpendrehzahl Minimum
{0x513D08A0,  CAT_FESTSTOFFKESSEL,  VT_PERCENT,       4202,  STR4202,  0,                    NULL,         FL_OEM, DEV_ALL}, // Pumpendrehzahl Maximum
{0x513D11C0,  CAT_FESTSTOFFKESSEL,  VT_TEMP,          4203,  STR4203,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl P-Band Xp
{0x513D11C2,  CAT_FESTSTOFFKESSEL,  VT_SECONDS_WORD,  4204,  STR4204,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Nachstellzeit Tn


// Pufferspeicher
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4708,  STR4708,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladungsollwert Kühlen
{0x053D0B2F,  CAT_PUFFERSPEICHER,   VT_TEMP,          4709,  STR4709,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladungsoll Heizen Min
{0x053D0B2E,  CAT_PUFFERSPEICHER,   VT_TEMP,          4710,  STR4710,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladungsoll Heizen Max
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4711,  STR4711,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladung Zeitpunkt
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4712,  STR4712,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladung Dauer Max
{0x053D0455,  CAT_PUFFERSPEICHER,   VT_ENUM,          4720,  STR4720,  sizeof(ENUM4720),     ENUM4720,     DEFAULT_FLAG, DEV_ALL}, // [0] - Pufferspeicher (nur wenn aktiviert) - Auto Erzeugersperre
{0x053D0858,  CAT_PUFFERSPEICHER,   VT_TEMP,          4721,  STR4721,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Auto Erzeugersperre SD
{0x053D0857,  CAT_PUFFERSPEICHER,   VT_TEMP,          4722,  STR4722,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Temp`diff Puffer/Heizkreis
{0x053D0A10,  CAT_PUFFERSPEICHER,   VT_TEMP,          4724,  STR4724,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Min Speichertemp Heizbetrieb
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4739,  STR4739,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Schichtschutz
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4740,  STR4740,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schichtschutz Tempdiff Max
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4743,  STR4743,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schichtschutz Vor’schauzeit
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4744,  STR4744,  0,                    NULL,         FL_OEM, DEV_ALL}, // Schichtschutz Nachstellzeit
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4746,  STR4746,  0,                    NULL,         FL_OEM, DEV_ALL}, // Trinkwasserschutz Kombi
{0x053D08A9,  CAT_PUFFERSPEICHER,   VT_TEMP,          4750,  STR4750,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Ladetemperatur
{0x053D08A8,  CAT_PUFFERSPEICHER,   VT_TEMP,          4751,  STR4751,  0,                    NULL,         FL_OEM, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Speichertemperatur Maximum
{0x053D0A0D,  CAT_PUFFERSPEICHER,   VT_TEMP,          4755,  STR4755,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Pufferspeicher (nur wenn aktiviert) - Rückkühltemperatur
{0x053D0A0A,  CAT_PUFFERSPEICHER,   VT_ONOFF,         4756,  STR4756,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Pufferspeicher (nur wenn aktiviert) - Rückkühlung TWW/HK`s
{0x053D0A0B,  CAT_PUFFERSPEICHER,   VT_ENUM,          4757,  STR4757,  sizeof(ENUM4757),     ENUM4757,     DEFAULT_FLAG, DEV_ALL}, // [0] - Pufferspeicher (nur wenn aktiviert) - Rückkühlung Kollektor
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4760,  STR4760,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ladefühler Elektroeinsatz
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4761,  STR4761,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zwangsladung mit Elektro
{0x053D0A12,  CAT_PUFFERSPEICHER,   VT_YESNO,         4783,  STR4783,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Pufferspeicher (nur wenn aktiviert) - Mit Solareinbindung
{0x053D08AD,  CAT_PUFFERSPEICHER,   VT_TEMP,          4790,  STR4790,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Temp'diff EIN Rückl'umlenk
{0x053D08AE,  CAT_PUFFERSPEICHER,   VT_TEMP,          4791,  STR4791,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Temp'diff AUS Rückl'umlenk
{0x053D0638,  CAT_PUFFERSPEICHER,   VT_ENUM,          4795,  STR4795,  sizeof(ENUM4795),     ENUM4795,     DEFAULT_FLAG, DEV_ALL}, // Vergleichstemp Rückl'umlenk
{0x053D085F,  CAT_PUFFERSPEICHER,   VT_ENUM,          4796,  STR4796,  sizeof(ENUM4796),     ENUM4796,     DEFAULT_FLAG, DEV_ALL}, // Wirksinn Rücklaufumlenkung
{0x193D0B87,  CAT_PUFFERSPEICHER,   VT_ENUM,          4810,  STR4810,  sizeof(ENUM4810),     ENUM4810,     FL_OEM, DEV_ALL}, // Durchladung
{CMD_UNKNOWN, CAT_PUFFERSPEICHER,   VT_UNKNOWN,       4811,  STR4811,  0,                    NULL,         FL_OEM, DEV_ALL}, // Durchladetemperatur Minimum
{0x193D0B88,  CAT_PUFFERSPEICHER,   VT_ENUM,          4813,  STR4813,  sizeof(ENUM4813),     ENUM4813,     FL_OEM, DEV_ALL}, // Durchladefühler

// Trinkwasserspeicher
{0x253D0737,  CAT_TWSPEICHER,       VT_ENUM,          5010,  STR5010,  sizeof(ENUM5010),     ENUM5010,     FL_OEM, DEV_ALL}, // Ladung
{0x053D0F7C,  CAT_TWSPEICHER,       VT_HOUR_MINUTES,  5011,  STR5011,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Trinkwasser-Speicher Ladevorlegungszeit
{0x313D3009,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5019,  STR5019,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Nachlad'Überhöh Schichtensp
{0x253D0720,  CAT_TWSPEICHER,       VT_TEMP,          5020,  STR5020,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser-Speicher - Vorlaufsollwertüberhöhung
{0x253D0720,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5020,  STR5020,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [°C ] - Trinkwasser-Speicher - Vorlaufsollwertüberhöhung
{0x253D07C1,  CAT_TWSPEICHER,       VT_TEMP,          5021,  STR5021,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [°C ] - Trinkwasser-Speicher - Umladeüberhöhung
{0x253D087B,  CAT_TWSPEICHER,       VT_ENUM,          5022,  STR5022,  sizeof(ENUM5022),     ENUM5022,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Ladeart
{0x253D087B,  CAT_TWSPEICHER,       VT_ENUM,          5022,  STR5022_2,sizeof(ENUM5022_2),   ENUM5022_2,   DEFAULT_FLAG, DEV_123_ALL}, // [0] - Trinkwasser-Speicher - Ladeart
{0x253D087B,  CAT_TWSPEICHER,       VT_ENUM,          5022,  STR5022_2,sizeof(ENUM5022_2),   ENUM5022_2,   DEFAULT_FLAG, DEV_162_ALL}, // [0] - Trinkwasser-Speicher - Ladeart
{0x253D087B,  CAT_TWSPEICHER,       VT_ENUM,          5022,  STR5022_2,sizeof(ENUM5022_2),   ENUM5022_2,   DEFAULT_FLAG, DEV_195_ALL}, // [0] - Trinkwasser-Speicher - Ladeart
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_090_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_096_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_103_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_107_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_108_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_116_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_119_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_123_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_138_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_162_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_163_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_170_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_171_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_172_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_195_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_203_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_205_ALL}, // TW Schaltdifferenz 1 ein
{0x313D071D,  CAT_TWSPEICHER,       VT_TEMP,          5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_211_ALL}, // TW Schaltdifferenz 1 ein
{0x213D2F8F,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5024,  STR5024,  0,                    NULL,         FL_OEM, DEV_ALL}, // Trinkwasser-Speicher Schaltdifferenz
{0x213D2F90,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5025,  STR5025,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Schaltdifferenz 1 Aus min
{0x213D2F91,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5026,  STR5026,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Schaltdifferenz 1 Aus max
{0x213D2F92,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5027,  STR5027,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Schaltdifferenz 2 Ein
{0x213D2FD5,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5028,  STR5028,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Schaltdifferenz 2 Aus min
{0x213D2F93,  CAT_TWSPEICHER,       VT_TEMP_SHORT5_US,5029,  STR5029,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Schaltdifferenz 2 Aus max
{0x253D0731,  CAT_TWSPEICHER,       VT_MINUTES_WORD,  5030,  STR5030,  0,                    NULL,         FL_OEM, DEV_ALL}, // TW Ladezeitbegrenzung //FUJITSU
{0x253D0754,  CAT_TWSPEICHER,       VT_ENUM,          5040,  STR5040,  sizeof(ENUM5040),     ENUM5040,     FL_OEM, DEV_ALL}, // TW Entladeschutz
{0x253D08A3,  CAT_TWSPEICHER,       VT_TEMP,          5050,  STR5050,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Ladetemperatur Maximum
{0x153D08A3,  CAT_TWSPEICHER,       VT_TEMP,          5050,  STR5050,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Ladetemperatur Maximum - logged on OCI700 via LPB
{0x253D08A7,  CAT_TWSPEICHER,       VT_TEMP,          5051,  STR5051,  0,                    NULL,         FL_OEM, DEV_ALL}, // Speichertemperatur Maximum
{0x253D08BD,  CAT_TWSPEICHER,       VT_TEMP,          5055,  STR5055,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Rückkühltemperatur
{0x393D08BD,  CAT_TWSPEICHER,       VT_TEMP,          5055,  STR5055,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Rückkühltemperatur - logged on OCI700 via LPB
{0x313D0713,  CAT_TWSPEICHER,       VT_ONOFF,         5056,  STR5056,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Rückkühlung Kessel/HK
{0x313D0714,  CAT_TWSPEICHER,       VT_ENUM,          5057,  STR5057,  sizeof(ENUM5057),     ENUM5057,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Rückkühlung Kollektor
{0x253D0728,  CAT_TWSPEICHER,       VT_ENUM,          5060,  STR5060,  sizeof(ENUM5060),     ENUM5060,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Elektroeinsatz Betriebsart
{0x253D0688,  CAT_TWSPEICHER,       VT_ENUM,          5061,  STR5061,  sizeof(ENUM5061),     ENUM5061,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Elektroeinsatz Freigabe
{0x253D0687,  CAT_TWSPEICHER,       VT_ENUM,          5062,  STR5062,  sizeof(ENUM5062),     ENUM5062,     DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Elektroeinsatz Regelung
{0x313D08AA,  CAT_TWSPEICHER,       VT_ONOFF,         5070,  STR5070,  0,                    NULL,         FL_OEM, DEV_ALL}, // Automatischer Push
{0x313D0B17,  CAT_TWSPEICHER,       VT_MINUTES_SHORT, 5071,  STR5071,  0,                    NULL,         FL_OEM, DEV_ALL}, // Ladevorrangzeit Push
{0x253D08CB,  CAT_TWSPEICHER,       VT_ONOFF,         5085,  STR5085,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Übertemperaturabnahme
{0x313D07C2,  CAT_TWSPEICHER,       VT_YESNO,         5090,  STR5090,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Trinkwasser-Speicher - Mit Pufferspeicher
{0x313D07C3,  CAT_TWSPEICHER,       VT_YESNO,         5092,  STR5092,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [ - ] - Trinkwasser-Speicher - Mit Vorregler/Zubring`pumpe
{0x253D0A11,  CAT_TWSPEICHER,       VT_YESNO,         5093,  STR5093,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [-] - Trinkwasser-Speicher - Mit Solareinbindung
{0x113D2F96,  CAT_TWSPEICHER,       VT_PERCENT,       5100,  STR5100,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TW Pumpe-PWM Durchladung
{0x253D08A1,  CAT_TWSPEICHER,       VT_PERCENT,       5101,  STR5101,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum %
{0x053D115C,  CAT_TWSPEICHER,       VT_PERCENT,       5101,  STR5101,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Pumpendrehzahl Minimum %
{0x053D115C,  CAT_TWSPEICHER,       VT_PERCENT,       5101,  STR5101,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Pumpendrehzahl Minimum %
{0x253D08A2,  CAT_TWSPEICHER,       VT_PERCENT,       5102,  STR5102,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Maximum %
{0x053D115D,  CAT_TWSPEICHER,       VT_PERCENT,       5102,  STR5102,  0,                    NULL,         DEFAULT_FLAG, DEV_123_ALL}, // Pumpendrehzahl Maximum %
{0x053D115D,  CAT_TWSPEICHER,       VT_PERCENT,       5102,  STR5102,  0,                    NULL,         DEFAULT_FLAG, DEV_162_ALL}, // Pumpendrehzahl Maximum %
{0x253D0B19,  CAT_TWSPEICHER,       VT_TEMP,          5103,  STR5103,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl P-Band Xp
{0x253D0B1A,  CAT_TWSPEICHER,       VT_SECONDS_WORD,  5104,  STR5104,  0,                    NULL,         FL_OEM, DEV_ALL}, // Drehzahl Nachstellzeit Tn
{0x053D10DE,  CAT_TWSPEICHER,       VT_PERCENT,       5108,  STR5108,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Anlaufdrehzahl Ladepumpe //Thision 19 Plus
{0x053D10DD,  CAT_TWSPEICHER,       VT_PERCENT,       5109,  STR5109,  0,                    NULL,         FL_RONLY, DEV_ALL}, // Anl'drehzahl Zwi'kreispumpe //Thision 19 Plus
{0x253D072C,  CAT_TWSPEICHER,       VT_TEMP,          5120,  STR5120,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischerüberhöhung
{0x253D072B,  CAT_TWSPEICHER,       VT_SECONDS_WORD,  5124,  STR5124,  0,                    NULL,         FL_OEM, DEV_ALL}, // Antrieb Laufzeit
{0x253D0729,  CAT_TWSPEICHER,       VT_TEMP,          5125,  STR5125,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer-B-Band Xp
{0x253D072A,  CAT_TWSPEICHER,       VT_SECONDS_WORD,  5126,  STR5126,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{0x253D0B53,  CAT_TWSPEICHER,       VT_ENUM,          5130,  STR5130,  sizeof(ENUM5130),     ENUM5130,     FL_OEM, DEV_ALL}, // Umladestrategie
{0x253D0B53,  CAT_TWSPEICHER,       VT_ENUM,          5130,  STR5130,  sizeof(ENUM5130_2),   ENUM5130_2,   FL_OEM, DEV_195_002}, // Umladestrategie
{0x253D0879,  CAT_TWSPEICHER,       VT_ENUM,          5131,  STR5131,  sizeof(ENUM5131),     ENUM5131,     FL_OEM, DEV_ALL}, // Vergleichstemp Umladung
{0x253D0879,  CAT_TWSPEICHER,       VT_ENUM,          5131,  STR5131,  sizeof(ENUM5131_2),   ENUM5131_2,   FL_OEM, DEV_195_002}, // Vergleichstemp Umladung
{0x253D10C9,  CAT_TWSPEICHER,       VT_TEMP,          5139,  STR5139,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Z'kreisüberhöhung Nachladen //Thision 19 Plus
{0x253D0E50,  CAT_TWSPEICHER,       VT_TEMP,          5140,  STR5140,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Zwischenkreisüberhöhung //Thision 19 Plus
{0x253D0E68,  CAT_TWSPEICHER,       VT_TEMP,          5141,  STR5141,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Z'kreistemp Überschreit Max //Thision 19 Plus
{0x253D0E51,  CAT_TWSPEICHER,       VT_SECONDS_SHORT, 5142,  STR5142,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Vorlaufsollw'führung Verzög //Thision 19 Plus
{0x313D0E67,  CAT_TWSPEICHER,       VT_YESNO,         5146,  STR5146,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Durchladen mit B36 //Thision 19 Plus
{0x253D0F94,  CAT_TWSPEICHER,       VT_TEMP,          5148,  STR5148,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Minimale Anlauftemp'diff Q33 //Thision 19 Plus
{0x253D0FED,  CAT_TWSPEICHER,       VT_SECONDS_SHORT, 5151,  STR5151,  0,                    NULL,         FL_RONLY,     DEV_ALL}, // Z'kreistemp Übersch Verzög //Thision 19 Plus

// Trinkwasser Durchl'erhitzer
{0x313D2FC5,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5400,  STR5400,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5400 Komfortsollwert [°C]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_TEMP,          5406,  STR5406,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Min Sollw'diff zu Speich'temp
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_TEMP,          5420,  STR5420,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5420 Vorlauf-Sollwertüberhöhung [°C]
{0x22052F8F,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5430,  STR5430,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einschaltdifferenz im BW-Betrieb (Fühler 1) [°C]
{0x22052F90,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5431,  STR5431,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Min. Ausschaltdifferenz im BW-Betrieb (Fühler 1) [°C]
{0x22052F91,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5432,  STR5432,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Max. Ausschaltdifferenz im BW-Betrieb (Fühler 1) [°C]
{0x22052F92,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5433,  STR5433,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Einschaltdifferenz im BW-Betrieb (Fühler 2) [°C]
{0x22052FD5,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5434,  STR5434,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Min. Ausschaltdifferenz im BW-Betrieb (Fühler 2) [°C]
{0x22052F93,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5435,  STR5435,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Max. Ausschaltdifferenz im BW-Betrieb (Fühler 2) [°C]
{0x31052FC0,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT64,  5450,  STR5450,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5450 Gradient Zapfende [K/s]
{0x31052FC1,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT64,  5451,  STR5451,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5451 Gradient Beginn Zapf Komf [K/s]
{0x31052FC2,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT64,  5452,  STR5452,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5452 Gradient Beginn Zapfung Hz [K/s]
{0x31052FB0,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5453,  STR5453,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwertkorrektur bei Komfortregelung mit 40°C
{0x31052FB1,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5454,  STR5454,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwertkorrektur bei Komfortregelung mit 60°C
{0x31052FB2,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5455,  STR5455,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwertkorrektur bei Auslaufregelung mit 40°C
{0x31052FB3,  CAT_DRUCHLERHITZER,   VT_TEMP_SHORT5,   5456,  STR5456,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Sollwertkorrektur bei Auslaufregelung mit 60°C
{0x31052FC3,  CAT_DRUCHLERHITZER,   VT_MINUTES_WORD10,5480,  STR5480,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5480 Komfortzeit ohne Hz-Anfo [min]
{0x31052FC4,  CAT_DRUCHLERHITZER,   VT_MINUTES_SHORT, 5481,  STR5481,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5481 Komfortzeit mit Hz-Anfo [min]
{0x153D3010,  CAT_DRUCHLERHITZER,   VT_SECONDS_WORD,  5482,  STR5482,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zeit TWW-FlowSwitch geschlossen
{0x193D3011,  CAT_DRUCHLERHITZER,   VT_SECONDS_WORD,  5483,  STR5483,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Zeit TWW-Komfort FlowSwitch geschlossen
{0x313D300D,  CAT_DRUCHLERHITZER,   VT_SECONDS_SHORT, 5486,  STR5486,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Reglerverzögerung bei Takten in DLH Auslaufbetr.
{0x2E3D2FDB,  CAT_DRUCHLERHITZER,   VT_SECONDS_SHORT, 5487,  STR5487,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5487 Pump'nachlauf Komf [min]
{0x2E3D2FDB,  CAT_DRUCHLERHITZER,   VT_MINUTES,       5487,  STR5487,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Pump'nachlauf Komf [min]
{0x223D301B,  CAT_DRUCHLERHITZER,   VT_SECONDS_SHORT, 5488,  STR5488,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // TODO Thision 5488 Pump'nachlauf Komf [sek]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_UNKNOWN,       5530,  STR5530,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_UNKNOWN,       5544,  STR5544,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Antrieb Laufzeit
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_UNKNOWN,       5545,  STR5545,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer P-Band Xp
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_UNKNOWN,       5546,  STR5546,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Nachstellzeit Tn
{CMD_UNKNOWN, CAT_DRUCHLERHITZER,   VT_UNKNOWN,       5547,  STR5547,  0,                    NULL,         FL_OEM, DEV_ALL}, // Mischer Vorhaltezeit Tv

// Konfiguration
{0x053D0712,  CAT_KONFIG,           VT_ENUM,          5700,  STR5700,  sizeof(ENUM5700),     ENUM5700,     DEFAULT_FLAG, DEV_ALL}, // Voreinstellung //FUJITSU
{0x2D3D2FEA,  CAT_KONFIG,           VT_BYTE,          5701,  STR5701,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 5701 Hydraulisches Schema [2..85 enum?]
{0x053D04C0,  CAT_KONFIG,           VT_ONOFF,         5710,  STR5710,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Konfiguration - Heizkreis 1
{0x2D3D04C0,  CAT_KONFIG,           VT_ONOFF,         5710,  STR5710,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Konfiguration - Heizkreis 1 - logged on OCI700 via LPB
{0x053D0A73,  CAT_KONFIG,           VT_ENUM,          5711,  STR5711,  sizeof(ENUM5711),     ENUM5711,     DEFAULT_FLAG, DEV_ALL}, // Kühlkreis 1 //FUJITSU
{0x053D0A77,  CAT_KONFIG,           VT_ENUM,          5712,  STR5712,  sizeof(ENUM5712),     ENUM5712,     DEFAULT_FLAG, DEV_ALL}, // Verwendung Mischer 1
{0x063D04C0,  CAT_KONFIG,           VT_ONOFF,         5715,  STR5715,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Konfiguration - Heizkreis 2
{0x2E3D04C0,  CAT_KONFIG,           VT_ONOFF,         5715,  STR5715,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // [0] - Konfiguration - Heizkreis 2 - logged on OCI700 via LPB
{0x073D04C0,  CAT_KONFIG,           VT_ONOFF,         5721,  STR5721,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Heizkreis 3
{0x313D071E,  CAT_KONFIG,           VT_ENUM,          5730,  STR5730,  sizeof(ENUM5730),     ENUM5730,     DEFAULT_FLAG, DEV_ALL}, // [0] - Konfiguration - Trinkwasser-Sensor B3
{0x253D071C,  CAT_KONFIG,           VT_ENUM,          5731,  STR5731,  sizeof(ENUM5731),     ENUM5731,     DEFAULT_FLAG, DEV_ALL}, // [0] - Konfiguration - Trinkwasser-Stellglied Q3
{0x113D2FE3,  CAT_KONFIG,           VT_SECONDS_SHORT, 5732,  STR5732,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 5732 TWW Pumpenpause Umsch UV [s]
{0x393D2FE3,  CAT_KONFIG,           VT_SECONDS_SHORT, 5732,  STR5732,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 5732 TWW Pumpenpause Umsch UV [s] - logged on OCI700 via LPB
{0x113D2FE4,  CAT_KONFIG,           VT_SECONDS_SHORT, 5733,  STR5733,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Thision 5733 TWW Pumpenpause Verzögerung [s]
{0x393D2FE4,  CAT_KONFIG,           VT_SECONDS_SHORT, 5733,  STR5733,  0,                    NULL,         DEFAULT_FLAG, DEV_064_ALL}, // Thision 5733 TWW Pumpenpause Verzögerung [s] - logged on OCI700 via LPB
{0x053D0F7B,  CAT_KONFIG,           VT_ENUM,          5734,  STR5734,  sizeof(ENUM5734),     ENUM5734,     FL_RONLY,     DEV_ALL}, // Grundposition TWW Uml'ventil
{0x053D0727,  CAT_KONFIG,           VT_ONOFF,         5736,  STR5736,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // [0] - Konfiguration - Trinkwasser Trennschaltung
// {CMD_UNKNOWN, CAT_KONFIG,           VT_UNKNOWN,       5737,  STR5737,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Wirksinn TW Umlenkventil
{0x053D12BC,  CAT_KONFIG,           VT_ENERGY_WORD,   5740,  STR5740,  0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Leistung Elektro TWW K6
{0x053D079C,  CAT_KONFIG,           VT_ENUM,          5760,  STR5760,  sizeof(ENUM5760),     ENUM5760,     DEFAULT_FLAG, DEV_ALL}, // Vorregler/Zubringerpumpe [Vor Pufferspeicher | Nach Pufferspeicher] (Nach Pufferspeicher)
{0x193D2FDC,  CAT_KONFIG,           VT_BIT,           5761,  STR5761,  sizeof(ENUM5761),     ENUM5761,     DEFAULT_FLAG, DEV_ALL}, // Thision 5761 Zubringerpumpe Q8 Bit 0-3 [?]
{0x053D0851,  CAT_KONFIG,           VT_ENUM,          5770,  STR5770,  sizeof(ENUM5770),     ENUM5770,     DEFAULT_FLAG, DEV_ALL}, // Erzeugertyp
{0x053D07BF,  CAT_KONFIG,         
