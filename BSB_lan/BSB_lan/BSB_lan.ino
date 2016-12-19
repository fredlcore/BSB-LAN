/*
 * BSB Boiler-System-Bus LAN Interface
 *
 * ATTENION:
 *       There is no waranty that this system will not damage your heating system!
 *
 * Author: Gero Schumacher (gero.schumacher@gmail.com)
 *        (based on the code and work from many other developers. Many thanks!)
 *
 * see README file for more information
 *
 * Version:
 *       0.1  - 21.01.2015 - initial version
 *       0.5  - 02.02.2015
 *       0.6  - 02.02.2015 
 *       0.7  - 06.02.2015 
 *       0.8  - 05.03.2015 
 *
 * Changelog:
 *       version 0.8
 *        - added parameters for ELCO Thision heating system
 *        - added IPWE extension
 *        - minor bugfixes
 *       version 0.7
 *        - added bus monitor functionality
 *       version 0.6
 *        - renamed SoftwareSerial to BSBSoftwareSerial
 *        - changed folder structure to enable simple build with arduino sdk
 *       version 0.5
 *        - bugfixes
 *        - added documentation (README)
 *        - added passkey feature
 *        - added R feature (query reset value)
 *        - added E feature (list enum values)
 *        - added setter for almost all value types
 *        - fixed indentation
 *        - added V feature to set verbosity for serial output
 *        - set baudrate to 115200 for serial output
 *        - redirecting favicon request
 *        - added some images of the BSB adapter
 *
 */

#include <avr/pgmspace.h>
#include "BSBSoftwareSerial.h"
#include "bsb.h"

#include <SPI.h>
#include <Ethernet.h>
#include <Arduino.h>
#include <util/crc16.h>

// if set to 1, all messages on the bus are printed to the serial interface
byte verbose = 0;
byte monitor = 0;

// if enabled the URL has to contain the defined passkey as first element
// e.g.
// http://192.168.178.88/1234/    - to see the help
// http://192.168.178.88/1234/K    - to list all categories
#define USE_PASSKEY  0

#define PASSKEY  "1234"

// defines the number of retries for the qery command
#define QUERY_RETRIES  3

// Adjust the following settings!

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
IPAddress ip(192,168,178,88);
EthernetServer server(80);
EthernetClient client;

// Software Serial needs special pins for RX: 10-13, 50-53, 62(A8)-69(A15)
// W5100 ethernet shield uses the following pins: 10, 50-53
BSB bus(68,69);

byte led0 = 3, led1 = 4 ; // Pins 3+4 for Relais

/****************************************************/
/* DEFINITIONS and TYPEDEFS                         */
/****************************************************/

/* telegram types */
#define TYPE_INF  0x02
#define TYPE_SET  0x03
#define TYPE_ACK  0x04
#define TYPE_NACK  0x05
#define TYPE_QUR  0x06
#define TYPE_ANS  0x07
#define TYPE_ERR  0x08
#define TYPE_QRV  0x0F // query reset value
#define TYPE_ARV  0x10 // anser reset value

/* telegram addresses */
#define ADDR_HEIZ  0x00
#define ADDR_RGT1  0x06
#define ADDR_RGT2  0x07
#define ADDR_DISP  0x0A
#define ADDR_ALL   0x7F

/* special command ids */
#define CMD_UNKNOWN 0x00000000u
#define CMD_END     0xffffffffu

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
  CAT_WAERMEPUMPE,
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
  CAT_IOTEST,
  CAT_STATUS,
  CAT_DIAG_KASKADE,
  CAT_DIAG_ERZEUGER,
  CAT_DIAG_VERBRAUCHER,
  CAT_FEUERUNGSAUTOMAT,
  CAT_USER_DEFINED,
  CAT_UNKNOWN
}category_t;

/* Parameter types */
typedef enum{
  VT_TEMP,              // 3 Byte - 1 enable / value/64
  VT_FP1,               // 3 Byte - 1 enable / value/10
  VT_FP02,              // 3 Byte - 1 enable / value/50
  VT_UINT,              // 3 Byte - 1 enable / value
  VT_ERRORCODE,         // 3 Byte - 1 enable / value
  VT_ONOFF,             //  2 Byte - 1 enable / 0=Aus 1=An (auch 0xff=An)
  VT_YESNO,             //  2 Byte - 1 enable / 0=Nein 1=Ja (auch 0xff=Ja)
  VT_CLOSEDOPEN,        //  2 Byte - 1 enable / 0=Offen 1=Geschlossen
  VT_MINUTES,           // 5 Byte - 1 enable / seconds/60
  VT_MINUTES_WORD,     // 3 Byte - 1 enable / minutes
  VT_MINUTES_SHORT,     // 2 Byte - 1 enable / minutes
  VT_HOURS,             // 5 Byte - 1 enable / seconds/3600
  VT_HOURS_WORD,        // 3 Byte - 1 enable / hours
  VT_HOURS_SHORT,       // 2 Byte - 1 enable / hours
  VT_HOUR_MINUTES,      // 3 Byte - 1 enable / h m
  VT_DAYS,              // 2 Byte - 1 enable / day
  VT_MONTHS,            // 2 Byte - 1 enable / months
  VT_DATETIME,          // 9 Byte - 1 enable / year+1900 month day weekday hour min sec
  VT_TIMEPROG,          // 12 Byte - 1_ein 1_aus 2_ein 2_aus 3_ein 3_aus (jeweils SS:MM)
  VT_VACATIONPROG,    // 9 Byte - 1 enable / byte 2/3 month/year
  VT_SUMMERPERIOD,    // 9 Byte - 1 enable / byte 2/3 month/year
  VT_WEEKDAY,           // 2 Byte - 1 enable / weekday (1=Mo..7=So)
  VT_PERCENT,           // 2 Byte - 1 enable / percent
  VT_PRESSURE,          // 2 Byte - 1 enable bar/10.0
  VT_PRESSURE_WORD,     // 3 Byte - 1 enable / bar/10.0
  VT_VOLTAGE,           // 2 Byte - 1 enable / volt (???) unklar, da nur 0.0V verfügbar
  VT_DWORD,             // 5 Byte - 1 enable / value
  VT_BYTE,              // 2 Byte - 1 enable / value
  VT_STRING,            // x Byte - 1 enable / string
  VT_ENUM,              // 2 Byte - 1 enable / value
  VT_LPBADDR,           // 2 Byte - 1 enable / adr/seg
  VT_UNKNOWN
}vt_type_t;

typedef struct {
  uint32_t cmd;
  uint8_t category;
  uint8_t type;
  uint16_t line;
  const char *desc;
  uint16_t enumstr_len;
  const char *enumstr;
} cmd_t;

/****************************************************/
/* PROGMEM TABLES and STRINGS                       */
/****************************************************/
//Kategorien
const char ENUM_CAT[] PROGMEM = {
"\x00 Uhrzeit und Datum\0"
"\x01 Bedieneinheit\0"
"\x02 Funk\0"
"\x03 Zeitprogramm Heizkreis 1\0"
"\x04 Zeitprogramm Heizkreis 2\0"
"\x05 Zeitprogramm 3/HKP\0"
"\x06 Zeitprogramm 4/TWW\0"
"\x07 Zeitprogramm 5\0"
"\x08 Ferien Heizkreis 1\0"
"\x09 Ferien Heizkreis 2\0"
"\x0a Ferien Heizkreis P\0"
"\x0b Heizkreis 1\0"
"\x0c Kühlkreis 1\0"
"\x0d Heizkreis 2\0"
"\x0e Heizkreis 3/P\0"
"\x0f Trinkwasser\0"
"\x10 Hx-Pumpe\0"
"\x11 Schwimmbad\0"
"\x12 Vorregler/Zubringerpumpe\0"
"\x13 Kessel\0"
"\x14 Wärmepumpe\0"
"\x15 Kaskade\0"
"\x16 Zusatzerzeuger\0"
"\x17 Solar\0"
"\x18 Feststoffkessel\0"
"\x19 Pufferspeicher\0"
"\x1a Trinkwasserspeicher\0"
"\x1b Trinkwasser Durchl'erhitzer\0"
"\x1c Konfiguration\0"
"\x1d LPB-System\0"
"\x1e Fehler\0"
"\x1f Wartung/Sonderbetrieb\0"
"\x20 Ein-/Ausgangstest\0"
"\x21 Status\0"
"\x22 Diagnose Kaskade\0"
"\x23 Diagnose Erzeuger\0"
"\x24 Diagnose Verbraucher\0"
"\x25 Feuerungsautomat\0"
"\x26 Benutzerdefiniert\0"
"\x27 unbekannte Kategorie\0"
};


 /* Menue Strings */
const char STR0[] PROGMEM = "Datum/Zeit";
const char STR1[] PROGMEM = "Stunden/Minuten";
const char STR2[] PROGMEM = "Tag/Monat";
const char STR3[] PROGMEM = "Jahr";
const char STR5[] PROGMEM = "Sommerzeitbeginn Tag/Monat";
const char STR6[] PROGMEM = "Sommerzeitende Tag/Monat";
const char STR20[] PROGMEM = "Sprachauswahl";
const char STR22[] PROGMEM = "Info";
const char STR23[] PROGMEM = "Fehleranzeige";
const char STR25[] PROGMEM = "Anzeigekontrast";
const char STR26[] PROGMEM = "Sperre Bedienung";
const char STR27[] PROGMEM = "Sperre Programmierung";
const char STR28[] PROGMEM = "Bedieneinheit Direktverstellung";
const char STR30[] PROGMEM = "Bedieneinheit Grundeinstellung sichern";
const char STR31[] PROGMEM = "Bedieneinheit Grundeinstellung aktivieren";
const char STR40[] PROGMEM = "Einsatz als";
const char STR42[] PROGMEM = "Zurodnung Raumgerät 1";
const char STR44[] PROGMEM = "Bedienung HK 2";
const char STR46[] PROGMEM = "Bedienung HK P";
const char STR48[] PROGMEM = "Wirkung Präsenztaste";
const char STR54[] PROGMEM = "Korrektur Raumfühler";
const char STR70[] PROGMEM = "Geräte-Version Bedienteil";
const char STR120[] PROGMEM = "Binding";
const char STR121[] PROGMEM = "Testmode";
const char STR130[] PROGMEM = "Raumgerät 1 Status ";
const char STR131[] PROGMEM = "Raumgerät 2 Status ";
const char STR132[] PROGMEM = "Raumgerät P Status ";
const char STR133[] PROGMEM = "Außenfühler P Status ";
const char STR134[] PROGMEM = "Repeater P Status ";
const char STR135[] PROGMEM = "Bedieneinheit 1 Status ";
const char STR136[] PROGMEM = "Bedieneinheit 2 Status ";
const char STR137[] PROGMEM = "Bedieneinheit P Status ";
const char STR138[] PROGMEM = "Servicegerät Status ";
const char STR140[] PROGMEM = "Alle Geräte löschen";
/*
const char STR500[] PROGMEM = "Vorwahl";
const char STR501[] PROGMEM = "Mo-So: 1. Phase Ein";
const char STR502[] PROGMEM = "Mo-So: 1. Phase Aus";
const char STR503[] PROGMEM = "Mo-So: 2. Phase Ein";
const char STR504[] PROGMEM = "Mo-So: 2. Phase Aus";
const char STR505[] PROGMEM = "Mo-So: 3. Phase Ein";
const char STR506[] PROGMEM = "Mo-So: 3. Phase Aus";
*/
const char STR500[] PROGMEM = "Mo";
const char STR501[] PROGMEM = "Di";
const char STR502[] PROGMEM = "Mi";
const char STR503[] PROGMEM = "Do";
const char STR504[] PROGMEM = "Fr";
const char STR505[] PROGMEM = "Sa";
const char STR506[] PROGMEM = "So";

const char STR516[] PROGMEM = "Standardwerte";
const char STR520[] PROGMEM = "Vorwahl";
const char STR521[] PROGMEM = "Mo-So: 1. Phase Ein";
const char STR522[] PROGMEM = "Mo-So: 1. Phase Aus";
const char STR523[] PROGMEM = "Mo-So: 2. Phase Ein";
const char STR524[] PROGMEM = "Mo-So: 2. Phase Aus";
const char STR525[] PROGMEM = "Mo-So: 3. Phase Ein";
const char STR526[] PROGMEM = "Mo-So: 3. Phase Aus";
const char STR536[] PROGMEM = "Standardwerte";
const char STR540[] PROGMEM = "Vorwahl";
const char STR541[] PROGMEM = "Mo-So: 1. Phase Ein";
const char STR542[] PROGMEM = "Mo-So: 1. Phase Aus";
const char STR543[] PROGMEM = "Mo-So: 2. Phase Ein";
const char STR544[] PROGMEM = "Mo-So: 2. Phase Aus";
const char STR545[] PROGMEM = "Mo-So: 3. Phase Ein";
const char STR546[] PROGMEM = "Mo-So: 3. Phase Aus";
const char STR556[] PROGMEM = "Standardwerte";
const char STR560[] PROGMEM = "Vorwahl";
const char STR561[] PROGMEM = "Mo-So: 1. Phase Ein";
const char STR562[] PROGMEM = "Mo-So: 1. Phase Aus";
const char STR563[] PROGMEM = "Mo-So: 2. Phase Ein";
const char STR564[] PROGMEM = "Mo-So: 2. Phase Aus";
const char STR565[] PROGMEM = "Mo-So: 3. Phase Ein";
const char STR566[] PROGMEM = "Mo-So: 3. Phase Aus";
const char STR576[] PROGMEM = "Standardwerte";
const char STR600[] PROGMEM = "Vorwahl";
const char STR601[] PROGMEM = "Mo-So: 1. Phase Ein";
const char STR602[] PROGMEM = "Mo-So: 1. Phase Aus";
const char STR603[] PROGMEM = "Mo-So: 2. Phase Ein";
const char STR604[] PROGMEM = "Mo-So: 2. Phase Aus";
const char STR605[] PROGMEM = "Mo-So: 3. Phase Ein";
const char STR606[] PROGMEM = "Mo-So: 3. Phase Aus";
const char STR616[] PROGMEM = "Standardwerte";

/* Die Zeilennummern 632-682 entsprechen nicht den Zeilennummern im Bedienteil, sondern wurden künstlich hinzugefügt*/
const char STR632[] PROGMEM = "Periode 1 Beginn Tag/Monat";
const char STR633[] PROGMEM = "Periode 1 Ende Tag/Monat";
const char STR634[] PROGMEM = "Periode 2 Beginn Tag/Monat";
const char STR635[] PROGMEM = "Periode 2 Ende Tag/Monat";
const char STR636[] PROGMEM = "Periode 3 Beginn Tag/Monat";
const char STR637[] PROGMEM = "Periode 3 Ende Tag/Monat";
const char STR638[] PROGMEM = "Periode 4 Beginn Tag/Monat";
const char STR639[] PROGMEM = "Periode 4 Ende Tag/Monat";
const char STR640[] PROGMEM = "Periode 5 Beginn Tag/Monat";
const char STR641[] PROGMEM = "Periode 5 Ende Tag/Monat";
const char STR642[] PROGMEM = "Periode 6 Beginn Tag/Monat";
const char STR643[] PROGMEM = "Periode 6 Ende Tag/Monat";
const char STR644[] PROGMEM = "Periode 7 Beginn Tag/Monat";
const char STR645[] PROGMEM = "Periode 7 Ende Tag/Monat";
const char STR646[] PROGMEM = "Periode 8 Beginn Tag/Monat";
const char STR647[] PROGMEM = "Periode 8 Ende Tag/Monat";
const char STR648[] PROGMEM = "Betriebsniveau";

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
const char STR641[] PROGMEM = "Vorwahl";
const char STR642[] PROGMEM = "Beginn Tag/Monat";
const char STR643[] PROGMEM = "Ende Tag/Monat";
const char STR648[] PROGMEM = "Betriebsniveau";
const char STR651[] PROGMEM = "Vorwahl";
const char STR652[] PROGMEM = "Beginn Tag/Monat";
const char STR653[] PROGMEM = "Ende Tag/Monat";
const char STR658[] PROGMEM = "Betriebsniveau";
const char STR661[] PROGMEM = "Vorwahl";
const char STR662[] PROGMEM = "Beginn Tag/Monat";
const char STR663[] PROGMEM = "Ende Tag/Monat";
const char STR668[] PROGMEM = "Betriebsniveau";
*/

