#include <Servo.h>

Servo servo1;

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    // Read the position for rthumb
    if (input == '1') {
      Serial.println("Enter position for Servo 1 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        servo1.write(newPosition);
        Serial.println("Servo 1 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }
  }
}
