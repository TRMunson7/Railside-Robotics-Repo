#include <FastLED.h>
#define NUM_LEDS 4
#define UP_TIME 700
#define WAIT_TIME 200
#define DOWN_TIME 100
CRGB leds[NUM_LEDS];
void setup() { 
  FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
}
void loop() {
  
  //Start Black
  for(int i = 0; i < NUM_LEDS; i+=1){
    leds[i] = CRGB(0,0,0);  
  }
  
  FastLED.show();   
  delay(5000);
  
  //3 count red fade up and down
  for(int count = 0; count < 3; count+=1){
    for(int j = 0; j<256; j+=1){
      for(int i = 0; i < NUM_LEDS; i+=1){
        leds[i] = CRGB(j,0,0);  
      }
    FastLED.show(); 
    delay(UP_TIME/256.0);
    }
    
    delay(WAIT_TIME);

    for(int j = 0; j<256; j+=1){
      for(int i = 0; i < NUM_LEDS; i+=1){
        leds[i] = CRGB(255-j,0,0);  
      }
    FastLED.show(); 
    delay(DOWN_TIME/256.0);
    }
  }

  //fade up green
  for(int j = 0; j<256; j+=1){
      for(int i = 0; i < NUM_LEDS; i+=1){
        leds[i] = CRGB(0,j,0);  
      }
    FastLED.show(); 
    delay(UP_TIME/256.0);
  }

  //fade green to white
  for(int j = 0; j<256; j+=1){
      for(int i = 0; i < NUM_LEDS; i+=1){
        leds[i] = CRGB(j,255,j);  
      }
    FastLED.show(); 
    delay(UP_TIME/256.0);
  }
  delay(5000);

}
