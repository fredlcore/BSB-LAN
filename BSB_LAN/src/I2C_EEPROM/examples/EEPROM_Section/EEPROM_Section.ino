#include <Wire.h>
#include <I2C_EEPROM.h>
#include <avr/eeprom.h>

struct Configuration
{
  char name[20];
  float  temperature;
}eepconfig  EEMEM ;







// ST24C08<0x50> eep; 
AT24C32<> eep; // Das EEProm auf der china üblichen RTC1307, default Adresse 0x50 
// AT24C32<0x57> eep; // Das EEProm auf der china üblichen RTC3231 


void setup() 
{
   Serial.begin(9600); 
   Wire.begin();

   if(eep.ready())
    Serial.println ("EE Prom ist bereit!");
    else Serial.println("EE Prom ist nicht bereit, Verkabelung prüfen ");
   

   Serial.print("EE Prom lenth: "); 
   Serial.println(eep.length()); 

   
   Serial.print("Adresse von Configuration.name: "); 
   Serial.println( (int)&eepconfig.name,HEX); 
   
   Serial.print("Adresse von Configuration.temperature: "); 
   Serial.println( (uint16_t)&eepconfig.temperature,HEX); 

    float temp = 0.3;
   eep.put(eepconfig.temperature,temp);
   temp = 5.5;
   eep.get(eepconfig.temperature,temp);

   
   Serial.print("Value von Configuration.temperature: "); 
   Serial.println(temp); 





   
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
