#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
// set the LCD address to 0x27 for a 16 chars and 2 line display

#include "HX711.h"
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;
float calibration_factor = 990;
// this calibration factor must be adjusted according to your load cell
// 1번:990 2번: 1080 
float units;

void setup() {
lcd.init(); // initialize the lcd
// Print a message to the LCD.
lcd.backlight();
lcd.print("Initiated");
delay(1000);

Serial.begin(9600);
scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
Serial.println("HX711 calibration sketch");
Serial.println("Remove all weight from scale");
Serial.println("After readings begin, place known weight on scale");
//Serial.println("Press + or a to increase calibration factor");
//Serial.println("Press - or z to decrease calibration factor");
scale.set_scale(calibration_factor); //Adjust to this calibration factor
scale.tare(); //Reset the scale to 0
long zero_factor = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
Serial.println(zero_factor);

}

void loop() {
  Serial.print("Reading");
  units = scale.get_units(), 5;
  if (units < 0) {
    units = 0.00;
  }
  Serial.print("Weight: ");
  Serial.print(units);
  Serial.print(" grams");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  //delay(1000);
  lcd.print(units);
  lcd.setCursor(5, 0);
  lcd.print("g");
  //lcd.noCursor();
  //lcd.noBlink();
  //delay(1000);
}
