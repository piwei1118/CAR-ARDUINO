/*
  for arm moving
*/

#include "Arduino.h"
#include <Servo.h>

class ARM : public Servo
{
  private:
    unsigned long smt, duration;//unsigned long 時間需要以較大的值
    int angle_read = 90, target = 90, output;
    int max ,min;

  public:
    ARM();//p = pin, m = mx ,mm = min
    ~ARM();
    int link(byte p, int mx,int mm);
    int run(int t);//t = target
};