#ifndef STEPPER_H
#define STEPPER_H

#if ARDUINO >= 100
#include "Arduino.h"
#else 
#include "WProgram.h"
#endif

#define PULSE_WIDTH 500
#define PERIOD 2
#define PPR 200


class stepper
{
    private:
    uint8_t m_motor_pin;
    uint8_t m_dir_pin;
    uint8_t m_ena_pin;
    
    public:
        stepper(uint8_t motor_pin, uint8_t dir_pin, uint8_t ena_pin);
        
        void step(int steps);
        void stepAngle(float deg);
        void singleStep();

        void enable();
        void disable();
};
#endif //STEPPER_H
