#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

void sendTweet(String status){

  HTTPClient twitterHttp;
  WiFiClientSecure client;

  client.setInsecure();
  client.setTimeout(10000);

  twitterHttp.begin(client, "https://api.twitter.com/2/tweets");
  twitterHttp.addHeader("Content-Type", "application/json");
  twitterHttp.addHeader("Authorization", "OAuth oauth_consumer_key=\"wpsn1rY4bSDsTChJqbqOzYFhv\",oauth_token=\"1263302848651165696-WZoegbLnMcwxZz34B8kva1TTSuxPiR\",oauth_signature_method=\"HMAC-SHA1\",oauth_timestamp=\"1680606753\",oauth_nonce=\"ii2cXuOBTqL\",oauth_version=\"1.0\",oauth_signature=\"OstWjFFFvP%2BOH7ZbYF25mVu9BLs%3D\"");

  String postData = "{\"text\": \"" + status + "\"}";

  int httpCode = twitterHttp.POST(postData);

  if (httpCode > 0)
  {
    String response = twitterHttp.getString();
    Serial.println("Response:");
    Serial.println(response);
  }
  else
  {
    Serial.println("Error on sending POST request");
    Serial.println(twitterHttp.errorToString(httpCode));
  }

  twitterHttp.end();

}