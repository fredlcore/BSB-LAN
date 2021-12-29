
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
   printHTTPheader(HTTP_OK, MIME_TYPE_TEXT_HTML, HTTP_ADD_CHARSET_TO_HEADER, HTTP_FILE_NOT_GZIPPED, HTTP_DO_NOT_CACHE);
 #if defined(__AVR__)
   printPStr(pgm_get_far_address(header_html), sizeof(header_html));
   #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printPStr(pgm_get_far_address(header_html2), sizeof(header_html2));
   #endif
   printPStr(pgm_get_far_address(header_html3), sizeof(header_html3));
 #else
   printPStr(header_html, sizeof(header_html));
   #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printPStr(header_html2, sizeof(header_html2));
   #endif
   printPStr(header_html3, sizeof(header_html3));
 #endif
 #if !defined(I_DO_NOT_NEED_NATIVE_WEB_INTERFACE)
   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("' ID=main_link class='logo'>"));
   printPStr(svg_favicon, sizeof(svg_favicon));
//   printToWebClient(PSTR("<img width=10% height=10% src='/favicon.svg'></A>\r\n"));
   printToWebClient(PSTR("</A></center>\r\n"));
   printToWebClient(PSTR("<table align=center><tr bgcolor=#f0f0f0>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("K'>" MENU_TEXT_HFK));

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));
   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("K66'>"));
   printToWebClient(STR_TEXT_SNS);

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   if (!logCurrentValues) {
     printToWebClient(PSTR("<font color=#000000>" MENU_TEXT_DLG "</font></td>"));
   } else {
     printToWebClient(PSTR("<a href='/"));
     printPassKey();
     printToWebClient(PSTR("DG'>" MENU_TEXT_SLG));
     printToWebClient(PSTR("</a></td>"));
   }

   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("Q' TARGET='_new'>" MENU_TEXT_CHK));
   printToWebClient(PSTR("</a></td>"));

   printToWebClient(PSTR("</tr>\r\n<tr bgcolor=#f0f0f0>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='/"));
   printPassKey();
   printToWebClient(PSTR("C'>" MENU_TEXT_CFG));

   //  client.print(F("</a></td><td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan/blob/master/command_ref/command_ref_" str(LANG) ".md'>" MENU_TEXT_URL));
   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_URL "' target='_new'>" MENU_TEXT_URL));

   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_TOC "' target='new'>" MENU_TEXT_TOC));
   printToWebClient(PSTR("</a></td>"));
   printToWebClient(PSTR("<td class=\"header\" width=20% align=center>"));

   printToWebClient(PSTR("<a href='"));
   printToWebClient(PSTR(MENU_LINK_FAQ "' target='_new'>" MENU_TEXT_FAQ));
   printToWebClient(PSTR("</a></td>"));

 //  client.println(F("<td width=20% align=center><a href='http://github.com/fredlcore/bsb_lan' target='new'>GitHub Repo</a></td>"));
   printToWebClient(PSTR("</tr></table>"));
#endif
   printToWebClient(PSTR("<p></p><table align=center><tr><td class=\"header\">\r\n"));
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
  printToWebClient(PSTR("</td></tr></table>\r\n</body>\r\n</html>\r\n\r\n"));
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

  printlnToWebClient(PSTR("<p>"));
  printToWebClient(PSTR("BSB-LAN, Version "));
  printToWebClient(BSB_VERSION);
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_HFK ":</b> " MENU_DESC_HFK ));
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_CFG ":</b> " MENU_DESC_CFG ));
  printlnToWebClient(PSTR("<p><b>" MENU_TEXT_URL ":</b> " MENU_DESC_URL ));

#if !defined(__AVR__)
#ifdef VERSION_CHECK
  if (enable_version_check) {
    printlnToWebClient(PSTR("<BR><BR>" MENU_TEXT_NVS "...<BR>"));
    flushToWebClient();
    httpclient.connect("bsb-lan.de", 80);
    httpclient.println("GET /bsb-version.h\r\n");

    unsigned long timeout = millis();
    while (millis() - timeout < 3000 && !httpclient.available()) {
    }

    int major = -1;
    int minor = -1;
    int patch = -1;
    char version_number[15] = { 0 };
    while (httpclient.available()) {
      char c = httpclient.read();
      if (c == '\"') {
        int index = 0;
        do {
          c = httpclient.read();
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
    httpclient.stop();
    if ((major > atoi(MAJOR)) || (major == atoi(MAJOR) && minor > atoi(MINOR)) || (major == atoi(MAJOR) && minor == atoi(MINOR) && patch > atoi(PATCH))) {
      printToWebClient(PSTR(MENU_TEXT_NVA ": "));
      printFmtToWebClient(PSTR("<A HREF=\"https://github.com/fredlcore/BSB-LAN/archive/master.zip\">%d.%d.%d</A><BR>\r\n"), major, minor, patch);
    } else {
      printlnToWebClient(PSTR(MENU_TEXT_NVN));
    }
  }
#endif
#endif

  webPrintFooter();
} // --- webPrintSite() ---
