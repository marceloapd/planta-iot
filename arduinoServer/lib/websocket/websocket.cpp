#include <WebSocketsServer.h>
#include <Neotimer.h>

WebSocketsServer webSocket = WebSocketsServer(81);
Neotimer mytimer = Neotimer(2000); // intervalo de envio da msg em sec


// websocket handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    Serial.println("webSocketEvent");
}

// send sensor data to client
void websocketSendData (String data) {
    webSocket.loop();
    
    if (mytimer.repeat()) {
        webSocket.sendTXT(0, "teste");
    }
}

// websocket setup
void webSocketSetup () {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}