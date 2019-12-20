#ifndef __EEPHANDLER_H__
#define __EEPHANDLER_H__

#include <Arduino.h>


#ifdef EEP_DEBUG
    #define eepdebug(...)   EEP_DEBUG.print(__VA_ARGS__)
    #define eepdebugln(...) EEP_DEBUG.println(__VA_ARGS__)
#else
    #define eepdebug(...)
    #define eepdebugln(...)
#endif




#ifndef EEP_WIRE
  // definiert in TinyWireM.h
  #ifdef TinyWireM_h 
  #define EEP_WIRE TinyWireM
  #endif
  
  
  // definiert in Wire.h
  #ifdef TwoWire_h 
  #define EEP_WIRE Wire
  #endif
#endif  

#ifndef EEP_WIRE
#error Weder Wire, noch TinyWireM gefunden.  EEP_WIRE ist nicht definiert.
#endif


template<uint8_t I2CADDRESS,uint32_t EEPLENGHT,uint8_t ADDRESSMODE,uint8_t PAGELENGTH> 
class eephandler
{
  private:
  enum ACCESSMODE {WRITEMODE,READMODE}; // Schreib/Lese Modus
  
  void (*onwaiting)() = 0;        // onWaiting Callback nullptr
  
  
  // prüft, ob Baustein unter der Adresse beschäftigt ist
  bool busy(uint16_t address)          // ACKNOWLEDGE POLLING
  {
    int Adresse = I2CADDRESS;  
    switch(ADDRESSMODE)
    {
      case 1 :  {Adresse +=  address >> 8;} break;
    }
    EEP_WIRE.beginTransmission(Adresse); 
    return (bool) EEP_WIRE.endTransmission();  
  }
  
  // aktives Warten, Rechenzeit wird abgegeben
  void wait(uint16_t address)
  {
    while(busy(address))
       if(onwaiting) 
       {
        onwaiting(); // Callback aufrufen
        eepdebugln("Wait for next I2C Access");
       } 
  }
  
  // lesen einer Page, oder eines Teils davon
  void pageRead(uint16_t address,uint8_t * start,uint16_t length)
  {
    uint8_t highaddr = (uint8_t)(address  >> 8);
    uint8_t lowaddr  = (uint8_t)(address & 0x00ff);
    int Adresse = I2CADDRESS;
    if(address + length >= EEPLENGHT) // adress überschreitung
    {
        eepdebug("pageRead Addressueberschreitung ");
        eepdebugln(address); 
        return; 
    }
    wait(address);
    switch(ADDRESSMODE)
    {
      case 1 :  {
                   Adresse += highaddr ;
                   eepdebugln("Addressmode 1");
                   EEP_WIRE.beginTransmission(Adresse); 
                 } break;
      case 2 :   {
                     EEP_WIRE.beginTransmission(Adresse); 
                     eepdebugln("Addressmode 2");
                     EEP_WIRE.write(highaddr);       
                 } break;
    }
    EEP_WIRE.write(lowaddr);       
    EEP_WIRE.endTransmission();    
    EEP_WIRE.requestFrom(Adresse,length);
    while(EEP_WIRE.available()) 
      *start++ = EEP_WIRE.read();
    eepdebug("pageRead -- I2C=0x");            
    eepdebug(Adresse,HEX);            
    eepdebug(" HighAddr=");            
    eepdebug(highaddr);            
    eepdebug(" LowAddr=");            
    eepdebug(lowaddr);            
    eepdebug(" Length=");            
    eepdebugln(length);            
  }

