#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26,16,2);
// set the LCD address to 0x27 for a 16 chars and 2 line display

#include "HX711.h"
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;
const int ledpin1 = 13;
const int ledpin2 = 12;
//const int LOADCELL_SCK_PIN = 3;

HX711 scale;
float calibration_factor1 = 990;
float calibration_factor2 = 1080;
// this calibration factor must be adjusted according to your load cell
// 1번:990 2번: 1080 
float units1;
float units2;

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
scale.set_scale(calibration_factor1); //Adjust to this calibration factor
scale.tare(); //Reset the scale to 0
long zero_factor = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
Serial.println(zero_factor);

Serial.begin(9600);
scale.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
//Serial.println("Press + or a to increase calibration factor");
//Serial.println("Press - or z to decrease calibration factor");
scale.set_scale(calibration_factor2); //Adjust to this calibration factor
scale.tare(); //Reset the scale to 0
long zero_factor2 = scale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
Serial.println(zero_factor2);

pinMode(ledpin1, OUTPUT); 
pinMode(ledpin2, OUTPUT); 
}

void loop() {
  Serial.print("Reading1");
  units1 = scale.get_units(), 5;
  if (units1 < 0) {
    units1 = 0.00;
  }
  Serial.print("Weight: ");
  Serial.print(units1);
  Serial.print(" grams");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor1);
  //Serial.println();

  Serial.print("Reading2");
  units2 = scale.get_units(), 5;
  if (units2 < 0) {
    units2 = 0.00;
  }
  Serial.print("  | Weight: ");
  Serial.print(units2);
  Serial.print(" grams");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor2);
  Serial.println();
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  //delay(1000);
  lcd.print(units1);
  lcd.setCursor(5, 0);
  lcd.print("g");

  if (units1 < 30) {
    digitalWrite(ledpin1, HIGH);
  }
  
  //lcd.noCursor();
  //lcd.noBlink();
  //delay(1000);
}
