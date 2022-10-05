/****************************************************/
/* DEFINITIONS and TYPEDEFS                         */
/****************************************************/

#if !defined(__AVR__)
#undef uint_farptr_t
#define uint_farptr_t const char*
#endif

#ifndef LANG
#define LANG EN
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

#if defined(__AVR__)
#define PROGMEM_LATE __attribute__ (( __section__(".fini1") ))
#define PROGMEM_LATEST __attribute__ (( __section__(".fini1") ))
#else
#define PROGMEM_LATE
#define PROGMEM_LATEST
#endif

/* telegram types */
#define TYPE_00   0x00 // undecoded type sent after date/time change
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
#define TYPE_QRE  0x11 // query reset value failed (1 byte payload of unknown meaning)
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
#define ADDR_RGT3  0x08
#define ADDR_DSP1  0x0A
#define ADDR_SRVC  0x0B
#define ADDR_DSP2  0x0C
#define ADDR_DSP3  0x0D
#define ADDR_OZW   0x31
#define ADDR_FUNK  0x32
#define ADDR_RC    0x36
#define ADDR_LAN   0x42
#define ADDR_ALL   0x7F

#define BUS_BSB 0
#define BUS_LPB 1
#define BUS_PPS 2

/* special command ids */
#define CMD_UNKNOWN 0x00000000u
#define CMD_END     0xffffffffu
#define FL_WRITEABLE    0
#define FL_RONLY        1
#define FL_WONLY        2
#define FL_NO_CMD       4
#define FL_OEM          8   // Known OEM parameters are set to read-only by default. If you want to have general write-access (not recommended!) to OEM parameters, set FL_OEM to 8.
#define FL_SPECIAL_INF  16  // Flag to distinguish between INF telegrams that reverse first two bytes (like room temperature) and those who don't (like outside temperature)
#define FL_EEPROM       32  // Flag to determine whether value should be written to EEPROM
#define FL_SW_CTL_RONLY 128 //Software controlled read-only flag. if readOnlyMode = 1 then program values won't save. If readOnlyMode = 0 - new values can be set.
/* heating systems */

#define DEV_021_ALL  21,255 // RVL470
#define DEV_023_ALL  23,255 // Grünenwald RVA46.531/109
#define DEV_025_ALL  25,255 // EVI-HEAT Combi-7 / RVA43.222/109
#define DEV_028_ALL  28,255 // Brötje SOB26 / LPB
#define DEV_029_ALL  29,255 // Grünenwald RVA63.280/109
#define DEV_036_ALL  36,255 // RVL472
#define DEV_037_ALL  37,255 // RVA47.320/109
#define DEV_044_ALL  44,255 // RVD230
#define DEV_049_ALL  49,255 // Weishaupt WRS-CPU-B1
#define DEV_050_ALL  50,255 // Weishaupt
#define DEV_051_ALL  51,255 // Weishaupt WRS-EM
#define DEV_052_ALL  52,255 // Weishaupt WRS-BE
#define DEV_054_ALL  54,255 // RVP320
#define DEV_059_ALL  59,255 // Weishaupt WRS-CPU-B3
#define DEV_064_ALL  64,255 // Brötje WGB 2 (über OCI420)
#define DEV_064_097  64,97  // LMU7 über OCI420
#define DEV_068_ALL  68,255 // RVA65.643/109
#define DEV_076_ALL  76,255 // RVA63.244/160
#define DEV_080_ALL  80,255 // Hansa SND 30TK (RVS13.143/183)
#define DEV_085_ALL  85,255 // Elco Aquatop 8es
#define DEV_088_ALL  88,255 // MAN Ölheizung (MHG EcoStar 200) mit RVS53.283/180
#define DEV_090_ALL  90,255 // RVS43.222 SSR C
#define DEV_090_239  90,239 // RVS63.283/200
#define DEV_091_ALL  91,255 // AVS75.390 Erweiterungsmodul (EWM)
#define DEV_092_ALL  92,255 // AVS37.294/100 (Bedienteil von Brötje EcoTherm WGB 20 E)
#define DEV_094_ALL  94,255 // QAA75.611/101
#define DEV_095_ALL  95,255 // Brötje LogoBloc Unit L-UB 25C
#define DEV_096_ALL  96,255 // Brötje NovoCondens SOB 22C, 26C
#define DEV_097_100  97,100 // Brötje WGB 20 C
#define DEV_097_ALL  97,255 // Elco Thision S 17.1, Brötje WBS 14D
#define DEV_098_ALL  98,255 // Brötje Ecotherm Plus WGB Pro Evo 20C, EcoCondens BBS Pro EVO 15 C
#define DEV_101_ALL  103,255 // AVS37.390/227
#define DEV_103_ALL  103,255 // CTC 380 IC
#define DEV_107_ALL  107,255 // RVS43.222-Z1
#define DEV_108_ALL  108,255 // Brötje Sensotherm BSW-K
#define DEV_108_100  108,100 // Brötje BSW 8K
#define DEV_108_160  108,160 // Elco AEROTOP T07-16 mit Logon B WP 61
#define DEV_108_169  108,169 // Wärmepumpe CTA Optiheat 1-18es RVS61.843D/169
#define DEV_108_217  108,217 // Elco Wärmepumpe RVS61.843E/560
#define DEV_116_ALL  116,255 // Brötje ISR-SSR B
#define DEV_118_ALL  118,255 // AVS37.394/136 (Bedieneinheit von Thision S 17.1)
#define DEV_119_ALL  119,255 // Waterstage WP 5kw
#define DEV_122_ALL  122,255 // Baxi Luna Duo Tec MP (LMS14.001C349)
#define DEV_123_ALL  123,255 // Brötje EcoTherm Kompakt WMS 24
#define DEV_123_231  123,231 // Baxi Luna Platinum+ 1.24
#define DEV_133_ALL  133,255 // QAA75.910/349
#define DEV_134_ALL  134,255 // RVS43.345/160 (Elco Straton S 21.2 14-24 kW)
#define DEV_136_ALL  136,255 // AVS75.391/109
#define DEV_137_ALL  137,255 // AGU2.550 Mischer-ClipIn
#define DEV_138_ALL  138,255 // Brötje BOB
#define DEV_148_ALL  148,255 // RVD265/109
#define DEV_162_ALL  162,255 // Brötje WGB 15 E, WGB-S 17/20E
#define DEV_162_005  162,5   // Brötje Eco-Therm Plus WGB 20E LMS14.001A100 (K.-H. M.)
#define DEV_162_014  162,14  // Broetje WBS 22 E (FunkOdyssey)
#define DEV_163_ALL  163,255 // Brötje WGB Evo 20 H
#define DEV_164_ALL  164,255 // AVS37.295/309 Olymp WHS-500 Luft-/Wasser-Wärmepumpe
#define DEV_165_ALL  165,255 // Funkempfänger FE ISR Plus AVS71.411/349
#define DEV_170_ALL  170,255 // Fujitsu Waterstage WSYK160DC9
#define DEV_171_ALL  171,255 // Bösch PEO Wood Pellet RVS43.344/146
#define DEV_172_ALL  172,255 // SensoTherm BLW Split B (RVS21.826F/200)
#define DEV_178_ALL  178,255 // Geminox Thrs 19 (LMS14.001A236)
#define DEV_184_ALL  184,255 // OZW672.01
#define DEV_186_ALL  186,255 // AVS75.370/109
#define DEV_188_ALL  188,255 // AVS37.296/141
#define DEV_191_ALL  191,255 // AVS71.393/101
#define DEV_195_ALL  195,255 // MHG Procon E 25 HS
#define DEV_195_002  195,2   // ELCO Thision S Plus 19 (LMS14.111B109)
#define DEV_196_ALL  196,255 // Domostar GBK 25 H/SH (LMS15.191A109)
#define DEV_198_ALL  198,255 // AVS37.396/141
#define DEV_202_ALL  202,255 // Viessmann Vitotwin 300 W (RVC32.430/124)
#define DEV_203_ALL  203,255 // Elco Thision 13 Plus
#define DEV_205_ALL  205,255 // Brötje Sensotherm BLW 15 B / 12 B (RVS21.825E/100)
#define DEV_206_ALL  206,255 // AVS74.261/109
#define DEV_209_ALL  209,255 // QAA74.611/101
#define DEV_211_ALL  211,255 // Fujitsu Waterstage WSYP100DG6 (Gerätevariante: 127, Geräteidentifikation: RVS21.831F/127)
#define DEV_ALL      255,255 // All devices
#define DEV_NONE     0,0
#define DEV_PPS      0,1
#define DEV_PPS_MCBA 0,2

#define DEV_FAM_(X, Y) ((X))
#define DEV_VAR_(X, Y) ((Y))
#define DEV_FAM(...) DEV_FAM_(__VA_ARGS__)
#define DEV_VAR(...) DEV_VAR_(__VA_ARGS__)

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

const float proglist4q[] PROGMEM_LATEST = {6224, 6220, 6221, 6227, 6228, 6229, 6231, 6232, 6233, 6234, 6235, 6223, 6236, 6258, 6259, 6343, 6344};
const float params4q[] PROGMEM_LATEST = {6225, 6226, 6224, 6220, 6221, 6227, 6229, 6231, 6232, 6233, 6234, 6235, 6223, 6236, 6258, 6259, 6343, 6344};
typedef enum { //BSP = base sensors program
  BSP_INTERNAL = 20000,    // brenner durations, internal functions
  BSP_AVERAGES = 20050,  //averages values (check size!)
  BSP_DHT22 = 20100,    // DHT22 sensor
  BSP_BME280 = 20200,    // BME280 sensor
  BSP_ONEWIRE = 20300,    // One wire (Dallas) sensor
  BSP_MAX = 20500,    // MAX! sensor
  BSP_FLOAT = 20700,    // custom_floats
  BSP_LONG = 20800,    // custom_longs
  BSP_END = 20900,    // end of sensors category
} dt_sensors_base_prog_t;

