#include <RGBLed.h>

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN, RGBLed::COMMON_ANODE);

void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:
  led.brightness(255, 0, 0, 100);
  delay(600);
  led.crossFade(255, 0, 0, 0, 0, 0, 64, 800);
  delay(100);
  led.crossFade(0, 0, 0, 255, 0, 0, 64, 100);
  delay(600);
  led.crossFade(255, 0, 0, 0, 0, 0, 64, 800);
  delay(100);
  led.crossFade(0, 0, 0, 255, 0, 0, 64, 100);
  delay(600);
  led.crossFade(255, 0, 0, 0, 0, 0, 64, 800);
  delay(100);
  led.crossFade(0, 0, 0, 0, 255, 0, 64, 100);
  delay(600);
  led.crossFade(0, 255, 0, 255, 255, 255, 64, 1000);
  delay(5000);
}
