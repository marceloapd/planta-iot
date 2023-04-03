#include <ESP8266WebServer.h>

void webServerInit();
void handleClient ();
void sendData();
int postReq(String url, String data);
String getGPT(String model, String content);
void blinkLed();