#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>

//communication channel
#define CHANNEL 1

#define MATCH_TIME 120000

//led vairables
#define NUM_LEDS 4
#define UP_TIME 300
#define WAIT_TIME 600
#define DOWN_TIME 100

CRGB leds[NUM_LEDS];

int TICK = 0;
int TIME_END = -1000;

int lt = 23;
int rt = 21;
int rb = 14;
int b = 12;
int lb = 32; 
int t = 22;
int m = 27;
int DIGITS[3] = {19,18,5};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
  
  FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);

  pinMode(t, OUTPUT);
  pinMode(lt, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(rt, OUTPUT);
  pinMode(m, OUTPUT);
  pinMode(DIGITS[0], OUTPUT);
  pinMode(DIGITS[1], OUTPUT);
  pinMode(DIGITS[2], OUTPUT);
  pinMode(13, OUTPUT);
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  Serial.print("I just got -> ");
  Serial.println(*data);
  
  TICK = 0;
  if (*data == 0) {
    countDown();
    TICK = 1;
    TIME_END = millis() + MATCH_TIME;
  } else if(*data == 2) {
    int R[3] = {255,0,0};
    PatternFlash(R);
  } else if(*data == 1) {
    int B[3] = {0,0,255};
    PatternFlash(B);
  } else if(*data == 3) {
    int R[3] = {255,0,0};
    PatternFlash(R);
    TIME_END = 0;
  } else if(*data == 4) {
    int B[3] = {0,0,255};
    PatternFlash(B);
    TIME_END = 0;
  } else {
    TIME_END = 0;
    for(int i = 0; i < NUM_LEDS; i+=1){
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
  }
  SSD_Time(0,0,0);
}

void loop() {
  int time = (int) (TIME_END-millis())/1000;
  if(time >= 0){
    int min = time/60;
    int dec = time/10 - min*6;
    int sec = time - min*60 - dec*10;
    SSD_Time(min,dec,sec);
    if(time==0){
      for(int i = 0; i < NUM_LEDS; i+=1){
        leds[i] = CRGB(0,0,0);  
      }
      FastLED.show();
    }
  }
}

void SSD_Time(int min, int dec, int sec){
  digitalWrite(DIGITS[0], 0);
  digitalWrite(DIGITS[1], 1);
  digitalWrite(DIGITS[2], 1);
  SSD(min, min);
  delay(6);
  digitalWrite(DIGITS[0], 1);
  digitalWrite(DIGITS[1], 0);
  digitalWrite(DIGITS[2], 1);
  SSD(dec,dec|min);
  delay(7);
  digitalWrite(DIGITS[0], 1);
  digitalWrite(DIGITS[1], 1);
  digitalWrite(DIGITS[2], 0);
  SSD(sec,sec|dec|min);
  delay(7);
}

void SSD(int num, int en) {
  digitalWrite(t, num != 1 && num != 4 && en);                            // 0,2,3,5,6,7,8,9    not4,1,
  digitalWrite(lt, num != 1 && num != 2 && num != 3 && num != 7 && en);   // 0,4,5,6,8,9        not1,2,3,7
  digitalWrite(lb, (num == 0 || num == 2 || num == 6 || num == 8) && en); // 0,2,6,8      
  digitalWrite(b, num != 1 && num != 4 && num != 7 && en);                // 0,2,3,5,6,8,9,     not 1,4,7
  digitalWrite(rb, num != 2 && en);                                       // 0,1,3,4,5,6,7,8,9  not2
  digitalWrite(rt, num != 5 && num != 6 && en);                           // 0,1,2,3,4,7,8,9    not 5,6
  digitalWrite(m, num != 0 && num != 1 && num != 7 && en);                // 2,3,4,5,6,8,9      not 0,1,7
}

void PatternFlash(int color[]) {
  //Start black
  for(int i = 0; i < NUM_LEDS; i+=1){
    leds[i] = CRGB(0,0,0);  
  }
  FastLED.show();

  //do a semi random pattern 5 times
  for(int count = 0; count < 3; count+=1){
    for(int j = 0; j < 3; j+=1){
      for(int i = 0; i < NUM_LEDS; i+=1){
        //Might want to change the pattern
        leds[i] = CRGB(color[0] *((i + j) % 3), color[1] *((i + j) % 3), color[2] *((i + j) % 3));  
      }
    FastLED.show();
    delay(111);
    }
  }

  //End black
  for(int i = 0; i < NUM_LEDS; i+=1){
    leds[i] = CRGB(0,0,0);  
  }
  FastLED.show();
}

void countDown() {
  //Start Black
  for(int i = 0; i < NUM_LEDS; i+=1){
    leds[i] = CRGB(0,0,0);  
  }
  
  FastLED.show();   
  delay(3000);
  digitalWrite(DIGITS[0], 1);
  digitalWrite(DIGITS[1], 1);
  digitalWrite(DIGITS[2], 0);
  //3 count red fade up and down
  for(int count = 0; count < 3; count+=1){
    SSD(3-count,1);
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
  SSD(0,1);
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
}
