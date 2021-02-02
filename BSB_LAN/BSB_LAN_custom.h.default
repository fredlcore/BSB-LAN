/* 
 * Example code for BSB_lan_custom.h
 * If configuration definement CUSTOM_COMMANDS is active, this code is run 
 * at the end of each main loop and utilizes the main loop variables 
 * custom_timer (set each loop to millis()) and custom_timer_compare.
 * This code example checks for absolute humidity of an inside as well as 
 * outside DHT22 temperature/humidity sensor and activates a fan on GPIO 6
 * if absolute outside humidity is 5% less than inside.
 * 
 * Afterwards, calculate the average of all MAX! wall and heating thermostats 
 * and send this as the current room temperature to the heating system.
*/

if (custom_timer > custom_timer_compare+20000) {    // every 20 seconds  
  custom_timer_compare = millis();
  int numDHTSensors = sizeof(DHT_Pins) / sizeof(int);
  double hum[2]={ 0 };
  double temp[2]={ 0 };
  for(int i=0;i<numDHTSensors;i++){
    DHT.read22(DHT_Pins[i]);
    hum[i] = DHT.humidity;
    temp[i] = DHT.temperature;
  }

  double abs_hum_inside = 216.7*(hum[0]/100.0*6.112*exp(17.62*temp[0]/(243.12+temp[0]))/(273.15+temp[0]));
  double abs_hum_outside = 216.7*(hum[1]/100.0*6.112*exp(17.62*temp[1]/(243.12+temp[1]))/(273.15+temp[1]));
  Serial.print(F("Absolute humidity inside: "));
  Serial.println(abs_hum_inside);
  Serial.print(F("Absolute humidity outside: "));
  Serial.println(abs_hum_outside);
  Serial.print(F("Temperature inside: "));
  Serial.println(temp[0]);
  Serial.print(F("Temperature outside: "));
  Serial.println(temp[1]);

  if (abs_hum_inside<40 && abs_hum_outside<40) {   // check for valid readings
    pinMode(6, OUTPUT);                            // use GPIO pin for fan
    if (abs_hum_outside*0.05 < abs_hum_inside && temp[0]>15) {
      digitalWrite(6, 1);
      Serial.println("Fan on");
    }
    if (abs_hum_outside >= abs_hum_inside || temp[0]<14.5) {
      digitalWrite(6, 0);
      Serial.println("Fan off");
    }
  }
#ifdef MAX_CUL
  
  max_cul.println(F("Zr")); // periodically (re-)activate "Moritz" mode on Cube to receive MAX messages
  int max_avg_count = 0;
  float max_avg = 0;
  for (int x=0;x<20;x++) {
    if (max_cur_temp[x] > 0) {
      max_avg += (float)max_cur_temp[x] / 10;
      max_avg_count++;
      Serial.print(max_devices[x], HEX);
      Serial.print(F(": "));
      Serial.print((float)max_cur_temp[x] / 10);  // Current temperature
      Serial.print(F(" / "));
      Serial.print((float)max_dst_temp[x] / 2);   // Desired temperature
      Serial.print(F(" / "));
      Serial.println(max_valve[x]);               // Valve opening in percent
    }
  }
  if (max_avg_count > 0) {
    Serial.print(F("AvgMax: "));
    Serial.println(max_avg / max_avg_count);

    char set_temp[6];
    dtostrf((max_avg/max_avg_count), 1, 1, set_temp);   // Send average temperature
//    Serial.print(F("Setting room temperature to "));
//    Serial.println(set_temp);
//    set(10000, set_temp, 0);
  }
#endif
}
