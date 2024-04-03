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

  if (MQTTTopicPrefix[0]) {
    appendStringBuffer(&sb_topic, "%s/", MQTTTopicPrefix);
  } else {
    appendStringBuffer(&sb_topic, "%s", "BSB-LAN/");
  }

  query(param.number);

  switch(mqtt_mode)
  {
    // =============================================
    // Send data as plain text
    // =============================================
    case 1:
      // use parameter code as sub-topic
      appendStringBuffer(&sb_topic, "%s", String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
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
    // send data as json message
    // =============================================
    case 2:
      // use sub-topic json
      appendStringBuffer(&sb_topic, "%s", "json");
      // Build the json heading
      appendStringBuffer(&sb_payload, "{\"%s\":{\"status\":{\"%s", mqtt_get_client_id(), String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
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
    // send full json message
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
      appendStringBuffer(&sb_payload, "\":{\"id\":%s", String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
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
  MQTTPubSubClient->publish(MQTTTopic, MQTTPayload);
  printlnToDebug("Successfully published...");
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
  if (MQTTTopicPrefix[0]) {
    strcpy_P(outBuf, MQTTTopicPrefix);
    strcat(outBuf, "/status");
  } else {
    strcpy_P(outBuf, "BSB-LAN/status");
  }
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
    uint16_t bufsize;
    MQTTPubSubClient = new PubSubClient(mqtt_client[0]);
    switch (mqtt_mode) {
      case 3: bufsize = 1024; break;
      case 2: bufsize = 512; break;
      case 1: bufsize = 128; break;
      default: bufsize = 32; break;
    }
    MQTTPubSubClient->setBufferSize(bufsize);
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
      const char* mqtt_subscr;
      if (MQTTTopicPrefix[0]) {
        mqtt_subscr = MQTTTopicPrefix;
      } else {
        mqtt_subscr="fromBroker";
      }
      MQTTPubSubClient->subscribe(mqtt_subscr);   //Luposoft: set the topic listen to
      printFmtToDebug("Subscribed to topic '%s'\r\n", mqtt_subscr);
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
  strcpy_P(C_value, "ACK_");   //dukess
  char firstsign;
  firstsign=' ';
  switch ((char)payload[0]) {
    case 'I':{firstsign='I';printToDebug("I");break;}
    case 'S':{firstsign='S';printToDebug("S");break;}
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
  char*C_payload=C_value+ 4;  //dukess
  if (firstsign!=' ') {
    C_payload++; //skip I/S
  }

  parameter param = parsingStringToParameter(C_payload);

  if (param.dest_addr > -1) {
    set_temp_destination(param.dest_addr);
  }

  char mqtt_Topic[75];
  if (MQTTTopicPrefix[0]) {
    strcpy_P(mqtt_Topic, MQTTTopicPrefix);
    strcat(outBuf, "/MQTT");
  } else {
    strcpy_P(mqtt_Topic, "BSB-LAN/MQTT");
  }
  MQTTPubSubClient->publish(mqtt_Topic, C_value);

  if (firstsign==' ') { //query
    printFmtToDebug("%.1f \r\n", param.number);
  } else { //command to heater
    C_payload=strchr(C_payload,'=');
    C_payload++;
    printFmtToDebug("%.1f=%s \r\n", param.number, C_payload);
    set(param.number,C_payload,firstsign=='S');  //command to heater
  }
  mqtt_sendtoBroker(param);  //send mqtt-message
  printlnToDebug("##MQTT#############################");
  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
  }

}
