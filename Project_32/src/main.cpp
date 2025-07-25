#include <Arduino.h>    // Include Arduino core library
#include <ArduinoOTA.h> // Library for OTA updates
#include <WiFi.h>       // Library for WiFi

// Motor 1 Pins
constexpr int M1_A_PIN = 26;
constexpr int M1_B_PIN = 27;

// Motor 1 PWM Channels
constexpr int M1_A_PWM_CH = 0;
constexpr int M1_B_PWM_CH = 1;

// Motor PWM Settings
constexpr int PWM_RESOLUTION = 10;
constexpr int PWM_FREQUENCY = 2000;
constexpr int MOTOR_SPEED = 500;

// WiFi settings
constexpr auto WIFI_SSID = "sesplearningstudios";
constexpr auto WIFI_PASSWORD = "@nn3nb3rg";

// OTA settings
constexpr auto OTA_PORT = 3232;

// Function prototypes
void connectWiFi();
void initOTA();
void initMotor();

void setup()
{
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("Starting simple motor control demo...");

  // Initialize WiFi
  connectWiFi();

  // Initialize OTA (Over-The-Air updates)
  initOTA();

  // Initialize motor
  initMotor();

  Serial.println("Motor M1 ready! Starting forward rotation...");
}

void loop()
{
  // Handle OTA updates
  ArduinoOTA.handle();

  // Rotate M1 motor forward continuously
  // Set M1_A to speed and M1_B to 0 for forward rotation
  ledcWrite(M1_A_PWM_CH, MOTOR_SPEED);
  ledcWrite(M1_B_PWM_CH, 0);

  // Small delay to prevent overwhelming the system
  delay(100);
}

void connectWiFi()
{
  // Connect to WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print connection info
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void initOTA()
{
  // Set OTA port
  ArduinoOTA.setPort(OTA_PORT);

  // OTA event handlers
  ArduinoOTA.onStart([]()
                     {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {
            type = "filesystem";
        }
        Serial.println("Start updating " + type); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
        int progressPercent = (progress * 100) / total;
        Serial.printf("Progress: %u%%\r", progressPercent); });

  ArduinoOTA.onEnd([]()
                   { Serial.println("\nOTA End"); });

  ArduinoOTA.onError([](ota_error_t error)
                     {
                       String errorMsg = "Error[" + String(error) + "]: ";
                       if (error == OTA_AUTH_ERROR)
                       {
                         errorMsg += "Auth Failed";
                       }
                       else if (error == OTA_BEGIN_ERROR)
                       {
                         errorMsg += "Begin Failed";
                       }
                       else if (error == OTA_CONNECT_ERROR)
                       {
                         errorMsg += "Connect Failed";
                       }
                       else if (error == OTA_RECEIVE_ERROR)
                       {
                         errorMsg += "Receive Failed";
                       }
                       else if (error == OTA_END_ERROR)
                       {
                         errorMsg += "End Failed";
                       }
                       Serial.println(errorMsg); });

  // Start OTA service
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
  Serial.print("OTA IP: ");
  Serial.println(WiFi.localIP());
}

void initMotor()
{
  // Setup PWM for motor M1
  ledcSetup(M1_A_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M1_B_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);

  // Attach pins to PWM channels
  ledcAttachPin(M1_A_PIN, M1_A_PWM_CH);
  ledcAttachPin(M1_B_PIN, M1_B_PWM_CH);

  Serial.println("Motor M1 initialized");
}