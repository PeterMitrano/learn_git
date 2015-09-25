/********************************************************
 * Travis Norris
 * RBE 2001
 * Prelab 4
/***************************************************/
#include <Servo.h>
const int motorPin = 9;
const int potPin = A10;
const int point1 = 512;
const int point2 = 512;
Servo motor;
int input=0;
int output=0;
int error=0;
int lastInput = 0;
int integral = 0;
int derivative = 0;
double kP = 0.07;
double kI = 0;
double kD = 0;
int delayTime= 100;
int startTime = 0;

void setup()
{
  motor.attach(motorPin);
  startTime= millis();
  Serial.begin(9600);
  delay(1000);
}
void loop()
{
  if (millis() < startTime + delayTime)
  {
    pid(point1);
  }
  else
  {
    pid(point2);
  }
  if (millis() > startTime + delayTime*2)
  {
    startTime = millis();
  }


}

void pid(int goal)
{
  input = analogRead(potPin);
  error = goal - input;
  Serial.print("Error = ");
  Serial.println( error);
  integral = integral + error;
  derivative = input - lastInput;
  output = kP * error + kI * integral + kD * derivative + 90;
  if (output>150)
  {
    motor.write(150);
  }
  else if (output < 30)
  {
    motor.write (30);
  }
  else
  {
    motor.write(output);
  }
  lastInput = input;


}


