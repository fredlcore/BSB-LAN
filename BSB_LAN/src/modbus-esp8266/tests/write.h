#pragma once
#include "common.h"

// Single Hreg write
void writeSingle(uint8_t sl, TAddress reg, uint16_t value) {
  Serial.print("Write Single ");
  switch (reg.type) {
  case TAddress::HREG:
    slave.addHreg(reg.address);
    Serial.print("HREG: ");
  break;
  case TAddress::IREG:
    slave.addIreg(reg.address);
    Serial.print("IREG: ");
  break;
  case TAddress::COIL:
    slave.addCoil(reg.address);
    Serial.print("COIL: ");
  break;
  case TAddress::ISTS:
    slave.addIsts(reg.address);
    Serial.print("ISTS: ");
  break;
  default:
    Serial.println("UNKNOWN");
    return;
  }
  if (!master.slave()) {
    bool res = false;
      switch (reg.type) {
      case TAddress::HREG:
        res = master.writeHreg(sl, reg.address, value, cbWrite);
      break;
      case TAddress::IREG:
        //res = master.writeIreg(sl, reg.address, value, cbWrite);
      break;
      case TAddress::COIL:
        res = master.writeCoil(sl, reg.address, value, cbWrite);
      break;
      case TAddress::ISTS:
        //res = master.writeIsts(sl, reg.address, value, cbWrite);
      break;
    }
    if (res) {
      Serial.print(" SENT ");
      if (wait() == Modbus::EX_SUCCESS) {
        uint16_t val = 0;
        switch (reg.type) {
        case TAddress::HREG:
          val = slave.Hreg(reg.address);
        break;
        case TAddress::IREG:
          val = slave.Ireg(reg.address);
        break;
        case TAddress::COIL:
          val = slave.Coil(reg.address);
        break;
        case TAddress::ISTS:
          val = slave.Ists(reg.address);
        break; 
      }
        if (val = value) {
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
}

// Multiple write
void writeMultiple(uint8_t sl, TAddress reg, uint16_t count = 1, void* value = nullptr) {
  Serial.print("Write Multiple ");
  bool mem = false;
  if (!value) {
    if (reg.isHreg() || reg.isIreg()) {
      value = malloc(count * sizeof(uint16_t));
      if (!value)
        return;
      for (uint8_t i = 0; i < count; i++) {
        ((uint16_t*)value)[i] = i;
      }
    } else {
      value = malloc(count * sizeof(bool));
      if (!value)
        return;
      for (uint8_t i = 0; i < count; i++) {
        ((bool*)value)[i] = i % 2;
      }
    }
    mem = true;
  }
  switch (reg.type) {
  case TAddress::HREG:
    slave.addHreg(reg.address, 0, count);
    Serial.print("HREG: ");
  break;
  case TAddress::IREG:
    slave.addIreg(reg.address, 0, count);
    Serial.print("IREG: ");
  break;
  case TAddress::COIL:
    slave.addCoil(reg.address, false, count);
    Serial.print("COIL: ");
  break;
  case TAddress::ISTS:
    slave.addIsts(reg.address, false, count);
    Serial.print("ISTS: ");
  break;
  default:
    Serial.println("UNKNOWN");
    return;
  }
  if (!master.slave()) {
    bool res = false;
      switch (reg.type) {
      case TAddress::HREG:
        res = master.writeHreg(sl, reg.address, (uint16_t*)value, count, cbWrite);
      break;
      case TAddress::IREG:
        //res = master.writeIreg(sl, reg.address, value, count, cbWrite);
      break;
      case TAddress::COIL:
        res = master.writeCoil(sl, reg.address, (bool*)value, count, cbWrite);
      break;
      case TAddress::ISTS:
        //res = master.writeIsts(sl, reg.address, value, count, cbWrite);
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
            //if (slave.Ireg(reg.address + i) != value[i]) res = false;
          }
        break;
        case TAddress::COIL:
          for (uint8_t i = 0; i < count; i++) {
            if (slave.Coil(reg.address + i) != ((bool*)value)[i]) res = false;
          }
        break;
        case TAddress::ISTS:
          for (uint8_t i = 0; i < count; i++) {
            //if (slave.Ists(reg.address + i) != value[i]) res = false;
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