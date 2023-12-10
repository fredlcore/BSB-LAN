#pragma once
#include "common.h"

#define FILE_LEN 100
uint8_t block[FILE_LEN*2];
uint8_t src[FILE_LEN*2];

Modbus::ResultCode handleFile(Modbus::FunctionCode func, uint16_t fileNum, uint16_t recNumber, uint16_t recLength, uint8_t* frame) {
    switch (func) {
    case Modbus::FC_READ_FILE_REC:
      memcpy(frame, src, recLength * 2);
      return Modbus::EX_SUCCESS;
    break;
    case Modbus::FC_WRITE_FILE_REC:
      memcpy(src, frame, recLength * 2);
      return Modbus::EX_SUCCESS;
    break;
    default:
      return Modbus::EX_ILLEGAL_FUNCTION;
    }
}

void initFile() {
    master.onFile(handleFile);
    slave.onFile(handleFile);
}

void testFile() {
  Serial.print("FILE READ:");
  if (master.readFileRec(1, 0, 0, FILE_LEN, block, cbWrite)) {
    Serial.print(" SENT");
    while (master.slave()) {
      master.task();
      slave.task();
      delay(1);
    }
    Serial.printf(" 0x%02X ", code);
    if (memcmp(block, src, FILE_LEN * 2) == 0) {
      Serial.println("PASSED");
    } else {
      Serial.println("FAILED");
    }
  }
  
  memset(block, 0xFF, FILE_LEN * 2);

  Serial.print("FILE WRITE:");
  if (master.writeFileRec(1, 0, 0, FILE_LEN, block, cbWrite)) {
    Serial.print(" SENT");
    while (master.slave()) {
      master.task();
      slave.task();
      delay(1);
    }
    Serial.printf(" 0x%02X ", code);
    if (memcmp(block, src, FILE_LEN * 2) == 0) {
      Serial.println("PASSED");
    } else {
      Serial.println("FAILED");
    }
  }
}