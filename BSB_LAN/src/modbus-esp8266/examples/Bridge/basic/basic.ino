/*
  Modbus ESP8266/ESP32
  Simple ModbesRTU to ModbusIP bridge

  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/
#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
#include <ModbusRTU.h>

#define TO_REG 10
#define SLAVE_ID 1
#define PULL_ID 1
#define FROM_REG 20

ModbusRTU mb1;
ModbusIP mb2;

void setup() {
  Serial.begin(115200);
   WiFi.begin("SSID", "PASSWORD");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial1.begin(9600, SERIAL_8N1); // Init Serial on default pins
  //Serial2.begin(19200, SERIAL_8N1, 19, 18); // Override default pins for ESP32
  mb1.begin(&Serial1);
  //mb1.begin(&Serial2, 17);  // Specify RE_DE control pin
  mb1.master();
  mb2.server();
  mb2.addHreg(TO_REG);
}

void loop() {
  if(!mb1.slave())
    mb1.pullHreg(PULL_ID, FROM_REG, TO_REG);
  mb1.task();
  mb2.task();
  delay(50);
}