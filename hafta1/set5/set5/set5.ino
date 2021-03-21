#include <Servo.h>

#define servo 3

Servo servo1;


void degree(int num, int state){
  //0 ileri
  if(!state){
  	servo1.write(num);
  	delay(500);
    return;
  }
  else{
  	servo1.write(360 - abs(num - 30));
  	delay(500);
    return;
  }
}

void setup() {
  servo1.attach(servo); 
}

void loop() {
  for(int i=0 ; i<=180 ; i+=15){
  degree(i,0);
  degree(i,1);
  }
}