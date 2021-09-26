#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <EEPROM.h>

#define flashButton D3
WiFiManager wm;

void managerWiFiCheckButton(){
    if (digitalRead(flashButton) == LOW){
        ESP.eraseConfig();
        ESP.restart();
    }
}
void managerWiFiInit(){
    WiFi.mode(WIFI_STA);
    bool res;
    res = wm.autoConnect("Planta-IoT"); 
    if(!res) {
        Serial.println("Failed to connect");
    }
    else {   
        Serial.println("Successfully connected");
    }
}