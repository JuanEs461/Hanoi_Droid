#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmr = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwml = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  80
#define SERVOMAX  650 
#define SERVO_FREQ 50

uint8_t servonum = 0;
//bool robotStarted = false;

void setup() {
  Serial.begin(9600);
  pwmr.begin();
  pwml.begin();
  pwmr.setOscillatorFrequency(27000000);
  pwml.setOscillatorFrequency(27000000);
  pwmr.setPWMFreq(SERVO_FREQ);
  pwml.setPWMFreq(SERVO_FREQ);
  delay(10);
  Serial.println("Servo Test");

  // Set initial positions for each servo (0 to 180 degrees)
  int initialPositionsr[] = {45, 45, 45, 45, 45, 45, 45, 45}; // Example positions

  for (int servoPinr = 0; servoPinr < 8; servoPinr++) {
    if (servoPinr < sizeof(initialPositionsr) / sizeof(initialPositionsr[0])) {
      int degreer = initialPositionsr[servoPinr];
      uint16_t initialPulser = map(degreer, 0, 180, SERVOMIN, SERVOMAX);
      pwmr.setPWM(servoPinr, 0, initialPulser);
    }
  }

  int initialPositionsl[] = {45, 45, 45, 45, 45, 45, 45, 45}; // Example positions

  for (int servoPinl = 0; servoPinl < 8; servoPinl++) {
    if (servoPinl < sizeof(initialPositionsl) / sizeof(initialPositionsl[0])) {
      int degreel = initialPositionsl[servoPinl];
      uint16_t initialPulsel = map(degreel, 0, 180, SERVOMIN, SERVOMAX);
      pwml.setPWM(servoPinl, 0, initialPulsel);
    }
  }

}
void setServoPulser(uint8_t nr, double pulser) {
  double pulselengthr;
  pulselengthr = 1000000;
  pulselengthr /= SERVO_FREQ;
  pulselengthr /= 4096;
  pulser *= 1000;
  pulser /= pulselengthr;
  pwmr.setPWM(nr, 0, pulser);
}

void setServoPulsel(uint8_t nl, double pulsel) {
  double pulselengthl;
  pulselengthl = 1000000;
  pulselengthl /= SERVO_FREQ;
  pulselengthl /= 4096;
  pulsel *= 1000;
  pulsel /= pulselengthl;
  pwml.setPWM(nl, 0, pulsel);
}


void loop() {
  while (Serial.available() > 0) {
    char servoPin = Serial.read();
    //if (!robotStarted && servoPin == 1) {
    // Check for the "start" command sent by the Python script
    //startRobot();
    //return;
    //}
    int degree = Serial.parseInt();
    if (degree >= 0 && degree <= 180) {
      uint16_t pulse = map(degree, 0, 180, SERVOMIN, SERVOMAX);
      switch (servoPin) {
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
          pwml.setPWM(0, 0, pulse);
          break;
        case '9':
          pwml.setPWM(1, 0, pulse);
          break;
        case 'a':
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