//WEBCONFIG
const char CF_USEEEPROM_TXT[] PROGMEM = CF_USEEEPROM_TEXT;
const char CF_BUSTYPE_TXT[] PROGMEM = CF_BUSTYPE_TEXT;
const char CF_OWN_BSBLPBADDR_TXT[] PROGMEM = CF_OWN_ADDR_TEXT;
const char CF_DEST_BSBLPBADDR_TXT[] PROGMEM = CF_DEST_ADDR_TEXT;
const char CF_PPS_WRITE_TXT[] PROGMEM = CF_PPS_WRITE_TEXT;
const char CF_LOGTELEGRAM_TXT[] PROGMEM = CF_LOGTELEGRAM_TEXT;
const char CF_CALCULATION_TXT[] PROGMEM = CF_CALCULATION_TEXT;
const char CF_LOGCURRINTERVAL_TXT[] PROGMEM = CF_LOGCURRINTERVAL_TEXT;
const char CF_PROGLIST_TXT[] PROGMEM = CF_PROGLIST_TEXT;
const char CF_DEVICES_TXT[] PROGMEM = CF_DEVICES_TEXT;
const char CF_MAC_TXT[] PROGMEM = MENU_TEXT_MAC;
const char CF_DHCP_TXT[] PROGMEM = CF_DHCP_TEXT;
const char CF_IPADDRESS_TXT[] PROGMEM = CF_IPADDRESS_TEXT;
const char CF_TRUSTEDIPADDRESS_TXT[] PROGMEM = CF_TRUSTEDIPADDRESS_TEXT;
const char CF_WIFI_SSID_TXT[] PROGMEM = CF_WIFI_SSID_TEXT;
const char CF_WIFI_PASSWORD_TXT[] PROGMEM = CF_WIFI_PASSWORD_TEXT;
const char CF_MASK_TXT[] PROGMEM = CF_MASK_TEXT;
const char CF_GATEWAY_TXT[] PROGMEM = CF_GATEWAY_TEXT;
const char CF_DNS_TXT[] PROGMEM = CF_DNS_TEXT;
const char CF_WWWPORT_TXT[] PROGMEM = CF_WWWPORT_TEXT;
const char CF_WEBSERVER_TXT[] PROGMEM = CF_WEBSERVER_TEXT;
const char CF_PASSKEY_TXT[] PROGMEM = CF_PASSKEY_TEXT;
const char CF_QAA_TYPE_TXT[] PROGMEM = CF_QAA_TYPE_TEXT;
const char CF_BASICAUTH_TXT[] PROGMEM = CF_BASICAUTH_TEXT;
const char CF_PINS_TXT[] PROGMEM = CF_PINS_TEXT;
const char CF_USE_TXT[] PROGMEM = CF_USE_TEXT;
const char CF_MAX_IPADDRESS_TXT[] PROGMEM = CF_MAX_IPADDRESS_TEXT;
const char CF_WRITEMODE_TXT[] PROGMEM = CF_WRITEMODE_TEXT;
const char CF_VERBOSE_TXT[] PROGMEM = MENU_TEXT_VBL;
const char CF_MONITOR_TXT[] PROGMEM = MENU_TEXT_MMD;
const char CF_SHOW_UNKNOWN_TXT[] PROGMEM = CF_SHOW_UNKNOWN_TEXT;
const char CF_MQTT_IPADDRESS_TXT[] PROGMEM = CF_MQTT_IPADDRESS_TEXT;
const char CF_MQTT_USERNAME_TXT[] PROGMEM = CF_MQTT_USERNAME_TEXT;
const char CF_MQTT_PASSWORD_TXT[] PROGMEM = CF_MQTT_PASSWORD_TEXT;
const char CF_MQTT_TOPIC_TXT[] PROGMEM = CF_MQTT_TOPIC_TEXT;
const char CF_MQTT_DEVICE_TXT[] PROGMEM = CF_MQTT_DEVICE_TEXT;
const char CF_LOGMODE_TXT[] PROGMEM = CF_LOGMODE_TEXT;
const char CF_CHECKUPDATE_TXT[] PROGMEM = CF_CHECKUPDATE_TEXT;
const char CF_MDNS_HOSTNAME_TXT[] PROGMEM = CF_MDNS_HOSTNAME_TEXT;
const char CF_NUM_TXT[] PROGMEM = CF_NUM_TEXT;
const char CF_OTA_UPDATE_TXT[] PROGMEM = CF_OTA_UPDATE_TEXT;
#ifdef RGT_EMULATOR
const char CF_RGT1_SENSOR_TXT[] PROGMEM = CF_RGT1_SENSOR_TEXT;
const char CF_RGT2_SENSOR_TXT[] PROGMEM = CF_RGT2_SENSOR_TEXT;
const char CF_RGT3_SENSOR_TXT[] PROGMEM = CF_RGT3_SENSOR_TEXT;
#else
const char CF_RGT1_SENSOR_TXT[] PROGMEM = "";
const char CF_RGT2_SENSOR_TXT[] PROGMEM = "";
const char CF_RGT3_SENSOR_TXT[] PROGMEM = "";
#endif
#ifdef BUTTONS
const char CF_TWW_PUSH_PIN_TXT[] PROGMEM = CF_TWW_PUSH_PIN_TEXT;
const char CF_RGT1_PRES_PIN_TXT[] PROGMEM = CF_RGT1_PRES_PIN_TEXT;
const char CF_RGT2_PRES_PIN_TXT[] PROGMEM = CF_RGT2_PRES_PIN_TEXT;
const char CF_RGT3_PRES_PIN_TXT[] PROGMEM = CF_RGT3_PRES_PIN_TEXT;
#else
const char CF_TWW_PUSH_PIN_TXT[] PROGMEM = "";
const char CF_RGT1_PRES_PIN_TXT[] PROGMEM = "";
const char CF_RGT2_PRES_PIN_TXT[] PROGMEM = "";
const char CF_RGT3_PRES_PIN_TXT[] PROGMEM = "";
#endif
const char CF_RX_PIN_TXT[] PROGMEM = CF_RX_PIN_TEXT;
const char CF_TX_PIN_TXT[] PROGMEM = CF_TX_PIN_TEXT;
const char CF_CONFIG_LEVEL_TXT[] PROGMEM = CF_CONFIG_LEVEL_TEXT;

const char CAT_GENERAL_TXT[] PROGMEM = CAT_GENERAL_TEXT;
const char CAT_IPV4_TXT[] PROGMEM = CAT_IPV4_TEXT;
const char CAT_MQTT_TXT[] PROGMEM = CAT_MQTT_TEXT;
const char CAT_BUS_TXT[] PROGMEM = CAT_BUS_TEXT;
const char CAT_IPWE_TXT[] PROGMEM = CAT_IPWE_TEXT;
const char CAT_DHTBUS_TXT[] PROGMEM = CAT_DHTBUS_TEXT;
const char CAT_ONEWIREBUS_TXT[] PROGMEM = CAT_ONEWIREBUS_TEXT;
const char CAT_DEBUG_TXT[] PROGMEM = CAT_DEBUG_TEXT;
const char CAT_MAX_TXT[] PROGMEM = CAT_MAX_TEXT;
const char CAT_LOGGING_TXT[] PROGMEM = CAT_LOGGING_TEXT;
const char CAT_24HAVG_TXT[] PROGMEM = CAT_24HAVG_TEXT;
const char CAT_RGT_EMUL_TXT[] PROGMEM = CAT_RGT_EMUL_TEXT;
const char CAT_BMEBUS_TXT[] PROGMEM = CAT_BMEBUS_TEXT;

const char STR_TEXT_FSP[] PROGMEM = MENU_TEXT_FSP;
const char STR_TEXT_SNS[] PROGMEM = MENU_TEXT_SNS;
typedef enum {
  DT_VALS,    // plain value
  DT_ENUM,    // value (8/16 Bit) followed by space followed by text
  DT_BITS,    // bit value followed by bitmask followed by text
  DT_WDAY,    // weekday. Not used but must leaved here. Or replaced with new data type in future
  DT_HHMM,    // hour:minute
  DT_DTTM,    // date and time
  DT_DDMM,    // day and month
  DT_STRN,    // string
  DT_DWHM,    // PPS time (day of week, hour:minute)
  DT_TMPR,    // time program
  DT_THMS,    // time (hours:minute:seconds)
} dt_types_t;

const char STR_VALS[] PROGMEM = "VALS";
const char STR_ENUM[] PROGMEM = "ENUM";
const char STR_BITS[] PROGMEM = "BITS";
const char STR_WDAY[] PROGMEM = "WDAY";
const char STR_HHMM[] PROGMEM = "HHMM";
const char STR_DTTM[] PROGMEM = "DTTM";
const char STR_DDMM[] PROGMEM = "DDMM";
const char STR_STRN[] PROGMEM = "STRN";
const char STR_DWHM[] PROGMEM = "DWHM";
const char STR_TMPR[] PROGMEM = "TMPR";
const char STR_THMS[] PROGMEM = "THMS";
const char STR_DISABLED[] PROGMEM = "---";

const char STR_IPWEZERO[] PROGMEM = "<td>0<br></td>";
const char STR_OPTION_VALUE[] PROGMEM = "<option value='";
const char STR_CLOSE_OPTION[] PROGMEM = "</option>\r\n";
const char STR_SELECTED[] PROGMEM = "' selected>";


