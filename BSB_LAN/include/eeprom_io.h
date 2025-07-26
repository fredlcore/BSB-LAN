/** *****************************************************************
 *  Function: initConfigTable(uint8_t)
 *  Does: creating config parameters address table.
 *  result table is sorted by parameters versions
 *  Pass parameters:
 *
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 * *************************************************************** */


uint32_t initConfigTable(uint8_t version) {
  CRC32 crc;
  if (version == 0xFF) version--; //protection against infinite loop
  // look for parameters vith selected version
  for (uint8_t v = 0; v <= version; v++) {
    //select config parameter
    for (uint8_t i = 0; i < CF_LAST_OPTION; i++) {
      bool allowedversion = false;
      uint16_t addr = baseConfigAddrInEEPROM;
      //look for config parameter in parameters table
      for (uint8_t j = 0; j < sizeof(config)/sizeof(config[0]); j++) {
        if (i == config[j].id) {
          if (config[j].version <= v) allowedversion = true;
        } else
          if (config[j].version <= v && i > config[j].id) {addr += config[j].size;}
      }
      if (allowedversion) {
        options[i].eeprom_address = addr;
        for (uint8_t k = 0; k < sizeof(addr); k++) {
          crc.update(((byte *)&addr)[k]);
        }
      }
    }
  }
  return crc.finalize();
}

//register pointer to variable of selected config option in config parameters address table
void registerConfigVariable(uint8_t id, byte *ptr) {
  options[id].option_address = ptr;
}

//remove variable address of selected config option from config parameters address table
void unregisterConfigVariable(uint8_t id) {
  options[id].option_address = nullptr;
}

byte *getConfigVariableAddress(uint8_t id) {
  return options[id].option_address;
}
//return EEPROM address for selected config option
uint16_t getEEPROMaddress(uint8_t id) {
  return options[id].eeprom_address;
}

uint16_t getVariableSize(uint8_t id) {
  uint16_t len = 0;
  for (uint8_t j = 0; j < sizeof(config)/sizeof(config[0]); j++) {
    if (id == config[j].id) {
      len = config[j].size;
      break;
    }
  }
return len;
}

//copy config option data from EEPROM to variable
bool readFromEEPROM(uint8_t id, byte *ptr) {
  if (!EEPROM_ready) return false;
  if (!ptr) return false;
  uint16_t len = getVariableSize(id);
  if (!len) return false;
  for (uint16_t i = 0; i < len; i++)
    ptr[i] = EEPROM.read(i + options[id].eeprom_address);
  return true;
}

//copy config option data from EEPROM to variable
bool readFromEEPROM(uint8_t id) {
  return readFromEEPROM(id, options[id].option_address);
}

//copy config option data from variable to EEPROM
//return true if EEPROM was updated with new value
bool writeToEEPROM(uint8_t id) {
  if (!EEPROM_ready) return false;
  bool EEPROMwasChanged = false;
  if (!options[id].option_address) return false;
//  printFmtToDebug("Option %d, EEPROM Address %04X, set value: ", id, options[id].eeprom_address);
  for (uint16_t i = 0; i < getVariableSize(id); i++) {
//Some PPS values will changing and writing too frequently. For prevention EEPROM deterioration  if PPS value has no flag it will be skipped.
    if(id == CF_PPS_VALUES && !(allow_write_pps_values[(i / sizeof(pps_values[0])) / 8] & (1 << ((i / sizeof(pps_values[0])) % 8)))){
      continue;
    }
    if (options[id].option_address[i] != EEPROM.read(i + options[id].eeprom_address)) {
      EEPROM.write(i + options[id].eeprom_address, options[id].option_address[i]);
//      printFmtToDebug("%02X ", options[id].option_address[i]);
      EEPROMwasChanged = true;
    }
  }

#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  if (EEPROMwasChanged)
    EEPROM.commit();
#endif
//  printToDebug("\r\n");
  return EEPROMwasChanged;
}

bool writeToConfigVariable(uint8_t id, byte *ptr) {
  if (!options[id].option_address) return false;
  memcpy(options[id].option_address, ptr, getVariableSize(id));
  return true;
}

bool readFromConfigVariable(uint8_t id, byte *ptr) {
  if (!options[id].option_address) return false;
  memcpy(ptr, options[id].option_address, getVariableSize(id));
  return true;
}
