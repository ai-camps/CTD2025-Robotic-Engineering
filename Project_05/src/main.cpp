#include <Arduino.h>
#include <WiFi.h>

// Global device ID
String deviceID;

// Wifi credentials
constexpr char ssid[] = "your_ssid";
constexpr char password[] = "your_password";

void setup()
{
  // Initialize WiFi
  WiFi.begin(ssid, password);

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Get device ID
  deviceID = String(ESP.getEfuseMac(), HEX);
}

void loop()
{
  // Print Hello World every 2 seconds
  Serial.println("Device ID: " + deviceID);
  Serial.println("WiFi connected: " + String(WiFi.isConnected()));
  Serial.println("WiFi MAC: " + String(WiFi.macAddress()));
  Serial.println("WiFi IP: " + String(WiFi.localIP().toString()));
  delay(3000);
}