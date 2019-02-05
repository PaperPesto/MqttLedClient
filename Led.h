#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led{
  private:
  int Gpio;
  
  public:
  Led(int gpio);
  void On();
  void Off();
  void Pwm(int value);
};

#endif