const char STR700[] PROGMEM = "Betriebsart";
const char STR710[] PROGMEM = "Komfortsollwert";
const char STR711[] PROGMEM = "Komfortsollwert Maximum";
const char STR712[] PROGMEM = "Reduziertsollwert";
const char STR714[] PROGMEM = "Frostschutzsollwert";
const char STR720[] PROGMEM = "Kennlinie Steilheit";
const char STR721[] PROGMEM = "Kennlinie Verschiebung";
const char STR726[] PROGMEM = "Kennlinie Adaption";
const char STR730[] PROGMEM = "Sommer-/ Winterheizgrenze";
const char STR732[] PROGMEM = "Tagesheizgrenze";
const char STR740[] PROGMEM = "Vorlaufsollwert Minimum";
const char STR741[] PROGMEM = "Vorlaufsollwert Maximum";
const char STR750[] PROGMEM = "Raumeinfluss";
const char STR760[] PROGMEM = "Raumtemperaturbegrenzung";
const char STR770[] PROGMEM = "Schnellaufheizung";
const char STR780[] PROGMEM = "Schnellabsenkung";
const char STR790[] PROGMEM = "Einschalt-Optimierung Max.";
const char STR791[] PROGMEM = "Ausschalt-Optimierung Max.";
const char STR800[] PROGMEM = "Reduziert-Anhebung Begin";
const char STR801[] PROGMEM = "Reduziert-Anhebung Ende";
const char STR820[] PROGMEM = "Überhitzschutz Pumpenkreis";
const char STR830[] PROGMEM = "Mischerüberhöhung";
const char STR850[] PROGMEM = "Estrichfunktion";
const char STR851[] PROGMEM = "Estrich sollwert manuell";
const char STR861[] PROGMEM = "Übertemperaturabnahme";
const char STR870[] PROGMEM = "Mit Pufferspeicher";
const char STR872[] PROGMEM = "Mit Vorregler/Zubring`pumpe";
const char STR882[] PROGMEM = "Pumpendrehzahl Minimum";
const char STR883[] PROGMEM = "Pumpendrehzahl Maximum";
const char STR884[] PROGMEM = "Drehzahlstufe Ausleg'punkt";
const char STR885[] PROGMEM = "Pumpe-PWM Minimum";
const char STR886[] PROGMEM = "Norm Aussentemperatur";
const char STR887[] PROGMEM = "Vorlaufsoll NormAussentemp";
const char STR888[] PROGMEM = "dt Überhöhungsfaktor";
const char STR894[] PROGMEM = "dt Spreizung Norm Aussent.";
const char STR895[] PROGMEM = "dt Spreizung Maximum";
const char STR900[] PROGMEM = "Betriebsartumschaltung";
const char STR901[] PROGMEM = "Betriebsart";
const char STR902[] PROGMEM = "Komfortsollwert";
const char STR907[] PROGMEM = "Freigabe";
const char STR908[] PROGMEM = "Vorlaufsollwert bei TA 25 °C";
const char STR909[] PROGMEM = "Vorlaufsollwert bei TA 35 °C";
const char STR912[] PROGMEM = "Kühlgrenze bei TA";
const char STR913[] PROGMEM = "Sperrdauer nach Heizende";
const char STR918[] PROGMEM = "Sommerkomp Beginn bei TA";
const char STR919[] PROGMEM = "Sommerkomp Ende bei TA";
const char STR920[] PROGMEM = "Sommerkomp Sollw’anhebung";
const char STR923[] PROGMEM = "Vorlaufsollwert Min bei TA 25 °C";
const char STR924[] PROGMEM = "Vorlaufsollwert Min bei TA 35 °C";
const char STR928[] PROGMEM = "Raumeinfluss";
const char STR932[] PROGMEM = "Raumtemperaturbegrenzung";
const char STR938[] PROGMEM = "Mischerunterkühlung";
const char STR939[] PROGMEM = "Antrieb Typ";
const char STR940[] PROGMEM = "Schaltdifferenz 2-Punkt";
const char STR941[] PROGMEM = "Antrieb Laufzeit";
const char STR945[] PROGMEM = "Mischventil im Heizbetrieb";
const char STR946[] PROGMEM = "Sperrdauer Taupunktwächt";
const char STR947[] PROGMEM = "Vorlaufsollw’anhebung Hygro";
const char STR948[] PROGMEM = "Vorl'anhebung Beginn bei r. F.";
const char STR950[] PROGMEM = "Vorlauftemp'diff Taupunkt";
const char STR962[] PROGMEM = "Mit Pufferspeicher";
const char STR963[] PROGMEM = "Mit Vorregler/Zubring'pumpe";
const char STR969[] PROGMEM = "Betriebsartumschaltung";
const char STR1010[] PROGMEM = "Komfortsollwert";
const char STR1011[] PROGMEM = "Komfortsollwert Maximum";
const char STR1012[] PROGMEM = "Reduziertsollwert";
const char STR1014[] PROGMEM = "Frostschutzsollwert";
const char STR1020[] PROGMEM = "Kennlinie Steilheit";
const char STR1021[] PROGMEM = "Kennlinie Verschiebung";
const char STR1026[] PROGMEM = "Kennlinie Adaption";
const char STR1030[] PROGMEM = "Sommer-/ Winterheizgrenze";
const char STR1032[] PROGMEM = "Tagesheizgrenze";
const char STR1040[] PROGMEM = "Vorlaufsollwert Minimum";
const char STR1041[] PROGMEM = "Vorlaufsollwert Maximum";
const char STR1050[] PROGMEM = "Raumeinfluss";
const char STR1060[] PROGMEM = "Raumtemperaturbegrenzung";
const char STR1070[] PROGMEM = "Schnellaufheizung";
const char STR1080[] PROGMEM = "Schnellabsenkung";
const char STR1090[] PROGMEM = "Einschalt-Optimierung Max.";
const char STR1091[] PROGMEM = "Ausschalt-Optimierung Max.";
const char STR1100[] PROGMEM = "Reduziert-Anhebung Begin";
const char STR1101[] PROGMEM = "Reduziert-Anhebung Ende";
const char STR1120[] PROGMEM = "Überhitzschutz Pumpenkreis";
const char STR1130[] PROGMEM = "Mischerüberhöhung";
const char STR1132[] PROGMEM = "Antrieb Typ";
const char STR1133[] PROGMEM = "Schaltdiffernez 2-Punkt";
const char STR1134[] PROGMEM = "Antrieb Laufzeit";
const char STR1135[] PROGMEM = "Mischer P-Band XP";
const char STR1150[] PROGMEM = "Estrichfunktion";
const char STR1151[] PROGMEM = "Estrich sollwert manuell";
const char STR1155[] PROGMEM = "Estrich Sollwert aktuell";
const char STR1156[] PROGMEM = "Estrich Tag aktuell";
const char STR1157[] PROGMEM = "Estrich Tag erfüllt";
const char STR1161[] PROGMEM = "Übertemperaturabnahme";
const char STR1170[] PROGMEM = "Mit Pufferspeicher";
const char STR1172[] PROGMEM = "Mit Vorregler/Zubring`pumpe";
const char STR1182[] PROGMEM = "Pumpendrehzahl Minimum";
const char STR1183[] PROGMEM = "Pumpendrehzahl Maximum";
const char STR1200[] PROGMEM = "Betriebsartumschaltung";
const char STR1300[] PROGMEM = "Betriebsart";
const char STR1310[] PROGMEM = "Komfortsollwert";
const char STR1312[] PROGMEM = "Reduziertsollwert";
const char STR1314[] PROGMEM = "Frostschutzsollwert";
const char STR1320[] PROGMEM = "Kennlinie Steilheit";
const char STR1321[] PROGMEM = "Kennlinie Verschiebung";
const char STR1326[] PROGMEM = "Kennlinie Adaption";
const char STR1330[] PROGMEM = "Sommer-/ Winterheizgrenze";
const char STR1332[] PROGMEM = "Tagesheizgrenze";
const char STR1340[] PROGMEM = "Vorlaufsollwert Minimum";
const char STR1341[] PROGMEM = "Vorlaufsollwert Maximum";
const char STR1350[] PROGMEM = "Raumeinfluss";
const char STR1360[] PROGMEM = "Raumtemperaturbegrenzung";
const char STR1370[] PROGMEM = "Schnellaufheizung";
const char STR1380[] PROGMEM = "Schnellabsenkung";
const char STR1390[] PROGMEM = "Einschalt-Optimierung Max.";
const char STR1391[] PROGMEM = "Ausschalt-Optimierung Max.";
const char STR1400[] PROGMEM = "Reduziert-Anhebung Begin";
const char STR1401[] PROGMEM = "Reduziert-Anhebung Ende";
const char STR1420[] PROGMEM = "Überhitzschutz Pumpenkreis";
const char STR1430[] PROGMEM = "Mischerüberhöhung";
const char STR1450[] PROGMEM = "Estrichfunktion";
const char STR1451[] PROGMEM = "Estrich sollwert manuell";
const char STR1455[] PROGMEM = "Estrich Sollwert aktuell";
const char STR1456[] PROGMEM = "Estrich Tag aktuell";
const char STR1457[] PROGMEM = "Estrich Tag erfüllt";
const char STR1461[] PROGMEM = "Übertemperaturabnahme";
const char STR1470[] PROGMEM = "Mit Pufferspeicher";
const char STR1472[] PROGMEM = "Mit Vorregler/Zubring`pumpe";
const char STR1482[] PROGMEM = "Pumpendrehzahl Minimum";
const char STR1483[] PROGMEM = "Pumpendrehzahl Maximum";
const char STR1500[] PROGMEM = "Betriebsartumschaltung";
const char STR1600[] PROGMEM = "Trinkwasserbetrieb";
const char STR1610[] PROGMEM = "Nennsollwert";
const char STR1612[] PROGMEM = "Reduziertsollwert";
const char STR1620[] PROGMEM = "Freigabe";
const char STR1630[] PROGMEM = "Ladevorgang";
const char STR1640[] PROGMEM = "Legionellenfunktion";
const char STR1641[] PROGMEM = "Legionellenfkt. Periodisch";
const char STR1642[] PROGMEM = "Legionellenfkt. Wochentag";
const char STR1644[] PROGMEM = "Legionellenfkt. Zeitpunkt";
const char STR1645[] PROGMEM = "Legionellenfkt. Sollwert";
const char STR1646[] PROGMEM = "Legionellenfkt. Verweildauer";
const char STR1647[] PROGMEM = "Legionellenfkt. Zirk`pumpe";
const char STR1660[] PROGMEM = "Zirkulationspumpe Freigabe";
const char STR1661[] PROGMEM = "Zirk`pumpe Taktbetrieb";
const char STR1663[] PROGMEM = "Zirkulations Sollwert";
const char STR2008[] PROGMEM = "H1 TWW-Ladevorrang";
const char STR2010[] PROGMEM = "H1 Übertemperaturabnahme";
const char STR2012[] PROGMEM = "H1 mit Pufferspeicher";
const char STR2014[] PROGMEM = "H1 Vorregler/Zubring`pumpe";
const char STR2015[] PROGMEM = "H1 Kälteanforderung";
const char STR2033[] PROGMEM = "H2 TWW-Ladevorrang ";
const char STR2035[] PROGMEM = "H2 Übertemperaturabnahme ";
const char STR2037[] PROGMEM = "H2 mit Pufferspeicher ";
const char STR2039[] PROGMEM = "H2 Vorregler / Zubring'pumpe ";
const char STR2040[] PROGMEM = "H2 Kälteanforderung";
const char STR2044[] PROGMEM = "H3 TWW-Ladevorrang";
const char STR2046[] PROGMEM = "H3 Übertemperaturabnahme";
const char STR2048[] PROGMEM = "H3 mit Pufferspeicher";
const char STR2050[] PROGMEM = "H3 Vorregler/Zubring`pumpe";
const char STR2051[] PROGMEM = "H3 Kälteanforderung";
const char STR2055[] PROGMEM = "Sollwert Solarbeheizung ";
const char STR2056[] PROGMEM = "Sollwert Erzeugerbeheizung ";
const char STR2065[] PROGMEM = "Ladevorrang Solar ";
const char STR2070[] PROGMEM = "Schwimmbadtemp Maximum";
const char STR2080[] PROGMEM = "Mit Solareinbindung";
const char STR2150[] PROGMEM = "Vorregler/Zubringerpumpe";
const char STR2201[] PROGMEM = "Erzeugersperre";
const char STR2203[] PROGMEM = "Freigabe unter Außentemp";
const char STR2205[] PROGMEM = "Bei Ökobetrieb";
const char STR2208[] PROGMEM = "Durchladung Pufferspeicher";
const char STR2210[] PROGMEM = "Sollwert Minimum";
const char STR2212[] PROGMEM = "Sollwert maximum";
const char STR2214[] PROGMEM = "Sollwert Handbetrieb";
const char STR2220[] PROGMEM = "Freigabeintegral Stufe 2";
const char STR2221[] PROGMEM = "Rückstellintegral Stufe 2";
const char STR2270[] PROGMEM = "Rücklaufsollwert Minimum";
const char STR2291[] PROGMEM = "Steuerung Bypasspumpe";
const char STR2330[] PROGMEM = "Leistung Nenn";
const char STR2331[] PROGMEM = "Leistung Grundstufe";
const char STR2340[] PROGMEM = "Auto Erz’folge 2 x 1 Kaskade";
const char STR2440[] PROGMEM = "Gebläse-PWM Hz Maximum";
const char STR2442[] PROGMEM = "Gebläse-PWM Reglerverzögerung";
const char STR2444[] PROGMEM = "Leistung Minimum";
const char STR2445[] PROGMEM = "Leistung Nenn";
const char STR2451[] PROGMEM = "Brennerpausenzeit Minimum";
const char STR2459[] PROGMEM = "Sperrzeit dynam Schaltdiff";
const char STR2471[] PROGMEM = "Pumpennachlaufzeit HK's";
const char STR2540[] PROGMEM = "Proportionalbeiwert Kp TWW";
const char STR2543[] PROGMEM = "Proportionalbeiwert Kp HK's";
const char STR2800[] PROGMEM = "Frostschutz Kondens’pumpe";
const char STR2801[] PROGMEM = "Steuerung Kondens’pumpe";
const char STR2802[] PROGMEM = "Vorlaufzeit Kondens’pumpe";
const char STR2803[] PROGMEM = "Nachlaufzeit Kondens’pumpe";
const char STR2805[] PROGMEM = "Soll Temp’Spreizung Kond";
const char STR2806[] PROGMEM = "Max Abweich Spreiz Kondens";
const char STR2815[] PROGMEM = "Quellentemp Min Wasser";
const char STR2816[] PROGMEM = "Quellentemp Min Sole";
const char STR2817[] PROGMEM = "Schaltdiff Quellenschutz";
const char STR2818[] PROGMEM = "Erhöhung Quellenschutztemp";
const char STR2819[] PROGMEM = "Vorlaufzeit Quelle";
const char STR2820[] PROGMEM = "Nachlaufzeit Quelle";
const char STR2821[] PROGMEM = "Quellen-Anlaufzeit Maximum";
const char STR2822[] PROGMEM = "Zeit Begr Quelletemp Min";
const char STR2840[] PROGMEM = "Schaltdiff Rücklauftemp";
const char STR2841[] PROGMEM = "Verd'laufzeit min einhalten";
const char STR2842[] PROGMEM = "Verdichterlaufzeit Minimum";
const char STR2843[] PROGMEM = "Verdichtersillstandszeit Min";
const char STR2844[] PROGMEM = "Ausschalttemp. max";
const char STR2845[] PROGMEM = "Reduktion Ausschaltemp Max";
const char STR2846[] PROGMEM = "Heissgastemp Max";
const char STR2852[] PROGMEM = "ND-Verzögerung beim Start";
const char STR2880[] PROGMEM = "Verwendung Elektro-Vorlauf";
const char STR2881[] PROGMEM = "Sperrzeit Elektro-Vorlauf ";
const char STR2882[] PROGMEM = "Freigabeintegr. Elektro-Vorl ";
const char STR2883[] PROGMEM = "Rückstellintegr. Elektro-Vorl ";
const char STR2884[] PROGMEM = "Freig Elektro-Vorl unter TA ";
const char STR2886[] PROGMEM = "Kompensation Wärmedefizit";
const char STR2893[] PROGMEM = "Anzahl TWW-Ladeversuche ";
const char STR2894[] PROGMEM = "Verzögerung Drehstr'fehler ";
const char STR2895[] PROGMEM = "Verzögerung Ström'wächter ";
const char STR2910[] PROGMEM = "Freigabe oberhalb TA ";
const char STR2911[] PROGMEM = "Für Pufferzwangsladung";
const char STR2912[] PROGMEM = "Durchladung Pufferspeicher";
const char STR2951[] PROGMEM = "Abtaufreigabe unterhalb TA ";
const char STR2952[] PROGMEM = "Schaltdifferenz Abtauen ";
const char STR2954[] PROGMEM = "Verdampfertemp Abtau-Ende ";
const char STR2963[] PROGMEM = "Dauer bis Zwangsabtauen ";
const char STR2964[] PROGMEM = "Abtaudauer Maximal ";
const char STR2965[] PROGMEM = "Abtropfdauer Verdampfer ";
const char STR2966[] PROGMEM = "Abkühldauer Verdampfer ";
const char STR3002[] PROGMEM = "Quellentemp min Kühlbetrieb ";
const char STR3006[] PROGMEM = "Während Verdichterbetrieb";
const char STR3007[] PROGMEM = "Im passiven Kühlbetrieb";
const char STR3010[] PROGMEM = "Drehz max V'lator/Q'Pump ";
const char STR3510[] PROGMEM = "Führungsstrategie";
const char STR3530[] PROGMEM = "Freigabeintegral Erz’folge";
const char STR3531[] PROGMEM = "Rückstellintegral Erz’folge";
const char STR3532[] PROGMEM = "Wiedereinschaltsperre";
const char STR3533[] PROGMEM = "Zuschaltverzögerung";
const char STR3540[] PROGMEM = "Auto Erz’folge Umschaltung";
const char STR3541[] PROGMEM = "Auto Erz’folge Ausgrenzung";
const char STR3544[] PROGMEM = "Führender Erzeuger";
const char STR3550[] PROGMEM = "Anfahrentlast Kaskad'pumpe";
const char STR3560[] PROGMEM = "Rücklaufsollwert Minimum";
const char STR3590[] PROGMEM = "Temp’spreizung Minimum";
const char STR3700[] PROGMEM = "Freigabe unter Außentemp";
const char STR3701[] PROGMEM = "Freigabe über Außentemp";
const char STR3705[] PROGMEM = "Nachlaufzeit";
const char STR3720[] PROGMEM = "Schaltintegral";
const char STR3722[] PROGMEM = "Schaltdifferenz Aus";
const char STR3723[] PROGMEM = "Sperrzeit";
const char STR3810[] PROGMEM = "Temperaturdifferenz Ein";
const char STR3811[] PROGMEM = "Temperaturdifferenz Aus";
const char STR3812[] PROGMEM = "Ladetemp Min TWW-Speicher";
const char STR3813[] PROGMEM = "Temp’diff EIN Puffer";
const char STR3814[] PROGMEM = "Temp’diff AUS Puffer";
const char STR3815[] PROGMEM = "Ladetemp Min Puffer";
const char STR3816[] PROGMEM = "Temp'differenz EIN Sch'bad";
const char STR3817[] PROGMEM = "Temp'differenz AUS Sch'bad";
const char STR3818[] PROGMEM = "Ladetemp Min Schwimmbad";
const char STR3822[] PROGMEM = "Ladevorrang Speicher";
const char STR3825[] PROGMEM = "Ladezeit relativer Vorrang";
const char STR3826[] PROGMEM = "Wartezeit relativer Vorrang";
const char STR3827[] PROGMEM = "Wartezeit Parallelbetrieb";
const char STR3828[] PROGMEM = "Verzögerung Sekundärpumpe";
const char STR3830[] PROGMEM = "Kollektorstartfunktion";
const char STR3831[] PROGMEM = "Mindestlaufzeit Kollek`pumpe";
const char STR3832[] PROGMEM = "Kollektorstartfunktion Ein";
const char STR3833[] PROGMEM = "Kollektorstartfunktion Aus";
const char STR3834[] PROGMEM = "Kollektorstartfkt Gradient";
const char STR3840[] PROGMEM = "Kollektor Frostschutz";
const char STR3850[] PROGMEM = "Kollektorüberhitzschutz";
const char STR3860[] PROGMEM = "Verdampfung Wärmeträger";
const char STR3870[] PROGMEM = "Pumpendrehzahl Minimum";
const char STR3871[] PROGMEM = "Pumpendrehzahl Maximum";
const char STR3880[] PROGMEM = "Frostschutzmittel";
const char STR3881[] PROGMEM = "Frost'mittel Konzentration";
const char STR3884[] PROGMEM = "Pumpendurchfluss";
const char STR4102[] PROGMEM = "Sperrt andere Erzeuger";
const char STR4110[] PROGMEM = "Sollwert Minimum";
const char STR4130[] PROGMEM = "Temperaturdifferenz Ein";
const char STR4131[] PROGMEM = "Temperaturdifferenz Aus";
const char STR4133[] PROGMEM = "Vergleichstempertatur";
const char STR4140[] PROGMEM = "Pumpennachlaufzeit";
const char STR4141[] PROGMEM = "Übertemperaturableitung";
const char STR4708[] PROGMEM = "Zwangsladungsollwert Kühlen";
const char STR4709[] PROGMEM = "Zwangsladungsoll Heizen Min";
const char STR4710[] PROGMEM = "Zwangsladungsoll Heizen Max";
const char STR4711[] PROGMEM = "Zwangsladung Zeitpunkt";
const char STR4712[] PROGMEM = "Zwangsladung Dauer Max";
const char STR4720[] PROGMEM = "Auto Erzeugersperre";
const char STR4721[] PROGMEM = "Auto Erzeugersperre SD";
const char STR4722[] PROGMEM = "Temp`diff Puffer/Heizkreis";
const char STR4724[] PROGMEM = "Min Speichertemp Heizbetrieb";
const char STR4739[] PROGMEM = "Schichtschutz";
const char STR4750[] PROGMEM = "Ladetemperatur Maximum";
const char STR4755[] PROGMEM = "Rückkühltemperatur";
const char STR4756[] PROGMEM = "Rückkühlung TWW/HK`s";
const char STR4757[] PROGMEM = "Rückkühlung Kollektor";
const char STR4760[] PROGMEM = "Ladefühler Elektroeinsatz";
const char STR4761[] PROGMEM = "Zwangsladung mit Elektro";
const char STR4783[] PROGMEM = "Mit Solareinbindung";
const char STR4790[] PROGMEM = "Temp'diff EIN Rückl'umlenk";
const char STR4791[] PROGMEM = "Temp'diff AUS Rückl'umlenk";
const char STR4795[] PROGMEM = "Vergleichstemp Rückl'umlenk";
const char STR4796[] PROGMEM = "Wirksinn Rücklaufumlenkung";
const char STR4810[] PROGMEM = "Durchladung";
const char STR5010[] PROGMEM = "Ladung";
const char STR5020[] PROGMEM = "Vorlaufsollwertüberhöhung";
const char STR5021[] PROGMEM = "Umladeüberhöhung";
const char STR5022[] PROGMEM = "Ladeart";
const char STR5050[] PROGMEM = "Ladetemperatur Maximum";
const char STR5055[] PROGMEM = "Rückkühltemperatur";
const char STR5056[] PROGMEM = "Rückkühlung Kessel/HK";
const char STR5057[] PROGMEM = "Rückkühlung Kollektor";
const char STR5060[] PROGMEM = "Elektroeinsatz Betriebsart";
const char STR5061[] PROGMEM = "Elektroeinsatz Freigabe";
const char STR5062[] PROGMEM = "Elektroeinsatz Regelung";
const char STR5085[] PROGMEM = "Übertemperaturabnahme";
const char STR5090[] PROGMEM = "Mit Pufferspeicher";
const char STR5092[] PROGMEM = "Mit Vorregler/Zubring`pumpe";
const char STR5093[] PROGMEM = "Mit Solareinbindung";
const char STR5101[] PROGMEM = "Pumpendrehzahl Minimum";
const char STR5102[] PROGMEM = "Pumpendrehzahl Maximum";
const char STR5130[] PROGMEM = "Umladestrategie";
const char STR5131[] PROGMEM = "Vergleichstemp Umladung";
const char STR5400[] PROGMEM = "Komfortsollwert";
const char STR5406[] PROGMEM = "Min Sollw'diff zu Speich'temp ";
const char STR5420[] PROGMEM = "Vorlauf-Sollwertüberhöhung";
const char STR5450[] PROGMEM = "Gradient Zapfende";
const char STR5451[] PROGMEM = "Gradient Beginn Zapf Komf";
const char STR5452[] PROGMEM = "Gradient Beginn Zapfung Hz";
const char STR5480[] PROGMEM = "Komfortzeit ohne Hz-Anforderung";
const char STR5481[] PROGMEM = "Komfortzeit mit Hz-Anforderung";
const char STR5487[] PROGMEM = "Pumpennachlauf Komf";
const char STR5530[] PROGMEM = "Pumpendrehzahl Minimum ";
const char STR5544[] PROGMEM = "Antrieb Laufzeit ";
const char STR5700[] PROGMEM = "Voreinstellung";
const char STR5701[] PROGMEM = "Hydraulisches Schema";
const char STR5710[] PROGMEM = "Heizkreis 1";
const char STR5711[] PROGMEM = "Kühlkreis 1 ";
const char STR5712[] PROGMEM = "Verwendung Mischer 1";
const char STR5715[] PROGMEM = "Heizkreis2";
const char STR5730[] PROGMEM = "Trinkwasser-Sensor B3";
const char STR5731[] PROGMEM = "Trinkwasser-Stellglied Q3";
const char STR5732[] PROGMEM = "TWW Pumpenpause Umsch UV";
const char STR5733[] PROGMEM = "TWW Pumpenpause Verzögerung";
const char STR5736[] PROGMEM = "Trinkwasser Trennschaltung";
const char STR5761[] PROGMEM = "Zubringerpumpe Q8 Bit 0-3";
const char STR5770[] PROGMEM = "Erzeugertyp";
const char STR5772[] PROGMEM = "Brenner Vorlaufzeit";
const char STR5800[] PROGMEM = "Wärmequelle";
const char STR5807[] PROGMEM = "Kälteerzeugung";
const char STR5810[] PROGMEM = "Spreizung HK bei TA –10 °C";
const char STR5840[] PROGMEM = "Solarstellglied";
const char STR5841[] PROGMEM = "Externer Solartauscher";
const char STR5870[] PROGMEM = "Kombispeicher";
const char STR5890[] PROGMEM = "Relaisausgang QX1";
const char STR5891[] PROGMEM = "Relaisausgang QX2";
const char STR5892[] PROGMEM = "Relaisausgang QX3";
const char STR5894[] PROGMEM = "Relaisausgang QX4";
const char STR5895[] PROGMEM = "Relaisausgang QX5";
const char STR5896[] PROGMEM = "Relaisausgang QX6";
const char STR5908[] PROGMEM = "Funktion Ausgang QX3-Mod";
const char STR5909[] PROGMEM = "Funktion Ausgang QX4-Mod";
const char STR5920[] PROGMEM = "Relaisausgang K2 LMU-Basis Bit 0-7";
const char STR5921[] PROGMEM = "Default K2 auf K1";
const char STR5922[] PROGMEM = "Relaisausgang 1 RelCl";
const char STR5923[] PROGMEM = "Relaisausgang 2 RelCl";
const char STR5924[] PROGMEM = "Relaisausgang 3 RelCl";
const char STR5926[] PROGMEM = "Relaisausgang 1 SolCl";
const char STR5927[] PROGMEM = "Relaisausgang 2 SolCl";
const char STR5928[] PROGMEM = "Relaisausgang 3 SolCl";
const char STR5930[] PROGMEM = "Fühlereingang BX 1";
const char STR5931[] PROGMEM = "Fühlereingang BX 2";
const char STR5932[] PROGMEM = "Fühlereingang BX 3";
const char STR5933[] PROGMEM = "Fühlereingang BX 4";
const char STR5934[] PROGMEM = "Fühlereingang BX5";
const char STR5950[] PROGMEM = "Funktion Eingang H1";
const char STR5951[] PROGMEM = "Wirksinn Kontakt H1";
const char STR5952[] PROGMEM = "Minimaler Vorlaufsollwert H1";
const char STR5953[] PROGMEM = "Spannungswert 1 H1";
const char STR5954[] PROGMEM = "Wärmeanforderung 10V H1";
const char STR5955[] PROGMEM = "Spannungswert 2 H1";
const char STR5956[] PROGMEM = "Druckwert 3.5V H1";
const char STR5957[] PROGMEM = "Modemfunktion";
const char STR5960[] PROGMEM = "Funktion Eingang H3";
const char STR5961[] PROGMEM = "Wirksinn Kontakt H3";
const char STR5962[] PROGMEM = "Minimaler Vorlaufsollwert H3";
const char STR5963[] PROGMEM = "Spannungswert 1 H3";
const char STR5964[] PROGMEM = "Wärmeanforderung 10V H3";
const char STR5965[] PROGMEM = "Spannungswert 2 H3";
const char STR5966[] PROGMEM = "Druckwert 3.5V H3";
const char STR5970[] PROGMEM = "Konfig Raumthermostat 1";
const char STR5971[] PROGMEM = "Konfig Raumthermostat 2";
const char STR5973[] PROGMEM = "Funktion Eingang RelCl";
const char STR5975[] PROGMEM = "Ext. Vorlaufsollwert Maximum";
const char STR5978[] PROGMEM = "Funktion Eingang SolCl";
const char STR5980[] PROGMEM = "Funktion Eingang EX1";
const char STR5981[] PROGMEM = "Wirksinn Eingang EX1";
const char STR5982[] PROGMEM = "Funktion Eingang EX2";
const char STR5983[] PROGMEM = "Wirksinn Eingang EX2";
const char STR5984[] PROGMEM = "Funktion Eingang EX3";
const char STR5985[] PROGMEM = "Wirksinn Eingang EX3";
const char STR5986[] PROGMEM = "Funktion Eingang EX4";
const char STR5987[] PROGMEM = "Wirksinn Eingang EX4";
const char STR5988[] PROGMEM = "Funktion Eingang EX5";
const char STR5990[] PROGMEM = "Funktion Eingang EX6";
const char STR5992[] PROGMEM = "Funktion Eingang EX7";
const char STR6014[] PROGMEM = "Funktion Mischergruppe 1";
const char STR6015[] PROGMEM = "Funktion Mischergruppe 2";
const char STR6020[] PROGMEM = "Funktion Erweiterungsmodul 1";
const char STR6021[] PROGMEM = "Funktion Erweiterungsmodul 2";
const char STR6030[] PROGMEM = "Relaisausgang QX21";
const char STR6031[] PROGMEM = "Relaisausgang QX22";
const char STR6032[] PROGMEM = "Relaisausgang QX23";
const char STR6040[] PROGMEM = "Fühlereingang BX21";
const char STR6041[] PROGMEM = "Fühlereingang BX22";
const char STR6046[] PROGMEM = "Funktion Eingang H2";
const char STR6047[] PROGMEM = "Wirksinn Kontakt H2";
const char STR6048[] PROGMEM = "Minimaler Vorlaufsollwert H2";
const char STR6049[] PROGMEM = "Spannungswert 1 H2";
const char STR6050[] PROGMEM = "Temperaturwert 10V H2";
const char STR6051[] PROGMEM = "Spannungswert 2 H2";
const char STR6052[] PROGMEM = "Funktionswert 2 H2";
const char STR6070[] PROGMEM = "Funktion Ausgang UX";
const char STR6071[] PROGMEM = "Signallogik Ausgang UX";
const char STR6072[] PROGMEM = "Signal Ausgang UX";
const char STR6075[] PROGMEM = "Temperaturwert 10V UX";
const char STR6089[] PROGMEM = "Mod Pumpe Drehzahlstufen";
const char STR6092[] PROGMEM = "Mod Pumpe PWM";
const char STR6097[] PROGMEM = "Fühlertyp Kollektor";
const char STR6098[] PROGMEM = "Korrektur Kollektorfühler";
const char STR6099[] PROGMEM = "Korrektur Kollektorfühler 2";
const char STR6100[] PROGMEM = "korrektur Aussenfühler";
const char STR6101[] PROGMEM = "Fühlertyp Abgastemperatur";
const char STR6102[] PROGMEM = "Korrektur Abgastemp'fühler";
const char STR6110[] PROGMEM = "Zeitkonstante Gebäude";
const char STR6112[] PROGMEM = "Gradient Raummodell";
const char STR6120[] PROGMEM = "Anlagenfrostschutz";
const char STR6128[] PROGMEM = "Wärm'anfo unter Außentemp";
const char STR6129[] PROGMEM = "Wärm'anfo über Außentemp";
const char STR6130[] PROGMEM = "H1 mit Pufferspeicher";
const char STR6131[] PROGMEM = "Wärm'anfo bei Ökobetrieb";
const char STR6134[] PROGMEM = "H2 mit Pufferspeicher";
const char STR6135[] PROGMEM = "Luftentfeuchter";
const char STR6136[] PROGMEM = "Luftentfeuchter Freigabe";
const char STR6137[] PROGMEM = "Luftentfeuchter r. F. EIN";
const char STR6138[] PROGMEM = "Luftentfeuchter r. F. SD";
const char STR6200[] PROGMEM = "Fühler Speichern";
const char STR6201[] PROGMEM = "Fühler löschen";
const char STR6205[] PROGMEM = "Parameter zurücksetzen";
const char STR6212[] PROGMEM = "Kontrollbnummer Erzeuger 1";
const char STR6213[] PROGMEM = "Kontrollbnummer Erzeuger 2";
const char STR6215[] PROGMEM = "Kontrollnummer Speicher";
const char STR6217[] PROGMEM = "Kontrollnummer Heizkreise";
const char STR6220[] PROGMEM = "Software- Version LOGON B";
const char STR6221[] PROGMEM = "Entwicklungs-Index";
const char STR6225[] PROGMEM = "Gerätefamilie";
const char STR6226[] PROGMEM = "Gerätevariante";
const char STR6227[] PROGMEM = "Objektverzeichnis-Version";
const char STR6240[] PROGMEM = "KonfigRg1 Bit 0-7";
const char STR6270[] PROGMEM = "KonfigRg4 Bit 0-7";
const char STR6300[] PROGMEM = "KonfigRg7 Bit 0-7";
const char STR6310[] PROGMEM = "KonfigRg8 Bit 0-7";
const char STR6330[] PROGMEM = "KonfigRg10 Bit 0-7";
const char STR6600[] PROGMEM = "Geräteadresse";
const char STR6601[] PROGMEM = "Segmentadresse";
const char STR6604[] PROGMEM = "Busspeisung Funktion";
const char STR6605[] PROGMEM = "Busspeisung Status";
const char STR6606[] PROGMEM = "LPB-Konfig. 0";
const char STR6610[] PROGMEM = "Anzeige Systemmeldungen";
const char STR6612[] PROGMEM = "Alarmverzögerung";
const char STR6620[] PROGMEM = "Wirkbereich Umschaltungen";
const char STR6621[] PROGMEM = "Sommerumschaltung";
const char STR6623[] PROGMEM = "Betriebsartumschaltung";
const char STR6624[] PROGMEM = "Manuelle Erzeugersperre";
const char STR6625[] PROGMEM = "Trinkwasserzuordnung";
const char STR6627[] PROGMEM = "Kälteanforderung";
const char STR6632[] PROGMEM = "TA'grenze ext Erz beachten";
const char STR6640[] PROGMEM = "Uhrbetrieb";
const char STR6650[] PROGMEM = "Aussentemperatur Lieferant";
const char STR6705[] PROGMEM = "SW Diagnosecode";
const char STR6710[] PROGMEM = "Reset Alarmrelais";
const char STR6711[] PROGMEM = "Reset Wärmepumpe";
const char STR6740[] PROGMEM = "Vorlauftemperatur 1 Alarm";
const char STR6741[] PROGMEM = "Vorlauftemperatur 2 Alarm";
const char STR6743[] PROGMEM = "Kesseltemperatur Alarm";
const char STR6745[] PROGMEM = "Trinkwasserladung Alarm ";
const char STR6746[] PROGMEM = "Vorlauftemp Kühlen 1 Alarm ";
/* TODO Thision
const char STR6800[] PROGMEM = "Historie 1";
const char STR6805[] PROGMEM = "SW Diagnosecode 1";
const char STR6810[] PROGMEM = "Historie 2";
const char STR6815[] PROGMEM = "SW Diagnosecode 2";
*/
const char STR6800[] PROGMEM = "Historie 1 Datum/Zeit";
const char STR6801[] PROGMEM = "Historie 1 Fehlercode";
const char STR6802[] PROGMEM = "Historie 2 Datum/Zeit";
const char STR6803[] PROGMEM = "Historie 2 Fehlercode";
const char STR6804[] PROGMEM = "Historie 3 Datum/Zeit";
const char STR6805[] PROGMEM = "Historie 3 Fehlercode";
const char STR6806[] PROGMEM = "Historie 4 Datum/Zeit";
const char STR6807[] PROGMEM = "Historie 4 Fehlercode";
const char STR6808[] PROGMEM = "Historie 5 Datum/Zeit";
const char STR6809[] PROGMEM = "Historie 5 Fehlercode";
const char STR6810[] PROGMEM = "Historie 6 Datum/Zeit";
const char STR6811[] PROGMEM = "Historie 6 Fehlercode";
const char STR6812[] PROGMEM = "Historie 7 Datum/Zeit";
const char STR6813[] PROGMEM = "Historie 7 Fehlercode";
const char STR6814[] PROGMEM = "Historie 8 Datum/Zeit";
const char STR6815[] PROGMEM = "Historie 8 Fehlercode";
const char STR6816[] PROGMEM = "Historie 9 Datum/Zeit";
const char STR6817[] PROGMEM = "Historie 9 Fehlercode";
const char STR6818[] PROGMEM = "Historie 10 Datum/Zeit";
const char STR6819[] PROGMEM = "Historie 10 Fehlercode";
// TODO Thision different numbers
const char STR6820[] PROGMEM = "Historie 3";
const char STR6825[] PROGMEM = "SW Diagnosecode 3";
const char STR6830[] PROGMEM = "Historie 4";
const char STR6835[] PROGMEM = "SW Diagnosecode 4";
const char STR6840[] PROGMEM = "Historie 5";
const char STR6845[] PROGMEM = "SW Diagnosecode 5";

const char STR7001[] PROGMEM = "Meldung";
const char STR7007[] PROGMEM = "Anzeige Meldungen";
const char STR7010[] PROGMEM = "Quittierung Meldung";
const char STR7011[] PROGMEM = "Repetitionszeit Meldung";
const char STR7012[] PROGMEM = "Reset Meldungen 1-6";
const char STR7040[] PROGMEM = "Brennerstunden Intervall";
const char STR7041[] PROGMEM = "Brennerstunden seit Wartung";
const char STR7042[] PROGMEM = "Brennerstarts Intervall";
const char STR7043[] PROGMEM = "Brennerstarts seit Wartung";
const char STR7044[] PROGMEM = "Wartungsintervall";
const char STR7045[] PROGMEM = "Zeit seit Wartung";
const char STR7051[] PROGMEM = "Meldung Ion Strom";
const char STR7053[] PROGMEM = "Abgastemperaturgrenze ";
const char STR7054[] PROGMEM = "Verzögerung Abgasmeldung ";
const char STR7070[] PROGMEM = "WP Zeitintervall ";
const char STR7071[] PROGMEM = "WP Zeit seit Wartung ";
const char STR7072[] PROGMEM = "Max Starts Verd1 / Betr’Std ";
const char STR7073[] PROGMEM = "Akt Starts Verd1 / Betr’Std ";
const char STR7074[] PROGMEM = "Max Starts Verd2 / Betr’Std ";
const char STR7075[] PROGMEM = "Akt Starts Verd2 / Betr’Std ";
const char STR7076[] PROGMEM = "Spreiz Kondens Max / Wo";
const char STR7077[] PROGMEM = "Akt Spreiz Kondens Max / Wo";
const char STR7078[] PROGMEM = "Spreiz Kondens Min / Wo";
const char STR7079[] PROGMEM = "Akt Spreiz Kondens Min / Wo";
const char STR7080[] PROGMEM = "Spreiz Verdampfer Max / Wo";
const char STR7081[] PROGMEM = "Akt Spreiz Verdampfer Max / Wo";
const char STR7082[] PROGMEM = "Spreiz Verdampfer Min / Wo";
const char STR7083[] PROGMEM = "Akt Spreiz Verdampfer Min / Wo";
const char STR7090[] PROGMEM = "TWW Speicher Zeitintervall";
const char STR7091[] PROGMEM = "TWW Speicher seit Wartung";
const char STR7092[] PROGMEM = "TWW Ladetemp WP Minimum";
const char STR7093[] PROGMEM = "Akt TWW Ladetemperatur WP";
const char STR7119[] PROGMEM = "Ökofunktion";
const char STR7120[] PROGMEM = "Ökobetrieb";
const char STR7130[] PROGMEM = "Schornsteinfegerfunktion";
const char STR7140[] PROGMEM = "Handbetrieb";
const char STR7141[] PROGMEM = "Notbetrieb";
const char STR7142[] PROGMEM = "Notbetrieb Funktionsstart";
const char STR7143[] PROGMEM = "Reglerstoppfunktion";
const char STR7145[] PROGMEM = "Reglerstopp Sollwert";
const char STR7146[] PROGMEM = "Entlüftungsfunktion";
const char STR7150[] PROGMEM = "Simulation Aussentemperatur";
const char STR7152[] PROGMEM = "Abtauen auslösen";
const char STR7160[] PROGMEM = "Reset Begrenzungszeiten";
const char STR7170[] PROGMEM = "Telefon Kundendienst";
const char STR7700[] PROGMEM = "Relaistest";
const char STR7705[] PROGMEM = "Mod'sollwert QX3 Relaistest";
const char STR7708[] PROGMEM = "Modulationssignal QX3";
const char STR7710[] PROGMEM = "Ausgangstest UX";
const char STR7711[] PROGMEM = "Spannungssignal UX";
const char STR7714[] PROGMEM = "PWM-Signal P1";
const char STR7730[] PROGMEM = "Aussentemperatur B9";
const char STR7732[] PROGMEM = "Vorlauftemperatur B1";
const char STR7734[] PROGMEM = "Vorlauftemperatur B12";
const char STR7750[] PROGMEM = "Trinkwassertemperatur B3";
const char STR7760[] PROGMEM = "Kesseltemperatur B2";
const char STR7770[] PROGMEM = "Vorlauftemperatur WP B21";
const char STR7771[] PROGMEM = "Rücklauftemperatur WP B71";
const char STR7772[] PROGMEM = "Heissgastemperatur B81";
const char STR7775[] PROGMEM = "Quelle Eintrittstemp B91";
const char STR7777[] PROGMEM = "Fühlertemperatur B92, B84";
const char STR7820[] PROGMEM = "Fühlertemperatur BX1";
const char STR7821[] PROGMEM = "Fühlertemperatur BX2";
const char STR7822[] PROGMEM = "Fühlertemperatur BX3";
const char STR7823[] PROGMEM = "Fühlertemperatur BX4";
const char STR7824[] PROGMEM = "Fühlertemperatur BX5";
const char STR7830[] PROGMEM = "Fühlertemp. BX21 Modul 1";
const char STR7831[] PROGMEM = "Fühlertemp. BX22 Modul 1";
const char STR7832[] PROGMEM = "Fühlertemp. BX21 Modul 2";
const char STR7833[] PROGMEM = "Fühlertemp. BX22 Modul 2";
const char STR7840[] PROGMEM = "Spannungssignal H1";
const char STR7841[] PROGMEM = "Kontaktzustand H1";
const char STR7845[] PROGMEM = "Spannungssignal H2";
const char STR7846[] PROGMEM = "Kontaktzustand H2";
const char STR7854[] PROGMEM = "Spannungssignal H3";
const char STR7855[] PROGMEM = "Kontaktzustand H3";
const char STR7870[] PROGMEM = "Brennerstörung S3";
const char STR7881[] PROGMEM = "1. Brennerstufe E1";
const char STR7889[] PROGMEM = "Niederdruckwächter E9";
const char STR7890[] PROGMEM = "Hochdruckwächter E10";
const char STR7891[] PROGMEM = "Wickl’schutz Verdicht 1 E11";
const char STR7911[] PROGMEM = "Eingang EX 1";
const char STR7912[] PROGMEM = "Eingang EX2";
const char STR7913[] PROGMEM = "Eingang EX 3";
const char STR7914[] PROGMEM = "Eingang EX 4";
const char STR7915[] PROGMEM = "Eingang EX 5";
const char STR7916[] PROGMEM = "Eingang EX 6";
const char STR7917[] PROGMEM = "Eingang EX 7";
const char STR8000[] PROGMEM = "Status Heizkreis 1";
const char STR8001[] PROGMEM = "Status Heizkreis 2";
const char STR8002[] PROGMEM = "Status Heizkreis P";
const char STR8003[] PROGMEM = "Status Trinkwasser";
const char STR8004[] PROGMEM = "Status Kühlkreis 1";
const char STR8005[] PROGMEM = "Status Kessel";
const char STR8006[] PROGMEM = "Status Wärmepumpe";
const char STR8007[] PROGMEM = "Status Solar";
const char STR8008[] PROGMEM = "Status Feststoffkessel";
const char STR8010[] PROGMEM = "Status Pufferspeicher";
const char STR8011[] PROGMEM = "Status Schwimmbad";
const char STR8022[] PROGMEM = "Status Zusatzerzeuger";
const char STR8050[] PROGMEM = "Zeitstemper Statushistorie 1";
const char STR8051[] PROGMEM = "Statuscode Statushistorie 1";
const char STR8052[] PROGMEM = "Zeitstemper Statushistorie 2";
const char STR8053[] PROGMEM = "Statuscode Statushistorie 2";
const char STR8054[] PROGMEM = "Zeitstemper Statushistorie 3";
const char STR8055[] PROGMEM = "Statuscode Statushistorie 3";
const char STR8056[] PROGMEM = "Zeitstemper Statushistorie 4";
const char STR8057[] PROGMEM = "Statuscode Statushistorie 4";
const char STR8058[] PROGMEM = "Zeitstemper Statushistorie 5";
const char STR8059[] PROGMEM = "Statuscode Statushistorie 5";
const char STR8060[] PROGMEM = "Zeitstemper Statushistorie 6";
const char STR8061[] PROGMEM = "Statuscode Statushistorie 6";
const char STR8062[] PROGMEM = "Zeitstemper Statushistorie 7";
const char STR8063[] PROGMEM = "Statuscode Statushistorie 7";
const char STR8064[] PROGMEM = "Zeitstemper Statushistorie 8 ";
const char STR8065[] PROGMEM = "Statuscode Statushistorie 8 ";
const char STR8066[] PROGMEM = "Zeitstemper Statushistorie 9 ";
const char STR8067[] PROGMEM = "Statuscode Statushistorie 10 ";
const char STR8068[] PROGMEM = "Zeitstemper Statushistorie 10 ";
const char STR8069[] PROGMEM = "Statuscode Statushistorie 10 ";
const char STR8100[] PROGMEM = "Priorität / Status Erzeuger 1 ";
const char STR8102[] PROGMEM = "Priorität / Status Erzeuger 2 ";
const char STR8104[] PROGMEM = "Priorität / Status Erzeuger 3 ";
const char STR8106[] PROGMEM = "Priorität / Status Erzeuger 4 ";
const char STR8108[] PROGMEM = "Priorität / Status Erzeuger 5 ";
const char STR8110[] PROGMEM = "Priorität / Status Erzeuger 6 ";
const char STR8112[] PROGMEM = "Priorität / Status Erzeuger 7 ";
const char STR8114[] PROGMEM = "Priorität / Status Erzeuger 8 ";
const char STR8116[] PROGMEM = "Priorität / Status Erzeuger 9 ";
const char STR8118[] PROGMEM = "Priorität / Status Erzeuger 10 ";
const char STR8120[] PROGMEM = "Priorität / Status Erzeuger 11 ";
const char STR8122[] PROGMEM = "Priorität / Status Erzeuger 12 ";
const char STR8124[] PROGMEM = "Priorität / Status Erzeuger 13 ";
const char STR8126[] PROGMEM = "Priorität / Status Erzeuger 14 ";
const char STR8128[] PROGMEM = "Priorität / Status Erzeuger 15 ";
const char STR8130[] PROGMEM = "Priorität / Status Erzeuger 16 ";
const char STR8138[] PROGMEM = "Kaskadenvorlauftemperatur ";
const char STR8139[] PROGMEM = "Kaskadenvorlaufsollwert ";
const char STR8140[] PROGMEM = "Kaskadenrücklauftemperatur ";
const char STR8141[] PROGMEM = "Kaskadenrücklaufsollwert ";
const char STR8150[] PROGMEM = "Erz'folge Umschalt aktuell ";
const char STR8300[] PROGMEM = "1. Brennerstufe T2";
const char STR8301[] PROGMEM = "2. Brennerstufe T8";
const char STR8308[] PROGMEM = "Drehzahl Kesselpumpe ";
const char STR8310[] PROGMEM = "Kesseltemperatur";
const char STR8311[] PROGMEM = "Kesselsollwert";
const char STR8312[] PROGMEM = "Kesselschaltpunkt ";
const char STR8314[] PROGMEM = "Kesselrücklauftemperatur";
const char STR8315[] PROGMEM = "Kesselrücklaufsollwert ";
const char STR8316[] PROGMEM = "Abgastemperatur";
const char STR8318[] PROGMEM = "Abgastemperatur Maximum";
const char STR8324[] PROGMEM = "Gebläsedrehzahl";
const char STR8326[] PROGMEM = "Brennermodulation ";
const char STR8327[] PROGMEM = "Wasserdruck";
const char STR8328[] PROGMEM = "Betriebsanzeige FA";
const char STR8329[] PROGMEM = "Ionisationsstrom";
const char STR8330[] PROGMEM = "Betriebsstunden 1.Stufe";
const char STR8331[] PROGMEM = "Startzähler 1.Stufe";
const char STR8332[] PROGMEM = "Betriebsstunden 2.Stufe";
const char STR8333[] PROGMEM = "Startzähler 2.Stufe";
const char STR8336[] PROGMEM = "Betriebsstunden Brenner";
const char STR8337[] PROGMEM = "Startzähler Brenner";
const char STR8338[] PROGMEM = "Betriebsstunden Heizbetrieb";
const char STR8339[] PROGMEM = "Betriebsstunden TWW";
const char STR8340[] PROGMEM = "Betriebsstunden Zonen";
const char STR8400[] PROGMEM = "Verdichter 1 K1";
const char STR8401[] PROGMEM = "Verdichter 2 K2";
const char STR8402[] PROGMEM = "Elektroeinsatz 1 Vorlauf";
const char STR8403[] PROGMEM = "Elektroeinsatz 2 Vorlauf";
const char STR8404[] PROGMEM = "Quellenpu Q8 / Ventilat K19";
const char STR8405[] PROGMEM = "Drehzahl Quellenpumpe";
const char STR8406[] PROGMEM = "Konendastorpumpe Q9";
const char STR8410[] PROGMEM = "Rücklauftemperatur WP";
const char STR8411[] PROGMEM = "Sollwert WP";
const char STR8412[] PROGMEM = "Vorlauftemperatur WP";
const char STR8415[] PROGMEM = "Heissgastemperatur 1";
const char STR8416[] PROGMEM = "Heissgastemperatur Max";
const char STR8417[] PROGMEM = "Heissgastemperatur 2";
const char STR8420[] PROGMEM = "Kältemitteltemperatur flüssig";
const char STR8425[] PROGMEM = "Temp’spreizung Kondensator";
const char STR8426[] PROGMEM = "Temp’spreizung Verdampfer";
const char STR8427[] PROGMEM = "Quelle Eintrittstemperatur";
const char STR8428[] PROGMEM = "Quelle Eintritt Min";
const char STR8429[] PROGMEM = "Quelle Austrittstemperatur";
const char STR8430[] PROGMEM = "Quelle Austritt Min";
const char STR8440[] PROGMEM = "Rest Stufe 1 Stillst’zeit Min";
const char STR8441[] PROGMEM = "Rest Stufe 2 Stillst’zeit Min";
const char STR8442[] PROGMEM = "Rest Stufe 1 Laufzeit Min";
const char STR8443[] PROGMEM = "Rest Stufe 2 Laufzeit Min";
const char STR8444[] PROGMEM = "Restzeit Begr Quelle TempMin";
const char STR8446[] PROGMEM = "Verdichterfolge";
const char STR8450[] PROGMEM = "Betr’stunden Verdichter 1";
const char STR8451[] PROGMEM = "Startzähler Verdichter 1";
const char STR8452[] PROGMEM = "Betr’stunden Verdichter 2";
const char STR8453[] PROGMEM = "Startzähler Verdichter 2";
const char STR8454[] PROGMEM = "Sperrdauer WP";
const char STR8455[] PROGMEM = "Zähler Anzahl Sperren WP";
const char STR8456[] PROGMEM = "Betr’stunden Elektro Vorl";
const char STR8457[] PROGMEM = "Startzähler Elektro Vorlauf";
const char STR8469[] PROGMEM = "Drehzahl Ventilator";
const char STR8470[] PROGMEM = "Ventilator K19";
const char STR8471[] PROGMEM = "Prozessumkehrventil";
const char STR8475[] PROGMEM = "Verdampfertemperatur";
const char STR8477[] PROGMEM = "Temp'diff Abtauen Istwert";
const char STR8478[] PROGMEM = "Temp'diff Abtauen Sollwert";
const char STR8480[] PROGMEM = "Restzeit Abtausperrung";
const char STR8481[] PROGMEM = "Restzeit Zwangsabtauen";
const char STR8482[] PROGMEM = "Restzeit Abtaustabilisierung";
const char STR8485[] PROGMEM = "Anzahl Abtauversuche";
const char STR8487[] PROGMEM = "Status Abtauen WP";
const char STR8505[] PROGMEM = "Drehzahl Kollektorpumpe 1";
const char STR8506[] PROGMEM = "Drehzahl Solarpump ext.Tau ";
const char STR8507[] PROGMEM = "Drehzahl Solarpumpe Puffer ";
const char STR8508[] PROGMEM = "Drehzahl Solarpump Sch'bad ";
const char STR8510[] PROGMEM = "Kollektortemperatur 1";
const char STR8511[] PROGMEM = "Kollektortemperatur 1 Max";
const char STR8512[] PROGMEM = "Kollektortemperatur 1 Min";
const char STR8513[] PROGMEM = "dT Kollektor 1/TWW";
const char STR8514[] PROGMEM = "dt Kollektor 1/Puffer";
const char STR8515[] PROGMEM = "dT Kollektor 1 / Schwimmbad ";
const char STR8519[] PROGMEM = "Solarvorlauftemperatur ";
const char STR8520[] PROGMEM = "Solarrücklauftemperatur ";
const char STR8526[] PROGMEM = "Tagesertrag Solarenergie ";
const char STR8527[] PROGMEM = "Gesamtertrag Solarenergie ";
const char STR8530[] PROGMEM = "Betr`stunden Solarertrag";
const char STR8531[] PROGMEM = "Betr`stunden Kollektor`überhitz";
const char STR8543[] PROGMEM = "Drehzahl Kollektorpumpe 2 ";
const char STR8547[] PROGMEM = "Kollektortemperatur 2 ";
const char STR8548[] PROGMEM = "Kollektortemperatur 2 Max ";
const char STR8549[] PROGMEM = "Kollektortemperatur 2 Min ";
const char STR8550[] PROGMEM = "dT Kollektor 2 / TWW ";
const char STR8551[] PROGMEM = "dT Kollektor 2 / Puffer ";
const char STR8552[] PROGMEM = "dT Kollektor 2 / Schwimmbad ";
const char STR8560[] PROGMEM = "Feststoffkesseltemperatur";
const char STR8570[] PROGMEM = "Betr'std Feststoffkessel ";
const char STR8700[] PROGMEM = "Aussentemperatur";
const char STR8701[] PROGMEM = "Außentemperatur Minimum";
const char STR8702[] PROGMEM = "Außentemperatur Maximum";
const char STR8703[] PROGMEM = "Aussentemperatur gedämpft";
const char STR8704[] PROGMEM = "Aussentemperatur gemischt";
const char STR8720[] PROGMEM = "Relative Raumfeuchte";
const char STR8721[] PROGMEM = "Raumtemperatur";
const char STR8722[] PROGMEM = "Taupunkttemperatur";
const char STR8730[] PROGMEM = "Heizkreispumpe Q2";
const char STR8731[] PROGMEM = "Heizkreismischer Auf Y1";
const char STR8732[] PROGMEM = "Heizkreismischer Zu Y2";
const char STR8735[] PROGMEM = "Drehzahl Heizkreispumpe 1";
const char STR8740[] PROGMEM = "Raumtemperatur 1";
const char STR8741[] PROGMEM = "Raumsollwert 1";
const char STR8742[] PROGMEM = "Raumtemperatur 1 Modell";
const char STR8743[] PROGMEM = "Vorlauftemperatur 1";
const char STR8744[] PROGMEM = "Vorlaufsollwert 1";
const char STR8750[] PROGMEM = "Mod Pumpe Sollwert";
const char STR8751[] PROGMEM = "Kühlkreispumpe Q24";
const char STR8752[] PROGMEM = "Kühlkreismischer Auf Y23";
const char STR8753[] PROGMEM = "Kühlkreismischer Zu Y24";
const char STR8754[] PROGMEM = "Umlenkventil Kühlen Y21";
const char STR8756[] PROGMEM = "Vorlauftemperatur Kühlen 1";
const char STR8757[] PROGMEM = "Vorlaufsollwert Kühlen1";
const char STR8760[] PROGMEM = "Heizkreispumpe 2";
const char STR8761[] PROGMEM = "Heizkreismischer 2 Auf";
const char STR8762[] PROGMEM = "Heizkreismischer 2 Zu";
const char STR8765[] PROGMEM = "Drehzahl Heizkreispumpe 2";
const char STR8770[] PROGMEM = "Raumtemperatur 2";
const char STR8771[] PROGMEM = "Raumsollwert 2";
const char STR8772[] PROGMEM = "Raumtemperatur 2 Modell";
const char STR8773[] PROGMEM = "Vorlauftemperatur 2";
const char STR8774[] PROGMEM = "Vorlaufsollwert 2";
const char STR8795[] PROGMEM = " Drehzahl Heizkreispumpe P";
const char STR8800[] PROGMEM = "Raumtemperatur P";
const char STR8801[] PROGMEM = "Raumsollwert P";
const char STR8803[] PROGMEM = "Vorlaufsollwert P";
const char STR8820[] PROGMEM = "Trinkwasserpumpe Q3";
const char STR8821[] PROGMEM = "Elektroeinsatz TWW K6";
const char STR8825[] PROGMEM = "Drehzahl Trinkwasserpumpe";
const char STR8826[] PROGMEM = "Drehzahl TWW Zw'kreispumpe";
const char STR8827[] PROGMEM = "Drehzahl Dl'erhitzerpumpe";
const char STR8830[] PROGMEM = "Trinkwassertemperatur 1";
const char STR8831[] PROGMEM = "Trinkwassersollwert";
const char STR8832[] PROGMEM = "Trinkwassertemperatur 2";
const char STR8835[] PROGMEM = "TWW Zirkulationstemperatur";
const char STR8836[] PROGMEM = "TWW Ladetemperatur";
const char STR8840[] PROGMEM = "Betr’stunden TWW-Pumpe";
const char STR8841[] PROGMEM = "Startzähler TWW-Pumpe";
const char STR8842[] PROGMEM = "Betr’stunden Elektro TWW";
const char STR8843[] PROGMEM = "Startzähler Elektro TWW";
const char STR8850[] PROGMEM = "TWW Vorreglertemperatur";
const char STR8851[] PROGMEM = "TWW Vorreglersollwert";
const char STR8852[] PROGMEM = "TWW Durchl'erhitzertemp";
const char STR8853[] PROGMEM = "TWW Durchl'erhitzersollwert";
const char STR8900[] PROGMEM = "Schwimmbadtemperatur";
const char STR8901[] PROGMEM = "Schwimmbadsollwert";
const char STR8930[] PROGMEM = "Vorreglertemperatur";
const char STR8931[] PROGMEM = "Vorreglersollwert";
const char STR8950[] PROGMEM = "Schienenvorlauftemperatur";
const char STR8951[] PROGMEM = "Schienenvorlaufsollwert";
const char STR8952[] PROGMEM = "Schienenrücklauftemperatur";
const char STR8957[] PROGMEM = "Schienenvorl'sollwert Kälte";
const char STR8962[] PROGMEM = "Leistungssollwert Schiene";
const char STR8970[] PROGMEM = "Elektroeinsatz Puffer";
const char STR8980[] PROGMEM = "Pufferspeichertemperatur 1";
const char STR8981[] PROGMEM = "Pufferspeichersollwert";
const char STR8982[] PROGMEM = "Pufferspeichertemperatur 2";
const char STR8983[] PROGMEM = "Pufferspeichertemperatur 3";
const char STR8990[] PROGMEM = "Betr’stunden Elektro Puffer";
const char STR8991[] PROGMEM = "Startzähler Elektro Puffer";
const char STR9000[] PROGMEM = "Vorlaufsollwert H1";
const char STR9001[] PROGMEM = "Vorlaufsollwert H2";
const char STR9004[] PROGMEM = "Vorlaufsollwert H3";
const char STR9005[] PROGMEM = "Wasserdruck H1";
const char STR9006[] PROGMEM = "Wasserdruck H2";
const char STR9009[] PROGMEM = "Wasserdruck H3";
const char STR9031[] PROGMEM = "Relaisausgang QX1";
const char STR9032[] PROGMEM = "Relaisausgang QX2";
const char STR9033[] PROGMEM = "Relaisausgang QX3";
const char STR9034[] PROGMEM = "Relaisausgang QX4";
const char STR9035[] PROGMEM = "Relaisausgang QX5";
const char STR9036[] PROGMEM = "Relaisausgang QX6";
const char STR9037[] PROGMEM = "Relaisausgang QX7";
const char STR9038[] PROGMEM = "Relaisausgang QX8";
const char STR9050[] PROGMEM = "Relaisausgang QX21 Modul 1";
const char STR9051[] PROGMEM = "Relaisausgang QX22 Modul 1";
const char STR9052[] PROGMEM = "Relaisausgang QX23 Modul 1";
const char STR9053[] PROGMEM = "Relaisausgang QX21 Modul 2";
const char STR9054[] PROGMEM = "Relaisausgang QX22 Modul 2";
const char STR9055[] PROGMEM = "Relaisausgang QX23 Modul 2";
const char STR9500[] PROGMEM = "Vorlüftzeit";
const char STR9502[] PROGMEM = "Gebl'ansteuerung Vorlüftung";
const char STR9504[] PROGMEM = "Solldrehzahl Vorlüftung";
const char STR9510[] PROGMEM = "Gebl'ansteuerung Zündung";
const char STR9512[] PROGMEM = "Solldrehzahl Zündung";
const char STR9520[] PROGMEM = "Gebl'ansteuerung Betrieb. Min";
const char STR9522[] PROGMEM = "Gebl'ansteuerung Betrieb. Max";
const char STR9524[] PROGMEM = "Solldrehzahl Betrieb Min";
const char STR9527[] PROGMEM = "Solldrehzahl Betrieb Max";
const char STR9540[] PROGMEM = "Nachlüftzeit";
const char STR9550[] PROGMEM = "Gebl'ansteuerung Stillstand";
const char STR9560[] PROGMEM = "Gebl'ansteuerung Durchlad";
const char STR9563[] PROGMEM = "Solldrehzahl Durchlasung";

