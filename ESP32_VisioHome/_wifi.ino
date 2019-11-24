/*******************************************************************************
  WiFi
*******************************************************************************/
void StartWiFi(const char* ssid, const char* password)
{
  debugger("StartWiFi \n");
  int connAttempts = 0;
  debugger("Connecting to: "); debugger(ssid); debugger("\n");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED )
  {
    debugger(".");
    delay(200);
    if (connAttempts > 3) {
      debugger("Failed to connect to WiFi \n");
    }
    connAttempts++;
  }

  //int locIP = WiFi.localIP();
  //debugger("IP address: "); debugger((int) locIP); debugger("\n");

  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) {                 //http://visiohome.local
    debugger("Error setting up MDNS responder!\n");
  }
  debugger("mDNS responder started\n");
  debugger("HOST: http://"); debugger(host); debugger(".local\n");
}
