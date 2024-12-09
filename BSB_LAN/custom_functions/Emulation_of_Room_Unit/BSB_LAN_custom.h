/*
 * Emulation of temperature sensor of room unit.
 * You can enter up to five parameter numbers which provide temperature data (for example sensors attached to BSB-LAN) and 
 * enter these into the three segments of "rgte_sensorid" (parameter number, destination device (-1 for default)).
 * The segments 1 to 3 correspond to the room units configured for heating circuits 1 to 3 (for PPS, only circuit 1 is used).
 * If you enter more than one parameter number for one segment, then an average will be calulated and sent to the heater.
 * A segment of all zeros means that no data will be sent to the corresponding heating circuit.
*/

// In this example, the current temperature of the first two MAX! devices will be used to calculate the average of these and then sent
// as room temperature for heating circuit 1.
parameter rgte_sensorid[3][5] = {
  {{20500.1, -1}, {20501.1, -1}, {0, -1}, {0, -1}, {0, -1}},  // parameters for heating circuit 1 (sent to parameter 10000 (BSB/LPB) / 15008 (PPS))
  {{0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}},              // parameters for heating circuit 2 (sent to parameter 10001 (not used for PPS))
  {{0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}}               // parameters for heating circuit 3 (sent to parameter 10002 (not used for PPS))
}; 

if (custom_timer > custom_timer_compare+300000) {    // every five minutes  
  custom_timer_compare = millis();
  uint8_t k = 3; // 3 circuits in BSB/LPB mode
  char set_temp[6];
  if (bus->getBusType() == BUS_PPS) {
    k = 1;
  }
  for (uint8_t i = 0; i < k; i++) {
    if (rgte_sensorid[i][0].number != 0) {
      uint8_t z = 0;
      float value = 0;
      for (uint8_t j = 0; j < 5; j++) {
        if (rgte_sensorid[i][j].number != 0) {
          uint8_t save_my_dev_fam = my_dev_fam;
          uint8_t save_my_dev_var = my_dev_var;
          uint32_t save_my_dev_serial = my_dev_serial;
          if(rgte_sensorid[i][j].dest_addr != -1) {
            set_temp_destination(rgte_sensorid[i][j].dest_addr);
          } 
          query(rgte_sensorid[i][j].number);
          if(rgte_sensorid[i][j].dest_addr != -1) {
            return_to_default_destination(dest_address);
            my_dev_fam = save_my_dev_fam;
            my_dev_var = save_my_dev_var;
            my_dev_serial = save_my_dev_serial;
          }
          if (decodedTelegram.type == VT_TEMP && decodedTelegram.error == 0) {
            z++;
            value += atof(decodedTelegram.value);
          }
        }
      }
      if (z != 0) {
        _printFIXPOINT(decodedTelegram.value, value / z, 2);
        strcpy(set_temp, decodedTelegram.value);
        if (bus->getBusType() != BUS_PPS) {
          set(10000 + i, set_temp, false); //send INF message like RGT1 - RGT3 devices
        } else {
          set(15000 + PPS_RTI, set_temp, true); //set PPS parameter PPS_RTI (Raumtemperatur Ist)
        }
      }
    }
  }
}
