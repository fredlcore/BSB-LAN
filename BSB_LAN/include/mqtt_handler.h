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

void mqtt_sendtoBroker(parameter param) {
  // Declare local variables and start building json if enabled
  String MQTTPayload = "";
  String MQTTTopic = "";

  if (MQTTTopicPrefix[0]) {
    MQTTTopic = MQTTTopicPrefix;
    MQTTTopic.concat(F("/"));
  } else {
    MQTTTopic = "BSB-LAN/";
  }

  query(param.number);

  switch(mqtt_mode)
  {
    // =============================================
    // Send data as plain text
    // =============================================
    case 1:
      // use parameter code as sub-topic
      MQTTTopic.concat(String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
      if (param.dest_addr > -1) {
        MQTTTopic.concat("!");
        MQTTTopic.concat(String(param.dest_addr));
      }
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME  || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
//---- yes, because build_pvalstr(0) sends both the value and the description. If only one is needed (I don't know about MQTT users) then we can use one of the other (FH 2.1.2021)
        MQTTPayload.concat(build_pvalstr(0));
      } else {
        MQTTPayload.concat(decodedTelegram.value);
      }
      break;
    // =============================================
    // send data as json message
    // =============================================
    case 2:
      // use sub-topic json
      MQTTTopic.concat(F("json"));
      // Build the json heading
      MQTTPayload.concat(F("{\""));
      MQTTPayload.concat(mqtt_get_client_id());
      MQTTPayload.concat(F("\":{\"status\":{\""));
      MQTTPayload.concat(String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
      if (param.dest_addr > -1) {
        MQTTPayload.concat("!");
        MQTTPayload.concat(String(param.dest_addr));
      }
      MQTTPayload.concat(F("\":\""));
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME || decodedTelegram.type == VT_WEEKDAY) {
//---- we really need build_pvalstr(0) or we need decodedTelegram.value or decodedTelegram.enumdescaddr ? ----
//---- yes, because build_pvalstr(0) sends both the value and the description. If only one is needed (I don't know about MQTT users) then we can use one of the other (FH 2.1.2021)
        MQTTPayload.concat(build_pvalstr(0));
      } else {
        MQTTPayload.concat(decodedTelegram.value);
      }
      MQTTPayload.concat(F("\"}}}"));
      break;
    // =============================================
    // send full json message
    // =============================================
    case 3:
      MQTTTopic.concat(F("json"));
      // Build the json heading
      MQTTPayload.concat(F("{\""));
      if (MQTTDeviceID[0]) {
        MQTTPayload.concat(MQTTDeviceID);
      } else {
        MQTTPayload.concat(F("BSB-LAN"));
      }
      MQTTPayload.concat(F("\":{\"id\":"));
      MQTTPayload.concat(String(param.number, (roundf(param.number * 10) != roundf(param.number) * 10)?1:0));
      if (param.dest_addr > -1) {
        MQTTPayload.concat("!");
        MQTTPayload.concat(String(param.dest_addr));
      }
      MQTTPayload.concat(F(",\"name\":\""));
      MQTTPayload.concat(decodedTelegram.prognrdescaddr);
      MQTTPayload.concat(F("\",\"value\": \""));
      MQTTPayload.concat(decodedTelegram.value);
      MQTTPayload.concat(F("\",\"desc\": \""));
      if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr) {
        MQTTPayload.concat(decodedTelegram.enumdescaddr);
      }
      MQTTPayload.concat(F("\",\"unit\": \""));
      MQTTPayload.concat(decodedTelegram.unit);
      MQTTPayload.concat(F("\",\"error\": "));
      MQTTPayload.concat(String(decodedTelegram.error));
      MQTTPayload.concat(F("}}"));
      break;
    default:
      printFmtToDebug(PSTR("Invalid mqtt mode: %d. Must be 1,2 or 3. Skipping publish."),mqtt_mode);
      return;
  }

  // debugging..
  printFmtToDebug(PSTR("Publishing to topic: %s\r\n"), MQTTTopic.c_str());
  printFmtToDebug(PSTR("Payload: %s\r\n"), MQTTPayload.c_str());
  // Now publish the json payload only once
  MQTTPubSubClient->publish(MQTTTopic.c_str(), MQTTPayload.c_str());
  printlnToDebug(PSTR("Successfully published..."));
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
  char* token = strtok(NULL, ":");   // first token: myAddr
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
      printlnToDebug(PSTR("MQTT connection lost"));
      return false;
    }
    if (mqtt_reconnect_timer && millis() - mqtt_reconnect_timer < 1000) {
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
    MQTTPubSubClient->setServer(mqtt_host, mqtt_port);
    String MQTTWillTopic = mqtt_get_will_topic();
    String MQTTRealClientId = mqtt_get_client_id();
    printFmtToDebug(PSTR("Client ID: %s\r\n"), MQTTRealClientId.c_str());
    printFmtToDebug(PSTR("Will topic: %s\r\n"), MQTTWillTopic.c_str());
    MQTTPubSubClient->connect(MQTTRealClientId.c_str(), MQTTUser, MQTTPass, MQTTWillTopic.c_str(), 0, true, PSTR("offline"));
    if (!MQTTPubSubClient->connected()) {
      printlnToDebug(PSTR("Failed to connect to MQTT broker, retrying..."));
    } else {
      printlnToDebug(PSTR("Connected to MQTT broker, updating will topic"));
      mqtt_reconnect_timer = 0;
      const char* mqtt_subscr;
      if (MQTTTopicPrefix[0]) {
        mqtt_subscr = MQTTTopicPrefix;
      } else {
        mqtt_subscr="fromBroker";
      }
      MQTTPubSubClient->subscribe(mqtt_subscr);   //Luposoft: set the topic listen to
      printFmtToDebug(PSTR("Subscribed to topic '%s'\r\n"), mqtt_subscr);
      MQTTPubSubClient->setKeepAlive(120);       //Luposoft: just for savety
      MQTTPubSubClient->setCallback(mqtt_callback);  //Luposoft: set to function is called when incoming message
      MQTTPubSubClient->publish(MQTTWillTopic.c_str(), PSTR("online"), true);
      printFmtToDebug(PSTR("Published status 'online' to topic '%s'\r\n"), MQTTWillTopic.c_str());
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
  uint8_t destAddr = bus->getBusDest();
  uint8_t save_my_dev_fam = my_dev_fam;
  uint8_t save_my_dev_var = my_dev_var;
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
  if (length > sizeof(C_value) - 5) { // fschaeck: changed from 4 to 5 bytes
    length = sizeof(C_value) - 5;     // fschaeck: 4 for 'ACK_' and one for the terminating nul
    printlnToDebug(PSTR("payload too big"));
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
    printFmtToDebug(PSTR("%.1f \r\n"), param.number);
  } else { //command to heater
    C_payload=strchr(C_payload,'=');
    C_payload++;
    printFmtToDebug(PSTR("%.1f=%s \r\n"), param.number, C_payload);
    set(param.number,C_payload,firstsign=='S');  //command to heater
  }
  mqtt_sendtoBroker(param);  //send mqtt-message
  printlnToDebug(PSTR("##MQTT#############################"));
  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
  }

}
