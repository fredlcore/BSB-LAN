/* Functions for management "Ring" debug buffer */
/** *****************************************************************
 *  Function: printToDebug(char *), printToDebug(const char *), printToDebug(uint_farptr_t), printFmtToDebug()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *
 *  Pass parameters:
 *  WiFiSpiClient/EthernetClient telnetClient
 *  Serial
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   DebugBuff variable
 * *************************************************************** */
 int printFmtToDebug(const char *format, ...) {
  va_list args;
  va_start(args, format);
#if defined(__AVR__)
  int len = vsnprintf_P(DebugBuff, sizeof(DebugBuff), format, args);
#else
  int len = vsnprintf(DebugBuff, sizeof(DebugBuff), format, args);
#endif
  va_end(args);
  switch (debug_mode) {
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if (haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  return len;
}

void writelnToDebug() {
#if defined(__AVR__)
  strcpy_P(DebugBuff, PSTR("\r\n"));
#else
  strcpy(DebugBuff, PSTR("\r\n"));
#endif
  switch (debug_mode) {
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if (haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
}

void printToDebug(char *format) {
  switch (debug_mode) {
    case 1: SerialOutput->print(format); break;
    case 2: if (haveTelnetClient)telnetClient.print(format); break;
  }
  return;
}

void printToDebug(const char *format) {
  #if defined(__AVR__)
  strcpy_P(DebugBuff, format);
  switch (debug_mode) {
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if (haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  #else
  switch (debug_mode) {
    case 1: SerialOutput->print(format); break;
    case 2: if (haveTelnetClient)telnetClient.print(format); break;
  }
  #endif
  return;
}

#if defined(__AVR__)
void printToDebug(uint_farptr_t src) {
  strcpy_PF(DebugBuff, src);
  switch (debug_mode) {
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if (haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  return;
}
#endif

#define printlnToDebug(format) {printToDebug(format); writelnToDebug();}