const char STR_BIT[] PROGMEM = "BIT";
const char STR_BYTE[] PROGMEM = "BYTE";
const char STR_BYTE10[] PROGMEM = "BYTE10";
const char STR_CLOSEDOPEN[] PROGMEM = "CLOSEDOPEN";
const char STR_DAYS[] PROGMEM = "DAYS";
const char STR_GRADIENT_SHORT[] PROGMEM = "GRADIENT_SHORT";
const char STR_HOURS_SHORT[] PROGMEM = "HOURS_SHORT";
const char STR_LPBADDR[] PROGMEM = "LPBADDR";
const char STR_MINUTES_SHORT[] PROGMEM = "MINUTES_SHORT";
const char STR_MONTHS[] PROGMEM = "MONTHS";
const char STR_ONOFF[] PROGMEM = "ONOFF";
const char STR_PERCENT[] PROGMEM = "PERCENT";
const char STR_PERCENT5[] PROGMEM = "PERCENT5";
const char STR_PRESSURE[] PROGMEM = "PRESSURE";
const char STR_PRESSURE50[] PROGMEM = "PRESSURE50";
const char STR_SECONDS_SHORT[] PROGMEM = "SECONDS_SHORT";
const char STR_SECONDS_SHORT2[] PROGMEM = "SECONDS_SHORT2";
const char STR_SECONDS_SHORT4[] PROGMEM = "SECONDS_SHORT4";
const char STR_SECONDS_SHORT5[] PROGMEM = "SECONDS_SHORT5";
const char STR_TEMP_SHORT[] PROGMEM = "TEMP_SHORT";
const char STR_TEMP_SHORT_US[] PROGMEM = "TEMP_SHORT_US";
const char STR_TEMP_SHORT5[] PROGMEM = "TEMP_SHORT5";
const char STR_TEMP_SHORT5_US[] PROGMEM = "TEMP_SHORT5_US";
const char STR_TEMP_SHORT64[] PROGMEM = "TEMP_SHORT64";
const char STR_TEMP_PER_MIN[] PROGMEM = "TEMP_PER_MIN";
const char STR_VOLTAGE[] PROGMEM = "VOLTAGE";
const char STR_VOLTAGEONOFF[] PROGMEM = "VOLTAGEONOFF";
const char STR_WEEKDAY[] PROGMEM = "WEEKDAY";
const char STR_YESNO[] PROGMEM = "YESNO";
const char STR_SPF[] PROGMEM = "SPF";
const char STR_CURRENT[] PROGMEM = "CURRENT";
const char STR_CURRENT1000[] PROGMEM = "CURRENT1000";
const char STR_DAYS_WORD[] PROGMEM = "DAYS_WORD";
const char STR_ERRORCODE[] PROGMEM = "ERRORCODE";
const char STR_FP1[] PROGMEM = "FP1";
const char STR_FP02[] PROGMEM = "FP02";
const char STR_GRADIENT[] PROGMEM = "GRADIENT";
const char STR_INTEGRAL[] PROGMEM = "INTEGRAL";
const char STR_MONTHS_WORD[] PROGMEM = "MONTHS_WORD";
const char STR_HOUR_MINUTES[] PROGMEM = "HOUR_MINUTES";
const char STR_HOURS_WORD[] PROGMEM = "HOURS_WORD";
const char STR_METER[] PROGMEM = "METER";
const char STR_SECONDS_WORD16[] PROGMEM = "SECONDS_WORD16";
const char STR_MINUTES_WORD[] PROGMEM = "MINUTES_WORD";
const char STR_MINUTES_WORD10[] PROGMEM = "MINUTES_WORD10";
const char STR_PERCENT_WORD1[] PROGMEM = "PERCENT_WORD1";
const char STR_PERCENT_WORD[] PROGMEM = "PERCENT_WORD";
const char STR_PERCENT1[] PROGMEM = "PERCENT1";
const char STR_PERCENT_100[] PROGMEM = "PERCENT_100";
const char STR_POWER_WORD[] PROGMEM = "POWER_WORD";
const char STR_POWER_WORD100[] PROGMEM = "POWER_WORD100";
const char STR_ENERGY_WORD[] PROGMEM = "ENERGY_WORD";
const char STR_ENERGY_CONTENT[] PROGMEM = "ENERGY_CONTENT";
const char STR_PRESSURE_WORD[] PROGMEM = "PRESSURE_WORD";
const char STR_PRESSURE_1000[] PROGMEM = "PRESSURE_1000";
const char STR_PROPVAL[] PROGMEM = "PROPVAL";
const char STR_PPM[] PROGMEM = "PPM";
const char STR_SECONDS_WORD[] PROGMEM = "SECONDS_WORD";
const char STR_SECONDS_WORD5[] PROGMEM = "SECONDS_WORD5";
const char STR_SPEED[] PROGMEM = "SPEED";
const char STR_SPEED2[] PROGMEM = "SPEED2";
const char STR_TEMP[] PROGMEM = "TEMP";
const char STR_TEMP_WORD[] PROGMEM = "TEMP_WORD";
const char STR_TEMP_WORD60[] PROGMEM = "TEMP_WORD60";
const char STR_TEMP_WORD5_US[] PROGMEM = "TEMP_WORD5_US";
const char STR_VOLTAGE_WORD[] PROGMEM = "VOLTAGE_WORD";
const char STR_CELMIN[] PROGMEM = "CELMIN";
const char STR_FREQ[] PROGMEM = "FREQ";
const char STR_LITERPERHOUR[] PROGMEM = "LITERPERHOUR";
const char STR_LITERPERMIN[] PROGMEM = "LITERPERMIN";
const char STR_LPM_SHORT[] PROGMEM = "LPM_SHORT";
const char STR_UINT[] PROGMEM = "UINT";
const char STR_UINT5[] PROGMEM = "UINT5";
const char STR_UINT10[] PROGMEM = "UINT10";
const char STR_SINT[] PROGMEM = "SINT";
const char STR_SINT1000[] PROGMEM = "SINT1000";
const char STR_PPS_TIME[] PROGMEM = "PPS_TIME";
const char STR_DWORD[] PROGMEM = "DWORD";
const char STR_DWORD10[] PROGMEM = "DWORD10";
const char STR_HOURS[] PROGMEM = "HOURS";
const char STR_MINUTES[] PROGMEM = "MINUTES";
const char STR_SECONDS_DWORD[] PROGMEM = "SECONDS_DWORD";
const char STR_POWER[] PROGMEM = "POWER";
const char STR_POWER100[] PROGMEM = "POWER100";
const char STR_ENERGY10[] PROGMEM = "ENERGY10";
const char STR_ENERGY[] PROGMEM = "ENERGY";
const char STR_UINT100[] PROGMEM = "UINT100";
const char STR_DATETIME[] PROGMEM = "DATETIME";
const char STR_YEAR[] PROGMEM = "YEAR";
const char STR_DAYMONTH[] PROGMEM = "DAYMONTH";
const char STR_TIME[] PROGMEM = "TIME";
const char STR_VACATIONPROG[] PROGMEM = "VACATIONPROG";
const char STR_TIMEPROG[] PROGMEM = "TIMEPROG";
const char STR_STRING[] PROGMEM = "STRING";
const char STR_CUSTOM_ENUM[] PROGMEM = "CUSTOM_ENUM";
const char STR_CUSTOM_BYTE[] PROGMEM = "CUSTOM_BYTE";
const char STR_CUSTOM_BIT[] PROGMEM = "CUSTOM_BIT";
const char STR_GR_PER_CUBM[] PROGMEM = "GR_PER_CUBM";
const char STR_FLOAT[] PROGMEM = "FLOAT";
const char STR_LONG[] PROGMEM = "LONG";
const char STR_ATM_PRESSURE[] PROGMEM = "ATM_PRESSURE";
const char STR_ALTITUDE[] PROGMEM = "ALTITUDE";
const char STR_UNKNOWN[] PROGMEM = "UNKNOWN";

const char U_METER[] PROGMEM = UNIT_METER_TEXT;
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
const char U_GR_PER_CUBM[] PROGMEM = UNIT_GR_PER_CUBM_TEXT;
const char U_ATM_PRESSURE[] PROGMEM = UNIT_HPA_TEXT;
const char U_ALTITUDE[] PROGMEM = UNIT_METER_TEXT;
const char U_PPM[] PROGMEM = UNIT_PPM_TEXT;
const char U_NONE[] PROGMEM = "";

typedef struct {
  uint8_t   type;             // message type (e.g. VT_TEMP)
  float     operand;          // both for divisors as well as factors (1/divisor)
  uint8_t   enable_byte;      // for regular commands either 1 or 6. 8 indicates data type does not use enable. 0 indicates no set telegram has been logged to determine correct enable byte.
  uint8_t   payload_length;   // length of payload in byte; +32 if special treatment is needed, +64 if payload length can vary; 0 for read-only type or unknown length
  uint8_t   data_type;        // Value, String, Date...
  uint8_t   precision;        // decimal places
  const char  *unit;
  uint8_t unit_len;
  const char  *type_text;
} units;

typedef struct {
  uint32_t    cmd;                 // the command or fieldID
//  uint8_t     category;            // the menu category
  uint8_t     type;                // the message type
  float       line;                // parameter number
  const char  *desc;               // description test
  uint16_t    enumstr_len;         // sizeof enum
  const char  *enumstr;            // enum string
  uint8_t     flags;               // e.g. FL_RONLY
  uint8_t     dev_fam;             // device family
  uint8_t     dev_var;             // device variant
//  uint32_t    devices;           // e.g. DEV_ALL, DEV_097_ALL, DEV_162_ALL+DEV_163_ALL, DEV_ALL-DEV_097_ALL
} cmd_t;

typedef struct {
  uint8_t type;
  const char  *type_text;
} dt_types;

PROGMEM_LATE const dt_types dt_types_text[]={
  {DT_VALS, STR_VALS},
  {DT_ENUM, STR_ENUM},
  {DT_BITS, STR_BITS},
  {DT_WDAY, STR_WDAY},
  {DT_HHMM, STR_HHMM},
  {DT_DTTM, STR_DTTM},
  {DT_DDMM, STR_DDMM},
  {DT_STRN, STR_STRN},
  {DT_DWHM, STR_DWHM},
  {DT_TMPR, STR_TMPR},
  {DT_THMS, STR_THMS}
};

