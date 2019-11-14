/*******************************************************************************
  pages HOME
*******************************************************************************/
void pagesHome()
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("showHome"));

  webpage = ""; // don't delete this command, it ensures the server works reliably!
  append_HTML_header();

  webpage += "<div class=\"info-container\">";
  
  webpage += "<span class=\"inf temp\" id=\"AI_01\"></span>";
  webpage += "<span class=\"inf hum\" id=\"AI_02\"></span>";

  webpage += "</div>";
  
  webpage += "<div class=\"container\">";
  
  webpage += "<div class=\"btn torchere\" id=\"DO_01\"><em>Спальня</em><em>Торшер</em></div>";
  webpage += "<div class=\"btn chandelier\" id=\"DO_02\"><em>Спальня</em><em>Центральный свет</em></div>";
  webpage += "<div class=\"btn light\" id=\"DO_03\"><em>Спальня</em><em>Боковой свет</em></div>";
  webpage += "<div class=\"btn service\" id=\"DO_04\"><em>Требуется</em><em>Уборка</em></div>";

  webpage += "</div>";
  append_HTML_footer();
  server.send(200, "text/html", webpage); 
}

/*******************************************************************************
  pages AJAX 
*******************************************************************************/
void pagesAJAX()
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("Выполняется функция обновления данных Температура, Влажность, Статус освещения"));
  Serial.print(F("Действующая заявка: ")); Serial.println(kvtemp);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Fahrenheit (the default)
  float hic = dht.computeHeatIndex(t, h, false);

  if (t > 30 && !kvtemp) {
    Serial.println(F("------------------------------------"));
    Serial.println(F("Зафиксировано превышение температуры > 30!"));
    Serial.print(F("Температура: ")); Serial.println(t);
  
    //topicid = SendTempRequestOpen(t);
    //kvtemp = topicid;
    
  } 

  if (t < 29 && kvtemp) {
    Serial.println(F("------------------------------------"));
    Serial.println(F("Зафиксировано востановление температуры < 29"));
    Serial.print(F("Температура: ")); Serial.println(t);
    
    //kvtemp = 0;
    //SendRequestClose(kvtemp);
    
  }
  
  /* server responds 200 with a json payload */
  /* although preferably concatenate your real sensor data here */
  String message="{";
  
  // Отправляем данные в виде JSON

  message += "\"Temp\": \"";
  message += t;
  message += "\"";
  
  message += ", \"Hum\": \"";
  message += h;
  message += "\"";

  message += ", \"HeatIndex\": \"";
  message += hic;
  message += "\"";
  
  // Объекты
  message += "," + PinSend("DO_01", 16);
  
  message += "}";
  server.send(200, "application/json",message);

}

/*******************************************************************************
  pages Command
*******************************************************************************/
void pagesCommand()
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("pagesCommand"));
  
  String message="{"; 
  if (server.args() > 0 )
  { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ )
    {
      String Argument_Name   = server.argName(i);
      String client_response = server.arg(i);
      
      Serial.println(Argument_Name+" : " + client_response);
      //infodata += Argument_Name+" : " + client_response; 
      
      if (Argument_Name == "DO_01") {
          if (client_response == "active") {
            digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on, set pin LOW on most boards
          }
          if (client_response == "inactive") {
            digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off, set pin HIGH, LED is active low!
          }         
      }
         
            message += "\"argument\" : \"";
            message += client_response;
            message += "\""; 
    }
  }
  message += "}";
  
  server.send(200, "application/json",message);
}

/*******************************************************************************
  pages NotFound
*******************************************************************************/
void handleNotFound()
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("handleNotFound"));
  
  String message = "Command not found\n";
  server.send(404, "text/plain", message);
}
