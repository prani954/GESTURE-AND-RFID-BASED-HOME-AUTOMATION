#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,6,5,4,3);
#define APDS9960_INT    2
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
int relay1 = 8;
int relay2 = 9; 
int relay3 = 10;
int relay4 = 7;
void setup () {
 pinMode (APDS9960_INT, INPUT);
pinMode (relay1, OUTPUT);
pinMode (relay2, OUTPUT);
pinMode (relay3, OUTPUT);
pinMode (relay4, OUTPUT);
 Serial.begin(9600);
 Serial.println();
Serial.println(F("--------------------------------"));
 Serial.println(F ("SparkFun APDS-9960 - GestureTest"));
Serial.println(F ("--------------------------------"));
attachInterrupt (0, interruptRoutine, FALLING);
if (apds.init() ) {
Serial.println(F("APDS-9960 initialization complete"));
}
 else {
Serial.println(F("Something went wrong during APDS-9960 init!"));
}
  if (apds.enableGestureSensor(true) ) {
 Serial.println(F ("Gesture sensor is now running"));
  } 
else {
    Serial.println(F ("Something went wrong during gesture sensor init!"));
  }
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print (" GESTURE BASED ");
  lcd.setCursor(0,1);
  lcd.print (" HOME AUTOMATION ");
  delay (5000);
}
void loop ()
{
          lcd.setCursor(0,0);
          lcd.print("  WAITING FOR   ");
          lcd.setCursor(0,1);
          lcd.print("     INPUT      ");
  if (isr_flag ==1) {
    detachInterrupt (0);
    handleGesture ();
    isr_flag = 0;
    attachInterrupt (0, interruptRoutine, FALLING);
  }
}
void interruptRoutine () {
  isr_flag = 1;
}
void handleGesture () {
if (apds.isGestureAvailable() ) {
      Serial.println("Detected Gesture....");
      switch (apds.readGesture() ) {
        case DIR_UP:
        {
          Serial.println("UP");
          digitalWrite (relay1, HIGH);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print(" HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print("BULB1 ON ");
          delay (2000);
          lcd.clear();
          break;
        }
        case DIR_DOWN:
          {
           Serial.println("DOWN");
          digitalWrite (relay2, HIGH);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print("HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print("BULB2 ON ");
          delay (2000);
          lcd.clear();
          break;
          }
        case DIR_LEFT:
          {
           Serial.println("LEFT");
          digitalWrite (relay3, HIGH);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print("HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print ("FAN ON ");
          delay (2000);
          lcd.clear();
          break;
          }
        case DIR_RIGHT:
          {
           Serial.println("RIGHT");
          digitalWrite (relay4, HIGH);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print("HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print("RELAY4 ON ");
          delay (2000);
          lcd.clear();
          break;
          }
        case DIR_NEAR:
          {
           Serial.println("NEAR");
          digitalWrite (relay1, HIGH);
          digitalWrite (relay2, HIGH);
          digitalWrite (relay3, HIGH);
          digitalWrite (relay4, HIGH);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print("HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print ("RELAY ON ");
          delay (2000);
          lcd.clear();
          break;
          }
        case DIR_FAR:
          {
           Serial.println("FAR");
          digitalWrite (relay1, LOW);
          digitalWrite (relay2, LOW);
          digitalWrite (relay3, LOW);
          digitalWrite (relay4, LOW);
          delay (2000);
          lcd.setCursor(0,0);
          lcd.print("HOME AUTOMATION ");
          lcd.setCursor(0,1);
          lcd.print ("RELAY OFF ");
          delay (2000);
          lcd.clear();
          break;
          }
        default:
          Serial.println("NONE");
}
}
 }
