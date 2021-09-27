#include <Arduino.h>
#include <websocket.h>
#include "managerWifi.h"


void setup() {
    Serial.begin(9600);
    managerWiFiInit();
    webSocketInit();
}

void loop() {
    managerWiFiCheckButton();
    websocketSendData();
}
