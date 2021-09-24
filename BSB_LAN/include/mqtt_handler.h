char *build_pvalstr(bool extended);
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
#ifdef MQTT
void mqtt_sendtoBroker(int param) {
  // Declare local variables and start building json if enabled
  String MQTTPayload = "";
  String MQTTTopic = "";
  if (mqtt_mode == 2 || mqtt_mode == 3) {
    MQTTPayload = "";
    // Build the json heading
    MQTTPayload.concat(F("{\""));
    if (MQTTDeviceID[0]) {
      MQTTPayload.concat(MQTTDeviceID);
    } else {
      MQTTPayload.concat(F("BSB-LAN"));
    }
    if (mqtt_mode == 2)
      MQTTPayload.concat(F("\":{\"status\":{"));
    if (mqtt_mode == 3)
      MQTTPayload.concat(F("\":{\"id\":"));
  }

  boolean is_first = true;
  if (is_first) {
    is_first = false;
  } else {
    MQTTPayload.concat(F(","));
  }
  if (MQTTTopicPrefix[0]) {
    MQTTTopic = MQTTTopicPrefix;
    MQTTTopic.concat(F("/"));
  } else {
    MQTTTopic = "BSB-LAN/";
  }
  // use the sub-topic "json" if json output is enabled
  if (mqtt_mode == 2 || mqtt_mode == 3) {
    MQTTTopic.concat(F("json"));
  } else {
    MQTTTopic.concat(String(param));
  }
  query(param);
  if (mqtt_mode == 3) { // Build the json doc on the fly
    int len = 0;
    outBuf[len] = 0;
    len += sprintf_P(outBuf + len, PSTR("%d,\"name\":\""), param);
    len += strlen(strcpy_PF(outBuf + len, decodedTelegram.prognrdescaddr));
    len += sprintf_P(outBuf + len, PSTR("\",\"value\": \"%s\",\"desc\": \""), decodedTelegram.value);
    if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr) {
      len += strlen(strcpy_PF(outBuf + len, decodedTelegram.enumdescaddr));
    }
    len += sprintf_P(outBuf + len, PSTR("\",\"unit\": \"%s\",\"error\": %d"), decodedTelegram.unit, decodedTelegram.error);
    MQTTPayload.concat(outBuf);
  } else if (mqtt_mode == 2) { // Build the json doc on the fly
    char tbuf[20];
    sprintf_P(tbuf, PSTR("\"%d\":\""), param);
    MQTTPayload.concat(tbuf);
    if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
      MQTTPayload.concat(String(build_pvalstr(0)));
    } else {
      MQTTPayload.concat(String(decodedTelegram.value));
    }
    MQTTPayload.concat(F("\""));
  } else { //plain text
    if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME  || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
      MQTTPubSubClient->publish(MQTTTopic.c_str(), build_pvalstr(0));
    } else {
      MQTTPubSubClient->publish(MQTTTopic.c_str(), decodedTelegram.value);
    }
  }
  // End of mqtt if loop so close off the json and publish
  if (mqtt_mode == 2 || mqtt_mode == 3) {
    // Close the json doc off
    if (mqtt_mode == 2) {
      MQTTPayload.concat(F("}}}"));
    } else {
      MQTTPayload.concat(F("}}"));
    }
    // debugging..
    printToDebug(PSTR("Output topic: "));
    printToDebug(MQTTTopic.c_str());
    printToDebug(PSTR("\r\nPayload Output : "));
    printToDebug(MQTTPayload.c_str());
    writelnToDebug();
    // Now publish the json payload only once
    MQTTPubSubClient->publish(MQTTTopic.c_str(), MQTTPayload.c_str());
  }
}

/* Function: mqtt_get_client_id()
 * Does: Gets the client ID to use for the MQTT connection based on the set
 *   MQTT Device ID, if unset, defaults to "BSB-LAN".
 * Pass parameters:
 *   none
 * Function value returned
 *   MQTT client ID as C++ String instance
 * Global resources used:
 *   none
 */

const String mqtt_get_client_id() {
  // Build Client ID
  String result = "";
  if (MQTTDeviceID[0]) {
    result.concat(MQTTDeviceID);
  } else {
    result.concat(PSTR("BSB-LAN"));
  }
  return result;
}

/* Function: mqtt_get_will_topic()
 * Does:    Constructs the MQTT Will Topic used throught the system
 * Pass parameters:
 *   none
 * Function value returned
 *   MQTT last will topic as C++ String instance
 * Global resources used:
 *   none
 */

const String mqtt_get_will_topic() {
  // Build (Last) Will Topic
  String MQTTLWTopic = "";
  if (MQTTTopicPrefix[0]) {
    MQTTLWTopic = MQTTTopicPrefix;
    MQTTLWTopic.concat(F("/status"));
  } else {
    MQTTLWTopic = F("BSB-LAN/status");
  }
  return MQTTLWTopic;
}

