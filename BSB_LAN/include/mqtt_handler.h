char *build_pvalstr(bool extended);
unsigned long mqtt_reconnect_timer;

//Luposoft: function mqtt_sendtoBroker
/*  Function: mqtt_sendtoBroker()
 *  Does:     send messages to mqtt-broker
 * Pass parameters:
 *  int param
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 *  MQTT instance
 * *************************************************************** */

/* Function: mqtt_get_client_id()
 * Does: Gets the client ID to use for the MQTT connection based on the set
 *   MQTT Device ID, if unset, defaults to "BSB-LAN".
 * Pass parameters:
 *   none
 * Function value returned
 *   MQTT client ID as pointer to char array
 * Global resources used:
 *   none
 */

const char* mqtt_get_client_id() {
  // Build Client ID
  const char* clientIDptr;
  if (MQTTDeviceID[0]) {
    clientIDptr = MQTTDeviceID;
  } else {
    clientIDptr = "BSB-LAN";
  }
  return clientIDptr;
}

void mqtt_sendtoBroker(parameter param) {
  // Declare local variables and start building json if enabled
  char MQTTPayload[2048] = "";
  char MQTTTopic[80] = "";
  StringBuffer sb_payload;
  StringBuffer sb_topic;
  initStringBuffer(&sb_payload, MQTTPayload, sizeof(MQTTPayload));
  initStringBuffer(&sb_topic, MQTTTopic, sizeof(MQTTTopic));
  appendStringBuffer(&sb_topic, "%s/", MQTTTopicPrefix);

  switch(mqtt_mode)
  {
    // =============================================
    // Send data as plain text
    // =============================================
    case 1:
      // use parameter code as sub-topic
      appendStringBuffer(&sb_topic, "%g", param.number);
      if (param.dest_addr > -1) {
        appendStringBuffer(&sb_topic, "!%d", param.dest_addr);
      }
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME  || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
//---- yes, because build_pvalstr(0) sends both the value and the description. If only one is needed (I don't know about MQTT users) then we can use one of the other (FH 2.1.2021)
        appendStringBuffer(&sb_payload, "%s", build_pvalstr(0));
      } else {
        appendStringBuffer(&sb_payload, "%s", decodedTelegram.value);
      }
      break;
    // =============================================
    // send data as json message (parameter / value only)
    // =============================================
    case 2:
      // use sub-topic json
      appendStringBuffer(&sb_topic, "%s", "json");
      // Build the json heading
      appendStringBuffer(&sb_payload, "{\"%s\":{\"status\":{\"%g", mqtt_get_client_id(), param.number);
      if (param.dest_addr > -1) {
        appendStringBuffer(&sb_payload, "!%d", param.dest_addr);
      }
      appendStringBuffer(&sb_payload, "\":\"");
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
//---- yes, because build_pvalstr(0) sends both the value and the description. If only one is needed (I don't know about MQTT users) then we can use one of the other (FH 2.1.2021)
        appendStringBuffer(&sb_payload, "%s", build_pvalstr(0));
      } else {
        appendStringBuffer(&sb_payload, "%s", decodedTelegram.value);
      }
      appendStringBuffer(&sb_payload, "\"}}}");
      break;
    // =============================================
    // send full json message (parameter number, parameter name, value, unit, error)
    // =============================================
    case 3:
      appendStringBuffer(&sb_topic, "%s", "json");
      // Build the json heading
      appendStringBuffer(&sb_payload, "{\"");
      if (MQTTDeviceID[0]) {
        appendStringBuffer(&sb_payload, "%s", MQTTDeviceID);
      } else {
        appendStringBuffer(&sb_payload, "%s", "BSB-LAN");
      }
      appendStringBuffer(&sb_payload, "\":{\"id\":%g", param.number);
      if (param.dest_addr > -1) {
        appendStringBuffer(&sb_payload, "!%d", param.dest_addr);
      }
      appendStringBuffer(&sb_payload, ",\"name\":\"%s\",\"value\": \"%s\",\"desc\": \"", decodedTelegram.prognrdescaddr, decodedTelegram.value);
      if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr) {
        appendStringBuffer(&sb_payload, "%s", decodedTelegram.enumdescaddr);
      }
      appendStringBuffer(&sb_payload, "\",\"unit\": \"%s\",\"error\": %d}}", decodedTelegram.unit, decodedTelegram.error);
      break;
    default:
      printFmtToDebug("Invalid mqtt mode: %d. Must be 1,2 or 3. Skipping publish.",mqtt_mode);
      return;
  }

  // debugging..
  printFmtToDebug("Publishing to topic: %s\r\n", MQTTTopic);
  printFmtToDebug("Payload: %s\r\n", MQTTPayload);
  // Now publish the json payload only once
  if (MQTTPubSubClient->connected()) {
    MQTTPubSubClient->publish(MQTTTopic, MQTTPayload, true);
  } else {
    printlnToDebug("Not connected to MQTT broker.");
  }
  printlnToDebug("Successfully published...");
}

