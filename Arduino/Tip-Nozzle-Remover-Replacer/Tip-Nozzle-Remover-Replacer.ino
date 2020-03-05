/*
 * TIP+NOZZLE REMOVER+REPLACER 
 * Alex Arbogast
 * February 8, 2019
 */
#include "DCMotor.h"
#include "Encoder.h"

#define MOTOR_PIN 9
#define DIR_PIN 8
#define LIMIT_SWITCH 53

#define ENCODER_A 2
#define ENCODER_B 3

#define SOLENOID 40

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
    
    pinMode(SOLENOID, OUTPUT);
    digitalWrite(SOLENOID, HIGH); // high retracts 
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
                dispenseTip();
                break;
            case 'e':
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
    motor.write(200, CW, 1);
}

void removeTip()
{       
    // CW for removing tip
    motor.write(55, CW);

    // move motor until tip is dumped
    while (digitalRead(LIMIT_SWITCH) != 0)
    { 
        // continue motor }
    }

    // move motor until dispense location is reached
    motor.stop();
    encoder.write(0);     // reset encoder
    motor.write(70, CCW); 
    while (encoder.read() < 600)
    { 
        // continue motor }
    }

    // stop for tip dispense
    motor.stop();
}

void replaceTip() 
{
    motor.stop();
}

void dispenseTip()
{
    digitalWrite(SOLENOID, LOW);
    delay(1000);

    motor.write(50, CCW);

    delay(500);
    motor.stop();

    digitalWrite(SOLENOID, HIGH);
    
}

void replaceNozzle()
{
    motor.stop();
    motor.write(200, CCW);
 
}
