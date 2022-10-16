#include <Arduino.h>

float getPercentHumidity() {
  int valorADC;
  int value;
  float umidadePercentual;

  valorADC = analogRead(0); //1024 -> 3,3V

  value = constrain(valorADC,560, 1024);
  umidadePercentual = map(value,560,1024,100,0);
  Serial.println("Valor do sensor:" + String(valorADC) + "\nUmidade do solo:" + umidadePercentual);

  return umidadePercentual;
}
