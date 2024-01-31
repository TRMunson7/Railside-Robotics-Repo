#include <RGBLed.h>

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN, RGBLed::COMMON_ANODE);

void setup() {
}

void loop() {
  led.crossFade(RGBLed::RED, RGBLed::MAGENTA, 64, 800);
  delay(100);
  led.crossFade(RGBLed::MAGENTA, RGBLed::BLUE, 64, 800);
  delay(100);
  led.crossFade(RGBLed::BLUE, RGBLed::CYAN, 64, 800);
  delay(100);
  led.crossFade(RGBLed::CYAN, RGBLed::GREEN, 64, 800);
  delay(100);
  led.crossFade(RGBLed::GREEN, RGBLed::YELLOW, 64, 800);
  delay(100);
  led.crossFade(RGBLed::YELLOW, RGBLed::RED, 64, 800);
  delay(100);
}
