#include "DCmotor.h"

DCmotor::DCmotor(uint8_t motorPin, uint8_t dirPin)
{ 
    this->m_motorPin = motorPin;
    this->m_dirPin = dirPin;
    this->m_speed = 0;
    this->m_enc = nullptr;

    pinMode(this->m_motorPin, OUTPUT);
    pinMode(this->m_dirPin, OUTPUT);
} 

DCmotor::DCmotor(uint8_t motorPin, uint8_t dirPin, Encoder* enc)
{
    this->m_motorPin = motorPin;
    this->m_dirPin = dirPin;
    this->m_speed = 0;
    this->m_enc = enc;

    pinMode(this->m_motorPin, OUTPUT);
    pinMode(this->m_dirPin, OUTPUT);
}

void DCmotor::write(uint8_t speed, bool dir)
{
    digitalWrite(this->m_dirPin, dir);
    analogWrite(this->m_motorPin, speed);

    this->m_speed = speed;
    this->m_direction = dir;
}

void DCmotor::setHome()
{
    this->m_enc->write(0);
}

void DCmotor::home()
{
    // TODO: find fastest path to 0
    long currenPosition = this->m_enc->read();

    // while not at 0 or 180 deg continue...
    write(30, CW);
    while(this->m_enc->read()%3200 != 0)
    {      
    }
    stop();
}

void DCmotor::stop()
{    
    analogWrite(this->m_motorPin, 0);
    this->m_speed = 0;
}
