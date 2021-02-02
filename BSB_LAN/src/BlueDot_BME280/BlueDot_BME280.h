

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Wire.h"
#include "SPI.h"


#define BME280_CHIP_ID			0xD0
#define BME280_CTRL_HUM			0xF2
#define BME280_CTRL_MEAS		0xF4		
#define BME280_CONFIG			0xF5
#define BME280_PRESSURE_MSB		0xF7
#define BME280_PRESSURE_LSB		0xF8
#define BME280_PRESSURE_XLSB	0xF9
#define BME280_TEMPERATURE_MSB	0xFA
#define BME280_TEMPERATURE_LSB	0xFB
#define BME280_TEMPERATURE_XLSB	0xFC
#define BME280_HUMIDITY_MSB		0xFD
#define BME280_HUMIDITY_LSB		0xFE

 


enum Coefficients
{
	BME280_DIG_T1_LSB	=		0x88,
	BME280_DIG_T1_MSB	=		0x89,
	BME280_DIG_T2_LSB	=		0x8A,
	BME280_DIG_T2_MSB	=		0x8B,
	BME280_DIG_T3_LSB	=		0x8C,
	BME280_DIG_T3_MSB	=		0x8D,

	BME280_DIG_P1_LSB	=		0x8E,
	BME280_DIG_P1_MSB	=		0x8F,
	BME280_DIG_P2_LSB	=		0x90,
	BME280_DIG_P2_MSB	=		0x91,
	BME280_DIG_P3_LSB	=		0x92,
	BME280_DIG_P3_MSB	=		0x93,	
	BME280_DIG_P4_LSB	=		0x94,
	BME280_DIG_P4_MSB	=		0x95,
	BME280_DIG_P5_LSB	=		0x96,
	BME280_DIG_P5_MSB	=		0x97,	
	BME280_DIG_P6_LSB	=		0x98,
	BME280_DIG_P6_MSB	=		0x99,	
	BME280_DIG_P7_LSB	=		0x9A,
	BME280_DIG_P7_MSB	=		0x9B,
	BME280_DIG_P8_LSB	=		0x9C,
	BME280_DIG_P8_MSB	=		0x9D,
	BME280_DIG_P9_LSB	=		0x9E,
	BME280_DIG_P9_MSB	=		0x9F,
	
	BME280_DIG_H1		=		0xA1,
	BME280_DIG_H2_LSB	=		0xE1,
	BME280_DIG_H2_MSB	=		0xE2,
	BME280_DIG_H3		=		0xE3,
	BME280_DIG_H4_MSB	=		0xE4,
	BME280_DIG_H4_LSB	=		0xE5,
	BME280_DIG_H5_MSB	=		0xE6,
	BME280_DIG_H6		=		0xE7,
};


struct BME280_Coefficients
{
      uint16_t dig_T1;
      int16_t  dig_T2;
      int16_t  dig_T3;

      uint16_t dig_P1;
      int16_t  dig_P2;
      int16_t  dig_P3;
      int16_t  dig_P4;
      int16_t  dig_P5;
      int16_t  dig_P6;
      int16_t  dig_P7;
      int16_t  dig_P8;
      int16_t  dig_P9;

      uint8_t  dig_H1;
      int16_t  dig_H2;
      uint8_t  dig_H3;
      int16_t  dig_H4;
      int16_t  dig_H5;
      int8_t   dig_H6;
	  
};
	
	
struct DeviceParameter
{
	uint8_t communication = 0;
	int8_t SPI_cs;
	int8_t SPI_sck;
	int8_t SPI_mosi;
	int8_t SPI_miso;
	uint8_t I2CAddress;
	uint8_t sensorMode;
	uint8_t IIRfilter;
	uint8_t tempOversampling;
	uint8_t pressOversampling;
	uint8_t humidOversampling;
	uint16_t pressureSeaLevel;
	int16_t tempOutsideCelsius = 999;
	int16_t tempOutsideFahrenheit = 999;
	
};


class BlueDot_BME280 
{
 public: 
  
  DeviceParameter parameter;
  BME280_Coefficients bme280_coefficients;
  int32_t t_fine;
  
  
  BlueDot_BME280();
  uint8_t init(void);
  uint8_t checkID(void);
  uint8_t readByte(byte reg);
  uint8_t spiTransfer(uint8_t data);
  void writeByte(byte reg, byte value);
  void writeIIRFilter(void);
  void readCoefficients(void);
  void writeCTRLMeas(void);
  float readPressure(void);
  float readTempC(void);
  float readTempF(void);
  float readHumidity(void);
  float readAltitudeFeet(void);
  float readAltitudeMeter(void);
  float convertTempKelvin(void);

};

