/*
 * TIP+NOZZLE REMOVER+REPLACER 
 * Alex Arbogast
 * March 14, 2019
 */
#define ENCODER_OPTIMIZE_INTERRUPTS
#include "DCmotor.h"
#include "stepper.h"

#include "pins.h"

char receivedChar;

// Initialize DC motors and enocder
DCmotor motor1(MOTOR1_PWM, MOTOR1_DIR);

Encoder encoder2(M2_ENC_A, M2_ENC_B);
DCmotor motor2(MOTOR2_PWM, MOTOR2_DIR, &encoder2);

DCmotor motor3(MOTOR3_PWM, MOTOR3_DIR);

// Initialize Stepper
stepper stpr(STPR_PWM, STPR_DIR, STPR_ENA);

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

    pinMode(LIMIT_SWITCH1, INPUT_PULLUP);
    pinMode(LIMIT_SWITCH2, INPUT_PULLUP);

    pinMode(IRBBS1, INPUT_PULLUP);
    pinMode(IRBBS2, INPUT_PULLUP);
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
            case 'z':
                test();
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
    while(digitalRead(IRBBS1)!= 0)
    {
        // wait for torch to come into position
    }

    delay(1500);
    motor1.write(230, CW);

    while(digitalRead(IRBBS1) != 1)
    {
        // wait for nozzle to fall
    }
    motor1.stop();

    // Delete THIS
    removeTip();
}

void removeTip()
{       
    while(digitalRead(IRBBS2) != 0)
    {
        // wait for torch to come into position
    }

    delay(1500);
    
    // CW for removing tip
    motor2.write(170, CW);
    delay(7000);
    motor2.stop();

    stpr.enable();
    stpr.reset();
    while(digitalRead(LIMIT_SWITCH1) != 0)
    {
        stpr.step(1);
    }

    stpr.reset();
    stpr.stepAngle(-100);   
    motor2.home();

    while(digitalRead(IRBBS2) != 0){  } // wait for tip dispense
    delay(2000); 

    stpr.reset();
    while(digitalRead(LIMIT_SWITCH2) != 0)
    {
        stpr.step(-1);
    }
    stpr.disable();

    replaceTip();
}

void replaceTip()
{
    delay(1000);
    motor2.write(170, CCW);
    delay(6000);
    motor2.stop();
    motor2.home();
}

void replaceNozzle()
{
    motor2.setHome();
}

void test()
{
    motor2.write(170, CW);
    delay(7000);
    motor2.stop();

    delay(1000);
    motor2.home();    
}
