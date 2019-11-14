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
#include <DHT.h>            // Оборудование
#include <Update.h>         // Обновление

/*******************************************************************************
  VARIABLES
*******************************************************************************/
const char* host        = "visiohome";      // visiohome.local
const char* ssid        = "SSID";           // WiFi SSID
const char* password    = "Password";       // WiFi Password

const char* siteheading = "VisioHome";      // Site's Main Title
String      object_name = "5015";     // Имя объекта (основная папка)
const char* room_name   = "Спальня";        // Имя комнаты (вложенная комната)
const char* siteversion = "v1.3";           // Version Website

const char* login_visiobas    = "login";    // not yet available
const char* password_visiobas = "password"; // not yet available

String webpage = "";                        // General purpose variable to hold HTML code
void SendData(String dataJson);
char request[64];
int topicid;
int kvtemp = 0;
int service;

String visiobas          = "http://67.207.77.41:8080"; // Visiobas server
String authorization     = "Bearer ";         // TOKEN
 

ESP32WebServer server(80);                  // Start server on port 80 or 8080 or other

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
  Serial.begin  (115200);                   // initialize serial communications
  GpioInit();                               // initialize gpio (see _gpio.ino)
  VisiobasInit();                           // not yet available
  
  // Initialize Ethernet
  // Serial.println(F("------------------------------------"));
  // ETH.begin ();

  // Initialize WiFi interfaces. 
  Serial.println(F("------------------------------------"));
  WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("IP address: ");  Serial.println(WiFi.localIP());

  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) {                 //http://visiohome.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  Serial.print("HOST: http://"); Serial.print(host); Serial.println(".local");

  GetVisiobas();                          // not yet available  
  // Initialize HTML.
  WebServerInit();                        // initialize html (see html.ino) 
}

/*******************************************************************************
  Loop
*******************************************************************************/
void loop ()
{
  server.handleClient();
}
