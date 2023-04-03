#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "sensorUmidadeSolo.h"
#include "managerWifi.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "managerTwitter.h"

int port = 5000;
ESP8266WebServer server(port);
WiFiClient wifiClient;
HTTPClient http; 
const char* openaiApiKey = "openaiApiKey";


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


  String getGPT(String model, String content) {
    WiFiClientSecure client;
    client.setInsecure();

    if (!client.connect("api.openai.com", 443)) {
      Serial.println("Connection failed");
    }

    // Crie a string JSON para enviar no corpo da solicitação
    String jsonString = String("{");
    jsonString += String("\"model\": \"") + model + "\",";
    jsonString += String("\"messages\": [{\"role\": \"user\",\"content\": \"" + content + "\"}]");
    jsonString += String("}");

    // Defina os cabeçalhos da solicitação HTTP
    String headers = String("POST /v1/chat/completions HTTP/1.1\r\n") +
                    String("Host: api.openai.com\r\n") +
                    String("Content-Type: application/json\r\n") +
                    String("Authorization: Bearer ") + openaiApiKey + "\r\n" +
                    String("Content-Length: ") + String(jsonString.length()) + "\r\n" +
                    String("\r\n");

    // Envie a solicitação HTTP POST com a string JSON no corpo
    client.print(headers);
    client.print(jsonString);

    // Aguarde a resposta
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }

    // Leitura da resposta
    String response;
    while (client.available()) {
      response += client.readStringUntil('\n');
    }
    response.replace("\"\\", "");
    response.replace("\\", "");
    Serial.println("Response do GPT: " + response);

    // Parsing do JSON
    int startIndex = response.indexOf("\"content\":\"") + 11;
    int endIndex = response.indexOf("\"", startIndex);

    String contentValue = response.substring(startIndex, endIndex);

    Serial.println(contentValue);
    client.stop();

    if (contentValue.length() > 280){
      getGPT(model, content);
    }

    return contentValue;

  }

void sendData(){
    float humidity = getPercentHumidity();
    String tweet = getGPT("gpt-3.5-turbo", "Primeira coisa que você precisa entender e que o texto gerado nao pode passar de 210 caracteres. Imagine que você é uma planta comediante e deseja enviar uma mensagem (no maximo 210 caracteres) para @marceloapda, seu criador. No entanto, a sua umidade do solo está em" + String(humidity) + "%, o que afeta diretamente o seu humor. Para a maioria das plantas a umidade do solo ideal é cerca de 50% a 75% , Entao crie um tweet com no maximo 210 caracteres em português que mencione de forma clara a sua condição de umidade, sem revelar que você é uma planta. Compartilhe uma mensagem engraçada ou fale um pouco sobre o que gostaria de fazer no dia de hoje ou talvez oque você sonhou, ou tentar conquistar o @marceloapda com uma cantada ou elegio, seja criativa. Deixe o humor da mensagem compatível com a umidade do solo Lembre-se de dar sugestões para @marceloapda para cuidar melhor de você SOMENTE caso as condições do seu solo não sejam as ideais. evite dizer que você e uma comediante. Não se esqueça: 210 caracteres!");
    sendTweet(tweet);
}

void handleClient () {
    server.handleClient();
}