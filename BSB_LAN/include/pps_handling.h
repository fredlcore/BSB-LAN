// PPS-Bus handling
uint16_t pps_bus_handling(byte *msg) {
  uint16_t log_now = 0;
  if (msg[0] == 0x17 && pps_write == 1) { // Send client data
    byte tx_msg[] = {0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    byte rx_msg[10] = { 0 };
    switch (msg_cycle) {
      case 0:
        tx_msg[1] = 0x38; // Typ
        if (pps_values[PPS_QTP] == 0) pps_values[PPS_QTP] = QAA_TYPE;
        tx_msg[7] = pps_values[PPS_QTP];
        break;
      case 1:
        tx_msg[1] = 0x18; // Position Drehknopf
        tx_msg[6] = pps_values[PPS_PDK] >> 8;
        tx_msg[7] = pps_values[PPS_PDK] & 0xFF;
        break;
      case 2:
        tx_msg[1] = 0x28; // Raumtemperatur Ist
        tx_msg[6] = pps_values[PPS_RTI] >> 8;
        tx_msg[7] = pps_values[PPS_RTI] & 0xFF;
        break;
      case 3:
        tx_msg[1] = 0x19; // Raumtepmeratur Soll
        tx_msg[6] = pps_values[PPS_RTZ] >> 8;
        tx_msg[7] = pps_values[PPS_RTZ] & 0xFF;
        break;
      case 4:
        tx_msg[1] = 0x4E;
        tx_msg[7] = 0x00;
        break;
      case 5:
        tx_msg[1] = 0x49;     // Betriebsart
        tx_msg[7] = pps_values[PPS_BA];
        break;
      case 6:
        tx_msg[1] = 0x56;
        tx_msg[7] = 0x00;
        break;
      case 7:
      {
        if (pps_time_set == true) {
          bool found = false;
          bool next_active = true;
          int16_t current_time = hour() * 6 + minute() / 10;
          int8_t PPS_weekday = weekday() - 1;
          uint8_t next_switchday = 0;
          uint8_t next_switchtime = 0;
          if (PPS_weekday == 0) PPS_weekday = 7;
          uint8_t index = PPS_S11 + ((PPS_weekday - 1) * 6);
          while (!found) {
            if (current_time < pps_values[index] || (index >= PPS_S11 + ((PPS_weekday - 1 ) * 6) + 6)  || index < PPS_S11 + ((PPS_weekday - 1) * 6)) {
              if (pps_values[index] == 0x90) {
                if (PPS_weekday == 7) PPS_weekday = 0;
                index = PPS_S11 + PPS_weekday * 6;
              }
              next_switchtime = pps_values[index];
              next_switchday = ((index - PPS_S11) / 6) + 1;
              next_switchday = next_switchday + (0x10 * next_active);
              found = true;
            } else {
              index++;
              next_active = !next_active;
            }
            if (index > PPS_E73) index = PPS_S11;
          }
          tx_msg[1] = 0x69;
          tx_msg[6] = next_switchday;     // high nibble: current heating program (0x10 = reduced, 0x00 = comfort), low nibble: day of week
          tx_msg[7] = next_switchtime;    // next heating program time (encoded as one increment translates to one 10 minute block)

          if (current_switchday != next_switchday) {    // Set presence parameter to on or off at the beginning of (non-)heating timeslot
            pps_values[PPS_AW] = !next_active;
            current_switchday = next_switchday;
          }

          if (pps_values[PPS_AW] == 0) {                 // Set destination temperature (comfort + knob for heating period, otherwise reduced temperature)
            pps_values[PPS_RTZ] = pps_values[PPS_RTA];
          } else {
            pps_values[PPS_RTZ] = pps_values[PPS_RTS] + pps_values[PPS_PDK];
          }
          break;
        } else {
          msg_cycle++;  // If time is not yet set, above code is not executed, but following case will. Increase msg_cycle so that it is not run a second time in the next iteration.
        }
      }
//            break;
      case 8:
        tx_msg[1] = 0x08;     // Raumtemperatur Soll
        tx_msg[6] = pps_values[PPS_RTS] >> 8;
        tx_msg[7] = pps_values[PPS_RTS] & 0xFF;
        break;
      case 9:
        tx_msg[1] = 0x09;     // Raumtemperatur Abwesenheit Soll
        tx_msg[6] = pps_values[PPS_RTA] >> 8;
        tx_msg[7] = pps_values[PPS_RTA] & 0xFF;
        break;
      case 10:
        tx_msg[1] = 0x0B; // Trinkwassertemperatur Soll
        tx_msg[6] = pps_values[PPS_TWS] >> 8;
        tx_msg[7] = pps_values[PPS_TWS] & 0xFF;
        break;
      case 11:
        tx_msg[1] = 0x4C; // Präsenz
        tx_msg[7] = pps_values[PPS_AW];
        break;
      case 12:
        tx_msg[1] = 0x1E; // Trinkwassertemperatur Reduziert Soll
        tx_msg[6] = pps_values[PPS_TWR] >> 8;
        tx_msg[7] = pps_values[PPS_TWR] & 0xFF;
        break;
      case 13:
      {
        if ((pps_time_set == true || pps_wday_set == true) && pps_time_received == true) {
          tx_msg[0] = 0xFB; // send time to heater
          tx_msg[1] = 0x79;
          tx_msg[4] = (weekday()>1?weekday()-1:7); // day of week
          tx_msg[5] = hour(); // hour
          tx_msg[6] = minute(); // minute
          tx_msg[7] = second(); // second
          break;
        }
      }
      case 14:
      {
        if ((pps_time_set == true || pps_wday_set == true) && pps_time_received == true) {
          tx_msg[0] = 0xFE; // unknown telegram
          tx_msg[1] = 0x79;
          pps_time_set = false;
          pps_wday_set = false;
          break;
        }
      }
      case 15:
        tx_msg[1] = 0x60;
        tx_msg[2] = pps_values[PPS_E13];
        tx_msg[3] = pps_values[PPS_S13];
        tx_msg[4] = pps_values[PPS_E12];
        tx_msg[5] = pps_values[PPS_S12];
        tx_msg[6] = pps_values[PPS_E11];
        tx_msg[7] = pps_values[PPS_S11];
        break;
      case 16:
        tx_msg[1] = 0x61;
        tx_msg[2] = pps_values[PPS_E23];
        tx_msg[3] = pps_values[PPS_S23];
        tx_msg[4] = pps_values[PPS_E22];
        tx_msg[5] = pps_values[PPS_S22];
        tx_msg[6] = pps_values[PPS_E21];
        tx_msg[7] = pps_values[PPS_S21];
        break;
      case 17:
        tx_msg[1] = 0x62;
        tx_msg[2] = pps_values[PPS_E33];
        tx_msg[3] = pps_values[PPS_S33];
        tx_msg[4] = pps_values[PPS_E32];
        tx_msg[5] = pps_values[PPS_S32];
        tx_msg[6] = pps_values[PPS_E31];
        tx_msg[7] = pps_values[PPS_S31];
        break;
      case 18:
        tx_msg[1] = 0x63;
        tx_msg[2] = pps_values[PPS_E43];
        tx_msg[3] = pps_values[PPS_S43];
        tx_msg[4] = pps_values[PPS_E42];
        tx_msg[5] = pps_values[PPS_S42];
        tx_msg[6] = pps_values[PPS_E41];
        tx_msg[7] = pps_values[PPS_S41];
        break;
      case 19:
        tx_msg[1] = 0x64;
        tx_msg[2] = pps_values[PPS_E53];
        tx_msg[3] = pps_values[PPS_S53];
        tx_msg[4] = pps_values[PPS_E52];
        tx_msg[5] = pps_values[PPS_S52];
        tx_msg[6] = pps_values[PPS_E51];
        tx_msg[7] = pps_values[PPS_S51];
        break;
      case 20:
        tx_msg[1] = 0x65;
        tx_msg[2] = pps_values[PPS_E63];
        tx_msg[3] = pps_values[PPS_S63];
        tx_msg[4] = pps_values[PPS_E62];
        tx_msg[5] = pps_values[PPS_S62];
        tx_msg[6] = pps_values[PPS_E61];
        tx_msg[7] = pps_values[PPS_S61];
        break;
      case 21:
        tx_msg[1] = 0x66;
        tx_msg[2] = pps_values[PPS_E73];
        tx_msg[3] = pps_values[PPS_S73];
        tx_msg[4] = pps_values[PPS_E72];
        tx_msg[5] = pps_values[PPS_S72];
        tx_msg[6] = pps_values[PPS_E71];
        tx_msg[7] = pps_values[PPS_S71];
        break;
      case 22:
        tx_msg[1] = 0x7C;
        tx_msg[7] = pps_values[PPS_FDT];     // Verbleibende Feriendauer in Tagen
        break;
      case 23:
        tx_msg[1] = 0x1B;                    // Frostschutz- und Maximaltemperatur
        tx_msg[4] = pps_values[PPS_SMX] >> 8;
        tx_msg[5] = pps_values[PPS_SMX] & 0xFF;
        tx_msg[6] = pps_values[PPS_FRS] >> 8;
        tx_msg[7] = pps_values[PPS_FRS] & 0xFF;
    }
    msg_cycle++;
    if (msg_cycle > 23) {
      msg_cycle = 0;
    }
    if (saved_msg_cycle > 0) {
      msg_cycle = saved_msg_cycle;
      saved_msg_cycle = 0;
    }
    if (tx_msg[1] != 0xFF &&  pps_write == 1) {
      bus->Send(0, 0, rx_msg, tx_msg);
    }

    if (verbose) {     // verbose output for PPS after time-critical sending procedure
      if (!monitor) {
        printTelegram(msg, -1);
      } else {
        printFmtToDebug(PSTR("%lu "), millis());
      }
      printTelegram(tx_msg, -1);
#ifdef LOGGER
      if (!monitor) {
        LogTelegram(msg);
        LogTelegram(tx_msg);
      }
#endif
    }

  } else {    // parse heating system data

    if (msg[0] == 0x1E) {   // Anfragen der Therme nach bestimmten Parametern
      saved_msg_cycle = msg_cycle;
      switch (msg[1]) {
        case 0x08: msg_cycle = 8; break;
        case 0x09: msg_cycle = 9; break;
        case 0x0B: msg_cycle = 10; break;
        case 0x38: msg_cycle = 0; break;
        case 0x48: msg_cycle = 1; break;
        case 0x49: msg_cycle = 5; break;
        case 0x4C: msg_cycle = 11; break;
        case 0x4D: msg_cycle = 2; break;
        case 0x4F: msg_cycle = 3; break;
        case 0x60: msg_cycle = 15; break;
        case 0x61: msg_cycle = 16; break;
        case 0x62: msg_cycle = 17; break;
        case 0x63: msg_cycle = 18; break;
        case 0x64: msg_cycle = 19; break;
        case 0x65: msg_cycle = 20; break;
        case 0x66: msg_cycle = 21; break;
        case 0x7C: msg_cycle = 22; break;
        default:
          printToDebug(PSTR("Unknown request: "));
          SerialPrintRAW(msg, 9);
          writelnToDebug();
#ifdef LOGGER
/*
                File dataFile = SD.open(journalFileName, FILE_WRITE);
                if (dataFile) {
                  int outBufLen = 0;
                  outBufLen += sprintf_P(outBuf + outBufLen, PSTR("%lu;%s;Unknown PPS telegram;"), millis(), GetDateTime(outBuf + outBufLen + 80));
                  bin2hex(outBuf + outBufLen, msg, 9+(pps_write!=1 && msg[0] == 0x17), ' ');
                  dataFile.println(outBuf);
                }
                dataFile.close();
*/
#endif
        break;
/*
Weitere noch zu überprüfende Telegramme:
https://www.mikrocontroller.net/topic/218643#3517035
 17 FD 4A 00 3B 00 0B 0F 00 64
-> 0x3B = 59 % Brennerleistung
-> 0x000B = wahrscheinlich Status 11 (es gibt noch 7, 19 usw, sicher bin
ich mir da nicht)
-> 0x0F00 = 3840 / 64 = 60 °C Ist-Kesseltemperatur

*/

      }
    } else {    // Info-Telegramme von der Therme (0x1D)

//            uint8_t pps_offset = (msg[0] == 0x17 && pps_write != 1);
      uint8_t pps_offset = 0;
//            uint16_t temp = (msg[6+pps_offset] << 8) + msg[7+pps_offset];
      uint16_t temp = (msg[6] << 8) + msg[7];
      uint16_t i = sizeof(cmdtbl1)/sizeof(cmdtbl1[0]) + sizeof(cmdtbl2)/sizeof(cmdtbl2[0]) + sizeof(cmdtbl3)/sizeof(cmdtbl3[0]) - 1;
      while (i > 0 && get_cmdtbl_line(i) >= 15000) {
        uint32_t cmd = get_cmdtbl_cmd(i);
        cmd = (cmd & 0x00FF0000) >> 16;
//              if (cmd == msg[1+pps_offset]) {
        if (cmd == msg[1]) {
          break;
        }
        i--;
      }
      uint8_t flags=get_cmdtbl_flags(i);
      if (programIsreadOnly(flags) || pps_write != 1 || (msg[1+pps_offset] == 0x79 && pps_time_received == false)) {
        switch (msg[1+pps_offset]) {
          case 0x4F: log_now = setPPS(PPS_CON, msg[7+pps_offset]); saved_msg_cycle = msg_cycle; msg_cycle = 0; break;  // Gerät an der Therme angemeldet? 0 = ja, 1 = nein

          case 0x08: pps_values[PPS_RTS] = temp; break; // Raumtemperatur Soll
          case 0x09: pps_values[PPS_RTA] = temp; break; // Raumtemperatur Abwesenheit Soll
          case 0x0B: pps_values[PPS_TWS] = temp; break; // Trinkwassertemperatur Soll
          case 0x0C: pps_values[PPS_TWR] = temp; break; // Trinkwassertemperatur Reduziert Soll (?)
          case 0x0E: pps_values[PPS_KVS] = temp; break; // Vorlauftemperatur Soll (?)
          case 0x18: pps_values[PPS_PDK] = temp; break; // Position Drehknopf
          case 0x19: log_now = setPPS(PPS_RTZ, temp); break; // Raumtemperatur Zieltemperatur (nur bei Komforttemperatur, dann zzgl. Einstellung am Drehknopf)
          case 0x1E: pps_values[PPS_TWR] = temp; break; // Trinkwasser-Soll Reduziert
          case 0x28: pps_values[PPS_RTI] = temp; break; // Raumtemperatur Ist
          case 0x29: pps_values[PPS_AT] = temp; break; // Außentemperatur
          case 0x2B: pps_values[PPS_TWI] = temp; break; // Trinkwassertemperatur Ist
          case 0x2C: pps_values[PPS_MVT] = temp; break; // Mischervorlauftemperatur
          case 0x2E: pps_values[PPS_KVT] = temp; break; // Vorlauftemperatur
          case 0x38: pps_values[PPS_QTP] = msg[7+pps_offset]; break; // QAA type
          case 0x49: log_now = setPPS(PPS_BA, msg[7+pps_offset]); break; // Betriebsart
          case 0x4A: 
            pps_values[PPS_KVT] = temp;               // Kesselvorlauftemperatur bei MCBA-Systemen
            pps_values[PPS_MOD] = msg[3+pps_offset];  // Brennermodulation bei MCBA-Systemen
            setPPS(PPS_BRS, msg[5+pps_offset]);       // Brennerstatus bei MCBA_Systemen
            break;
          case 0x4C: log_now = setPPS(PPS_AW, msg[7+pps_offset]); break; // Komfort-/Eco-Modus
          case 0x4D: log_now = setPPS(PPS_BRS, msg[7+pps_offset]); break; // Brennerstatus
          case 0x57: pps_values[PPS_ATG] = temp; log_now = setPPS(PPS_TWB, msg[2+pps_offset]); break; // gemischte Außentemperatur / Trinkwasserbetrieb
          case 0x60:
            pps_values[PPS_S11] = msg[7+pps_offset];
            pps_values[PPS_E11] = msg[6+pps_offset];
            pps_values[PPS_S12] = msg[5+pps_offset];
            pps_values[PPS_E12] = msg[4+pps_offset];
            pps_values[PPS_S13] = msg[3+pps_offset];
            pps_values[PPS_E13] = msg[2+pps_offset];
            break;
          case 0x61:
            pps_values[PPS_S21] = msg[7+pps_offset];
            pps_values[PPS_E21] = msg[6+pps_offset];
            pps_values[PPS_S22] = msg[5+pps_offset];
            pps_values[PPS_E22] = msg[4+pps_offset];
            pps_values[PPS_S23] = msg[3+pps_offset];
            pps_values[PPS_E23] = msg[2+pps_offset];
            break;
          case 0x62:
            pps_values[PPS_S31] = msg[7+pps_offset];
            pps_values[PPS_E31] = msg[6+pps_offset];
            pps_values[PPS_S32] = msg[5+pps_offset];
            pps_values[PPS_E32] = msg[4+pps_offset];
            pps_values[PPS_S33] = msg[3+pps_offset];
            pps_values[PPS_E33] = msg[2+pps_offset];
            break;
          case 0x63:
            pps_values[PPS_S41] = msg[7+pps_offset];
            pps_values[PPS_E41] = msg[6+pps_offset];
            pps_values[PPS_S42] = msg[5+pps_offset];
            pps_values[PPS_E42] = msg[4+pps_offset];
            pps_values[PPS_S43] = msg[3+pps_offset];
            pps_values[PPS_E43] = msg[2+pps_offset];
            break;
          case 0x64:
            pps_values[PPS_S51] = msg[7+pps_offset];
            pps_values[PPS_E51] = msg[6+pps_offset];
            pps_values[PPS_S52] = msg[5+pps_offset];
            pps_values[PPS_E52] = msg[4+pps_offset];
            pps_values[PPS_S53] = msg[3+pps_offset];
            pps_values[PPS_E53] = msg[2+pps_offset];
            break;
          case 0x65:
            pps_values[PPS_S61] = msg[7+pps_offset];
            pps_values[PPS_E61] = msg[6+pps_offset];
            pps_values[PPS_S62] = msg[5+pps_offset];
            pps_values[PPS_E62] = msg[4+pps_offset];
            pps_values[PPS_S63] = msg[3+pps_offset];
            pps_values[PPS_E63] = msg[2+pps_offset];
            break;
          case 0x66:
            pps_values[PPS_S71] = msg[7+pps_offset];
            pps_values[PPS_E71] = msg[6+pps_offset];
            pps_values[PPS_S72] = msg[5+pps_offset];
            pps_values[PPS_E72] = msg[4+pps_offset];
            pps_values[PPS_S73] = msg[3+pps_offset];
            pps_values[PPS_E73] = msg[2+pps_offset];
            break;
          case 0x69: break;                             // Nächste Schaltzeit
          case 0x79:
          {
            if (pps_wday_set == false) {
              pps_values[PPS_DOW] = msg[4+pps_offset];    // Datum (msg[4] Wochentag)
            }
            int pps_hour, pps_minute, pps_second;
            if (pps_time_set == false) {
              pps_hour = msg[5+pps_offset];
              pps_minute = msg[6+pps_offset];
              pps_second = msg[5+pps_offset];
            } else {
              pps_hour = hour();
              pps_minute = minute();
              pps_second = second();
            }
            setTime(pps_hour, pps_minute, pps_second, pps_values[PPS_DOW], 1, 2018);
            pps_time_received = true;
            break;
          }
          case 0x7C: pps_values[PPS_FDT] = temp & 0xFF; // Verbleibende Ferientage
          case 0x48: log_now = setPPS(PPS_HP, msg[7+pps_offset]); break;   // Heizprogramm manuell/automatisch (0 = Auto, 1 = Manuell)
          case 0x1B:                                    // Frostschutz-Temperatur
            pps_values[PPS_FRS] = temp;
            pps_values[PPS_SMX] = (msg[4+pps_offset] << 8) + msg[5+pps_offset];
            break;
          case 0x00: break;
          default:
            printToDebug(PSTR("Unknown telegram: "));
            SerialPrintRAW(msg, 9 + pps_offset);
            writelnToDebug();
            break;
        }
      }

/*
            printToDebug(PSTR("Outside Temperature: "));
            DebugOutput.println(outside_temp);
            printToDebug(PSTR("Boiler Temperature: "));
            DebugOutput.println(boiler_temp);
            printToDebug(PSTR("Mixer Flow Temperature: "));
            DebugOutput.println(mixer_flow_temp);
            printToDebug(PSTR("Flow Temperature: "));
            DebugOutput.println(flow_temp);
            printToDebug(PSTR("Weighted Temperature: "));
            DebugOutput.println(weighted_temp);
            printToDebug(PSTR("Boiler active: "));
            if (boiler_active) {
              printlnToDebug(PSTR("yes"));
            } else {
              printlnToDebug(PSTR("no"));
            }
            printToDebug(PSTR("Time: ")); DebugOutput.print(d); DebugOutput.print(", "); DebugOutput.print(h); DebugOutput.print(":"); DebugOutput.print(m); DebugOutput.print(":"); DebugOutput.println(s);
*/
    } // End parsing 0x1D heater telegrams

    if (verbose && !monitor) {     // verbose output for PPS after time-critical sending procedure
      printTelegram(msg, -1);
#ifdef LOGGER
      LogTelegram(msg);
#endif
    }
  } // End parse PPS heating data
  return log_now;
}

void pps_query_mcba() {
  byte rx_msg[10] = { 0 };
  byte tx_msg[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  if (msg_cycle % 4 == 0) {         // Trinkwassertemperatur (Reduziert?) Soll
    tx_msg[0] = 0x1D;
    tx_msg[1] = 0x0C;
    tx_msg[6] = pps_values[PPS_TWS] >> 8;
    tx_msg[7] = pps_values[PPS_TWS] & 0xFF;
  } else if(msg_cycle % 2 == 0) {   // Kesselvorlauftemperatur Soll
    tx_msg[0] = 0x1D;
    tx_msg[1] = 0x0E;
    tx_msg[6] = pps_values[PPS_KVS] >> 8;
    tx_msg[7] = pps_values[PPS_KVS] & 0xFF;
  } else {                          // Request telegram from heater
    tx_msg[0] = 0x17;
  }
  if (pps_write == 1) {
    bus->Send(0, 0, rx_msg, tx_msg);
  }
  if (verbose) {     // verbose output for PPS after time-critical sending procedure
    if (monitor) {
      printFmtToDebug(PSTR("%lu "), millis());
    }
    printTelegram(tx_msg, -1);
#ifdef LOGGER
    if (!monitor) {
      LogTelegram(tx_msg);
    }
#endif
  }
  msg_cycle++;
  if (msg_cycle > 3) {
    msg_cycle = 0;
  }
}
