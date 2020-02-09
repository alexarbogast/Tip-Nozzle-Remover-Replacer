#include "DCmotor.h"

DCmotor::DCmotor(uint8_t motorPin, uint8_t dirPin)
{ 
    this->m_motorPin = motorPin;
    this->m_dirPin = dirPin;
    this->m_speed = 0;

    pinMode(this->m_motorPin, OUTPUT);
    pinMode(this->m_dirPin, OUTPUT);
} 

void DCmotor::write(uint8_t speed, bool dir)
{
    digitalWrite(this->m_dirPin, dir);
    analogWrite(this->m_motorPin, speed);

    this->m_speed = speed;
}

// Write motor with acceleration until speed is reached
// CAUTION: Can't read other signals until full speed is reached
void DCmotor::write(uint8_t speed, bool dir, uint8_t accel)
{
    while(this->m_speed < speed)
    {
        this->m_speed += accel;
        this->write(this->m_speed, dir);
        delay(2); // write aditional acceleration percentage per ms         
    }
}

void DCmotor::stop()
{
    analogWrite(this->m_motorPin, 0);
    this->m_speed = 0;
}
