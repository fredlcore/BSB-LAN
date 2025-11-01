// --- BSB-LAN Relay Plugin (SENDER) ---

// This block will intercept messages from a specific device and forward them.
{
  // --- Configuration ---
  const char*    RELAY_TARGET_IP          = "remote_bsb_lan.dyndns.org";
  const uint16_t RELAY_TARGET_PORT        = 80;
  const byte     RELAY_SOURCE_DEVICE_ADDR = 0x08;      // The address of the device on THIS (Sender) bus to be relayed.
  const byte     RELAY_TARGET_DEVICE_ADDR = 0x00;      // The address of the device on the REMOTE (Receiver) bus.
  const char*    RELAY_TARGET_PASSKEY     = "1234";
  const char*    RELAY_TARGET_USER        = "username";
  const char*    RELAY_TARGET_PASSWORD    = "password";
  // --- End of Configuration ---
  
  // Check if the message is a broadcast message for the current bus type.
  bool is_broadcast = (bus->getBusType() == BUS_BSB && decodedTelegram.dest_addr == ADDR_ALL) || (bus->getBusType() == BUS_LPB && decodedTelegram.dest_addr >= 0xF0);

  // Only forward messages that are from the remote device AND are addressed to the destination device OR are broadcast messages.
  if (decodedTelegram.src_addr == RELAY_SOURCE_DEVICE_ADDR && (decodedTelegram.dest_addr == RELAY_TARGET_DEVICE_ADDR || is_broadcast)) {
    printFmtToDebug("[RELAY] (%lu) Intercepted message from source device 0x%02X. Forwarding...\r\n", millis(), RELAY_SOURCE_DEVICE_ADDR);

    // 1. Hex-encode the incoming telegram
    char hex_telegram[100] = "";
    int msg_len = msg[bus->getLen_idx()] + bus->getBusType();
    bin2hex(hex_telegram, msg, msg_len, 0);

    // 2. Create the HTTP client and URL
    ComClient relay_client;
    char url[200] = "";
    sprintf(url, "/%s/YR,%s", RELAY_TARGET_PASSKEY, hex_telegram);

//    printFmtToDebug("[RELAY] Connecting to receiver: %s:%d\r\n", RELAY_TARGET_IP, RELAY_TARGET_PORT);
//    printFmtToDebug("[RELAY] Request URL: %s\r\n", url);

    if (relay_client.connect(RELAY_TARGET_IP, RELAY_TARGET_PORT)) {
//      printFmtToDebug("[RELAY] Connected. Sending request.\r\n");
      relay_client.print("GET ");
      relay_client.print(url);
      relay_client.println(" HTTP/1.1");
      relay_client.print("Host: ");
      relay_client.println(RELAY_TARGET_IP);
      relay_client.println("Connection: close");

      // Add HTTP Basic Authentication if username is set
      if (strlen(RELAY_TARGET_USER) > 0) {
        char user_pass[128] = "";
        sprintf(user_pass, "%s:%s", RELAY_TARGET_USER, RELAY_TARGET_PASSWORD);
        
        char base64_user_pass[172] = "";
        Base64.encode(base64_user_pass, user_pass, strlen(user_pass));

        relay_client.print("Authorization: Basic ");
        relay_client.println(base64_user_pass);
//        printFmtToDebug("[RELAY] Sending HTTP Basic Authentication for user '%s'.\r\n", RELAY_TARGET_USER);
      }

      relay_client.println();

      // 3. Wait for and parse the response from the receiver
      unsigned long timeout = millis();
      while (!relay_client.available() && millis() - timeout < 5000) {
        delay(10);
      }

      // Find the start of the response body (after the double CRLF)
      char endOfHeaders[] = "\r\n\r\n";
      if (relay_client.find(endOfHeaders)) {
        char hex_response[100] = "";
        int hex_len = relay_client.readBytesUntil('\r', hex_response, 99);
        hex_response[hex_len] = '\0';

        byte response_telegram[33];
        int response_len = 0;
        for (int i = 0; i < hex_len && i < 66; i += 2) {
          char hex_pair[3] = {hex_response[i], hex_response[i+1], '\0'};
          response_telegram[response_len++] = (byte)strtol(hex_pair, NULL, 16);
        }
        response_telegram[response_len] = '\0'; // Null-terminate the byte array for _send

        if (response_len > 0) {
          printFmtToDebug("[RELAY] (%lu) Received response of %d bytes. Relaying to local bus.\r\n", millis(), response_len);
          uint32_t cmd = 0;
          if ((response_telegram[4+bus->offset] & 0x0F)==TYPE_QUR || (response_telegram[4+bus->offset] & 0x0F)==TYPE_SET || (response_telegram[4+bus->offset] & 0x0F)==TYPE_QRV || (response_telegram[4+bus->offset] & 0x0F)==TYPE_QINF) { //QUERY and SET: First two bytes of CommandID are in reversed order
            cmd=(uint32_t)response_telegram[6+bus->offset]<<24 | (uint32_t)response_telegram[5+bus->offset]<<16 | (uint32_t)response_telegram[7+bus->offset] << 8 | (uint32_t)response_telegram[8+bus->offset];
          } else {
            cmd=(uint32_t)response_telegram[5+bus->offset]<<24 | (uint32_t)response_telegram[6+bus->offset]<<16 | (uint32_t)response_telegram[7+bus->offset] << 8 | (uint32_t)response_telegram[8+bus->offset];
          }
          printTelegram(response_telegram, -1);
          printFmtToDebug("CommandID: %08X, Payload: ", cmd);
          for (int i=0; i < decodedTelegram.payload_length; i++) {
            printFmtToDebug("%02X ", decodedTelegram.payload[i]);
          }
          writelnToDebug();
          // 4. Send the raw response telegram to the local bus using the refactored _send()
          int retries = 3;
          while (bus->_send(response_telegram) != BUS_OK && retries > 0) {
            printFmtToDebug("Retrying...\r\n");
            delay(500);
            retries--;
          }
        }
      }
      relay_client.stop();
    } else {
      printFmtToDebug("[RELAY] Connection to receiver %s failed.\r\n", RELAY_TARGET_IP);
    }
  }
}
