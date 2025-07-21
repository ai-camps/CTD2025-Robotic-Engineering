#include <Arduino.h>

// Global device ID
String deviceID;

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Get device ID
  deviceID = String(ESP.getEfuseMac(), HEX);
}

void loop()
{
  // Print Hello World every 2 seconds
  Serial.println("Device ID: " + deviceID);
  delay(3000);
}