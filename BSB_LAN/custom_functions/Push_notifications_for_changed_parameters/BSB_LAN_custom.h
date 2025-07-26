/* 
 * This code is run at the end of each main loop and utilizes the main loop variables 
 * custom_timer (set each loop to millis()) and custom_timer_compare.
 * This short example prints a "Ping!" message every 60 seconds.
*/

if (custom_timer > custom_timer_compare+60000) {    // every 60 seconds  
  uint16_t port = 80;
  custom_timer_compare = millis();
  Client *pushClient = nullptr;
  bool sendNotification = false; // Flag to determine if a notification needs to be sent
  char pushMessage[256];
  
#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  ComClientSecure *httpsclient = new ComClientSecure();
  httpsclient->setInsecure(); // WARNING: Bypasses SSL certificate validation
  pushClient = httpsclient;
  port = 443;
#else
  ComClient *httpclient = new ComClient();
  pushClient = httpclient;
#endif

  uint8_t destAddr = bus->getBusDest();
  uint8_t d_addr = destAddr;
  uint8_t save_my_dev_fam = my_dev_fam;
  uint8_t save_my_dev_var = my_dev_var;
  uint8_t save_my_dev_oc = my_dev_oc;
  uint32_t save_my_dev_serial = my_dev_serial;

  for (int i=0; i < sizeof(pushParameters) / sizeof(pushParameters[0]); i++) {
    if (pushParameters[i].number > 0) {
      if (pushParameters[i].dest_addr > -1){
        if(pushParameters[i].dest_addr != d_addr) {
          d_addr = pushParameters[i].dest_addr;
          set_temp_destination(pushParameters[i].dest_addr);
        }
      } else {
        if (destAddr != d_addr) {
          d_addr = destAddr;
          return_to_default_destination(destAddr);
          my_dev_fam = save_my_dev_fam;
          my_dev_var = save_my_dev_var;
          my_dev_oc = save_my_dev_oc;
          my_dev_serial = save_my_dev_serial;
        }
      }
      parameter pushParam = pushParameters[i];
      printFmtToDebug("Checking parameter %g!%d...\r\n", pushParam.number, pushParam.dest_addr);
      query(pushParam.number);

      if (decodedTelegram.error == 0) {
        bool valueChanged = strcmp(decodedTelegram.value, previousErrorValue[i]) != 0;
      
        if (valueChanged) {
          printFmtToDebug("Push: Parameter %g!%d (%s) changed from '%s' to '%s'\r\n", pushParam.number, pushParam.dest_addr, decodedTelegram.prognrdescaddr, previousErrorValue[i], decodedTelegram.value);
          snprintf(pushMessage, sizeof(pushMessage), "%s: %s", decodedTelegram.prognrdescaddr, decodedTelegram.value);
          // Now check if it is an ENUM parameter and add the option text
          if (decodedTelegram.enumdescaddr != nullptr) {
            size_t len = strnlen(decodedTelegram.enumdescaddr, 64);
            if (len > 0 && len < 64 && ((unsigned char)(decodedTelegram.enumdescaddr[0])) > 32) {  // if it is within the description boundaries and starts with readable characters, then we're good...
              snprintf(pushMessage + strlen(pushMessage), sizeof(pushMessage) - strlen(pushMessage), " (%s)", decodedTelegram.enumdescaddr);
            }
          }
          sendNotification = true; // Mark that we need to send this
        }
      } else {
        printFmtToDebug("Pushsafer Notify: Failed to query parameter %g!%d. Error: %d\r\n", pushParam.number, pushParam.dest_addr, decodedTelegram.error);
      }
      if (sendNotification == true && !pushFirstRun) {
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
          
              if (strstr(lineBuf, "success") != nullptr) {
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

          strncpy(previousErrorValue[i], decodedTelegram.value, sizeof(previousErrorValue[i]) -1);
          previousErrorValue[i][sizeof(previousErrorValue)-1] = '\0';
        } else {
          printFmtToDebug("Connection to %s failed.\r\n", pushHost);
        }
        sendNotification = false;
      } else {
        // use the first run to populate the previousErrorValue array
        strncpy(previousErrorValue[i], decodedTelegram.value, sizeof(previousErrorValue[i]) -1);
        previousErrorValue[i][sizeof(previousErrorValue)-1] = '\0';
      }
    }
    yield();
  }

  if (destAddr != d_addr) {
    return_to_default_destination(destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
    my_dev_oc = save_my_dev_oc;
    my_dev_serial = save_my_dev_serial;
  }

  if (pushClient != nullptr) {
    delete pushClient;
    pushClient = nullptr;
  }

  if (pushFirstRun == true) pushFirstRun = false;
}
