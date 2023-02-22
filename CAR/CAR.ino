#include <PS2X_lib.h>
//public 像是ev3程式的綠色方塊馬達
//public通常是可以開放大家使用的
//C語言有public與private之分
//private是作者本人測試 或是public程式會使用的"原始程式"
//private 像是ev3程式的藍色方塊馬達
//millis 
PS2X ps2x; 
int error;

//smt_rx = start movinig time rx, and so on
int old_raw_rx = 5;
unsigned long smt_rx , duration_rx;//f
int read_rx=90, rx=90;

#include "MOVE.h"
 MOVE move(46);
#include <Servo.h>

#include "Arm.h"
ARM arm_1(8 , 90 ,90);
ARM arm_2(9 , 90 ,90);
ARM arm_3(10, 90 ,90);
ARM arm_4(11, 90 ,90);
ARM arm_5(12, 25, 125);
ARM arm_6(13, 10, 170);


void setup(){
//46-53  
  Serial.begin(57600);
  Serial.println("Start");
  for (int x = 46 ; x < 54 ; x = x + 1){

  pinMode( x , OUTPUT); 
  }
  do { 
    //GamePad(clock, command, attention, data,)
    error = ps2x.config_gamepad(14, 16, 15, 17,true,true);   //這行要和接線對應正確
    if (error == 0) { Serial.print("Gamepad found!");break; } 
    else { delay(100); Serial.print("..");} 
  } while (1);

  

}
void loop() {

    ps2x.read_gamepad();  //讀取手把狀態
    delay(10);
    
     int raw_rx = ps2x.Analog(PSS_RX) /25;// MAP 攝氏華氏
 
    if (old_raw_rx != raw_rx){ //raw_rx蘑菇頭數值
     arm_6.run(raw_rx);
     old_raw_rx = raw_rx;
    }
 
   if(ps2x.Button(PSB_PAD_UP)){
     move.forward();
   }
   else if(ps2x.Button(PSB_PAD_RIGHT)){
     move.right();
  }
   else if(ps2x.Button(PSB_PAD_LEFT)){
     move.left();
  }
   else if(ps2x.Button(PSB_PAD_DOWN)){
     move.backward();
  }
   else if(ps2x.Button(PSB_R1)){
     move.turn_right();
   }
   else if(ps2x.Button(PSB_L1)){
     move.turn_left();
   }
   else { 
     move.stop();
   }
  
}