const char STR10000[] PROGMEM = "Raumtemperatur 1";



/* ENUM tables */
/*
const char ENUM648[] PROGMEM = {"\x00 Frostschutz\0\x01 Reduziert"};
#define ENUM658 ENUM648
#define ENUM668 ENUM648
*/
const char ENUM648[] PROGMEM = {"\x00 Frostschutz\0\x01 Reduziert"};
#define ENUM665 ENUM648
#define ENUM682 ENUM648

const char ENUM700[] PROGMEM = {"\x00 Schutzbetrieb\0\x01 Automatik\0\x02 Reduziert\0\x03 Komfort"};

const char ENUM780[] PROGMEM = {"\x00 Aus\0\x01 Bis Reduziertsollwert\0\x02 Bis Frostschutzsollwert"};
const char ENUM850[] PROGMEM = {"\x00 Aus\0\x01 Funktionsheizen\0\x02 Belegreifheizen\0\x03 Funktions-/Belegreifheizen\0\x04 Beleg-/Funktionsheizen\0\x05 Manuell"};
const char ENUM861[] PROGMEM = {"\x00 Aus\0\x01 Heizbetrieb\0\x02 Immer"};
const char ENUM900[] PROGMEM = {"\x00 Keine\0\x01 Schutzbetrieb\0\x02 Reduziert\0\x03 Komfort\0\x04 Automatik"};

#define ENUM1080 ENUM780
#define ENUM1150 ENUM850
#define ENUM1161 ENUM861
#define ENUM1200 ENUM900
const char ENUM1620[] PROGMEM = {"\x00 24h/Tag\0\x01 Zeitprogramme Heizkreise\0\x02 Zeitprogramm 4/TWW"};
const char ENUM1630[] PROGMEM = {"\x00 Absolut\0\x01 Gleitend\0\x02 Kein\0\x03 MK gleitend PK absolut\0\x04 Aus"};
const char ENUM1640[] PROGMEM = {"\x00 Aus\0\x01 Periodisch\0\x02 Fixer Wochentag"};
const char ENUM1660[] PROGMEM = {"\x01 Zeitprogramm 3/HKP\0\x02 Trinkwasser Freigabe\0\x03 Zeitprogramm 4/TWW\0\x04 Zeitprogramm 5"};
const char ENUM5022[] PROGMEM = {"\x01 Mit B3\0\x02 Mit B3/B31\0\x03 Mit B3, Legio B3/31"};
const char ENUM5057[] PROGMEM = {"\x00 Aus\0\x01 Sommer\0\x02 Immer"};
const char ENUM5060[] PROGMEM = {"\x01 Ersatz\0\x02 Sommer\0\x03 Immer"};
const char ENUM5061[] PROGMEM = {"\x01 24H/Tag\0\x02 Trinkwasser Freigabe\0\x03 Zeitprogramm 4/TWW"};
const char ENUM5062[] PROGMEM = {"\x01 Externer Thermostat\0\x02 Trinkwasserfühler"};
const char ENUM5730[] PROGMEM = {"\x00 Fühler\0\x01 Thermostat"};
const char ENUM5731[] PROGMEM = {"\x00 kein\0\x01 Ladepumpe\0\x02 Umlenkventil"};

const char ENUM5890[] PROGMEM = {
"\x00 Kein\0"
"\x01 Zirkulationspumpe Q4\0"
"\x02 Elektroeinsatz TWW K6\0"
"\x03 Kollektorpumpe Q5\0"
"\x04 H1-Pumpe Q15\0"
"\x05 Kesselpumpe Q1\0"
"\x06 Bypasspumpe Q12\0"
"\x07 Alarmausgang K10\0"
"\x08 2.Pumpenstufe HK1 Q21\0"
"\x09 2.Pumpenstufe HK2 Q22\0"
"\x0a 2.Pumpenstufe HKP Q32\0"
"\x0b Heizkreispumpe HKP Q20\0"
"\x0c H2-Pumpe Q18\0"
"\x0d Zubringerpumpe Q14\0"
"\x0e Erzeugersperrventil Y4\0"
"\x0f Feststoffkesselpumpe Q10\0"
"\x10 Zeitprogramm 5 K13\0"
"\x11 Pufferrücklaufventil Y15\0"
"\x12 Solarpumpe ext. Tauscher K9\0"
"\x13 Solarstellglied Puffer K8\0"
"\x14 Solarstellglied Schw'bad K18\0"
"\x15 Kollektorpumpe 2 Q16\0"
"\x16 H3-Pumpe Q19\0"
"\x17 Abgasrelais K17\0"
"\x19 Kaskadenpumpe Q25\0"
"\x1a Speicherumladepumpe Q11\0"
"\x1b TWW Durchmischpumpe Q35\0"
"\x1c TWW Zwisch'kreispumpe Q33\0"
"\x1d Wärmeanforderung K27"};


#define ENUM5891 ENUM5890
#define ENUM5892 ENUM5890

const char ENUM5922[] PROGMEM = {
"\x00 Default, Keine Funktion\0"
"\x01 Meldeausgang\0"
"\x02 Alarmausgang\0"
"\x03 Betriebsmeldung\0"
"\x04 Externer Trafo\0"
"\x05 Heizkreispumpe HK2 (Q2Y2)\0"
"\x06 Zirkulationspumpe\0"
"\x07 Torschleierfunktion\0"
"\x08 Pumpe Hydraulische Weiche\0"
"\x09 Zubringerpumpe Q8\0"
"\x0a Grundfunktion K2\0"
"\x0b Trinkwasserdurchladung\0"
"\x0c Schwelle Analogsignal\0"
"\x0d Abgasklappe\0"
"\x0e Kollektorpumpe\0"
"\x0f Gebläseabschaltung\0"
"\x10 Pumpe Q1\0"
"\x11 TWW Durchmischpumpe Q35"
};
#define ENUM5923 ENUM5922
#define ENUM5924 ENUM5922
#define ENUM5926 ENUM5922
#define ENUM5927 ENUM5922
#define ENUM5928 ENUM5922

const char ENUM5930[] PROGMEM = {
"\x00 Kein\0"
"\x01 Trinkwasserfühler B31\0"
"\x02 Kollektorfühler B6\0"
"\x04 TWW Zirkulationsfühler B39\0"
"\x05 Pufferspeicherfühler B4\0"
"\x06 Pufferspeicherfühler B41\0"
"\x07 Abgastemperaturfühler B8\0"
"\x08 Schienenvorlauffühler B10\0"
"\x09 Feststoffkesselfühler B22\0"
"\x0a TWW Ladefühler B36\0"
"\x0b Pufferspeicherfühler B42\0"
"\x0c Schienenrücklauffühler B73\0"
"\x0d Kaskadenrücklauffühler B70\0"
"\x0e Schwimmbadfühler B13\0"
"\x0f Kollektorfühler 2 B61\0"
"\x10 Solarvorlauffühler B63\0"
"\x11 Solarrücklauffühler B64"};

#define ENUM5931 ENUM5930
#define ENUM5932 ENUM5930
#define ENUM5933 ENUM5930

const char ENUM5950[] PROGMEM = {
"\x01 BA-Umschaltung HK's + TWW\0"
"\x02 BA-Umschaltung HK's\0"
"\x03 BA-Umschaltung HK1\0"
"\x04 BA-Umschaltung HK2\0"
"\x05 BA-Umschaltung HKP\0"
"\x06 Erzeugersperre\0"
"\x07 Fehler- / Alarmmeldung\0"
"\x08 Minimaler Vorlaufsollwert\0"
"\x09 Übertemperaturableitung\0"
"\x0a Freigabe Schwimmbad\0"
"\x0d Wärmeanforderung 10V\0"
"\x0e Druckmessung 10V"};

const char ENUM5951[] PROGMEM = {"\x00 Ruhekontakt\0\x01 Arbeitskontakt"};

const char ENUM5957[] PROGMEM = {
"\x01 in alle Heizkreisen und Trinkwasser\0"
"\x02 in alle Heizkreisen\0"
"\x03 in Heizkreis 1\0"
"\x04 in Heizkreis 2"
};

#define ENUM5960 ENUM5950
#define ENUM5961 ENUM5951
const char ENUM5982[] PROGMEM = {
"\x01 Zähler 2.Brennerstufe\0"
"\x02 Erzeugersperre\0"
"\x03 Fehler- / Alarmmeldung\0"
"\x04 STB Fehlermeldung\0"
"\x05 Übertemperaturableitung"};

const char ENUM5970[] PROGMEM = {
"\x00 Kein\0"
"\x01 Raumthermostat\0"
"\x02 Schaltuhr Raumniveau\0"
"\x03 Schaltuhr Heizungsanforderung\0"
"\x04 Schaltuhr TWW Niveau"
};
#define ENUM5971 ENUM5970

const char ENUM5973[] PROGMEM = {
"\x00 Keine Funktion\0"
"\x01 Modemfunktion\0"
"\x02 Modemfunktion invers\0"
"\x03 Torschleierfunktion\0"
"\x04 Sollwertvorgabe\0"
"\x05 Leistungsvorgabe\0"
"\x06 Fühler hydraulische Weiche\0"
"\x07 Rückmeldung AbgKlp\0"
"\x08 Erzeugersperre\0"
"\x09 Erzeugersperre invers\0"
"\x0b Erzeugersperre Fühler"
};

const char ENUM5978[] PROGMEM = {
"\x00 kein\0"
"\x0a Kollektor Fühler"
};

#define ENUM5983 ENUM5951

const char ENUM6014[] PROGMEM = {
"\x01 Heizkreis 1\0"
"\x03 Vorregler / Zubringerpumpe\0"
"\x04 Trinkwasser Vorregler\0"
"\x05 Trinkwasser Durchl'erhitzer\0"
"\x06 Rücklaufregler Kaskade"};

const char ENUM6020[] PROGMEM = {
"\x00 Keine Funktion\0"
"\x01 Multifunktional\0"
"\x02 Heizkreis 2\0"
"\x03 Rücklaufregler\0"
"\x04 Solar Trinkwasser\0"
"\x05 Vorregler / Zubringerpumpe\0"
"\x06 Trinkwasser Vorregler\0"
"\x07 Trinkwasser Durchl'erhitzer\0"
"\x08 Rücklaufregler Kaskade"};

#define ENUM6021 ENUM6020

const char ENUM6604[] PROGMEM = {
"\x00 Aus\0"
"\x01 Automatisch"
};

const char ENUM6620[] PROGMEM = {
"\x00 Segment\0"
"\x01 System"
};

const char ENUM6621[] PROGMEM = {
"\x00 Lokal\0"
"\x01 Zentral"
};

const char ENUM6625[] PROGMEM = {
"\x00 Lokale Heizkreise\0"
"\x01 Alle Heizkreise im Segment\0"
"\x02 Alle Heizkreise im System"
};

const char ENUM6640[] PROGMEM = {
"\x00 Autonom\0"
"\x01 Slave ohne Fernverstellung\0"
"\x02 Slave mit Fernverstellung\0"
"\x03 Master"
};

const char ENUM7700[] PROGMEM = {
"\x00 Kein Test\0"
"\x01 Alles aus\0"
"\x02 ---\0"
"\x03 ---\0"
"\x04 Trinkwasserpumpe Q3\0"
"\x05 Heizkreispumpe Q2\0"
"\x06 Heizkreismischer Auf Y1\0"
"\x07 Heizkreismischer Zu Y2\0"
"\x08 Heizkreispumpe Q6\0"
"\x09 Heizkreismischer Auf Y5\0"
"\x0a Heizkreismischer Zu Y6\0"
"\x0b Relaisausgang QX1\0"
"\x0c Relaisausgang QX2\0"
"\x0d Relaisausgang QX3\0"
"\x0e Relaisausgang QX4\0"
"\x0f Relaisausgang QX21 Modul 1\0"
"\x10 Relaisausgang QX22 Modul 1\0"
"\x11 Relaisausgang QX23 Modul 1\0"
"\x12 Relaisausgang QX21 Modul 2\0"
"\x13 Relaisausgang QX22 Modul 2\0"
"\x14 Relaisausgang QX23 Modul 2"
};

//Status Heizkreis
const char ENUM8000[] PROGMEM = {
"\x00 ---\0"
"\x03 Wächter angesprochen\0"
"\x04 Handbetrieb aktiv\0"
"\x11 Nachlauf aktiv\0"
"\x16 Anlagenfrostschutz aktiv\0"
"\x17 Frostschutz aktiv\0"
"\x18 Aus\0"
"\x38 Überhitzschutz aktiv\0"
"\x65 Raumfrostschutz aktiv\0"
"\x66 Estrichfunktion aktiv\0"
"\x67 Eingeschränkt, Kesselschutz\0"
"\x68 Eingeschränkt, TWW-Vorrang\0"
"\x69 Eingeschränkt, Puffer\0"
"\x6a Heizbetrieb eingeschränkt\0"
"\x6b Zwangsabnahme Puffer\0"
"\x6c Zwangsabnahme TWW\0"
"\x6d Zwangsabnahme Erzeuger\0"
"\x6e Zwangsabnahme\0"
"\x6f Einschaltopt + Schnellaufheiz\0"
"\x70 Einschaltoptimierung\0"
"\x71 Schnellaufheizung\0"
"\x72 Heizbetrieb Komfort\0"
"\x73 Ausschaltoptimierung\0"
"\x74 Heizbetrieb Reduziert\0"
"\x75 Vorlauffrostschutz aktiv\0"
"\x76 Sommerbetrieb\0"
"\x77 Tages-Eco aktiv\0"
"\x78 Absenkung Reduziert\0"
"\x79 Absenkung Frostschutz\0"
"\x7a Raumtemp’begrenzung"};

#define ENUM8001 ENUM8000
#define ENUM8002 ENUM8000


//Status Trinkwasser
const char ENUM8003[] PROGMEM = {
"\x00 ---\0"
"\x03 Wächter angesprochen\0"
"\x04 Handbetrieb aktiv\0"
"\x11 Nachlauf aktiv\0"
"\x18 Frostschutz aktiv\0"
"\x19 Aus\0"
"\x35 Rückkühlung aktiv\0"
"\x42 Ladung Elektroeinsatz\0"
"\x43 Zwangsladung aktiv\0"
"\x45 Ladung aktiv\0"
"\x46 Geladen, Max Speichertemp\0"
"\x47 Geladen, Max Ladetemp\0"
"\x4b Geladen\0"
"\x4d Rückkühlung via Kollektor\0"
"\x4e Rückkühlung via Erz / Hk's\0"
"\x4f Entladeschutz aktiv\0"
"\x50 Ladezeitbegrenzung aktiv\0"
"\x51 Ladung gesperrt\0"
"\x52 Ladesperre aktiv\0"
"\x53 Zwang, Max Speichertemp\0"
"\x54 Zwang, Max Ladetemperatur\0"
"\x55 Zwang, Legionellensollwert\0"
"\x56 Zwang, Nennsollwert\0"
"\x57 Ladung Elektro, Leg’sollwert\0"
"\x58 Ladung Elektro, Nennsollwert\0"
"\x59 Ladung Elektro, Red’sollwert\0"
"\x5a Ladung Elektro, Fros’sollwert\0"
"\x5b Elektroeinsatz freigegeben\0"
"\x5c Push, Legionellensollwert\0"
"\x5d Push, Nennsollwert\0"
"\x5e Push aktiv\0"
"\x5f Ladung, Legionellensollwert\0"
"\x60 Ladung, Nennsollwert\0"
"\x61 Ladung, Reduziertsollwert\0"
"\x62 Geladen, Legio’temperatur\0"
"\x63 Geladen, Nenntemperatur\0"
"\x64 Geladen, Reduz’temperatur\0"
"\xc7 Zapfbetrieb\0"
"\xc8 Bereit\0"
"\xc9 Bereitschaftsladung"
};

//Status Kessel
const char ENUM8005[] PROGMEM = {
"\x00 ---\0"
"\x01 STB angesprochen\0"
"\x02 Störung\0"
"\x03 Wächter angesprochen\0"
"\x04 Handbetrieb aktiv\0"
"\x05 Schornsteinfegerfkt, Vollast\0"
"\x06 Schornsteinfegerfkt, Teillast\0"
"\x07 Schornsteinfegerfkt aktiv\0"
"\x08 Gesperrt, Manuell\0"
"\x09 Gesperrt, Automatisch\0"
"\x0a Gesperrt\0"
"\x0b Anfahrentlastung\0"
"\x0c Anfahrentlastung, Teillast\0"
"\x0d Rückl’begrenzung\0"
"\x0e Rückl’begrenzung, Teillast\0"
"\x11 Nachlauf aktiv\0"
"\x12 In Betrieb\0"
"\x13 Freigegeben\0"
"\x14 Minimalbegrenzung\0"
"\x15 Minimalbegrenzung, Teillast\0"
"\x16 Minimalbegrenzung aktiv\0"
"\x17 Anlagenfrostschutz aktiv\0"
"\x18 Frostschutz aktiv\0"
"\x19 Aus\0"
"\x3b Ladung Pufferspeicher\0"
"\x7b STB Test aktiv\0"
"\xa6 In Betrieb für Heizkreis\0"
"\xa7 In Teillastbetrieb für HK\0"
"\xa8 In Betrieb für Trinkwasser\0"
"\xa9 In Teillastbetrieb für TWW\0"
"\xaa In Betrieb für HK, TWW\0"
"\xab In Teillastbetrieb für HK, TWW\0"
"\xac Gesperrt, Feststoffkessel\0"
"\xad Freigegeben für HK, TWW\0"
"\xae Freigeben für TWW\0"
"\xaf Freigegeben für HK\0"
"\xb0 Gesperrt, Außentemperatur\0"
"\xc6 Gesperrt, Ökobetrieb"};

//Status Solar
const char ENUM8007[] PROGMEM = {
"\x00 ---\0"
"\x04 Handbetrieb aktiv\0"
"\x02 Störung\0"
"\x34 Kollektorfrostschutz aktiv\0"
"\x35 Rückkühlung aktiv\0"
"\x36 Max Speichertemp erreicht\0"
"\x37 Verdampfungsschutz aktiv\0"
"\x38 Überhitzschutz aktiv\0"
"\x39 Max Ladetemp erreicht\0"
"\x3a Ladung Trinkwasser\0"
"\x3b Ladung Pufferspeicher\0"
"\x3c Ladung Schwimmbad\0"
"\x3d Min Ladetemp nicht erreicht\0"
"\x3e Temp’differenz ungenügend\0"
"\x3f Einstrahlung ungenügend\0"
"\x97 Lad'ng TWW + Puffer + Sch'bad\0"
"\x98 Ladung Trinkwasser + Puffer\0"
"\x99 Ladung Trinkwasser + Sch'bad\0"
"\x9a Ladung Puffer + Schwimmbad"
};


//Status Feststoffkessel
const char ENUM8008[] PROGMEM = {
"\x00 ---\0"
"\x04 Handbetrieb aktiv\0"
"\x02 Störung\0"
"\x08 Gesperrt, Manuell\0"
"\x09 Gesperrt, Automatisch\0"
"\x0a Gesperrt\0"
"\x0b Anfahrentlastung\0"
"\x0c Anfahrentlastung, Teillast\0"
"\x0d Rücklaufbegrenzung\0"
"\x0e Rücklaufbegrenzung, Teillast\0"
"\x11 Nachlauf aktiv\0"
"\x12 In Betrieb\0"
"\x13 Freigegeben\0"
"\x14 Minimalbegrenzung\0"
"\x15 Minimalbegrenzung, Teillast\0"
"\x16 Minimalbegrenzung aktiv\0"
"\x17 Anlagenfrostschutz aktiv\0"
"\x18 Frostschutz aktiv\0"
"\x19 Aus\0"
"\x38 Überhitzschutz aktiv\0"
"\x8d Kesselfrostschutz aktiv\0"
"\xa3 Anfeuerungshilfe aktiv\0"
"\xa6 In Betrieb für Heizkreis\0"
"\xa7 In Teillastbetrieb für HK\0"
"\xa8 In Betrieb für Trinkwasser\0"
"\xa9 In Teillastbetrieb für TWW\0"
"\xaa In Betrieb für HK, TWW\0"
"\xab In Teillastbetrieb für HK, TWW"
};

//Status Pufferspeicher
const char ENUM8010[] PROGMEM = {
"\x00 ---\0"
"\x18 Frostschutz aktiv\0"
"\x33 Keine Wärmeanforderung\0"
"\x35 Rückkühlung aktiv\0"
"\x40 Ladung Elektro, Notbetrieb\0"
"\x41 Ladung Elektro, Quell’schutz\0"
"\x42 Ladung Elektroeinsatz\0"
"\x43 Zwangsladung aktiv\0"
"\x44 Teilladung aktiv\0"
"\x45 Ladung aktiv\0"
"\x46 Geladen, Max Speichertemp\0"
"\x47 Geladen, Max Ladetemp\0"
"\x48 Geladen, Zwanglad Solltemp\0"
"\x49 Geladen, Solltemperatur\0"
"\x4a Teilgeladen, Solltemperatur\0"
"\x4b Geladen\0"
"\x4c Kalt\0"
"\x4d Rückkühlung via Kollektor\0"
"\x51 Ladung gesperrt\0"
"\x68 Eingeschränkt, TWW-Vorrang\0"
"\x7c Ladung eingeschränkt\0"
"\x83 Ladung Elektro, Abtauen\0"
"\x87 Sperrdauer nach Heizen\0"
"\x8e Rückkühlung via TWW / Hk’s\0"
"\x8f Geladen, Min Ladetemp\0"
"\x93 Warm\0"
"\xa4 Ladung Elektro, Zwang\0"
"\xa5 Ladung Elektro, Ersatz\0"
"\xca Frostschutz Kühlen aktiv\0"
"\xcb Durchladung aktiv"
};

