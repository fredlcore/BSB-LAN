/*
* This code will check if a SET command is received for the default destination address from outside of BSB-LAN.
* Use this to monitor changes in a setting where several households share one LPB bus and 
* you want to be notified if a change occurs that may not be originating from your own household.
* This approach may not be 100% reliable as telegrams might be missed by BSB-LAN if the bus is very busy, but it should work in most cases
* and covers changes of all parameters on your controller.
* If you need greater reliability, use the approach in BSB_LAN_custom_global.h and BSB_LAN_custom.h in this folder, but that approach only monitors changes of specific parameters.
* This script works with pushsafer.com, but it should be easy to adapt it to other services by adjusting the variables below.
* There is one hard-coded check below that checks for the result string containing "success" or "error" which might have to 
* be adjusted for the debug messages to work, but it won't do any harm to leave it as it is if debug output is not needed.
*/

{
  if (decodedTelegram.dest_addr == dest_address && decodedTelegram.msg_type == TYPE_SET) {  // If you own more than one device on the bus, you can add additional checks in the first "if" statement.
    const char* pushHost = "www.pushsafer.com";
    const char* pushKey = "YOUR-PUSHSAFER.COM-KEY-HERE";
    const char* pushSubject = "Parameter change";

    const char* pushMethod = "POST";
    const char* pushPath = "/api";
    const char* pushFormatString = "k=%s&t=%s&m=%s";        // first parameter ("k=") = pushKey, second parameter ("t=") = pushSubject, third parameter ("m=") = message body
    uint16_t port = 80;
    Client *pushClient = nullptr;
    char pushMessage[256];

#if !defined(NO_TLS)
    ComClientSecure *httpsclient = new ComClientSecure();
    httpsclient->setCACertBundle(certs_bundle, certs_bundle_len); // replace this with httpsclient->setInsecure(); if you don't care about TLS certificate verification (not recommended for production use) 
    pushClient = httpsclient;
    port = 443;
#else
    ComClient *httpclient = new ComClient();
    pushClient = httpclient;
#endif

    printFmtToDebug("Parameter %g was changed to %s by device id %d.\r\n", decodedTelegram.prognr, decodedTelegram.value, decodedTelegram.src_addr);
    snprintf(pushMessage, sizeof(pushMessage), "%s: %s", decodedTelegram.prognrdescaddr, decodedTelegram.value);
    // Now check if it is an ENUM parameter and add the option text
    if (decodedTelegram.enumdescaddr != nullptr) {
      size_t len = strnlen(decodedTelegram.enumdescaddr, 64);
      if (len > 0 && len < 64 && ((unsigned char)(decodedTelegram.enumdescaddr[0])) > 32) {  // if it is within the description boundaries and starts with readable characters, then we're good...
        snprintf(pushMessage + strlen(pushMessage), sizeof(pushMessage) - strlen(pushMessage), " (%s)", decodedTelegram.enumdescaddr);
      }
    }

    printFmtToDebug("Attempting to connect to %s on port %d...\r\n", pushHost, port);
    if (pushClient->connect(pushHost, port)) {
      char postMessage[300];
      uint16_t pushDataLen = snprintf(postMessage, sizeof(postMessage), pushFormatString, pushKey, pushSubject, pushMessage);
    
      pushClient->print(pushMethod);
      pushClient->print(" ");
      pushClient->print(pushPath);
      pushClient->println(" HTTP/1.1");
      pushClient->print("Host: ");
      pushClient->println(pushHost);
      pushClient->print("Content-Length: ");
      pushClient->println(pushDataLen);
      pushClient->println("Content-Type: application/x-www-form-urlencoded");
      pushClient->println("Connection: close");
      pushClient->println(); // End of headers
      pushClient->print(postMessage);
    
      // Wait for response with a timeout
      unsigned long timeout = millis();
      while (pushClient->available() == 0) {
        if (millis() - timeout > 7000) { // 7-second timeout
          printlnToDebug("Client Response Timeout!");
          pushClient->stop();
          break;
        }
        delay(10);
      }

      // Parse the response:
      char lineBuf[128];  // Adjust size as needed
      int index = 0;
          
      while (pushClient->available()) {
        char c = pushClient->read();
          
        // Accumulate characters until newline or buffer is full
        if (c != '\n' && index < sizeof(lineBuf) - 1) {
          lineBuf[index++] = c;
        } else {
          lineBuf[index] = '\0'; // Null-terminate
          
          // Convert to lowercase in-place (optional, for case-insensitive matching)
          for (int i = 0; i < index; ++i) {
            lineBuf[i] = tolower(lineBuf[i]);
          }
          
          if (strstr(lineBuf, "success") != nullptr) {  // Adjust this check if your push notification service returns a different success indicator
            printlnToDebug("Push status: Success");
            break;
          } else if (strstr(lineBuf, "error") != nullptr) {
            printlnToDebug("Push status: Error");
            printlnToDebug(lineBuf);
            break;
          }
          
          index = 0;  // Reset buffer for next line
        }
      }

      while (pushClient->available()) pushClient->read();
      pushClient->stop();
    } else {
      printFmtToDebug("Connection to %s failed.\r\n", pushHost);
    }
    if (pushClient != nullptr) {
      delete pushClient;
      pushClient = nullptr;
    }
  }
}
