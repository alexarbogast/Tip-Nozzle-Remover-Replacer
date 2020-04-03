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

    long currentPosition = this->m_enc->read();
    Serial.println("Current Position:");
    Serial.println(currentPosition);
    
    // normalize encoder position between 0 and 180 deg
    if (currentPosition < 0)
    {
        currentPosition = (6534 + (currentPosition % 6534))%3267;
    }
    else
    {
        currentPosition = currentPosition % 3267;
    }
    //this->m_enc->write(currentPosition);
    Serial.println("Normalized:");
    Serial.println(currentPosition);

    // find fastest path to 0 or 180 deg
    if (currentPosition == 0)
    {
        return;
    }
    else if (currentPosition <= 1634)
    {  
        while(this->m_enc->read()%3267 !=0)
        {
            write(35, CW);
        }
    }
    else if (currentPosition > 1634)
    {
        while(this->m_enc->read()%3267 !=0)
        {    
            write(35, CCW);
        }
    }  
    stop();

    // probably delete this
    delay(20);
    if(this->m_enc->read()%3267 != 0)
    {
        home();
    }
    
    Serial.println(this->m_enc->read()%3267);
}

void DCmotor::stop()
{    
    analogWrite(this->m_motorPin, 0);
    this->m_speed = 0;
}
