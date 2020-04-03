/*
 * Stepper motor class for use with TB6600 driver
 * Alex Arbogast
 * March 26, 2020
 */

#ifndef STEPPER_H
#define STEPPER_H

#if ARDUINO >= 100
#include "Arduino.h"
#else 
#include "WProgram.h"
#endif

#define PPR 800

class stepper
{
    private:
    uint8_t m_motor_pin;
    uint8_t m_dir_pin;
    uint8_t m_ena_pin;

    const float m_max_period = 1500; // us
    const float m_min_period = 1200; // us
    const float m_period_accel = 0.5; // us/step
    
    float m_period;

    public:
        stepper(uint8_t motor_pin, uint8_t dir_pin, uint8_t ena_pin);
        
        void step(int steps);
        void stepAngle(float deg);

        void reset();
        void enable();
        void disable();

    private:
        void singleStep();
        void updatePeriod();
};
#endif //STEPPER_H
