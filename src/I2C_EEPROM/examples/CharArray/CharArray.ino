#include <Wire.h>
#include <I2C_EEPROM.h>







// ST24C08<0x50> eep; 
AT24C32<> eep; // Das EEProm auf der china üblichen RTC1307, default Adresse 0x50 
// AT24C32<0x57> eep; // Das EEProm auf der china üblichen RTC3231 



void setup() 
{
   Serial.begin(9600); 
   Wire.begin();
   
   Serial.print("EE Prom lenth: "); 
   Serial.println(eep.length()); 

   if(eep.ready())
    Serial.println ("EE Prom ist bereit!");
    else Serial.println("EE Prom ist nicht bereit, Verkabelung prüfen ");
   


  char test[100] = "Dieses ist ein total langer Teststring. Eigentlich muesste hier ein ganzer Roman stehen.";
  eep.put(0,test); // String ins EEProm schreiben
  
  unsigned long time;
  
  Serial.print("eep.get() needs ");
  time = micros();
  eep.get(0,test); // String lesen
  Serial.print(micros()-time);
  Serial.println(" Microseconds");
  
  Serial.print("fastBlockRead ");
  time = micros();
  eep.fastBlockRead(0,&test,sizeof(test));// String lesen
  Serial.print(micros()-time);
  Serial.println(" Microseconds");

  Serial.println(test);
   
}

void loop() 
{
}
