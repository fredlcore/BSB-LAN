// Is this a broadcast message?
if (((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2] >= 0xF0 && bus->getBusType()==BUS_LPB)) && msg[4+(bus->offset)]==TYPE_INF) { // Only handle broadcast messages
  uint32_t cmd=(uint32_t)msg[5+(bus->offset)]<<24 | (uint32_t)msg[6+(bus->offset)]<<16 | (uint32_t)msg[7+(bus->offset)] << 8 | (uint32_t)msg[8+(bus->offset)];
  if (cmd==0x0500006B) {
    uint8_t error = msg[9+(bus->offset)];
    if (error > 0) {
      // Take note that the heating system will send error messages approx. once a minute until it is resolved.
      printFmtToDebug("Heating system reports error no. %d occurred!\r\n", msg[9+(bus->offset)]); // First byte of payload of 0x0500006B is the error code
      // Take some kind of action, such as notification, that goes beyond the common (MQTT-)handling of broadcast messages.
    } else {
      // Take note that it might happen that BSB-LAN doesn't catch the error == 0 broadcast
      printFmtToDebug("Heating system reports that previous error has been resolved.\r\n");
    }
  }
}