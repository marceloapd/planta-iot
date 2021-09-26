#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <websocket.h>


const char* ssid     = "SAFIRA";
const char* password = "6wp853rp";
String sensors[1] = {"temperature"};
int sensorData[1] = {0};

void wifiConnect() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(9600);
  wifiConnect(); // wifi setup
  webSocketSetup(); // websocket setup
}

void loop() {
  websocketSendData();
}

