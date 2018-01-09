/* 
 * Example code for BSB_lan_custom.h
 * If configuration definement CUSTOM_COMMANDS is active, this code is run 
 * at the end of each main loop and utilizes the main loop variables 
 * custom_timer (set each loop to millis()) and custom_timer_compare.
 * This code example checks for absolute humidity of an inside as well as 
 * outside DHT22 temperature/humidity sensor and activates a fan on GPIO 6
 * if absolute outside humidity is 5% less than inside.
*/

if (custom_timer > custom_timer_compare+10000) {    // every 10 seconds  
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
}
