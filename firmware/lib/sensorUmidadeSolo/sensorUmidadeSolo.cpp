#include <Arduino.h>

float getPercentHumidity() {
  int valorADC;
  int value;
  float umidadePercentual;

  valorADC = analogRead(0); //1024 -> 3,3V

  value = constrain(valorADC,700, 1024);
  umidadePercentual = map(value,700, 1024, 100, 0);

  // Serial.println("valorADC: " + String(valorADC) + " umidadePercentual: " + umidadePercentual );
  return umidadePercentual;
}

void printDatas() {
    float umidadePercentual = getPercentHumidity();
    int valorADC = analogRead(0);
    Serial.println("Valor do sensor: " + String(valorADC) + "\tUmidade do solo: " + umidadePercentual);
}
