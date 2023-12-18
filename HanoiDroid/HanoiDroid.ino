#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmr = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwml = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  150
#define SERVOMAX  600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwmr.begin();
  pwml.begin();
  pwmr.setOscillatorFrequency(27000000);
  pwml.setPWMFreq(SERVO_FREQ);
  pwmr.setOscillatorFrequency(27000000);
  pwml.setPWMFreq(SERVO_FREQ);

  delay(10);
}

uint16_t calculatePulse(int angle) {
  double pulselength;
  pulselength = 1000000;
  pulselength /= 60;
  pulselength /= 4096;
  double pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pulse *= 1000;
  pulse /= pulselength;
  return (uint16_t)pulse;
}

void loop() {
  if (Serial.available()) {
    char servoSelection = Serial.read();
    int newPosition;

    Serial.println("Enter position for Servo (0-180):");
    while (!Serial.available());
    newPosition = Serial.parseInt();

    if (newPosition >= 0 && newPosition <= 180) {
      uint16_t pulse = calculatePulse(newPosition);
      switch (servoSelection) {
        case '0':
          pwmr.setPWM(0, 0, pulse);
          break;
        case '1':
          pwmr.setPWM(1, 0, pulse);
          break;
        case '2':
          pwmr.setPWM(2, 0, pulse);
          break;
        case '3':
          pwmr.setPWM(3, 0, pulse);
          break;
        case '4':
          pwmr.setPWM(4, 0, pulse);
          break;
        case '5':
          pwmr.setPWM(5, 0, pulse);
          break;
        case '6':
          pwmr.setPWM(6, 0, pulse);
          break;
        case '7':
          pwmr.setPWM(7, 0, pulse);
          break;
        case '8':
          pwmr.setPWM(8, 0, pulse);
          break;
        case '9':
          pwmr.setPWM(9, 0, pulse);
          break;
        case 'A':
        case 'a':
          pwmr.setPWM(10, 0, pulse);
          break;
        case 'B':
        case 'b':
          pwmr.setPWM(11, 0, pulse);
          break;
        case 'C':
        case 'c':
          pwmr.setPWM(12, 0, pulse);
          break;
        case 'D':
        case 'd':
          pwmr.setPWM(13, 0, pulse);
          break;
        case 'E':
        case 'e':
          pwmr.setPWM(14, 0, pulse);
          break;
        case 'F':
        case 'f':
          pwmr.setPWM(15, 0, pulse);
          break;
        case 'G':
        case 'g':
          pwml.setPWM(0, 0, pulse);
          break;
        case 'H':
        case 'h':
          pwml.setPWM(1, 0, pulse);
          break;
        case 'J':
        case 'j':
          pwml.setPWM(2, 0, pulse);
          break;
        case 'K':
        case 'k':
          pwml.setPWM(3, 0, pulse);
          break;
        case 'L':
        case 'l':
          pwml.setPWM(4, 0, pulse);
          break;
        case 'M':
        case 'm':
          pwml.setPWM(5, 0, pulse);
          break;
        case 'N':
        case 'n':
          pwml.setPWM(6, 0, pulse);
          break;
        case 'O':
        case 'o':
          pwml.setPWM(7, 0, pulse);
          break;
        case 'P':
        case 'p':
          pwml.setPWM(8, 0, pulse);
          break;
        case 'Q':
        case 'q':
          pwml.setPWM(9, 0, pulse);
          break;
        case 'R':
        case 'r':
          pwml.setPWM(10, 0, pulse);
          break;
        case 'S':
        case 's':
          pwml.setPWM(11, 0, pulse);
          break;
        case 'T':
        case 't':
          pwml.setPWM(12, 0, pulse);
          break;
        case 'U':
        case 'u':
          pwml.setPWM(13, 0, pulse);
          break;
        case 'W':
        case 'w':
          pwml.setPWM(14, 0, pulse);
          break;
        case 'X':
        case 'x':
          pwml.setPWM(15, 0, pulse);
          break;
      }

    }
    else {
      Serial.println("Invalid position. Please enter a value between 0 and 180.");
    }
  }
}
