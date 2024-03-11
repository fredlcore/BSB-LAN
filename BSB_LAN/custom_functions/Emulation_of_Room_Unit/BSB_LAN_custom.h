/*
 * Emulation of temperature sensor of room unit.
 * You can enter up to five parameter numbers which provide temperature data (for example sensors attached to BSB-LAN) and 
 * enter these into the three segments of "rgte_sensorid" in BSB_LAN_custom_global.h
 * The segments 1 to 3 correspond to the room units configured for heating circuits 1 to 3.
 * If you enter more than one parameter number for one segment, then an average will be calulated and sent to the heater.
 * A segment of all zeros means that no data will be sent to the corresponding heating circuit.
*/

  {
    byte tempTime = (millis() / 60000) % 60;
    if (newMinuteValue != tempTime) {
      newMinuteValue = tempTime;
      uint8_t k = 3; // 3 circuits in BSB/LPB mode
      if (bus->getBusType() == BUS_PPS) {
        k = 1;
      }
      for (uint8_t i = 0; i < k; i++) {
        if (rgte_sensorid[i][0].number != 0) {
          uint8_t z = 0;
          float value = 0;
          for (uint8_t j = 0; j < 5; j++) {
            if (rgte_sensorid[i][j].number != 0) {
              if(rgte_sensorid[i][j].dest_addr != -1) set_temp_destination(rgte_sensorid[i][j].dest_addr);
              query(rgte_sensorid[i][j].number);
              if(rgte_sensorid[i][j].dest_addr != -1) return_to_default_destination(dest_address);
              if (decodedTelegram.type == VT_TEMP && decodedTelegram.error == 0) {
                z++;
                value += atof(decodedTelegram.value);
              }
            }
          }
          if (z != 0) {
            _printFIXPOINT(decodedTelegram.value, value / z, 2);
            if (bus->getBusType() != BUS_PPS) {
// if we want to substitute own address sometime to RGT1(2,3)
//              uint8_t saved_own_address = bus->getBusAddr();
//              bus->setBusType(bus->getBusType(), ADDR_RGT1 + i, bus->getBusDest());
              set(10000 + i, decodedTelegram.value, false); //send INF message like RGT1 - RGT3 devices
//              bus->setBusType(bus->getBusType(), saved_own_address, bus->getBusDest());
            } else {
              set(15000 + PPS_RTI, decodedTelegram.value, false); //set PPS parameter PPS_RTI (Raumtemperatur Ist)
            }
          }
        }
      }
    }
  }