/* SPECIAL ENUM tables */
//Fehlercodes
const char ENUM_ERROR[] PROGMEM = {
"\x00 kein Fehler\0"
"\x0a Außentemperatur Fühlerfehler\0"
"\x14 Kesseltemperatur 1 Fühlerfehler\0"
"\x19 Feststoffkesseltemperatur (Holz) Fühlerfehler\0"
"\x1a Gemeinsame Vorlauftemperatur Fühlerfehler\0"
"\x1c Rauch- / Abgastemperatur Fühlerfehler\0"
"\x1e Vorlauftemperatur 1 Fühlerfehler\0"
"\x1f Vorlauftemperatur 1 Kühlen Fühlerfehler\0"
"\x20 Vorlauftemperatur 2 Fühlerfehler\0"
"\x26 Vorlauftemperatur Vorregler Fühlerfehler\0"
"\x28 Rücklauftemperatur 1 Fühlerfehler\0"
"\x2e Rücklauftemperatur Kaskade Fühlerfehler\0"
"\x2f Gemeinsame Rücklauftemperatur Fühlerfehler\0"
"\x32 Trinkwassertemperatur 1 Fühlerfehler\0"
"\x34 Trinkwassertemperatur 2 Fühlerfehler\0"
"\x36 TWW-Vorregler Fühlerfehler\0"
"\x39 TWW-Zirkulationstemperatur Fühlerfehler\0"
"\x3c Raumtemperatur 1 Fühlerfehler\0"
"\x41 Raumtemperatur 2 Fühlerfehler\0"
"\x44 Raumtemperatur 3 Fühlerfehler\0"
"\x46 Pufferspeichertemperatur 1 Fühlerfehler\0"
"\x47 Pufferspeichertemperatur 2 Fühlerfehler\0"
"\x48 Pufferspeichertemperatur 3 Fühlerfehler\0"
"\x49 Kollektortemperatur 1 Fühlerfehler\0"
"\x4a Kollektortemperatur 2 Fühlerfehler\0"
"\x51 LPB-Kurzschluss\0"
"\x52 LPB-Adresskollision\0"
"\x53 BSB-Draht Kurzschluss\0"
"\x54 BSB-Adresskollision\0"
"\x55 BSB-Funk Kommunikationsfehler\0"
"\x62 Erweiterungsmodul 1 Fehler (Sammelfehler)\0"
"\x63 Erweiterungsmodul 2 Fehler (Sammelfehler)\0"
"\x64 Zwei Uhrzeitmaster (LPB)\0"
"\x66 Uhrzeitmaster ohne Gangreserve (LPB)\0"
"\x69 Wartungsmeldung\0"
"\x6d Kesseltemperatur Überwachung\0"
"\x6e STB Störabschaltung\0"
"\x75 Obere Druckgrenze (überschritten)\0"
"\x76 Kritische untere Druckgrenze (unterschritten)\0"
"\x79 Vorlauftemperatur 1 (Hk1) Überwachung\0"
"\x7a Vorlauftemperatur 2 (Hk2) Überwachung\0"
"\x7e Trinkwasser-Ladeüberwachung\0"
"\x7f Legionellentemperatur nicht erreicht\0"
"\x83 Brennerstörung\0"
"\x92 Konfigurationsfehler Sammelmeldung\0"
"\xab Alarmkontakt 1 (H1) aktiv\0"
"\xac Alarmkontakt 2 (H2) aktiv\0"
"\xad Alarmkontakt 3 (EX2 / 230 VAC) aktiv\0"
"\xae Alarmkontakt 4 (H3) aktiv\0"
"\xb0 Obere Druckgrenze 2 (überschritten)\0"
"\xb1 Kritische untere Druckgrenze 2 (unterschritten)\0"
"\xb2 Temperaturwächter Heizkreis 1\0"
"\xb3 Temperaturwächter Heizkreis 2\0"
"\xcf Störung Kühlkreis\0"
"\xd9 Fühler- / Sensorfehler Sammelmeldung\0"
"\xd9 Fühler- / Sensorfehler Sammelmeldung\0"
"\xda Drucküberwachung Sammelmeldung\0"
"\xf1 Vorlauffühler Solar Fühlerfehler\0"
"\xf2 Rücklauffühler Solar Fühlerfehler\0"
"\xf3 Schwimmbadtemperatur Fühlerfehler\0"
"\x1\x40 TWW Ladetemperatur Fühlerfehler\0"
"\x1\x41 Durchl’erhitzer Zapftemperatur Fühlerfehler\0"
"\x1\x42 Obere Druckgrenze 3 (überschritten)\0"
"\x1\x43 Kritische untere Druckgrenze 3 (unterschritten)\0"
"\x1\x44 BX gleiche Fühler\0"
"\x1\x45 BX/Erweiterungsmodul gleiche Fühler\0"
"\x1\x46 BX/Mischergruppe gleiche Fühler\0"
"\x1\x47 Erweiterungsmodul gleiche Funktion\0"
"\x1\x48 Mischergruppe gleiche Funktion\0"
"\x1\x49 Erweit’modul / Mischergruppe gleiche Funktion\0"
"\x1\x4a Fühler BX1 keine Funktion\0"
"\x1\x4b Fühler BX2 keine Funktion\0"
"\x1\x4c Fühler BX3 keine Funktion\0"
"\x1\x4d Fühler BX4 keine Funktion\0"
"\x1\x4e Fühler BX5 keine Funktion\0"
"\x1\x4f Fühler BX21 keine Funktion\0"
"\x1\x50 Fühler BX22 keine Funktion\0"
"\x1\x51 Fühler BX1 keine Funktion\0"
"\x1\x52 Fühler BX12 keine Funktion\0"
"\x1\x53 Kollektorpumpe Q5 fehlt\0"
"\x1\x54 Kollektorpumpe Q16 fehlt\0"
"\x1\x55 Kollektorfühler B6 fehlt\0"
"\x1\x56 Solar TWW-Fühler B31 fehlt\0"
"\x1\x57 Solareinbindung fehlt\0"
"\x1\x58 Solarstellglied Puffer K8 fehlt\0"
"\x1\x59 Solarstellglied Schwimmbad K18 fehlt\0"
"\x1\x5a Feststoffkesselpumpe Q10 fehlt\0"
"\x1\x5b Feststoffkessel Vergleichsfühler fehlt\0"
"\x1\x5c Feststoffkessel Adressfehler\0"
"\x1\x5d Pufferrücklaufventil Y15 fehlt\0"
"\x1\x5e Pufferspeicher Adressfehler\0"
"\x1\x5f Vorregler / Zubringerpumpe Adressfehler\0"
"\x1\x60 Hydraulische Weiche Adressfehler\0"
"\x1\x61 Kaskadenfühler B10 fehlt\0"
"\x1\x65 Vorlauftemperatur Kühlkreis 1 Überwachung\0"
"\x1\x6e Raumtemperatur Hx Fühlerfehler\0"
"\x1\x6f Relative Raumfeuchte Hx Fühlerfehler"
};

// Wartungs-Codes
const char ENUM_WARTUNG[] PROGMEM = {
"\x01 Brennerbetriebsstunden überschritten\0"
"\x02 Brennerstarts überschritten\0"
"\x03 Wartungsintervall überschritten\0"
"\x05 Wasserdruck Heizkreis zu niedrig (Untere Druckgrenze 1 unterschritten)\0"
"\x12 Wasserdruck 2 Heizkreis zu niedrig (Untere Druckgrenze 2 unterschritten)\0"
"\x0a Batterie Außenfühler wechseln\0"
"\x15 Maximale Abgastemperatur überschritten\0"
"\x16 Wasserdruck 3 Heizkreis zu niedrig (Untere Druckgrenze 3 unterschritten)"
};

// Sonderbetriebs-Codes
const char ENUM_SONDERBETRIEB[] PROGMEM = {
"\x1\x2d Handbetrieb\0"
"\x1\x2e STB-Test\0"
"\x1\x2f Schornsteinfegerfkt\0"
"\x1\x35 Simulation Außentemp\0"
"\x1\x36 Alternativenerg"
};

// Sonderbetriebs-Codes
const char ENUM_WEEKDAY[] PROGMEM = {
"\x01 Montag\0"
"\x02 Dienstag\0"
"\x03 Mittwoch\0"
"\x04 Donnerstag\0"
"\x05 Freitag\0"
"\x06 Samstag\0"
"\x07 Sonntag"
};

/*
 * Bei der Änderung des Komfortsollwertes durch einfaches Drehen des Rades werden scheinbar die Grenzwerte abgefragt:
HEIZ->DISP ANS  710 11 - Heizkreis 1 - Komfortsollwert 20.00 &deg;C
HEIZ->DISP ANS      2D3D05A5 00 08 C0 (35.0°C)
DC 80 0A 0E 07 2D 3D 05 A5 00 08 C0 3F 7B
HEIZ->DISP ANS  712 11 - Heizkreis 1 - Reduziertsollwert 15.00 &deg;C
*/

/*global command table */
PROGMEM const cmd_t cmdtbl[]={
// Uhrzeit und Datum
{0x0500006C, CAT_DATUMZEIT, VT_DATETIME, 0, STR0, 0, NULL}, // [ ] - Uhrzeit und Datum
{CMD_UNKNOWN, CAT_DATUMZEIT, VT_UNKNOWN, 1, STR1, 0, NULL}, // [hh:mm ] - Uhrzeit und Datum - Stunden/Minuten
{CMD_UNKNOWN, CAT_DATUMZEIT, VT_UNKNOWN, 2, STR2, 0, NULL}, // [tt:MM ] - Uhrzeit und Datum - Tag/Monat
{CMD_UNKNOWN, CAT_DATUMZEIT, VT_UNKNOWN, 3, STR3, 0, NULL}, // [jjjj ] - Uhrzeit und Datum - Jahr
// Sommerzeit scheint im DISP gehandelt zu werden
// Bei Anzeige werden keine Werte abgefragt. Bei Änderung wird ein INF geschickt.
// Sommerzeit Beginn 25.3. DISP->ALL  INF      0500009E 00 FF 03 19 FF FF FF FF 16
// Sommerzeit Ende 25.11. DISP->ALL  INF      0500009D 00 FF 0B 19 FF FF FF FF 16
{0x0500009E, CAT_DATUMZEIT, VT_SUMMERPERIOD, 5, STR5, 0, NULL}, // [tt:MM ] - Uhrzeit und Datum - Sommerzeitbeginn Tag/Monat
{0x0500009D, CAT_DATUMZEIT, VT_SUMMERPERIOD, 6, STR6, 0, NULL}, // [tt.MM ] - Uhrzeit und Datum - Sommerzeitende Tag/Monat

// nur Bedienteil -> keine Kommunikation über BSB
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 20, STR20, 0, NULL}, // [0] - Bedieneinheit - Sprachauswahl
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 22, STR22, 0, NULL}, // [0] - Bedieneinheit - Info
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 23, STR23, 0, NULL}, // Fehleranzeige
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 25, STR25, 0, NULL}, // Anzeigekontrast
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 26, STR26, 0, NULL}, // [0] - Bedieneinheit - Sperre Bedienung
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 27, STR27, 0, NULL}, // [0] - Bedieneinheit - Sperre Programmierung
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 28, STR28, 0, NULL}, // [0] - Bedieneinheit - Bedieneinheit Direktverstellung
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 30, STR30, 0, NULL}, // Bedieneinheit Grundeinstellung sichern
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 31, STR31, 0, NULL}, // Bedieneinheit Grundeinstellung aktivieren
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 40, STR40, 0, NULL}, // Einsatz als
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 42, STR42, 0, NULL}, // Zurodnung Raumgerät 1
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 44, STR44, 0, NULL}, // [0] - Bedieneinheit - Bedienung HK 2
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 46, STR46, 0, NULL}, // [0] - Bedieneinheit - Bedienung HK P
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 48, STR48, 0, NULL}, // Wirkung Präsenztaste
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 54, STR54, 0, NULL}, // Korrektur Raumfühler
{CMD_UNKNOWN, CAT_BEDIENEINHEIT, VT_UNKNOWN, 70, STR70, 0, NULL}, // [0] - Bedieneinheit - Geraete-Version Bedienteil

// Funk
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 120, STR120, 0, NULL}, // Binding
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 121, STR121, 0, NULL}, // Testmode
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 130, STR130, 0, NULL}, // Raumgerät 1 Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 131, STR131, 0, NULL}, // Raumgerät 2 Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 132, STR132, 0, NULL}, // Raumgerät P Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 133, STR133, 0, NULL}, // Außenfühler P Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 134, STR134, 0, NULL}, // Repeater P Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 135, STR135, 0, NULL}, // Bedieneinheit 1 Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 136, STR136, 0, NULL}, // Bedieneinheit 2 Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 137, STR137, 0, NULL}, // Bedieneinheit P Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 138, STR138, 0, NULL}, // Servicegerät Status
{CMD_UNKNOWN, CAT_FUNK, VT_UNKNOWN, 140, STR140, 0, NULL}, // Alle Geräte löschen

