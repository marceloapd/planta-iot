#include <Arduino.h>
#include "managerWifi.h"
#include "webServerAPI.h"
#include "sensorUmidadeSolo.h"

void setup() {
    Serial.begin(9600);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    managerWiFiInit();
    webServerInit();
}

void loop() {
    managerWiFiCheckButton();
    handleClient();
}
