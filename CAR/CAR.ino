#include <PS2X_lib.h>
//public 像是ev3程式的綠色方塊馬達
//public通常是可以開放大家使用的
//C語言有public與private之分
//private是作者本人測試 或是public程式會使用的"原始程式"
//private 像是ev3程式的藍色方塊馬達
PS2X ps2x; 
int error;

#include <Servo.h>
  Servo num_1;
  Servo num_2;
  Servo num_3;
  Servo num_4;
  Servo num_5;
  Servo num_6;
void setup(){
//46-53
  for (int x = 46 ; x < 54 ; x = x + 1){
 
  pinMode( x , OUTPUT); 
  }
  Serial.begin(57600);
  do { 
    //GamePad(clock, command, attention, data,)
    error = ps2x.config_gamepad(14, 16, 15, 17,true,true);   //這行要和接線對應正確
    if (error == 0) { Serial.print("Gamepad found!");break; } 
    else { delay(100); } 
  } while (1);

  num_1.attach(8);
  num_2.attach(9);
  num_3.attach(10);
  num_4.attach(11);
  num_5.attach(12);
  num_6.attach(13);
}
void forward(){

  for(int i = 46; i < 54 ; i+=2){  // i = i = 1 or i++ or i+=1
  digitalWrite (i, HIGH);
  digitalWrite (i+1, LOW);

  }
}
void backward(){

  for(int i = 46; i < 54 ; i+=2){
  digitalWrite (i, LOW);
  digitalWrite (i+1, HIGH);
  }
}
void right(){
 
  int j = 1;
  for(int i = 46; i < 54 ; i+=2){

  if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11 % 3 = 2
  digitalWrite (i, HIGH);
  digitalWrite (i+1, LOW);  
}

  else{
  digitalWrite (i, LOW);
  digitalWrite (i+1, HIGH);  
}
  j++;

  }
}
void left(){
 
  int j = 1;
  for(int i = 46; i < 54 ; i+=2){

  if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11%3 = 2
  digitalWrite (i+1, HIGH);
  digitalWrite (i, LOW);  
}

  else{
  digitalWrite (i+1, LOW);
  digitalWrite (i, HIGH);  
}
  j++;

  }
}
void stop(){
 
  int j = 1;
  for(int i = 46; i < 54 ; i+=2){

  if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11%3 = 2
  digitalWrite (i, LOW);
  digitalWrite (i+1, LOW);  
}
  }
}
void loop() {

    ps2x.read_gamepad();  //讀取手把狀態
    delay(10);
    
   int now_ly = num_5.read();
   Serial.println(now_ly);

   
   
    int raw_rx = ps2x.Analog(PSS_RX) /2.5 ;// MAP 攝氏華氏
    //Serial.print(raw_rx);
    //Serial.print("   ");
     int rx = map(raw_rx , 0, 100, 170, 10); 
     //num_6.write(rx);

    int raw_ly = ps2x.Analog(PSS_LY) /2.5 ; 
    //Serial.println(raw_ly);
      int ly = map(raw_ly , 0, 100, 25, 125); 
      //num_5.write(ly);
      
    for(int test_ly = 125; test_ly >=25 ; test_ly -= 10){
      num_5.write(test_ly);
      delay(5);      
    }
    for(int test_ly = 25; test_ly <= 125 ; test_ly += 10){
      num_5.write(test_ly);
      delay(5);
    }
 
   if(ps2x.Button(PSB_PAD_UP)){
     forward();
   }
   else if(ps2x.Button(PSB_PAD_RIGHT)){
     right();
  }
   else if(ps2x.Button(PSB_PAD_LEFT)){
     left();
  }
   else if(ps2x.Button(PSB_PAD_DOWN)){
     backward();
  }
   else if(ps2x.Button(PSB_R1)){
     turn_right();
   }
   else if(ps2x.Button(PSB_L1)){
     turn_left();
   }
   else { 
     stop();
   }
}
void turn_right(){

   int j = 1;
   for(int i = 46; i < 54 ; i+=2){

      if (j <= 2){
        digitalWrite(i,LOW);
        digitalWrite(i+1,HIGH);      
      }
      else{
        digitalWrite(i,HIGH);
        digitalWrite(i+1,LOW);
    }
    j++;
  }
}
void turn_left(){
   int j = 1;
   for(int i = 46; i < 54 ; i+=2){

    if (j <= 2){
        digitalWrite(i,HIGH);
        digitalWrite(i+1,LOW);      
      }
    else{
      digitalWrite(i,LOW);
      digitalWrite(i+1,HIGH);
      }
      j++;
  }
}