//Luposoft: Funktionen mqtt_connect
/*  Function: mqtt_connect()
 *  Does:     connect to mqtt broker

 * Pass parameters:
 *  none
 * Parameters passed back:
 *  none
 * Function value returned:
 *  boolean
 * Global resources used:
 *  Serial instance
 *  Ethernet instance
 *  MQTT instance
 * *************************************************************** */

boolean mqtt_connect() {
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
  }
  if (!MQTTPubSubClient->connected()) {
    char* MQTTUser = NULL;
    if(MQTTUsername[0])
      MQTTUser = MQTTUsername;
    const char* MQTTPass = NULL;
    if(MQTTPassword[0])
      MQTTPass = MQTTPassword;
    IPAddress MQTTBroker(mqtt_broker_ip_addr[0], mqtt_broker_ip_addr[1], mqtt_broker_ip_addr[2], mqtt_broker_ip_addr[3]);
    MQTTPubSubClient->setServer(MQTTBroker, 1883);
    String MQTTWillTopic = mqtt_get_will_topic();
    String MQTTRealClientId = mqtt_get_client_id();
    int retries = 0;
    printFmtToDebug(PSTR("Client ID: %s\r\n"), MQTTRealClientId.c_str());
    printFmtToDebug(PSTR("Will topic: %s\r\n"), MQTTWillTopic.c_str());
    while (!MQTTPubSubClient->connected() && retries < 3) {
      MQTTPubSubClient->connect(MQTTRealClientId.c_str(), MQTTUser, MQTTPass, MQTTWillTopic.c_str(), 0, true, PSTR("offline"));
      retries++;
      if (!MQTTPubSubClient->connected()) {
        delay(1000);
        printlnToDebug(PSTR("Failed to connect to MQTT broker, retrying..."));
      } else {
        printlnToDebug(PSTR("Connect to MQTT broker, updating will topic"));
        const char* mqtt_subscr;
        if (MQTTTopicPrefix[0]) {mqtt_subscr = MQTTTopicPrefix;} else {mqtt_subscr="fromBroker";}
        MQTTPubSubClient->subscribe(mqtt_subscr);   //Luposoft: set the topic listen to
        MQTTPubSubClient->setKeepAlive(120);       //Luposoft: just for savety
        MQTTPubSubClient->setCallback(mqtt_callback);  //Luposoft: set to function is called when incoming message
        MQTTPubSubClient->publish(MQTTWillTopic.c_str(), PSTR("online"), true);
        return true;
      }
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
      String MQTTWillTopic = mqtt_get_will_topic();
      printlnToDebug(PSTR("Disconnect from MQTT broker, updating will topic"));
      printFmtToDebug(PSTR("Will topic: %s\r\n"), MQTTWillTopic.c_str());
      MQTTPubSubClient->publish(MQTTWillTopic.c_str(), PSTR("offline"), true);
      MQTTPubSubClient->disconnect();
    } else {
      printlnToDebug(PSTR("Dropping unconnected MQTT client"));
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
  //boolean setcmd;
  printlnToDebug(PSTR("##MQTT#############################"));
  printToDebug(PSTR("mqtt-message arrived ["));
  printToDebug(topic);
  printlnToDebug(PSTR("] "));
  char C_value[24];
  strcpy_P(C_value, PSTR("ACK_"));   //dukess
  char firstsign;
  firstsign=' ';
  switch ((char)payload[0]) {
    case 'I':{firstsign='I';printToDebug(PSTR("I"));break;}
    case 'S':{firstsign='S';printToDebug(PSTR("S"));break;}
  }
  //buffer overflow protection    //dukess
  if (length > sizeof(C_value) - 4) {
    length = sizeof(C_value) - 4;
    printlnToDebug(PSTR("payload too big"));
  }
  for (unsigned int i=0;i<length;i++) {
    C_value[i+4]=char(payload[i]);
  }
  C_value[length+4]='\0';
  char*C_payload=C_value+ 4;  //dukess
  if (firstsign!=' ') C_payload++; //skip I/S
  int I_line=atoi(C_payload);
  String mqtt_Topic;
  if (MQTTTopicPrefix[0]) {
    mqtt_Topic = MQTTTopicPrefix;
    mqtt_Topic.concat(F("/"));
  } else {
    mqtt_Topic = "BSB-LAN/";
  }
  mqtt_Topic.concat(F("MQTT"));
  MQTTPubSubClient->publish(mqtt_Topic.c_str(), C_value);

  if (firstsign==' ') { //query
    printFmtToDebug(PSTR("%d \r\n"), I_line);
  } else { //command to heater
    C_payload=strchr(C_payload,'=');
    C_payload++;
    printFmtToDebug(PSTR("%d=%s \r\n"), I_line, C_payload);
    set(I_line,C_payload,firstsign=='S');  //command to heater
  }
  mqtt_sendtoBroker(I_line);  //send mqtt-message
  printlnToDebug(PSTR("##MQTT#############################"));
}
#endif
