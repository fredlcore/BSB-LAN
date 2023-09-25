/*
 * This script takes care of the problem that the sorting of DS18B20 sensors might not always be the same after each reboot
 * or when sensors suddenly fail. Therefore, it iterates through the sensors (parameters 20300 upwards), and then puts them into
 * fixed positions of the custom_floats[] array depending on the sensor's address.
 * custom_floats[] can contain up to 20 values. Here we skip the first 10 in case they are already used by other functions,
 * so the values can then be found in parameter 20710 and above.
*/

#define number_of_DS18B20_sensors 5     // five sensors in total

for (int i = number_of_DS18B20_sensors - 1; i >=0; i--) { 
  custom_floats[10+i]=NAN;
 
  query(20300.1+i);
  float DS_Value = atof(decodedTelegram.value);

  if (!(decodedTelegram.error == 0)) {
    Serial.print("Error decodedTelegram.value: ");
    Serial.print(decodedTelegram.error);
    Serial.print(" with parameter: ");
    Serial.println(20300+i);
    continue;
  }

  if (DS_Value==0) {
    Serial.print("No value found for parameter: ");
    Serial.println(20300+i);
    continue;
  }

  query(20300+i);
  unsigned long long DS_Addr = std::stoll(decodedTelegram.value, NULL, 16);
 
// Replace the addresses in the case statements with your sensors' addresses
  switch(DS_Addr) {
    case (0x28616408EB7E2EA8): // Brenner
      custom_floats[10]=DS_Value;
      break;
    case (0x28616408EB4370C8): // HK Vorlauf
      custom_floats[11]=DS_Value;
      break;
    case (0x28619381E3E13CCA): // HK Rücklauf
      custom_floats[12]=DS_Value;
      break;
    case (0x28B3B181E3E13C1B): // WW Speicher
      custom_floats[13]=DS_Value;
      break;
    case (0x28AD8E81E3E13CB8): // WW Entnahme
      custom_floats[14]=DS_Value;
      break;
    default:
      Serial.print("No match for sensor address ");
      Serial.println(DS_Addr, HEX);
  }
}