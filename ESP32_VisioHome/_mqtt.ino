/*******************************************************************************
  MQTT 
*******************************************************************************/
void MQTTpublish() {

  float humidity    = dht.readHumidity();
  float pressure    = 0;
  float temperature = dht.readTemperature();
  //float hic = dht.computeHeatIndex(t, h, false); // TODO consider the need for this option

  // Create outTopic 1 string
  // outTopic String format: {"key1":"value1", "key2":"value2"}
  String outTopic = "{";
  outTopic += "\"temperature\":";      outTopic += temperature;       outTopic += ",";
  outTopic += "\"pressure\":";         outTopic += pressure;          outTopic += ",";
  outTopic += "\"humidity\":";         outTopic += humidity;
  outTopic += "}";
  transmitPayload(outTopic);
  
  // Create outTopic 2 string
  outTopic = "{";
  for ( uint8_t i = 0; i < 3; i++ ) {
    if(i==0) outTopic += "\"output";
    else outTopic += ",\"output";
      outTopic += i+1;
      outTopic += "\":";
      if (output[i] == 0) {outTopic += "\"inactive\"";}
      if (output[i] == 1) {outTopic += "\"active\"";}
      if (output[i] > 1) {outTopic += output[i];}     
    }
  outTopic += "}";
  transmitPayload(outTopic);
  
  // Create outTopic 3 string
  outTopic = "{";
  for ( uint8_t i = 3; i < 5; i++ ) {
    if(i==3) outTopic += "\"output";
    else outTopic += ",\"output";
      outTopic += i+1;
      outTopic += "\":";
      if (output[i] == 0) {outTopic += "\"inactive\"";}
      if (output[i] == 1) {outTopic += "\"active\"";}
      if (output[i] > 1) {outTopic += output[i];}     
    }
  outTopic += ",\"scene\":";         outTopic += scene;
  outTopic += "}";
  transmitPayload(outTopic);

  // Create outTopic 4 string
  outTopic = "{";
  for ( uint8_t i = 0; i < 4; i++ ) {
    if(i==0) outTopic += "\"input";
    else outTopic += ",\"input";
      outTopic += i+1;
      outTopic += "\":";
      if (input[i] == 0) {outTopic += "\"inactive\"";}
      if (input[i] == 1) {outTopic += "\"active\"";}
      if (input[i] > 1) {outTopic += input[i];}     
    }
  outTopic += "}";
  transmitPayload(outTopic);
}

/*******************************************************************************
  reconnect MQTT
*******************************************************************************/
void StartMqtt() {
  // Loop until we're reconnected
    debugger("Attempting MQTT connection...\n");
    // Attempt to connect
    if (client.connect(mqtt_name, mqtt_user, NULL)) {
      debugger("MQTT connected\n");
    } else {
      debugger("Failed publish MQTT rc = "); 
              Serial.print(client.state());
            // TODO To make a conclusion of the text on case
            //  int - the client state, which can take the following values (constants defined in PubSubClient.h):
            // -4 : MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time
            // -3 : MQTT_CONNECTION_LOST - the network connection was broken
            // -2 : MQTT_CONNECT_FAILED - the network connection failed
            // -1 : MQTT_DISCONNECTED - the client is disconnected cleanly
            // 0 : MQTT_CONNECTED - the client is connected
            // 1 : MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT
            // 2 : MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier
            // 3 : MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection
            // 4 : MQTT_CONNECT_BAD_CREDENTIALS - the username/password were rejected
            // 5 : MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect
      debugger(" try again in 5 seconds\n");
    }
}

/*******************************************************************************
  MQTT transmit
*******************************************************************************/
void transmitPayload(String payload)
{
  webSocketTransmit(payload);
  
  debugger("MQTT Topic: "); debugger(payload);debugger("\n");
  // Convert Payload string to c-string and transmit
  char attributes[500];
  payload.toCharArray(attributes, 500);
  client.publish("v1/devices/me/telemetry", attributes);
}

/*******************************************************************************
  MQTT handle message arrived
*******************************************************************************/
void callback(char* topic, byte* payload, unsigned int length) {
  debugger("Message arrived ["); debugger(topic); debugger("]\n");

  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    String str_payload = (String)payload[i];
    debugger(str_payload);
  }
  debugger("\n");
}