  // schreiben einer Page, oder eines Teils davon
  void pageWrite(uint16_t address,uint8_t * start, uint16_t length)
  {
    uint8_t highaddr = (uint8_t)(address  >> 8);
    uint8_t lowaddr  = (uint8_t)(address & 0x00ff);
    int Adresse = I2CADDRESS;
    if(address + length >= EEPLENGHT) // adress überschreitung
    {
        eepdebug("pageWrite Addressueberschreitung ");
        eepdebugln(address); 
        return; 
    }
    wait(address);
    switch(ADDRESSMODE)
    {
      case 1 :  {
                  Adresse += highaddr ;
                  eepdebugln("Addressmode 1");
                  EEP_WIRE.beginTransmission(Adresse); 
                } break;
      case 2 :   {
                   EEP_WIRE.beginTransmission(Adresse); 
                   eepdebugln("Addressmode 2");
                   EEP_WIRE.write(highaddr);       
                 } break;
    }
    EEP_WIRE.write(lowaddr);    
    for(int i = 0; i<length;i++)   
        EEP_WIRE.write(*start++);             
    EEP_WIRE.endTransmission();  
    eepdebug("pageWrite -- I2C=0x");            
    eepdebug(Adresse,HEX);            
    eepdebug(" HighAddr=");            
    eepdebug(highaddr);            
    eepdebug(" LowAddr=");            
    eepdebug(lowaddr);            
    eepdebug(" Length=");            
    eepdebugln(length);            
  }
  
  // splitten eines BlockZugriffs in Pages
  template<ACCESSMODE MODE>
  void fastBlock(uint16_t address,void * start, uint16_t length)
  {
    uint16_t toReadWrite  = length;
    uint8_t * ptr = (uint8_t*)start;
    uint16_t addresse = address;
    while(toReadWrite>0)
    {
      int pageoffset = addresse % PAGELENGTH;
      int count      = PAGELENGTH - pageoffset;
      if (count > toReadWrite) count = toReadWrite;
      switch(MODE)
      {
        case READMODE  :  {pageRead(addresse,ptr,count);}  break;
        case WRITEMODE :  {pageWrite(addresse,ptr,count);}  break;
      }
      ptr += count;
      toReadWrite -= count;
      addresse += count;
    }
  }


  public:
  
  // Blockschreiben unter ausnutzung der max. Pagelen
  void fastBlockWrite(uint16_t address,void * start, uint16_t length)
  {
    fastBlock<WRITEMODE>(address,start,length);
  }
  
   // Blocklesen unter ausnutzung der max. Pagelen
  void fastBlockRead(uint16_t address,void * start, uint16_t length)
  {
    fastBlock<READMODE>(address,start,length);
  }
  
  // Baustein Bereit?
  bool ready()
  {
    return !busy(I2CADDRESS);
  }
  
  // größe des eeproms in Byte
  unsigned long length()
  {
    return EEPLENGHT;
  }  

  // einzelnes Byte schreiben 
  void write(uint16_t address,uint8_t value)
  {
    pageWrite(address,&value,1);
  }
  
  // einzelnes Byte lesen
  uint8_t read(uint16_t address)
  {
    uint8_t result = 0; 
    pageRead(address,&result,1);
    return   result; 
  }
  
  // Byte schreiben, wenn ungleich vorhandenem
  void update(uint16_t address,uint8_t value)
  {
    uint8_t old = read(address);
    if (old != value) write(address,value);
  }
  
  // lesen beliebiger Datentypen
  template< typename T >
  void get(uint16_t address, T &customvar)
//  T &get(uint16_t address, T &customvar)
  {
    uint8_t *ptr = (uint8_t*) &customvar;
    for(int i = 0; i < sizeof(T); i++)
      *ptr++ = read(address + i);
   // return &customvar;
  }

 

  // schreiben beliebiger Datentypen
  template< typename T >
  void put(uint16_t address,T &customvar)
//  T put(uint16_t address,T &customvar)
  {
    uint8_t *ptr = (uint8_t*) &customvar;
    for(int i = 0; i < sizeof(T); i++)
       update(address + i,*ptr++);
    // return &customvar;
  }
  
  // callback speichern
  void onWaiting( void (*callback)())
  {
    onwaiting = callback;  
  }
  
};


#endif
