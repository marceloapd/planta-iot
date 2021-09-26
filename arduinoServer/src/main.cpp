#include <Arduino.h>
#include <websocket.h>
#include "sensorUmidadeSolo.h"


const char* ssid     = "SAFIRA";
const char* password = "6wp853rp";

void setup() {
  Serial.begin(9600);
  webSocketSetup(); // websocket setup
}

void loop() {
  Serial.println(fazLeituraUmidade());
  websocketSendData();
}
