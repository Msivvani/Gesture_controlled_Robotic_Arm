#include <Servo.h>
char x;
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

void setup() {
  Serial.begin(9600);
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s4.attach(5);
  s5.attach(6);

}

void loop() {

  while (Serial.available() > 0) {
    Serial.print("entered");
    x = (Serial.read());
    Serial.println(x);
    Serial.println("exit");
  }
  switch (x) {
    case '1':
      s1.write(0);
      s2.write(180);
      s3.write(180);
      s4.write(180);
      s5.write(0);
      break;

    case '2':
      s1.write(0);
      s2.write(0);
      s3.write(180);
      s4.write(180);
      s5.write(0);
      break;

    case '3':
      s1.write(0);
      s2.write(0);
      s3.write(0);
      s4.write(180);
      s5.write(0);
      break;

    case '4':
      s1.write(0);
      s2.write(0);
      s3.write(0);
      s4.write(0);
      s5.write(0);
      break;

    case '5':
     s1.write(0);
      s2.write(0);
      s3.write(0);
      s4.write(0);
      s5.write(90);
      break;

    case '0':
      s1.write(180);
      s2.write(180);
      s3.write(180);
      s4.write(180);
      s5.write(45);
      break;

    default:
    s1.write(0);
      s2.write(0);
      s3.write(0);
      s4.write(0);
      s5.write(90);
      break;
    
       }

}
