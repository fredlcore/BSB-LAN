#ifndef __I2C_EEPROM_H__
#define __I2C_EEPROM_H__


#include "inc/eephandler.h"


/**
 * 
 *
 *  *****************************
 * Anlegen eigener EEProms: 
 * eephandler<uint8_t I2CADDRESS,uint16_t EEPLENGHT,uint8_t ADDRESSMODE,uint8_t PAGELENGTH> 
 * I2CADDRESS -- Die i2c basisaddresse des eeproms
 * Manche EEProms belegen mehrere Addressen, das wird abgehandelt.
 * Manche haben Addresspins A0 bis A2 um die Basisadresse festzulegen 
 * Ein I2C Scanner gibt gerne Auskunft.   
 *  
 * EEPLENGHT -- größe des EEProm in Byte
 *  
 * ADDRESSMODE -- größere EEProms haben eine 2 Byte Adresse
 * kleinere eine 1 Byte Adresse, teilweise werden Adressbits in die DeviceAdresse übernommen.   
 *  
 * PAGELENGTH -- größt mögliche Schreib/Lesemenge
 * Je nach Baustein, aber maximal 32, wegen der beschränkten Buffergröße von Wire 
 * 
 * Bitte Datenblatt des jeweiligen Herstellers konsultieren.
 *    
 *    
*/


  //Atmel
template<uint8_t I2CADDRESS=0x50> class AT24C01   : public  eephandler<I2CADDRESS,  128UL,1, 8>{}; 
template<uint8_t I2CADDRESS=0x50> class AT24C02   : public  eephandler<I2CADDRESS,  256UL,1, 8>{};
template<uint8_t I2CADDRESS=0x50> class AT24C04   : public  eephandler<I2CADDRESS,  512UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class AT24C08   : public  eephandler<I2CADDRESS, 1024UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class AT24C16   : public  eephandler<I2CADDRESS, 2048UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class AT24C32   : public  eephandler<I2CADDRESS, 4096UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class AT24C64   : public  eephandler<I2CADDRESS, 8192UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class AT24C128  : public  eephandler<I2CADDRESS,16384UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class AT24C256  : public  eephandler<I2CADDRESS,32768UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class AT24C512  : public  eephandler<I2CADDRESS,65536UL,2,32>{};


//STMicroelectronics
template<uint8_t I2CADDRESS=0x50> class  M24C01  : public  eephandler<I2CADDRESS,  128UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class ST24C01  : public  eephandler<I2CADDRESS,  128UL,1, 8>{};
template<uint8_t I2CADDRESS=0x50> class  M24C02  : public  eephandler<I2CADDRESS,  256UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class ST24C02  : public  eephandler<I2CADDRESS,  256UL,1, 8>{};
template<uint8_t I2CADDRESS=0x50> class  M24C04  : public  eephandler<I2CADDRESS,  512UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class ST24C04  : public  eephandler<I2CADDRESS,  512UL,1, 8>{};
template<uint8_t I2CADDRESS=0x50> class  M24C08  : public  eephandler<I2CADDRESS, 1024UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class ST24C08  : public  eephandler<I2CADDRESS, 1024UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class  M24C16  : public  eephandler<I2CADDRESS, 2048UL,1,16>{};
template<uint8_t I2CADDRESS=0x50> class ST24C32  : public  eephandler<I2CADDRESS, 4096UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class  M24C64  : public  eephandler<I2CADDRESS, 8192UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class  M24128  : public  eephandler<I2CADDRESS,16384UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class  M24256  : public  eephandler<I2CADDRESS,32768UL,2,32>{};
template<uint8_t I2CADDRESS=0x50> class  M24512  : public  eephandler<I2CADDRESS,65536UL,2,32>{};


// Microchip
template<uint8_t I2CADDRESS=0x50> class MC24C01      : public  eephandler<I2CADDRESS, 128UL,1,16>{};  
template<uint8_t I2CADDRESS=0x50> class MC24AA02E48  : public  eephandler<I2CADDRESS, 256UL,1, 8>{};  
template<uint8_t I2CADDRESS=0x50> class MC24AA025E48 : public  eephandler<I2CADDRESS, 256UL,1,16>{};  


#endif
