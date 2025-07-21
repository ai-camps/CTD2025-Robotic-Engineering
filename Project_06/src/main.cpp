#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

// WiFi credentials
constexpr char ssid[] = "sesplearningstudios";
constexpr char password[] = "@nn3nb3rg";

// WordPress API endpoint (use HTTPS for security)
constexpr char apiEndpoint[] = "https://www.ai-camps.com/wp-json/device/v1/info";

// API Token
constexpr char apiToken[] = "CTD2025-TOKEN-20250630";

// Device information
String chipModel; // Will be initialized in setup()
String deviceID;  // Will be initialized in setup()

// Owner information
constexpr char ownerOrg[] = "CTD2025";
constexpr char ownerEmail[] = "jun.wen@ai-camps.com";

void setupWiFi()
{
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void registerDevice()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    HTTPClient http;

    Serial.println("Connecting to server...");

    // Skip certificate validation (for testing only)
    client.setInsecure(); // WARNING: disables SSL certificate verification!

    if (!http.begin(client, apiEndpoint))
    {
      Serial.println("Failed to connect to server");
      return;
    }

    // Set headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", apiToken);

    // Create JSON document
    JsonDocument doc;
    doc["chipModel"] = chipModel;
    doc["deviceID"] = deviceID;
    doc["ownerOrg"] = ownerOrg;
    doc["ownerEmail"] = ownerEmail;
    doc["mac"] = WiFi.macAddress();
    doc["IP"] = WiFi.localIP().toString();

    String jsonString;
    serializeJson(doc, jsonString);

    Serial.println("Sending data: " + jsonString);

    // Send POST request
    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0)
    {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    }
    else
    {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      Serial.print("Error: ");
      Serial.println(http.errorToString(httpResponseCode));
      // Keep register LED off on failure
    }

    http.end();
  }
  else
  {
    Serial.println("WiFi not connected!");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Initialize device ID and chip model
  deviceID = String(ESP.getEfuseMac(), HEX);
  chipModel = ESP.getChipModel();

  Serial.print("Device ID: ");
  Serial.println(deviceID);
  Serial.print("Chip Model: ");
  Serial.println(chipModel);

  setupWiFi();
  registerDevice();
}

void loop()
{
  // Re-register device every hour
  static unsigned long lastRegistration = 0;
  const unsigned long registrationInterval = 3600000; // 1 hour

  if (millis() - lastRegistration >= registrationInterval)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      setupWiFi();
    }
    registerDevice();
    lastRegistration = millis();
  }

  delay(1000);
}