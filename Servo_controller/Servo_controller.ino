#include <Servo.h>

// Create Servo objects for 16 servos
Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8;
Servo servo9, servo10, servo11, servo12, servo13, servo14, servo15, servo16;

int servoSelector = 0; // Variable to store the selected servo number

void setup() {
  // Attach each servo to a pin
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);
  servo9.attach(10);
  servo10.attach(11);
  servo11.attach(12);
  servo12.attach(13);

  // Set initial servo position to 90 degrees 
  for (int i = 1; i <= 13; i++) {
    setServoPosition(i, 90);
  }

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the switch input to select a servo
  servoSelector = readSwitch(); // This function to reads your switch input

  // Check if the selected servo number is valid (between 1 and 16)
  if (servoSelector >= 1 && servoSelector <= 16) {
    // Read and set the new position for the selected servo
    int newPosition = readNewPosition(); // Implement this function to read your input (e.g., potentiometer)
    setServoPosition(servoSelector, newPosition);
    Serial.print("Servo ");
    Serial.print(servoSelector);
    Serial.print(" set to position ");
    Serial.println(newPosition);
    delay(1000); // Delay to avoid rapid changes
  }
}

// Function to set the position of a servo by its number (1 to 16)
void setServoPosition(int servoNumber, int newPosition) {
  switch (servoNumber) {
    case 1:
      servo1.write(newPosition);
      break;
    case 2:
      servo2.write(newPosition);
      break;
    case 3:
      servo3.write(newPosition);
      break;
    case 4:
      servo4.write(newPosition);
      break;
    case 5:
      servo5.write(newPosition);
      break;
    case 6:
      servo6.write(newPosition);
      break;
    case 7:
      servo7.write(newPosition);
      break;
    case 8:
      servo8.write(newPosition);
      break;
    case 9:
      servo9.write(newPosition);
      break;
    case 10:
      servo10.write(newPosition);
      break;
    case 11:
      servo11.write(newPosition);
      break;
    case 12:
      servo12.write(newPosition);
      break;
    case 13:
      servo13.write(newPosition);
      break;
    case 14:
      servo14.write(newPosition);
      break;
    case 15:
      servo15.write(newPosition);
      break;
    case 16:
      servo16.write(newPosition);
      break;
    default:
      break;
  }
}

// Implement a function to read your switch input (e.g., digitalRead)
int readSwitch() {
  int switchPin = 2; // Replace with the actual pin number connected to the switch
  return digitalRead(switchPin);
}


// Implement a function to read your input (e.g., analogRead)
int readNewPosition() {
  int potPin = A0; // Replace with the actual analog pin number connected to the potentiometer
  int sensorValue = analogRead(potPin);
  // Map the sensor value to the servo position (0-180 degrees)
  int newPosition = map(sensorValue, 0, 1023, 0, 180); // Assumes a 10-bit ADC (1024 levels)
  return newPosition;
}
