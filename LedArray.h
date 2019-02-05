#ifndef LedArray_h
#define LedArray_h

#include "Arduino.h"
#include "Led.h"

class LedArray{

  
  private:
  Led* Led0;
  Led* Led1;
  Led* Led2;
  Led* Led3;
  Led* Led4;

  public:
  LedArray();
  LedArray(int led0, int led1, int led2, int led3, int led4);
  void On();
  void Off();
  void Pwm(int pwm0, int pwm1, int pwm2, int pwm3, int pwm4);
};

#endif
