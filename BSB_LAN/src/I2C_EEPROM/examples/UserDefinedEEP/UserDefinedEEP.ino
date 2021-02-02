#include <Wire.h>
#include <I2C_EEPROM.h>


template<uint8_t I2CADDRESS=0x50> class UserDefinedEEP : public  eephandler<I2CADDRESS, 1024U,1,16>{};
//EEProm mit Unbekannter Bezeichnung 
// Größe: 1024 Byte (8kBit)
// AddressMode: 1 (1 Byte Adresse, alternativ 2 Byte Addresse)
// PageLength: 16 Byte (max 32 Byte angeben)

UserDefinedEEP<> eep; // default Adresse 0x50 (80)

void setup() 
{
   Serial.begin(9600); 
   Wire.begin();
 
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