// Zeitprogramm Heizkreis 1
// HEIZ->DISP ANS 500 Vorwahl  05 00 15 00 98 00 18 00 98 00 18 00
// set Mo 1. Heizphase 05:10  -> DISP->HEIZ SET 3D050A8C 05 0A 15 00 80 00 00 00 80 00 00 00
// set Mo 1. Heizphase 05:00  -> DISP->HEIZ SET 3D050A8C 05 00 15 00 80 00 00 00 80 00 00 00
/*
 Für jeden Wochentag können 3 Phasen gesetzt werden. Die Kombinationen Mo-Fr, Mo-So, Sa - So werden nur auf dem Bedienteil angezeigt.
 8C = Mo .. 92 = So
*/
/* virtuelle Zeilen*/
{0x053d0a8c, CAT_ZEITPROG_HK1, VT_TIMEPROG, 500, STR500, 0, NULL}, // [0] - Zeitprogramm Heizkreis 1 - Vorwahl
{0x053d0a8d, CAT_ZEITPROG_HK1, VT_TIMEPROG, 501, STR501, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Ein
{0x053d0a8e, CAT_ZEITPROG_HK1, VT_TIMEPROG, 502, STR502, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 1. Phase Aus
{0x053d0a8f, CAT_ZEITPROG_HK1, VT_TIMEPROG, 503, STR503, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Ein
{0x053d0a90, CAT_ZEITPROG_HK1, VT_TIMEPROG, 504, STR504, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 2. Phase Aus
{0x053d0a91, CAT_ZEITPROG_HK1, VT_TIMEPROG, 505, STR505, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Ein
{0x053d0a92, CAT_ZEITPROG_HK1, VT_TIMEPROG, 506, STR506, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 1 - Mo-So: 3. Phase Aus
{0x053d05b2, CAT_ZEITPROG_HK1, VT_YESNO, 516, STR516, 0, NULL}, // [0] - Zeitprogramm Heizkreis 1 - Standardwerte

// Zeitprogramm Heizkreis 2
/* virtuelle Zeilen*/
{0x063d0a8c, CAT_ZEITPROG_HK2, VT_TIMEPROG, 520, STR520, 0, NULL}, // [0] - Zeitprogramm Heizkreis 2 - Vorwahl
{0x063d0a8d, CAT_ZEITPROG_HK2, VT_TIMEPROG, 521, STR521, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Ein
{0x063d0a8e, CAT_ZEITPROG_HK2, VT_TIMEPROG, 522, STR522, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 1. Phase Aus
{0x063d0a8f, CAT_ZEITPROG_HK2, VT_TIMEPROG, 523, STR523, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Ein
{0x063d0a90, CAT_ZEITPROG_HK2, VT_TIMEPROG, 524, STR524, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 2. Phase Aus
{0x063d0a91, CAT_ZEITPROG_HK2, VT_TIMEPROG, 525, STR525, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Ein
{0x063d0a92, CAT_ZEITPROG_HK2, VT_TIMEPROG, 526, STR526, 0, NULL}, // [hh:mm ] - Zeitprogramm Heizkreis 2 - Mo-So: 3. Phase Aus
// Thision 535 Tag kopieren auf
{0x063d05b2, CAT_ZEITPROG_HK2, VT_YESNO, 536, STR536, 0, NULL}, // [0] - Zeitprogramm Heizkreis 2 - Standardwerte

// Zeitprogramm 3/HKP
/* virtuelle Zeilen*/
{0x073d0a8c, CAT_ZEITPROG_HKP, VT_TIMEPROG, 540, STR540, 0, NULL}, // [0] - Zeitprogramm 3 HKP - Vorwahl
{0x073d0a8d, CAT_ZEITPROG_HKP, VT_TIMEPROG, 541, STR541, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Ein
{0x073d0a8e, CAT_ZEITPROG_HKP, VT_TIMEPROG, 542, STR542, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 1. Phase Aus
{0x073d0a8f, CAT_ZEITPROG_HKP, VT_TIMEPROG, 543, STR543, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Ein
{0x073d0a90, CAT_ZEITPROG_HKP, VT_TIMEPROG, 544, STR544, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 2. Phase Aus
{0x073d0a91, CAT_ZEITPROG_HKP, VT_TIMEPROG, 545, STR545, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Ein
{0x073d0a92, CAT_ZEITPROG_HKP, VT_TIMEPROG, 546, STR546, 0, NULL}, // [hh:mm ] - Zeitprogramm 3 HKP - Mo-So: 3. Phase Aus
// Thision 555 Tag kopieren auf
{0x073d05b2, CAT_ZEITPROG_HKP, VT_YESNO, 556, STR556, 0, NULL}, // [0] - Zeitprogramm 3 HKP - Standardwerte

// Zeitprogramm 4/TWW
{0x053d0aa0, CAT_ZEITPROG_TWW, VT_TIMEPROG, 560, STR560, 0, NULL}, // [0] - Zeitprogramm 4 TWW - Vorwahl
{0x053d0aa1, CAT_ZEITPROG_TWW, VT_TIMEPROG, 561, STR561, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Ein
{0x053d0aa2, CAT_ZEITPROG_TWW, VT_TIMEPROG, 562, STR562, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 1. Phase Aus
{0x053d0aa3, CAT_ZEITPROG_TWW, VT_TIMEPROG, 563, STR563, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Ein
{0x053d0aa4, CAT_ZEITPROG_TWW, VT_TIMEPROG, 564, STR564, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 2. Phase Aus
{0x053d0aa5, CAT_ZEITPROG_TWW, VT_TIMEPROG, 565, STR565, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Ein
{0x053d0aa6, CAT_ZEITPROG_TWW, VT_TIMEPROG, 566, STR566, 0, NULL}, // [hh:mm ] - Zeitprogramm 4 TWW - Mo-So: 3. Phase Aus
// Thision 575 Tag kopieren auf
{0x053d05b3, CAT_ZEITPROG_TWW, VT_YESNO, 576, STR576, 0, NULL}, // [0] - Zeitprogramm 4 TWW - Standardwerte

// Zeitprogramm 5
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 600, STR600, 0, NULL}, // [0] - Zeitprogramm 5 - Vorwahl
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 601, STR601, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 1. Phase Ein
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 602, STR602, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 1. Phase Aus
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 603, STR603, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 2. Phase Ein
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 604, STR604, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 2. Phase Aus
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 605, STR605, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 3. Phase Ein
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_TIMEPROG, 606, STR606, 0, NULL}, // [hh:mm ] - Zeitprogramm 5 - Mo-So: 3. Phase Aus
{CMD_UNKNOWN, CAT_ZEITPROG_5, VT_YESNO, 616, STR616, 0, NULL}, // [0] - Zeitprogramm 5 - Standardwerte

/*
 Es gibt 8 Perioden c4..d3 (jeweils Beginn/Ende).
 Zeile 641 dient nur zur Vorwahl der Perioden auf dem Bedienteil.
 Die Parameter scheinen VT_DATETIME ähnlich zu sein.
 1. Byte:
 Bei RX 00=enabled 01=disabled
 Bei TX 06=enable 05=disable
 byte 3 Monat
 byte 4 Tag
 byte 17=0x17
 alle anderen Bytes sind 0
 z.B.:
 DISP->HEIZ SET      3D0509C6 06 00 02 0A 00 00 00 00 17
 Periode 2 Ende: DC 80 0A 14 07 05 3D 09 C6 01 00 01 01 00 00 00 00 17 0C 38
*/
// Ferien Heizkreis 1
/* virtuelle Zeilen*/
{0x053d09c4, CAT_FERIEN_HK1, VT_VACATIONPROG, 632, STR632, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 1 Beginn Tag/Monat
{0x053d09c5, CAT_FERIEN_HK1, VT_VACATIONPROG, 633, STR633, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 1 Ende Tag/Monat
{0x053d09c6, CAT_FERIEN_HK1, VT_VACATIONPROG, 634, STR634, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 2 Beginn Tag/Monat
{0x053d09c7, CAT_FERIEN_HK1, VT_VACATIONPROG, 635, STR635, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 2 Ende Tag/Monat
{0x053d09c8, CAT_FERIEN_HK1, VT_VACATIONPROG, 636, STR636, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 3 Beginn Tag/Monat
{0x053d09c9, CAT_FERIEN_HK1, VT_VACATIONPROG, 637, STR637, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 3 Ende Tag/Monat
{0x053d09ca, CAT_FERIEN_HK1, VT_VACATIONPROG, 638, STR638, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 4 Beginn Tag/Monat
{0x053d09cb, CAT_FERIEN_HK1, VT_VACATIONPROG, 639, STR639, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 4 Ende Tag/Monat
{0x053d09cc, CAT_FERIEN_HK1, VT_VACATIONPROG, 640, STR640, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 5 Beginn Tag/Monat
{0x053d09cd, CAT_FERIEN_HK1, VT_VACATIONPROG, 641, STR641, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 5 Ende Tag/Monat
{0x053d09ce, CAT_FERIEN_HK1, VT_VACATIONPROG, 642, STR642, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Beginn Tag/Monat
{0x053d09cf, CAT_FERIEN_HK1, VT_VACATIONPROG, 643, STR643, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 6 Ende Tag/Monat
{0x053d09d0, CAT_FERIEN_HK1, VT_VACATIONPROG, 644, STR644, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 7 Beginn Tag/Monat
{0x053d09d1, CAT_FERIEN_HK1, VT_VACATIONPROG, 645, STR645, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 7 Ende Tag/Monat
{0x053d09d2, CAT_FERIEN_HK1, VT_VACATIONPROG, 646, STR646, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 8 Beginn Tag/Monat
{0x053d09d3, CAT_FERIEN_HK1, VT_VACATIONPROG, 647, STR647, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Periode 8 Ende Tag/Monat
{0x2d3d04c2, CAT_FERIEN_HK1, VT_ENUM, 648, STR648, sizeof(ENUM648), ENUM648}, // [0] - Ferienheizkreis 1 - Betriebsniveau
// Ferien Heizkreis 2
/* virtuelle Zeilen*/
{0x063d09c4, CAT_FERIEN_HK2, VT_VACATIONPROG, 649, STR649, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 1 Beginn Tag/Monat
{0x063d09c5, CAT_FERIEN_HK2, VT_VACATIONPROG, 650, STR650, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 1 Ende Tag/Monat
{0x063d09c6, CAT_FERIEN_HK2, VT_VACATIONPROG, 651, STR651, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 2 Beginn Tag/Monat
{0x063d09c7, CAT_FERIEN_HK2, VT_VACATIONPROG, 652, STR652, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 2 Ende Tag/Monat
{0x063d09c8, CAT_FERIEN_HK2, VT_VACATIONPROG, 653, STR653, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 3 Beginn Tag/Monat
{0x063d09c9, CAT_FERIEN_HK2, VT_VACATIONPROG, 654, STR654, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 3 Ende Tag/Monat
{0x063d09ca, CAT_FERIEN_HK2, VT_VACATIONPROG, 655, STR655, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 4 Beginn Tag/Monat
{0x063d09cb, CAT_FERIEN_HK2, VT_VACATIONPROG, 656, STR656, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 4 Ende Tag/Monat
{0x063d09cc, CAT_FERIEN_HK2, VT_VACATIONPROG, 657, STR657, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 5 Beginn Tag/Monat
{0x063d09cd, CAT_FERIEN_HK2, VT_VACATIONPROG, 658, STR658, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 5 Ende Tag/Monat
{0x063d09ce, CAT_FERIEN_HK2, VT_VACATIONPROG, 659, STR659, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 6 Beginn Tag/Monat
{0x063d09cf, CAT_FERIEN_HK2, VT_VACATIONPROG, 660, STR660, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 6 Ende Tag/Monat
{0x063d09d0, CAT_FERIEN_HK2, VT_VACATIONPROG, 661, STR661, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 7 Beginn Tag/Monat
{0x063d09d1, CAT_FERIEN_HK2, VT_VACATIONPROG, 662, STR662, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 7 Ende Tag/Monat
{0x063d09d2, CAT_FERIEN_HK2, VT_VACATIONPROG, 663, STR663, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 8 Beginn Tag/Monat
{0x063d09d3, CAT_FERIEN_HK2, VT_VACATIONPROG, 664, STR664, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 - Periode 8 Ende Tag/Monat
{0x2e3d04c2, CAT_FERIEN_HK2, VT_ENUM, 665, STR665, sizeof(ENUM665), ENUM665}, // [0] - Ferienheizkreis 2 - Betriebsniveau
// Ferien Heizkreis P
/* virtuelle Zeilen*/
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 666, STR666, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 1 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 667, STR667, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 1 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 668, STR668, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 2 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 669, STR669, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 2 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 670, STR670, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 3 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 671, STR671, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 3 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 672, STR672, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 4 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 673, STR673, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 4 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 674, STR674, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 5 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 675, STR675, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 5 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 676, STR676, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 6 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 677, STR677, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 6 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 678, STR678, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 7 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 679, STR679, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 7 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 680, STR680, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 8 Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_VACATIONPROG, 681, STR681, 0, NULL}, // [tt.MM ] - Ferienheizkreis P - Periode 8 Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_ENUM, 682, STR682, sizeof(ENUM682), ENUM682}, // [0] - Ferienheizkreis P - Betriebsniveau
/*
{CMD_UNKNOWN, CAT_FERIEN_HK1, VT_UNKNOWN, 641, STR641, 0, NULL}, // [0] - Ferienheizkreis 1 - Vorwahl
{0x053d09c4, CAT_FERIEN_HK1, VT_VACATIONPROG, 642, STR642, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Beginn Tag/Monat
{0x053d09c5, CAT_FERIEN_HK1, VT_UNKNOWN, 643, STR643, 0, NULL}, // [tt.MM ] - Ferienheizkreis 1 - Ende Tag/Monat
{0x2d3d04c2, CAT_FERIEN_HK1, VT_ENUM, 648, STR648, sizeof(ENUM648), ENUM648}, // [0] - Ferienheizkreis 1 - Betriebsniveau

// Ferien Heizkreis 2
{CMD_UNKNOWN, CAT_FERIEN_HK2, VT_UNKNOWN, 651, STR651, 0, NULL}, // [0] - Ferienheizkreis 2 (nur wenn aktiviert) - Vorwahl
{0x063d09c4, CAT_FERIEN_HK2, VT_UNKNOWN, 652, STR652, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 (nur wenn aktiviert) - Beginn Tag/Monat
{0x063d09c5, CAT_FERIEN_HK2, VT_UNKNOWN, 653, STR653, 0, NULL}, // [tt.MM ] - Ferienheizkreis 2 (nur wenn aktiviert) - Ende Tag/Monat
{0x2e3d04c2, CAT_FERIEN_HK2, VT_UNKNOWN, 658, STR658, sizeof(ENUM658), ENUM658}, // [0] - Ferienheizkreis 2 (nur wenn aktiviert) - Betriebsniveau

// Ferien Heizkreis P
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_UNKNOWN, 661, STR661, 0, NULL}, // [0] - Ferienheizkreis P (nur wenn aktiviert) - Vorwahl
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_UNKNOWN, 662, STR662, 0, NULL}, // [tt.MM ] - Ferienheizkreis P (nur wenn aktiviert) - Beginn Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_UNKNOWN, 663, STR663, 0, NULL}, // [tt.MM ] - Ferienheizkreis P (nur wenn aktiviert) - Ende Tag/Monat
{CMD_UNKNOWN, CAT_FERIEN_HKP, VT_UNKNOWN, 668, STR668, sizeof(ENUM668), ENUM668}, // [0] - Ferienheizkreis P (nur wenn aktiviert) - Betriebsniveau
*/

// Heizkreis 1
{0x2D3D0574, CAT_HK1, VT_ENUM, 700, STR700, sizeof(ENUM700), ENUM700}, // [-] - Heizkreis 1 - Betriebsart ***(virtuelle Zeile)***
{0x2d3d058e, CAT_HK1, VT_TEMP, 710, STR710, 0, NULL}, // [°C ] - Heizkreis 1 - Komfortsollwert
//HEIZ->DISP ANS      2D3D05A5 00 08 C0 (35.0°C)
// line not in menue!
/* virtuelle Zeile*/
{0x2D3D05A5, CAT_HK1, VT_TEMP, 711, STR711, 0, NULL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max
{0x2d3d0590, CAT_HK1, VT_TEMP, 712, STR712, 0, NULL}, // [°C ] - Heizkreis 1 - Reduziertsollwert
{0x2d3d0592, CAT_HK1, VT_TEMP, 714, STR714, 0, NULL}, // [°C ] - Heizkreis 1 - Frostschutzsollwert
{0x2d3d05f6, CAT_HK1, VT_FP02, 720, STR720, 0, NULL}, // [0] - Heizkreis 1 - Kennlinie Steilheit
{0x2d3d0610, CAT_HK1, VT_TEMP, 721, STR721, 0, NULL}, // [°C ] - Heizkreis 1 - Kennlinie Verschiebung
{0x2d3d060b, CAT_HK1, VT_ONOFF, 726, STR726, 0, NULL}, // [] - Heizkreis 1 - Kennlinie Adaption
{0x2d3d05fd, CAT_HK1, VT_TEMP, 730, STR730, 0, NULL}, // [°C ] - Heizkreis 1 - Sommer-/ Winterheizgrenze
{0x2d3d0640, CAT_HK1, VT_TEMP, 732, STR732, 0, NULL}, // [°C ] - Heizkreis 1 - Tagesheizgrenze
{0x213d0663, CAT_HK1, VT_TEMP, 740, STR740, 0, NULL}, // [°C ] - Heizkreis 1 - Vorlaufsollwert Minimum
{0x213d0662, CAT_HK1, VT_TEMP, 741, STR741, 0, NULL}, // [°C ] - Heizkreis 1 - Vorlaufsollwert Maximum
{0x2d3d0603, CAT_HK1, VT_PERCENT, 750, STR750, 0, NULL}, // [% ] - Heizkreis 1 - Raumeinfluss
{0x2d3d0614, CAT_HK1, VT_TEMP, 760, STR760, 0, NULL}, // [°C ] - Heizkreis 1 - Raumtemperaturbegrenzung
{0x2d3d0602, CAT_HK1, VT_TEMP, 770, STR770, 0, NULL}, // [°C ] - Heizkreis 1 - Schnellaufheizung
{0x2d3d05e8, CAT_HK1, VT_ENUM, 780, STR780, sizeof(ENUM780), ENUM780}, // [-] - Heizkreis 1 - Schnellabsenkung
{0x2d3d0607, CAT_HK1, VT_MINUTES, 790, STR790, 0, NULL}, // [Min ] - Heizkreis 1 - Einschalt-Optimierung Max.
{0x2d3d0609, CAT_HK1, VT_MINUTES, 791, STR791, 0, NULL}, // [Min ] - Heizkreis 1 - Ausschalt-Optimierung Max.
{0x2d3d059e, CAT_HK1, VT_TEMP, 800, STR800, 0, NULL}, // [°C ] - Heizkreis 1 - Reduziert-Anhebung Begin
{0x2d3d059d, CAT_HK1, VT_TEMP, 801, STR801, 0, NULL}, // [°C ] - Heizkreis 1 - Reduziert-Anhebung Ende
{0x213D0674, CAT_HK1, VT_ONOFF, 820, STR820, 0, NULL}, // [  - ] - Heizkreis 1 - Überhitzschutz Pumpenkreis
{0x213D065D, CAT_HK1, VT_TEMP, 830, STR830, 0, NULL}, // [°C ] - Heizkreis 1 - Mischerüberhöhung
{0x2d3d067b, CAT_HK1, VT_ENUM, 850, STR850, sizeof(ENUM850), ENUM850}, // [-] - Heizkreis 1 - Estrichfunktion
{0x2d3d068a, CAT_HK1, VT_TEMP, 851, STR851, 0, NULL}, // [°C ] - Heizkreis 1 - Estrich sollwert manuell
{0x213D08C9, CAT_HK1, VT_ENUM, 861, STR861, sizeof(ENUM861), ENUM861}, // [0] - Heizkreis 1 - Übertemperaturabnahme
{0x2D3D07C4, CAT_HK1, VT_YESNO, 870, STR870, 0, NULL}, // [0] - Heizkreis 1 - Mit Pufferspeicher
{0x2D3D07C5, CAT_HK1, VT_YESNO, 872, STR872, 0, NULL}, // [0] - Heizkreis 1 - Mit Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HK1, VT_UNKNOWN, 882, STR882, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_HK1, VT_UNKNOWN, 883, STR883, 0, NULL}, // Pumpendrehzahl Maximum
{CMD_UNKNOWN, CAT_HK1, VT_UNKNOWN, 884, STR884, 0, NULL}, // TODO Thision 884 Drehzahlstufe Ausleg'punkt [1-50, 9-13kW=16, 17-25kW=19, 35-50kW=24]
{CMD_UNKNOWN, CAT_HK1, VT_PERCENT, 885, STR885, 0, NULL}, // TODO Thision 885 Pumpe-PWM Minimum [%] 
{CMD_UNKNOWN, CAT_HK1, VT_TEMP, 886, STR886, 0, NULL}, // TODO Thision 886 Norm Aussentemperatur [°C]
{CMD_UNKNOWN, CAT_HK1, VT_TEMP, 887, STR887, 0, NULL}, // TODO Thision 887 Vorlaufsoll NormAussentemp [°C]
{CMD_UNKNOWN, CAT_HK1, VT_PERCENT, 888, STR888, 0, NULL}, // TODO Thision 888 dt Überhöhungsfaktor [%]
{CMD_UNKNOWN, CAT_HK1, VT_TEMP, 894, STR894, 0, NULL}, // TODO Thision 894 dt Spreizung Norm Aussent. [°C]
{CMD_UNKNOWN, CAT_HK1, VT_TEMP, 895, STR895, 0, NULL}, // TODO Thision 895 dt Spreizung Maximum [°C]
{0x053D07BE, CAT_HK1, VT_ENUM, 900, STR900, sizeof(ENUM900), ENUM900}, // [0] - Heizkreis 1 - Betriebsartumschaltung

// Kühlkreis 1
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 901, STR901, 0, NULL}, // Betriebsart
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 902, STR902, 0, NULL}, // Komfortsollwert
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 907, STR907, 0, NULL}, // Freigabe
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 908, STR908, 0, NULL}, // Vorlaufsollwert bei TA 25 °C
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 909, STR909, 0, NULL}, // Vorlaufsollwert bei TA 35 °C
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 912, STR912, 0, NULL}, // Kühlgrenze bei TA
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 913, STR913, 0, NULL}, // Sperrdauer nach Heizende
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 918, STR918, 0, NULL}, // Sommerkomp Beginn bei TA
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 919, STR919, 0, NULL}, // Sommerkomp Ende bei TA
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 920, STR920, 0, NULL}, // Sommerkomp Sollw’anhebung
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 923, STR923, 0, NULL}, // Vorlaufsollwert Min bei TA 25 °C
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 924, STR924, 0, NULL}, // Vorlaufsollwert Min bei TA 35 °C
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 928, STR928, 0, NULL}, // Raumeinfluss
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 932, STR932, 0, NULL}, // Raumtemperaturbegrenzung
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 938, STR938, 0, NULL}, // Mischerunterkühlung
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 939, STR939, 0, NULL}, // Antrieb Typ
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 940, STR940, 0, NULL}, // Schaltdifferenz 2-Punkt
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 941, STR941, 0, NULL}, // Antrieb Laufzeit
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 945, STR945, 0, NULL}, // Mischventil im Heizbetrieb
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 946, STR946, 0, NULL}, // Sperrdauer Taupunktwächt
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 947, STR947, 0, NULL}, // Vorlaufsollw’anhebung Hygro
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 948, STR948, 0, NULL}, // Vorl'anhebung Beginn bei r. F.
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 950, STR950, 0, NULL}, // Vorlauftemp'diff Taupunkt
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 962, STR962, 0, NULL}, // Mit Pufferspeicher
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 963, STR963, 0, NULL}, // Mit Vorregler/Zubring'pumpe
{CMD_UNKNOWN, CAT_KUEHL1, VT_UNKNOWN, 969, STR969, 0, NULL}, // Betriebsartumschaltung

// Heizkreis 2
{0x2e3d058e, CAT_HK2, VT_TEMP, 1010, STR1010, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Komfortsollwert
// line not in menue!
/* virtuelle Zeile*/
{0x2E3D05A5, CAT_HK2, VT_TEMP, 1011, STR1011, 0, NULL}, // [°C ] - Heizkreis 1 - Komfortsollwert Max
{0x2e3d0590, CAT_HK2, VT_TEMP, 1012, STR1012, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziertsollwert
{0x2e3d0592, CAT_HK2, VT_TEMP, 1014, STR1014, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Frostschutzsollwert
{0x2e3d05f6, CAT_HK2, VT_FP02, 1020, STR1020, 0, NULL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Steilheit
{0x2e3d0610, CAT_HK2, VT_TEMP, 1021, STR1021, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Verschiebung
{0x2e3d060b, CAT_HK2, VT_ONOFF, 1026, STR1026, 0, NULL}, // [] - Heizkreis 2 (nur wenn aktiviert) - Kennlinie Adaption
{0x2e3d05fd, CAT_HK2, VT_TEMP, 1030, STR1030, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Sommer-/ Winterheizgrenze
{0x2e3d0640, CAT_HK2, VT_TEMP, 1032, STR1032, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Tagesheizgrenze
{0x223d0663, CAT_HK2, VT_TEMP, 1040, STR1040, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Vorlaufsollwert Minimum
{0x223d0662, CAT_HK2, VT_TEMP, 1041, STR1041, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Vorlaufsollwert Maximum
{0x2e3d0603, CAT_HK2, VT_PERCENT, 1050, STR1050, 0, NULL}, // [% ] - Heizkreis 2 (nur wenn aktiviert) - Raumeinfluss
{0x2e3d0614, CAT_HK2, VT_TEMP, 1060, STR1060, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Raumtemperaturbegrenzung
{0x2e3d0602, CAT_HK2, VT_TEMP, 1070, STR1070, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Schnellaufheizung
{0x2e3d05e8, CAT_HK2, VT_ENUM, 1080, STR1080, sizeof(ENUM1080), ENUM1080}, // [-] - Heizkreis 2 (nur wenn aktiviert) - Schnellabsenkung
{0x2e3d0607, CAT_HK2, VT_MINUTES, 1090, STR1090, 0, NULL}, // [min] - Heizkreis 2 (nur wenn aktiviert) - Einschalt-Optimierung Max.
{0x2e3d0609, CAT_HK2, VT_MINUTES, 1091, STR1091, 0, NULL}, // [min] - Heizkreis 2 (nur wenn aktiviert) - Ausschalt-Optimierung Max.
{0x2e3d059e, CAT_HK2, VT_TEMP, 1100, STR1100, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziert-Anhebung Begin
{0x2e3d059d, CAT_HK2, VT_TEMP, 1101, STR1101, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Reduziert-Anhebung Ende
{CMD_UNKNOWN, CAT_HK2, VT_ONOFF, 1120, STR1120, 0, NULL}, // [  - ] - Heizkreis 2 (nur wenn aktiviert) - Überhitzschutz Pumpenkreis
{0x223d065d, CAT_HK2, VT_TEMP, 1130, STR1130, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Mischerüberhöhung
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1132, STR1132, 0, NULL}, // Antrieb Typ
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1133, STR1133, 0, NULL}, // Schaltdiffernez 2-Punkt
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1134, STR1134, 0, NULL}, // TODO Thision 1134 Antrieb Laufzeit [s]
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1135, STR1135, 0, NULL}, // TODO Thision 1135 Mischer P-Band XP [K]
{0x2e3d067b, CAT_HK2, VT_ENUM, 1150, STR1150, sizeof(ENUM1150), ENUM1150}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Estrichfunktion
{0x2e3d068a, CAT_HK2, VT_TEMP, 1151, STR1151, 0, NULL}, // [°C ] - Heizkreis 2 (nur wenn aktiviert) - Estrich sollwert manuell
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1155, STR1155, 0, NULL}, // TODO Thision 1155 Estrich Sollwert aktuell [Tage]
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1156, STR1156, 0, NULL}, // Estrich Tag aktuell
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1157, STR1157, 0, NULL}, // Estrich Tag erfüllt
{CMD_UNKNOWN, CAT_HK2, VT_ENUM, 1161, STR1161, sizeof(ENUM1161), ENUM1161}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HK2, VT_YESNO, 1170, STR1170, 0, NULL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Mit Pufferspeicher
{CMD_UNKNOWN, CAT_HK2, VT_YESNO, 1172, STR1172, 0, NULL}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Mit Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1182, STR1182, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_HK2, VT_UNKNOWN, 1183, STR1183, 0, NULL}, // Pumpendrehzahl Maximum
{CMD_UNKNOWN, CAT_HK2, VT_ENUM, 1200, STR1200, sizeof(ENUM1200), ENUM1200}, // [0] - Heizkreis 2 (nur wenn aktiviert) - Betriebsartumschaltung

// Heizkreis 3/P
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1300, STR1300, 0, NULL}, // Betriebsart
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1310, STR1310, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Komfortsollwert
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1312, STR1312, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziertsollwert
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1314, STR1314, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Frostschutzsollwert
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1320, STR1320, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Steilheit
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1321, STR1321, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Verschiebung
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1326, STR1326, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Kennlinie Adaption
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1330, STR1330, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Sommer-/ Winterheizgrenze
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1332, STR1332, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Tagesheizgrenze
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1340, STR1340, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Vorlaufsollwert Minimum
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1341, STR1341, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Vorlaufsollwert Maximum
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1350, STR1350, 0, NULL}, // [% ] - Heizkreis 3/P (nur wenn aktiviert) - Raumeinfluss
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1360, STR1360, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Raumtemperaturbegrenzung
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1370, STR1370, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Schnellaufheizung
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1380, STR1380, 0, NULL}, // [-] - Heizkreis 3/P (nur wenn aktiviert) - Schnellabsenkung
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1390, STR1390, 0, NULL}, // [min] - Heizkreis 3/P (nur wenn aktiviert) - Einschalt-Optimierung Max.
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1391, STR1391, 0, NULL}, // [min] - Heizkreis 3/P (nur wenn aktiviert) - Ausschalt-Optimierung Max.
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1400, STR1400, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziert-Anhebung Begin
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1401, STR1401, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Reduziert-Anhebung Ende
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1420, STR1420, 0, NULL}, // [  - ] - Heizkreis 3/P (nur wenn aktiviert) - Überhitzschutz Pumpenkreis
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1430, STR1430, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Mischerüberhöhung
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1450, STR1450, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Estrichfunktion
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1451, STR1451, 0, NULL}, // [°C ] - Heizkreis 3/P (nur wenn aktiviert) - Estrich sollwert manuell
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1455, STR1455, 0, NULL}, // Estrich Sollwert aktuell
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1456, STR1456, 0, NULL}, // Estrich Tag aktuell
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1457, STR1457, 0, NULL}, // Estrich Tag erfüllt
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1461, STR1461, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1470, STR1470, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Mit Pufferspeicher
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1472, STR1472, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Mit Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1482, STR1482, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1483, STR1483, 0, NULL}, // Pumpendrehzahl Maximum
{CMD_UNKNOWN, CAT_HKP, VT_UNKNOWN, 1500, STR1500, 0, NULL}, // [0] - Heizkreis 3/P (nur wenn aktiviert) - Betriebsartumschaltung

// Trinkwasser
{0x313D0571, CAT_TW, VT_YESNO, 1600, STR1600, 0, NULL}, // [-] - Trinkwasser - Trinkwasserbetrieb Ein/Aus ***(virtuelle Zeile)***
{0x313d06b9, CAT_TW, VT_TEMP, 1610, STR1610, 0, NULL}, // [°C ] - Trinkwasser  - Nennsollwert
{0x313d06ba, CAT_TW, VT_TEMP, 1612, STR1612, 0, NULL}, // [°C ] - Trinkwasser  - Reduziertsollwert
{0x253d0722, CAT_TW, VT_ENUM, 1620, STR1620, sizeof(ENUM1620), ENUM1620}, // [0] - Trinkwasser  - Freigabe
{0x313D0721, CAT_TW, VT_ENUM, 1630, STR1630, sizeof(ENUM1630), ENUM1630}, // [0] - Trinkwasser  - Ladevorgang
{0x313d0759, CAT_TW, VT_ENUM, 1640, STR1640, sizeof(ENUM1640), ENUM1640}, // [0] - Trinkwasser  - Legionellenfunktion
{0x313d0738, CAT_TW, VT_DAYS, 1641, STR1641, 0, NULL}, // [Tage ] - Trinkwasser  - Legionellenfkt. Periodisch
{0x313d075e, CAT_TW, VT_WEEKDAY, 1642, STR1642, 0, NULL}, // [0] - Trinkwasser  - Legionellenfkt. Wochentag
{0x313d075a, CAT_TW, VT_HOUR_MINUTES, 1644, STR1644, 0, NULL}, // [hh:mm ] - Trinkwasser  - Legionellenfkt. Zeitpunkt
{0x313d06bc, CAT_TW, VT_TEMP, 1645, STR1645, 0, NULL}, // [°C ] - Trinkwasser  - Legionellenfkt. Sollwert
{0x313d0496, CAT_TW, VT_MINUTES_WORD, 1646, STR1646, 0, NULL}, // [min] - Trinkwasser  - Legionellenfkt. Verweildauer
{0x313d08ab, CAT_TW, VT_ONOFF, 1647, STR1647, 0, NULL}, // [0] - Trinkwasser  - Legionellenfkt. Zirk`pumpe
{0x253d072e, CAT_TW, VT_ENUM, 1660, STR1660, sizeof(ENUM1660), ENUM1660}, // [0] - Trinkwasser  - Zirkulationspumpe Freigabe
{0x253d0689, CAT_TW, VT_ONOFF, 1661, STR1661, 0, NULL}, // [0] - Trinkwasser  - Zirk`pumpe Taktbetrieb
{0x253D077E, CAT_TW, VT_TEMP, 1663, STR1663, 0, NULL}, // [°C ] - Trinkwasser  - Zirkulations Sollwert

// Hx-Pumpe
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2008, STR2008, 0, NULL}, // H1 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2010, STR2010, 0, NULL}, // [  - ] - H1/H3-Pumpe (nur wenn aktiviert)  - H1 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2012, STR2012, 0, NULL}, // [-] - H1/H3-Pumpe (nur wenn aktiviert)  - H1 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2014, STR2014, 0, NULL}, // [  - ] - H1/H3-Pumpe (nur wenn aktiviert)  - H1 Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2015, STR2015, 0, NULL}, // H1 Kälteanforderung
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2033, STR2033, 0, NULL}, // H2 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2035, STR2035, 0, NULL}, // H2 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2037, STR2037, 0, NULL}, // H2 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2039, STR2039, 0, NULL}, // H2 Vorregler / Zubring'pumpe
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2040, STR2040, 0, NULL}, // H2 Kälteanforderung
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2044, STR2044, 0, NULL}, // H3 TWW-Ladevorrang
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2046, STR2046, 0, NULL}, // [  - ] - H1/H3-Pumpe (nur wenn aktiviert)  - H3 Übertemperaturabnahme
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2048, STR2048, 0, NULL}, // [-] - H1/H3-Pumpe (nur wenn aktiviert)  - H3 mit Pufferspeicher
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2050, STR2050, 0, NULL}, // [  - ] - H1/H3-Pumpe (nur wenn aktiviert)  - H3 Vorregler/Zubring`pumpe
{CMD_UNKNOWN, CAT_HXPUMPE, VT_UNKNOWN, 2051, STR2051, 0, NULL}, // H3 Kälteanforderung

// Schwimmbad
{CMD_UNKNOWN, CAT_SCHWIMMBAD, VT_UNKNOWN, 2055, STR2055, 0, NULL}, // Sollwert Solarbeheizung
{CMD_UNKNOWN, CAT_SCHWIMMBAD, VT_UNKNOWN, 2056, STR2056, 0, NULL}, // Sollwert Erzeugerbeheizung
{CMD_UNKNOWN, CAT_SCHWIMMBAD, VT_UNKNOWN, 2065, STR2065, 0, NULL}, // Ladevorrang Solar
{CMD_UNKNOWN, CAT_SCHWIMMBAD, VT_UNKNOWN, 2070, STR2070, 0, NULL}, // Schwimmbadtemp Maximum
{CMD_UNKNOWN, CAT_SCHWIMMBAD, VT_UNKNOWN, 2080, STR2080, 0, NULL}, // Mit Solareinbindung

// Vorregler/Zubringerpumpe
{CMD_UNKNOWN, CAT_VORREGLERPUMPE, VT_UNKNOWN, 2150, STR2150, 0, NULL}, // Vorregler/Zubringerpumpe

// Kessel
{CMD_UNKNOWN, CAT_KESSEL, VT_ONOFF, 2201, STR2201, 0, NULL}, // TODO Thision 2201 Erzeugersperre [Ein/Aus]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2203, STR2203, 0, NULL}, // Freigabe unter Außentemp
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2205, STR2205, 0, NULL}, // Bei Ökobetrieb
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2208, STR2208, 0, NULL}, // Durchladung Pufferspeicher
{0x0d3d092c, CAT_KESSEL, VT_TEMP, 2210, STR2210, 0, NULL}, // [°C ] - Kessel  - Sollwert Minimum
{0x0d3d092b, CAT_KESSEL, VT_TEMP, 2212, STR2212, 0, NULL}, // [°C ] - Kessel  - Sollwert maximum
{CMD_UNKNOWN, CAT_KESSEL, VT_TEMP, 2214, STR2214, 0, NULL}, // TODO Thision 2214 Sollwert Handbetrieb [°C]

{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2220, STR2220, 0, NULL}, // Freigabeintegral Stufe 2
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2221, STR2221, 0, NULL}, // Rückstellintegral Stufe 2
{0x0d3d08eb, CAT_KESSEL, VT_TEMP, 2270, STR2270, 0, NULL}, // [°C ] - Kessel  - Rücklaufsollwert Minimum
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2291, STR2291, 0, NULL}, // Steuerung Bypasspumpe
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2330, STR2330, 0, NULL}, // Leistung Nenn
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2331, STR2331, 0, NULL}, // Leistung Grundstufe
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2340, STR2340, 0, NULL}, // Auto Erz’folge 2 x 1 Kaskade

{CMD_UNKNOWN, CAT_KESSEL, VT_PERCENT, 2440, STR2440, 0, NULL}, // TODO Thision 2440 Gebläse-PWM Hz Maximum [%]
{CMD_UNKNOWN, CAT_KESSEL, VT_PERCENT, 2442, STR2442, 0, NULL}, // TODO Thision 2442 Gebläse-PWM Reglerverzögerung [%]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2444, STR2444, 0, NULL}, // TODO Thision 2444 Leistung Minimum [kW]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2445, STR2445, 0, NULL}, // TODO Thision 2445 Leistung Nenn [kW]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2451, STR2451, 0, NULL}, // TODO Thision 2451 Brennerpausenzeit Minimum [s]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2459, STR2459, 0, NULL}, // TODO Thision 2459 Sperrzeit dynam Schaltdiff [s]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2471, STR2471, 0, NULL}, // TODO Thision 2471 Pumpennachlaufzeit HK's [min]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2540, STR2540, 0, NULL}, // TODO Thision 2540 Proportionalbeiwert Kp TWW [0..9.9375]
{CMD_UNKNOWN, CAT_KESSEL, VT_UNKNOWN, 2543, STR2543, 0, NULL}, // TODO Thision 2543 Proportionalbeiwert Kp HK's [0..9.9375]

// Wärmpumpe
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2800, STR2800, 0, NULL}, // Frostschutz Kondens’pumpe
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2801, STR2801, 0, NULL}, // Steuerung Kondens’pumpe
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2802, STR2802, 0, NULL}, // Vorlaufzeit Kondens’pumpe
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2803, STR2803, 0, NULL}, // Nachlaufzeit Kondens’pumpe
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2805, STR2805, 0, NULL}, // Soll Temp’Spreizung Kond
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2806, STR2806, 0, NULL}, // Max Abweich Spreiz Kondens
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2815, STR2815, 0, NULL}, // Quellentemp Min Wasser
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2816, STR2816, 0, NULL}, // Quellentemp Min Sole
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2817, STR2817, 0, NULL}, // Schaltdiff Quellenschutz
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2818, STR2818, 0, NULL}, // Erhöhung Quellenschutztemp
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2819, STR2819, 0, NULL}, // Vorlaufzeit Quelle
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2820, STR2820, 0, NULL}, // Nachlaufzeit Quelle
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2821, STR2821, 0, NULL}, // Quellen-Anlaufzeit Maximum
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2822, STR2822, 0, NULL}, // Zeit Begr Quelletemp Min
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2840, STR2840, 0, NULL}, // Schaltdiff Rücklauftemp
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2841, STR2841, 0, NULL}, // Verd'laufzeit min einhalten
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2842, STR2842, 0, NULL}, // Verdichterlaufzeit Minimum
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2843, STR2843, 0, NULL}, // Verdichtersillstandszeit Min
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2844, STR2844, 0, NULL}, // Ausschalttemp. max
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2845, STR2845, 0, NULL}, // Reduktion Ausschaltemp Max
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2846, STR2846, 0, NULL}, // Heissgastemp Max
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2852, STR2852, 0, NULL}, // ND-Verzögerung beim Start
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2880, STR2880, 0, NULL}, // Verwendung Elektro-Vorlauf
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2881, STR2881, 0, NULL}, // Sperrzeit Elektro-Vorlauf
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2882, STR2882, 0, NULL}, // Freigabeintegr. Elektro-Vorl
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2883, STR2883, 0, NULL}, // Rückstellintegr. Elektro-Vorl
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2884, STR2884, 0, NULL}, // Freig Elektro-Vorl unter TA
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2886, STR2886, 0, NULL}, // Kompensation Wärmedefizit
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2893, STR2893, 0, NULL}, // Anzahl TWW-Ladeversuche
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2894, STR2894, 0, NULL}, // Verzögerung Drehstr'fehler
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2895, STR2895, 0, NULL}, // Verzögerung Ström'wächter
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2910, STR2910, 0, NULL}, // Freigabe oberhalb TA
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2911, STR2911, 0, NULL}, // Für Pufferzwangsladung
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2912, STR2912, 0, NULL}, // Durchladung Pufferspeicher
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2951, STR2951, 0, NULL}, // Abtaufreigabe unterhalb TA
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2952, STR2952, 0, NULL}, // Schaltdifferenz Abtauen
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2954, STR2954, 0, NULL}, // Verdampfertemp Abtau-Ende
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2963, STR2963, 0, NULL}, // Dauer bis Zwangsabtauen
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2964, STR2964, 0, NULL}, // Abtaudauer Maximal
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2965, STR2965, 0, NULL}, // Abtropfdauer Verdampfer
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 2966, STR2966, 0, NULL}, // Abkühldauer Verdampfer
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 3002, STR3002, 0, NULL}, // Quellentemp min Kühlbetrieb
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 3006, STR3006, 0, NULL}, // Während Verdichterbetrieb
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 3007, STR3007, 0, NULL}, // Im passiven Kühlbetrieb
{CMD_UNKNOWN, CAT_WAERMEPUMPE, VT_UNKNOWN, 3010, STR3010, 0, NULL}, // Drehz max V'lator/Q'Pump

// Kaskade
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3510, STR3510, 0, NULL}, // Führungsstrategie
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3530, STR3530, 0, NULL}, // Freigabeintegral Erz’folge
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3531, STR3531, 0, NULL}, // Rückstellintegral Erz’folge
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3532, STR3532, 0, NULL}, // Wiedereinschaltsperre
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3533, STR3533, 0, NULL}, // Zuschaltverzögerung
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3540, STR3540, 0, NULL}, // Auto Erz’folge Umschaltung
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3541, STR3541, 0, NULL}, // Auto Erz’folge Ausgrenzung
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3544, STR3544, 0, NULL}, // Führender Erzeuger
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3550, STR3550, 0, NULL}, // Anfahrentlast Kaskad'pumpe
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3560, STR3560, 0, NULL}, // Rücklaufsollwert Minimum
{CMD_UNKNOWN, CAT_KASKADE, VT_UNKNOWN, 3590, STR3590, 0, NULL}, // Temp’spreizung Minimum

// Zusatzerzeuger
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3700, STR3700, 0, NULL}, // Freigabe unter Außentemp
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3701, STR3701, 0, NULL}, // Freigabe über Außentemp
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3705, STR3705, 0, NULL}, // Nachlaufzeit
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3720, STR3720, 0, NULL}, // Schaltintegral
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3722, STR3722, 0, NULL}, // Schaltdifferenz Aus
{CMD_UNKNOWN, CAT_ZUSATZERZEUGER, VT_UNKNOWN, 3723, STR3723, 0, NULL}, // Sperrzeit

// Solar
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3810, STR3810, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Temperaturdifferenz Ein
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3811, STR3811, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Temperaturdifferenz Aus
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3812, STR3812, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Ladetemp Min TWW-Speicher
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3813, STR3813, 0, NULL}, // Temp’diff EIN Puffer
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3814, STR3814, 0, NULL}, // Temp’diff AUS Puffer
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3815, STR3815, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Ladetemp Min Puffer
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3816, STR3816, 0, NULL}, // Temp'differenz EIN Sch'bad
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3817, STR3817, 0, NULL}, // Temp'differenz AUS Sch'bad
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3818, STR3818, 0, NULL}, // Ladetemp Min Schwimmbad
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3822, STR3822, 0, NULL}, // Ladevorrang Speicher
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3825, STR3825, 0, NULL}, // Ladezeit relativer Vorrang
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3826, STR3826, 0, NULL}, // Wartezeit relativer Vorrang
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3827, STR3827, 0, NULL}, // Wartezeit Parallelbetrieb
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3828, STR3828, 0, NULL}, // Verzögerung Sekundärpumpe
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3830, STR3830, 0, NULL}, // [min ] - Solar (nur wenn aktiviert)  - Kollektorstartfunktion
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3831, STR3831, 0, NULL}, // [ sec ] - Solar (nur wenn aktiviert)  - Mindestlaufzeit Kollek`pumpe
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3832, STR3832, 0, NULL}, // Kollektorstartfunktion Ein
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3833, STR3833, 0, NULL}, // Kollektorstartfunktion Aus
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3834, STR3834, 0, NULL}, // Kollektorstartfkt Gradient
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3840, STR3840, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Kollektor Frostschutz
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3850, STR3850, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Kollektorüberhitzschutz
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3860, STR3860, 0, NULL}, // [°C ] - Solar (nur wenn aktiviert)  - Verdampfung Waermetaeger
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3870, STR3870, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3871, STR3871, 0, NULL}, // Pumpendrehzahl Maximum
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3880, STR3880, 0, NULL}, // Frostschutzmittel
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3881, STR3881, 0, NULL}, // Frost'mittel Konzentration
{CMD_UNKNOWN, CAT_SOLAR, VT_UNKNOWN, 3884, STR3884, 0, NULL}, // Pumpendurchfluss

// Feststoffkessel
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4102, STR4102, 0, NULL}, // [0] - Feststoffkessel (nur wenn aktiviert) - Sperrt andere Erzeuger
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4110, STR4110, 0, NULL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Sollwert Minimum
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4130, STR4130, 0, NULL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Temperaturdifferenz Ein
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4131, STR4131, 0, NULL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Temperaturdifferenz Aus
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4133, STR4133, 0, NULL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Vergleichstempertatur
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4140, STR4140, 0, NULL}, // Pumpennachlaufzeit
{CMD_UNKNOWN, CAT_FESTSTOFFKESSEL, VT_UNKNOWN, 4141, STR4141, 0, NULL}, // [°C ] - Feststoffkessel (nur wenn aktiviert) - Übertemperaturableitung

// Pufferspeicher
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4708, STR4708, 0, NULL}, // Zwangsladungsollwert Kühlen
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4709, STR4709, 0, NULL}, // Zwangsladungsoll Heizen Min
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4710, STR4710, 0, NULL}, // Zwangsladungsoll Heizen Max
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4711, STR4711, 0, NULL}, // Zwangsladung Zeitpunkt
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4712, STR4712, 0, NULL}, // Zwangsladung Dauer Max
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4720, STR4720, 0, NULL}, // [0] - Pufferspeicher (nur wenn aktiviert)  - Auto Erzeugersperre
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4721, STR4721, 0, NULL}, // [°C ] - Pufferspeicher (nur wenn aktiviert)  - Auto Erzeugersperre SD
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4722, STR4722, 0, NULL}, // [°C ] - Pufferspeicher (nur wenn aktiviert)  - Temp`diff Puffer/Heizkreis
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4724, STR4724, 0, NULL}, // [°C ] - Pufferspeicher (nur wenn aktiviert)  - Min Speichertemp Heizbetrieb
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4739, STR4739, 0, NULL}, // Schichtschutz
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4750, STR4750, 0, NULL}, // [°C ] - Pufferspeicher (nur wenn aktiviert)  - Ladetemperatur Maximum
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4755, STR4755, 0, NULL}, // [°C ] - Pufferspeicher (nur wenn aktiviert)  - Rückkühltemperatur
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4756, STR4756, 0, NULL}, // [-] - Pufferspeicher (nur wenn aktiviert)  - Rückkühlung TWW/HK`s
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4757, STR4757, 0, NULL}, // [0] - Pufferspeicher (nur wenn aktiviert)  - Rückkühlung Kollektor
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4760, STR4760, 0, NULL}, // Ladefühler Elektroeinsatz
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4761, STR4761, 0, NULL}, // Zwangsladung mit Elektro
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4783, STR4783, 0, NULL}, // [0] - Pufferspeicher (nur wenn aktiviert)  - Mit Solareinbindung
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4790, STR4790, 0, NULL}, // Temp'diff EIN Rückl'umlenk
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4791, STR4791, 0, NULL}, // Temp'diff AUS Rückl'umlenk
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4795, STR4795, 0, NULL}, // Vergleichstemp Rückl'umlenk
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4796, STR4796, 0, NULL}, // Wirksinn Rücklaufumlenkung
{CMD_UNKNOWN, CAT_PUFFERSPEICHER, VT_UNKNOWN, 4810, STR4810, 0, NULL}, // Durchladung

// Trinkwasserspeicher
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5010, STR5010, 0, NULL}, // Ladung
{0x253d0720, CAT_TWSPEICHER, VT_TEMP, 5020, STR5020, 0, NULL}, // [°C ] - Trinkwasser-Speicher      - Vorlaufsollwertüberhöhung
{0x253D07C1, CAT_TWSPEICHER, VT_TEMP, 5021, STR5021, 0, NULL}, // [°C ] - Trinkwasser-Speicher      - Umladeüberhöhung
{0x253D087B, CAT_TWSPEICHER, VT_ENUM, 5022, STR5022, sizeof(ENUM5022), ENUM5022}, // [0] - Trinkwasser-Speicher      - Ladeart
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5050, STR5050, 0, NULL}, // Ladetemperatur Maximum
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5055, STR5055, 0, NULL}, // Rückkühltemperatur
{0x313D0713, CAT_TWSPEICHER, VT_ONOFF, 5056, STR5056, 0, NULL}, // [0] - Trinkwasser-Speicher      - Rückkühlung Kessel/HK
{0x313D0714, CAT_TWSPEICHER, VT_ENUM, 5057, STR5057, sizeof(ENUM5057), ENUM5057}, // [0] - Trinkwasser-Speicher      - Rückkühlung Kollektor
{0x253D0728, CAT_TWSPEICHER, VT_ENUM, 5060, STR5060, sizeof(ENUM5060), ENUM5060}, // [0] - Trinkwasser-Speicher      - Elektroeinsatz Betriebsart
{0x253D0688, CAT_TWSPEICHER, VT_ENUM, 5061, STR5061, sizeof(ENUM5061), ENUM5061}, // [0] - Trinkwasser-Speicher      - Elektroeinsatz Freigabe
{0x253D0687, CAT_TWSPEICHER, VT_ENUM, 5062, STR5062, sizeof(ENUM5062), ENUM5062}, // [0] - Trinkwasser-Speicher      - Elektroeinsatz Regelung
{0x253D08CB, CAT_TWSPEICHER, VT_ONOFF, 5085, STR5085, 0, NULL}, // [0] - Trinkwasser-Speicher      - Übertemperaturabnahme
{0x313D07C2, CAT_TWSPEICHER, VT_YESNO, 5090, STR5090, 0, NULL}, // [0] - Trinkwasser-Speicher      - Mit Pufferspeicher
{0x313D07C3, CAT_TWSPEICHER, VT_YESNO, 5092, STR5092, 0, NULL}, // [  - ] - Trinkwasser-Speicher      - Mit Vorregler/Zubring`pumpe
{0x253D0A11, CAT_TWSPEICHER, VT_YESNO, 5093, STR5093, 0, NULL}, // [-] - Trinkwasser-Speicher      - Mit Solareinbindung
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5101, STR5101, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5102, STR5102, 0, NULL}, // Pumpendrehzahl Maximum
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5130, STR5130, 0, NULL}, // Umladestrategie
{CMD_UNKNOWN, CAT_TWSPEICHER, VT_UNKNOWN, 5131, STR5131, 0, NULL}, // Vergleichstemp Umladung

// Trinkwasser Durchl'erhitzer
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_TEMP, 5400, STR5400, 0, NULL},// TODO Thision 5400 Komfortsollwert [°C]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_TEMP, 5406, STR5406, 0, NULL}, // Min Sollw'diff zu Speich'temp
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_TEMP, 5420, STR5420, 0, NULL},// TODO Thision 5420 Vorlauf-Sollwertüberhöhung [°C]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5450, STR5450, 0, NULL},// TODO Thision 5450 Gradient Zapfende [K/s]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5451, STR5451, 0, NULL},// TODO Thision 5451 Gradient Beginn Zapf Komf [K/s]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5452, STR5452, 0, NULL},// TODO Thision 5452 Gradient Beginn Zapfung Hz [K/s]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5480, STR5480, 0, NULL},// TODO Thision 5480 Komfortzeit ohne Hz-Anfo [min]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5481, STR5481, 0, NULL},// TODO Thision 5481 Komfortzeit mit Hz-Anfo [min]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5487, STR5487, 0, NULL},// TODO Thision 5487 Pump'nachlauf Komf [min]
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5530, STR5530, 0, NULL}, // Pumpendrehzahl Minimum
{CMD_UNKNOWN, CAT_DRUCHLERHITZER, VT_UNKNOWN, 5544, STR5544, 0, NULL}, // Antrieb Laufzeit