/* Parameter types */
/* order of types must according to optbl table */
typedef enum{
  VT_BIT,               //  2 Byte - 1 enable 0x01 / value
  VT_BYTE,              //  2 Byte - 1 enable 0x01 / value
  VT_BYTE_N,            //  2 Byte - 1 enable 0x06 / value
  VT_BYTE10,            //  2 Byte - 1 enable 0x01 / value/10
  VT_CLOSEDOPEN,        //  2 Byte - 1 enable 0x01 / 0=Offen 1=Geschlossen Choice
  VT_DAYS,              //  2 Byte - 1 enable 0x01 / day
  VT_ENUM,              //* 2 Byte - 1 enable 0x01 / value        Choice
  VT_GRADIENT_SHORT,    //  2 Byte - 1 enable / value min/K
  VT_HOURS_SHORT,       //  2 Byte - 1 enable 0x01 / hours        Int08
  VT_HOURS_SHORT_N,       //  2 Byte - 1 enable 0x01 / hours        Int08
  VT_LPBADDR,           //* 2 Byte - 1 enable / adr/seg           READ-ONLY
  VT_LPM_SHORT,         //  2 Byte - 1 enable / value / 10
  VT_MINUTES_SHORT,     //  2 Byte - 1 enable 0x01 / minutes      Int08S
  VT_MINUTES_SHORT_N,   //  2 Byte - 1 enable 0x06 / minutes      Int08S
  VT_MONTHS,            //  2 Byte - 1 enable 0x01 / months       Int08S
  VT_MONTHS_N,          //  2 Byte - 1 enable 0x06 / months       Int08S
  VT_ONOFF,             //  2 Byte - 1 enable 0x01 / 0=Aus  1=An (auch 0xff=An)
  VT_PERCENT,           //  2 Byte - 1 enable 0x06 / percent
  VT_PERCENT_NN,        //  2 Byte - 1 enable 0x01 / percent
  VT_PERCENT1,           // 2 Byte - 1 enable 0x01 / percent
  VT_PERCENT5,          //  2 Byte - 1 enable 0x01 / value/2
  VT_PRESSURE,          //  2 Byte - 1 enable 0x06 / bar/10.0     READ-ONLY
  VT_PRESSURE_NN,       //  2 Byte - 1 enable 0x01 / bar/10.0     READ-ONLY
  VT_PRESSURE50,        //  2 Byte - 1 enable 0x01 / bar/50.0
  VT_SECONDS_SHORT,     //  2 Byte - 1 enable 0x01 / seconds
  VT_SECONDS_SHORT_N,   //  2 Byte - 1 enable 0x06 / seconds
  VT_SECONDS_SHORT2,    //  2 Byte - 1 enable 0x01 / value/2 (signed?)
  VT_SECONDS_SHORT2_N,  //  2 Byte - 1 enable 0x01 / value/2 (signed?)
  VT_SECONDS_SHORT4,    //  2 Byte - 1 enable 0x01 / value/4 (signed?)
  VT_SECONDS_SHORT5,    //  2 Byte - 1 enable 0x01 / value/5 (signed?)
  VT_TEMP_SHORT,        //  2 Byte - 1 enable 0x01 / value (signed)
  VT_TEMP_SHORT_US,     //  2 Byte - 1 enable 0x01 / value (unsigned)
  VT_TEMP_SHORT_US_N,   //  2 Byte - 1 enable 0x01 / value (unsigned)
  VT_TEMP_SHORT5,       //  2 Byte - 1 enable 0x01 / value/2 (signed)
  VT_TEMP_SHORT5_N,     //  2 Byte - 1 enable 0x06 / value/2 (signed)
  VT_TEMP_SHORT5_US,    //  2 Byte - 1 enable 0x01 / value/2 (unsigned)
  VT_TEMP_SHORT64,      //  2 Byte - 1 enable 0x01 / value/64 (signed)
  VT_TEMP_PER_MIN,      //  2 Byte - 1 enable 0x06 / value
  VT_VOLTAGE,           //  2 Byte - 1 enable / volt z.B. 2.9V
  VT_VOLTAGE_N,         //  2 Byte - 6 enable / volt z.B. 2.9V
  VT_VOLTAGEONOFF,      //  2 Byte - 1 enable / volt 0V (0x00) or 230V (0xFF)
  VT_WEEKDAY,           //  2 Byte - 1 enable 0x01 / weekday (1=Mo..7=So)
  VT_YESNO,             //  2 Byte - 1 enable 0x01 / 0=Nein 1=Ja (auch 0xff=Ja)
  VT_SPF,               //  3 Byte -  / value / 100
  VT_CURRENT,           //  3 Byte - 1 enable / value/100 uA
  VT_CURRENT1000,       //  3 Byte - 1 enable / value/1000 uA
  VT_DAYS_WORD,         //  3 Byte - 1 enable / day
  VT_ERRORCODE,         //  3 Byte - 1 enable / value READ-ONLY
  VT_FP1,               //  3 Byte - 1 enable / value/10 READ-ONLY
  VT_FP02,              //  3 Byte - 1 enable 0x01 / value/50
  VT_GRADIENT,          //  3 Byte - 1 enable / value min/K
//  VT_INTEGRAL,          //  3 Byte - 1 enable / value Kmin
  VT_METER,             //  3 Byte - 1 enable 0x06 / meter / 10
  VT_MONTHS_WORD,       //  3 Byte - 1 enable 0x06 / months
  VT_HOUR_MINUTES,      //  3 Byte - 1 enable 0x06 / hh mm
  VT_HOUR_MINUTES_N,    //  3 Byte - 1 enable 0x06 / hh mm
  VT_HOURS_WORD,        //  3 Byte - 1 enable 0x01 / hours
  VT_HOURS_WORD_N,      //  3 Byte - 1 enable 0x06 / hours
  VT_MINUTES_WORD,      //  3 Byte - 1 enable 0x06 / minutes
  VT_MINUTES_WORD_N,    //  3 Byte - 1 enable 0x06 / minutes
  VT_MINUTES_WORD10,    //  3 Byte - 1 enable 0x06 / minutes / 10
  VT_PERCENT_WORD1,     //  3 Byte - 1 enable / percent
  VT_PERCENT_WORD,      //  3 Byte - 1 enable / percent/2
  VT_PERCENT_100,       //  3 Byte - 1 enable / percent/100
  VT_POWER_WORD,        //  3 Byte - 1 enable / value/10 kW
  VT_POWER_WORD_N,        //  3 Byte - 1 enable / value/10 kW
  VT_POWER_WORD100,     //  3 Byte - 1 enable / value/100 kW
  VT_POWER_WORD100_N,   //  3 Byte - 1 enable / value/100 kW
  VT_ENERGY_WORD,       //  3 Byte - 1 enable / value/10 kWh
  VT_ENERGY_CONTENT,    //  3 Byte - 1 enable / value/10 kWh/m³
  VT_PRESSURE_WORD,     //  3 Byte - 1 enable / bar/10.0
  VT_PRESSURE_WORD_NN,  //  3 Byte - 1 enable / bar/10.0
  VT_PRESSURE_1000,     //  3 Byte - 1 enable / bar/1000.0
  VT_PROPVAL,           //  3 Byte - 1 enable / value/16
  VT_PPM,               //  2 Byte - 1 enable 0x   / ppm/1 signed
  VT_CEL_PER_MIN_WORD,  //  3 Byte - 1 enable / k/min
  VT_SECONDS_WORD,      //  3 Byte - 1 enable / seconds
  VT_SECONDS_WORD_N,    //  3 Byte - 1 enable / seconds
  VT_SECONDS_WORD5,     //  3 Byte - 1 enable / seconds / 2
  VT_SECONDS_WORD16,    //  3 Byte - 1 enable / seconds / 16
  VT_SPEED,             //  3 Byte - 1 enable / value * 50 rpm
  VT_SPEED2,            //  3 Byte - 1 enable / rpm
  VT_SPEED2_N,          //  3 Byte - 1 enable / rpm
  VT_TEMP,              //  3 Byte - 1 enable / value/64
  VT_TEMP_N,            //  3 Byte - 1 enable / value/64
  VT_TEMP_WORD,         //  3 Byte - 1 enable / value
//  VT_TEMP_WORD60,       //  3 Byte - 1 enable / value / 60
  VT_TEMP_WORD5_US,     //  3 Byte - 1 enable / value / 2
  VT_VOLTAGE_WORD,      //  3 Byte - 1 enable / volt z.B. 2.9V
  VT_CELMIN,            //  3 Byte - 1 enable / value
  VT_CELMIN_N,          //  3 Byte - 1 enable / value
  VT_FREQ,              //  3 Byte - 1 enabl / value / 200
  VT_LITERPERHOUR,      //  3 Byte - 1 enable / value
  VT_LITERPERHOUR_N,    //  3 Byte - 1 enable / value
  VT_LITERPERMIN,       //  3 Byte - 1 enable / value / 10
  VT_LITERPERMIN_N,     //  3 Byte - 1 enable / value / 10
  VT_UINT,              //  3 Byte - 1 enable 0x01 / value
  VT_UINT_N,            //  3 Byte - 1 enable 0x06 / value
  VT_UINT5,             //  3 Byte - 1 enable / value * 5
  VT_UINT10,            //  3 Byte - 1 enable / value / 10
  VT_UINT100_WORD,      //  3 Byte - 1 enable / value / 100
  VT_UINT100_WORD_N,    //  3 Byte - 1 enable / value / 100
  VT_SINT,              //  3 Byte - 1 enable 0x06 / value
  VT_SINT_NN,            //  3 Byte - 1 enable 0x01 / value
  VT_SINT1000,          //  3 Byte - 1 enable value / 1000
  VT_PPS_TIME,          //  4 Byte
  VT_DWORD,             //  5 Byte - 1 enable 0x06 / value
  VT_DWORD_N,           //  5 Byte - 1 enable 0x06 / value
  VT_DWORD10,           //  5 Byte - 1 enable 0x   / value
  VT_HOURS,             //  5 Byte - 1 enable / seconds/3600
  VT_HOURS_N,           //  5 Byte - 6 enable / seconds/3600
  VT_MINUTES,           //  5 Byte - 1 enable 0x01 / seconds/60
  VT_SECONDS_DWORD,     //  5 Byte - 1 enable 0x01 / seconds
  VT_POWER,             //  5 Byte - 1 enable / value/10 kW
  VT_POWER100,          //  5 Byte - 1 enable / value/100 kW
//  VT_ENERGY10,          //  5 Byte - 1 enable / value/10 kWh
  VT_ENERGY,            //  5 Byte - 1 enable / value/1 kWh
  VT_ENERGY_N,          //  5 Byte - 1 enable / value/1 kWh
  VT_UINT100,           //  5 Byte - 1 enable / value / 100
  VT_DATETIME,          //* 9 Byte - 1 enable 0x01 / year+1900 month day weekday hour min sec
  VT_YEAR,              // subset of VT_DATETIME
  VT_DAYMONTH,          // subset of VT_DATETIME
  VT_TIME,              // subset of VT_DATETIME
  VT_VACATIONPROG,      // subset of VT_DATETIME
  VT_TIMEPROG,          //*12 Byte - no flag / 1_ein 1_aus 2_ein 2_aus 3_ein 3_aus (jeweils SS:MM)
  VT_STRING,            //* x Byte - 1 enable / string
  VT_CUSTOM_ENUM,       //* x Byte - 1 Byte Position, 1 Byte Parameter-Wert, Space, Text
  VT_CUSTOM_BYTE,       //* x Byte - 1 Byte Position, 1 Byte Länge Parameter, Space (!) (nötig für Erkennung)
  VT_CUSTOM_BIT,        //* x Byte - 1st Byte position, then 1 Byte bit value, 1 Byte bitmask, space, text
  VT_GR_PER_CUBM,       //Virtual (DHT22): Gram per cubic meter (Abs humidity)
  VT_FLOAT,             //Virtual: custom_float
  VT_LONG,              //Virtual: custom_long
  VT_PRESSURE_HPA,      //Virtual: Pressure [hPa]
  VT_ALTITUDE,          //Virtual: Altitude [m]
  VT_UNKNOWN
}vt_type_t;

