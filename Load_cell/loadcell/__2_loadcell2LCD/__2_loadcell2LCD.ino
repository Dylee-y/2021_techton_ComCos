#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711-multi.h"
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);
// set the LCD address to 0x27 for a 16 chars and 2 line display
// I2C로 연결되기 때문에 핀 번호를 따로 써 줄 필요는 없다.
// SDA: A4, SCL: A5

const int ledpin1 = 13;
const int ledpin2 = 12;
float w1;
float w2;

// Pins to the load cell amp
#define CLK A0      // clock pin to the load cell amp
#define DOUT1 A1    // data pin to the first lca
#define DOUT2 A2    // data pin to the second lca

#define BOOT_MESSAGE "Successfully Booted!"

#define TARE_TIMEOUT_SECONDS 4

byte DOUTS[2] = {DOUT1, DOUT2};

#define CHANNEL_COUNT sizeof(DOUTS)/sizeof(byte)

long int results[CHANNEL_COUNT];

HX711MULTI scales(CHANNEL_COUNT, DOUTS, CLK);

void setup() {
  lcd1.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd2.init(); // initialize the lcd
  lcd1.backlight();
  lcd2.backlight();
  lcd1.print("Initiated LCD 1");
  lcd2.print("Initiated LCD 2");
  // Print a message to the LCD
  delay(2000);

  Serial.begin(115200);
  //Serial.println(BOOT_MESSAGE);
  //Serial.flush();
  //pinMode(11,OUTPUT);

  tare();

  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  /* Useless code from other reference
      Leaving this cuz this might be helpful
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
  */

}


void tare() {
  bool tareSuccessful = false;

  unsigned long tareStartTime = millis();
  while (!tareSuccessful && millis() < (tareStartTime + TARE_TIMEOUT_SECONDS * 1000)) {
    tareSuccessful = scales.tare(20, 10000); //reject 'tare' if still ringing
  }
}
void LCDLEDdisplay() {
  w1 = abs(float(results[0]) / 1000.);
  w2 = abs(float(results[1]) / 1000.);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Kiehl Lip Balm");
  lcd1.setCursor(0, 1);
  //delay(1000);
  lcd1.print(w1);
  lcd1.setCursor(5, 1);
  lcd1.print("g");

  if (w1 < 20) {
    digitalWrite(ledpin1, HIGH);
  }
  else {
    digitalWrite(ledpin1, LOW);
  }


  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Tonymoly Tint");
  lcd2.setCursor(0, 1);
  //delay(1000);
  lcd2.print(w2);
  lcd2.setCursor(5, 1);
  lcd2.print("g");

  if (w2 < 8) {
    digitalWrite(ledpin2, HIGH);
  }
  else {
    digitalWrite(ledpin2, LOW);
  }

}
void sendRawData() {
  scales.read(results);
  Serial.println(w1);
  Serial.println(w2);
  LCDLEDdisplay();
  /*
  for (int i = 0; i < scales.get_count(); ++i) {
    ;
    Serial.print( float(results[i]) / 1000.);
    //modify this for better serial monitor displaying
    
    Serial.print( (i != scales.get_count() - 1) ? "\t" : "\n");
    LCDLEDdisplay();
  }
  */
  delay(2500);
}

void loop() {

  sendRawData(); //this is for sending raw data, for where everything else is done in processing

  //on serial data (any data) re-tare
  if (Serial.available() > 0) {
    while (Serial.available()) {
      Serial.read();
    }
    tare();
  }



  /*
    //Serial.print("Reading");
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
    lcd.setCursor(0, 0);
    //delay(1000);
    lcd.print(units);
    lcd.setCursor(5, 0);
    lcd.print("g");
    //lcd.noCursor();
    //lcd.noBlink();
    //delay(1000);
  */
}
