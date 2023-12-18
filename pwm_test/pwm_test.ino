#include <Adafruit_PWMServoDriver.h> // Libreria Para el manejo de motores SERVO

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // Llamado al método pwm de la librería de la PCA9685*
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41); // Llamado al método pwm de la librería de la PCA9685*

#define SERVO0  140
#define SERVO90  370
#define SERVO180  600

// definición de variables
int num = 0;

//Se configuran los métodos
void setup()
{
  Serial.begin(9600);
  pwm.begin(); // configurar los metodos del pwm
  pwm1.begin();
  pwm.setPWMFreq(60); // configurar la frecuencia del pwn
  pwm1.setPWMFreq(60); // configurar la frecuencia del pwn
}

// Configurar los pasos de los servos (La linealidad)
void setServoPulse(uint8_t n, double pulse)
{
  double pulselength;
  pulselength = 1000000;
  pulselength /= 60;
  pulselength /= 4096;
  pulse *= 1000;
  pulse /= pulselength;
  pwm.setPWM(n, 0, pulse);
}

void loop()
{
  while (Serial.available() > 0)
  {
    int pos = Serial.parseInt();

    switch (pos) // Los if anidados tienen problemas de consecución
    {
      //Cuando en el caso x se cumple la declaración, salir del bucle.
      case 0:
        pwm.setPWM(8, 0, SERVO0);
        pwm1.setPWM(0, 0, SERVO0);
        break;
      case 1:
        pwm.setPWM(8, 0, SERVO180);
        pwm1.setPWM(0, 0, SERVO0);
        break;
      case 2:
        pwm.setPWM(8, 100, SERVO90);
        pwm1.setPWM(0, 0, SERVO0);
        break;
      case 3:
        pwm.setPWM(1, 0, SERVO180);
        break;
      case 4:
        pwm.setPWM(1, 100, SERVO0);
        break;
      case 5:
        pwm.setPWM(2, 0, SERVO180);
        break;
      case 6:
        pwm.setPWM(2, 100, SERVO0);
        break;
      case 7:
        pwm.setPWM(3, 0, SERVO180);
        break;
      case 8:
        pwm.setPWM(3, 100, SERVO0);
        break;
      case 9:
        pwm.setPWM(4, 0, SERVO180);
        break;
      case 10:
        pwm.setPWM(4, 100, SERVO0);
        break;
    }
  }
}
