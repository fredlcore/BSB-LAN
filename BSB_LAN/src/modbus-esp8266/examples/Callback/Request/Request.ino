/*
  Modbus-Arduino Example - Using request processing callback to control access to Hreg write operations
 
  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusTCP.h>

const uint16_t RO_FLAG = 100; // Coil register to allow/disallow Hregs write
const uint16_t RW_HREG = 200; // Sample Hreg

//ModbusIP object
ModbusTCP mb;

Modbus::ResultCode cbPreRequest(Modbus::FunctionCode fc, const Modbus::RequestData data) {
  Serial.printf("PRE Function: %02X\n", fc);
  if ((fc == Modbus::FC_WRITE_REG || fc == Modbus::FC_WRITE_REGS) && mb.Coil(RO_FLAG))
    return Modbus::EX_ILLEGAL_FUNCTION;
  return Modbus::EX_SUCCESS;
}

Modbus::ResultCode cbPostRequest(Modbus::FunctionCode fc, const Modbus::RequestData data) {
  Serial.printf("POST Function: %02X\n", fc);
  return Modbus::EX_SUCCESS;
}

// Callback function for client connect. Returns true to allow connection.
bool cbConn(IPAddress ip) {
  Serial.println(ip);
  return true;
}
 
void setup() {
  Serial.begin(115200);

  WiFi.begin("SID", "PASSWORD");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  mb.onConnect(cbConn);   // Add callback on connection event
  mb.onRequest(cbPreRequest);
  mb.onRequestSuccess(cbPostRequest);
  mb.server();

  mb.addCoil(RO_FLAG);
  mb.addHreg(RW_HREG, 100);
}

void loop() {
   mb.task();
   delay(10);
}