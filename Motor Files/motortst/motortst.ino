#include <Servo.h>
#include <Servo.h>
Servo ESC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("NO FORMAT");
  Serial.print(1);
  ESC.attach(9, 1000, 2000);
  ESC.write(2000);
  delay(5000);
  ESC.write(1000);
  delay(3000);
  pinMode(8, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool x = digitalRead(8);
  Serial.print(x);
  Serial.println();
  /*if (x) {
    ESC.write(1500);
    digitalWrite(LED_BUILTIN, 1);
  }else{
    ESC.write(1050);
     digitalWrite(LED_BUILTIN, 0);
  } */
}