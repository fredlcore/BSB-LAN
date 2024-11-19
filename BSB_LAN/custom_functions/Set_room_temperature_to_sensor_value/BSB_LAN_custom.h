/* 
 * Run every five minutes, this code takes the value of one parameter, 
 * in this case 20500.1 (which contains the measured temperature of the first MAX! device),
 * and sends it to the room temperature parameter (10000 for BSB/LPB, 15008 for PPS).
*/

// Set the parameter that refers to the temperature sensor here:
float sensor_parameter = 20500.1;  // 20500.1 is the measured temperature of the first MAX! device

if (custom_timer > custom_timer_compare+300000) {    // every five minutes  
  custom_timer_compare = millis();
  query(sensor_parameter);
  char set_temp[6];
  strcpy(set_temp, decodedTelegram.value);
  if (bus->getBusType() == BUS_PPS) {
    set(15008, set_temp, 1);  // PPS: Send sensor value to room temperature parameter 15008
  } else {
    set(10000, set_temp, 0);  // BSB/LPB: Send sensor value to room temperature parameter 10000
  }
}
