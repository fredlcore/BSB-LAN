#pragma once
#include "common.h"

// Single Hreg write
// Multiple read
void readMultiple(uint8_t sl, TAddress reg, uint16_t count = 1, void* value = nullptr) {
  Serial.print("Read Multiple ");
  bool mem = false;
  if (!value) {
    if (reg.isHreg() || reg.isIreg()) {
      value = malloc(count * sizeof(uint16_t));
      if (!value) {
        Serial.println(" FAILED");
        return;
      }
      for (uint8_t i = 0; i < count; i++) {
        ((uint16_t*)value)[i] = i;
      }
    } else {
      value = malloc(count * sizeof(bool));
      if (!value) {
        Serial.println(" FAILED");
        return;
      }
      for (uint8_t i = 0; i < count; i++) {
        ((bool*)value)[i] = i % 2;
      }
    }
    mem = true;
  }
  bool addRes = true;
  switch (reg.type) {
  case TAddress::HREG:
    for (uint8_t i = 0; i < count; i++) {
      addRes = addRes && slave.addHreg(reg.address + i, ((uint16_t*)value)[i]);
    }
    Serial.print("HREG: ");
  break;
  case TAddress::IREG:
    for (uint8_t i = 0; i < count; i++) {
      addRes = addRes && slave.addIreg(reg.address + i, ((uint16_t*)value)[i]);
      //Serial.print(slave.Ireg(reg.address + i)); Serial.print(" ");
    }
    Serial.print("IREG: ");
  break;
  case TAddress::COIL:
    for (uint8_t i = 0; i < count; i++) {
      addRes = addRes && slave.addCoil(reg.address + i, ((bool*)value)[i]);
    }
    Serial.print("COIL: ");
  break;
  case TAddress::ISTS:
    for (uint8_t i = 0; i < count; i++) {
      addRes = addRes && slave.addIsts(reg.address + i, ((bool*)value)[i]);
    }
    Serial.print("ISTS: ");
  break;
  default:
    addRes = false;
    Serial.println("UNKNOWN");
    return;
  }
  if (!addRes) {
    Serial.println(" SLAVE FAILED");
    return;
  }
  if (reg.isHreg() || reg.isIreg()) {
    for (uint8_t i = 0; i < count; i++) {
        ((uint16_t*)value)[i] = 0;
    }
  } else {
    for (uint8_t i = 0; i < count; i++) {
        ((bool*)value)[i] = false;
    }
  }
  if (!master.slave()) {
    bool res = false;
      switch (reg.type) {
      case TAddress::HREG:
        res = master.readHreg(sl, reg.address, (uint16_t*)value, count, cbWrite);
      break;
      case TAddress::IREG:
        res = master.readIreg(sl, reg.address, (uint16_t*)value, count, cbWrite);
      break;
      case TAddress::COIL:
        res = master.readCoil(sl, reg.address, (bool*)value, count, cbWrite);
      break;
      case TAddress::ISTS:
        res = master.readIsts(sl, reg.address, (bool*)value, count, cbWrite);
      break;
    }
    if (res) {
      Serial.print(" SENT ");
      if (wait() == Modbus::EX_SUCCESS) {
        bool res = true;
        switch (reg.type) {
        case TAddress::HREG:
          for (uint8_t i = 0; i < count; i++) {
            if (slave.Hreg(reg.address + i) != ((uint16_t*)value)[i]) res = false;
          }
        break;
        case TAddress::IREG:
          for (uint8_t i = 0; i < count; i++) {
            if (slave.Ireg(reg.address + i) != ((uint16_t*)value)[i]) res = false;
          }
        break;
        case TAddress::COIL:
          for (uint8_t i = 0; i < count; i++) {
            if (slave.Coil(reg.address + i) != ((bool*)value)[i]) res = false;
          }
        break;
        case TAddress::ISTS:
          for (uint8_t i = 0; i < count; i++) {
            if (slave.Ists(reg.address + i) != ((bool*)value)[i]) res = false;
          }
        break; 
      }
        if (res) {
          Serial.println(" PASSED");
        } else {
          Serial.print(" INCORRECT");
        }
      } else {
        Serial.println();
      }
    } else {
      Serial.println(" FAILED");
    }
  } else {
    Serial.println(" BUSY");
  }
  if (mem)
    free(value);
}