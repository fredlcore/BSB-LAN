/*
  Modbus-Arduino Example - Publish multiple DI as coils (Modbus IP ESP8266/ESP32)
  
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2018 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else	//ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

//Used Pins
#ifdef ESP8266
 uint8_t pinList[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};
#else	//ESP32
  uint8_t pinList[] = {12, 13, 14, 14, 16, 17, 18, 21, 22, 23};
#endif
#define LEN sizeof(pinList)/sizeof(uint8_t)
#define COIL_BASE 0
//ModbusIP object
ModbusIP mb;

// Callback function to read corresponding DI
uint16_t cbRead(TRegister* reg, uint16_t val) {
  // Checking value of register address which callback is called on.
  // See Modbus.h for TRegister and TAddress definition
  if(reg->address.address < COIL_BASE)
    return 0;
  uint8_t offset = reg->address.address - COIL_BASE;
  if(offset >= LEN)
    return 0; 
  return COIL_VAL(digitalRead(pinList[offset]));
}
// Callback function to write-protect DI
uint16_t cbWrite(TRegister* reg, uint16_t val) {
  return reg->value;
}

// Callback function for client connect. Returns true to allow connection.
bool cbConn(IPAddress ip) {
  Serial.println(ip);
  return true;
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin("ssid", "password");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  for (uint8_t i = 0; i < LEN; i++)
    pinMode(pinList[i], INPUT);
  mb.onConnect(cbConn);   // Add callback on connection event
  mb.server();

  mb.addCoil(COIL_BASE, COIL_VAL(false), LEN); // Add Coils.
  mb.onGetCoil(COIL_BASE, cbRead, LEN);  // Add single callback for multiple Coils. It will be called for each of these coils value get
  mb.onSetCoil(COIL_BASE, cbWrite, LEN); // The same as above just for set value
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   delay(10);
}