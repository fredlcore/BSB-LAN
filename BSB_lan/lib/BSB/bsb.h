#ifndef __BSB_H__
#define __BSB_H__

//Now the library is compatible both with Arduino <=0023 and Arduino >=100
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SoftwareSerial.h"
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
  bool GetMessage(byte* msg);
  void print(byte* msg);
  bool send(byte TYPE, byte A1, byte A2, byte A3, byte A4, byte LEN=0, byte* DATA=0);
  
  // Generic Get and Set
  bool Query(uint32_t cmd, byte* msg);
  bool Set(uint32_t cmd, byte* param, byte param_len, byte* msg);

private:
  uint8_t myAddr;
  inline void _send(byte* msg);
  uint16_t CRC (byte* buffer, uint8_t length);

  SoftwareSerial* serial;
};

#endif