// Konfiguration
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5700, STR5700, 0, NULL}, // Voreinstellung
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5701, STR5701, 0, NULL}, // TODO Thision 5701 Hydraulisches Schema [2..85 enum?]
{0x053d04c0, CAT_KONFIG, VT_ONOFF, 5710, STR5710, 0, NULL}, // [0] - Konfiguration - Heizkreis 1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5711, STR5711, 0, NULL}, // Kühlkreis 1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5712, STR5712, 0, NULL}, // Verwendung Mischer 1
{0x063d04c0, CAT_KONFIG, VT_ONOFF, 5715, STR5715, 0, NULL}, // [0] - Konfiguration - Heizkreis2
{0x313D071E, CAT_KONFIG, VT_ENUM, 5730, STR5730, sizeof(ENUM5730), ENUM5730}, // [0] - Konfiguration - Trinkwasser-Sensor B3
{0x253D071C, CAT_KONFIG, VT_ENUM, 5731, STR5731, sizeof(ENUM5731), ENUM5731}, // [0] - Konfiguration - Trinkwasser-Stellglied Q3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5732, STR5732, 0, NULL}, // TODO Thision 5732 TWW Pumpenpause Umsch UV [s]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5733, STR5733, 0, NULL}, // TODO Thision 5733 TWW Pumpenpause Verzögerung [s]
{0x053D0727, CAT_KONFIG, VT_ONOFF, 5736, STR5736, 0, NULL}, // [0] - Konfiguration - Trinkwasser Trennschaltung
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5761, STR5761, 0, NULL}, // TODO Thision 5761 Zubringerpumpe Q8 Bit 0-3 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5770, STR5770, 0, NULL}, // Erzeugertyp
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5772, STR5772, 0, NULL}, // Brenner Vorlaufzeit
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5800, STR5800, 0, NULL}, // Wärmequelle
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5807, STR5807, 0, NULL}, // Kälteerzeugung
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5810, STR5810, 0, NULL}, // Spreizung HK bei TA –10 °C
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5840, STR5840, 0, NULL}, // Solarstellglied
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5841, STR5841, 0, NULL}, // Externer Solartauscher
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5870, STR5870, 0, NULL}, // Kombispeicher
{0x053D0497, CAT_KONFIG, VT_ENUM, 5890, STR5890, sizeof(ENUM5890), ENUM5890}, // [-] - Konfiguration - Relaisausgang QX1
{0x053D0498, CAT_KONFIG, VT_ENUM, 5891, STR5891, sizeof(ENUM5891), ENUM5891}, // [-] - Konfiguration - Relaisausgang QX2
{0x053D0587, CAT_KONFIG, VT_ENUM, 5892, STR5892, sizeof(ENUM5892), ENUM5892}, // [-] - Konfiguration - Relaisausgang QX3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5894, STR5894, 0, NULL}, // Relaisausgang QX4
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5895, STR5895, 0, NULL}, // Relaisausgang QX5
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5896, STR5896, 0, NULL}, // Relaisausgang QX6
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5908, STR5908, 0, NULL}, // Funktion Ausgang QX3-Mod
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5909, STR5909, 0, NULL}, // Funktion Ausgang QX4-Mod
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5920, STR5920, 0, NULL}, // TODO Thision 5920 Relaisausgang K2 LMU-Basis Bit 0-7 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_YESNO, 5921, STR5921, 0, NULL}, // TODO Thision 5921 Default K2 auf K1 [Ja/Nein]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5922, STR5922, sizeof(ENUM5922), ENUM5922}, // TODO Thision 5922 Relaisausgang 1 RelCl [enum: ]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5923, STR5923, sizeof(ENUM5923), ENUM5923}, // TODO Thision 5923 Relaisausgang 2 RelCl [s.o.]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5924, STR5924, sizeof(ENUM5924), ENUM5924}, // TODO Thision 5924 Relaisausgang 3 RelCl [s.o.]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5926, STR5926, sizeof(ENUM5926), ENUM5926}, // TODO Thision 5926 Relaisausgang 1 SolCl [s.o.]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5927, STR5927, sizeof(ENUM5927), ENUM5927}, // TODO Thision 5927 Relaisausgang 2 SolCl [s.o.]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5928, STR5928, sizeof(ENUM5928), ENUM5928}, // TODO Thision 5928 Relaisausgang 3 SolCl [s.o.]
{0x053D0567, CAT_KONFIG, VT_ENUM, 5930, STR5930, sizeof(ENUM5930), ENUM5930}, // [-] - Konfiguration - Fühlereingang BX 1
{0x053D0568, CAT_KONFIG, VT_ENUM, 5931, STR5931, sizeof(ENUM5931), ENUM5931}, // [-] - Konfiguration - Fühlereingang BX 2
{0x053D07CA, CAT_KONFIG, VT_ENUM, 5932, STR5932, sizeof(ENUM5932), ENUM5932}, // [-] - Konfiguration - Fühlereingang BX 3
{0x053D07CB, CAT_KONFIG, VT_ENUM, 5933, STR5933, sizeof(ENUM5933), ENUM5933}, // [-] - Konfiguration - Fühlereingang BX 4
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5934, STR5934, 0, NULL}, // Fühlereingang BX5
{0x053D0807, CAT_KONFIG, VT_ENUM, 5950, STR5950, sizeof(ENUM5950), ENUM5950}, // [-] - Konfiguration - Funktion Eingang H1
{0x053D0808, CAT_KONFIG, VT_ENUM, 5951, STR5951, sizeof(ENUM5951), ENUM5951}, // [0] - Konfiguration - Wirksinn Kontakt H1
{0x293D0656, CAT_KONFIG, VT_TEMP, 5952, STR5952, 0, NULL}, // [°C ] - Konfiguration - Minimaler Vorlaufsollwert H1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5953, STR5953, 0, NULL}, // Spannungswert 1 H1
{0x053D079F, CAT_KONFIG, VT_TEMP, 5954, STR5954, 0, NULL}, // [°C ] - Konfiguration - Waermeanforderung 10V H1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5955, STR5955, 0, NULL}, // Spannungswert 2 H1
{0x053D05DC, CAT_KONFIG, VT_PRESSURE, 5956, STR5956, 0, NULL}, // [bar ] - Konfiguration - Druckwer 3.5V H1
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5957, STR5957, sizeof(ENUM5957), ENUM5957}, // TODO Thision 5957 Modemfunktion [enum]
{0x073D0807, CAT_KONFIG, VT_ENUM, 5960, STR5960, sizeof(ENUM5960), ENUM5960}, // [-] - Konfiguration - Funktion Eingang H3
{0x073D0808, CAT_KONFIG, VT_ENUM, 5961, STR5961, sizeof(ENUM5961), ENUM5961}, // [0] - Konfiguration - Wirksinn Kontakt H3
{0x2B3D0656, CAT_KONFIG, VT_TEMP, 5962, STR5962, 0, NULL}, // [°C ] - Konfiguration - Minimaler Vorlaufsollwert H3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5963, STR5963, 0, NULL}, // Spannungswert 1 H3
{0x073D079F, CAT_KONFIG, VT_TEMP, 5964, STR5964, 0, NULL}, // [°C ] - Konfiguration - Waermeanforderung 10V H3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5965, STR5965, 0, NULL}, // Spannungswert 2 H3
{0x073D05DC, CAT_KONFIG, VT_PRESSURE, 5966, STR5966, 0, NULL}, // [bar ] - Konfiguration - Druckwer 3.5V H3
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5970, STR5970, sizeof(ENUM5970), ENUM5970}, // TODO Thision 5970 Konfig Raumthermostat 1 [enum]

{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5971, STR5971, sizeof(ENUM5971), ENUM5971}, // TODO Thision 5971 Konfig Raumthermostat 2 [enum: s.o.]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5973, STR5973, sizeof(ENUM5973), ENUM5973}, // TODO Thision 5973 Funktion Eingang RelCl [enum]

/*
*/
{CMD_UNKNOWN, CAT_KONFIG, VT_TEMP, 5975, STR5975, 0, NULL}, // TODO Thision 5975 Ext. Vorlaufsollwert Maximum [°C?]
{CMD_UNKNOWN, CAT_KONFIG, VT_ENUM, 5978, STR5978, sizeof(ENUM5978), ENUM5978}, // TODO Thision 5978 Funktion Eingang SolCl [enum]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5980, STR5980, 0, NULL}, // Funktion Eingang EX1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5981, STR5981, 0, NULL}, // Wirksinn Eingang EX1
{0x053D07CE, CAT_KONFIG, VT_ENUM, 5982, STR5982, sizeof(ENUM5982), ENUM5982}, // [0] - Konfiguration - Funktion Eingang EX2
{0x053D07D1, CAT_KONFIG, VT_ENUM, 5983, STR5983, sizeof(ENUM5983), ENUM5983}, // [0] - Konfiguration - Wirksinn Eingang EX2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5984, STR5984, 0, NULL}, // Funktion Eingang EX3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5985, STR5985, 0, NULL}, // Wirksinn Eingang EX3
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5986, STR5986, 0, NULL}, // Funktion Eingang EX4
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5987, STR5987, 0, NULL}, // Wirksinn Eingang EX4
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5988, STR5988, 0, NULL}, // Funktion Eingang EX5
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5990, STR5990, 0, NULL}, // Funktion Eingang EX6
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 5992, STR5992, 0, NULL}, // Funktion Eingang EX7
{0x053D07CF, CAT_KONFIG, VT_ENUM, 6014, STR6014, sizeof(ENUM6014), ENUM6014}, // [0] - Konfiguration - Funktion Mischergruppe 1
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6015, STR6015, 0, NULL}, // Funktion Mischergruppe 2
{0x053D0788, CAT_KONFIG, VT_ENUM, 6020, STR6020, sizeof(ENUM6020), ENUM6020}, // [0] - Konfiguration - Funktion Erweiterungsmodul 1
{0x053D0789, CAT_KONFIG, VT_ENUM, 6021, STR6021, sizeof(ENUM6021), ENUM6021}, // [0] - Konfiguration - Funktion Erweiterungsmodul 2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6030, STR6030, 0, NULL}, // Relaisausgang QX21
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6031, STR6031, 0, NULL}, // Relaisausgang QX22
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6032, STR6032, 0, NULL}, // Relaisausgang QX23
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6040, STR6040, 0, NULL}, // Fühlereingang BX21
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6041, STR6041, 0, NULL}, // Fühlereingang BX22
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6046, STR6046, 0, NULL}, // Funktion Eingang H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6047, STR6047, 0, NULL}, // Wirksinn Kontakt H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6048, STR6048, 0, NULL}, // Minimaler Vorlaufsollwert H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6049, STR6049, 0, NULL}, // Spannungswert 1 H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6050, STR6050, 0, NULL}, // Temperaturwert 10V H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6051, STR6051, 0, NULL}, // Spannungswert 2 H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6052, STR6052, 0, NULL}, // Funktionswert 2 H2
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6070, STR6070, 0, NULL}, // Funktion Ausgang UX
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6071, STR6071, 0, NULL}, // Signallogik Ausgang UX
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6072, STR6072, 0, NULL}, // Signal Ausgang UX
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6075, STR6075, 0, NULL}, // Temperaturwert 10V UX
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6089, STR6089, 0, NULL}, // TODO Thision 6089 Mod Pumpe Drehzahlstufen [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6092, STR6092, 0, NULL}, // TODO Thision 6092 Mod Pumpe PWM [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6097, STR6097, 0, NULL}, // Fühlertyp Kollektor
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6098, STR6098, 0, NULL}, // Korrektur Kollektorfühler
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6099, STR6099, 0, NULL}, // Korrektur Kollektorfühler 2
{0x053D05F1, CAT_KONFIG, VT_TEMP, 6100, STR6100, 0, NULL}, // [°C ] - Konfiguration - korrektur Aussenfühler
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6101, STR6101, 0, NULL}, // Fühlertyp Abgastemperatur
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6102, STR6102, 0, NULL}, // Korrektur Abgastemp'fühler
{0x053d0600, CAT_KONFIG, VT_HOURS_SHORT, 6110, STR6110, 0, NULL}, // [h  ] - Konfiguration - Zeitkonstante Gebaeude
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6112, STR6112, 0, NULL}, // TODO Thision 6112 Gradient Raummodell [min/K]
{0x053d05fe, CAT_KONFIG, VT_ONOFF, 6120, STR6120, 0, NULL}, // [0] - Konfiguration - Anlagenfrostschutz
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6128, STR6128, 0, NULL}, // Wärm'anfo unter Außentemp
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6129, STR6129, 0, NULL}, // Wärm'anfo über Außentemp
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6130, STR6130, 0, NULL}, // H1 mit Pufferspeicher
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6131, STR6131, 0, NULL}, // Wärm'anfo bei Ökobetrieb
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6134, STR6134, 0, NULL}, // H2 mit Pufferspeicher
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6135, STR6135, 0, NULL}, // Luftentfeuchter
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6136, STR6136, 0, NULL}, // Luftentfeuchter Freigabe
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6137, STR6137, 0, NULL}, // Luftentfeuchter r. F. EIN
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6138, STR6138, 0, NULL}, // Luftentfeuchter r. F. SD
{0x053D06AB, CAT_KONFIG, VT_YESNO, 6200, STR6200, 0, NULL}, // [0] - Konfiguration - Fühler Speichern
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6201, STR6201, 0, NULL}, // Fühler löschen
{0x053D05D5, CAT_KONFIG, VT_YESNO, 6205, STR6205, 0, NULL}, // [-] - Konfiguration - Parameter zurücksetzen
{0x053D0BD0, CAT_KONFIG, VT_DWORD, 6212, STR6212, 0, NULL}, // [0] - Konfiguration - Kontrollnummer Erzeuger 1
{0x053D0BD1, CAT_KONFIG, VT_DWORD, 6213, STR6213, 0, NULL}, // [0] - Konfiguration - Kontrollnummer Erzeuger 2
{0x053D0BD2, CAT_KONFIG, VT_DWORD, 6215, STR6215, 0, NULL}, // [0] - Konfiguration - Kontrollnummer Speicher
{0x053D0BD3, CAT_KONFIG, VT_DWORD, 6217, STR6217, 0, NULL}, // [0] - Konfiguration - Kontrollnummer Heizkreise
{0x053d000e, CAT_KONFIG, VT_FP1, 6220, STR6220, 0, NULL}, // [0] - Konfiguration - Software- Version LOGON B
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6221, STR6221, 0, NULL}, // TODO Thision 6221 Entwicklungs-Index [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6225, STR6225, 0, NULL}, // TODO Thision 6225 Gerätefamilie [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6226, STR6226, 0, NULL}, // TODO Thision 6226 Gerätevariante [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6227, STR6227, 0, NULL}, // TODO Thision 6227 Objektverzeichnis-Version [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6240, STR6240, 0, NULL}, // TODO Thision 6240 KonfigRg1 Bit 0-7 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6270, STR6270, 0, NULL}, // TODO Thision 6270 KonfigRg4 Bit 0-7 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6300, STR6300, 0, NULL}, // TODO Thision 6300 KonfigRg7 Bit 0-7 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6310, STR6310, 0, NULL}, // TODO Thision 6310 KonfigRg8 Bit 0-7 [?]
{CMD_UNKNOWN, CAT_KONFIG, VT_UNKNOWN, 6330, STR6330, 0, NULL}, // TODO Thision 6330 KonfigRg10 Bit 0-7 [?]

// LPB-System
{0x053D00C9, CAT_LPB, VT_BYTE, 6600, STR6600, 0, NULL}, // [0] - LPB   - Geraeteadresse
{0x053D00CA, CAT_LPB, VT_BYTE, 6601, STR6601, 0, NULL}, // [0] - LPB   - Segmentadresse
{0x053D0071, CAT_LPB, VT_ENUM, 6604, STR6604, sizeof(ENUM6604), ENUM6604}, // [0] - LPB   - Busspeisung Funktion
{0x053D0072, CAT_LPB, VT_ONOFF, 6605, STR6605, 0, NULL}, // [0] - LPB   - Busspeisung Status
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6606, STR6606, 0, NULL}, // TODO Thision 6606 LPB-Konfig. 0 [?]
{0x053D006A, CAT_LPB, VT_YESNO, 6610, STR6610, 0, NULL}, // [0] - LPB   - Anzeige Systemmeldungen
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6612, STR6612, 0, NULL}, // Alarmverzögerung
{0x053D0839, CAT_LPB, VT_ENUM, 6620, STR6620, sizeof(ENUM6620), ENUM6620}, // [  - ] - LPB   - Wirkbereich Umschaltungen
{0x2D3D0611, CAT_LPB, VT_ENUM, 6621, STR6621, sizeof(ENUM6621), ENUM6621}, // [0] - LPB   - Sommerumschaltung
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6623, STR6623, 0, NULL}, // Betriebsartumschaltung
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6624, STR6624, 0, NULL}, // Manuelle Erzeugersperre
{0x253D074A, CAT_LPB, VT_ENUM, 6625, STR6625, sizeof(ENUM6625), ENUM6625}, // [0] - LPB   - Trinkwasserzuordnung
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6627, STR6627, 0, NULL}, // Kälteanforderung
{CMD_UNKNOWN, CAT_LPB, VT_UNKNOWN, 6632, STR6632, 0, NULL}, // TA'grenze ext Erz beachten
{0x053D006D, CAT_LPB, VT_ENUM, 6640, STR6640, sizeof(ENUM6640), ENUM6640}, // [0] - LPB   - Uhrbetrieb
// Codierung unklar: 15.01 -> HEIZ->DISP ANS 6650 Aussentemperatur Lieferant 00 F0 ???
{0x053D009F, CAT_LPB, VT_LPBADDR, 6650, STR6650, 0, NULL}, // [0] - LPB   - Aussentemperatur Lieferant

//Fehler
{CMD_UNKNOWN, CAT_FEHLER, VT_ERRORCODE, 6705, STR6705, 0, NULL}, // TODO Thision 6705 SW Diagnosecode [VT_ERRORCODE?]
{0x053D05D6, CAT_FEHLER, VT_YESNO, 6710, STR6710, 0, NULL}, // [0] - Fehler - Reset Alarmrelais
{CMD_UNKNOWN, CAT_FEHLER, VT_UNKNOWN, 6711, STR6711, 0, NULL}, // Reset Wärmepumpe
{0x213D069D, CAT_FEHLER, VT_MINUTES_SHORT, 6740, STR6740, 0, NULL}, // [min ] - Fehler - Vorlauftemperatur 1 Alarm
{0x223D069D, CAT_FEHLER, VT_MINUTES_SHORT, 6741, STR6741, 0, NULL}, // [min ] - Fehler - Vorlauftemperatur 2 Alarm
{0x113D05DE, CAT_FEHLER, VT_MINUTES_SHORT, 6743, STR6743, 0, NULL}, // [min ] - Fehler - Kesseltemperatur Alarm
{CMD_UNKNOWN, CAT_FEHLER, VT_UNKNOWN, 6745, STR6745, 0, NULL}, // Trinkwasserladung Alarm
{CMD_UNKNOWN, CAT_FEHLER, VT_UNKNOWN, 6746, STR6746, 0, NULL}, // Vorlauftemp Kühlen 1 Alarm
{0x053D06D3, CAT_FEHLER, VT_DATETIME, 6800, STR6800, 0, NULL}, // [  ] - Fehler - Historie 1 Datum/Zeit
{0x053D0814, CAT_FEHLER, VT_ERRORCODE, 6801, STR6801, 0, NULL}, // [  ] - Fehler - Historie 1 Fehlercode
{0x053D06D4, CAT_FEHLER, VT_DATETIME, 6802, STR6802, 0, NULL}, // [  ] - Fehler - Historie 2 Datum/Zeit
{0x053D0815, CAT_FEHLER, VT_ERRORCODE, 6803, STR6803, 0, NULL}, // [  ] - Fehler - Historie 2 Fehlercode
{0x053D06D5, CAT_FEHLER, VT_DATETIME, 6804, STR6804, 0, NULL}, // [  ] - Fehler - Historie 3 Datum/Zeit
{0x053D0816, CAT_FEHLER, VT_ERRORCODE, 6805, STR6805, 0, NULL}, // [  ] - Fehler - Historie 3 Fehlercode
{0x053D06D6, CAT_FEHLER, VT_DATETIME, 6806, STR6806, 0, NULL}, // [  ] - Fehler - Historie 4 Datum/Zeit
{0x053D0817, CAT_FEHLER, VT_ERRORCODE, 6807, STR6807, 0, NULL}, // [  ] - Fehler - Historie 4 Fehlercode
{0x053D06D7, CAT_FEHLER, VT_DATETIME, 6808, STR6808, 0, NULL}, // [  ] - Fehler - Historie 5 Datum/Zeit
{0x053D0818, CAT_FEHLER, VT_ERRORCODE, 6809, STR6809, 0, NULL}, // [  ] - Fehler - Historie 5 Fehlercode
{0x053D06D8, CAT_FEHLER, VT_DATETIME, 6810, STR6810, 0, NULL}, // [  ] - Fehler - Historie 6 Datum/Zeit
{0x053D0819, CAT_FEHLER, VT_ERRORCODE, 6811, STR6811, 0, NULL}, // [  ] - Fehler - Historie 6 Fehlercode
{0x053D06D9, CAT_FEHLER, VT_DATETIME, 6812, STR6812, 0, NULL}, // [  ] - Fehler - Historie 7 Datum/Zeit
{0x053D081A, CAT_FEHLER, VT_ERRORCODE, 6813, STR6813, 0, NULL}, // [  ] - Fehler - Historie 7 Fehlercode
{0x053D06DA, CAT_FEHLER, VT_DATETIME, 6814, STR6814, 0, NULL}, // [  ] - Fehler - Historie 8 Datum/Zeit
{0x053D081B, CAT_FEHLER, VT_ERRORCODE, 6815, STR6815, 0, NULL}, // [  ] - Fehler - Historie 8 Fehlercode
{0x053D06DB, CAT_FEHLER, VT_DATETIME, 6816, STR6816, 0, NULL}, // [  ] - Fehler - Historie 9 Datum/Zeit
{0x053D081C, CAT_FEHLER, VT_ERRORCODE, 6817, STR6817, 0, NULL}, // [  ] - Fehler - Historie 9 Fehlercode
{0x053D06DC, CAT_FEHLER, VT_DATETIME, 6818, STR6818, 0, NULL}, // [  ] - Fehler - Historie 10 Datum/Zeit
{0x053D081D, CAT_FEHLER, VT_ERRORCODE, 6819, STR6819, 0, NULL}, // [  ] - Fehler - Historie 10 Fehlercode
// TODO Thision 6800 Historie 1
// TODO Thision 6805 SW Diagnosecode 1
// TODO Thision 6810 Historie 2
// TODO Thision 6815 SW Diagnosecode 2
{CMD_UNKNOWN, CAT_FEHLER, VT_DATETIME, 6820, STR6820, 0, NULL}, // TODO Thision 6820 Historie 3
{CMD_UNKNOWN, CAT_FEHLER, VT_ERRORCODE, 6825, STR6825, 0, NULL}, // TODO Thision 6825 SW Diagnosecode 3
{CMD_UNKNOWN, CAT_FEHLER, VT_DATETIME, 6830, STR6830, 0, NULL}, // TODO Thision 6830 Historie 4
{CMD_UNKNOWN, CAT_FEHLER, VT_ERRORCODE, 6835, STR6835, 0, NULL}, // TODO Thision 6835 SW Diagnosecode 4
{CMD_UNKNOWN, CAT_FEHLER, VT_DATETIME, 6840, STR6840, 0, NULL}, // TODO Thision 6840 Historie 5
{CMD_UNKNOWN, CAT_FEHLER, VT_ERRORCODE, 6845, STR6845, 0, NULL}, // TODO Thision 6845 SW Diagnosecode 5

// Wartung/Sonderbetrieb
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7001, STR7001, 0, NULL}, // TODO Thision 7001 Meldung [?]
{CMD_UNKNOWN, CAT_WARTUNG, VT_ONOFF, 7007, STR7007, 0, NULL}, // TODO Thision 7007 Anzeige Meldungen [Ein/Aus]
{CMD_UNKNOWN, CAT_WARTUNG, VT_ONOFF, 7010, STR7010, 0, NULL}, // TODO Thision 7010 Quittierung Meldung [Ein/Aus]
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7011, STR7011, 0, NULL}, // TODO Thision 7011 Repetitionszeit Meldung [Tage]
{CMD_UNKNOWN, CAT_WARTUNG, VT_YESNO, 7012, STR7012, 0, NULL}, // TODO Thision 7012 Reset Meldungen 1-6 [Ja/Nein]

{0x053d03f1, CAT_WARTUNG, VT_HOURS_WORD, 7040, STR7040, 0, NULL}, // [h  ] - Wartung/Service   - Brennerstunden Intervall
{0x053d03f3, CAT_WARTUNG, VT_HOURS_WORD, 7041, STR7041, 0, NULL}, // [h  ] - Wartung/Service   - Brennerstunden seit Wartung
{0x053D0C69, CAT_WARTUNG, VT_UINT, 7042, STR7042, 0, NULL}, // [0] - Wartung/Service   - Brennerstarts Intervall
{0x053D05E0, CAT_WARTUNG, VT_UINT, 7043, STR7043, 0, NULL}, // [0] - Wartung/Service   - Brennerstarts seit Wartung
{0x053d05e1, CAT_WARTUNG, VT_MONTHS, 7044, STR7044, 0, NULL}, // [Monate ] - Wartung/Service   - Wartungsintervall
{0x053d05e2, CAT_WARTUNG, VT_MONTHS, 7045, STR7045, 0, NULL}, // [Monate ] - Wartung/Service   - Zeit seit Wartung
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7051, STR7051, 0, NULL}, // TODO Thision 7051 Meldung Ion Strom [?]
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7053, STR7053, 0, NULL}, // Abgastemperaturgrenze
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7054, STR7054, 0, NULL}, // Verzögerung Abgasmeldung
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7070, STR7070, 0, NULL}, // WP Zeitintervall
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7071, STR7071, 0, NULL}, // WP Zeit seit Wartung
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7072, STR7072, 0, NULL}, // Max Starts Verd1 / Betr’Std
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7073, STR7073, 0, NULL}, // Akt Starts Verd1 / Betr’Std
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7074, STR7074, 0, NULL}, // Max Starts Verd2 / Betr’Std
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7075, STR7075, 0, NULL}, // Akt Starts Verd2 / Betr’Std
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7076, STR7076, 0, NULL}, // Spreiz Kondens Max / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7077, STR7077, 0, NULL}, // Akt Spreiz Kondens Max / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7078, STR7078, 0, NULL}, // Spreiz Kondens Min / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7079, STR7079, 0, NULL}, // Akt Spreiz Kondens Min / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7080, STR7080, 0, NULL}, // Spreiz Verdampfer Max / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7081, STR7081, 0, NULL}, // Akt Spreiz Verdampfer Max / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7082, STR7082, 0, NULL}, // Spreiz Verdampfer Min / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7083, STR7083, 0, NULL}, // Akt Spreiz Verdampfer Min / Wo
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7090, STR7090, 0, NULL}, // TWW Speicher Zeitintervall
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7091, STR7091, 0, NULL}, // TWW Speicher seit Wartung
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7092, STR7092, 0, NULL}, // TWW Ladetemp WP Minimum
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7093, STR7093, 0, NULL}, // Akt TWW Ladetemperatur WP
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7119, STR7119, 0, NULL}, // Ökofunktion
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7120, STR7120, 0, NULL}, // Ökobetrieb
{0x0d3d092a, CAT_WARTUNG, VT_ONOFF, 7130, STR7130, 0, NULL}, // [0] - Wartung/Service   - Schornsteinfegerfunktion
{0x053d0075, CAT_WARTUNG, VT_ONOFF, 7140, STR7140, 0, NULL}, // [0] - Wartung/Service   - Handbetrieb
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7141, STR7141, 0, NULL}, // Notbetrieb
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7142, STR7142, 0, NULL}, // Notbetrieb Funktionsstart
{CMD_UNKNOWN, CAT_WARTUNG, VT_ONOFF, 7143, STR7143, 0, NULL}, // TODO Thision 7143 Reglerstoppfunktion [Ein/Aus]
{CMD_UNKNOWN, CAT_WARTUNG, VT_PERCENT, 7145, STR7145, 0, NULL}, // TODO Thision 7145 Reglerstopp Sollwert [%]
{CMD_UNKNOWN, CAT_WARTUNG, VT_ONOFF, 7146, STR7146, 0, NULL}, // TODO Thision 7146 Entlüftungsfunktion [Ein/Aus]
{0x053D0528, CAT_WARTUNG, VT_TEMP, 7150, STR7150, 0, NULL}, // [ °C ] - Wartung/Service   - Simulation Aussentemperatur
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7152, STR7152, 0, NULL}, // Abtauen auslösen
{CMD_UNKNOWN, CAT_WARTUNG, VT_UNKNOWN, 7160, STR7160, 0, NULL}, // Reset Begrenzungszeiten
{0x053D06E8, CAT_WARTUNG, VT_STRING, 7170, STR7170, 0, NULL}, // [0] - Wartung/Service   - Telefon Kundendienst

// Ein-/Ausgangstest
{0x053D0073, CAT_IOTEST, VT_ENUM, 7700, STR7700, sizeof(ENUM7700), ENUM7700}, // [0] - Ein-/Ausgangstest - Relaistest
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7705, STR7705, 0, NULL}, // Mod'sollwert QX3 Relaistest
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7708, STR7708, 0, NULL}, // Modulationssignal QX3
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7710, STR7710, 0, NULL}, // Ausgangstest UX
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7711, STR7711, 0, NULL}, // Spannungssignal UX
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7714, STR7714, 0, NULL}, // PWM-Signal P1
{0x053D0470, CAT_IOTEST, VT_TEMP, 7730, STR7730, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Aussentemperatur B9
{0x053D08C5, CAT_IOTEST, VT_TEMP, 7732, STR7732, 0, NULL}, // [°C ] - Ein-/Ausgangstest - vorlauftemperatur B1
{0x053D08C6, CAT_IOTEST, VT_TEMP, 7734, STR7734, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Vorlauftemperatur B12
{0x053D0462, CAT_IOTEST, VT_TEMP, 7750, STR7750, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Trinkwassertemperatur B3
{0x053D0468, CAT_IOTEST, VT_TEMP, 7760, STR7760, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Kesseltemperatur B2
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7770, STR7770, 0, NULL}, // Vorlauftemperatur WP B21
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7771, STR7771, 0, NULL}, // Rücklauftemperatur WP B71
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7772, STR7772, 0, NULL}, // Heissgastemperatur B81
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7775, STR7775, 0, NULL}, // Quelle Eintrittstemp B91
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7777, STR7777, 0, NULL}, // Fühlertemperatur B92, B84
{0x053D056B, CAT_IOTEST, VT_TEMP, 7820, STR7820, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemperatur BX1
{0x053D056C, CAT_IOTEST, VT_TEMP, 7821, STR7821, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemperatur BX2
{0x053D0791, CAT_IOTEST, VT_TEMP, 7822, STR7822, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemperatur BX3
{0x053D0792, CAT_IOTEST, VT_TEMP, 7823, STR7823, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemperatur BX4
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7824, STR7824, 0, NULL}, // Fühlertemperatur BX5
{0x053D0793, CAT_IOTEST, VT_TEMP, 7830, STR7830, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemp. BX21 Modul 1
{0x053D0799, CAT_IOTEST, VT_TEMP, 7831, STR7831, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemp. BX22 Modul 1
{0x053D079A, CAT_IOTEST, VT_TEMP, 7832, STR7832, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemp. BX21 Modul 2
{0x053D079B, CAT_IOTEST, VT_TEMP, 7833, STR7833, 0, NULL}, // [°C ] - Ein-/Ausgangstest - Fühlertemp. BX22 Modul 2
{0x053D082F, CAT_IOTEST, VT_VOLTAGE, 7840, STR7840, 0, NULL}, // [V ] - Ein-/Ausgangstest - Spannungssignal H1
{0x053D0809, CAT_IOTEST, VT_CLOSEDOPEN, 7841, STR7841, 0, NULL}, // [0] - Ein-/Ausgangstest - Kontaktzustand H1
{CMD_UNKNOWN, CAT_IOTEST, VT_VOLTAGE, 7845, STR7845, 0, NULL}, // [V ] - Ein-/Ausgangstest - Spannungssignal H2
{CMD_UNKNOWN, CAT_IOTEST, VT_CLOSEDOPEN, 7846, STR7846, 0, NULL}, // [0] - Ein-/Ausgangstest - Kontaktzustand H2
{0x073D082F, CAT_IOTEST, VT_VOLTAGE, 7854, STR7854, 0, NULL}, // Spannungssignal H3
{0x073D0809, CAT_IOTEST, VT_CLOSEDOPEN, 7855, STR7855, 0, NULL}, // Kontaktzustand H3
{0x053D03F6, CAT_IOTEST, VT_VOLTAGE, 7870, STR7870, 0, NULL}, // [V] - Ein-/Ausgangstest - Brennerstörung S3
{0x053D03F5, CAT_IOTEST, VT_VOLTAGE, 7881, STR7881, 0, NULL}, // [V] - Ein-/Ausgangstest - 1. Brennerstufe E1
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7889, STR7889, 0, NULL}, // Niederdruckwächter E9
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7890, STR7890, 0, NULL}, // Hochdruckwächter E10
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7891, STR7891, 0, NULL}, // Wickl’schutz Verdicht 1 E11
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7911, STR7911, 0, NULL}, // Eingang EX 1
{0x053D03FC, CAT_IOTEST, VT_VOLTAGE, 7912, STR7912, 0, NULL}, // [V] - Ein-/Ausgangstest - Eingang EX2
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7913, STR7913, 0, NULL}, // Eingang EX 3
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7914, STR7914, 0, NULL}, // Eingang EX 4
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7915, STR7915, 0, NULL}, // Eingang EX 5
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7916, STR7916, 0, NULL}, // Eingang EX 6
{CMD_UNKNOWN, CAT_IOTEST, VT_UNKNOWN, 7917, STR7917, 0, NULL}, // Eingang EX 7

