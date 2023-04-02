#include <WiFiClient.h>

WiFiClient client;

void sendTweet(String apiKey, String tweet) {
  tweet.replace(" ", "%20");
  // Conecta ao servidor HTTP
  if (!client.connect("api.thingspeak.com", 80)) {
    Serial.println("Falha ao conectar ao servidor HTTP");
    return;
  }

  // Faz uma requisição GET para atualizar o status do ThingTweet
  String url = "/apps/thingtweet/1/statuses/update?api_key=" + apiKey + "&status=" + tweet;
  Serial.print("Fazendo requisição GET para: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + "api.thingspeak.com" + "\r\n" +
               "Connection: close\r\n\r\n");

  // Lê a resposta do servidor HTTP
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Resposta do servidor HTTP:");
      break;
    }
  }

  String response = client.readString();
  Serial.println(response);
}