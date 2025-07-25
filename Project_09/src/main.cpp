#include <Arduino.h>

// Pin definitions
constexpr auto TILT_SENSOR_PIN = 2;

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the Red LED pin as an output
  pinMode(TILT_SENSOR_PIN, INPUT);
}

void loop()
{

  // Read the state of the Red LED
  Serial.println(digitalRead(TILT_SENSOR_PIN) ? "On" : "Off");

  delay(3000);
}