void LogToMQTT (float line) {
  parameter param;
  param.number = line;
  uint8_t current_dest = bus->getBusDest();
  if (current_dest==dest_address || decodedTelegram.msg_type == TYPE_INF) {   // dest_address holds the standard destination address
    param.dest_addr = -1;
  } else {
    param.dest_addr = current_dest;
  }
  if ((LoggingMode & CF_LOGMODE_MQTT) && decodedTelegram.error == 0) {
    mqtt_sendtoBroker(param);
  }
}

/* Function: mqtt_get_will_topic()
 * Does:    Constructs the MQTT Will Topic used throught the system
 * Pass parameters:
 *   none
 * Function value returned
 *   MQTT last will topic as pointer to char array
 * Global resources used:
 *   none
 */

char* mqtt_get_will_topic() {
  // Build (Last) Will Topic
  outBuf[0] = 0;
  strcpy(outBuf, MQTTTopicPrefix);
  strcat(outBuf, "/status");
  return outBuf;
}

//Luposoft: Funktionen mqtt_connect
/*  Function: mqtt_connect()
 *  Does:     connect to mqtt broker

 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  bool
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 *  MQTT instance
 * *************************************************************** */

bool mqtt_connect() {
  char* tempstr = (char*)malloc(sizeof(mqtt_broker_addr));  // make a copy of mqtt_broker_addr for destructive strtok operation
  strcpy(tempstr, mqtt_broker_addr);
  uint16_t mqtt_port = 1883; 
  char* mqtt_host = strtok(tempstr,":");  // hostname is before an optional colon that separates the port
  char* token = strtok(NULL, ":");   // remaining part is the port number
  if (token != 0) {
    mqtt_port = atoi(token);
  }
  free(tempstr);

  bool first_connect = false;
  if(MQTTPubSubClient == NULL) {
    mqtt_client= new ComClient();
    MQTTPubSubClient = new PubSubClient(mqtt_client[0]);
    MQTTPubSubClient->setBufferSize(1024);
    mqtt_reconnect_timer = 0;
    first_connect = true;
  }
  if (!MQTTPubSubClient->connected()) {
    if (!first_connect && !mqtt_reconnect_timer) {
      // We just lost connection, don't try to reconnect immediately
      mqtt_reconnect_timer = millis();
      printlnToDebug("MQTT connection lost");
      return false;
    }
    if (mqtt_reconnect_timer && millis() - mqtt_reconnect_timer < 10000) {
      // Wait 1s between reconnection attempts
      return false;
    }

    char* MQTTUser = NULL;
    if(MQTTUsername[0]) {
      MQTTUser = MQTTUsername;
    }
    const char* MQTTPass = NULL;
    if(MQTTPassword[0]) {
      MQTTPass = MQTTPassword;
    }
    printFmtToDebug("Connecting to MQTT broker %s on port %d...\r\n", mqtt_host, mqtt_port);
    MQTTPubSubClient->setServer(mqtt_host, mqtt_port);
    printFmtToDebug("Client ID: %s\r\n", mqtt_get_client_id());
    printFmtToDebug("Will topic: %s\r\n", mqtt_get_will_topic());
    MQTTPubSubClient->connect(mqtt_get_client_id(), MQTTUser, MQTTPass, mqtt_get_will_topic(), 0, true, "offline");
    if (!MQTTPubSubClient->connected()) {
      printlnToDebug("Failed to connect to MQTT broker, retrying...");
      mqtt_reconnect_timer = millis();
    } else {
      printlnToDebug("Connected to MQTT broker, updating will topic");
      mqtt_reconnect_timer = 0;
      MQTTPubSubClient->subscribe(MQTTTopicPrefix);   //Luposoft: set the topic listen to
      printFmtToDebug("Subscribed to topic '%s'\r\n", MQTTTopicPrefix);
      MQTTPubSubClient->setKeepAlive(120);       //Luposoft: just for savety
      MQTTPubSubClient->setCallback(mqtt_callback);  //Luposoft: set to function is called when incoming message
      MQTTPubSubClient->publish(mqtt_get_will_topic(), "online", true);
      printFmtToDebug("Published status 'online' to topic '%s'\r\n", mqtt_get_will_topic());
      return true;
    }
  } else {
    return true;
  }
  return false;
}

