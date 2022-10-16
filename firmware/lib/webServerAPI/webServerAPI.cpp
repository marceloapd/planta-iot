#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "sensorUmidadeSolo.h"
#include "managerWifi.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int port = 5000;
ESP8266WebServer server(port);
WiFiClient wifiClient;
HTTPClient http; 

void setHeaders() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Max-Age", "600");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
}

void handleNotFounded() {
    server.send(404, "application/json", "Not found");
};

void blinkLed() {
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
    digitalWrite(BUILTIN_LED, HIGH); 
}

void sensors() {
    setHeaders();
    String data = getParams();
    server.send(200, "application/json", data);
    blinkLed();
}

void setRoutes () {
    server.on("/sensors", HTTP_GET, sensors);
    server.onNotFound(handleNotFounded);
}

void webServerInit() {
    setRoutes();
    setHeaders();
    server.begin();
    String ipLocal = WiFi.localIP().toString();
    String ipMac = WiFi.macAddress();
    Serial.println("HTTP server started at " + ipLocal + ":" + String(port) + "\n\nMAC: " + ipMac );
}

int postReq(String url, String data) {
    http.begin(wifiClient, url);     
    http.addHeader("Content-Type", "application/json");  
    int httpCode = http.POST(data);
    http.end(); 
    blinkLed();
    return httpCode;
}

void sendData(){
    Serial.println("sending data to API");
    String data = getParams();
    int statusCode = postReq("http://ptsv2.com/t/g5483-1665875753/post", data);
    Serial.print("status code: ");
    Serial.println(statusCode);
}

void handleClient () {
    server.handleClient();
}