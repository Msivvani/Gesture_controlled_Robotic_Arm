#include <Servo.h>    
#include <SPI.h>      
#include "RF24.h"     

Servo myServo1;
Servo myServo3;
Servo myServo4;
Servo myServo2;
Servo myServo5;


RF24 radio(9,10);  

const uint64_t pipe = 0xE8E8F0F0E1LL; 

int msg[5];

void setup(){

  Serial.begin(9600);
  myServo1.attach(8); 
  myServo2.attach(3); 
  myServo3.attach(4); 
  myServo4.attach(5); 
  myServo5.attach(6); 
  Serial.print("s");
  radio.begin();                    
  radio.openReadingPipe(1, pipe);   
  radio.startListening();
   
             
  }


void loop(){

    if ( radio.available() )
  {
    Serial.print("done");
    bool done = false;
    while (!done)
    { 
     radio.read(msg, sizeof(msg));
     done=true;
 
    myServo1.write(msg[4]); 
    myServo2.write(msg[3]); 
    myServo3.write(msg[2]); 
    myServo4.write(msg[1]); 
    myServo5.write(msg[0]); 
    Serial.print("servo1:");
    Serial.println(msg[4]);
    Serial.println(msg[0]);
    delay(3000);
    
    }

  }
}
