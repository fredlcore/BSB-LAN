/*
    Modbus Library for ESP8266/ESP32
    Functional tests
    Copyright (C) 2019 Alexander Emelianov (a.m.emelianov@gmail.com)
	https://github.com/emelianov/modbus-esp8266
	This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#pragma once
#include <ModbusRTU.h>
//#define HW_SERIAL

#define BSIZE 1024

#if defined(HW_SERIAL)
#define P1 Serial1
#define P2 Serial2
#else
uint8_t buf1[BSIZE];
uint8_t buf2[BSIZE];

StreamBuf S1(buf1, BSIZE);
StreamBuf S2(buf2, BSIZE);
DuplexBuf P1(&S1, &S2);
DuplexBuf P2(&S2, &S1);
#endif

ModbusRTU master;
ModbusRTU slave;

bool result;
uint8_t code ;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  //Serial.printf_P(" 0x%02X ", event);
  //if (event == 0x00) {
  code = event;
  result = true;
  return true;
}

uint8_t wait() {
  result = false;
  code = 0;
  while (!result) {
    master.task();
    slave.task();
    yield();
  }
  Serial.printf_P(" 0x%02X", code);
  return code;
}