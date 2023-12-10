/*
    Modbus Library for ESP8266/ESP32
    Functional tests
    Copyright (C) 2019 Alexander Emelianov (a.m.emelianov@gmail.com)
	https://github.com/emelianov/modbus-esp8266
	This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <ModbusRTU.h>
#include <StreamBuf.h>
#include "common.h"
#include "write.h"
#include "read.h"
#include "files.h"


uint8_t stage = 0;
uint16_t readHreg = 0;

#define SLAVE_ID 1
#define HREG_ID 10
#define HREG_VALUE 100

#define HREGS_ID 20
#define HREGS_COUNT 20

void setup() {
  Serial.begin(115200);
  Serial.println("ModbusRTU API test");
#if defined(HW_SERIAL)
  Serial1.begin(115200, SERIAL_8N1, 18, 19);
  Serial2.begin(115200, SERIAL_8N1, 22, 23);
#endif
  delay(100);
  master.begin((Stream*)&P1);
  master.master();
  slave.begin((Stream*)&P2);
  slave.slave(SLAVE_ID);
  slave.addHreg(HREG_ID);

writeSingle(SLAVE_ID, HREG(HREG_ID), HREG_VALUE);
writeSingle(SLAVE_ID, COIL(HREG_ID), true);

writeMultiple(SLAVE_ID, HREG(HREG_ID), 10);
writeMultiple(SLAVE_ID, COIL(HREG_ID), 10);

readMultiple(SLAVE_ID, HREG(HREG_ID), 10);
readMultiple(SLAVE_ID, COIL(HREG_ID), 10);
readMultiple(SLAVE_ID, IREG(HREG_ID), 10);
readMultiple(SLAVE_ID, ISTS(HREG_ID), 10);

// Read-Write Hreg
{
  Serial.print("Read-Write Hreg: ");
  #define RD 0x10
  #define WR 0x20
  #define RW_COUNT 10
  uint16_t rd[10];
  uint16_t wr[10];
  for (uint8_t i = 0; i < RW_COUNT; i++)
    wr[i] = WR;
  slave.addHreg(110, RD, RW_COUNT);
  slave.addHreg(120, !WR, RW_COUNT);
  master.readWriteHreg(SLAVE_ID, 110, rd, RW_COUNT, 120, wr, RW_COUNT, cbWrite);
  wait();
  uint8_t i,j;
  for (i = 0; i < RW_COUNT; i++)
    if (rd[i] != RD)
      break;
  for (j = 0; j < RW_COUNT; j++)
    if (slave.Hreg(120 + j) != WR)
      break;
  if (i < RW_COUNT || j < RW_COUNT)
    Serial.println(" FAILED");
  else
    Serial.println(" PASSED");
}
// Mask Hreg
{
  Serial.print("Mask Hreg: ");
  slave.addReg(HREG(130), 0xF0F0);
  slave.addReg(HREG(131), 0x1212);
  master.maskHreg(SLAVE_ID, 130, 0xF0F0, 0x0000, cbWrite);
  wait();
  master.maskHreg(SLAVE_ID, 131, 0xF2F2, 0x2525, cbWrite);
  wait();
  if (slave.Reg(HREG(130)) != 0xF0F0 || slave.Reg(HREG(131)) != 0x1717)
    Serial.println(" FAILED");
  else
    Serial.println(" PASSED");
}
// Garbage read
  {
  bool Node_1_ackStatus = false;
  bool Node_2_ackStatus = false;
  slave.addIsts(100, true);
  slave.addIsts(101, true);
  Serial.print("Write garbage: ");
  if (!master.slave()) {
        master.readIsts(2, 100, &Node_1_ackStatus, 1, NULL);
        while (master.slave()) {
           master.task();
           slave.task();
           delay(1);
        }
        master.readIsts(SLAVE_ID, 100, &Node_1_ackStatus, 1, NULL);
        while (master.slave()) {
          master.task();
          slave.task();
          delay(1);
        }
        master.readIsts(SLAVE_ID, 101, &Node_2_ackStatus, 1, NULL);
        while (master.slave()) {
           master.task();
           while(P2.available())
              P2.write(P2.read());
           //slave.task();
           delay(1);
        }
        master.readIsts(SLAVE_ID, 101, &Node_2_ackStatus, 1, NULL);
        while (master.slave()) {
          master.task();
          slave.task();
          delay(1);
        }
  }
  if (Node_1_ackStatus && Node_2_ackStatus) {
    Serial.println(" PASSED");
  } else {
    Serial.println(" FAILED");
  }
  }
  {
    initFile();
    testFile();
  }
}
void loop() {
  yield();
}