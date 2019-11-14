/*******************************************************************************
  WiFi
*******************************************************************************/
void StartWiFi(const char* ssid, const char* password)
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("StartWiFi"));

  int connAttempts = 0;
  Serial.print(F("\r\nConnecting to: ")); Serial.println(String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED )
  {
    delay(500); Serial.print(".");
    if (connAttempts > 20) {
      Serial.println("Failed to connect to WiFi");
    }
    connAttempts++;
  }
}