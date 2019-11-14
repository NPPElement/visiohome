/*******************************************************************************
  Data
*******************************************************************************/
String PinSend(String pintipe, uint8_t no_pin)
{
  Serial.println(F("------------------------------------"));
  Serial.println(F("PinSend"));
   
  String pinstatus = "\"" + pintipe + "\" : \"";
  if (digitalRead(no_pin)) pinstatus += "active";
  if (!digitalRead(no_pin)) pinstatus += "inactive";
  pinstatus += "\"";
  return pinstatus;
}