/* order of types must according to vt_type_t enum */
PROGMEM_LATE const units optbl[]={
{VT_BIT,              1.0,    1, 1, DT_BITS, 0,  U_NONE, sizeof(U_NONE), STR_BIT},
{VT_BYTE,             1.0,    1, 1, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_BYTE},
{VT_BYTE_N,           1.0,    6, 1, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_BYTE},
{VT_BYTE10,           10.0,   1, 1, DT_VALS, 1,  U_NONE, sizeof(U_NONE), STR_BYTE10},
{VT_CLOSEDOPEN,       1.0,    1, 1, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_CLOSEDOPEN},
{VT_DAYS,             1.0,    1, 1, DT_VALS, 0,  U_DAYS, sizeof(U_DAYS), STR_DAYS},
{VT_ENUM,             1.0,    1, 1, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_ENUM},
{VT_GRADIENT_SHORT,   1.0,    6, 6, DT_VALS, 0,  U_GRADIENT, sizeof(U_GRADIENT), STR_GRADIENT_SHORT},
{VT_HOURS_SHORT,      1.0,    1, 1, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS_SHORT},
{VT_HOURS_SHORT_N,    1.0,    6, 1, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS_SHORT},
{VT_LPBADDR,          1.0,    1, 1, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_LPBADDR},
{VT_LPM_SHORT,        10.0,   0, 2, DT_VALS, 1,  U_LITERPERMIN, sizeof(U_LITERPERMIN), STR_LPM_SHORT},
{VT_MINUTES_SHORT,    1.0,    1, 1, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES_SHORT},
{VT_MINUTES_SHORT_N,  1.0,    6, 1, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES_SHORT},
{VT_MONTHS,           1.0,    1, 1, DT_VALS, 0,  U_MONTHS, sizeof(U_MONTHS), STR_MONTHS},
{VT_MONTHS_N,         1.0,    6, 1, DT_VALS, 0,  U_MONTHS, sizeof(U_MONTHS), STR_MONTHS},
{VT_ONOFF,            1.0,    1, 1, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_ONOFF},
{VT_PERCENT,          1.0,    6, 1, DT_VALS, 0,  U_PERC, sizeof(U_PERC), STR_PERCENT},
{VT_PERCENT_NN,       1.0,    1, 1, DT_VALS, 0,  U_PERC, sizeof(U_PERC), STR_PERCENT},
{VT_PERCENT1,         1.0,    1, 1, DT_VALS, 0,  U_PERC, sizeof(U_PERC), STR_PERCENT1},
{VT_PERCENT5,         2.0,    1, 1, DT_VALS, 0,  U_PERC, sizeof(U_PERC), STR_PERCENT5},
{VT_PRESSURE,         10.0,   6, 1, DT_VALS, 1,  U_BAR, sizeof(U_BAR), STR_PRESSURE},
{VT_PRESSURE_NN,      10.0,   1, 1, DT_VALS, 1,  U_BAR, sizeof(U_BAR), STR_PRESSURE},
{VT_PRESSURE50,       50.0,   1, 1, DT_VALS, 2,  U_BAR, sizeof(U_BAR), STR_PRESSURE50},
{VT_SECONDS_SHORT,    1.0,    1, 1, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT},
{VT_SECONDS_SHORT_N,  1.0,    6, 1, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT},
{VT_SECONDS_SHORT2,   2.0,    1, 1, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT2},
{VT_SECONDS_SHORT2_N, 2.0,    6, 1, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT2},
{VT_SECONDS_SHORT4,   4.0,    1, 1, DT_VALS, 1,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT4},
{VT_SECONDS_SHORT5,   5.0,    1, 1, DT_VALS, 1,  U_SEC, sizeof(U_SEC), STR_SECONDS_SHORT5},
{VT_TEMP_SHORT,       1.0,    1, 1, DT_VALS, 0,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT},
{VT_TEMP_SHORT_US,    1.0,    1, 1, DT_VALS, 0,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT_US},
{VT_TEMP_SHORT_US_N,  1.0,    6, 1, DT_VALS, 0,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT_US},
{VT_TEMP_SHORT5,      2.0,    1, 1, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT5},
{VT_TEMP_SHORT5_N,    2.0,    6, 1, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT5},
{VT_TEMP_SHORT5_US,   2.0,    1, 1, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_SHORT5_US},
{VT_TEMP_SHORT64,     64.0,   1, 1, DT_VALS, 5,  U_GRADIENTKS, sizeof(U_GRADIENTKS), STR_TEMP_SHORT64},
{VT_TEMP_PER_MIN,     1.0,    6, 1, DT_VALS, 0,  U_TEMP_PER_MIN, sizeof(U_TEMP_PER_MIN), STR_TEMP_PER_MIN},
{VT_VOLTAGE,          10.0,   1, 1, DT_VALS, 1,  U_VOLT, sizeof(U_VOLT), STR_VOLTAGE},
{VT_VOLTAGE_N,        10.0,   6, 1, DT_VALS, 1,  U_VOLT, sizeof(U_VOLT), STR_VOLTAGE},
{VT_VOLTAGEONOFF,     1.0,    1, 1, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_VOLTAGEONOFF},
{VT_WEEKDAY,          1.0,    1, 1, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_WEEKDAY},
{VT_YESNO,            1.0,    1, 1, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_YESNO},
{VT_SPF,              100.0,  0, 2, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_SPF},
{VT_CURRENT,          100.0,  0, 2, DT_VALS, 2,  U_CURR, sizeof(U_CURR), STR_CURRENT},
{VT_CURRENT1000,      1000.0, 0, 0, DT_VALS, 2,  U_CURR, sizeof(U_CURR), STR_CURRENT1000},
{VT_DAYS_WORD,        1.0,    1, 2, DT_VALS, 0,  U_DAYS, sizeof(U_DAYS), STR_DAYS_WORD},
{VT_ERRORCODE,        1.0,    0, 0, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_ERRORCODE},
{VT_FP1,              10.0,   0, 2, DT_VALS, 1,  U_NONE, sizeof(U_NONE), STR_FP1},
{VT_FP02,             50.0,   1, 2, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_FP02},
{VT_GRADIENT,         1.0,    1, 2, DT_VALS, 0,  U_GRADIENT, sizeof(U_GRADIENT), STR_GRADIENT},
// {VT_INTEGRAL,         1.0,    0, 2, DT_VALS, 0,  U_INTEGRAL, sizeof(U_INTEGRAL), STR_INTEGRAL},
{VT_METER,            10,     1, 2, DT_VALS, 0,  U_METER, sizeof(U_METER), STR_METER},
{VT_MONTHS_WORD,      1.0,    1, 2, DT_VALS, 0,  U_MONTHS, sizeof(U_MONTHS), STR_MONTHS_WORD},
{VT_HOUR_MINUTES,     1.0,    1, 2+32, DT_HHMM, 0,  U_NONE, sizeof(U_NONE), STR_HOUR_MINUTES},
{VT_HOUR_MINUTES_N,   1.0,    6, 2+32, DT_HHMM, 0,  U_NONE, sizeof(U_NONE), STR_HOUR_MINUTES},
{VT_HOURS_WORD,       1.0,    1, 2, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS_WORD},
{VT_HOURS_WORD_N,     1.0,    6, 2, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS_WORD},
{VT_MINUTES_WORD,     1.0,    1, 2, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES_WORD},
{VT_MINUTES_WORD_N,   1.0,    6, 2, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES_WORD},
{VT_MINUTES_WORD10,   0.1,    0, 2, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES_WORD10},
{VT_PERCENT_WORD1,    1.0,    1, 2, DT_VALS, 1,  U_PERC, sizeof(U_PERC), STR_PERCENT_WORD1},
{VT_PERCENT_WORD,     2.0,    1, 2, DT_VALS, 1,  U_PERC, sizeof(U_PERC), STR_PERCENT_WORD},
{VT_PERCENT_100,      100.0,  1, 2, DT_VALS, 1,  U_PERC, sizeof(U_PERC), STR_PERCENT_100},
{VT_POWER_WORD,       10.0,   1, 2, DT_VALS, 1,  U_KW, sizeof(U_KW), STR_POWER_WORD},
{VT_POWER_WORD_N,     10.0,   6, 2, DT_VALS, 1,  U_KW, sizeof(U_KW), STR_POWER_WORD},
{VT_POWER_WORD100,    100.0,  1, 2, DT_VALS, 2,  U_KW, sizeof(U_KW), STR_POWER_WORD100},
{VT_POWER_WORD100_N,  100.0,  6, 2, DT_VALS, 2,  U_KW, sizeof(U_KW), STR_POWER_WORD100},
{VT_ENERGY_WORD,      10.0,   0, 2, DT_VALS, 1,  U_KWH, sizeof(U_KWH), STR_ENERGY_WORD},
{VT_ENERGY_CONTENT,   10.0,   0, 2, DT_VALS, 1,  U_KWHM3, sizeof(U_KWHM3), STR_ENERGY_CONTENT},
{VT_PRESSURE_WORD,    10.0,   6, 2, DT_VALS, 1,  U_BAR, sizeof(U_BAR), STR_PRESSURE_WORD},
{VT_PRESSURE_WORD_NN, 10.0,   1, 2, DT_VALS, 1,  U_BAR, sizeof(U_BAR), STR_PRESSURE_WORD},
{VT_PRESSURE_1000,    1000.0, 0, 2, DT_VALS, 1,  U_BAR, sizeof(U_BAR), STR_PRESSURE_1000},
{VT_PROPVAL,          16.0,   1, 2, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_PROPVAL},
{VT_PPM,              1.0,    0, 2, DT_VALS, 0,  U_PPM, sizeof(U_PPM), STR_PPM},
{VT_CEL_PER_MIN_WORD, 1.0,    1, 2, DT_VALS, 0,  U_SEC, sizeof(U_CEL_MIN), STR_TEMP_PER_MIN},
{VT_SECONDS_WORD,     1.0,    1, 2, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_WORD},
{VT_SECONDS_WORD_N,   1.0,    6, 2, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_WORD},
{VT_SECONDS_WORD5,    2.0,    1, 2, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_WORD5},
{VT_SECONDS_WORD16,   16.0,   1, 2, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_WORD16},
{VT_SPEED,            0.02,   0, 2, DT_VALS, 0,  U_RPM, sizeof(U_RPM), STR_SPEED},
{VT_SPEED2,           1.0,    1, 2, DT_VALS, 0,  U_RPM, sizeof(U_RPM), STR_SPEED2},
{VT_SPEED2_N,         6.0,    1, 2, DT_VALS, 0,  U_RPM, sizeof(U_RPM), STR_SPEED2},
{VT_TEMP,             64.0,   1, 2+32, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP},
{VT_TEMP_N,           64.0,   6, 2+32, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP},
{VT_TEMP_WORD,        1.0,    1, 2, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_WORD},
// {VT_TEMP_WORD60,    60.0,   6, 2, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_WORD60},
{VT_TEMP_WORD5_US,    2.0,    1, 2, DT_VALS, 1,  U_DEG, sizeof(U_DEG), STR_TEMP_WORD5_US},
{VT_VOLTAGE_WORD,     10.0,   1, 2, DT_VALS, 1,  U_VOLT, sizeof(U_VOLT), STR_VOLTAGE_WORD},
{VT_CELMIN,           1.0,    1, 2, DT_VALS, 1,  U_CEL_MIN, sizeof(U_CEL_MIN), STR_CELMIN},
{VT_CELMIN_N,         1.0,    6, 2, DT_VALS, 1,  U_CEL_MIN, sizeof(U_CEL_MIN), STR_CELMIN},
{VT_FREQ,             1.0,    1, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_FREQ},
{VT_LITERPERHOUR,     1.0,    1, 2, DT_VALS, 0,  U_LITERPERHOUR, sizeof(U_LITERPERHOUR), STR_LITERPERHOUR},
{VT_LITERPERHOUR_N,   1.0,    6, 2, DT_VALS, 0,  U_LITERPERHOUR, sizeof(U_LITERPERHOUR), STR_LITERPERHOUR},
{VT_LITERPERMIN,      10.0,   1, 2, DT_VALS, 1,  U_LITERPERMIN, sizeof(U_LITERPERMIN), STR_LITERPERMIN},
{VT_LITERPERMIN_N,    10.0,   6, 2, DT_VALS, 1,  U_LITERPERMIN, sizeof(U_LITERPERMIN), STR_LITERPERMIN},
{VT_UINT,             1.0,    1, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_UINT},
{VT_UINT_N,           1.0,    6, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_UINT},
{VT_UINT5,            5.0,    1, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_UINT5},
{VT_UINT10,           10.0,   6, 2, DT_VALS, 1,  U_NONE, sizeof(U_NONE), STR_UINT10},
{VT_UINT100_WORD,     100.0,  1, 4, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_UINT100},
{VT_UINT100_WORD_N,   100.0,  6, 4, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_UINT100},
{VT_SINT,             1.0,    6, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_SINT},
{VT_SINT_NN,          1.0,    1, 2, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_SINT},
{VT_SINT1000,         1000,   1, 2+32, DT_VALS, 3,  U_NONE, sizeof(U_NONE), STR_SINT1000},
{VT_PPS_TIME,         1.0,    0, 0, DT_DWHM, 0,  U_NONE, sizeof(U_NONE), STR_PPS_TIME},
{VT_DWORD,            1.0,    1, 4, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_DWORD},
{VT_DWORD_N,          1.0,    6, 4, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_DWORD},
{VT_DWORD10,          10.0,   0, 4, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_DWORD10},
{VT_HOURS,            3600.0, 1, 4, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS},
{VT_HOURS_N,          3600.0, 6, 4, DT_VALS, 0,  U_HOUR, sizeof(U_HOUR), STR_HOURS},
{VT_MINUTES,          60.0,   1, 4, DT_VALS, 0,  U_MIN, sizeof(U_MIN), STR_MINUTES},
{VT_SECONDS_DWORD,    1.0,    0, 4, DT_VALS, 0,  U_SEC, sizeof(U_SEC), STR_SECONDS_DWORD},
{VT_POWER,            10.0,   1, 4, DT_VALS, 1,  U_KW, sizeof(U_KW), STR_POWER},
{VT_POWER100,         100.0,  0, 4, DT_VALS, 2,  U_KW, sizeof(U_KW), STR_POWER100},
// {VT_ENERGY10,       10.0,   1, 4, DT_VALS, 1,  U_KWH, sizeof(U_KWH), STR_ENERGY10},
{VT_ENERGY,           1.0,    1, 4, DT_VALS, 0,  U_KWH, sizeof(U_KWH), STR_ENERGY},
{VT_ENERGY_N,         1.0,    6, 4, DT_VALS, 0,  U_KWH, sizeof(U_KWH), STR_ENERGY},
{VT_UINT100,          100.0,  1, 4, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_UINT100},
{VT_DATETIME,         1.0,    1, 8+32, DT_DTTM, 0,  U_NONE, sizeof(U_NONE), STR_DATETIME},
{VT_YEAR,             1.0,    1, 8+32, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_YEAR},
{VT_DAYMONTH,         1.0,    1, 8+32, DT_DDMM, 0,  U_NONE, sizeof(U_NONE), STR_DAYMONTH},
{VT_TIME,             1.0,    1, 8+32, DT_THMS, 0,  U_NONE, sizeof(U_NONE), STR_TIME},
{VT_VACATIONPROG,     1.0,    6, 8+32, DT_DDMM, 0,  U_NONE, sizeof(U_NONE), STR_VACATIONPROG},
{VT_TIMEPROG,         1.0,    8, 11+32, DT_TMPR, 0,  U_NONE, sizeof(U_NONE), STR_TIMEPROG},
{VT_STRING,           1.0,    8, 22+64, DT_STRN, 0,  U_NONE, sizeof(U_NONE), STR_STRING},
{VT_CUSTOM_ENUM,      1.0,    8, 22+32+64, DT_ENUM, 0,  U_NONE, sizeof(U_NONE), STR_CUSTOM_ENUM},
{VT_CUSTOM_BYTE,      1.0,    0, 22+32+64, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_CUSTOM_BYTE},
{VT_CUSTOM_BIT,       1.0,    0, 22+32+64, DT_BITS, 0,  U_NONE, sizeof(U_NONE), STR_CUSTOM_BIT},
{VT_GR_PER_CUBM,      1.0,    0, 0, DT_VALS, 3,  U_GR_PER_CUBM, sizeof(U_GR_PER_CUBM), STR_GR_PER_CUBM},
{VT_FLOAT,            1.0,    0, 0, DT_VALS, 2,  U_NONE, sizeof(U_NONE), STR_FLOAT},
{VT_LONG,             1.0,    0, 0, DT_VALS, 0,  U_NONE, sizeof(U_NONE), STR_LONG},
{VT_PRESSURE_HPA,     1.0,    0, 0, DT_VALS, 2,  U_ATM_PRESSURE, sizeof(U_ATM_PRESSURE), STR_ATM_PRESSURE},
{VT_ALTITUDE,         1.0,    0, 0, DT_VALS, 0,  U_ALTITUDE, sizeof(U_ALTITUDE), STR_ALTITUDE},
{VT_UNKNOWN,          1.0,    0, 0, DT_VALS, 1,  U_NONE, sizeof(U_NONE), STR_UNKNOWN},
};

