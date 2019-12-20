#include <TinyWireM.h>
#include <I2C_EEPROM.h>





// ST24C08<0x50> eep; 
AT24C32<> eep; // Das EEProm auf der china üblichen RTC1307, default Adresse 0x50 
// AT24C32<0x57> eep; // Das EEProm auf der china üblichen RTC3231 

void setup() 
{
   TinyWireM.begin();

   if(eep.ready()) // eeprom bereit ?
   {
      // eeprom wurde gefunden, und ist bereit
   }else
   {
      // eeprom hat nicht geantwortet
      // Auch direkt nach dem schreiben blockiert das eeprom ein paar ms
   }
}

void loop() 
{

}
