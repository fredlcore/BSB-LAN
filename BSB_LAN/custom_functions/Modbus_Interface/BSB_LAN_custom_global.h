/*
 * These three scripts need to be copied to the main directory in order to start a Modbus server that will relay queries 
 * from Modbus to the heating system and return the requested parameter values. Writing parameters is also possible.
 * You need to define the parameters that should be allowed to be queried via the mb.addHreg function in BSB_LAN_custom_setup.h
 * Since querying/setting parameters from/to the heating system may take up to two seconds, make sure that the Modbus client does not
 * exit prematurely due to a timeout.
*/

#include "src/modbus-esp8266/src/ModbusTCP.h"
ModbusTCP mb;

// Remove this function when using Modbus RTU (over serial/RS485)
bool cbConn(IPAddress ip) {     
  Serial.print("Modbus connection from IP: ");
  Serial.println(ip);
  return true;  // return false for example to prevent forbidden IP ranges
}

// Callback for querying a parameter - value will be queried from heating system and returned to Modbus client
// This function only supports integers up to 16 bit unsigned.
// Any other values will require further encoding into Modbus' 16 bit unsigned integers to whatever necessary value here!
uint16_t cbGet(TRegister* reg, uint16_t val) {
  uint16_t param = reg->address.address;
  query(param);
  if (decodedTelegram.prognr < 0) return 65535;
  val = strtod(decodedTelegram.value, NULL);
  return val;
}

// Callback for setting a parameter - value received will be sent to the heating system
// This function only supports integers up to 16 bit unsigned.
// Any other values will require further decoding from Modbus' 16 bit unsigned integers to whatever necessary value here!
uint16_t cbSet(TRegister* reg, uint16_t val) {
  uint16_t param = reg->address.address;
  char val_as_char[20];
  sprintf(val_as_char, "%d", val);
  set(param, (char*)val_as_char, (param!=10000?1:0));       // dirty hack to send INF for paramater 10000
//  Serial.println(val);                // new value
//  Serial.println(reg->value);         // previous value in register
//  Serial.println(reg->address.type);  // register type (03 = holding register)
  return val;
}