//Status
{0x053d07a3, CAT_STATUS, VT_ENUM, 8000, STR8000, sizeof(ENUM8000), ENUM8000}, // [ ] - Status  - Status Heizkreis 1
{0x053d07a5, CAT_STATUS, VT_ENUM, 8001, STR8001, sizeof(ENUM8001), ENUM8001}, // [ ] - Status  - Status Heizkreis 2
{0x053D07A7, CAT_STATUS, VT_ENUM, 8002, STR8002, sizeof(ENUM8002), ENUM8002}, // [ ] - Status  - Status Heizkreis P
{0x053d07a1, CAT_STATUS, VT_ENUM, 8003, STR8003, sizeof(ENUM8003), ENUM8003}, // [] - Status  - Status Trinkwasser
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8004, STR8004, 0, NULL}, // Status Kühlkreis 1
{0x053d07a9, CAT_STATUS, VT_ENUM, 8005, STR8005, sizeof(ENUM8005), ENUM8005}, // [] - Status  - Status Kessel
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8006, STR8006, 0, NULL}, // Status Wärmepumpe
{0x053d07ad, CAT_STATUS, VT_ENUM, 8007, STR8007, sizeof(ENUM8007), ENUM8007}, // [] - Status  - Status Solar
{0x053D0A08, CAT_STATUS, VT_ENUM, 8008, STR8008, sizeof(ENUM8008), ENUM8008}, // [] - Status  - Status Feststoffkessel
{0x053D07AB, CAT_STATUS, VT_ENUM, 8010, STR8010, sizeof(ENUM8010), ENUM8010}, // [] - Status  - Status Pufferspeicher
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8011, STR8011, 0, NULL}, // Status Schwimmbad
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8022, STR8022, 0, NULL}, // Status Zusatzerzeuger
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8050, STR8050, 0, NULL}, // Zeitstemper Statushistorie 1
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8051, STR8051, 0, NULL}, // Statuscode Statushistorie 1
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8052, STR8052, 0, NULL}, // Zeitstemper Statushistorie 2
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8053, STR8053, 0, NULL}, // Statuscode Statushistorie 2
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8054, STR8054, 0, NULL}, // Zeitstemper Statushistorie 3
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8055, STR8055, 0, NULL}, // Statuscode Statushistorie 3
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8056, STR8056, 0, NULL}, // Zeitstemper Statushistorie 4
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8057, STR8057, 0, NULL}, // Statuscode Statushistorie 4
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8058, STR8058, 0, NULL}, // Zeitstemper Statushistorie 5
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8059, STR8059, 0, NULL}, // Statuscode Statushistorie 5
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8060, STR8060, 0, NULL}, // Zeitstemper Statushistorie 6
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8061, STR8061, 0, NULL}, // Statuscode Statushistorie 6
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8062, STR8062, 0, NULL}, // Zeitstemper Statushistorie 7
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8063, STR8063, 0, NULL}, // Statuscode Statushistorie 7
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8064, STR8064, 0, NULL}, // Zeitstemper Statushistorie 8
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8065, STR8065, 0, NULL}, // Statuscode Statushistorie 8
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8066, STR8066, 0, NULL}, // Zeitstemper Statushistorie 9
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8067, STR8067, 0, NULL}, // Statuscode Statushistorie 10
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8068, STR8068, 0, NULL}, // Zeitstemper Statushistorie 10
{CMD_UNKNOWN, CAT_STATUS, VT_UNKNOWN, 8069, STR8069, 0, NULL}, // Statuscode Statushistorie 10

// Diagnose Kaskade
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8100, STR8100, 0, NULL}, // Priorität / Status Erzeuger 1
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8102, STR8102, 0, NULL}, // Priorität / Status Erzeuger 2
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8104, STR8104, 0, NULL}, // Priorität / Status Erzeuger 3
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8106, STR8106, 0, NULL}, // Priorität / Status Erzeuger 4
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8108, STR8108, 0, NULL}, // Priorität / Status Erzeuger 5
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8110, STR8110, 0, NULL}, // Priorität / Status Erzeuger 6
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8112, STR8112, 0, NULL}, // Priorität / Status Erzeuger 7
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8114, STR8114, 0, NULL}, // Priorität / Status Erzeuger 8
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8116, STR8116, 0, NULL}, // Priorität / Status Erzeuger 9
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8118, STR8118, 0, NULL}, // Priorität / Status Erzeuger 10
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8120, STR8120, 0, NULL}, // Priorität / Status Erzeuger 11
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8122, STR8122, 0, NULL}, // Priorität / Status Erzeuger 12
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8124, STR8124, 0, NULL}, // Priorität / Status Erzeuger 13
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8126, STR8126, 0, NULL}, // Priorität / Status Erzeuger 14
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8128, STR8128, 0, NULL}, // Priorität / Status Erzeuger 15
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8130, STR8130, 0, NULL}, // Priorität / Status Erzeuger 16
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8138, STR8138, 0, NULL}, // Kaskadenvorlauftemperatur
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8139, STR8139, 0, NULL}, // Kaskadenvorlaufsollwert
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8140, STR8140, 0, NULL}, // Kaskadenrücklauftemperatur
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8141, STR8141, 0, NULL}, // Kaskadenrücklaufsollwert
{CMD_UNKNOWN, CAT_DIAG_KASKADE, VT_UNKNOWN, 8150, STR8150, 0, NULL}, // Erz'folge Umschalt aktuell


//Diagnose Erzeuger
{0x053D09A0, CAT_DIAG_ERZEUGER, VT_ONOFF, 8300, STR8300, 0, NULL}, // [0] - Diagnose Erzeuger - 1. Brennerstufe T2
{0x053D09A1, CAT_DIAG_ERZEUGER, VT_ONOFF, 8301, STR8301, 0, NULL}, // [0] - Diagnose Erzeuger - 2. Brennerstufe T8
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8308, STR8308, 0, NULL}, // Drehzahl Kesselpumpe
{0x0d3d0519, CAT_DIAG_ERZEUGER, VT_TEMP, 8310, STR8310, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kesseltemperatur
{0x0d3d0923, CAT_DIAG_ERZEUGER, VT_TEMP, 8311, STR8311, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kesselsollwert
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8312, STR8312, 0, NULL}, // Kesselschaltpunkt
{0x113d051a, CAT_DIAG_ERZEUGER, VT_TEMP, 8314, STR8314, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kesselrücklauftemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8315, STR8315, 0, NULL}, // Kesselrücklaufsollwert
{0x053D051D, CAT_DIAG_ERZEUGER, VT_TEMP, 8316, STR8316, 0, NULL}, // [°C ] - Diagnose Erzeuger - Abgastemperatur
{0x053D051C, CAT_DIAG_ERZEUGER, VT_TEMP, 8318, STR8318, 0, NULL}, // [°C ] - Diagnose Erzeuger - Abgastemperatur Maximum
{0x113D305D, CAT_DIAG_ERZEUGER, VT_PERCENT, 8324, STR8324, 0, NULL}, // TODO Thision Diagnose Erzeuger - Gebläsedrehzahl
{0x113D305F, CAT_DIAG_ERZEUGER, VT_PERCENT, 8326, STR8326, 0, NULL}, // TODO Thision Brennermodulation 
{0x113D3063, CAT_DIAG_ERZEUGER, VT_PRESSURE, 8327, STR8327, 0, NULL}, // TODO Thision Wasserdruck
{0x093D3034, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8328, STR8328, 0, NULL}, // TODO Thision Betriebsanzeige FA [?] TODO Thision
{0x153D2FF0, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8329, STR8329, 0, NULL}, // TODO Thision Ionisationsstrom [uA?] TODO Thision
{0x0D3D093B, CAT_DIAG_ERZEUGER, VT_HOURS, 8330, STR8330, 0, NULL}, // [h  ] - Diagnose Erzeuger - Betriebstunden 1.Stufe
{0x053D08A5, CAT_DIAG_ERZEUGER, VT_DWORD, 8331, STR8331, 0, NULL}, // [0] - Diagnose Erzeuger - Startzaehler 1.Stufe
{0x0D3D093D, CAT_DIAG_ERZEUGER, VT_HOURS, 8332, STR8332, 0, NULL}, // [h  ] - Diagnose Erzeuger - Betriebsstunden 2. Stufe
{0x053D08A6, CAT_DIAG_ERZEUGER, VT_DWORD, 8333, STR8333, 0, NULL}, // [0] - Diagnose Erzeuger - Startzaehler 2.Stufe
{0x093D3036, CAT_DIAG_ERZEUGER, VT_HOURS, 8336, STR8336, 0, NULL}, // TODO Thision Betriebsstunden Brenner
{0x093D3035, CAT_DIAG_ERZEUGER, VT_DWORD, 8337, STR8337, 0, NULL}, // TODO Thision Startzähler Brenner
{0x193D2FEB, CAT_DIAG_ERZEUGER, VT_HOURS, 8338, STR8338, 0, NULL}, // TODO Thision Betriebsstunden Heizbetrieb
{0x193D2FEC, CAT_DIAG_ERZEUGER, VT_HOURS, 8339, STR8339, 0, NULL}, // TODO Thision Betriebsstunden TWW
{0x193D2FED, CAT_DIAG_ERZEUGER, VT_HOURS, 8340, STR8340, 0, NULL}, // TODO Thision Betriebsstunden Zonen
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8400, STR8400, 0, NULL}, // Verdichter 1 K1
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8401, STR8401, 0, NULL}, // Verdichter 2 K2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8402, STR8402, 0, NULL}, // Elektroeinsatz 1 Vorlauf
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8403, STR8403, 0, NULL}, // Elektroeinsatz 2 Vorlauf
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8404, STR8404, 0, NULL}, // Quellenpu Q8 / Ventilat K19
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8405, STR8405, 0, NULL}, // Drehzahl Quellenpumpe
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8406, STR8406, 0, NULL}, // Konendastorpumpe Q9
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8410, STR8410, 0, NULL}, // Rücklauftemperatur WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8411, STR8411, 0, NULL}, // Sollwert WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8412, STR8412, 0, NULL}, // Vorlauftemperatur WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8415, STR8415, 0, NULL}, // Heissgastemperatur 1
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8416, STR8416, 0, NULL}, // Heissgastemperatur Max
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8417, STR8417, 0, NULL}, // Heissgastemperatur 2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8420, STR8420, 0, NULL}, // Kältemitteltemperatur flüssig
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8425, STR8425, 0, NULL}, // Temp’spreizung Kondensator
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8426, STR8426, 0, NULL}, // Temp’spreizung Verdampfer
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8427, STR8427, 0, NULL}, // Quelle Eintrittstemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8428, STR8428, 0, NULL}, // Quelle Eintritt Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8429, STR8429, 0, NULL}, // Quelle Austrittstemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8430, STR8430, 0, NULL}, // Quelle Austritt Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8440, STR8440, 0, NULL}, // Rest Stufe 1 Stillst’zeit Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8441, STR8441, 0, NULL}, // Rest Stufe 2 Stillst’zeit Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8442, STR8442, 0, NULL}, // Rest Stufe 1 Laufzeit Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8443, STR8443, 0, NULL}, // Rest Stufe 2 Laufzeit Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8444, STR8444, 0, NULL}, // Restzeit Begr Quelle TempMin
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8446, STR8446, 0, NULL}, // Verdichterfolge
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8450, STR8450, 0, NULL}, // Betr’stunden Verdichter 1
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8451, STR8451, 0, NULL}, // Startzähler Verdichter 1
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8452, STR8452, 0, NULL}, // Betr’stunden Verdichter 2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8453, STR8453, 0, NULL}, // Startzähler Verdichter 2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8454, STR8454, 0, NULL}, // Sperrdauer WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8455, STR8455, 0, NULL}, // Zähler Anzahl Sperren WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8456, STR8456, 0, NULL}, // Betr’stunden Elektro Vorl
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8457, STR8457, 0, NULL}, // Startzähler Elektro Vorlauf
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8469, STR8469, 0, NULL}, // Drehzahl Ventilator
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8470, STR8470, 0, NULL}, // Ventilator K19
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8471, STR8471, 0, NULL}, // Prozessumkehrventil
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8475, STR8475, 0, NULL}, // Verdampfertemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8477, STR8477, 0, NULL}, // Temp'diff Abtauen Istwert
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8478, STR8478, 0, NULL}, // Temp'diff Abtauen Sollwert
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8480, STR8480, 0, NULL}, // Restzeit Abtausperrung
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8481, STR8481, 0, NULL}, // Restzeit Zwangsabtauen
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8482, STR8482, 0, NULL}, // Restzeit Abtaustabilisierung
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8485, STR8485, 0, NULL}, // Anzahl Abtauversuche
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8487, STR8487, 0, NULL}, // Status Abtauen WP
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8505, STR8505, 0, NULL}, // Drehzahl Kollektorpumpe 1
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8506, STR8506, 0, NULL}, // Drehzahl Solarpump ext.Tau
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8507, STR8507, 0, NULL}, // Drehzahl Solarpumpe Puffer
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8508, STR8508, 0, NULL}, // Drehzahl Solarpump Sch'bad
{0x493d052a, CAT_DIAG_ERZEUGER, VT_TEMP, 8510, STR8510, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kollektortemperatur 1
{0x493D053F, CAT_DIAG_ERZEUGER, VT_TEMP, 8511, STR8511, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kollektortemperatur 1 Max
{0x493D0718, CAT_DIAG_ERZEUGER, VT_TEMP, 8512, STR8512, 0, NULL}, // [°C ] - Diagnose Erzeuger - Kollektortemperatur 1Min
{0x493D053B, CAT_DIAG_ERZEUGER, VT_TEMP, 8513, STR8513, 0, NULL}, // [°C ] - Diagnose Erzeuger - dT Kollektor 1/TWW
{0x493D053C, CAT_DIAG_ERZEUGER, VT_TEMP, 8514, STR8514, 0, NULL}, // [°C ] - Diagnose Erzeuger - dt Kollektor 1/Puffer
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8515, STR8515, 0, NULL}, // dT Kollektor 1 / Schwimmbad
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8519, STR8519, 0, NULL}, // Solarvorlauftemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8520, STR8520, 0, NULL}, // Solarrücklauftemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8526, STR8526, 0, NULL}, // Tagesertrag Solarenergie
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8527, STR8527, 0, NULL}, // Gesamtertrag Solarenergie
{0x493d0893, CAT_DIAG_ERZEUGER, VT_HOURS, 8530, STR8530, 0, NULL}, // [h  ] - Diagnose Erzeuger - Betr`stunden Solarertrag
{0x493D0717, CAT_DIAG_ERZEUGER, VT_HOURS, 8531, STR8531, 0, NULL}, // [h  ] - Diagnose Erzeuger - Betr`stunden Kollektor`überhitz
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8543, STR8543, 0, NULL}, // Drehzahl Kollektorpumpe 2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8547, STR8547, 0, NULL}, // Kollektortemperatur 2
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8548, STR8548, 0, NULL}, // Kollektortemperatur 2 Max
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8549, STR8549, 0, NULL}, // Kollektortemperatur 2 Min
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8550, STR8550, 0, NULL}, // dT Kollektor 2 / TWW
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8551, STR8551, 0, NULL}, // dT Kollektor 2 / Puffer
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8552, STR8552, 0, NULL}, // dT Kollektor 2 / Schwimmbad
{0x513D052E, CAT_DIAG_ERZEUGER, VT_TEMP, 8560, STR8560, 0, NULL}, // [°C ] - Diagnose Erzeuger - Feststoffkesseltemperatur
{CMD_UNKNOWN, CAT_DIAG_ERZEUGER, VT_UNKNOWN, 8570, STR8570, 0, NULL}, // Betr'std Feststoffkessel

