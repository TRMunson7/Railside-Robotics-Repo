#include <Servo.h>

#define SERVO_PIN 9 // signal pin for the ESC.
#define SERVO_PIN2 10 // signal pin for the ESC.
#define INPUT_PIN A0 // analog input pin.
#define INPUT_PIN2 A1 // analog input pin.
#define ENABLE_PIN 8 // wire this to 5V to enable(safety precaution)
#define MACRO_PIN 2 // wire this to 5V to enable(safety precaution)
#define HIGH_ESC_SIGNAL 1900
#define LOW_ESC_SIGNAL 1100

Servo ESC;
Servo ESC2;
bool macro_sig = 0;

void setup() {
  Serial.begin(9600);
  ESC.attach(SERVO_PIN,LOW_ESC_SIGNAL,HIGH_ESC_SIGNAL);
  ESC.attach(SERVO_PIN2,LOW_ESC_SIGNAL,HIGH_ESC_SIGNAL);
  pinMode(MACRO_PIN, INPUT_PULLUP);
  attachInterrupt(MACRO_PIN - 2, macro, RISING);
  ESC.writeMicroseconds(LOW_ESC_SIGNAL); // send low signal and wait 
}

void loop() {

  int potVal = analogRead(INPUT_PIN); // read from the input (I used a potentiometer, y'all will use a reciever).
  
  int pwmVal = map(potVal, 0, 1023, 1100, 1900); // map input values to PWM value.
  
  int potVal2 = analogRead(INPUT_PIN2); // read from the input (I used a potentiometer, y'all will use a reciever).
  
  int pwmVal2 = map(potVal2, 0, 1023, 1100, 1900); // map input values to PWM value.

  // Notes on the Map func:
  // The first input is the value to be mapped, the potentiometer reading
  // Next is the its lowest value, 0.
  // Then is the its highest value, 1023 = (2^10)-1, because analog read is 10 bits.
  // Then what the lowest value should be mapped to, 1100 microseconds because most esc can read from 1 to 2 milliseconds and it is best not to be to close to the edges.
  // Last what the highest value should be mapped to,  1900 microseconds, increasing this will NOT make it go faster the ESC automaticly sets the highest valueread to be max speed.
  
  // If you want a nonlinear map function feel free to make one

  bool enable = digitalRead(ENABLE_PIN);

  if(enable){
    if(macro_sig){
      macro_sig = 0;
      Serial.println("\n\n-----------------------MACRO-----------------------");
        // for(int angle = 0; angle < 180; )
        Serial.print("\n180H: ");
        ESC.write(180);
        delay(1000);

        Serial.print("\n90: ");
        ESC.write(135);
        delay(1000);

        Serial.print("\n0: ");
        ESC.write(90);
        delay(1000);
    }else{
      ESC.writeMicroseconds(pwmVal);
      ESC2.writeMicroseconds(pwmVal2);
      Serial.print(potVal, DEC); //Print the input value as a decimal number on a new line
      Serial.print(", "); //Print the input value as a decimal number on a new line
      Serial.println(potVal2, DEC); //Print the input value as a decimal number on a new line
    }
  } else {
    ESC.writeMicroseconds(LOW_ESC_SIGNAL); // Send signal to ESC.    
    Serial.println("off");
  }
}

void macro() {
  macro_sig = 1;
}
