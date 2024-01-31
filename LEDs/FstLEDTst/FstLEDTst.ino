#include <FastLED.h>
#define NUM_LEDS 4
#define D 50
CRGB leds[NUM_LEDS];
void setup() { 
  
  FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
}
void loop() {
  int i = 0;
  leds[0] = CRGB (25,25,25);  
  leds[1] = CRGB (0,0,0);  
  leds[2] = CRGB (0,0,0);  
  leds[3] = CRGB (0,0,0);  
  FastLED.show(); 
  delay(D);

  for(; i <= NUM_LEDS; i+=1){
    leds[i-1] = CRGB (0,0,0);  
    leds[i] = CRGB (25,25,25);  
    leds[i+1] = CRGB (10,10,10);  
    FastLED.show(); 
    delay(D);
  }
}