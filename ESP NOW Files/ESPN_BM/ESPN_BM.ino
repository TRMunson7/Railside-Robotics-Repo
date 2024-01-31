#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1;

esp_now_peer_info_t slave;

uint8_t data = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_send_cb(onDataSent);
  setUpSlave();
  esp_now_add_peer(&slave);
}

void loop() {
  esp_now_send(slave.peer_addr, &data, sizeof(data));
  delay(3000);
  data+=1;
}

// run this every time data is sent, like an interupt
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("I sent my data -> ");
  Serial.println(data);
}

// set the slave's info, it is just easier to do this manually
void setUpSlave() {
  uint8_t macAddress[6] = {0x08, 0xD1, 0xF9, 0x29, 0xD6, 0x14}; // replace this with the slave address 
  memcpy(slave.peer_addr, macAddress, 6); // update the mac address for the slave
  slave.channel = CHANNEL; // pick a channel
  slave.encrypt = 0; // no encryption
}
