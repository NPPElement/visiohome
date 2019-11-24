/*******************************************************************************
  Communication module visioHOME
*******************************************************************************/
#include <ESP32WebServer.h>  //https://github.com/Pedroalbuquerque/ESP32WebServer download and place in your Libraries folder
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MD5Builder.h>
#include <string.h>
#include <time.h>
//#include  <ETH.h>         // Ethernet
#include <WiFi.h>           // WiFi
#include <WiFiClient.h>
#include <WebSocketsServer.h> // WebSockets
#include <DHT.h>            // Оборудование
#include <Update.h>         // Обновление
#include <PubSubClient.h>   // MQTT

/*******************************************************************************
  VARIABLES
*******************************************************************************/
// TODO To transfer the settings via the WEB with an entry in the memory
const char* host              = "visiohome";  // visiohome.local
int web_port                  = 80;           // Web port
const char* ssid              = "SSID";       // WiFi SSID
const char* password          = "password";   // WiFi Password
    
const char* siteheading       = "visioHOME";  // Site's Main Title
String      object_name       = "5015";       // Имя объекта (основная папка)
const char* room_name         = "Спальня";    // Имя комнаты (вложенная комната)
const char* siteversion       = "v1.3";       // Version Website

// Visiodesk option not yet available
String visiodesk               = "http://visiodesk.net:8080";    // visiodesk server
String authorization           = "Bearer ";                      // TOKEN
const char* login_visiodesk    = "login";                        // visiodesk login
const char* password_visiodesk = "password";                     // visiodesk password

// MQTT Client Info
const char* mqtt_server       = "92.53.70.228";                  // mqtt server "visiodesk.net"
int mqtt_port                 = 1883;                            // mqtt port
const char* mqtt_user         = "zVqQjHD3IoNuIYnAbfF4";          // mqtt device login
const char* mqtt_name         = "visiohome_module";              // mqtt name

// WebSockets Server
int ws_port                   = 9999;                             // ws port

String webpage = "";                          // General purpose variable to hold HTML code
void SendData(String dataJson);
char request[64];
int topicid;
int kvtemp = 0;
int service;
int scene;     // Сцена 1-15 (F)
int output[5]; // Выходы реле или ШИМ
int input[4];  // Входы сцен или ШИМ

String infopage; 
unsigned long timer100ms;
unsigned long timer5000ms;

// WiFi MQTT WEB WS
WiFiClient espClient;
PubSubClient client(espClient);
ESP32WebServer server(web_port);
WebSocketsServer webSocket = WebSocketsServer(ws_port);

// TODO Transfer to settings via WEB
// Uncomment the type of sensor in use:
#define DHTPIN 5
// Uncomment the type of sensor in use:
#define DHTTYPE      DHT11   // DHT 11
//#define DHTTYPE    DHT22   // DHT 22 (AM2302)
//#define DHTTYPE    DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

/*******************************************************************************

*******************************************************************************/
void setup()
{
  Serial.begin  (115200);                    // initialize serial communications
  GpioInit();
  
  // Initialize Ethernet
  // ETH.begin ();

  // Initialize WiFi interfaces. 
  visiodeskInit();                            // not yet available
  StartWiFi (ssid, password);                 // Start WiFi
 
  // Getvisiodesk();                          // not yet available  
  WebServerInit();                            // initialize html (see html.ino) 

  // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  StartTime();                                // Initialize Time
  delay(1500);
}

/*******************************************************************************
  Loop
*******************************************************************************/
void loop ()
{
  server.handleClient();  // Look for and handle WEB
  webSocket.loop();       // Look for and handle WebSocket data
  client.loop();          // Look for and handle MQTT data
  
  if (millis() > timer100ms) start100ms();
  if (millis() > timer5000ms) start5000ms();
      
}

/*******************************************************************************
  Tasks each 100 ms
*******************************************************************************/
void start100ms()
{
  timer100ms = millis() + 100;
  
}

/*******************************************************************************
  Tasks each 2 seconds
*******************************************************************************/
void start5000ms()
{
  if (!client.connected()) {
    StartMqtt();
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    StartWiFi (ssid, password);
  }
  
  timer5000ms = millis() + 5000;
  
  MQTTpublish();

}
