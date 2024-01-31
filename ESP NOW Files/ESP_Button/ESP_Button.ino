#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1;

esp_now_peer_info_t slave;

bool blue = 0;
bool red = 0;

bool en = 1;
bool wait = 0;
bool started = 0;

uint8_t data = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_send_cb(onDataSent);
  setUpSlave();
  esp_now_add_peer(&slave);

  pinMode(34, INPUT_PULLDOWN);
  pinMode(27, INPUT_PULLDOWN);
  pinMode(35, INPUT_PULLDOWN);

  // attachInterrupt(digitalPinToInterrupt(34), blueReady, RISING);
  // attachInterrupt(digitalPinToInterrupt(27), redReady, RISING);
  // attachInterrupt(digitalPinToInterrupt(35), tapout, RISING);
}

void loop() {
  if(red && blue && en && !started){
    data = 0;
    delay(1000);
    esp_now_send(slave.peer_addr, &data, sizeof(data));
    started = 1;
    red = 0;
    blue = 0;
  } else if(digitalRead(35) && en){
    en = 0;
    blueReady();
  } else if(digitalRead(34) && en){
    en = 0;
    redReady();
  } else if(!(digitalRead(34)||digitalRead(35))){
    en = wait;
    wait = !wait; 
  }
}

void blueReady(){
  data = started? 3:1;
  esp_now_send(slave.peer_addr, &data, sizeof(data));
  blue = started?0:1;
  started = 0;
}

void redReady(){
  data = started? 4:2;
  esp_now_send(slave.peer_addr, &data, sizeof(data));
  red = started?0:1;;
  started = 0;
}

// run this every time data is sent, like an interupt
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("I sent my data -> ");
  Serial.println(data);
  if(data == 0) {
    Serial.println("Start Count Down");
  } else if(data == 1) {
    Serial.println("Blue");
  } else if(data == 2) {
    Serial.println("Red");
  } else if(data == 3) {
    Serial.println("Blue Tapout");
  } else if(data == 4) {
    Serial.println("Red Tapout");
  } else {
    Serial.println("WHat is THis");
  }
}

// set the slave's info, it is just easier to do this manually
void setUpSlave() {
  uint8_t macAddress[6] = {0x08, 0xD1, 0xF9, 0x29, 0xD6, 0x14}; // replace this with the slave address 
  memcpy(slave.peer_addr, macAddress, 6); // update the mac address for the slave
  slave.channel = CHANNEL; // pick a channel
  slave.encrypt = 0; // no encryption
}
