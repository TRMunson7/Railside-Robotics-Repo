#include "WiFi.h"

void setup(){
  Serial.begin(115200);              //set serial rate to max
  WiFi.mode(WIFI_MODE_STA);          //set wifi mode, STA or station mode can connect to networks like normal, AP or Acess Point can be connected to by other things
  Serial.println(WiFi.macAddress()); //print mac Address you need it for something
}
// Mac for Com7/left  A0:A3:B3:2D:B9:FC
// Mac for Com6/right 08:D1:F9:29:D6:14
void loop() {
  // put your main code here, to run repeatedly:

}
