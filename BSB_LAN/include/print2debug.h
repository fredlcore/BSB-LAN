/* Functions for management "Ring" debug buffer */
/** *****************************************************************
 *  Function: printToDebug(char *), printToDebug(const char *), printToDebug(uint_farptr_t), printFmtToDebug()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *
 *  Pass parameters:
 *  EthernetClient telnetClient
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
  int len = vsnprintf(DebugBuff, sizeof(DebugBuff), format, args);
  va_end(args);
  switch (debug_mode) {
    case 1: SerialOutput->print(DebugBuff); break;
    case 2: if (haveTelnetClient)telnetClient.print(DebugBuff); break;
  }
  return len;
}

void writelnToDebug() {
  strcpy(DebugBuff, "\r\n");
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
  switch (debug_mode) {
    case 1: SerialOutput->print(format); break;
    case 2: if (haveTelnetClient)telnetClient.print(format); break;
  }
  return;
}

#define printlnToDebug(format) {printToDebug(format); writelnToDebug();}
