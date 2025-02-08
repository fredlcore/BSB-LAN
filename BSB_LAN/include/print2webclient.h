
/* Functions for management "Ring" output buffer */
/** *****************************************************************
 *  Function: printToWebClient(char *), printToWebClient(const char *), printToWebClient(uint_farptr_t), printFmtToWebClient()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *         flushToWebClient() can be called when you want.
 *         forcedflushToWebClient() must be called before end of connection
 *  Pass parameters:
 *  EthernetClient &cl
 * Parameters passed back:
 *   none
 * Function value returned:
 *   none
 * Global resources used:
 *   bigBuffPos and bigBuff variable
 * *************************************************************** */

void flushToWebClient() {
  if (bigBuffPos > 0) {
    // for debug purposes
    //if (bigBuffPos > sizeof(bigBuff)) printlnToDebug("bigBuffPos > bigBuff size");
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
    return;
  }
// for debug purposes
//  if (bigBuffPos < 0)  printlnToDebug("bigBuffPos is negative");
}

void forcedflushToWebClient() {
  if (bigBuffPos > 0) {
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
  }
//  client.flush();     // check if substitute for flush() is available since it is now deprecated. clear() only clears the RX buffer, but we want to flush the TX buffer.
}

int writelnToWebClient() {
  int len = strlen(strcpy(bigBuff + bigBuffPos, "\r\n"));
  bigBuffPos += len;
  return len;
}

int printToWebClient(char *format) {
  int len = strlen(strcpy(bigBuff + bigBuffPos, format));
  bigBuffPos += len;
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

int printToWebClient(const char *format) {
  int len = strlen(strcpy(bigBuff + bigBuffPos, format));
  bigBuffPos += len;
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

#define printlnToWebClient(format) (printToWebClient(format), writelnToWebClient())

int printFmtToWebClient(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int len = vsprintf(bigBuff + bigBuffPos, format, args);
  bigBuffPos += len;
  va_end(args);
  if (bigBuffPos > OUTBUF_USEFUL_LEN) {
    flushToWebClient();
  }
  return len;
}

void printToWebClient_prognrdescaddr() {
  if (decodedTelegram.prognr < 0) return;
  if (decodedTelegram.prognr >= (float)BSP_AVERAGES && decodedTelegram.prognr < (float)BSP_DHT22) {
    printToWebClient(STR_24A_TEXT);
    printToWebClient(". ");
  }
  printToWebClient(decodedTelegram.prognrdescaddr);
  if (decodedTelegram.sensorid) {
    printFmtToWebClient(" #%d", decodedTelegram.sensorid);
  }
}


//Utility Functions
void printParameterInJSON_ToWebClient(parameter param){
  printFmtToWebClient("    { \"parameter\": %g, \"destination\": %d }", param.number, param.dest_addr);
}
