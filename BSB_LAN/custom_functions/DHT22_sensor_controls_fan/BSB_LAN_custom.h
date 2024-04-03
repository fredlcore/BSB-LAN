/* 
 * This code example checks for absolute humidity of an inside as well as 
 * outside DHT22 temperature/humidity sensor and activates a fan on GPIO 6
 * if absolute outside humidity is 5% less than inside.
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
/*
  // Debug output
  Serial.print("Absolute humidity inside: ");
  Serial.println(abs_hum_inside);
  Serial.print("Absolute humidity outside: ");
  Serial.println(abs_hum_outside);
  Serial.print("Temperature inside: ");
  Serial.println(temp[0]);
  Serial.print("Temperature outside: ");
  Serial.println(temp[1]);
*/

  if (abs_hum_inside<40 && abs_hum_outside<40) {   // check for valid readings
    pinMode(6, OUTPUT);                            // use GPIO pin 6 for fan
    if (abs_hum_outside*0.05 < abs_hum_inside && temp[0]>15) {  // turn on fan if absolute humidity is 5% less outside compared to inside and temperature inside is above 15 degrees celsius
      digitalWrite(6, 1);
      Serial.println("Fan on");
    }
    if (abs_hum_outside >= abs_hum_inside || temp[0]<14.5) {    // otherwise turn fan off
      digitalWrite(6, 0);
      Serial.println("Fan off");
    }
  }
}