/* User-defined command numbers */
#define STR10000 STR8740
#define STR10001 STR8770
#define STR10002 STR8800

const char STR10100[] PROGMEM = STR10100_TEXT;
const char STR10101[] PROGMEM = STR10101_TEXT;
const char STR10102[] PROGMEM = STR10102_TEXT;
const char STR10103[] PROGMEM = STR10103_TEXT;
const char STR10104[] PROGMEM = STR10104_TEXT;

const char STR10200[] PROGMEM = STR10200_TEXT;

const char STR14081[] PROGMEM = STR14081_TEXT;
const char STR14082[] PROGMEM = STR14082_TEXT;
const char STR14083[] PROGMEM = STR14083_TEXT;
const char STR14084[] PROGMEM = STR14084_TEXT;
const char STR14085[] PROGMEM = STR14085_TEXT;
const char STR14086[] PROGMEM = STR14086_TEXT;
const char STR14087[] PROGMEM = STR14087_TEXT;
const char STR14088[] PROGMEM = STR14088_TEXT;
const char STR14089[] PROGMEM = STR14089_TEXT;

const char STR15000[] PROGMEM = STR15000_TEXT;
const char STR15001[] PROGMEM = STR15001_TEXT;
const char STR15002[] PROGMEM = STR15002_TEXT;
const char STR15003[] PROGMEM = STR15003_TEXT;
const char STR15004[] PROGMEM = STR15004_TEXT;
const char STR15005[] PROGMEM = STR15005_TEXT;
const char STR15006[] PROGMEM = STR15006_TEXT;
const char STR15007[] PROGMEM = STR15007_TEXT;
const char STR15008[] PROGMEM = STR15008_TEXT;
const char STR15020[] PROGMEM = STR15020_TEXT;
const char STR15021[] PROGMEM = STR15021_TEXT;
const char STR15022[] PROGMEM = STR15022_TEXT;
const char STR15023[] PROGMEM = STR15023_TEXT;
const char STR15030[] PROGMEM = STR15030_TEXT;
const char STR15031[] PROGMEM = STR15031_TEXT;
const char STR15032[] PROGMEM = STR15032_TEXT;
const char STR15033[] PROGMEM = STR15033_TEXT;
const char STR15034[] PROGMEM = STR15034_TEXT;
const char STR15035[] PROGMEM = STR15035_TEXT;
const char STR15036[] PROGMEM = STR15036_TEXT;
const char STR15040[] PROGMEM = STR15040_TEXT;
const char STR15041[] PROGMEM = STR15041_TEXT;
const char STR15042[] PROGMEM = STR15042_TEXT;
const char STR15043[] PROGMEM = STR15043_TEXT;
const char STR15044[] PROGMEM = STR15044_TEXT;
const char STR15045[] PROGMEM = STR15045_TEXT;
const char STR15046[] PROGMEM = STR15046_TEXT;
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
const char STR15063[] PROGMEM = STR15063_TEXT;
const char STR15064[] PROGMEM = STR15064_TEXT;
const char STR15065[] PROGMEM = STR15065_TEXT;
const char STR15066[] PROGMEM = STR15066_TEXT;
const char STR15067[] PROGMEM = STR15067_TEXT;
const char STR15068[] PROGMEM = STR15068_TEXT;
const char STR15069[] PROGMEM = STR15069_TEXT;
const char STR15070[] PROGMEM = STR15070_TEXT;
const char STR15071[] PROGMEM = STR15071_TEXT;
const char STR15072[] PROGMEM = STR15072_TEXT;
const char STR15073[] PROGMEM = STR15073_TEXT;
const char STR15074[] PROGMEM = STR15074_TEXT;
const char STR15075[] PROGMEM = STR15075_TEXT;
const char STR15076[] PROGMEM = STR15076_TEXT;
const char STR15077[] PROGMEM = STR15077_TEXT;
const char STR15078[] PROGMEM = STR15078_TEXT;
const char STR15079[] PROGMEM = STR15079_TEXT;
const char STR15080[] PROGMEM = STR15080_TEXT;
const char STR15081[] PROGMEM = STR15081_TEXT;
const char STR15082[] PROGMEM = STR15082_TEXT;
const char STR15083[] PROGMEM = STR15083_TEXT;
const char STR15084[] PROGMEM = STR15084_TEXT;
const char STR15085[] PROGMEM = STR15085_TEXT;
const char STR15086[] PROGMEM = STR15086_TEXT;
const char STR15087[] PROGMEM = STR15087_TEXT;
const char STR15088[] PROGMEM = STR15088_TEXT;
const char STR15089[] PROGMEM = STR15089_TEXT;
const char STR15090[] PROGMEM = STR15090_TEXT;
const char STR15091[] PROGMEM = STR15091_TEXT;

const char STR20000[] PROGMEM = MENU_TEXT_BZ1;
const char STR20001[] PROGMEM = MENU_TEXT_BT1;
const char STR20002[] PROGMEM = MENU_TEXT_BZ2;
const char STR20003[] PROGMEM = MENU_TEXT_BT2;
const char STR20004[] PROGMEM = MENU_TEXT_TZ1;
const char STR20005[] PROGMEM = MENU_TEXT_TT1;
const char STR20006[] PROGMEM = MENU_TEXT_BRS;

const char STR20100[] PROGMEM = STR20100_TEXT;
const char STR20101[] PROGMEM = STR20101_TEXT;
const char STR20102[] PROGMEM = STR20102_TEXT;
const char STR20103[] PROGMEM = STR20103_TEXT;
const char STR20200[] PROGMEM = STR20200_TEXT;
const char STR20201[] PROGMEM = STR20201_TEXT;
const char STR20202[] PROGMEM = STR20202_TEXT;
const char STR20203[] PROGMEM = STR20203_TEXT;
const char STR20204[] PROGMEM = STR20204_TEXT;
const char STR20205[] PROGMEM = STR20205_TEXT;
const char STR20300[] PROGMEM = STR20300_TEXT;
const char STR20301[] PROGMEM = STR20301_TEXT;
const char STR20500[] PROGMEM = STR20500_TEXT;
const char STR20501[] PROGMEM = STR20501_TEXT;
const char STR20502[] PROGMEM = STR20502_TEXT;
const char STR20503[] PROGMEM = STR20503_TEXT;
const char STR20700[] PROGMEM = STR20700_TEXT;
const char STR20800[] PROGMEM = STR20800_TEXT;

