/*******************************************************************************
  WebSocket
*******************************************************************************/
// Вызывается при получении любого сообщения WebSocket
void onWebSocketEvent(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {
 
  // Проверим тип события WebSocket
  switch(type) {
 
    // Клиент отключился
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
 
    // Новый клиент подключился
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;
 
    // Сообщение от клиента
    case WStype_TEXT:
      Serial.printf("num: %u, type: %s, payload: %s, length: %u \n", num, type, payload, length);
      //char toWait[20] = payload;
      
      /*String socketstr = "";
      for ( uint8_t i = 0; i < length; i++ ) {
        
        socketstr =+ (char)payload[i];
      }*/
      
      //SceneControl(scene);
      //webSocket.sendTXT(num, payload); 
      break;
 
    // Для всего остального: ничего пока не делать 
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

/*******************************************************************************
  webSocket transmit
*******************************************************************************/
void webSocketTransmit(String payload)
{
  debugger("webSocket: "); debugger(payload);debugger("\n");
  // send message to client
  // webSocket.sendTXT(num, "message here");

  // send data to all connected clients
  webSocket.broadcastTXT(payload);

}
