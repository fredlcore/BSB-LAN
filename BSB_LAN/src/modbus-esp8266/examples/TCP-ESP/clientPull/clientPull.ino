/*
  Modbus-Arduino Example -  Modbus IP Client (ESP8266/ESP32)
  Control Led on D4/TX pin by remote Modbus device using Read Single Coil Modbus Function

  (c)2018 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>


const int LED_COIL = 1;               // Modbus Coil Offset
IPAddress remote(192, 168, 30, 116);  // Address of Modbus Slave device

//Used Pins
#ifdef ESP8266
  #define USE_LED D4
 #else
  #define UES_LED TX
 #endif

ModbusIP mb;  //ModbusIP object

uint16_t gc(TRegister* r, uint16_t v) { // Callback function
  if (r->value != v) {  // Check if Coil state is going to be changed
    Serial.print("Set reg: ");
    Serial.println(v);
    if (COIL_BOOL(v)) {
      digitalWrite(USE_LED, LOW);
    } else {
      digitalWrite(USE_LED, HIGH);
    }
  }
  return v;
}

void setup() {
  Serial.begin(115200);
 
  WiFi.begin("SSID", "password");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();                    // Initialize local Modbus Client
  pinMode(USE_LED, OUTPUT);
  mb.addCoil(LED_COIL);           // Add Coil
  mb.onSetCoil(LED_COIL, gc);     // Assign Callback on set the Coil
}

void loop() {
  if (mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
    mb.pullCoil(remote, LED_COIL, LED_COIL);  // Initiate Read Coil from Modbus Slave
  } else {
    mb.connect(remote);           // Try to connect if no connection
  }
  mb.task();                      // Common local Modbus task
  delay(10);                     // Polling interval
}