// Diagnose Verbraucher
{0x053d0521, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8700, STR8700, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Aussentemperatur
{0x053D056F, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8701, STR8701, 0, NULL}, // Außentemperatur Minimum
{0x053D056E, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8702, STR8702, 0, NULL}, // Außentemperatur Maximum
{0x053d05f0, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8703, STR8703, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Aussentemperatur gedaempft
{0x053d05f2, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8704, STR8704, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Aussentemperatur gemischt
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8720, STR8720, 0, NULL}, // Relative Raumfeuchte
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8721, STR8721, 0, NULL}, // Raumtemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8722, STR8722, 0, NULL}, // Taupunkttemperatur
{0x053D09A5, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8730, STR8730, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreispumpe Q2
{0x053D09A6, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8731, STR8731, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreismischer Auf Y1
{0x053D09A7, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8732, STR8732, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreismischer Zu Y2
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8735, STR8735, 0, NULL}, // Drehzahl Heizkreispumpe 1
{0x2d3d051e, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8740, STR8740, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumtemperatur 1
{0x2d3d0593, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8741, STR8741, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumsollwert 1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8742, STR8742, 0, NULL}, // TODO Thision 8742 Raumtemperatur 1 Modell [°C]
{0x213d0518, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8743, STR8743, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlauftemperatur 1 Alarm
{0x213d0667, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8744, STR8744, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlaufsollwert 1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_PERCENT, 8750, STR8750, 0, NULL}, // TODO Thision 8750 Mod Pumpe Sollwert [%]
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8751, STR8751, 0, NULL}, // Kühlkreispumpe Q24
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8752, STR8752, 0, NULL}, // Kühlkreismischer Auf Y23
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8753, STR8753, 0, NULL}, // Kühlkreismischer Zu Y24
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8754, STR8754, 0, NULL}, // Umlenkventil Kühlen Y21
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8756, STR8756, 0, NULL}, // Vorlauftemperatur Kühlen 1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8757, STR8757, 0, NULL}, // Vorlaufsollwert Kühlen1
{0x053D09A8, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8760, STR8760, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreispumpe Q6
{0x053D09A9, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8761, STR8761, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreismischer Auf Y5
{0x053D09AA, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8762, STR8762, 0, NULL}, // [0] - Diagnose Verbraucher  - Heizkreismischer Zu Y6
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8765, STR8765, 0, NULL}, // Drehzahl Heizkreispumpe 2
{0x2e3d051e, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8770, STR8770, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumtemperatur 2
{0x2e3d0593, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8771, STR8771, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumsollwert 2
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8772, STR8772, 0, NULL}, // TODO Thision 8772 Raumtemperatur 2 Modell [°C]
{0x223d0518, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8773, STR8773, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlauftemperatur 2
{0x223d0667, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8774, STR8774, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlaufsollwert 2
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8795, STR8795, 0, NULL}, //  Drehzahl Heizkreispumpe P
{0x2F3D051E, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8800, STR8800, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumtemperatur P
{0x2F3D0593, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8801, STR8801, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Raumsollwert P
{0x233D0667, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8803, STR8803, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlaufsol wert P
{0x053D09A3, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 8820, STR8820, 0, NULL}, // [0] - Diagnose Verbraucher  - Trinkwasserpumpe Q3
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8821, STR8821, 0, NULL}, // Elektroeinsatz TWW K6
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8825, STR8825, 0, NULL}, // Drehzahl Trinkwasserpumpe
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8826, STR8826, 0, NULL}, // Drehzahl TWW Zw'kreispumpe
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8827, STR8827, 0, NULL}, // Drehzahl Dl'erhitzerpumpe
{0x313d052f, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8830, STR8830, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Trinkwassertemperatur 1
{0x313d074b, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8831, STR8831, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Trinkwassersollwert
{0x313d0530, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8832, STR8832, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Trinkwassertemperatur 2
{0x253D077D, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8835, STR8835, 0, NULL}, // [°C ] - Diagnose Verbraucher  - TWW Zirkulationstemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8836, STR8836, 0, NULL}, // TWW Ladetemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8840, STR8840, 0, NULL}, // Betr’stunden TWW-Pumpe
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8841, STR8841, 0, NULL}, // Startzähler TWW-Pumpe
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8842, STR8842, 0, NULL}, // Betr’stunden Elektro TWW
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8843, STR8843, 0, NULL}, // Startzähler Elektro TWW
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8850, STR8850, 0, NULL}, // TWW Vorreglertemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8851, STR8851, 0, NULL}, // TWW Vorreglersollwert
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8852, STR8852, 0, NULL}, // TWW Durchl'erhitzertemp
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8853, STR8853, 0, NULL}, // TWW Durchl'erhitzersollwert
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8900, STR8900, 0, NULL}, // Schwimmbadtemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8901, STR8901, 0, NULL}, // Schwimmbadsollwert
{0x053D08C7, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8930, STR8930, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorreglertemperatur
{0x053D08C8, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8931, STR8931, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorreglersollwert
{0x053D051F, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8950, STR8950, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Schienenvorlauftemperatur
{0x053D0783, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8951, STR8951, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Schienenvorlaufsollwert
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8952, STR8952, 0, NULL}, // Schienenrücklauftemperatur
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8957, STR8957, 0, NULL}, // Schienenvorl'sollwert Kälte
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8962, STR8962, 0, NULL}, // Leistungssollwert Schiene
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8970, STR8970, 0, NULL}, // Elektroeinsatz Puffer
{0x053d0534, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8980, STR8980, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Pufferspeichertemperatur 1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8981, STR8981, 0, NULL}, // Pufferspeichersollwert
{0x053D0535, CAT_DIAG_VERBRAUCHER, VT_TEMP, 8982, STR8982, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Pufferspeichertemperatur 2
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8983, STR8983, 0, NULL}, // Pufferspeichertemperatur 3
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8990, STR8990, 0, NULL}, // Betr’stunden Elektro Puffer
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 8991, STR8991, 0, NULL}, // Startzähler Elektro Puffer
{0x053D080C, CAT_DIAG_VERBRAUCHER, VT_TEMP, 9000, STR9000, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlaufsollwert H1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_TEMP, 9001, STR9001, 0, NULL}, // [°C ] - Diagnose Verbraucher  - Vorlaufsollwert H2
{0x073D080C, CAT_DIAG_VERBRAUCHER, VT_TEMP, 9004, STR9004, 0, NULL}, // Vorlaufsollwert H3
{0x053D0805, CAT_DIAG_VERBRAUCHER, VT_PRESSURE_WORD, 9005, STR9005, 0, NULL}, // [bar ] - Diagnose Verbraucher  - Wasserdruck H1
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_PRESSURE_WORD, 9006, STR9006, 0, NULL}, // [bar ] - Diagnose Verbraucher  - Wasserdruck H2
{0x073D0805, CAT_DIAG_VERBRAUCHER, VT_PRESSURE_WORD, 9009, STR9009, 0, NULL}, // [bar ] - Diagnose Verbraucher  - Wasserdruck H3
{0x053D09BA, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9031, STR9031, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX1
{0x053D09BB, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9032, STR9032, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX2
{0x053D09BC, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9033, STR9033, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX3
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 9034, STR9034, 0, NULL}, // Relaisausgang QX4
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 9035, STR9035, 0, NULL}, // Relaisausgang QX5
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 9036, STR9036, 0, NULL}, // Relaisausgang QX6
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 9037, STR9037, 0, NULL}, // Relaisausgang QX7
{CMD_UNKNOWN, CAT_DIAG_VERBRAUCHER, VT_UNKNOWN, 9038, STR9038, 0, NULL}, // Relaisausgang QX8
{0x053D09F6, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9050, STR9050, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX21 Modul 1
{0x053D09F7, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9051, STR9051, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX22 Modul 1
{0x053D09F8, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9052, STR9052, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX23 Modul 1
{0x053D09F9, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9053, STR9053, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX21 Modul 2
{0x053D09FA, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9054, STR9054, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX22 Modul 2
{0x053D09FB, CAT_DIAG_VERBRAUCHER, VT_ONOFF, 9055, STR9055, 0, NULL}, // [0] - Diagnose Verbraucher  - Relaisausgang QX23 Modul 2

// Feuerungsautomat
{0x2d3d3037, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9500, STR9500, 0, NULL}, //  Vorlüftzeit
{0x213d3038, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9502, STR9502, 0, NULL}, //  Gebl'ansteuerung Vorlüftung [%]
{0x213d300f, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9504, STR9504, 0, NULL}, //  Solldrehzahl Vorlüftung [rpm]
{0x0d3d3048, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9510, STR9510, 0, NULL}, //  Gebl'ansteuerung Zündung [%]
{0x0d3d2fc9, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9512, STR9512, 0, NULL}, //  Solldrehzahl Zündung [rpm]
{0x0d3d3049, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9520, STR9520, 0, NULL}, //  Gebl'ansteuerung Betrieb. Min [%]
{0x0d3d304a, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9522, STR9522, 0, NULL}, //  Gebl'ansteuerung Betrieb. Max [%]
{0x0d3d2fca, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9524, STR9524, 0, NULL}, //  Solldrehzahl Betrieb Min [rpm]
{0x0d3d2fcb, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9527, STR9527, 0, NULL}, //  Solldrehzahl Betrieb Max [rpm]
{0x2d3d304c, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9540, STR9540, 0, NULL}, //  Nachlüftzeit
{CMD_UNKNOWN, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9550, STR9550, 0, NULL}, // TODO Thision 9550 Gebl'ansteuerung Stillstand [%]
{0x253d2fe8, CAT_FEUERUNGSAUTOMAT, VT_PERCENT, 9560, STR9560, 0, NULL}, //  Gebl'ansteuerung Durchlad [%]
{0x253d2fe9, CAT_FEUERUNGSAUTOMAT, VT_UNKNOWN, 9563, STR9563, 0, NULL}, //  Solldrehzahl Durchladung [rpm]

 /*** virtuelle Zeilen ***/
{0x2d3d0215, CAT_USER_DEFINED, VT_TEMP, 10000, STR10000, 0, NULL}, // Raumtemperatur 1 (kann als INF geschickt werden)

{CMD_END, CAT_UNKNOWN, VT_UNKNOWN,0,"", 0, NULL}
};

/* buffer to load PROGMEM values in RAM */
#define BUFLEN 3500
char buffer[BUFLEN];

/* buffer to print output lines*/
#define OUTBUF_LEN  300
char outBuf[OUTBUF_LEN];
byte outBufLen=0;

void outBufclear(void){
  outBufLen=0;
  outBuf[0]='\0';
}

int dayofweek(uint8_t day, uint8_t month, uint16_t year)
{
   /** Zeller's congruence for the Gregorian calendar. **/
   /** With 1=Monday, ... 5=Saturday, 7=Sunday         **/
   if (month < 3) {
      month += 12;
      year--;
   }
   return (((13*month+3)/5 + day + year + year/4 - year/100 + year/400) % 7) + 1;
}


void setup() {
  Serial.begin(115200);
  Serial.println(F("READY"));
  Serial.print(F("free RAM:"));
  Serial.println(freeRam());

  digitalWrite(led0, HIGH);
  pinMode(led0, OUTPUT);

  // enable w5100 SPI
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  // disable SD Card
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
}

int findLine(uint16_t line, uint16_t start_idx, uint32_t *cmd){
  int found;
  int i;
  uint32_t c;
  uint16_t l;

  // search for the line in cmdtbl
  i=start_idx;
  found=0;
  do{
    c=pgm_read_dword(&cmdtbl[i].cmd);
    if(c==CMD_END) break;
    l=pgm_read_word(&cmdtbl[i].line);
    if(l==line){
      found=1;
      break;
    }
    if(l>line){
      break;
    }
    i++;
  }while(1);

  if(!found){
    return -1;
  }
  if(cmd!=NULL) *cmd=c;
  return i;
}

#define MAX_PARAM_LEN 22

int set(uint16_t line,char *val, bool setcmd){
  byte msg[33];
  byte tx_msg[33];
  int i;
  uint32_t c;
  uint8_t param[MAX_PARAM_LEN]; // 33 -9 - 2
  uint8_t param_len;

  i=findLine(line,0,&c);
  if(i<0) return 0;

  // get type
  switch(pgm_read_byte(&cmdtbl[i].type)){
    case VT_TEMP:
      {
      uint16_t t=atof(val)*64.0;
      if(setcmd){
        param[0]=0x01;
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{ // INF message type (e.g. for room temperature)
        param[0]=(t >> 8);
        param[1]= t & 0xff;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;
    case VT_PERCENT:
      {
      if(val[0]!='\0'){
        uint8_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=t;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
      }
      param_len=2;
      }
      break;
    case VT_ENUM:
    case VT_ONOFF: // 1 = On
    case VT_CLOSEDOPEN: // 1 = geschlossen
    case VT_YESNO: // 1 = Ja
    case VT_WEEKDAY: // (1=Mo..7=So)
      {
      uint8_t t=atoi(val);
      param[0]=0x01;
      param[1]=t;
      param_len=2;
      }
      break;
    case VT_FP02: // (e.g. Kennlinie Steilheit)
      {
      uint16_t t=atof(val)*50.0;
      param[0]=0x01;
      param[1]=(t >> 8);
      param[2]= t & 0xff;
      param_len=3;
      }
      break;
    case VT_PRESSURE:
      {
      uint8_t t=atof(val)*10.0;
      param[0]=0x01;
      param[1]= t;
      param_len=2;
      }
      break;
    case VT_UINT: // (Brennerstarts Intervall/Brennerstarts seit Wartung)
      {
      if(val[0]!='\0'){
        uint16_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=(t >> 8);
        param[2]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;
    case VT_MINUTES: // (HK1 - Einschaltoptimierung)
      {
      uint32_t t=atoi(val)*60;
      param[0]=0x01;
      param[1]=(t >> 24) & 0xff;
      param[2]=(t >> 16) & 0xff;
      param[3]=(t >> 8) & 0xff;
      param[4]= t & 0xff;
      param_len=5;
      }
      break;
    case VT_HOURS_WORD: // (Brennerstunden Intervall - nur durch 100 teilbare Werte)
    case VT_MINUTES_WORD: // (Legionellenfunktion Verweildauer)
      {
      if(val[0]!='\0'){
        uint16_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=(t >> 8) & 0xff;
        param[2]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;
    case VT_MONTHS: //(Wartungsintervall)
    case VT_MINUTES_SHORT: // ( Fehler - Alarm)
      {
      if(val[0]!='\0'){
        uint8_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]= t;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
      }
      param_len=2;
      }
      break;    
    case VT_DAYS: // (Legionellenfkt. Periodisch)
    case VT_HOURS_SHORT: // (Zeitkonstante Gebäude)
      {
      uint8_t t=atoi(val);
      param[0]=0x01;  //enable
      param[1]= t;
      param_len=2;
      }
      break;
    case VT_HOUR_MINUTES: //TODO test it
      {
      if(val[0]!='\0'){
        uint8_t h=atoi(val);
        uint8_t m=0;
        while(*val!='\0' && *val!=':') val++;
        if(*val==':'){
          val++;
          m=atoi(val);
        }
        param[0]=0x06;  //enable
        param[1]= h;
        param[2]= m;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
      }
      param_len=3;
      }
      break;
    case VT_DWORD:
      {
      if(val[0]!='\0'){
        uint32_t t=atoi(val);
        param[0]=0x06;  //enable
        param[1]=(t >> 24) & 0xff;
        param[2]=(t >> 16) & 0xff;
        param[3]=(t >> 8) & 0xff;
        param[4]= t & 0xff;
      }else{
        param[0]=0x05;  // disable
        param[1]=0x00;
        param[2]=0x00;
        param[3]=0x00;
        param[4]=0x00;
      }
      param_len=5;
      }
      break;
    case VT_BYTE: // TODO test it (LPB Geräteadresse / Segmentadresse)
      {
      uint8_t t=atoi(val);
      param[0]=0x01;
      param[1]=t;
      param_len=2;
      }
      break;
    case VT_STRING: // (Telefon Kundendienst)
      {
      strncpy((char *)param,val,MAX_PARAM_LEN);
      param[MAX_PARAM_LEN-1]='\0';
      param_len=strlen((char *)param)+1;
      }
      break;
    case VT_DATETIME: // TODO do we have to send INF or SET command?
      {
      //S0=dd.mm.yyyy_mm:hh:ss
      // date and time are transmitted as INF message by the display unit
      // DISP->ALL  INF    0 Uhrzeit und Datum -  Datum/Zeit: 30.01.2015 23:17:00
	  // DC 8A 7F 14 02 05 00 00 6C 00 73 01 1E 05 17 11 00 00 A1 AB
      int d,m,y,min,hour,sec;
      if(6!=sscanf(val,"%d.%d.%d_%d:%d:%d",&d,&m,&y,&hour,&min,&sec))
        return 0;
        
      Serial.print("date time: ");
      Serial.print(d);
      Serial.print(".");
      Serial.print(m);
      Serial.print(".");
      Serial.print(y);
      Serial.print(" ");
      Serial.print(hour);
      Serial.print(":");
      Serial.print(min);
      Serial.print(":");
      Serial.println(sec);
      
      //outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d.%d %02d:%02d:%02d",msg[12],msg[11],msg[10]+1900,msg[14],msg[15],msg[16]);
      param[0]=0x01; //???
      param[1]=y-1900;
      param[2]=m;
      param[3]=d;
      param[4]=dayofweek(d,m,y);
      param[6]=hour;
      param[7]=min;
      param[8]=sec;
      param_len=9;
      }
      break;
    case VT_TIMEPROG: // TODO test it
      {
      //S502=05:00-22:00|xx:xx-xx:xx|xx:xx-xx:xx
      //DISP->HEIZ SET  502 Zeitprogramm Heizkreis 1 -  Mi: 1. 05:00 - 22:00 2. --:-- - --:-- 3. --:-- - --:--
      //DC 8A 00 17 03 3D 05 0A 8E 05 00 16 00 80 00 00 00 80 00 00 00 08 98
      int h1s=0x80,m1s=0x00,h2s=0x80,m2s=0x00,h3s=0x80,m3s=0x00;
      int h1e=0x80,m1e=0x00,h2e=0x80,m2e=0x00,h3e=0x80,m3e=0x00;
      int ret;
      ret=sscanf(val,"%d:%d-%d:%d|%d:%d-%d:%d|%d:%d-%d:%d",&h1s,&m1s,&h1e,&m1e,&h2s,&m2s,&h2e,&m2e,&h3s,&m3s,&h3e,&m3e);
      // we need at least the first period
      if(ret<4)
        return 0;
      param[0]=h1s;
      param[1]=m1s;
      param[2]=h1e;
      param[3]=m1e;

      param[4]=h2s;
      param[5]=m2s;
      param[6]=h2e;
      param[7]=m2e;

      param[8]=h3s;
      param[9]=m3s;
      param[10]=h3e;
      param[11]=m3e;
      param_len=12;
      }
      break;
    case VT_VACATIONPROG: 
      //DISP->HEIZ SET      3D0509C6 06 00 02 0A 00 00 00 00 17
      //outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[12],msg[11]);
      param[1]=0;
      param[2]=0;
      param[3]=0;
      param[4]=0;
      param[5]=0;
      param[6]=0;
      param[7]=0;
      param[8]=0x17; //?
      param_len=9;
      if(val[0]!='\0'){
          int d,m;
          if(2!=sscanf(val,"%d.%d.",&d,&m))
            return 0;
          param[0]=0x06;
          param[2]=m;
          param[3]=d;
      }else{
          param[0]=0x05;
      }
      break;
    case VT_SUMMERPERIOD: // TODO do we have to send INF or SET command?
      {
    // Sommerzeit scheint im DISP gehandelt zu werden
    // Bei Anzeige werden keine Werte abgefragt. Bei Änderung wird ein INF geschickt.
    // Sommerzeit Beginn 25.3. DISP->ALL  INF      0500009E 00 FF 03 19 FF FF FF FF 16
    // Sommerzeit Ende 25.11. DISP->ALL  INF      0500009D 00 FF 0B 19 FF FF FF FF 16
      int d,m;
      if(2!=sscanf(val,"%d.%d",&d,&m))
        return 0;
      param[0]=0;
      param[1]=0xff;
      param[2]=m;
      param[3]=d;
      param[4]=0xff;
      param[5]=0xff;
      param[6]=0xff;
      param[7]=0xff;
      param[8]=0x17; //?
      param_len=9;
      }
      break;
    case VT_HOURS: // (read only)
    case VT_VOLTAGE: // read only (Ein-/Ausgangstest)
    case VT_LPBADDR: // read only (LPB-System - Aussentemperaturlieferant)
    case VT_PRESSURE_WORD: // read only (Diagnose Verbraucher)
    case VT_FP1: // read only (SW-Version)
    case VT_ERRORCODE: // read only
    case VT_UNKNOWN:
    default:
      return 0;
    break;
  }
  Serial.print("setting line: ");
  Serial.print(line);
  Serial.print(" val: ");
  SerialPrintRAW(param,param_len);
  Serial.println();

  uint8_t t=setcmd?TYPE_SET:TYPE_INF;

  if(!bus.Send(t, c, msg, tx_msg, param, param_len, setcmd)){
    Serial.println("set failed");
    return 0;
  }

  if(verbose) printTelegram(tx_msg);

  // no answer fpr TYPE_INF
  if(t!=TYPE_SET) return 1;

  printTelegram(msg);
  if(msg[4]!=TYPE_ACK){
    Serial.println("set failed NACK");
    return 0;
  }

  return 1;
}

double query(uint16_t line_start, uint16_t line_end, boolean no_print){
  byte msg[33];
  byte tx_msg[33];
  uint32_t c;
  uint16_t line;
  int i=0;
  int idx=0;
  int retry;
  double returnval=0.0;

  if (!no_print) {
    client.println("<p>");
  }
  for(line=line_start;line<=line_end;line++){
    outBufclear();
    i=findLine(line,idx,&c);

    if(i>=0){
      idx=i;
      //Serial.println("found");
      if(c!=CMD_UNKNOWN){
        retry=QUERY_RETRIES;
        while(retry){
          if(bus.Send(TYPE_QUR, c, msg, tx_msg)){

            if(verbose) printTelegram(tx_msg);
            
            printTelegram(msg);
            break;
          }else{
            Serial.println("query failed");
            retry--;
          }
        }
        if(retry==0)
          outBufLen+=sprintf(outBuf+outBufLen,"%d query failed",line);
      }else{
        //Serial.println("unknown command");
        //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d unknown command",line);
      }
    }else{
      //Serial.println("line not found");
      //if(line_start==line_end) outBufLen+=sprintf(outBuf+outBufLen,"%d line not found",line);
    }
    if(outBufLen>0){
      if (!no_print) {
        client.println(outBuf);
        client.println("<br>");
      }
    }
  }
  if (!no_print) {
    client.println("</p>");
  }
  // TODO: check at least for data length (only used for temperature values)
  int data_len=msg[3]-11;
  returnval = printFIXPOINT(msg,data_len,64.0,1,"");  
  return returnval;
}

void loop() {
  byte msg[33];
  byte tx_msg[33];
  char c;
  const byte MaxArrayElement=252;
  char cLineBuffer[MaxArrayElement];
  byte bPlaceInBuffer;

  // monitor bus
  if(monitor){
    bus.Monitor();
  }else{
    // listen for incoming messages
    if(verbose){
      if (bus.GetMessage(msg)) printTelegram(msg);
    }
  }
  
  // listen for incoming clients
  client = server.available();
  if (client) {
    bPlaceInBuffer=0;
    while (client.connected()) {
      if (client.available()) {
        c = client.read();
        Serial.print(c);

        if ((c!='\n') && (c!='\r') && (bPlaceInBuffer<MaxArrayElement)){
          cLineBuffer[bPlaceInBuffer++]=c;
          continue;
        }
        Serial.println();

        // Flush any remaining bytes from the client buffer
        client.flush();
        // GET / HTTP/1.1 (anforderung website)
        // GET /710 HTTP/1.0 (befehlseingabe)
        String urlString = String(cLineBuffer);
        urlString = urlString.substring(urlString.indexOf('/'), urlString.indexOf(' ', urlString.indexOf('/')));
                Serial.println(urlString);
        urlString.toCharArray(cLineBuffer, MaxArrayElement);

// IPWE START
          if (urlString == "/ipwe.cgi") {
            Ipwe();
            break;
          }
          if (urlString == "/leds.cgi?led=0") {
            LedsCgi(led0);
            break;
          }
          if (urlString == "/leds.cgi?led=1") {
            LedsCgi(led1);
            break;
          }
          if (urlString == "/status.xml") {
            StatusXml();
            break;
          }
          if (urlString == "/heating.cgi?1") {
            Heating("1");
            break;
          }
          if (urlString == "/heating.cgi?0") {
            Heating("0");
            break;
          }
// IPWE END

        char *p=cLineBuffer;
#if USE_PASSKEY
        // check for valid passkey
        p=strchr(cLineBuffer+1,'/');
        if(p==NULL){
          break;
        }
        *p='\0';
        if(strcmp(cLineBuffer+1, PASSKEY)){
          Serial.println(F("no matching passkey"));
          webPrintHeader();
          webPrintFooter();
          break;
        }
        *p='/';
#endif
        // simply print the website
        if(!strcmp(p,"/")){
          webPrintSite();
          break;
        }
        // answer to unknown requests
        if(!isdigit(p[1]) && strchr("KSIREVM",p[1])==NULL){
          webPrintHeader();
          webPrintFooter();
          break;
        }
        // setting verbosity level
        if(p[1]=='V'){
          p+=2;
          verbose=atoi(p);
          webPrintHeader();
          if(verbose>0){
            client.println(F("verbose mode activated<br>"));
          }else{
            client.println(F("verbose mode deactivated<br>"));
          }
          client.println(F("only serial output is affected"));
          webPrintFooter();
          break;
        }
        // switching monitor on/off
        if(p[1]=='M'){
          p+=2;
          monitor=atoi(p);
          webPrintHeader();
          if(monitor>0){
            client.println(F("monitor activated<br>"));
          }else{
            client.println(F("monitor deactivated<br>"));
          }
          client.println(F("only serial output is affected"));
          webPrintFooter();
          break;
        }
        // set command
        if(p[1]=='S' || p[1]=='I'){
          int line;
          bool setcmd= (p[1]=='S');

          p+=2;
          if(!isdigit(*p)){
            webPrintHeader();
            client.println(F("ERROR: invalid parameter line"));
            webPrintFooter();
            break;
          }
          line=atoi(p);
          p=strchr(p,'=');
          if(p==NULL){
            webPrintHeader();
            client.println(F("ERROR: invalid parameter val"));
            webPrintFooter();
            break;
          }
          p++;
          Serial.print("set line ");
          Serial.print(line);
          Serial.print(" = ");
          Serial.println(p);

          if(!set(line,p,setcmd)){
            webPrintHeader();
            client.println(F("ERROR: set failed"));
            webPrintFooter();
            break;
          }
          if(setcmd){
            webPrintHeader();
            query(line,line,0);
            webPrintFooter();
          }else{
            webPrintHeader();
            webPrintFooter();
          }
          break;
        }
        // list categories
        if(p[1]=='K' && !isdigit(p[2])){
          //list categories
          webPrintHeader();
          int len=sizeof(ENUM_CAT);
          memcpy_P(buffer, &ENUM_CAT,len);
          buffer[len]=0;
          for(int cat=0;cat<CAT_UNKNOWN;cat++){
            outBufclear();
            printENUM(buffer,len,cat,1);
            Serial.println();
            client.println(outBuf);
            client.println("<br>");
          }
          webPrintFooter();
          break;
        }
        // list enum values
        if(p[1]=='E'){
          webPrintHeader();
          uint16_t line = atoi(&p[2]);
          int i=findLine(line,0,NULL);
          if(i>=0){
            // check type
            if(pgm_read_byte(&cmdtbl[i].type)==VT_ENUM){
              uint16_t enumstr_len=pgm_read_word(&cmdtbl[i].enumstr_len);
              memcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].enumstr)),enumstr_len);
              buffer[enumstr_len]=0;

              uint16_t val;
              uint16_t c=0;
              while(c<enumstr_len){
                if(buffer[c+1]!=' '){
                val=uint16_t(((uint8_t*)buffer)[c]) << 8 | uint16_t(((uint8_t*)buffer)[c+1]);
                c++;
                }else{
                val=uint16_t(((uint8_t*)buffer)[c]);
                }
                //skip leading space
                c+=2;

                sprintf(outBuf,"%d - %s",val,&buffer[c]);
                client.println(outBuf);
                client.println("<br>");

                while(buffer[c]!=0) c++;
                c++;
              }
            }else{
              client.println(F("ERROR: wrong type"));
            }
          }else{
            client.println(F("ERROR: line not found"));
          }
          webPrintFooter();
          break;
        }
        // query reset value
        if(p[1]=='R'){
          uint32_t c;
          webPrintHeader();
          uint16_t line = atoi(&p[2]);
          int i=findLine(line,0,&c);
          if(i<0){
            client.println(F("ERROR: line not found"));
          }else{
            if(!bus.Send(TYPE_QRV, c, msg, tx_msg)){
              Serial.println("set failed");
              client.println(F("ERROR: set failed"));
            }else{
              
              if(verbose) printTelegram(tx_msg);
              
              printTelegram(msg);
              if(outBufLen>0){
                client.println(outBuf);
                client.println("<br>");
              }
            }
          }
          webPrintFooter();
          break;
        }
        // print queries
        webPrintHeader();
        char* range;
        char* line_start;
        char* line_end;
        int start=-1;
        int end=-1;
        range = strtok(p,"/");
        while(range!=0){
          if(range[0]=='K'){
            uint8_t cat,search_cat;
            uint16_t line;
            int i;
            uint32_t c;
            i=0;
            start=-1;
            end=-1;
            search_cat=atoi(&range[1]);
            c=pgm_read_dword(&cmdtbl[i].cmd);
            while(c!=CMD_END){
              cat=pgm_read_byte(&cmdtbl[i].category);
              if(cat==search_cat){
                if(start<0){
                  line=pgm_read_word(&cmdtbl[i].line);
                  start=line;
                }
              }else{
                if(start>=0){
                  line=pgm_read_word(&cmdtbl[i-1].line);
                  end=line;
                  break;
                }
              }
              i++;
              c=pgm_read_dword(&cmdtbl[i].cmd);
            }
            if(end<start){
              end=start;
            }
          }else{
            // split range
            line_start=range;
            line_end=strchr(range,'-');
            if(line_end==NULL){
              line_end=line_start;
            }else{
              *line_end='\0';
              line_end++;
            }
            start=atoi(line_start);
            end=atoi(line_end);
          }
          query(start,end,0);

          range = strtok(NULL,"/");
        }
        webPrintFooter();
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void SerialPrintHex(byte val) {
  if (val < 16) Serial.print("0");
    Serial.print(val, HEX);
}

void SerialPrintHex32(uint32_t val) {
  if (val <= 0x0fffffff) Serial.print("0");
  if (val <= 0x00ffffff) Serial.print("0");
  if (val <= 0x000fffff) Serial.print("0");
  if (val <= 0x0000ffff) Serial.print("0");
  if (val <= 0x00000fff) Serial.print("0");
  if (val <= 0x000000ff) Serial.print("0");
  if (val <= 0x0000000f) Serial.print("0");
  Serial.print(val, HEX);
}


void SerialPrintData(byte* msg){
  int data_len=msg[3]-11;
  for(int i=0;i<data_len;i++){
    SerialPrintHex(msg[9+i]);
    Serial.print(" ");
  }
}

void SerialPrintRAW(byte* msg, byte len){
  for(int i=0;i<len;i++){
    SerialPrintHex(msg[i]);
    Serial.print(" ");
  }
}

void SerialPrintAddr(byte addr){
  switch(addr&0x7F){
    case ADDR_HEIZ: Serial.print(F("HEIZ")); break;
    case ADDR_RGT1: Serial.print(F("RGT1")); break;
    case ADDR_RGT2: Serial.print(F("RGT2")); break;
    case ADDR_DISP: Serial.print(F("DISP")); break;
    case ADDR_ALL: Serial.print(F("ALL ")); break;
    default: SerialPrintHex(addr); break;
  }
}

void SerialPrintType(byte type){
  switch(type){
    case TYPE_INF: Serial.print(F("INF")); break;
    case TYPE_SET: Serial.print(F("SET")); break;
    case TYPE_ACK: Serial.print(F("ACK")); break;
    case TYPE_NACK: Serial.print(F("NACK")); break;
    case TYPE_QUR: Serial.print(F("QUR")); break;
    case TYPE_ANS: Serial.print(F("ANS")); break;
    case TYPE_QRV: Serial.print(F("QRV")); break;
    case TYPE_ARV: Serial.print(F("ARV")); break;
    case TYPE_ERR:
    Serial.print(F("ERR"));
    //outBufLen+=sprintf(outBuf+outBufLen,"ERR");
    break;
    default: SerialPrintHex(type); break;
  }
}

void printLineNumber(uint32_t val) {
    char *p=outBuf+outBufLen;
    outBufLen+=sprintf(outBuf+outBufLen,"%4ld",val);
    Serial.print(p);
}

void printBYTE(byte *msg,byte data_len,const char *postfix){
  char *p=outBuf+outBufLen;
  if(data_len == 2){
    if(msg[9]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%d",msg[10]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("BYTE len error len!=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printWORD(byte *msg,byte data_len,const char *postfix){
  long lval;
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[9]==0){
      lval=(long(msg[10])<<8)+long(msg[11]);
      outBufLen+=sprintf(outBuf+outBufLen,"%ld",lval);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("WORD len error len!=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printDWORD(byte *msg,byte data_len,long divider, const char *postfix){
  long lval;
  char *p=outBuf+outBufLen;

  if(data_len == 5){
    if(msg[9]==0){
      lval=((long(msg[10])<<24)+(long(msg[11])<<16)+(long(msg[12])<<8)+long(msg[13]))/divider;
      outBufLen+=sprintf(outBuf+outBufLen,"%ld",lval);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("DWORD len error len!=5: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void _printFIXPOINT(double dval, int precision, const char* postfix){
  int a,b,i;
  if(dval<0){
    outBufLen+=sprintf(outBuf+outBufLen,"-");
    dval*=-1.0;
  }
  double rval=10.0;
  for(i=0;i<precision;i++) rval*=10.0;
  dval+=5.0/rval;
  a=(int)(dval);
  rval/=10.0;
  b=(int)(dval*rval - a*rval);
  if(precision==0){
    outBufLen+=sprintf(outBuf+outBufLen,"%d",a);
  }else{
    char formatstr[8]="%d.%01d";
    formatstr[5]='0'+precision;
    outBufLen+=sprintf(outBuf+outBufLen,formatstr,a,b);
  }
}

double printFIXPOINT(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[9]==0){
      dval=double((msg[10] << 8) + msg[11]) / divider;
      _printFIXPOINT(dval,precision,postfix);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT len !=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
  return dval;
}

void printFIXPOINT_BYTE(byte *msg,byte data_len,double divider,int precision,const char *postfix){
  double dval;
  char *p=outBuf+outBufLen;

  if(data_len == 2){
    if(msg[9]==0){
      dval=double(msg[10]) / divider;
      _printFIXPOINT(dval,precision,postfix);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    if(postfix!=NULL){
      outBufLen+=sprintf(outBuf+outBufLen," %s",postfix);
    }
    Serial.print(p);
  }else{
    Serial.print(F("FIXPOINT_BYTE len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printCHOICE(byte *msg,byte data_len,const char *val0,const char *val1){
  char *p=outBuf+outBufLen;

  if(data_len == 2){
    if(msg[9]==0){
      if(msg[10]==0){
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",msg[10],val0);
      }else{
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",msg[10],val1);
      }
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F("CHOICE len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printENUM(char* enumstr,uint16_t enumstr_len,uint16_t search_val, int print_val){
  uint16_t val;
  char *p=outBuf+outBufLen;

  if(enumstr!=NULL){
    uint16_t c=0;
    while(c<enumstr_len){
      if((byte)enumstr[c+1]!=' '){
      val=uint16_t(((uint8_t*)enumstr)[c]) << 8 | uint16_t(((uint8_t*)enumstr)[c+1]);
      c++;
      }else{
      val=uint16_t(((uint8_t*)enumstr)[c]);
      }
      //skip leading space
      c+=2;
      if(val==search_val){
       // enum value found
       break;
      }
      while(enumstr[c]!=0) c++;
      c++;
    }
    if(c<enumstr_len){
      if(print_val){
        outBufLen+=sprintf(outBuf+outBufLen,"%d - %s",val,&enumstr[c]);
      }else{
        outBufLen+=sprintf(outBuf+outBufLen,"%s",&enumstr[c]);
      }
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"%d - not found",search_val);
    }
    Serial.print(p);
  }
}

void printDateTime(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 9){
    if(msg[9]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d.%d %02d:%02d:%02d",msg[12],msg[11],msg[10]+1900,msg[14],msg[15],msg[16]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_DATETIME len !=9: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printDate(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 9){
    if(msg[9]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[12],msg[11]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"---");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_DATE len !=9: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void prinTimeProg(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 12){
    outBufLen+=sprintf(outBuf+outBufLen,"1. ");
    if(msg[9]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[9],msg[10],msg[11],msg[12]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    outBufLen+=sprintf(outBuf+outBufLen," 2. ");
    if(msg[13]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[13],msg[14],msg[15],msg[16]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    outBufLen+=sprintf(outBuf+outBufLen," 3. ");
    if(msg[17]<24){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d - %02d:%02d",msg[17],msg[18],msg[19],msg[20]);
    }else{
      outBufLen+=sprintf(outBuf+outBufLen,"--:-- - --:--");
    }
    Serial.print(p);
  }else{
    Serial.print(F(" VT_TIMEPROG len !=12: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printTime(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;

  if(data_len == 3){
    if(msg[9]==0){
      outBufLen+=sprintf(outBuf+outBufLen,"%02d:%02d",msg[10],msg[11]);
    } else {
      outBufLen+=sprintf(outBuf+outBufLen,"--:--");
    }
    Serial.print(p);
  }else{
    Serial.print(F("VT_HOUR_MINUTES len !=3: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printLPBAddr(byte *msg,byte data_len){
  char *p=outBuf+outBufLen;
  
  if(data_len == 2){
  if(msg[9]==0){
    outBufLen+=sprintf(outBuf+outBufLen,"%02d.%02d",msg[10]>>4,(msg[10] & 0x0f)+1);
  }else{
    outBufLen+=sprintf(outBuf+outBufLen,"---");
  }
  Serial.print(p);
  }else{
    Serial.print(F(" VT_LPBADDR len !=2: "));
    SerialPrintData(msg);
    outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
  }
}

void printTelegram(byte* msg) {
  char gradC[]="&deg;C";
  char perc[]="&#037;";

  outBufclear();
/*
#if !DEBUG
  // suppress DE telegrams
  if(msg[0]==0xDE) return;

  // suppress QUERY telegrams
  if(msg[4]==TYPE_QUR) return;
#endif
*/
  // source
  SerialPrintAddr(msg[1]); // source
  Serial.print("->");
  SerialPrintAddr(msg[2]); // destination
  Serial.print(" ");
  // msg[3] contains the message length
  SerialPrintType(msg[4]); // type
  Serial.print(" ");

  uint32_t cmd;
  if(msg[4]==TYPE_QUR || msg[4]==TYPE_SET){ //QUERY and SET: byte 5 and 6 are in reversed order
    cmd=(uint32_t)msg[6]<<24 | (uint32_t)msg[5]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
  }else{
    cmd=(uint32_t)msg[5]<<24 | (uint32_t)msg[6]<<16 | (uint32_t)msg[7] << 8 | (uint32_t)msg[8];
  }

  // search for the command in cmdtbl
  int i=0;
  int known=0;
  uint32_t c;
  c=pgm_read_dword(&cmdtbl[i].cmd);
  while(c!=CMD_END){
    if(c == cmd){
      known=1;
      break;
    }
    i++;
    c=pgm_read_dword(&cmdtbl[i].cmd);
  }
  if(!known){
    Serial.print("     ");
    SerialPrintHex32(cmd);
    Serial.print(" ");
  }else{
    uint16_t line=pgm_read_word(&cmdtbl[i].line);
    printLineNumber(line);
    Serial.print(" ");
    outBufLen+=sprintf(outBuf+outBufLen," ");

    // print category
    int cat=pgm_read_byte(&cmdtbl[i].category);
    int len=sizeof(ENUM_CAT);
    memcpy_P(buffer, &ENUM_CAT,len);
    buffer[len]=0;
    printENUM(buffer,len,cat,0);
    Serial.print(" - ");
    outBufLen+=sprintf(outBuf+outBufLen," - ");

    // print menue text
    strcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].desc)));
    char *p=outBuf+outBufLen;
    outBufLen+=sprintf(outBuf+outBufLen," %s: ",buffer);
    Serial.print(p);
  }
  // decode parameter
  int data_len=msg[3]-11;
  if(data_len < 0){
    Serial.print(F("len ERROR "));
    Serial.print(msg[3]);
  }else{
    if(data_len > 0){
      if(known){
        if(msg[4]==TYPE_ERR){
          char *p=outBuf+outBufLen;
          outBufLen+=sprintf(outBuf+outBufLen,"error %d",msg[9]);
          if(msg[9]==0x07){
            outBufLen+=sprintf(outBuf+outBufLen," (parameter not supported)");
          }
          Serial.print(p);
        }else{
  /*
          double dval;
          long lval;
  */
          switch(pgm_read_byte(&cmdtbl[i].type)){
            case VT_DATETIME: // special
              printDateTime(msg,data_len);
              break;
            case VT_SUMMERPERIOD:
            case VT_VACATIONPROG:
              printDate(msg,data_len);
              break;
            case VT_TIMEPROG:
              prinTimeProg(msg,data_len);
              break;
            case VT_MINUTES_SHORT: //u8 min
              printBYTE(msg,data_len,"min");
              break;
            case VT_MINUTES_WORD: //u16 min
              printWORD(msg,data_len,"min");
              break;
            case VT_MINUTES: // u32 min
              printDWORD(msg,data_len,60,"min");
              break;
            case VT_HOURS_SHORT: // u8 h
              printBYTE(msg,data_len,"h");
              break;
            case VT_HOURS_WORD: // u16 h
              printWORD(msg,data_len,"h");
              break;
            case VT_HOURS: // u32 h
              printDWORD(msg,data_len,3600,"h");
              break;
            case VT_HOUR_MINUTES: // u8:u8
              printTime(msg,data_len);
              break;
            case VT_TEMP: // s16 / 64.0 - Wert als Temperatur interpretiert (RAW / 64)
              printFIXPOINT(msg,data_len,64.0,1,gradC);
              break;
            case VT_PRESSURE_WORD: // u16 / 10.0 bar
              printFIXPOINT(msg,data_len,10.0,1,"bar");
              break;
            case VT_PRESSURE: // u8 / 10.0 bar
              printFIXPOINT_BYTE(msg,data_len,10.0,1,"bar");
              break;
            case VT_FP02: // u16 / 50.0 - Wert als Festkommazahl mit 2/100 Schritten interpretiert (RAW / 50)
              printFIXPOINT(msg,data_len,50.0,2,NULL);
              break;
            case VT_FP1: // s16 / 10.0 Wert als Festkommazahl mit 1/10 Schritten interpretiert (RAW / 10)
              printFIXPOINT(msg,data_len,10.0,1,NULL);
              break;
            case VT_BYTE: // u8
              printBYTE(msg,data_len,NULL);
              break;
            case VT_ONOFF:
              printCHOICE(msg,data_len,"Aus","Ein");
              break;
            case VT_YESNO:
              printCHOICE(msg,data_len,"Nein","Ja");
              break;
            case VT_CLOSEDOPEN:
              printCHOICE(msg,data_len,"Offen","Geschlossen");
              break;
            case VT_DAYS: // u8 Tage
              printBYTE(msg,data_len,"Tage");
              break;
            case VT_MONTHS: // u8 Monate
              printBYTE(msg,data_len,"Monate");
              break;
            case VT_WEEKDAY: // enum
              if(data_len == 2){
                if(msg[9]==0){
                  int len=sizeof(ENUM_WEEKDAY);
                  memcpy_P(buffer, &ENUM_WEEKDAY,len);
                  buffer[len]=0;
                  printENUM(buffer,len,msg[10],0);
                }else{
                  Serial.print(F("---"));
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              }else{
                Serial.print(F(" VT_WEEKDAY !=2: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_ENUM: // enum
              if(data_len == 2){
                if(msg[9]==0){
                  if(pgm_read_word(&cmdtbl[i].enumstr)!=0){
                    int len=pgm_read_word(&cmdtbl[i].enumstr_len);
                    memcpy_P(buffer, (char*)pgm_read_word(&(cmdtbl[i].enumstr)),len);
                    buffer[len]=0;

                    printENUM(buffer,len,msg[10],1);
                  }else{
                    Serial.print(F("no enum str "));
                    SerialPrintData(msg);
                    outBufLen+=sprintf(outBuf+outBufLen,"no enum str");
                  }
                }else{
                  Serial.print(F("---"));
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              }else{
                Serial.print(F(" VT_ENUM len !=2: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_PERCENT: // u8 %
              printBYTE(msg,data_len,perc);
              break;
            case VT_DWORD: // s32
              printDWORD(msg,data_len,1,NULL);
              break;
            case VT_STRING: // string
              if(data_len > 0){
                if(msg[9]!=0){
                  msg[9 + data_len]='\0'; // write terminating zero
                  Serial.print((char*)&msg[9]);
                  outBufLen+=sprintf(outBuf+outBufLen,"%s",(char*)&msg[9]);
                } else {
                  Serial.print("-");
                  outBufLen+=sprintf(outBuf+outBufLen,"-");
                }
              }else{
                Serial.print(F(" VT_STRING len ==0: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_ERRORCODE: //  s16
              if(data_len == 3){
                if(msg[9]==0){
                  long lval;
                  lval=(long(msg[10])<<8)+long(msg[11]);
                  int len=sizeof(ENUM_ERROR);
                  memcpy_P(buffer, &ENUM_ERROR,len);
                  buffer[len]=0;
                  printENUM(buffer,len,lval,1);
                } else {
                  Serial.print("---");
                  outBufLen+=sprintf(outBuf+outBufLen,"---");
                }
              }else{
                Serial.print(F(" VT_ERRORCODE len ==0: "));
                SerialPrintData(msg);
                outBufLen+=sprintf(outBuf+outBufLen,"decoding error");
              }
              break;
            case VT_UINT: //  s16
              printWORD(msg,data_len,NULL);
              break;
            case VT_VOLTAGE: // u16 - 0.0 -> 00 00 (decoding unklar, da nur 0V gesehen)
              //printFIXPOINT_BYTE(msg,data_len,10.0,1,"Volt");
              printBYTE(msg,data_len,"Volt");
              break;
            case VT_LPBADDR: //decoding unklar 00 f0 -> 15.01
              printLPBAddr(msg,data_len);
              break;
            case VT_UNKNOWN:
            default:
              SerialPrintData(msg);
              outBufLen+=sprintf(outBuf+outBufLen,"unknown type");
              break;
          }
        }
      }else{
        SerialPrintData(msg);
       //Serial.println();
       // SerialPrintRAW(msg,msg[3]);
        outBufLen+=sprintf(outBuf+outBufLen,"unknown command");
      }
    }
  }
  Serial.println();
  if(verbose){
    SerialPrintRAW(msg,msg[3]);
    Serial.println();
  }
}

void webPrintHeader(void){
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.println(F("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">"));
  client.println(F("<html>"));
  client.println(F("<head>"));
  client.println(F("<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">"));
  client.println(F("<title>BSB LAN-SERVER</title>"));
  client.println(F("<link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"http://arduino.cc/en/favicon.png\" />"));
  client.println(F("</head>"));
  client.println(F("<body>"));
}

void webPrintFooter(void){
  client.println(F("</body>"));
  client.println(F("</html>"));
  client.println();

}

void webPrintSite() {
  webPrintHeader();

  client.println(F("<p>"));
  client.print(F("BSB Web"));
  client.print(F(" ----------</p>"));
  client.print(F(" <p>options:"));
  client.print(F(" <table>"));
  client.print(F(" <tr><td>/K</td> <td>list available categories</td></tr>"));
  client.print(F(" <tr><td>/Kx</td> <td>query all values in category x</td></tr>"));
  client.print(F(" <tr><td>/x</td> <td>query value for line x</td></tr>"));
  client.print(F(" <tr><td>/x-y</td> <td>query all values from line x up to line y</td></tr>"));
  client.print(F(" <tr><td>/Sx=v</td> <td>set value v for line x and query the new value afterwards (empty string after = disables the value</td></tr>"));
  client.print(F(" <tr><td>/Ix=v</td> <td>send INF message for command in line x with value v</td></tr>"));
  client.print(F(" <tr><td>/Ex</td> <td>list enum values for line x</td></tr>"));
  client.print(F(" <tr><td>/Rx</td> <td>query reset value for line x</td></tr>"));
  client.print(F(" <tr><td>/Vn</td> <td>set verbosity level for serial output</td></tr>"));
  client.print(F(" <tr><td>/Mn</td> <td>activate/deactivate monitor functionality (n=0 disable, n=1 enable)</td></tr>"));
  client.print(F(" </table>"));
  client.print(F(" multiple queries are possible, e.g. /K0/710/8000-8999</p>"));
  webPrintFooter();
}

/*************************** IPWE Extension **************************************/
void Ipwe() {
  webPrintHeader();
  int sensor_anz = 6;
  double sensors[sensor_anz];
  sensors[0] = query(8700,8700,1);
  sensors[1] = query(8743,8743,1);
  sensors[2] = query(8314,8314,1);
  sensors[3] = query(8310,8310,1);
  sensors[4] = query(8830,8830,1);
  sensors[5] = !digitalRead(led0)*99+1;

  client.print(F("<html><body><form><table border=1><tbody><tr><td>Sensortyp</td><td>Adresse</td><td>Beschreibung</td><td>Temperatur</td><td>Luftfeuchtigkeit</td><td>Windgeschwindigkeit</td><td>Regenmenge</td></tr>"));
  for (int i=0; i < sensor_anz; i++) {
    client.print(F("<tr><td>T<br></td><td>"));
    client.print(i+1);
    client.print(F("<br></td><td>T"));
    client.print(i+1);
    client.print(F("<br></td><td>"));
    client.print(sensors[i]);
    client.print(F("<br></td><td>0<br></td><td>0<br></td><td>0<br></td></tr>"));
  }
  client.print(F("</tbody></table></form>"));
  webPrintFooter();
}

// Relais Status
void StatusXml() {
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<status><volts>5</volts><led0>"));
  client.print(!digitalRead(led0));
  client.print(F("</led0><led1>"));
  client.print(!digitalRead(led1));
  client.print(F("</led1></status>"));
}

//Switch Relais
void LedsCgi(int led) {
  char* ledstatus;
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  if (digitalRead(led)) digitalWrite(led, LOW);
  else digitalWrite(led, HIGH);
  client.print(F("Success! "));
  client.print(!digitalRead(led));
  if (!digitalRead(led) == false) {
    ledstatus = "0";
  } else {
    ledstatus = "1";
  }
//  set(700,ledstatus,true);  // Zusätzlich (bzw. ggf. alternativ) noch Wechsel zwischen Automatik- und Frostschutzmodus
} 

//Heizung an-/abschalten
void Heating(char* status) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  if (status=="1") {
    digitalWrite(led0, LOW);
  } else {
    digitalWrite(led0, HIGH);
  }
  client.print(F("Success! "));
  client.print(status);
  set(700,status,true);    // Zusätzlich (bzw. ggf. alternativ) noch Wechsel zwischen Automatik- und Frostschutzmodus
} 
