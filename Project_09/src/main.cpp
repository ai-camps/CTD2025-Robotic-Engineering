#include <Arduino.h>

// Device ID
String deviceID;

// Pin definitions
constexpr auto TILT_SENSOR_PIN = 2;

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Get device ID
  deviceID = String(ESP.getEfuseMac(), HEX);

  // Initialize the Red LED pin as an output
  pinMode(TILT_SENSOR_PIN, INPUT);
}

void loop()
{

  // Print the device ID
  Serial.println(deviceID);

  // Read the state of the Red LED
  Serial.println(digitalRead(TILT_SENSOR_PIN));

  delay(3000);
}