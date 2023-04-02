#include <Arduino.h>
#include "managerWifi.h"
#include "webServerAPI.h"
#include "managerTwitter.h"
#include "sensorUmidadeSolo.h"
#include "abstracts.h"
#include <TimerEvent.h>

const unsigned int timeToSend = hour(1);
const unsigned int timeToUpdate = min(30);

TimerEvent cronSendData;
TimerEvent cronWarning;
boolean warning = 0;

void setWarning(){
    warning = 0;
}

void setup() {
    cronSendData.set(timeToSend, sendData);
    cronWarning.set(timeToUpdate, setWarning);
    Serial.begin(9600);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    managerWiFiInit();
    webServerInit();
}

void warn(){
    float humidity = getPercentHumidity();
    delay(10);
    if ((warning == 0) && (humidity < 10  ||  humidity > 90)) {
        warning = 1;
        Serial.println("\ndangerous humidity values, sending alert...");
        String data = getParams();
        int statusCode = postReq("http://ptsv2.com/t/g5483-1665875753/post", data);
        Serial.print("status code: ");
        Serial.println(statusCode);
    }
}

void loop() {
    warn();
    cronWarning.update();
    cronSendData.update();
    managerWiFiCheckButton();
    handleClient();
}
