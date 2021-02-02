#include <Wire.h>

#define EEP_WIRE Wire1 
#include <I2C_EEPROM.h> 





// ST24C08<0x50> eep; 
AT24C32<> eep; // Das EEProm auf der china üblichen RTC1307, default Adresse 0x50 
// AT24C32<0x57> eep; // Das EEProm auf der china üblichen RTC3231 

void setup() 
{
   Serial.begin(9600); 
   Wire1.begin();
 
   // die Speichergröße des EEProm wird in der Klasse gespeichert
   // kann also ausgelesen werden, ohne dass das EEProm wirlich
   // bereit ist 
   Serial.print("EE Prom lenth: "); 
   Serial.println(eep.length()); 

   if(eep.ready()) // eeprom bereit ?
   {
      // eeprom wurde gefunden, und ist bereit
      Serial.println ("EEProm ist bereit!");
   }else
   {
      // eeprom hat nicht geantwortet
      // Auch direkt nach dem schreiben blockiert das eeprom ein paar ms
      Serial.println("EEProm ist nicht bereit, Verkabelung prüfen ");
   }
}

void loop() 
{

}