/* Function: mqtt_disconnect()
 * Does:     Will disconnect from the MQTT Broker if connected.
 *           Frees accociated resources
 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *   Serial instance
 *   Ethernet instance
 *   MQTT instance
 */

void mqtt_disconnect() {
  if (MQTTPubSubClient) {
    if (MQTTPubSubClient->connected()) {
      printlnToDebug("Disconnect from MQTT broker, updating will topic");
      printFmtToDebug("Will topic: %s\r\n", mqtt_get_will_topic());
      MQTTPubSubClient->publish(mqtt_get_will_topic(), "offline", true);
      MQTTPubSubClient->disconnect();
    } else {
      printlnToDebug("Dropping unconnected MQTT client");
    }
    delete MQTTPubSubClient;
    MQTTPubSubClient = NULL;
    mqtt_client->stop();
    delete mqtt_client;
  }
}

//Luposoft: Funktionen mqtt_callback
/*  Function: mqtt_callback()
 *  Does:     will call by MQTTPubSubClient.loop() when incomming mqtt-message from broker
 *            Example: set <mqtt2Server> publish <MQTTTopicPrefix> S700=1
              send command to heater and return an acknowledge to broker
 * Pass parameters:
 *  topic,payload,length
 * Parameters passed back:
 *  none
 * Function value returned:
 *  none
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 * *************************************************************** */

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  uint8_t destAddr = bus->getBusDest();
  uint8_t save_my_dev_fam = my_dev_fam;
  uint8_t save_my_dev_var = my_dev_var;
  //boolean setcmd;
  printlnToDebug("##MQTT#############################");
  printToDebug("mqtt-message arrived [");
  printToDebug(topic);
  printlnToDebug("] ");
  char C_value[24];
  strcpy(C_value, "ACK_");   //dukess
  char firstsign;
  firstsign=' ';
  switch ((char)payload[0]) {
    case 'I': {firstsign='I';printToDebug("I");break;}
    case 'S': {firstsign='S';printToDebug("S");break;}
  }
  //buffer overflow protection    //dukess
  if (length > sizeof(C_value) - 5) { // fschaeck: changed from 4 to 5 bytes
    length = sizeof(C_value) - 5;     // fschaeck: 4 for 'ACK_' and one for the terminating nul
    printlnToDebug("payload too big");
  }
  for (unsigned int i=0;i<length;i++) {
    C_value[i+4]=char(payload[i]);
  }
  C_value[length+4]='\0';
  char* C_payload = C_value+4;  //dukess
  if (firstsign != ' ') {
    C_payload++; //skip I/S
  }

  parameter param = parsingStringToParameter(C_payload);

  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    set_temp_destination(param.dest_addr);
  }

  char mqtt_Topic[75];
  strcpy(mqtt_Topic, MQTTTopicPrefix);
  strcat(mqtt_Topic, "/MQTT");
  MQTTPubSubClient->publish(mqtt_Topic, C_value);

  if (firstsign==' ') { //query
    printFmtToDebug("%g \r\n", param.number);
  } else { //command to heater
    C_payload=strchr(C_payload,'=');
    C_payload++;
    printFmtToDebug("%.1f=%s \r\n", param.number, C_payload);
    set(param.number,C_payload,firstsign=='S');  //command to heater
  }
  query(param.number);
