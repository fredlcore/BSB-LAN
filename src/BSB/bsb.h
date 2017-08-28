#ifndef __BSB_H__
#define __BSB_H__

//Now the library is compatible both with Arduino <=0023 and Arduino >=100
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "BSBSoftwareSerial.h"
#include "util/crc16.h"

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
  BSB(uint8_t rx, uint8_t tx, uint8_t addr=0x06 );
  void Monitor(byte* msg);
  bool GetMessage(byte* msg);
  void print(byte* msg);
  uint8_t setBusType(uint8_t bus_type_val);
  uint8_t getBusType();

  bool Send(uint8_t type, uint32_t cmd, byte* rx_msg, byte* tx_msg, byte* param=NULL, byte param_len=0, bool wait_for_reply=true);

private:
  uint8_t myAddr;
  uint8_t bus_type = 0;
  uint8_t len_idx = 3;
  inline bool _send(byte* msg);
  uint16_t CRC (byte* buffer, uint8_t length);
  uint16_t CRC_LPB (byte* buffer, uint8_t length);

  BSBSoftwareSerial* serial;
};

#endif
