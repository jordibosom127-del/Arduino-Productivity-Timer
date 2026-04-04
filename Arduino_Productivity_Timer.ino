#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte BUTTON = 7;
const byte BUZZER = 8;
const byte LED_20MIN = 9;
const byte LED_40MIN = 10;
const byte LED_60MIN = 11;


void setup() {
  pinConfig();
  lcd.init();
  lcd.backlight();

  digitalWrite(LED_20MIN, HIGH);
  motivationalMessage("STUDY TIME...");
  beep();
  delay(2000);


  digitalWrite(LED_40MIN, HIGH);
  motivationalMessage("BEGIN NOW!");
  beep();
  delay(2000);

  digitalWrite(LED_60MIN, HIGH);
  motivationalMessage("YOU CAN DO IT!");
  beep();
  delay(2000);

  turnOffLEDs();
  delay(500);
}

void loop() {
  motivationalMessage("LET'S DO IT!");
  delay(2000);
  // 20 MIN
  timerMessage("0-20 MIN", "IN PROGRESS");
  delay(600000);
  motivationalMessage("KEEP IT UP!");
  delay(3000);
  timerMessage("0-20 MIN", "IN PROGRESS");
  delay(600000);
  digitalWrite(LED_20MIN, HIGH);
  beep();
  delay(300);

  // 40 MIN
  timerMessage("20-40 MIN", "IN PROGRESS");
  delay(600000);
  motivationalMessage("COME ON!");
  delay(3000);
  timerMessage("20-40 MIN", "IN PROGRESS");
  delay(600000);
  digitalWrite(LED_40MIN, HIGH);
  beep();
  delay(300);

  // 60 MIN
  timerMessage("40-60 MIN", "FINAL PUSH!");
  delay(600000);
  motivationalMessage("ALMOST DONE!");
  delay(3000);
  timerMessage("40-60 MIN", "FINAL PUSH!");
  delay(600000);
  digitalWrite(LED_60MIN, HIGH);
  beep();
  motivationalMessage("AMAZING JOB!");
  delay(3000);

  //DECISION WITH BUTTON
  motivationalMessage("CONTINUE?");

  while (true) {
    if (digitalRead(BUTTON) == HIGH) {
      delay(50);
      if (digitalRead(BUTTON) == HIGH) {
        turnOffLEDs();
        delay(300);

        motivationalMessage("Restarting...");
        delay(3000);

        return;
      }
    }
  }
}

//SYSTEM CONFIG//

void pinConfig() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_20MIN, OUTPUT);
  pinMode(LED_40MIN, OUTPUT);
  pinMode(LED_60MIN, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(50);
  digitalWrite(BUZZER, LOW);
}

void turnOffLEDs() {
  digitalWrite(LED_20MIN, LOW);
  digitalWrite(LED_40MIN, LOW);
  digitalWrite(LED_60MIN, LOW);
}

void motivationalMessage(const char* msg) {
  lcd.clear();

  int len = strlen(msg);
  int col = (16 - len) / 2;

  if (col < 0) col = 0;

  lcd.setCursor(col, 0);
  lcd.print(msg);
}

void timerMessage(const char* line1, const char* line2) {
  lcd.clear();

  int len1 = strlen(line1);
  int col1 = (16 - len1) / 2;
  if (col1 < 0) col1 = 0;

  int len2 = strlen(line2);
  int col2 = (16 - len2) / 2;
  if (col2 < 0) col2 = 0;

  lcd.setCursor(col1, 0);
  lcd.print(line1);

  lcd.setCursor(col2, 1);
  lcd.print(line2);
}
