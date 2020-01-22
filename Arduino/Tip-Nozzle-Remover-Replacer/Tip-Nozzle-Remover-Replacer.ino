/*
 * TIP+NOZZLE REMOVER+REPLACER 
 * Alex Arbogast
 * January 21, 2019
 */
#include "Servo.h"

#define MOTOR_PIN 9
#define LIMIT_SWITCH 52

char receivedChar;
Servo motor;

void removeNozzle() 
{
    motor.writeMicroseconds(2000);

    while (digitalRead(LIMIT_SWITCH) != 0)
    {
        // continue motor
    }

    motor.writeMicroseconds(1500);
        
}

void removeTip(){}
void replaceTip() { }
void replaceNozzle() { }

void setup() 
{
    Serial.begin(9600);
    while(!Serial)
    {
        // wait for serial coneection to establish
    }  

    motor.attach(MOTOR_PIN);
    pinMode(LIMIT_SWITCH, INPUT_PULLUP);
}

void loop() 
{
    if (Serial.available() > 0)
    {
        receivedChar = Serial.read();

        switch (receivedChar)
        {
            case 'a':
                removeNozzle();
                break;
            case 'b':
                removeTip();
                break;
            case 'c':
                replaceTip();
                break;
            case 'd':
                replaceNozzle();
                break;
            default:
                // do nothing
                break;
        }
    }
}
