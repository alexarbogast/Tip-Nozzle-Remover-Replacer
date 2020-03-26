#include "stepper.h"

stepper::stepper(uint8_t motor_pin, uint8_t dir_pin, uint8_t ena_pin)
{
    this->m_motor_pin = motor_pin;
    this->m_dir_pin = dir_pin;
    this->m_ena_pin = ena_pin;

    pinMode(this->m_motor_pin, OUTPUT);
    pinMode(this->m_dir_pin, OUTPUT);
    pinMode(this->m_ena_pin, OUTPUT);

    disable();
}

void stepper::step(int steps) // if steps + CW, - CCW
{
    if (steps > 0)
    {
        digitalWrite(this->m_dir_pin, HIGH);
    }
    else if (steps < 0)
    {
        digitalWrite(this->m_dir_pin, LOW);
    }
    for (int i = 0; i < abs(steps); i++)
    {
        singleStep();
    }
}

void stepper::stepAngle(float deg)
{
    float steps = deg*PPR/360;
    step(steps);
}

void stepper::singleStep()
{
    digitalWrite(this->m_motor_pin, HIGH);
    delayMicroseconds(PULSE_WIDTH); // pulse width
    digitalWrite(this->m_motor_pin, LOW);
    delay(PERIOD); // period in milliseconds
}

void stepper::enable()
{
    digitalWrite(this->m_ena_pin, LOW);
}

void stepper::disable()
{
    digitalWrite(this->m_ena_pin, HIGH);
}
