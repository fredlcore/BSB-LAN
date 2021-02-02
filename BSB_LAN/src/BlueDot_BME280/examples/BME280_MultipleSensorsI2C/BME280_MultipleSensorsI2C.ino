
/***************************************************************************
  Example for BME280 Weather Station using two Sensors with I2C Communication
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/


#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme1;                                     //Object for Sensor 1
BlueDot_BME280 bme2;                                     //Object for Sensor 2

int bme1Detected = 0;                                    //Checks if Sensor 1 is available
int bme2Detected = 0;                                    //Checks if Sensor 2 is available


void setup() {
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************
  //*************BASIC SETUP - SAFE TO IGNORE**************************** 
  
  //This program is set for the I2C mode

    bme1.parameter.communication = 0;                    //I2C communication for Sensor 1 (bme1)
    bme2.parameter.communication = 0;                    //I2C communication for Sensor 2 (bme2)
    

  
  //*********************************************************************
  //*************BASIC SETUP - SAFE TO IGNORE****************************
    
  //Set the I2C address of your breakout board  

    bme1.parameter.I2CAddress = 0x77;                    //I2C Address for Sensor 1 (bme1)
    bme2.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor 2 (bme2)

    
  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
    
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  
    bme1.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 1
    bme2.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 2 


                  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Great! Now set up the internal IIR Filter
  //The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  //In short, a high factor value means less noise, but measurements are also less responsive
  //You can play with these values and check the results!
  //In doubt just leave on default

  //0b000:      factor 0 (filter off)
  //0b001:      factor 2
  //0b010:      factor 4
  //0b011:      factor 8
  //0b100:      factor 16 (default value)

    bme1.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 1
    bme2.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 2

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************

    //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero

  //0b000:      factor 0 (Disable humidity measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

    bme1.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 1
    bme2.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 2

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements
  
  //0b000:      factor 0 (Disable temperature measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

    bme1.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 1
    bme2.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 2

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default
  
  //0b000:      factor 0 (Disable pressure measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)  

    bme1.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 1
    bme2.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 2 

     
  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa);
  
    bme1.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 1)
    bme2.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 2)

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C and 59°F);
  
    bme1.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    bme2.parameter.tempOutsideCelsius = 15;               //default value of 15°C
  
    bme1.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme2.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F

  
    
  //*********************************************************************
  //*************ADVANCED SETUP IS OVER - LET'S CHECK THE CHIP ID!*******

  if (bme1.init() != 0x60)
  {    
    Serial.println(F("Ops! First BME280 Sensor not found!"));
    bme1Detected = 0;
  }

  else
  {
    Serial.println(F("First BME280 Sensor detected!"));
    bme1Detected = 1;
  }

  if (bme2.init() != 0x60)
  {    
    Serial.println(F("Ops! Second BME280 Sensor not found!"));
    bme2Detected = 0;
  }

  else
  {
    Serial.println(F("Second BME280 Sensor detected!"));
    bme2Detected = 1;
  }

  if ((bme1Detected == 0)&(bme2Detected == 0))
  {
    Serial.println();
    Serial.println();
    Serial.println(F("Troubleshooting Guide"));
    Serial.println(F("*************************************************************"));
    Serial.println(F("1. Let's check the basics: Are the VCC and GND pins connected correctly? If the BME280 is getting really hot, then the wires are crossed."));
    Serial.println();
    Serial.println(F("2. Did you connect the SDI pin from your BME280 to the SDA line from the Arduino?"));
    Serial.println();
    Serial.println(F("3. And did you connect the SCK pin from the BME280 to the SCL line from your Arduino?"));
    Serial.println();
    Serial.println(F("4. One of your sensors should be using the alternative I2C Address(0x76). Did you remember to connect the SDO pin to GND?"));
    Serial.println();
    Serial.println(F("5. The other sensor should be using the default I2C Address (0x77. Did you remember to leave the SDO pin unconnected?"));

    Serial.println();
    
    while(1);
  }
    
  Serial.println();
  Serial.println();

}

  //*********************************************************************
  //*************NOW LET'S START MEASURING*******************************
void loop() {
   
  Serial.print(F("Duration in Seconds:  "));
  Serial.println(float(millis())/1000);

  if (bme1Detected)
  {
    Serial.print(F("Temperature Sensor 1 [°C]:\t\t")); 
    Serial.println(bme1.readTempC());
    //Serial.print(F("Temperature Sensor 1 [°F]:\t\t"));            
    //Serial.println(bme1.readTempF());
    Serial.print(F("Humidity Sensor 1 [%]:\t\t\t")); 
    Serial.println(bme1.readHumidity());
    Serial.print(F("Pressure Sensor 1 [hPa]:\t\t")); 
    Serial.println(bme1.readPressure());
    Serial.print(F("Altitude Sensor 1 [m]:\t\t\t")); 
    Serial.println(bme1.readAltitudeMeter());
    //Serial.print(F("Altitude Sensor 1 [ft]:\t\t\t")); 
    //Serial.println(bme1.readAltitudeFeet());
    Serial.println(F("****************************************"));    
  }

  else
  {
    Serial.print(F("Temperature Sensor 1 [°C]:\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Temperature Sensor 1 [°F]:\t\t")); 
    //Serial.println(F("Null"));
    Serial.print(F("Humidity Sensor 1 [%]:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure Sensor 1 [hPa]:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude Sensor 1 [m]:\t\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Altitude Sensor 1 [ft]:\t\t\t")); 
    //Serial.println(F("Null"));
    Serial.println(F("****************************************"));   
  }

  if (bme2Detected)
  {
    Serial.print(F("Temperature Sensor 2 [°C]:\t\t")); 
    Serial.println(bme2.readTempC());
    //Serial.print(F("Temperature Sensor 2 [°F]:\t\t")); 
    //Serial.println(bme2.readTempF());
    Serial.print(F("Humidity Sensor 2 [%]:\t\t\t")); 
    Serial.println(bme2.readHumidity());
    Serial.print(F("Pressure Sensor 2 [hPa]:\t\t")); 
    Serial.println(bme2.readPressure());
    Serial.print(F("Altitude Sensor 2 [m]:\t\t\t")); 
    Serial.println(bme2.readAltitudeMeter());
    //Serial.print(F("Altitude Sensor 2 [ft]:\t\t\t")); 
    //Serial.println(bme2.readAltitudeFeet());    
  }

  else
  {
    Serial.print(F("Temperature Sensor 2 [°C]:\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Temperature Sensor 2 [°F]:\t\t")); 
    //Serial.println(F("Null"));
    Serial.print(F("Humidity Sensor 2 [%]:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure Sensor 2 [hPa]:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude Sensor 2 [m]:\t\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Altitude Sensor 2 [ft]:\t\t\t")); 
    //Serial.println(F("Null"));
  }
   
   Serial.println();
   Serial.println();

   delay(1000);
   
 
}
