/*******************************************************************************
  Data
*******************************************************************************/
String PinSend(String pintipe, uint8_t no_pin)
{
  debugger("PinSend \n");
   
  String pinstatus = "\"" + pintipe + "\" : \"";
  if (digitalRead(no_pin)) pinstatus += "active";
  if (!digitalRead(no_pin)) pinstatus += "inactive";
  pinstatus += "\"";
  return pinstatus;
}
