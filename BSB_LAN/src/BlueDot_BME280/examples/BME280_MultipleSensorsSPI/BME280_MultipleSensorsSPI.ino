
/***************************************************************************
  Example for BME280 Weather Station using up to four Sensors with SPI
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
BlueDot_BME280 bme3;                                     //Object for Sensor 3
BlueDot_BME280 bme4;                                     //Object for Sensor 4

int bme1Detected = 0;                                    //Checks if Sensor 1 is available
int bme2Detected = 0;                                    //Checks if Sensor 2 is available
int bme3Detected = 0;                                    //Checks if Sensor 3 is available
int bme4Detected = 0;                                    //Checks if Sensor 4 is available


void setup() {
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!********************* 
  
  //Choose between Software and Hardware SPI protocol for all sensors

    bme1.parameter.communication = 1;                    //Hardware SPI for Sensor 1 (bme1)
    bme2.parameter.communication = 1;                    //Hardware SPI for Sensor 2 (bme2)
    bme3.parameter.communication = 1;                    //Hardware SPI for Sensor 3 (bme3)
    bme4.parameter.communication = 1;                    //Hardware SPI for Sensor 4 (bme4) 

      

  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!*********************
  
  //Set the Chip Select pins for the SPI Communication.
  //Each sensor must have a different Chip Select pin.
  //Connect the Chip Select pins from the sensors to regular digital pins on the Arduino.

    bme1.parameter.SPI_cs = 4;                          //Chip Select Pin for Sensor 1
    bme2.parameter.SPI_cs = 5;                          //Chip Select Pin for Sensor 2
    bme3.parameter.SPI_cs = 6;                          //Chip Select Pin for Sensor 3
    bme4.parameter.SPI_cs = 7;                          //Chip Select Pin for Sensor 4

    

  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!*********************
  
  //If you are using Hardware SPI, then the MOSI, MISO and SCK pins are predefined by the Arduino Board (ICSP Header).
  //The ICSP Header looks like this:
  //                ICSP 
  //          MISO |x  x| VCC
  //           SCK |x  x| MOSI
  //        /RESET |x  x| GND
  //Connect the SDO (sensor) to MISO (Arduino).
  //Connect the SDI (sensor) to MOSI (Arduino).
  //Connect the SCK (sensor) to SCK (Arduino). This one was obvious!
  //In this case you can comment this section out.
  
  //But if you are using Software SPI you need to set the pins for the MOSI, MISO and SCK lines.
  //Per default the MOSI line is on the pin 11, the MISO line on the pin 12 and the SCK line on the pin 13.
  //You may change those pins if you like, but remember to connect that pin to all sensors.

  
    bme1.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors
    bme2.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors
    bme3.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors
    bme4.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors

    bme1.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors
    bme2.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors
    bme3.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors
    bme4.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors

    bme1.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors
    bme2.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors
    bme3.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors
    bme4.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors    
  

  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
   
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  
    bme1.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 1
    bme2.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 2
    bme3.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 3
    bme4.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 4 

              
    
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
    bme3.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 3
    bme4.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 4

    

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
    bme3.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 3
    bme4.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 4

    

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
    bme3.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 3
    bme4.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 4

    

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
    bme3.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 3
    bme4.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 4 

       
  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa);
  
    bme1.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 1)
    bme2.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 2)
    bme3.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 3)
    bme4.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 4)

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C);
  
    bme1.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    bme2.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    bme3.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    bme4.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    
    bme1.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme2.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme3.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme4.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F

  
  //*********************************************************************
  //*************ADVANCED SETUP IS OVER - LET'S CHECK THE CHIP ID!*******
  
  // Initialize Sensor 1
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

  
  // Initialize Sensor 2
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

  
  // Initialize Sensor 3
  if (bme3.init() != 0x60)
  {    
    Serial.println(F("Ops! Third BME280 Sensor not found!"));
    bme3Detected = 0;
  }
  else
  {
    Serial.println(F("Third BME280 Sensor detected!"));
    bme3Detected = 1;
  }

  
  // Initialize Sensor 4
  if (bme4.init() != 0x60)
  {    
    Serial.println(F("Ops! Fourth BME280 Sensor not found!"));
    bme4Detected = 0;
  }

  else
  {
    Serial.println(F("Fourth BME280 Sensor detected!"));
    bme4Detected = 1;
  }

  if ((bme1Detected == 0)&(bme2Detected == 0)&(bme3Detected == 0)&(bme4Detected == 0))
  {
    Serial.println();
    Serial.println();
    Serial.println(F("Troubleshooting Guide"));
    Serial.println(F("*************************************************************"));
    Serial.println(F("1. Let's check the basics: Are the VCC and GND pins connected correctly? If the BME280 is getting really hot, then the wires are crossed."));
    Serial.println();
    Serial.println(F("2. Did you connect the Chip Select (CS) pin from each sensor to a different digital pin on the Arduino?"));
    Serial.println();
    Serial.println(F("3. Are you using Hardware SPI? In this case, the MOSI, MISO and SCK pins from your Arduino are on the ICSP header."));
    Serial.println();
    Serial.println(F("4. Are you using Software SPI instead? In this case, the MOSI, MISO and SCK pins are regular digital pins choosen by you."));
    Serial.println();
    Serial.println(F("5. Did you connect the SDI pin from each sensor to the same MOSI pin from your Arduino? All sensors must share the same MOSI pin."));
    Serial.println();
    Serial.println(F("6. Did you connect the SDO pin from each BME280 sensor to the same MISO pin from your Arduino? All sensors must share the same MISO pin."));
    Serial.println();
    Serial.println(F("7. And finally, did you connect the SCK pin from each BME280 sensor to the same SCK pin from your Arduino? Yes, all sensors must share the same SCK pin."));
    Serial.println();


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

//Read Sensor 1
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

//Read Sensor 2
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
    Serial.println(F("****************************************"));       
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
    Serial.println(F("****************************************"));    
  }

  //Read Sensor 3
  if (bme3Detected)
  {
    Serial.print(F("Temperature Sensor 3 [°C]:\t\t")); 
    Serial.println(bme3.readTempC());
    //Serial.print(F("Temperature Sensor 3 [°F]:\t\t"));            
    //Serial.println(bme3.readTempF());
    Serial.print(F("Humidity Sensor 3 [%]:\t\t\t")); 
    Serial.println(bme3.readHumidity());
    Serial.print(F("Pressure Sensor 3 [hPa]:\t\t")); 
    Serial.println(bme3.readPressure());
    Serial.print(F("Altitude Sensor 3 [m]:\t\t\t")); 
    Serial.println(bme3.readAltitudeMeter());
    //Serial.print(F("Altitude Sensor 3 [ft]:\t\t\t")); 
    //Serial.println(bme3.readAltitudeFeet());
    Serial.println(F("****************************************"));    
  }

  else
  {
    Serial.print(F("Temperature Sensor 3 [°C]:\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Temperature Sensor 3 [°F]:\t\t")); 
    //Serial.println(F("Null"));
    Serial.print(F("Humidity Sensor 3 [%]:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure Sensor 3 [hPa]:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude Sensor 3 [m]:\t\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Altitude Sensor 3 [ft]:\t\t\t")); 
    //Serial.println(F("Null"));
    Serial.println(F("****************************************"));   
  }

//Read Sensor 4
  if (bme4Detected)
  {
    Serial.print(F("Temperature Sensor 4 [°C]:\t\t")); 
    Serial.println(bme4.readTempC());
    //Serial.print(F("Temperature Sensor 4 [°F]:\t\t"));            
    //Serial.println(bme4.readTempF());
    Serial.print(F("Humidity Sensor 4 [%]:\t\t\t")); 
    Serial.println(bme4.readHumidity());
    Serial.print(F("Pressure Sensor 4 [hPa]:\t\t")); 
    Serial.println(bme4.readPressure());
    Serial.print(F("Altitude Sensor 4 [m]:\t\t\t")); 
    Serial.println(bme4.readAltitudeMeter());
    //Serial.print(F("Altitude Sensor 4 [ft]:\t\t\t")); 
    //Serial.println(bme4.readAltitudeFeet());
    Serial.println(F("****************************************"));    
  }

  else
  {
    Serial.print(F("Temperature Sensor 4 [°C]:\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Temperature Sensor 4 [°F]:\t\t")); 
    //Serial.println(F("Null"));
    Serial.print(F("Humidity Sensor 4 [%]:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure Sensor 4 [hPa]:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude Sensor 4 [m]:\t\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Altitude Sensor 4 [ft]:\t\t\t")); 
    //Serial.println(F("Null"));
    Serial.println(F("****************************************"));   
  }
   
   Serial.println();
   Serial.println();

   delay(1000);
   
 
}
