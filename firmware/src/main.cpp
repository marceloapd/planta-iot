#include <Arduino.h>
#include "managerWifi.h"
#include "webServerAPI.h"
#include "managerTwitter.h"
#include "sensorUmidadeSolo.h"
#include "abstracts.h"
#include <TimerEvent.h>

const unsigned int timeToSend = hour(6);
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
    delay(1000);
    if ((warning == 0) && (humidity < 10  ||  humidity > 90)) {
        warning = 1;
        Serial.println("\ndangerous humidity values, sending alert...");
        String tweet = getGPT("gpt-3.5-turbo", "Primeira coisa que você precisa entender e que o texto gerado nao pode passar de 210 caracteres. Imagine que você é uma planta comediante e deseja enviar uma mensagem (no maximo 210 caracteres) de socorro para @marceloapda, seu criador. No entanto, a sua umidade do solo está em" + String(humidity) + "%, o que afeta diretamente o seu humor. Crie um tweet com no maximo 210 caracteres em português que mencione de forma clara a sua condição de umidade, sem revelar que você é uma planta. Compartilhe uma mensagem engraçada pedindo socorro @marceloapda dizendo que algo esta acontecendo de errado, seja criativa. Deixe o humor da mensagem compatível com a umidade do solo Lembre-se de dar sugestões para @marceloapda para reverter a situação da condições do seu solo, evite dizer que você e uma comediante. Não se esqueça: 210 caracteres!");
        sendTweet(tweet);
    }
}

void loop() {
    warn();
    cronWarning.update();
    cronSendData.update();
    managerWiFiCheckButton();
    handleClient();
}
