#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int PIN_MQ2    = A0;
const int PIN_LED    = 8;
const int PIN_BUZZER = 9;
const int PIN_RELAY  = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned long WARMUP_TIME_MS   = 45000;
const int DISCARD_READS               = 10;
const int CALIBRATION_READS           = 20;
const int THRESHOLD_OFFSET            = 100;

int baseline = 0;
int gasThreshold = 300;

void setup() {
 pinMode(PIN_LED,    OUTPUT);
 pinMode(PIN_BUZZER, OUTPUT);
 pinMode(PIN_RELAY,  OUTPUT);
 digitalWrite(PIN_LED,    LOW);
 digitalWrite(PIN_BUZZER, LOW);
 digitalWrite(PIN_RELAY,  LOW);
 
 Wire.begin();
 lcd.init();
 lcd.backlight();
 
 lcd.clear();
 lcd.print("Aquecendo MQ-2");
 unsigned long t0 = millis();
 while (millis() - t0 < WARMUP_TIME_MS) {
   delay(500);
 }
 
 lcd.clear();
 lcd.print("Descartando...");
 for (int i = 0; i < DISCARD_READS; i++) {
   analogRead(PIN_MQ2);
   delay(100);
 }
 
 lcd.clear();
 lcd.print("Calibrando...");
 long sum = 0;
 for (int i = 0; i < CALIBRATION_READS; i++) {
   sum += analogRead(PIN_MQ2);
   delay(100);
 }
 baseline = sum / CALIBRATION_READS;
 
 gasThreshold = baseline + THRESHOLD_OFFSET;
 gasThreshold = constrain(gasThreshold, 0, 1023);
 
 lcd.clear();
 lcd.print("Base:");
 lcd.print(baseline);
 lcd.setCursor(0,1);
 lcd.print("Lim:");
 lcd.print(gasThreshold);
 delay(3000);
 lcd.clear();
}

void loop() {
 int gasValue = analogRead(PIN_MQ2);
 
 lcd.setCursor(0,0);
 lcd.print("GAS:");
 lcd.print(gasValue);
 lcd.print("   ");
 lcd.setCursor(0,1);
 lcd.print("T:");
 lcd.print(gasThreshold);
 lcd.print("   ");
 
 if (gasValue > gasThreshold) {
   digitalWrite(PIN_LED, HIGH);
   tone(PIN_BUZZER, 1000);
   digitalWrite(PIN_RELAY, HIGH);
 } else {
   digitalWrite(PIN_LED, LOW);
   noTone(PIN_BUZZER);
   digitalWrite(PIN_RELAY, LOW);
 }
 
 delay(1000);
}
