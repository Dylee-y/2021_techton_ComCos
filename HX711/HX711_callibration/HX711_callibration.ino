/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale1(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);


void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1.5);
  scale.tare();
  
}

void loop() {
  Serial.println(scale.get_units(10));
  /*scale.set_scale(5.55);*/

}
