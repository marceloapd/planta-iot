#include <Arduino.h>
#include "websocket.h"
#include "managerWifi.h"
#include "webServerAPI.h"

void setup() {
    Serial.begin(9600);
    managerWiFiInit();
    webSocketInit();
    webServerInit();
}

void loop() {
    managerWiFiCheckButton();
    websocketSendData();
    handleClient();
}
