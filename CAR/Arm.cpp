/*
  for arm moving
*/

#include "Arm.h"
#include "Arduino.h"

#include <Servo.h>

ARM::ARM(byte p, int mx,int mm){
  attach(p);
  max = mx;
  min = mm;
}
ARM::~ARM(){
  detach();
}

ARM::run(int t){
  smt = millis();

  target = map(t , 0, 10, min, max);//targat angle
  read = read();

  while(duration < 500){
    output = map(duration, 0, 500, read, target);
    write(output);
    
    duration = millis() - smt;
  }  
}