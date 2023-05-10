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
/*
舊的
int old_raw_rx = 9;
int old_raw_ly = 9;
int old_raw_ry = 9;
int old_raw_lx = 9;
*/


#include "MOVE.h"
#include <Servo.h>
#include "Arm.h"


ARM arm_1;
ARM arm_2;
ARM arm_3;
ARM arm_4;
ARM arm_5;
ARM arm_6;

//define 定義 不同於變數他是不可變的 [常數]
//#define check_count 3;
static int check_count = 2;
//static 靜態 變數
int ps2check[10] = {0,0,0,0,0,0,0,0,0,0};
//up , down , left , right , R1 , L1 , RX , RY , LY , LX 
int psslast[4] = {9,9,9,9};
//上一次的紀錄
bool psblast[6] = {0, 0, 0, 0, 0, 0};

MOVE move(46);

int arm_angle[7] = {0, 15, 15, 15, 15, 15, 15};
int arm_old[7] = {0, 15, 15, 15, 15, 15, 15};

void setup(){
 arm_6.link(8, 0, 180);
 arm_5.link(9, 0, 150);
 arm_4.link(10, 0 ,180);
 arm_3.link(11, 10 ,160);
 arm_2.link(12 , 0 ,180);
 arm_1.link(13, 0 ,180);
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

   //check 歸零
   if(ps2x.Button(PSB_PAD_UP) != psblast[0]) ps2check[0] = 0;
   if(ps2x.Button(PSB_PAD_DOWN) != psblast[1]) ps2check[1] = 0;
   if(ps2x.Button(PSB_PAD_LEFT) != psblast[2]) ps2check[2] = 0;
   if(ps2x.Button(PSB_PAD_RIGHT) != psblast[3]) ps2check[3] = 0;
   if(ps2x.Button(PSB_L1) != psblast[4]) ps2check[4] = 0;
   if(ps2x.Button(PSB_R1) != psblast[5]) ps2check[5] = 0;

  if (ps2x.Button(PSB_R3)){
    arm_angle[5] = 3;
    arm_5.run(arm_angle[5]);
    delay(100);
    arm_angle[6] = 15;
    arm_6.run(arm_angle[6]);
    arm_angle[5] = 15;
    arm_5.run(arm_angle[5]);
    while(!(ps2x.ButtonReleased(PSB_R3))){
      ps2x.read_gamepad();
    } 
  }


  int ry = ps2x.Analog(PSS_RY) - 128 ;
  arm_angle[5] += (ry > 20) ? (((ry - 20)/30)+1 ) : ((ry < -20) ? (((ry + 20)/30)-1 ): 0);
  
  if(arm_angle[5] > 30 || arm_angle[5] < 0){
    arm_angle[5] = (arm_angle[5] > 15)? (30) : (0);
  }

  if(arm_old[5] != arm_angle[5]){
    arm_5.run(arm_angle[5]);
    arm_old[5] = arm_angle[5];
  }

  
  int rx = ps2x.Analog(PSS_RX) - 128 ;
    arm_angle[6] += (rx > 20) ? (((rx - 20)/30)+1 ) : ((rx < -20) ? (((rx + 20)/30)-1 ): 0);
  
  if(arm_angle[6] > 30 || arm_angle[5] < 0){
    arm_angle[6] = (arm_angle[6] > 15)? (30) : (0);
  }

  if(arm_old[6] != arm_angle[6]){
    arm_6.run(arm_angle[6]);
    arm_old[6] = arm_angle[6];
  }




/*條件運算符 
結構: (條件) ?成立時的指令 : 不成立的指令
多重條件結構 : (ask1) ? true1 : (ask2)?true :false
*/


/*
     int raw_rx = ps2x.Analog(PSS_RX) /13;// MAP 攝氏華氏
     int raw_ly= ps2x.Analog(PSS_LY) /13;
     int raw_ry = ps2x.Analog(PSS_RY) /13;
     int raw_lx = (ps2x.Analog(PSS_LX) /13) +1;

   if(raw_lx != psslast[0]) ps2check[6] = 0;
   if(raw_ly != psslast[1]) ps2check[7] = 0;
   if(raw_rx != psslast[2]) ps2check[8] = 0;
   if(raw_ry != psslast[3]) ps2check[9] = 0;
    
    if ((old_raw_ly != raw_ly) && (ps2check[7] > check_count)){ //raw_ly蘑菇頭數值
     arm_3.run(raw_ly);
     old_raw_ly = raw_ly;
    }
    if ((old_raw_lx != raw_lx) && (ps2check[6] > check_count)){ //raw_lx蘑菇頭數值
     arm_2.run(raw_lx);
     old_raw_lx = raw_lx;
    }
    if ((old_raw_ry != raw_ry) && (ps2check[9] > check_count)){ //raw_ry蘑菇頭數值
     arm_5.run(raw_ry);
     old_raw_ry = raw_ry;
    }
    
    if ((old_raw_rx != raw_rx) && (ps2check[8] > check_count)){ //raw_rx蘑菇頭數值
     arm_6.run(raw_rx);
     old_raw_rx = raw_rx;
    }
    //check先確定有沒有被按過 所以需要放在前後 分別是check歸零 check累計 
*/
   
     if(ps2x.Button(PSB_PAD_UP) && ps2check[0] > check_count){
     move.forward(); } 
     else if(ps2x.Button(PSB_PAD_DOWN)&& ps2check[1] > check_count){
     move.backward(); }

     else if(ps2x.Button(PSB_PAD_LEFT)&& ps2check[2] > check_count){
     move.left(); }
     
     else if(ps2x.Button(PSB_PAD_RIGHT)&& ps2check[3] > check_count){
     move.right(); }

   else if(ps2x.Button(PSB_L1)&& ps2check[4] > check_count){
     move.turn_left(); }
   
   else if(ps2x.Button(PSB_R1)&& ps2check[5] > check_count){
     move.turn_right();
   }
   else { 
     move.stop();
   }

  //check累加
   if(ps2x.Button(PSB_PAD_UP) == psblast[0]) ps2check[0] ++;
   if(ps2x.Button(PSB_PAD_DOWN) == psblast[1]) ps2check[1] ++;
   if(ps2x.Button(PSB_PAD_LEFT) == psblast[2]) ps2check[2] ++;
   if(ps2x.Button(PSB_PAD_RIGHT) == psblast[3]) ps2check[3] ++;
   if(ps2x.Button(PSB_L1) == psblast[4]) ps2check[4] ++;
   if(ps2x.Button(PSB_R1) == psblast[5]) ps2check[5] ++;
/*
   if(raw_lx == psslast[0]) ps2check[6] ++;
   if(raw_ly == psslast[1]) ps2check[7] ++;
   if(raw_rx == psslast[2]) ps2check[8] ++;
   if(raw_ry == psslast[3]) ps2check[9] ++;
*/ 

   psblast[0] = ps2x.Button(PSB_PAD_UP);
   psblast[1] = ps2x.Button(PSB_PAD_DOWN);
   psblast[2] = ps2x.Button(PSB_PAD_LEFT);
   psblast[3] = ps2x.Button(PSB_PAD_RIGHT);
   psblast[4] = ps2x.Button(PSB_L1);
   psblast[5] = ps2x.Button(PSB_R1);
/*
   psslast[0] = raw_lx ;
   psslast[1] = raw_ly ;
   psslast[2] = raw_rx ;
   psslast[3] = raw_ry ;
*/
}

