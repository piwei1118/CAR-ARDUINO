/*
  for ilon wheel moving 
*/
 #include "move.h"
 #include "Arduino.h"

MOVE::MOVE(byte p){
  pin = p;
  for (int x = pin ; x < pin + 8 ; x = x + 1){
    pinMode( x , OUTPUT);  
  }
}
MOVE::~MOVE(){
  disattach();
}

void MOVE::forward(){

  for(int i = pin; i < pin+8 ; i+=2){  // i = i = 1 or i++ or i+=1
    digitalWrite (i, HIGH);
    digitalWrite (i+1, LOW);
  }
}
void MOVE::backward(){

  for(int i = pin; i < pin+8 ; i+=2){
    digitalWrite (i, LOW);
    digitalWrite (i+1, HIGH);
  }
}
void MOVE::right(){
 
  int j = 1;
  for(int i = pin; i < pin+8 ; i+=2){

    if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11 % 3 = 2
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
void MOVE::left(){
 
  int j = 1;
  for(int i = pin; i < pin+8 ; i+=2){

    if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11%3 = 2
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
void MOVE::stop(){
 
  int j = 1;
  for(int i = pin; i < pin+8 ; i+=2){

  if(j % 2 == 1 ){  //模數除法% 用法:11除以3於2: 11%3 = 2
  digitalWrite (i, LOW);
  digitalWrite (i+1, LOW);  
    }
  }
}
void MOVE::turn_right(){
   int j = 1;
   for(int i = pin; i < pin+8 ; i+=2){

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
void MOVE::turn_left(){
   int j = 1;
   for(int i = pin; i < pin+8 ; i+=2){

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
void MOVE::disattach(){
    for (int x = pin ; x < pin + 8 ; x = x + 1){
      digitalWrite(x , LOW);
      pinMode( x , INPUT);  
  }
}