#include <Arduino.h>

// Device ID
String deviceID;

// Pin definitions
constexpr auto BUTTON_PIN = 2;

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Get device ID
  deviceID = String(ESP.getEfuseMac(), HEX);

  // Initialize the Red LED pin as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{

  // Print the device ID
  Serial.println(deviceID);

  // Read the state of the Red LED
  Serial.println(digitalRead(BUTTON_PIN));

  delay(3000);
}