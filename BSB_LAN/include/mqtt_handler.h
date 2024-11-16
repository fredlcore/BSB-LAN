char *build_pvalstr(bool extended);
unsigned long mqtt_reconnect_timer;

#define MQTT_SENSOR 1
#define MQTT_BINARY_SENSOR 2
#define MQTT_SWITCH 4
#define MQTT_SELECT 8
#define MQTT_TEXT 16

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
  appendStringBuffer(&sb_topic, "%s/%d/%d/%g/status", MQTTTopicPrefix, (param.dest_addr==-1?bus->getBusDest():param.dest_addr), decodedTelegram.cat, param.number);

  switch(mqtt_mode)
  {
    // =============================================
    // Send data as plain text
    // "76.5"
    // "1 - Automatic"
    // =============================================
    case 1:
      // Send clear text option for VT_ENUM-type parameters, otherwise value only
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME  || decodedTelegram.type == VT_WEEKDAY) {
        appendStringBuffer(&sb_payload, build_pvalstr(0));
      } else {
        appendStringBuffer(&sb_payload, decodedTelegram.value);
      }
      break;
    // =============================================
    // send data as json message (parameter / value only)
    // {
    //   "BSB-LAN": {
    //     "status": {
    //       "10044!0":"77.9"
    //     }
    //   }
    // }
    // =============================================
    case 2:
      // Build the json structure
      appendStringBuffer(&sb_payload, "{\"%s\":{\"status\":{\"%g!%d\":\"", mqtt_get_client_id(), param.number, (param.dest_addr==-1?bus->getBusDest():param.dest_addr));
      // Send clear text option for VT_ENUM-type parameters, otherwise value only
      if (decodedTelegram.type == VT_ENUM || decodedTelegram.type == VT_BINARY_ENUM || decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO || decodedTelegram.type == VT_BIT || decodedTelegram.type == VT_ERRORCODE || decodedTelegram.type == VT_DATETIME || decodedTelegram.type == VT_DAYMONTH || decodedTelegram.type == VT_TIME || decodedTelegram.type == VT_WEEKDAY) {
        appendStringBuffer(&sb_payload, build_pvalstr(0));
      } else {
        appendStringBuffer(&sb_payload, decodedTelegram.value);
      }
      appendStringBuffer(&sb_payload, "\"}}}");
      break;
    // =============================================
    // send full json message (parameter number, parameter name, value, unit, error)
    // {
    //   "BSB-LAN": {
    //     "device": 0,
    //     "parameter": 10044,
    //     "name": "Prozess-Sig Schienenvorlauf",
    //     "value": "74.2",
    //     "desc": "",
    //     "unit": "°C",
    //     "error": 0
    //   }
    // }
    // =============================================
    case 3:
      // Build the json heading
      appendStringBuffer(&sb_payload, "{\"%s\":{\"device\":%d,\"parameter\":%g,\"name\":\"%s\",\"value\":\"%s\",\"desc\":\"", (MQTTDeviceID[0]?MQTTDeviceID:"BSB-LAN"), (param.dest_addr==-1?bus->getBusDest():param.dest_addr), param.number, decodedTelegram.prognrdescaddr, decodedTelegram.value);
      if (decodedTelegram.data_type == DT_ENUM && decodedTelegram.enumdescaddr) {
        appendStringBuffer(&sb_payload, decodedTelegram.enumdescaddr);
      }
      appendStringBuffer(&sb_payload, "\",\"unit\":\"%s\",\"error\":%d}}", decodedTelegram.unit, decodedTelegram.error);
      break;
    default:
      printFmtToDebug("Invalid mqtt mode: %d. Must be 1,2 or 3. Skipping publish.",mqtt_mode);
      return;
  }

  // debugging..
  printFmtToDebug("Publishing to topic: %s\r\n", MQTTTopic);
  // Now publish the json payload only once
  if (MQTTPubSubClient != NULL) {
    if (MQTTPubSubClient->connected()) {
      printFmtToDebug("Payload: %s\r\n", MQTTPayload);
      MQTTPubSubClient->publish(MQTTTopic, MQTTPayload, true);
      printlnToDebug("Successfully published...");
    } else {
      printlnToDebug("Not connected to MQTT broker.");
    }
  } else {
    printlnToDebug("MQTT broker could not be reached, aborting...")
  }
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
    MQTTPubSubClient->setBufferSize(2048);
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
    MQTTPubSubClient->connect(mqtt_get_client_id(), MQTTUser, MQTTPass, mqtt_get_will_topic(), 1, true, "offline");
    if (!MQTTPubSubClient->connected()) {
      printlnToDebug("Failed to connect to MQTT broker, retrying...");
      mqtt_reconnect_timer = millis();
    } else {
      printlnToDebug("Connected to MQTT broker, updating will topic");
      mqtt_reconnect_timer = 0;
      char tempTopic[67];
      strcpy(tempTopic, MQTTTopicPrefix);
      strcat(tempTopic, "/#");
      MQTTPubSubClient->subscribe(tempTopic, 1);   //Luposoft: set the topic listen to
      printFmtToDebug("Subscribed to topic '%s'\r\n", tempTopic);
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

void mqtt_callback(char* topic, byte* passed_payload, unsigned int length) {
  uint8_t destAddr = bus->getBusDest();
  uint8_t save_my_dev_fam = my_dev_fam;
  uint8_t save_my_dev_var = my_dev_var;
  uint32_t save_my_dev_id = my_dev_id;
  uint8_t setmode = 0;  // 0 = send INF, 1 = send SET, 2 = query
  int topic_len = strlen(MQTTTopicPrefix);
  parameter param;
  char parsed_command[10];
  int parsed_device, parsed_category = 0;
  float parsed_parameter = 0;
  char* payload = (char*)passed_payload;
  payload[length] = '\0';

  // New get/set hierarchy topic: BSB-LAN/<device id>/<category>/<parameter>/set|inf|poll
  // Optional payload will be used for set command
  if (sscanf(topic+topic_len, "/%d/%d/%g/%s", &parsed_device, &parsed_category, &parsed_parameter, parsed_command) == 4) {
    param.dest_addr = parsed_device;
    param.number = parsed_parameter;
    if (!strcmp(parsed_command, "poll")) {
      setmode = 2;  // QUR
    } else if (!strcmp(parsed_command, "set")) {
      setmode = 1;  // SET
    } else if (!strcmp(parsed_command, "inf")) {
      setmode = 0;  // INF
    } else if (!strcmp(parsed_command, "status")) {
      return;   // silently discard status topic to avoid recursively replying to ourself.
    } else {
      printFmtToDebug("Unknown command at the end of MQTT topic: %s\r\n", parsed_command);
      return;
    }
  // Publish comma-separated parameters to /poll underneath main topic to update a number of parameters at once
  } else if (sscanf(topic+topic_len, "/%s", parsed_command) == 1) {
    if (!strcmp(parsed_command, "poll")) {
      printFmtToDebug("MQTT message received [%s | %s]\r\n", topic, payload);
      char* token;
      char* payload_copy = (char*)malloc(strlen(payload) + 1);
      strcpy(payload_copy, payload);
      token = strtok(payload_copy, ",");   // parameters to be updated are separated by a comma, parameters either in topic structure or parameter!device notation
      while (token != NULL) {
        while (token[0] == ' ') token++;
        if (token[0] == '/') {
          if (sscanf(token, "/%" PRId16 "/%*d/%g",&param.dest_addr, &param.number) != 2) {
            printFmtToDebug("Invalid topic structure, discarding...\r\n");
            break;
          }
        } else {
          param = parsingStringToParameter(token);
        }
        if (param.dest_addr > -1 && destAddr != param.dest_addr) {
          set_temp_destination(param.dest_addr);
        }
        printFmtToDebug("%g!%d \r\n", param.number, param.dest_addr);
        query(param.number);
      
        if (param.dest_addr > -1 && destAddr != param.dest_addr) {
          bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
          my_dev_fam = save_my_dev_fam;
          my_dev_var = save_my_dev_var;
          my_dev_id = save_my_dev_id;
        }
        token = strtok(NULL, ",");   // next parameter
      }
      free(payload_copy);
      return;
    } else if (!strcmp(parsed_command, "status")) {
      // status is handled by the will topic, so exit quietly here...
      return;
    } else {
      printFmtToDebug("Unknown command at the end of main MQTT topic: %s\r\n", parsed_command);
      return;
    }
  // Legacy MQTT payload: Publish URL-style command to topic BSB-LAN (MQTTTopicPrefix)
  } else if (!strcmp(topic, MQTTTopicPrefix)) {
    switch (payload[0]) {
      case 'I': {setmode = 0;payload++;break;}
      case 'S': {setmode = 1;payload++;break;}
      default: {setmode = 2;break;}
    }
    param = parsingStringToParameter(payload);
    payload=strchr(payload,'=');
    payload++;
  } else {
    printFmtToDebug("MQTT message not recognized: %s - %s\r\n", topic, payload);
    return;
  }

  printFmtToDebug("MQTT message received [%s | %s]\r\n", topic, payload);

  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    set_temp_destination(param.dest_addr);
  }

  if (setmode == 2) { //query
    printFmtToDebug("%g!%d \r\n", param.number, param.dest_addr);
  } else { //command to heater
    printFmtToDebug("%s%g!%d=%s \r\n", (setmode==1?"S":"I"), param.number, param.dest_addr, payload);
    set(param.number,payload,setmode);  //command to heater
  }
  query(param.number);

  if (param.dest_addr > -1 && destAddr != param.dest_addr) {
    bus->setBusType(bus->getBusType(), bus->getBusAddr(), destAddr);
    my_dev_fam = save_my_dev_fam;
    my_dev_var = save_my_dev_var;
    my_dev_id = save_my_dev_id;
  }

}

