#include <Arduino.h>
#include "sensorUmidadeSolo.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(fazLeituraUmidade());
}