//  mqtt_sendtoBroker(param);  //send mqtt-message      <-- no longer necessary, as query() will call mqtt_sendtoBroker itself
  printlnToDebug("##MQTT#############################");
  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
  }

}

void mqtt_send_discovery(boolean create=true) {
//  uint8_t destAddr = bus->getBusDest();
  char MQTTPayload[2048] = "";
  char MQTTTopic[80] = "";
  StringBuffer sb_payload;
  StringBuffer sb_topic;
  int i = 0;
  float line = 0;
  if (bus->getBusType() == BUS_PPS) {
    line = 15000;
  }
  while (line < 21000) {
    if (line == 19999) line++;    // skip entry for unknown parameter
    if (bus->getBusType() != BUS_PPS && line == 15000) line = 16000;
    i=findLine(line);
    if (i>=0) {
      MQTTPayload[0] = '\0';
      MQTTTopic[0] = '\0';
      initStringBuffer(&sb_payload, MQTTPayload, sizeof(MQTTPayload));
      initStringBuffer(&sb_topic, MQTTTopic, sizeof(MQTTTopic));
      loadPrognrElementsFromTable(line, i);
      loadCategoryDescAddr();
      appendStringBuffer(&sb_topic, "%s", "homeassistant/");
      appendStringBuffer(&sb_payload, " \
{ \
  \"name\":\"%02d %s - %g - %s\", \
  \"unique_id\":\"%g-%d-%d\", \
  \"state_topic\":\"%s/%g\",", decodedTelegram.cat, decodedTelegram.catdescaddr, line, decodedTelegram.prognrdescaddr, line, cmdtbl[i].dev_fam, cmdtbl[i].dev_var, MQTTTopicPrefix, line);
      if (decodedTelegram.isswitch) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:toggle-switch\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_DEG) || !strcmp(decodedTelegram.unit, U_TEMP_PER_MIN) || !strcmp(decodedTelegram.unit, U_CEL_MIN)) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:thermometer\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_PERC)) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:percent\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_MONTHS) || !strcmp(decodedTelegram.unit, U_DAYS) || decodedTelegram.type == VT_WEEKDAY || (decodedTelegram.type >= VT_DATETIME && decodedTelegram.type <= VT_TIMEPROG)) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:calendar\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_HOUR) || !strcmp(decodedTelegram.unit, U_MIN) || !strcmp(decodedTelegram.unit, U_SEC) || !strcmp(decodedTelegram.unit, U_MSEC) || decodedTelegram.type == VT_HOUR_MINUTES || decodedTelegram.type == VT_HOUR_MINUTES_N || decodedTelegram.type == VT_PPS_TIME) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:clock\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_RPM)) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:fan\"," NEWLINE);
      } else if (!strcmp(decodedTelegram.unit, U_WATT) || !strcmp(decodedTelegram.unit, U_VOLT) || !strcmp(decodedTelegram.unit, U_KW) || !strcmp(decodedTelegram.unit, U_KWH) || !strcmp(decodedTelegram.unit, U_KWHM3) || !strcmp(decodedTelegram.unit, U_MWH) || !strcmp(decodedTelegram.unit, U_CURR) || !strcmp(decodedTelegram.unit, U_AMP)) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:lightning-bolt\"," NEWLINE);
      } else if (decodedTelegram.type != VT_ENUM && decodedTelegram.type != VT_CUSTOM_ENUM && decodedTelegram.type != VT_CUSTOM_BYTE && decodedTelegram.type != VT_CUSTOM_BIT) {
        appendStringBuffer(&sb_payload, "%s", "\"icon\": \"mdi:numeric\"," NEWLINE);
      }
      if (decodedTelegram.readwrite == FL_RONLY || decodedTelegram.type == VT_CUSTOM_ENUM || decodedTelegram.type == VT_CUSTOM_BYTE || decodedTelegram.type == VT_CUSTOM_BIT) {
        if (decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO) {
          appendStringBuffer(&sb_topic, "%s", "binary_sensor/");
          appendStringBuffer(&sb_payload, "%s", "\"value_template\": \"{{ 'OFF' if value.split(' - ')[0] == '0' else 'ON' }}\"," NEWLINE);
        } else {
          appendStringBuffer(&sb_topic, "%s", "sensor/");
          appendStringBuffer(&sb_payload, "  \"unit_of_measurement\":\"%s\"," NEWLINE, decodedTelegram.unit);
        }
      } else {
        if (decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO) {
          const char* value_on = NULL;
          const char* value_off = NULL;
          if (decodedTelegram.type == VT_ONOFF) {
            value_on = STR_ON;
            value_off = STR_OFF;
          } else {
            value_on = STR_YES;
            value_off = STR_NO;
          }
          appendStringBuffer(&sb_topic, "%s", "switch/");
          appendStringBuffer(&sb_payload, " \
  \"state_on\": \"1 - %s\", \
  \"state_off\": \"0 - %s\", \
  \"command_topic\": \"%s\", \
  \"payload_on\": \"S%g=1\", \
  \"payload_off\": \"S%g=0\",", value_on, value_off, MQTTTopicPrefix, line, line);
        } else if (decodedTelegram.type == VT_ENUM || decodedTelegram.isswitch) {
          appendStringBuffer(&sb_topic, "%s", "select/");
          appendStringBuffer(&sb_payload, " \
  \"command_topic\":\"%s\", \
  \"command_template\": \"S%g={{ value.split(' - ')[0] }}\", \
  \"options\": [", MQTTTopicPrefix, line);

          // We can be more relaxed in parsing the ENUMs here because all the special cases (VT_CUSTOM_ENUM or ENUMs with more than one byte etc.) are already handled above.
          uint16_t val = 0;
          uint16_t c=0;
          uint_farptr_t descAddr;
          while (c + 2 < decodedTelegram.enumstr_len) {
            val=uint16_t(*(decodedTelegram.enumstr+c));
            c = c + 2;
            descAddr = decodedTelegram.enumstr + c;
            appendStringBuffer(&sb_payload, "\"%d - %s\"," NEWLINE, val, descAddr);
            c = c + strlen(descAddr) + 1;
          }
          appendStringBuffer(&sb_payload, "%s", "\"65535 - ---\"]," NEWLINE);
        } else {
          appendStringBuffer(&sb_topic, "%s", "text/");
          appendStringBuffer(&sb_payload, " \
  \"unit_of_measurement\":\"%s\", \
  \"command_topic\":\"%s\", \
  \"command_template\": \"S%g={{value}}\",", decodedTelegram.unit, MQTTTopicPrefix, line);
        }
      }
      appendStringBuffer(&sb_topic, "%g_%d_%d", line, cmdtbl[i].dev_fam, cmdtbl[i].dev_var);
      appendStringBuffer(&sb_topic, "%s", "/config");
 
      appendStringBuffer(&sb_payload, " \
  \"device\": { \
    \"name\":\"%s\", \
    \"identifiers\":\"%s-%02X%02X%02X%02X%02X%02X\", \
    \"manufacturer\":\"bsb-lan.de\", \
    \"model\":\"" MAJOR "." MINOR "." PATCH "\" \
  } \
}", MQTTTopicPrefix, MQTTTopicPrefix, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

      if (!create) {
        MQTTPayload[0] = '\0';      // If remove flag is set, send empty message to instruct auto discovery to remove the entry 
      }
      MQTTPubSubClient->publish(MQTTTopic, MQTTPayload, true);
    }
    line = get_next_prognr(line);
  }
}