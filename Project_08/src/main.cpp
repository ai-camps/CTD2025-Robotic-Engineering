#include <Arduino.h>

// Pin definitions
constexpr auto BUTTON_PIN = 4;

void setup()
{

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the Red LED pin as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{

  // Read the state of the Red LED
  Serial.println(digitalRead(BUTTON_PIN) ? "Released" : "Pressed");

  delay(3000);
}