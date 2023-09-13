#include "HX711.h"
// HX711.DOUT - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(A1, A0); // parameter "gain" is ommited; the default value 128 is used by the library

void setup()
{
Serial.begin(9600);
}

void loop()
{
scale.set_gain(128);
Serial.print("Loadcell A > ");
Serial.print((scale.read())); // print a raw reading from the ADC channel B

scale.set_gain(32);
Serial.print(" Loadcell B > ");
Serial.println((scale.read())); // print a raw reading from the ADC channel A
}
