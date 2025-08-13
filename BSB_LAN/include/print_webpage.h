
/** *****************************************************************
 *  Function:  webPrintHeader()
 *  Does:      Sets up the HTML code to start a web page
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintHeader(void) {
  flushToWebClient();
  printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_NO_DOWNLOAD, HTTP_DO_NOT_CACHE);
  printPStr(header_html, sizeof(header_html));
  printPStr(header_html2, sizeof(header_html2));
  printPStr(header_html3, sizeof(header_html3));
  printToWebClient("<a href='/");
  printPassKey();
  printToWebClient("' ID=main_link class='logo'>");
  printPStr(svg_favicon, sizeof(svg_favicon));
//  printToWebClient("<img width=10% height=10% src='/favicon.svg'></A>\r\n");
  printToWebClient("</A></center>\r\n");
  printToWebClient("<table align=center><tr bgcolor=#f0f0f0>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='/");
  printPassKey();
  printToWebClient("K'>" MENU_TEXT_HFK);

  printToWebClient("</a></td>");
  printToWebClient("<td class=\"header\" width=20% align=center>");
  printToWebClient("<a href='/");
  printPassKey();
  printFmtToWebClient("K%d'>", CAT_USERSENSORS);
  printToWebClient(STR_TEXT_SNS);

  printToWebClient("</a></td>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  if (!(LoggingMode & CF_LOGMODE_SD_CARD)) {
    printToWebClient("<font color=#000000>" MENU_TEXT_DLG "</font></td>");
  } else {
    printToWebClient("<a href='/");
    printPassKey();
    printToWebClient("DG'>" MENU_TEXT_SLG);
    printToWebClient("</a></td>");
  }

  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='/");
  printPassKey();
  printToWebClient("Q' TARGET='_new'>" MENU_TEXT_CHK);
  printToWebClient("</a></td>");

  printToWebClient("</tr>\r\n<tr bgcolor=#f0f0f0>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='/");
  printPassKey();
  printToWebClient("C'>" MENU_TEXT_CFG);

  //  client.print("</a></td><td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan/blob/master/command_ref/command_ref_" str(LANG) ".md'>" MENU_TEXT_URL);
  printToWebClient("</a></td>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='");
  printToWebClient(MENU_LINK_URL "' target='_new'>" MENU_TEXT_URL);

  printToWebClient("</a></td>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='");
  printToWebClient(MENU_LINK_TOC "' target='new'>" MENU_TEXT_TOC);
  printToWebClient("</a></td>");
  printToWebClient("<td class=\"header\" width=20% align=center>");

  printToWebClient("<a href='");
  printToWebClient(MENU_LINK_FAQ "' target='_new'>" MENU_TEXT_FAQ);
  printToWebClient("</a></td>");

//  client.println("<td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan' target='new'>GitHub Repo</a></td>");
  printToWebClient("</tr></table>");
  printToWebClient("<p></p><table align=center><tr><td class=\"header\">\r\n");
  flushToWebClient();
} // --- webPrintHeader() ---


/** *****************************************************************
 *  Function:  webPrintFooter()
 *  Does:      Sets up the closing HTML code of a web page.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintFooter(void) {
  printToWebClient("</td></tr></table>\r\n</body>\r\n</html>\r\n\r\n");
  flushToWebClient();
} // --- webPrintFooter() ---

/** *****************************************************************
 *  Function:  webPrintSite()
 *  Does:      Sets up HTML code to display a help page.
 *  Pass parameters:
 *   none
 *  Parameters passed back:
 *   none
 *  Function value returned:
 *   none
 *  Global resources used:
 *   client object
 * *************************************************************** */
void webPrintSite() {
  webPrintHeader();

  printlnToWebClient("<p>");
  printToWebClient("BSB-LAN, Version ");
  printToWebClient(BSB_VERSION);
  if (enable_ota_update) {
    printToWebClient(" / <a id=\"ota_link\" target=\"_new\">OTA</a>");
    printToWebClient("<script>");
    printToWebClient("var port = 8080; var path = '/';");
    printToWebClient("var proto = (location.protocol === 'https' ? 'https' : 'http');");
    printToWebClient("document.getElementById('ota_link').href = proto + '://' + location.hostname + ':' + port + path;");
    printToWebClient("</script>");
  }
#if defined(DEFAULT_DEFS)
  if (bus_type < 2) {
    printlnToWebClient("<p><br><b>" MENU_TEXT_SDF "</b><br><br>");
  }
#endif
  printlnToWebClient("<p><b>" MENU_TEXT_HFK ":</b> " MENU_DESC_HFK );
  printlnToWebClient("<p><b>" MENU_TEXT_CFG ":</b> " MENU_DESC_CFG );
  printlnToWebClient("<p><b>" MENU_TEXT_URL ":</b> " MENU_DESC_URL );

  if (enable_version_check) {
    printlnToWebClient("<BR><BR>" MENU_TEXT_NVS "...<BR>");
    flushToWebClient();
    ComClient *httpclient = new ComClient();
    httpclient->connect("bsb-lan.de", 80);
    httpclient->println("GET /bsb-version.h\r\n");

    unsigned long timeout = millis();
    while (millis() - timeout < 3000 && !httpclient->available()) {
      delay(10);
    }

    int major = -1;
    int minor = -1;
    int patch = -1;
    char version_number[15] = { 0 };
    while (httpclient->available()) {
      char c = httpclient->read();
      if (c == '\"') {
        int index = 0;
        do {
          c = httpclient->read();
          if (index >= 14) continue;  // don't write beyond version_number[]!
          version_number[index] = c;
          index++;
        } while (c != '\"');
        if (index > 1) {
          version_number[index-1] = '\0';
          if (major < 0) {
            major = atoi(version_number);
          } else if (minor < 0) {
            minor = atoi(version_number);
          } else if (patch < 0) {
            patch = atoi(version_number);
          }
        }
      }
    }
    httpclient->stop();
    delete httpclient;
    httpclient = nullptr;
    if ((major > atoi(MAJOR)) || (major == atoi(MAJOR) && minor > atoi(MINOR)) || (major == atoi(MAJOR) && minor == atoi(MINOR) && patch > atoi(PATCH))) {
      printToWebClient(MENU_TEXT_NVA ": ");
      printFmtToWebClient("<A HREF=\"https://github.com/fredlcore/BSB-LAN/archive/master.zip\">%d.%d.%d</A><BR>\r\n", major, minor, patch);
      if (major > atoi(MAJOR) || minor > atoi(MINOR)) {
        printToWebClient(MENU_TEXT_NVW "<BR>\r\n");
      }
    } else {
      printlnToWebClient(MENU_TEXT_NVN);
    }
  }

  webPrintFooter();
} // --- webPrintSite() ---
