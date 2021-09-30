#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "sensorUmidadeSolo.h"

int port = 80;
ESP8266WebServer server(port);

void handleNotFounded() {
    server.send(404, "application/json", "Not found");
};

void sensors() {
    float humidity = getPercentHumidity();
    String data = "{\"humidity\":" + String(humidity) + "}";
    server.send(200, "application/json", data);
}

void webServerInit() {
    server.on("/sensors", HTTP_GET, sensors);
    server.onNotFound(handleNotFounded);
    server.begin();
    String ipLocal = WiFi.localIP().toString();
    Serial.println("HTTP server started at " + ipLocal + ":" + String(port));
}

void handleClient () {
    server.handleClient();
}


