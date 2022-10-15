#include <Arduino.h>

float getPercentHumidity() {
  int valorADC;
  int value;
  float umidadePercentual;'

  valorADC = analogRead(0); //1024 -> 3,3V
  Serial.println(valorADC);
  // umidadePercentual = 100 * ((1024 - (float)valorADC) / 674);
  // umidadePercentual = 100 * ((980 - (float)valorADC) / 710);  
  // int max = 300;
  // int min = 450;
  // int range = max - min;
  
  // umidadePercentual = ((float)valorADC - min) * 100 / range;'

  value = constrain(valorADC,560, 1024);
  umidadePercentual = map(value,560,1024,100,0);


  // if (valorADC <= 270) {
  //   umidadePercentual = 100.0;
  // } else if (valorADC >=1000) {
  //   umidadePercentual = 0;
  // }

  return umidadePercentual;
}
