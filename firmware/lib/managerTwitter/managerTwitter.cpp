#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

HTTPClient twitterHttp;
WiFiClient twitterClient;

void sendTweet(String status) {
  twitterHttp.begin(twitterClient, "http://api.thingspeak.com/apps/thingtweet/1/statuses/update");
  twitterHttp.addHeader("Content-Type", "application/json");

  // Define o corpo da requisição
  String requestBody = "{\"api_key\": \"{{api_key}}\", \"status\":\""+status+"\"}";
  Serial.println(requestBody);

  // Envia a requisição HTTP POST
  int httpResponseCode = twitterHttp.POST(requestBody);

  // Verifica se a requisição foi bem sucedida
  if (httpResponseCode == HTTP_CODE_OK) {
    Serial.println("Tweet enviado com sucesso!");
  } else {
    Serial.println("Erro ao enviar tweet.");
  }

  // Encerra a conexão HTTP
  twitterHttp.end();
}