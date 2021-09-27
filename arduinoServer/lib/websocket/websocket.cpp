#include <WebSocketsServer.h>
#include <Neotimer.h>
#include <ESP8266WiFi.h>
#include <sensorUmidadeSolo.h>


const int PORT = 81;
WebSocketsServer webSocket = WebSocketsServer(PORT);
Neotimer mytimer = Neotimer(2000); // intervalo de envio da msg em sec


// websocket handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    Serial.println("webSocketEvent");
}

// send sensor data to client
void websocketSendData () {
    float humidity = getPercentHumidity();
    String data = "";
    data.concat(humidity);
    // Serial.println(data);
    delay(5);
    webSocket.loop();
    if (mytimer.repeat()) {
        webSocket.sendTXT(0, data);
    }
}

// websocket setup
void webSocketInit () {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    String messageServer = "WebSocket server started at ws://";
    messageServer += WiFi.localIP().toString();
    messageServer += ":" + String(PORT);
    Serial.println(messageServer);
}