void broadcast_msg_handling(byte *msg){
  // Is this a broadcast message?
  if (((msg[2]==ADDR_ALL && bus->getBusType()==BUS_BSB) || (msg[2]>=0xF0 && bus->getBusType()==BUS_LPB)) && msg[4+(bus->offset)]==TYPE_INF) { // handle broadcast messages
  // Decode the rcv telegram and send it to the PC serial interface
    if (!verbose && !monitor) {        // don't log twice if in verbose mode, but log broadcast messages also in non-verbose mode
      printTelegram(msg, -1);
      LogTelegram(msg);
    }

    // Filter Brenner Status messages

    uint32_t cmd;
    cmd=(uint32_t)msg[5+(bus->offset)]<<24 | (uint32_t)msg[6+(bus->offset)]<<16 | (uint32_t)msg[7+(bus->offset)] << 8 | (uint32_t)msg[8+(bus->offset)];
    if (cmd==0x0500006C && !ntp_server[0]) {   // set Time from BC unless NTP is used, same CommandID for BSB and LPB
      setTime(msg[bus->getPl_start()+5], msg[bus->getPl_start()+6], msg[bus->getPl_start()+7], msg[bus->getPl_start()+3], msg[bus->getPl_start()+2], msg[bus->getPl_start()+1]+1900);
    }

    if (cmd==0x31000212) {    // TWW Status
      printFmtToDebug("INF: TWW-Status: %d\r\n", msg[11+bus->offset]);

      if (msg[11+bus->offset] & 0x08) {  // See parameter 10018
        if (TWW_start==0) {        // has not been timed
          TWW_start=millis();   // keep current timestamp
          TWW_count++;          // increment number of starts
        }
      } else {             // TWW Ladung aus
        if (TWW_start!=0) {        // start has been timed
          unsigned long TWW_end;
          TWW_end=millis();      // timestamp the end
          if (TWW_end >= TWW_start) {
            TWW_duration+=(TWW_end-TWW_start)/1000;
          } else { // overflow
            TWW_duration+=(0xffffffff-TWW_start+TWW_end)/1000;
          }
            TWW_start=0;
        } // endif, a previous start has been timed
      } // endif, TWW is off
    } // endif, Status TWW command code

    if (cmd==0x05000213) {     // Brennerstatus: Payload byte 0: bit 3 (0x04) = Stufe 1, bit 5 (0x10) = Stufe 2, payload byte 1: 0x81 = Handbetrieb
      unsigned long brenner_end;
      bool reset_brenner_timer = 0;
      printFmtToDebug("INF: Brennerstatus: %d\r\n", msg[bus->getPl_start()]);      // first payload byte

      if (msg[bus->getPl_start()] & 0x04) {       // Stufe 1
        if (brenner_start==0) {        // has not been timed
          brenner_start=millis();   // keep current timestamp
          brenner_count++;          // increment number of starts
        }
        if (brenner_stufe == 2) {
          reset_brenner_timer = 1;
        }
        brenner_stufe=1;
      }
      if (msg[bus->getPl_start()] & 0x10) {       // Stufe 2 (only oil furnace)
        if (brenner_start_2==0) {        // has not been timed
          brenner_start_2=millis();   // keep current timestamp
          brenner_count_2++;          // increment number of starts
        }
        if (brenner_stufe == 1) {
          reset_brenner_timer = 1;
        }
        brenner_stufe=2;
      }
      if (reset_brenner_timer == 1) {   // Stufenwechsel bei mehrstufigem Ölbrenner
        brenner_end=millis();      // timestamp the end
        if (brenner_stufe == 2) {    // Stufe jetzt 2, war also vorher 1
          if (brenner_end >= brenner_start) {
            brenner_duration+=(brenner_end-brenner_start)/1000;
          } else { // overflow
            brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
          }
          brenner_start=0;
        }
        if (brenner_stufe == 1) {   // Stufe jetzt 1, war also vorher 2
          if (brenner_end >= brenner_start_2) {
            brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
          } else { // overflow
            brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
          }
          brenner_start_2=0;
        }
        reset_brenner_timer = 0;
      }
      if ((msg[bus->getPl_start()] & 0x0F) != 0x04) {    // brenner off
        brenner_end=millis();      // timestamp the end
        brenner_stufe=0;
        if (brenner_start!=0) {        // start has been timed
          if (brenner_end >= brenner_start) {
            brenner_duration+=(brenner_end-brenner_start)/1000;
          } else { // overflow
            brenner_duration+=(0xffffffff-brenner_start+brenner_end)/1000;
          }
          brenner_start=0;
        } // endif, a previous start has been timed
        if (brenner_start_2!=0) {        // start has been timed
          if (brenner_end >= brenner_start_2) {
            brenner_duration_2+=(brenner_end-brenner_start_2)/1000;
          } else { // overflow
            brenner_duration_2+=(0xffffffff-brenner_start_2+brenner_end)/1000;
          }
          brenner_start_2=0;
        } // endif, a previous start has been timed
      } // endif, brenner is off
    } // endif, Status Brenner command code
  } // endif, broadcasts
}
