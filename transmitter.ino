#include <SPI.h>                      
#include "RF24.h"                     

int msg[5]; 

int flex_5 = A4;
int flex_4 = A3;
int flex_3 = A2;
int flex_2 = A1;
int flex_1 = A0;

int flex_5_val;
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;
int servo_5;
int servo_4;
int servo_3;
int servo_2;
int servo_1;

RF24 radio(9,10);                     
const uint64_t pipe = 0xE8E8F0F0E1LL; 


void setup(void){
  Serial.begin(9600);
  radio.begin();           
  radio.openWritingPipe(pipe);        
}

void loop(void){
 
  
  flex_5_val = analogRead(flex_5); 
  servo_5=map(flex_5_val,970,1023,180,0);
  servo_5=constrain(servo_5,0,180);

  flex_4_val = analogRead(flex_4);
  servo_4=map(flex_4_val,970,1023,180,0);
  servo_4=constrain(servo_4,0,180);

 
  flex_3_val = analogRead(flex_3);
  servo_3=map(flex_3_val,970,1023,180,0);
  servo_3=constrain(servo_3,0,180);

  
 flex_2_val = analogRead(flex_2);
  servo_2=map(flex_2_val,970,1023,180,0);
  servo_2=constrain(servo_2,0,180);
  
  
  flex_1_val = analogRead(flex_1);
  servo_1=map(flex_1_val,970,1023,180,0);
  servo_1=constrain(servo_1,0,180);
  Serial.print("sensor1:");
  Serial.print(flex_1_val);
  Serial.print("servo1:");
  Serial.println(servo_1);
  delay(1000);
  
  msg[0] = servo_5;
  msg[1] = servo_4;
  msg[2] = servo_3;
  msg[3] = servo_2;
  msg[4] = servo_1;
  radio.write(msg, sizeof(msg));
  Serial.println(msg[4]);
  
}
