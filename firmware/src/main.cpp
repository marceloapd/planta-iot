#include <Arduino.h>
#include "websocket.h"
#include "managerWifi.h"
#include "webServerAPI.h"

void setup() {
    Serial.begin(9600);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    managerWiFiInit();
    webServerInit();
    // webSocketInit();
}

void loop() {
    managerWiFiCheckButton();
    // websocketSendData();
    handleClient();
}