const char STR65535[] PROGMEM = "";
// A catch-all description string for unrecognised command codes
const char STR99999[] PROGMEM = STR99999_TEXT;

//WEBCONFIG
//Read/write config in EEPROM
const char ENUM_EEPROM_ONOFF[] PROGMEM_LATEST = {
"\x69 " MENU_TEXT_OFF "\0"
"\x96 " MENU_TEXT_ON
};

const char ENUM_BUSTYPE[] PROGMEM_LATEST = {
"\x00 " "BSB" "\0"
"\x01 " "LPB" "\0"
"\x02 " "PPS"
};
const char ENUM_LOGTELEGRAM[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_OFF "\0"
"\x01 " MENU_TEXT_LAT "\0"
"\x02 " MENU_TEXT_BUT " (" MENU_TEXT_OFF ")" "\0"
"\x03 " MENU_TEXT_BUT "\0"
"\x04 " MENU_TEXT_LBO " (" MENU_TEXT_OFF ")" "\0"
"\x05 " MENU_TEXT_LBO "\0"
"\x06 " MENU_TEXT_UBT " (" MENU_TEXT_OFF ")" "\0"
"\x07 " MENU_TEXT_UBT
};
const char ENUM_DEBUG[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_OFF "\0"
"\x01 " ENUM_DEBUG_SERIAL_TEXT "\0"
"\x02 " ENUM_DEBUG_TELNET_TEXT
};
const char ENUM_MQTT[] PROGMEM_LATEST = {
"\x01 " ENUM_MQTT_PLAIN_TEXT "\0"
"\x02 " ENUM_MQTT_JSON_TEXT "\0"
"\x03 " ENUM_MQTT_JSON2_TEXT
};
const char ENUM_PPS_MODE[] PROGMEM_LATEST = {
"\x00 " ENUM_PPS_MODE_PASSIVE_TEXT "\0"
"\x01 " ENUM_PPS_MODE_QAA_TEXT
};
const char ENUM_WRITEMODE[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_OFF "\0"
"\x01 " ENUM_WRITE_ENG_TEXT "\0"
"\x02 " ENUM_WRITE_OEM_TEXT
};

const char ENUM_VOLTAGEONOFF[] PROGMEM_LATEST = {
"\x00 " "0 " UNIT_VOLT_TEXT "\0"
"\x01 " "230 " UNIT_VOLT_TEXT
};

