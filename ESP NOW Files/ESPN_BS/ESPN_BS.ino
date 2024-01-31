#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  Serial.print("I just got -> ");
  Serial.println(*data);
}

void loop() {
  // pull a giri, Chill
}
