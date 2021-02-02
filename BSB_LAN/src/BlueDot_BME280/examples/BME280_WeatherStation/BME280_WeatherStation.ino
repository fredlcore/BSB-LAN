
/***************************************************************************
  Example for BME280 Weather Station
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/


#include <Wire.h>
#include "BlueDot_BME280.h"
BlueDot_BME280 bme280 = BlueDot_BME280();


void setup() {
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!*********************
    
  //Choose between the SPI and I2C Communication protocols
  //Or leave the I2C Communication as default

  //0:        Set to 0 for I2C (default value)
  //1:        Set to 1 for Software SPI
  //2:        Set to 2 for Hardware SPI
 
    bme280.parameter.communication = 0;                  //Choose communication protocol

    
     
  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!*********************
    
  //Set the I2C address of your breakout board  
  //Or ignore this, if you're using SPI Communication

  //0x76:       Alternative I2C Address (SDO pin connected to GND)
  //0x77:       Default I2C Address (SDO pin unconnected)
  
     bme280.parameter.I2CAddress = 0x77;                  //Choose I2C Address

     
     
  //*********************************************************************
  //*************BASIC SETUP - READ BEFORE GOING ON!*********************
    
  //Set the pins for SPI Communication
  //Or ignore this, if you're using I2C Communication instead

    bme280.parameter.SPI_cs = 10;                          //Are you using either Software SPI or Hardware SPI? Then you need to define the Chip Select Pin.
    
    bme280.parameter.SPI_mosi = 13;                       //If you are using Software SPI, then you need to define the MOSI line. For Hardware SPI you can leave this line commented.
    bme280.parameter.SPI_miso = 11;                       //If you are using Software SPI, then you need to define the MISO line. Just comment this out for Hardware SPI.
    bme280.parameter.SPI_sck = 12;                        //If you are using Software SPI, then you need to define the SCK line. Same as before. For Hardware SPI, just comment this out.

    
  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  
    bme280.parameter.sensorMode = 0b11;                   //Choose sensor mode

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
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

    bme280.parameter.IIRfilter = 0b100;                    //Setup for IIR Filter

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
  //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero

  //0b000:      factor 0 (Disable humidity measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)
  
    bme280.parameter.humidOversampling = 0b101;            //Setup Humidity Oversampling

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements
  
  //0b000:      factor 0 (Disable temperature measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

    bme280.parameter.tempOversampling = 0b101;             //Setup Temperature Ovesampling

    

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default
  
  //0b000:      factor 0 (Disable pressure measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)
  
    bme280.parameter.pressOversampling = 0b101;            //Setup Pressure Oversampling 

    
  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE!************************
  
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa)
  
    bme280.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa

  //Now write here the current average temperature outside (yes, the outside temperature!)
  //You can either use the value in Celsius or in Fahrenheit, but only one of them (comment out the other value)
  //In order to calculate the altitude, this temperature is converted by the library into Kelvin
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C)
  //Remember, leave one of the values here commented, and change the other one!
  //If both values are left commented, the default temperature of 15°C will be used
  //But if both values are left uncommented, then the value in Celsius will be used    
  
    bme280.parameter.tempOutsideCelsius = 15;              //default value of 15°C
  //bme280.parameter.tempOutsideFahrenheit = 59;           //default value of 59°F
    
  
  //*********************************************************************
  //*************ADVANCED SETUP IS OVER - LET'S CHECK THE CHIP ID!*******
  
  if (bme280.init() != 0x60)
  {    
    
    
    Serial.println(F("Ops! BME280 could not be found!"));
    Serial.println(F("Please check your connections."));
    Serial.println();
    Serial.println(F("Troubleshooting Guide"));
    Serial.println(F("*************************************************************"));
    Serial.println(F("1. Let's check the basics: Are the VCC and GND pins connected correctly? If the BME280 is getting really hot, then the wires are crossed."));
    Serial.println();
    Serial.println(F("2. Are you using the I2C mode? Did you connect the SDI pin from your BME280 to the SDA line from the Arduino?"));
    Serial.println();
    Serial.println(F("3. And did you connect the SCK pin from the BME280 to the SCL line from your Arduino?"));
    Serial.println();
    Serial.println(F("4. Are you using the alternative I2C Address(0x76)? Did you remember to connect the SDO pin to GND?"));
    Serial.println();
    Serial.println(F("5. If you are using the default I2C Address (0x77), did you remember to leave the SDO pin unconnected?"));
    Serial.println();
    Serial.println(F("6. Are you using the SPI mode? Did you connect the Chip Select (CS) pin to the pin 10 of your Arduino (or to wherever pin you choosed)?"));
    Serial.println();
    Serial.println(F("7. Did you connect the SDI pin from the BME280 to the MOSI pin from your Arduino?"));
    Serial.println();
    Serial.println(F("8. Did you connect the SDO pin from the BME280 to the MISO pin from your Arduino?"));
    Serial.println();
    Serial.println(F("9. And finally, did you connect the SCK pin from the BME280 to the SCK pin from your Arduino?"));
    Serial.println();
    
    while(1);
  }

  else
  {
    Serial.println(F("BME280 detected!"));
  }
  Serial.println();
  Serial.println();

}
  //*********************************************************************
  //*************NOW LET'S START MEASURING*******************************
void loop() 
{ 
  
   
   Serial.print(F("Duration in Seconds:\t\t"));
   Serial.println(float(millis())/1000);
 
   Serial.print(F("Temperature in Celsius:\t\t")); 
   Serial.println(bme280.readTempC());
 
   Serial.print(F("Temperature in Fahrenheit:\t")); 
   Serial.println(bme280.readTempF());
   
   Serial.print(F("Humidity in %:\t\t\t")); 
   Serial.println(bme280.readHumidity());

   Serial.print(F("Pressure in hPa:\t\t")); 
   Serial.println(bme280.readPressure());

   Serial.print(F("Altitude in Meters:\t\t")); 
   Serial.println(bme280.readAltitudeMeter());

   Serial.print(F("Altitude in Feet:\t\t")); 
   Serial.println(bme280.readAltitudeFeet());
   
   Serial.println();
   Serial.println();

   delay(1000);   
 
}
