/* 
 * Calculate the average of all MAX! wall and heating thermostats every 60 seconds
 * and send this as the current room temperature to the heating system.
*/

if (custom_timer > custom_timer_compare+60000) {    // every 60 seconds  
  custom_timer_compare = millis();

  max_cul->println("Zr"); // periodically (re-)activate "Moritz" mode on Cube to receive MAX messages
  int max_avg_count = 0;
  float max_avg_cur = 0;
  float max_avg_dst = 0;
  for (int x=0;x<20;x++) {
    if (max_cur_temp[x] > 0) {
      max_avg_cur += (float)max_cur_temp[x] / 10;
      max_avg_dst += (float)max_dst_temp[x] / 2;
      max_avg_count++;
/*
      // Debug output
      Serial.print(max_devices[x], HEX);
      Serial.print(": ");
      Serial.print((float)max_cur_temp[x] / 10);  // Current temperature
      Serial.print(" / ");
      Serial.print((float)max_dst_temp[x] / 2);   // Desired temperature
      Serial.print(" / ");
      Serial.println(max_valve[x]);               // Valve opening in percent
*/
    }
  }
  if (max_avg_count > 0) {
    Serial.print("Avgerage current temperature based on all MAX! thermostats: ");
    Serial.println(max_avg_cur / max_avg_count);
    Serial.print("Avgerage setpoint temperature based on all MAX! thermostats: ");
    Serial.println(max_avg_dst / max_avg_count);

    char set_temp[6];
    dtostrf((max_avg_cur/max_avg_count), 1, 1, set_temp);   // Convert current temperature value to char as required by set() function
    Serial.print("Setting room temperature to ");
    Serial.println(set_temp);
    set(10000, set_temp, 0);

    dtostrf((max_avg_dst/max_avg_count), 1, 1, set_temp);   // Convert setpoint temperature value to char as required by set() function
    Serial.print("Setting setpoint temperature to ");
    Serial.println(set_temp);
    set(710, set_temp, 1);                                  // Write average setpoint temperature to parameter 710 (comfort setpoint HC1, adjust parameter as necessary)
  }
}
