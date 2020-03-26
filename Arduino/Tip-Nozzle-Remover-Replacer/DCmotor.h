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

#include "Encoder.h"

// convenience macros
#define CW 1 // Motor direction seen from top
#define CCW 0

class DCmotor
{
public:
   DCmotor(uint8_t motorPin, uint8_t dirPin);
   DCmotor(uint8_t motorPin, uint8_t dirPin, Encoder* enc);
   void write(uint8_t speed, bool dir);
   void setHome();
   void home();
   void stop();

   inline uint8_t readSpeed() { return this->m_speed; }
private: 
   uint8_t m_motorPin;
   uint8_t m_dirPin;
   uint8_t m_speed;

   bool m_direction;
   Encoder* m_enc;
};

#endif //DCMOTOR_H
