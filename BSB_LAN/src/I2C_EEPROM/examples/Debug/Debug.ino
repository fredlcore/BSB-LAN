

#include <Wire.h>


// Debugausgabe Stream festlegen
#define EEP_DEBUG Serial // Auskomentieren wenn Testphase fertig


#include <I2C_EEPROM.h>







//ST24C08<0x50> eep; 
AT24C32<> eep; // Das EEProm auf der china üblichen RTC 1307, default Adresse 0x50 (80)


// schreibt an Adresse 250 im EEProm
void setup() 
{
   Serial.begin(9600); 
   Wire.begin();
   
   Serial.print("EE Prom lenth: "); 
   Serial.println(eep.length()); 

   if(eep.ready())
    Serial.println ("EE Prom ist bereit!");
    else Serial.println("EE Prom ist nicht bereit, Verkabelung prüfen ");
   


  char test[70] = "Leorem ipsum dolor sit amet consectetuer justo semper Vivamus.";
  eep.put(250,test); // String ins EEProm schreiben

  
  unsigned long time;
  
  Serial.print("eep.get()  ");
  time = micros();
  eep.get(250,test); // String lesen
  Serial.println(micros()-time);
  
  Serial.print("fastBlockRead ");
  time = micros();
  eep.fastBlockRead(250,&test,sizeof(test));// String lesen
  Serial.println(micros()-time);

  Serial.println(test);
   
}

void loop() 
{
}
