#include "Servo.h"

#define MOTOR 5
#define ENCODER_A 2

#define readA bitRead(PIND, 2) // faster than digitalRead()

volatile int count = 0;

Servo motor;


void setup() 
{
    // Set pullup resistor 
    pinMode(ENCODER_A, INPUT_PULLUP);

    motor.attach(MOTOR);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), isrA, RISING);

    // begin Serial
    Serial.begin(9600);
}

void loop() 
{
  while(count < 1600)
  {
        motor.writeMicroseconds(2000);
  }

  motor.writeMicroseconds(1500);
}

void isrA()
{
    count++;
}
