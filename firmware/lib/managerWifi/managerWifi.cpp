#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <EEPROM.h>
#include "sensorUmidadeSolo.h"
#include "webServerAPI.h"
#define flashButton D3
WiFiManager wm;
char consumerKey[200];
char consumerSecret[200];
char accessTokenKey[200];
char accessTokenSecret[200];
char phraseType[200];
char twitterUser[200];
boolean buttonActive = false;
boolean longPressActive = false;
long buttonTimer = 0;
long longPressTime = 250;
WiFiManagerParameter consumerKeyParam("consumerKey", "consumerKey", consumerKey, 200);
WiFiManagerParameter consumerSecretParam("consumerSecret", "consumerSecret", consumerSecret, 200);
WiFiManagerParameter accessTokenKeyParam("accessTokenKey", "accessTokenKey", accessTokenKey, 200);
WiFiManagerParameter accessTokenSecretParam("accessTokenSecret", "accessTokenSecret", accessTokenSecret, 200);
WiFiManagerParameter phraseTypeParam("phraseType", "phraseType", phraseType, 200);
WiFiManagerParameter twitterUserParam("twitterUser", "twitterUser", twitterUser, 200);
WiFiManagerParameter custom_text("<br/>Preencha os campos abaixo<br/>");


void managerWiFiCheckButton(){
    if (digitalRead(flashButton) == LOW){
        printDatas();
        delay(180);
		if (buttonActive == false) {

			buttonActive = true;
			buttonTimer = millis();

		}

    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
        longPressActive = true;
		}
    }else {
        if (buttonActive == true) {
            if (longPressActive == true) {
                longPressActive = false;
                ESP.eraseConfig();
                ESP.restart();
            }
            buttonActive = false;
        }
    }
}

String getParams(){
    String ipMac = WiFi.macAddress();
    float humidity = getPercentHumidity();
    return "{\"consumerKey\": \"" + String(consumerKeyParam.getValue()) + "\",\"consumerSecret\": \"" + String(consumerSecretParam.getValue()) + "\",\"accessTokenKey\": \"" + String(accessTokenKeyParam.getValue()) + "\",\"accessTokenSecret\": \"" + String(accessTokenSecretParam.getValue()) + "\",\"phraseType\": \"" + String(phraseTypeParam.getValue()) + "\",\"twitterUser\": \"" + String(twitterUserParam.getValue()) +"\",\"humidity\":" + humidity +",\"MAC\": \"" + String(ipMac) + "\"}";
}

void managerWiFiInit(){ 
    wm.addParameter(&custom_text);
    wm.addParameter(&consumerKeyParam);
    wm.addParameter(&consumerSecretParam);
    wm.addParameter(&accessTokenKeyParam);
    wm.addParameter(&accessTokenSecretParam);
    wm.addParameter(&phraseTypeParam);
    wm.addParameter(&twitterUserParam);
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
