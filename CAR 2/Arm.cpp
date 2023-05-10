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

  target = map(t , 0, 30, min, max);//targat angle 
  angle_read = read();  //把馬達細劃成20個
 //如果測試的時候馬達也無法到達0 或 20
  duration = millis() - smt;

  while(duration < 200){
    output = map(duration, 0, 200, angle_read, target);
    write(output);
    duration = millis() - smt;
  }  
}