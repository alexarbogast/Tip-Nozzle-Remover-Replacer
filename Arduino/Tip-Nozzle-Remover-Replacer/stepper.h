#ifndef STEPPER_H
#define STEPPER_H

#define PULSE_WIDTH 500
#define PERIOD 2
#define PPR 200


class stepper
{
    private:
    int m_motor_pin;
    int m_dir_pin;
    
    public:
        stepper(int motor_pin, int dir_pin)
        {
            this->m_motor_pin = motor_pin;
            this->m_dir_pin = dir_pin;

            pinMode(this->m_motor_pin, OUTPUT);
            pinMode(this->m_dir_pin, OUTPUT);

        }
        
        void step(int steps) // if steps + CW, - CCW
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

        void stepAngle(float deg)
        {
            float steps = deg*PPR/360;
            step(steps);
        }
        
        void singleStep()
        {
            digitalWrite(this->m_motor_pin, HIGH);
            delayMicroseconds(PULSE_WIDTH); // pulse width
            digitalWrite(this->m_motor_pin, LOW);

            delay(PERIOD); // period in milliseconds
        }
};
#endif //STEPPER_H
