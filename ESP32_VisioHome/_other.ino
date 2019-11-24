/*******************************************************************************
  Get Time
*******************************************************************************/
void StartTime() {
  configTime(0, 0, "0.uk.pool.ntp.org", "time.nist.gov");
  setenv("TZ", "UTC-3",1); // Set for your locale MSK-3MSD,M3.5.0/2,M10.5.0/3
  delay(200);
  GetTime();
}

String GetTime() {
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    StartTime();
  }
  //See http://www.cplusplus.com/reference/ctime/strftime/
  //Serial.println(&timeinfo, "%a %b %d %Y   %H:%M:%S"); // Displays: Saturday, June 24 2017 14:05:49
  char output[50];
  strftime(output, 50, "%d-%m-%Y %H:%M:%S", &timeinfo); // Format needed for Google Charts is "11/12/17 22:01:00"; //dd/mm/yy hh:hh:ss
  return output;
  
}

/*******************************************************************************
  Debugger
*******************************************************************************/
void debugger(String intext) {
  Serial.print (intext);
  intext.replace("{", " "); intext.replace("}", " "); intext.replace("\"", " "); intext.replace("\n", "<br>");
  infopage += intext;
  
  }
  
