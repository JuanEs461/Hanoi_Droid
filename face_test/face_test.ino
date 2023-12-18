#include <Servo.h>

Servo myservo;  // Create a servo object

int restPosition = 90;  // Set the rest position in degrees

void setup() {
  myservo.attach(3);  // Attach the servo to pin 3
  myservo.write(restPosition);  // Move the servo to the rest position
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Servo control example");
}

void loop() {
  int userPosition;
  
  // Prompt the user for input
  Serial.print("Enter a servo position (0-180): ");
  
  // Wait for user input
  while (Serial.available() == 0) {
    // Do nothing until input is received
  }
  
  // Read user input
  userPosition = Serial.parseInt();
  
  // Check if the input is within the valid range (0-180)
  if (userPosition >= 0 && userPosition <= 180) {
    // Move the servo to the user-specified position
    myservo.write(userPosition);
    delay(500);  // Delay to allow the servo to reach the desired position
    Serial.print("Moved to position: ");
    Serial.println(userPosition);
  } else {
    Serial.println("Invalid input. Please enter a position between 0 and 180.");
  }
}
