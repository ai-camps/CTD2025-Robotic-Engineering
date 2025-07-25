#include <Arduino.h>    // Include Arduino core library
#include <ArduinoOTA.h> // Library for OTA updates
#include <WiFi.h>       // Library for WiFi

// Motor Pins
constexpr int M1_A_PIN = 26;
constexpr int M1_B_PIN = 27;
constexpr int M2_A_PIN = 33;
constexpr int M2_B_PIN = 25;
constexpr int M3_A_PIN = 32;
constexpr int M3_B_PIN = 16;
constexpr int M4_A_PIN = 17;
constexpr int M4_B_PIN = 18;

// Motor PWM Channels
constexpr int M1_A_PWM_CH = 0;
constexpr int M1_B_PWM_CH = 1;
constexpr int M2_A_PWM_CH = 2;
constexpr int M2_B_PWM_CH = 3;
constexpr int M3_A_PWM_CH = 4;
constexpr int M3_B_PWM_CH = 5;
constexpr int M4_A_PWM_CH = 6;
constexpr int M4_B_PWM_CH = 7;

// Motor PWM Resolution
constexpr int PWM_RESOLUTION = 10;

// Motor PWM Frequency
constexpr int PWM_FREQUENCY = 2000;

// Motor Normal Speed
constexpr int MOTOR_NORMAL_SPEED = 1000;

// WiFi settings
constexpr auto WIFI_SSID = "sesplearningstudios";
constexpr auto WIFI_PASSWORD = "@nn3nb3rg";

// OTA settings
constexpr auto OTA_PORT = 3232; // OTA port

// function prototypes
void connectWiFi();
void initOTA();
void initMotors();
void rotateMotorForward(int motorAChannel, int motorBChannel, int speed);
void rotateMotorBackward(int motorAChannel, int motorBChannel, int speed);
void stopMotor(int motorAChannel, int motorBChannel);
void rotateAllMotorsForward(int speed);
void rotateAllMotorsBackward(int speed);
void stopAllMotors();

void setup()
{
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize WiFi
  connectWiFi();

  // Initialize OTA
  initOTA();

  // Initialize motors
  initMotors();

  Serial.println("Vehicle motor control system ready!");
  Serial.println("Starting motor rotation sequence...");
}

void loop()
{
  // Handle OTA updates
  ArduinoOTA.handle();

  // Rotate all motors forward for 3 seconds
  Serial.println("Rotating all motors forward...");
  rotateAllMotorsForward(MOTOR_NORMAL_SPEED);
  delay(3000);

  // Stop all motors for 1 second
  Serial.println("Stopping all motors...");
  stopAllMotors();
  delay(1000);

  // Rotate all motors backward for 3 seconds
  Serial.println("Rotating all motors backward...");
  rotateAllMotorsBackward(MOTOR_NORMAL_SPEED);
  delay(3000);

  // Stop all motors for 1 second
  Serial.println("Stopping all motors...");
  stopAllMotors();
  delay(1000);
}

// Function to rotate a motor forward
void rotateMotorForward(int motorAChannel, int motorBChannel, int speed)
{
  ledcWrite(motorAChannel, speed);
  ledcWrite(motorBChannel, 0);
}

// Function to rotate a motor backward
void rotateMotorBackward(int motorAChannel, int motorBChannel, int speed)
{
  ledcWrite(motorAChannel, 0);
  ledcWrite(motorBChannel, speed);
}

// Function to stop a motor
void stopMotor(int motorAChannel, int motorBChannel)
{
  ledcWrite(motorAChannel, 0);
  ledcWrite(motorBChannel, 0);
}

// Function to rotate all motors forward
void rotateAllMotorsForward(int speed)
{
  rotateMotorForward(M1_A_PWM_CH, M1_B_PWM_CH, speed);
  rotateMotorForward(M2_A_PWM_CH, M2_B_PWM_CH, speed);
  rotateMotorForward(M3_A_PWM_CH, M3_B_PWM_CH, speed);
  rotateMotorForward(M4_A_PWM_CH, M4_B_PWM_CH, speed);
}

// Function to rotate all motors backward
void rotateAllMotorsBackward(int speed)
{
  rotateMotorBackward(M1_A_PWM_CH, M1_B_PWM_CH, speed);
  rotateMotorBackward(M2_A_PWM_CH, M2_B_PWM_CH, speed);
  rotateMotorBackward(M3_A_PWM_CH, M3_B_PWM_CH, speed);
  rotateMotorBackward(M4_A_PWM_CH, M4_B_PWM_CH, speed);
}

// Function to stop all motors
void stopAllMotors()
{
  stopMotor(M1_A_PWM_CH, M1_B_PWM_CH);
  stopMotor(M2_A_PWM_CH, M2_B_PWM_CH);
  stopMotor(M3_A_PWM_CH, M3_B_PWM_CH);
  stopMotor(M4_A_PWM_CH, M4_B_PWM_CH);
}

void connectWiFi()
{
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print connection status
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());
}

// Function to initialize OTA
void initOTA()
{
  ArduinoOTA.setPort(OTA_PORT);

  ArduinoOTA.onStart([]()
                     {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else { // U_SPIFFS
            type = "filesystem";
        }
        Serial.println("Start updating " + type); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
        // Calculate progress percentage
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

  // Start OTA
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
  Serial.print("OTA Port: ");
  Serial.println(OTA_PORT);
  Serial.print("OTA IP: ");
  Serial.println(WiFi.localIP());
}

void initMotors()
{
  // Initialize motor pins
  ledcSetup(M1_A_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M1_B_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2_A_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2_B_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M3_A_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M3_B_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M4_A_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M4_B_PWM_CH, PWM_FREQUENCY, PWM_RESOLUTION);

  ledcAttachPin(M1_A_PIN, M1_A_PWM_CH);
  ledcAttachPin(M1_B_PIN, M1_B_PWM_CH);
  ledcAttachPin(M2_A_PIN, M2_A_PWM_CH);
  ledcAttachPin(M2_B_PIN, M2_B_PWM_CH);
  ledcAttachPin(M3_A_PIN, M3_A_PWM_CH);
  ledcAttachPin(M3_B_PIN, M3_B_PWM_CH);
  ledcAttachPin(M4_A_PIN, M4_A_PWM_CH);
  ledcAttachPin(M4_B_PIN, M4_B_PWM_CH);
}