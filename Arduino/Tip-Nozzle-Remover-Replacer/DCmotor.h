/* Class for control of DCmotor
 * using the DFROBOT 2x15A motor controller 
 * https://www.dfrobot.com/product-796.html?search=2x15A&description=true
 * 
 * Version 1.0 - initial release
 */

#ifndef DCMOTOR_H
#define DCMOTOR_H

#if ARDUINO >= 100
#include "Arduino.h"
#else 
#include "WProgram.h"
#endif

// convenience macros
#define CW 1 // Motor direction seen from top
#define CCW 0

class DCmotor
{
public:
   DCmotor(uint8_t motorPin, uint8_t dirPin);
   void write(uint8_t speed, bool dir);
   void write(uint8_t speed, bool dir, uint8_t accel);
   inline uint8_t readSpeed() { return this->m_speed;  }
   void stop();
private: 
   uint8_t m_motorPin;
   uint8_t m_dirPin;
   uint8_t m_speed;
};

#endif //DCMOTOR_H
