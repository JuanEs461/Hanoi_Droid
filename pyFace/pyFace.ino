#include <Servo.h>

Servo servoX;
Servo servoY;

void setup() {
  servoX.attach(9);  // Attach the servos to the correct pins
  servoY.attach(10);
  Serial.begin(9600);

  // Set servos to rest position
  servoX.write(90);
  servoY.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming bytes
    String input = Serial.readStringUntil('\n');
    int commaIndex = input.indexOf(',');
    int posX = input.substring(0, commaIndex).toInt();
    int posY = input.substring(commaIndex + 1).toInt();

    // Move the servos
    servoX.write(posX);
    servoY.write(posY);
  }
}
