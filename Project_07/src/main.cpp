#include <Arduino.h>

// Pin definitions
constexpr auto RED_LED_PIN = 13;

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the Red LED pin as an output
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop()
{
  // Read the state of the Red LED
  Serial.println(digitalRead(RED_LED_PIN) ? "On" : "Off");
  delay(3000);
}