const char ENUM_ONOFF[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_NO "\0"
"\x01 " MENU_TEXT_YES
};
const char ENUM_YESNO[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_NO "\0"
"\x01 " MENU_TEXT_YES
};
const char ENUM_CLOSEDOPEN[] PROGMEM_LATEST = {
"\x00 " MENU_TEXT_OPEN "\0"
"\x01 " MENU_TEXT_CLOSE
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

//TODO: Move to translations
const char ENUM_LOGGER_MODE[] PROGMEM_LATEST = {
"\x01\x01 " ENUM_LOGMODE_01_TEXT
#ifdef AVERAGES
"\0\x02\x02 " ENUM_LOGMODE_02_TEXT
#endif
#ifdef MQTT
"\0\x04\x04 " ENUM_LOGMODE_04_TEXT
#endif
//#ifdef UDP
"\0\x08\x08 " ENUM_LOGMODE_08_TEXT
//#endif

};

// PPS Betriebsart
const char ENUM15000[] PROGMEM_LATEST = {
"\x00 " ENUM15000_00_TEXT "\0"
"\x01 " ENUM15000_01_TEXT "\0"
"\x02 " ENUM15000_02_TEXT
};

const char ENUM15044[] PROGMEM_LATEST = {
"\x00\x01 " "?" "\0"
"\x01\x01 " "?" "\0"
"\x00\x02 " ENUM15044_00_02_TEXT "\0"
"\x02\x02 " ENUM15044_02_02_TEXT "\0"
"\x00\x04 " "?" "\0"
"\x04\x04 " "?" "\0"
"\x00\x08 " ENUM15044_00_08_TEXT "\0"
"\x08\x08 " ENUM15044_08_08_TEXT "\0"
"\x00\x10 " ENUM15044_00_10_TEXT "\0"
"\x10\x10 " ENUM15044_10_10_TEXT
};

const char ENUM15046[] PROGMEM_LATEST = {
"\x52 " ENUM15046_52_TEXT "\0"
"\x53 " ENUM15046_53_TEXT "\0"
"\x5a " ENUM15046_5a_TEXT "\0"
"\x37 " ENUM15046_37_TEXT "\0"
"\x66 " ENUM15046_66_TEXT "\0"
"\xea " ENUM15046_ea_TEXT         // Use unused value 0xEA for MCBA/DC225 type
};

#include "BSB_LAN_custom_defs.h"

//PPS-Bus commands
#define PPS_BA  0
#define PPS_PDK 1
#define PPS_AW  2
#define PPS_FDT 3
#define PPS_RTS 4
#define PPS_RTA 5
#define PPS_FRS 6
#define PPS_SMX 7
#define PPS_RTI 8
#define PPS_TWB 20
#define PPS_TWI 21
#define PPS_TWR 22
#define PPS_TWS 23
#define PPS_AT  30
#define PPS_ATG 31
#define PPS_KVT 32
#define PPS_KVS 33
#define PPS_MVT 34
#define PPS_RTZ 35
#define PPS_MOD 36
#define PPS_TIM 40
#define PPS_DOW 41
#define PPS_NHP 42
#define PPS_HP  43
#define PPS_BRS 44
#define PPS_CON 45
#define PPS_QTP 46

#define PPS_S11 50
#define PPS_E11 51
#define PPS_S12 52
#define PPS_E12 53
#define PPS_S13 54
#define PPS_E13 55
#define PPS_S21 56
#define PPS_E21 57
#define PPS_S22 58
#define PPS_E22 59
#define PPS_S23 60
#define PPS_E23 61
#define PPS_S31 62
#define PPS_E31 63
#define PPS_S32 64
#define PPS_E32 65
#define PPS_S33 66
#define PPS_E33 67
#define PPS_S41 68
#define PPS_E41 69
#define PPS_S42 70
#define PPS_E42 71
#define PPS_S43 72
#define PPS_E43 73
#define PPS_S51 74
#define PPS_E51 75
#define PPS_S52 76
#define PPS_E52 77
#define PPS_S53 78
#define PPS_E53 79
#define PPS_S61 80
#define PPS_E61 81
#define PPS_S62 82
#define PPS_E62 83
#define PPS_S63 84
#define PPS_E63 85
#define PPS_S71 86
#define PPS_E71 87
#define PPS_S72 88
#define PPS_E72 89
#define PPS_S73 90
#define PPS_E73 91

#define PPS_ANZ 92

#define LAST_ENUM_NR 15046
#define LAST_ENUM ENUM15046

{0x2D490000,  VT_ENUM,          15000, STR15000, sizeof(ENUM15000),    ENUM15000,    DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Betriebsart
{0x2D4C0001,  VT_ONOFF,         15001, STR15001, sizeof(ENUM_ONOFF),   ENUM_ONOFF,   DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Anwesenheit
{0x2D180002,  VT_TEMP,          15002, STR15002, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Position Drehknopf
{0x2D7C0003,  VT_BYTE,          15003, STR15003, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Verbleibende Feriendauer in Tagen
{0x2D080004,  VT_TEMP,          15004, STR15004, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Raumtemperatur Soll
{0x2D090005,  VT_TEMP,          15005, STR15005, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Raumtemperatur Abwesenheit Soll
{0x2D1B0006,  VT_TEMP,          15006, STR15006, 0,                    NULL,         FL_RONLY, DEV_ALL}, // Frostschutz-Sollwert
{0x2D1B0007,  VT_TEMP,          15007, STR15007, 0,                    NULL,         FL_RONLY, DEV_ALL}, // Sollwert-Maximum
{0x2D280008,  VT_TEMP,          15008, STR15008, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Raumtemperatur Ist
{0x2D570014,  VT_ONOFF,         15020, STR15020, sizeof(ENUM_ONOFF),   ENUM_ONOFF,   FL_RONLY, DEV_ALL},     // Trinkwasserladung
{0x2D2B0015,  VT_TEMP,          15021, STR15021, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Trinkwassertemperatur Ist
{0x2D1E0016,  VT_TEMP,          15022, STR15022, 0,                    NULL,         FL_RONLY, DEV_PPS},     // Trinkwassertemperatur Reduziert Soll
{0x2D0B0017,  VT_TEMP,          15023, STR15023, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_PPS}, // Trinkwassertemperatur Soll
{0x2D0C0017,  VT_TEMP,          15023, STR15023, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_PPS_MCBA}, // Trinkwassertemperatur Soll
{0x2D29001E,  VT_TEMP,          15030, STR15030, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Außentemperatur
{0x2D57001F,  VT_TEMP,          15031, STR15031, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Außentemperatur gemischt
{0x2D2E0020,  VT_TEMP,          15032, STR15032, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Kesselvorlauftemperatur
{0x2D0E0021,  VT_TEMP,          15033, STR15033, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Kesselvorlauftemperatur Soll (writing only makes sense on MCBA/DC225 systems)
{0x2D2C0022,  VT_TEMP,          15034, STR15034, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Mischervorlauftemperatur
{0x2D190023,  VT_TEMP,          15035, STR15035, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Zieltemperatur (entweder Absenktemperatur oder Komforttemperatur zzgl. Drehknopfposition)
{0x2D4A0024,  VT_PERCENT,       15036, STR15036, 0,                    NULL,         FL_RONLY, DEV_ALL},     // Brennermodulation
{0x2D790028,  VT_PPS_TIME,      15040, STR15040, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // Heater time
{0x2D790029,  VT_WEEKDAY,       15041, STR15041, sizeof(ENUM_WEEKDAY), ENUM_WEEKDAY, DEFAULT_FLAG, DEV_ALL}, // Heater day of week
{0x2D69002A,  VT_TEMP,          15042, STR15042, 0,                    NULL,         FL_NO_CMD, DEV_ALL},    // Nächstes Heizprogramm
{0x2D48002B,  VT_ONOFF,         15043, STR15043, sizeof(ENUM_ONOFF),   ENUM_ONOFF,   FL_RONLY, DEV_ALL},     // Manuelles Heizen (0 = Heizprogramm, 1 = Manuell)
{0x2D4D002C,  VT_BIT,           15044, STR15044, sizeof(ENUM15044),    ENUM15044,    FL_RONLY, DEV_ALL},     // Brennerstatus (Mögliche Werte: 0x07 = Brenner ein, 0x0D = Brenner aus, 0x03/0x09/0xFF)
{0x2D4F002D,  VT_YESNO,         15045, STR15045, sizeof(ENUM_YESNO),   ENUM_YESNO,   FL_RONLY, DEV_ALL},     // Verbindung erkannt (0 = ja, 1 = nein)
{0x2D38002E,  VT_ENUM,          15046, STR15046, sizeof(ENUM15046),    ENUM15046,    DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // QAA Type (0x52 = QAA 50 / 0x53 = QAA 70)
{0x2D600032,  VT_HOUR_MINUTES,  15050, STR15050, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Montag Start
{0x2D600033,  VT_HOUR_MINUTES,  15051, STR15051, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Montag Ende
{0x2D600034,  VT_HOUR_MINUTES,  15052, STR15052, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Montag Start
{0x2D600035,  VT_HOUR_MINUTES,  15053, STR15053, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Montag Ende
{0x2D600036,  VT_HOUR_MINUTES,  15054, STR15054, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Montag Start
{0x2D600037,  VT_HOUR_MINUTES,  15055, STR15055, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Montag Ende
{0x2D610038,  VT_HOUR_MINUTES,  15056, STR15056, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Dienstag Start
{0x2D610039,  VT_HOUR_MINUTES,  15057, STR15057, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Dienstag Ende
{0x2D61003A,  VT_HOUR_MINUTES,  15058, STR15058, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Dienstag Start
{0x2D61003B,  VT_HOUR_MINUTES,  15059, STR15059, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Dienstag Ende
{0x2D61003C,  VT_HOUR_MINUTES,  15060, STR15060, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Dienstag Start
{0x2D61003D,  VT_HOUR_MINUTES,  15061, STR15061, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Dienstag Ende
{0x2D62003E,  VT_HOUR_MINUTES,  15062, STR15062, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Mittwoch Start
{0x2D62003F,  VT_HOUR_MINUTES,  15063, STR15063, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Mittwoch Ende
{0x2D620040,  VT_HOUR_MINUTES,  15064, STR15064, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Mittwoch Start
{0x2D620041,  VT_HOUR_MINUTES,  15065, STR15065, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Mittwoch Ende
{0x2D620042,  VT_HOUR_MINUTES,  15066, STR15066, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Mittwoch Start
{0x2D620043,  VT_HOUR_MINUTES,  15067, STR15067, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Mittwoch Ende
{0x2D630044,  VT_HOUR_MINUTES,  15068, STR15068, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Donnerstag Start
{0x2D630045,  VT_HOUR_MINUTES,  15069, STR15069, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Donnerstag Ende
{0x2D630046,  VT_HOUR_MINUTES,  15070, STR15070, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Donnerstag Start
{0x2D630047,  VT_HOUR_MINUTES,  15071, STR15071, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Donnerstag Ende
{0x2D630048,  VT_HOUR_MINUTES,  15072, STR15072, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Donnerstag Start
{0x2D630049,  VT_HOUR_MINUTES,  15073, STR15073, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Donnerstag Ende
{0x2D64004A,  VT_HOUR_MINUTES,  15074, STR15074, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Freitag Start
{0x2D64004B,  VT_HOUR_MINUTES,  15075, STR15075, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Freitag Ende
{0x2D64004C,  VT_HOUR_MINUTES,  15076, STR15076, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Freitag Start
{0x2D64004D,  VT_HOUR_MINUTES,  15077, STR15077, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Freitag Ende
{0x2D64004E,  VT_HOUR_MINUTES,  15078, STR15078, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Freitag Start
{0x2D64004F,  VT_HOUR_MINUTES,  15079, STR15079, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Freitag Ende
{0x2D650050,  VT_HOUR_MINUTES,  15080, STR15080, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Samstag Start
{0x2D650051,  VT_HOUR_MINUTES,  15081, STR15081, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Samstag Ende
{0x2D650052,  VT_HOUR_MINUTES,  15082, STR15082, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Samstag Start
{0x2D650053,  VT_HOUR_MINUTES,  15083, STR15083, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Samstag Ende
{0x2D650054,  VT_HOUR_MINUTES,  15084, STR15084, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Samstag Start
{0x2D650055,  VT_HOUR_MINUTES,  15085, STR15085, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Samstag Ende
{0x2D660056,  VT_HOUR_MINUTES,  15086, STR15086, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Sonntag Start
{0x2D660057,  VT_HOUR_MINUTES,  15087, STR15087, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 1 Sonntag Ende
{0x2D660058,  VT_HOUR_MINUTES,  15088, STR15088, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Sonntag Start
{0x2D660059,  VT_HOUR_MINUTES,  15089, STR15089, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 2 Sonntag Ende
{0x2D66005A,  VT_HOUR_MINUTES,  15090, STR15090, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Sonntag Start
{0x2D66005B,  VT_HOUR_MINUTES,  15091, STR15091, 0,                    NULL,         DEFAULT_FLAG+FL_EEPROM, DEV_ALL}, // Zeitfenster 3 Sonntag Ende
//PPS-Bus commands end

/*
// ProgNrs 10900 to 10999 can be assigned to unrecognised command codes until
// we find a better explanation for them. !Assign STR99999 to all of them.!
*/
// Placeholder to keep the compiler happy with STR99999:
{0xDEADBEEF,  VT_UNKNOWN,       19999, STR99999, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, //


{CMD_UNKNOWN, VT_SECONDS_DWORD, BSP_INTERNAL+0, STR20000, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_DWORD,         BSP_INTERNAL+1, STR20001, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_SECONDS_DWORD, BSP_INTERNAL+2, STR20002, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_DWORD,         BSP_INTERNAL+3, STR20003, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_SECONDS_DWORD, BSP_INTERNAL+4, STR20004, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_DWORD,         BSP_INTERNAL+5, STR20005, 0,                  NULL,         FL_RONLY, DEV_ALL},     // brenner_duration
{CMD_UNKNOWN, VT_ONOFF,         BSP_INTERNAL+6, STR20006, sizeof(ENUM_ONOFF), ENUM_ONOFF,   DEFAULT_FLAG, DEV_ALL}, // reset 20000-20005
{CMD_UNKNOWN, VT_FLOAT,         BSP_AVERAGES,   STR20000, 0,                  NULL,         DEFAULT_FLAG, DEV_ALL}, // Dummy for averages parameters
{CMD_UNKNOWN, VT_STRING,        BSP_DHT22+0.0, STR20100, 0,                   NULL,         FL_RONLY, DEV_ALL},     // DHT22 sensor ID
{CMD_UNKNOWN, VT_TEMP,          BSP_DHT22+0.1, STR20101, 0,                   NULL,         FL_RONLY, DEV_ALL},     // DHT22 sensor Current temperature
{CMD_UNKNOWN, VT_PERCENT_WORD1, BSP_DHT22+0.2, STR20102, 0,                   NULL,         FL_RONLY, DEV_ALL},     // DHT22 sensor Humidity
{CMD_UNKNOWN, VT_GR_PER_CUBM,   BSP_DHT22+0.3, STR20103, 0,                   NULL,         FL_RONLY, DEV_ALL},     // DHT22 sensor Abs Humidity
{CMD_UNKNOWN, VT_STRING,        BSP_BME280+0.0, STR20200, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor address/ID
{CMD_UNKNOWN, VT_TEMP,          BSP_BME280+0.1, STR20201, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor Current temperature
{CMD_UNKNOWN, VT_PERCENT_WORD1, BSP_BME280+0.2, STR20202, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor Humidity
{CMD_UNKNOWN, VT_PRESSURE_HPA,  BSP_BME280+0.3, STR20203, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor Pressure [hPa]
{CMD_UNKNOWN, VT_ALTITUDE,      BSP_BME280+0.4, STR20204, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor Altitude [m]
{CMD_UNKNOWN, VT_GR_PER_CUBM,   BSP_BME280+0.5, STR20205, 0,                  NULL,         FL_RONLY, DEV_ALL},     // BME280 sensor Abs Humidity
{CMD_UNKNOWN, VT_STRING,        BSP_ONEWIRE+0.0, STR20300, 0,                 NULL,         FL_RONLY, DEV_ALL},     // One wire (Dallas) sensor ID
{CMD_UNKNOWN, VT_TEMP,          BSP_ONEWIRE+0.1, STR20301, 0,                 NULL,         FL_RONLY, DEV_ALL},     // One wire (Dallas) sensor Current temperature
{CMD_UNKNOWN, VT_STRING,        BSP_MAX+0.0, STR20500, 0,                     NULL,         FL_RONLY, DEV_ALL},     // MAX! sensor ID
{CMD_UNKNOWN, VT_TEMP,          BSP_MAX+0.1, STR20501, 0,                     NULL,         FL_RONLY, DEV_ALL},     // MAX! sensor Current temperature
{CMD_UNKNOWN, VT_TEMP,          BSP_MAX+0.2, STR20502, 0,                     NULL,         FL_RONLY, DEV_ALL},     // MAX! sensor Destination temperature
{CMD_UNKNOWN, VT_PERCENT_WORD1, BSP_MAX+0.3, STR20503, 0,                     NULL,         FL_RONLY, DEV_ALL},     // MAX! sensor valve opening (in percent)
{CMD_UNKNOWN, VT_FLOAT,         BSP_FLOAT, STR20700, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // custom_floats
{CMD_UNKNOWN, VT_LONG,          BSP_LONG, STR20800, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}, // custom_longs

//{CMD_END,     VT_UNKNOWN,       65535, "",       0,                    NULL,         DEFAULT_FLAG, DEV_ALL}

  //Prognr 65526 - 65534 is a dirty trick for reducing enumerations addresses to the same type
{0xDEADBEEF,  VT_ENUM,          65526, STR65535, sizeof(ENUM_LOGGER_MODE),  ENUM_LOGGER_MODE,   DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65527, STR65535, sizeof(ENUM_PPS_MODE),     ENUM_PPS_MODE,      DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65528, STR65535, sizeof(ENUM_WRITEMODE),    ENUM_WRITEMODE,     DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65529, STR65535, sizeof(ENUM_MQTT),         ENUM_MQTT,          DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65530, STR65535, sizeof(ENUM_DEBUG),        ENUM_DEBUG,         DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65531, STR65535, sizeof(ENUM_LOGTELEGRAM),  ENUM_LOGTELEGRAM,   DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65532, STR65535, sizeof(ENUM_BUSTYPE),      ENUM_BUSTYPE,       DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65533, STR65535, sizeof(ENUM_ONOFF),        ENUM_ONOFF,         DEFAULT_FLAG, DEV_ALL}, //
{0xDEADBEEF,  VT_ENUM,          65534, STR65535, sizeof(ENUM_EEPROM_ONOFF), ENUM_EEPROM_ONOFF,  DEFAULT_FLAG, DEV_ALL}, //
{CMD_END,     VT_UNKNOWN,       65535, STR65535, 0,                    NULL,         DEFAULT_FLAG, DEV_ALL}
};
