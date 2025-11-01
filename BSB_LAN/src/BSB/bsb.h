#ifndef __BSB_H__
#define __BSB_H__

//Now the library is compatible both with Arduino <=0023 and Arduino >=100
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if defined(__AVR__)
#include "BSBSoftwareSerial.h"
//#include "util/crc16.h"
#endif

#define BUS_BSB 0
#define BUS_LPB 1
#define BUS_PPS 2
#define BUS_OK 1
#define BUS_NOTFREE -1
#define BUS_NOMATCH -2

// See this page for further details:
// http://www.mikrocontroller.net/topic/218643
/*
typedef struct
{
  byte SOF;

  byte SRC;
  byte RCV;

  byte LEN;

  byte TYP;

  byte ADR_1;
  byte ADR_2;
  byte ADR_3;
  byte ADR_4;

  byte DATA[3];
} BSB_MESSAGE;
*/

class BSB
{
public:
  BSB(uint8_t rx, uint8_t tx, uint8_t addr=0x42, uint8_t d_addr=0x00 );
  bool Monitor(byte* msg);
  bool GetMessage(byte* msg);
  void print(byte* msg);
  uint8_t setBusType(uint8_t bus_type_val, uint16_t addr=0x100, uint16_t d_addr=0x100);
  void enableInterface();
  void disableInterface();
  uint8_t getBusType();
  uint8_t getBusAddr();
  uint8_t getBusDest();
  uint8_t setBusDest(uint8_t addr);
  uint8_t getPl_start();
  uint8_t getLen_idx();
  uint8_t offset;

  int8_t Send(uint8_t type, uint32_t cmd, byte* rx_msg, byte* tx_msg, byte* param=NULL, byte param_len=0, bool wait_for_reply=true);
  int8_t _send(byte* msg);

private:
  uint8_t myAddr;
  uint8_t destAddr;
  uint8_t bus_type;
  uint8_t len_idx;
  uint8_t pl_start;
  uint8_t rx_pin;
  uint8_t tx_pin;
  uint16_t CRC (byte* buffer, uint8_t length);
  uint16_t CRC_LPB (byte* buffer, uint8_t length);
  uint8_t CRC_PPS (byte* buffer, uint8_t length);
  uint16_t _crc_xmodem_update (uint16_t crc, uint8_t data);
  uint8_t readByte();
  bool rx_pin_read();

  Stream* serial;  // Bus interface. Point to Software or HarwareSerial
};

#endif
