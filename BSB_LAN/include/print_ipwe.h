#ifdef IPWE

/*************************** IPWE Extension **************************************/
/** *****************************************************************
 *  Function:  Ipwe()
 *  Does:      Sets up HTML code to display a table with sensor readings.
 *             Queries several controller parameters addressed by their
 *             line (ProgNr) and the LED0 output pin.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *    numSensors
 *    client object
 *    led0   output pin 3
 * *************************************************************** */
 void Ipwe() {
   int i;
   int counter = 0;
   int numIPWESensors = sizeof(ipwe_parameters) / sizeof(ipwe_parameters[0]);
   printFmtToDebug(PSTR("IPWE sensors: %d\r\n"), numIPWESensors);
   printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_DO_NOT_CACHE);
   printToWebClient(PSTR("\r\n<html><body><form><table border=1><tbody><tr><td>Sensortyp</td><td>Adresse</td><td>Beschreibung</td><td>Wert</td><td>Luftfeuchtigkeit</td><td>Windgeschwindigkeit</td><td>Regenmenge</td></tr>"));
   for (i=0; i < numIPWESensors; i++) {
     if (!ipwe_parameters[i]) continue;
     query(ipwe_parameters[i]);
     counter++;
     printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
     printToWebClient_prognrdescaddr();
     printFmtToWebClient(PSTR("<br></td><td>%s&nbsp;%s<br></td>"), decodedTelegram.value, decodedTelegram.unit);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
   }

 #ifdef AVERAGES
   if (LoggingMode & CF_LOGMODE_24AVG) {
     for (int i=0; i<numAverages; i++) {
       if (avg_parameters[i] > 0) {
         counter++;
         query(20050 + i);
         printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d"), counter);
         printToWebClient(PSTR("<br></td><td>"));
         printToWebClient_prognrdescaddr();
         printFmtToWebClient(PSTR("<br></td><td>%s&nbsp;%s<br></td>"), decodedTelegram.value, decodedTelegram.unit);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(STR_IPWEZERO);
         printToWebClient(PSTR("</tr>"));
       }
     }
   }
 #endif

 #ifdef ONE_WIRE_BUS
   if (One_Wire_Pin) {
     // output of one wire sensors
     for (i=0;i<numSensors * 2;i += 2) {
       printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
       query(i + 20300);
       printToWebClient(decodedTelegram.value);
       query(i + 20301);
       printFmtToWebClient(PSTR("<br></td><td>%s<br></td>"), decodedTelegram.value);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(STR_IPWEZERO);
       printToWebClient(PSTR("</tr>"));
     }
   }
 #endif

 #ifdef DHT_BUS
   // output of DHT sensors
   int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
   for (i=0;i<numDHTSensors;i++) {
     if (!DHT_Pins[i]) continue;
     query(20101 + i * 4);
     counter++;
     printFmtToWebClient(PSTR("<tr><td>T<br></td><td>%d<br></td><td>"), counter);
     printFmtToWebClient(PSTR("DHT sensor %d temperature"), DHT_Pins[i]);
     printFmtToWebClient(PSTR("<br></td><td>%s<br></td>"), decodedTelegram.value);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
     counter++;
     query(20102 + i * 4);
     printFmtToWebClient(PSTR("<tr><td>F<br></td><td>%d<br></td><td>"), counter);
     printFmtToWebClient(PSTR("DHT sensor %d humidity<br></td>"), DHT_Pins[i]);
     printToWebClient(STR_IPWEZERO);
     printFmtToWebClient(PSTR("<td>%s<br></td>"), decodedTelegram.value);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(STR_IPWEZERO);
     printToWebClient(PSTR("</tr>"));
   }
 #endif

   printToWebClient(PSTR("</tbody></table></form></body></html>\r\n\r\n"));
   forcedflushToWebClient();
 }

 #endif    // --- Ipwe() ---
