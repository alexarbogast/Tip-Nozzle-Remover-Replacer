/*
 * TIP+NOZZLE REMOVER+REPLACER 
 * Alex Arbogast
 * February 8, 2019
 */
#include "DCMotor.h"
#include "Encoder.h"

#define MOTOR_PIN 9
#define DIR_PIN 8
#define LIMIT_SWITCH 52

#define ENCODER_A 2
#define ENCODER_B 3

char receivedChar;

// Initialize motors and enocder
DCmotor motor(MOTOR_PIN, DIR_PIN);
Encoder encoder(ENCODER_A, ENCODER_B);

void removeNozzle();
void removeTip();
void replaceTip();
void replaceNozzle();

void setup() 
{
    Serial.begin(9600);
    while(!Serial)
    {
        // wait for serial coneection to establish
    }  

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

// --- FUNCTIONS ---
void removeNozzle()
{
    motor.write(127, CW, 1);
}

void removeTip()
{       
    //motor.writeMicroseconds(1625);

    // move motor until tip is dumped
    while (digitalRead(LIMIT_SWITCH) != 0)
    { 
        // continue motor }
    }

    // move motor until dispense location is reached
    //encoder.write(0);     // reset encoder
    //motor.writeMicroseconds(1400); 
    while (encoder.read() < 1100)
    { 
        // continue motor }
    }

    // stop for tip dispense
    //motor.writeMicroseconds(1500);
}

void replaceTip() 
{
    motor.stop();
}

void replaceNozzle()
{
    motor.write(127, CCW, 1);
}
