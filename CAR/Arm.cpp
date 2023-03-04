/*
  for arm moving
*/

#include "Arm.h"
#include "Arduino.h"

#include <Servo.h>

ARM::ARM(){

}
ARM::~ARM(){
  detach();
}
ARM::link(byte p, int mm,int mx){
  if(mm>mx){
    attach(p,mx,mm);
  }
  else{
    attach(p,mm,mx);
  }
  max = mx;
  min = mm;
}
ARM::run(int t){
  smt = millis();

  target = map(t , 0, 10, min, max);//targat angle
  angle_read = read();
  
  duration = millis() - smt;

  while(duration < 500){
    output = map(duration, 0, 500, angle_read, target);
    write(output);
    duration = millis() - smt;
  }  
}