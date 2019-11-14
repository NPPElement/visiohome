/*******************************************************************************
  Configuration fits ready-made solutions:
  https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/open-source-hardware
  https://www.olimex.com/Products/IoT/ESP32/ESP32-POE-ISO/open-source-hardware
  https://www.olimex.com/Products/IoT/ESP32/ESP32-GATEWAY/open-source-hardware
  and not only)

  GPIO00 Auto program
  GPIO02 Auto program
  GPIO01 USB
  GPIO03 USB
  GPIO14 CD   
  GPIO15 CD
  Ethernet GPIO 18-27

*******************************************************************************/
void GpioInit()
{
  // Initialize UART interfaces.
  Serial2.begin (115200, SERIAL_8N1, 36, 4, false);
  Serial.println(F("------------------------------------"));
  Serial.println(F("UART RXD Pin: 36"));
  Serial.println(F("UART TXD Pin: 04"));

  // Initialize i2c interfaces.
  Serial.println(F("------------------------------------"));
  Serial.println(F("I2C Sensors to the default SDA, SCL "));
  Serial.print  (F("I2C SDA Pin: ")); Serial.println(String(SDA)); // GPIO16 I2C  (SDA)
  Serial.print  (F("I2C SCL Pin: ")); Serial.println(String(SCL)); // GPIO13 I2C  (SCL)
  
  // Initialize DI pin
  pinMode (36, INPUT); //DI-1 / UART (RXD)
  pinMode (35, INPUT); //DI-2
  pinMode (34, INPUT); //DI-3
  pinMode (39, INPUT); //DI-4

  // Initialize DO pin 
  pinMode (04, OUTPUT); digitalWrite(04, LOW); //DO-1 / UART (TXD)
  //pinMode (05, OUTPUT); digitalWrite(05, LOW); //DO-2
  pinMode (12, OUTPUT); digitalWrite(12, LOW); //DO-3
  pinMode (32, OUTPUT); digitalWrite(32, LOW); //DO-4
  pinMode (33, OUTPUT); digitalWrite(33, LOW); //DO-5

  dht.begin();                              // Датчик температуры и влажности
}
