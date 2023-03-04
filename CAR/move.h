 /*
 for ilon wheel moving
 */

 #ifndef _MOVE_H__
 #define _MOVE_H__
 //匯入arduino核心標頭檔案
 #include "Arduino.h"

 class MOVE
 {
    private://隱藏的
      byte pin; //start pin 48

    public://公開的

     MOVE(byte p);//LED = 建構函式  
     ~MOVE();     //~LED = 解構函式
     
     void forward();
     void backward();
     void right();
     void left();
     void turn_right();
     void turn_left();
     void stop();

     void disattach();           //釋放引腳與led的繫結 
 };
#endif