const int ledPin = LED_BUILTIN;  // the number of the LED pin

int ledState = LOW;  // ledState used to set the LED

unsigned long previousMillis = 0;  // will store last time LED was updated

int onInterval = 0;  // interval at which to be on (milliseconds)
int offInterval = 10;  // interval at which to be off (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

int count = 0;
int up = 1;

void loop() {
  
  unsigned long currentMillis = millis();

  // if the LED is off turn it on and vice-versa:
  if ((ledState == LOW) && (currentMillis - previousMillis >= offInterval)) {
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    previousMillis = currentMillis;
    count += 1;
  } else if ((ledState == HIGH) && (currentMillis - previousMillis >= onInterval)) {
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    previousMillis = currentMillis;
  }

  if(count == 9){
    count = 0;
    if((offInterval>0 && up)||(onInterval <= 0)){
      onInterval  += 1;
      offInterval -= 1;
      up = 1;
    } else {
      up = 0;
      onInterval  -= 1;
      offInterval += 1;
    } 
  }
}
