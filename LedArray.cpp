#include "Arduino.h"
#include "LedArray.h"
#include "Led.h"


LedArray::LedArray(){}

LedArray::LedArray(int led0, int led1, int led2, int led3, int led4){

  
  Led0 = new Led(led0);
  Led1 = new Led(led1);
  Led2 = new Led(led2);
  Led3 = new Led(led3);
  Led4 = new Led(led4);

  Led0->Off();
  Led1->Off();
  Led2->Off();
  Led3->Off();
  Led4->Off();
}

void LedArray::On(){
  Led0->On();
  Led1->On();
  Led2->On();
  Led3->On();
  Led4->On();
}

void LedArray::Off(){
  Led0->Off();
  Led1->Off();
  Led2->Off();
  Led3->Off();
  Led4->Off();
}

void LedArray::Pwm(int pwm0, int pwm1, int pwm2, int pwm3, int pwm4){
  Led0->Pwm(pwm0);
  Led1->Pwm(pwm1);
  Led2->Pwm(pwm2);
  Led3->Pwm(pwm3);
  Led4->Pwm(pwm4);
}
