#include <Servo.h>

#define SERVO_PIN 9 // signal pin for the ESC.
#define INPUT_PIN A0 // analog input pin.
#define ENABLE_PIN 8 // wire this to 5V to enable(safety precaution)
#define MACRO_PIN 7 // wire this to ground and then 5V to do a macro
#define HIGH_ESC_SIGNAL 1900
#define LOW_ESC_SIGNAL 1100

bool resetMacro = 0;
Servo ESC;

void setup() {
  Serial.begin(9600);
  ESC.attach(SERVO_PIN);
  // delay(1000);
  // ESC.writeMicroseconds(HIGH_ESC_SIGNAL); // send High signal and wait
  // delay(3000);
  ESC.writeMicroseconds(LOW_ESC_SIGNAL); // send low signal and wait
  delay(3000);
}

void loop() {

  int potVal = analogRead(INPUT_PIN); // read from the input (I used a potentiometer, y'all will use a reciever).
  
  Serial.println(potVal,DEC); //Print the input value as a decimal number on a new line

  int pwmVal = map(potVal,0, 1023, 1100, 1900); // map input values to PWM value.
  
  // Notes on the Map func:
  // The first input is the value to be mapped, the potentiometer reading
  // Next is the its lowest value, 0.
  // Then is the its highest value, 1023 = (2^10)-1, because analog read is 10 bits.
  // Then what the lowest value should be mapped to, 1100 microseconds because most esc can read from 1 to 2 milliseconds and it is best not to be to close to the edges.
  // Last what the highest value should be mapped to,  1900 microseconds, increasing this will NOT make it go faster the ESC automaticly sets the highest valueread to be max speed.
  
  // If you want a nonlinear map function feel free to make one

  bool enable = digitalRead(ENABLE_PIN);
  bool goMacro = digitalRead(MACRO_PIN);

  if(enable){
    if(goMacro & !resetMacro) {
      for(int i = 0; i<5; i+=1){
        ESC.writeMicroseconds(1900);
        delay(300);
        ESC.writeMicroseconds(1100);
        delay(300);
      }
      resetMacro = 1;
    } else{
      ESC.writeMicroseconds(pwmVal);
      resetMacro = goMacro;
    }
  } else {
    ESC.writeMicroseconds(LOW_ESC_SIGNAL); // Send signal to ESC.    
  }
  
}
