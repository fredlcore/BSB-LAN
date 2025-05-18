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
  uint8_t destAddr = bus->getBusDest();
  uint8_t d_addr = destAddr;
  uint8_t save_my_dev_fam = my_dev_fam;
  uint8_t save_my_dev_var = my_dev_var;
  uint32_t save_my_dev_serial = my_dev_serial;
  printFmtToDebug("IPWE sensors: %d\r\n", numIPWESensors);
  printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_DO_NOT_CACHE);
  printToWebClient("\r\n<html><body><form><table border=1><tbody><tr><td>Sensortyp</td><td>Adresse</td><td>Beschreibung</td><td>Wert</td><td>Luftfeuchtigkeit</td><td>Windgeschwindigkeit</td><td>Regenmenge</td></tr>");

  for (i=0; i < numIPWESensors; i++) {
    if (!ipwe_parameters[i].number) continue;
    if (ipwe_parameters[i].dest_addr > -1){
      if( ipwe_parameters[i].dest_addr != d_addr) {
        d_addr = ipwe_parameters[i].dest_addr;
        set_temp_destination(d_addr);
      }
    } else {
      if (destAddr != d_addr) {
        d_addr = destAddr;
        return_to_default_destination(destAddr);
        my_dev_fam = save_my_dev_fam;
        my_dev_var = save_my_dev_var;
        my_dev_serial = save_my_dev_serial;
      }
    }
    query(ipwe_parameters[i].number);
    counter++;
    printFmtToWebClient("<tr><td>T<br></td><td>%d<br></td><td>", counter);
    printToWebClient_prognrdescaddr();
    printFmtToWebClient("<br></td><td>%s&nbsp;%s<br></td>", decodedTelegram.value, decodedTelegram.unit);
    printToWebClient(STR_IPWEZERO);
    printToWebClient(STR_IPWEZERO);
    printToWebClient(STR_IPWEZERO);
    printToWebClient("</tr>");
  }
  if (destAddr != d_addr) {
    return_to_default_destination(destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
    my_dev_serial = save_my_dev_serial;
  }

  if (LoggingMode & CF_LOGMODE_24AVG) {
    for (int i=0; i<numAverages; i++) {
      if (avg_parameters[i].number > 0) {
        counter++;
        query(BSP_AVERAGES + i);
        printFmtToWebClient("<tr><td>T<br></td><td>%d", counter);
        printToWebClient("<br></td><td>");
        printToWebClient_prognrdescaddr();
        printFmtToWebClient("<br></td><td>%s&nbsp;%s<br></td>", decodedTelegram.value, decodedTelegram.unit);
        printToWebClient(STR_IPWEZERO);
        printToWebClient(STR_IPWEZERO);
        printToWebClient(STR_IPWEZERO);
        printToWebClient("</tr>");
      }
    }
  }

  if (One_Wire_Pin >= 0) {
    // output of one wire sensors
    for (i = 0; i < numSensors * 2; i += 2) {
      printFmtToWebClient("<tr><td>T<br></td><td>%d<br></td><td>", counter);
      query(i + BSP_ONEWIRE);
      printToWebClient(decodedTelegram.value);
      query(i + BSP_ONEWIRE + 1);
      printFmtToWebClient("<br></td><td>%s<br></td>", decodedTelegram.value);
      printToWebClient(STR_IPWEZERO);
      printToWebClient(STR_IPWEZERO);
      printToWebClient(STR_IPWEZERO);
      printToWebClient("</tr>");
    }
  }
  // output of DHT sensors
  int numDHTSensors = sizeof(DHT_Pins) / sizeof(DHT_Pins[0]);
  for (i = 0; i < numDHTSensors; i++) {
    if (DHT_Pins[i] < 0) continue;
    query(BSP_DHT22 + 1 + i * 4);
    counter++;
    printFmtToWebClient("<tr><td>T<br></td><td>%d<br></td><td>", counter);
    printFmtToWebClient("DHT sensor %d temperature", DHT_Pins[i]);
    printFmtToWebClient("<br></td><td>%s<br></td>", decodedTelegram.value);
    printToWebClient(STR_IPWEZERO);
    printToWebClient(STR_IPWEZERO);
    printToWebClient(STR_IPWEZERO);
    printToWebClient("</tr>");
    counter++;
    query(BSP_DHT22 + 2 + i * 4);
    printFmtToWebClient("<tr><td>F<br></td><td>%d<br></td><td>", counter);
    printFmtToWebClient("DHT sensor %d humidity<br></td>", DHT_Pins[i]);
    printToWebClient(STR_IPWEZERO);
    printFmtToWebClient("<td>%s<br></td>", decodedTelegram.value);
    printToWebClient(STR_IPWEZERO);
    printToWebClient(STR_IPWEZERO);
    printToWebClient("</tr>");
  }
  printToWebClient("</tbody></table></form></body></html>\r\n\r\n");
  forcedflushToWebClient();
}
// --- Ipwe() ---
