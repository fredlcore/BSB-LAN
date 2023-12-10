/*
  ModbusRTU ESP32
  Minimalistic example of server responding for multiple IDs. That is the server looks as multiple devices on bus.

  (c)2022 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266

  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <ModbusRTU.h>

#define REGN 10
#define PRIMARY_ID 1
#define PRIMERT_VALUE 100
#define SECONDARY_ID 2
#define SECONDARY_VALUE 200

ModbusRTU mb;

Modbus::ResultCode cbRtuRaw(uint8_t* data, uint8_t len, void* custom) {
  auto src = (Modbus::frame_arg_t*) custom; // <custom> argument contains some data on incoming packet
  Serial.printf("RTU Slave: %d, Fn: %02X, len: %d, ", src->slaveId, data[0], len);
  if (src->slaveId == SECONDARY_ID)   // Check if incoming packet is addresses to server with ID <SECONDARY_ID>
    return Modbus::EX_FORCE_PROCESS;  // Instruct the library to force the packet processing
                                      // It's required as otherwise packet will be not processed as not addressed
                                      // to the server <PRIMARY_ID>

  return Modbus::EX_PASSTHROUGH;      // or process packet normally
}

uint16_t cbRead(TRegister* reg, uint16_t val) {
    if (mb.eventSource() == SECONDARY_ID)
        return SECONDARY_VALUE;
    return val;
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  mb.begin(&Serial1);
  mb.slave(PRIMARY_ID); // Set Modbus to work as a server with ID <PRIMARY_ID>
  mb.onRaw(cbRtuRaw); // Assign raw packet callback
  mb.addHreg(REGN, PRIMARY_VALUE);
  mb.onGet(cbReadHreg)
}

void loop() {
  mb.task();
  yield();
}