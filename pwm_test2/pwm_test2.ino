#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmr = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwml = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  80
#define SERVOMAX  600
#define SERVO_FREQ 60

uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  pwmr.begin();
  pwmr.setOscillatorFrequency(27000000);
  pwmr.setPWMFreq(SERVO_FREQ);
  delay(10);
  Serial.println("Servo Test");

  // Set initial positions for each servo (0 to 180 degrees)
  int initialPositions[] = {90, 120, 80, 60, 110, 90, 75, 135}; // Example positions

  for (int servoPin = 0; servoPin < 8; servoPin++) {
    if (servoPin < sizeof(initialPositions) / sizeof(initialPositions[0])) {
      int degree = initialPositions[servoPin];
      uint16_t initialPulse = map(degree, 0, 180, SERVOMIN, SERVOMAX);
      pwmr.setPWM(servoPin, 0, initialPulse);
      pwml.setPWM(servoPin, 0, initialPulse);
    }
  }

}
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;
  pulselength /= SERVO_FREQ;
  pulselength /= 4096;
  pulse *= 1000;
  pulse /= pulselength;
  pwmr.setPWM(n, 0, pulse);
}

void startRobot() {
  // Implement your robot startup logic here
  robotStarted = true;
  // Add any necessary actions to start the robot
}

void loop() {
  while (Serial.available() > 0) {
    int servoPin = Serial.parseInt();
    if (servoPin >= 0 && servoPin < 8) {
      int degree = Serial.parseInt();
      if (degree >= 0 && degree <= 180) {
        uint16_t pulse = map(degree, 0, 180, SERVOMIN, SERVOMAX);
        switch (servoPin) {
          case 0:
            pwmr.setPWM(0, 0, pulse);
            break;
          case 1:
            pwmr.setPWM(1, 0, pulse);
            break;
          case 2:
            pwmr.setPWM(2, 0, pulse);
            break;
          case 3:
            pwmr.setPWM(3, 0, pulse);
            break;
          case 4:
            pwmr.setPWM(4, 0, pulse);
            break;
          case 5:
            pwmr.setPWM(5, 0, pulse);
            break;
          case 6:
            pwmr.setPWM(6, 0, pulse);
            break;
          case 7:
            pwmr.setPWM(7, 0, pulse);
            break;
          case 8:
            pwml.setPWM(0, 0, pulse);
            break;
          case 9:
            pwml.setPWM(1, 0, pulse);
            break;
          case 97:
            pwml.setPWM(2, 0, pulse);
            break;
          case 'b':
            pwml.setPWM(3, 0, pulse);
            break;
          case 'c':
            pwml.setPWM(4, 0, pulse);
            break;
          case 'd':
            pwml.setPWM(5, 0, pulse);
            break;
          case 'e':
            pwml.setPWM(6, 0, pulse);
            break;
          case 'f':
            pwml.setPWM(7, 0, pulse);
            break;
        }
      }
    }
  }
}
