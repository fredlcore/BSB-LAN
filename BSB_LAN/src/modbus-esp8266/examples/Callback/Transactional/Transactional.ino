/*
  Modbus-Arduino Example - Modbus IP Client (ESP8266/ESP32)
  Write multiple coils to Slave device

  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

const int REG = 100;                    // Modbus Coils Offset
const int COUNT = 5;                    // Count of Coils
IPAddress remote(192, 168, 20, 102);    // Address of Modbus Slave device

ModbusIP mb;  // ModbusIP object

void setup() {
  Serial.begin(115200);
 
  WiFi.begin();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();
}

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    Serial.printf("Modbus result: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    mb.disconnect(remote);              // Close connection to slave and
    mb.dropTransactions();              // Cancel all waiting transactions
  }
  return true;
}

bool res[COUNT] = {false, true, false, true, true};

void loop() {
    if (!mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
        mb.connect(remote);           // Try to connect if no connection
        Serial.print(".");
    }
    if (!mb.writeCoil(remote, REG, res, COUNT, cb)) // Try to Write array of COUNT of Coils to Modbus Slave
        Serial.print("#");  
    mb.task(); // Modbus task
    delay(50); // Pushing interval
}