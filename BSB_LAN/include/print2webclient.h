
/* Functions for management "Ring" output buffer */
/** *****************************************************************
 *  Function: printToWebClient(char *), printToWebClient(const char *), printToWebClient(uint_farptr_t), printFmtToWebClient()
 *  Does: do buffered print to network client. Increasing net perfomance 2~50 times
 *         flushToWebClient() can be called when you want.
 *         forcedflushToWebClient() must be called before end of connection
 *  Pass parameters:
 *  WiFiSpiClient/EthernetClient &cl
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
    //if (bigBuffPos > sizeof(bigBuff)) printlnToDebug(PSTR("bigBuffPos > bigBuff size"));
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
    return;
  }
// for debug purposes
//  if (bigBuffPos < 0)  printlnToDebug(PSTR("bigBuffPos is negative"));
}

void forcedflushToWebClient() {
  if (bigBuffPos > 0) {
    client.write(bigBuff, bigBuffPos);
    bigBuffPos = 0;
  }
  client.flush();
}

int writelnToWebClient() {
  int len = strlen(strcpy(bigBuff + bigBuffPos, PSTR("\r\n")));
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

#define printlnToWebClient(format) (printToWebClient(format) + writelnToWebClient())

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
  if (decodedTelegram.prognr >= 20050 && decodedTelegram.prognr < 20100) {
    printToWebClient(PSTR(STR_24A_TEXT));
    printToWebClient(PSTR(". "));
  }
  printToWebClient(decodedTelegram.prognrdescaddr);
  if (decodedTelegram.sensorid) {
    printFmtToWebClient(PSTR(" #%d"), decodedTelegram.sensorid);
  }
}