boolean mqtt_send_discovery(boolean create=true) {
//  uint8_t destAddr = bus->getBusDest();
  char MQTTPayload[2048] = "";
  char MQTTTopic[80] = "";
  StringBuffer sb_payload;
  StringBuffer sb_topic;
  uint8_t sensor_type = 0;
  int i = 0;
  float line = 0;
  float old_line = -1;
  for (uint16_t j=0;j<sizeof(cmdtbl)/sizeof(cmdtbl[0]) - 1;j++) {
    if (bus->getBusType() == BUS_PPS && line < 15000) {
      j = findLine(15000);
    }
    line = cmdtbl[j].line;
    if (line == old_line) continue;
    if (bus->getBusType() != BUS_PPS && line >= 15000 && line <= 16000) continue;
    if (line == 19999) continue;    // skip entry for unknown parameter
    if (line > 20999) break;
    do {
      i=findLine(line);
      if (i>=0) {
        MQTTPayload[0] = '\0';
        MQTTTopic[0] = '\0';
        initStringBuffer(&sb_payload, MQTTPayload, sizeof(MQTTPayload));
        initStringBuffer(&sb_topic, MQTTTopic, sizeof(MQTTTopic));
        loadPrognrElementsFromTable(line, i);
        loadCategoryDescAddr();
        appendStringBuffer(&sb_topic, "homeassistant/");
        appendStringBuffer(&sb_payload, "{\"~\":\"%s/%d/%d/%g\",\"unique_id\":\"%g-%d-%d-%d\",\"state_topic\":\"~/status\",", MQTTTopicPrefix, bus->getBusDest(), decodedTelegram.cat, line, line, cmdtbl[i].dev_fam, cmdtbl[i].dev_var, my_dev_id);
        if (decodedTelegram.isswitch) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:toggle-switch\",");
        } else if (!strcmp(decodedTelegram.unit, U_DEG) || !strcmp(decodedTelegram.unit, U_TEMP_PER_MIN) || !strcmp(decodedTelegram.unit, U_CEL_MIN)) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:thermometer\",");
        } else if (!strcmp(decodedTelegram.unit, U_PERC)) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:percent\",");
        } else if (!strcmp(decodedTelegram.unit, U_MONTHS) || !strcmp(decodedTelegram.unit, U_DAYS) || decodedTelegram.type == VT_WEEKDAY || (decodedTelegram.type >= VT_DATETIME && decodedTelegram.type <= VT_TIMEPROG)) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:calendar\",");
        } else if (!strcmp(decodedTelegram.unit, U_HOUR) || !strcmp(decodedTelegram.unit, U_MIN) || !strcmp(decodedTelegram.unit, U_SEC) || !strcmp(decodedTelegram.unit, U_MSEC) || decodedTelegram.type == VT_HOUR_MINUTES || decodedTelegram.type == VT_HOUR_MINUTES_N || decodedTelegram.type == VT_PPS_TIME) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:clock\",");
        } else if (!strcmp(decodedTelegram.unit, U_RPM)) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:fan\",");
        } else if (!strcmp(decodedTelegram.unit, U_WATT) || !strcmp(decodedTelegram.unit, U_VOLT) || !strcmp(decodedTelegram.unit, U_KW) || !strcmp(decodedTelegram.unit, U_KWH) || !strcmp(decodedTelegram.unit, U_KWHM3) || !strcmp(decodedTelegram.unit, U_MWH) || !strcmp(decodedTelegram.unit, U_CURR) || !strcmp(decodedTelegram.unit, U_AMP)) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:lightning-bolt\",");
        } else if (decodedTelegram.type != VT_ENUM && decodedTelegram.type != VT_CUSTOM_ENUM && decodedTelegram.type != VT_CUSTOM_BYTE && decodedTelegram.type != VT_CUSTOM_BIT) {
          appendStringBuffer(&sb_payload, "\"icon\":\"mdi:numeric\",");
        }
        if (decodedTelegram.readwrite == FL_RONLY || decodedTelegram.type == VT_CUSTOM_ENUM || decodedTelegram.type == VT_CUSTOM_BYTE || decodedTelegram.type == VT_CUSTOM_BIT) {
          if (decodedTelegram.type == VT_ONOFF || decodedTelegram.type == VT_YESNO) {
            appendStringBuffer(&sb_topic, "binary_sensor/");
            appendStringBuffer(&sb_payload, "\"value_template\":\"{{'OFF' if value.split(' - ')[0] == '0' else 'ON'}}\",");
            sensor_type = MQTT_BINARY_SENSOR;
          } else {
            appendStringBuffer(&sb_topic, "sensor/");
            if (decodedTelegram.unit[0]) {
              appendStringBuffer(&sb_payload, "\"unit_of_measurement\":\"%s\",", decodedTelegram.unit);
              if (strcmp(decodedTelegram.unit, U_HOUR) && strcmp(decodedTelegram.unit, U_KWH)) {    // do not add state_class for potentially cumulative parameters 
                appendStringBuffer(&sb_payload, "\"state_class\":\"measurement\",");
              }
            }
            sensor_type = MQTT_SENSOR;
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
            appendStringBuffer(&sb_topic, "switch/");
            appendStringBuffer(&sb_payload, "\"state_on\":\"1 - %s\",\"state_off\":\"0 - %s\",\"command_topic\":\"~/set\",\"payload_on\":\"1\",\"payload_off\":\"0\",", value_on, value_off, bus->getBusDest());
            sensor_type = MQTT_SWITCH;
          } else if (decodedTelegram.type == VT_ENUM || decodedTelegram.isswitch) {
            appendStringBuffer(&sb_topic, "select/");
            appendStringBuffer(&sb_payload, "\"command_topic\":\"~/set\",\"command_template\":\"{{value.split(' - ')[0]}}\",\"options\":[");
            // We can be more relaxed in parsing the ENUMs here because all the special cases (VT_CUSTOM_ENUM or ENUMs with more than one byte etc.) are already handled above.
            uint16_t val = 0;
            uint16_t c=0;
            uint_farptr_t descAddr;
            while (c + 2 < decodedTelegram.enumstr_len) {
              val=uint16_t(*(decodedTelegram.enumstr+c));
              c = c + 2;
              descAddr = decodedTelegram.enumstr + c;
              appendStringBuffer(&sb_payload, "\"%d - %s\",", val, descAddr);
              c = c + strlen(descAddr) + 1;
            }
            appendStringBuffer(&sb_payload, "\"65535 - ---\"],");
            sensor_type = MQTT_SELECT;
          } else {
            appendStringBuffer(&sb_topic, "text/");
            appendStringBuffer(&sb_payload, "\"command_topic\":\"~/set\",\"command_template\":\"{{value}}\",");
            sensor_type = MQTT_TEXT;
          }
        }
        appendStringBuffer(&sb_payload, "\"name\":\"%02d-%02d %s - %g - %s", bus->getBusDest(), decodedTelegram.cat, decodedTelegram.catdescaddr, line, decodedTelegram.prognrdescaddr);
        if (sensor_type == MQTT_TEXT && decodedTelegram.unit[0]) {
          appendStringBuffer(&sb_payload, " (%s)", decodedTelegram.unit);
        }
        appendStringBuffer(&sb_payload, "\",\"device\":{\"name\":\"%s\",\"identifiers\":\"%s-%02X%02X%02X%02X%02X%02X\",\"manufacturer\":\"bsb-lan.de\",\"model\":\"" MAJOR "." MINOR "." PATCH "\"}}", MQTTTopicPrefix, MQTTTopicPrefix, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  
        appendStringBuffer(&sb_topic, "BSB-LAN/%g-%d-%d-%d/config", line, cmdtbl[i].dev_fam, cmdtbl[i].dev_var, my_dev_id);
  
        if (!create) {
          MQTTPayload[0] = '\0';      // If remove flag is set, send empty message to instruct auto discovery to remove the entry 
        }
        if (bus->getBusDest() == 0 || line < 15000) {     // do not send (again) parameters > 15000 when using non-zero device ID
          if (MQTTPubSubClient->connected()) {
            MQTTPubSubClient->publish(MQTTTopic, MQTTPayload, true);
          } else {
            printlnToDebug("No connection to MQTT broker, aborting...");
            return false;
          }
        }
      }
      old_line = line;
      line = get_next_prognr(line);
    } while (cmdtbl[j+1].line > line);
  }
  return true;
}