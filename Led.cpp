#include "Arduino.h"
#include "Led.h"

Led::Led(int gpio){
  Gpio = gpio;
  pinMode(Gpio, OUTPUT);  
}

void Led::On(){
  digitalWrite(Gpio, HIGH);
}

void Led::Off(){
  digitalWrite(Gpio, LOW);
}

void Led::Pwm(int value){
  analogWrite(Gpio, value);
}
