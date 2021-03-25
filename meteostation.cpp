
#include <LiquidCrystal.h>
#include "DHT.h"
#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1307); 

#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
const int buttonupPin = 9 ;
const int buttondownPin = 10 ;
const int buttonsetPin = 11 ;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int buttonupState = 0;
int buttondownState = 0;
int buttonsetState = 0;

char v ;

unsigned long timenow;
void setup()
{
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  delay(300);
  Serial.begin(9600);  // определение скорости порта
  time.begin();
  lcd.begin(16, 2);

  dht.begin();
}
void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();


  lcd.setCursor(0, 0);
  lcd.print(time.gettime("d-m-y"));
  lcd.setCursor(8, 0);
  lcd.print(time.gettime( "H:i:s"));
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(7, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(13, 1);
  lcd.print(v, HEX);

  if ((millis() - timenow) > 3) {
    if (!digitalRead(11)) {
      v = v + 1 ;
    }
    if (!digitalRead(buttonupPin))
      switch (v) {
        case (1):
          Serial.println('+');
          time.gettime();
          if ((time.minutes + 1) > 59)
            time.settime(-1, 0, -1, -1, -1, -1);
          else time.settime(-1, time.minutes + 1, -1, -1, -1, -1);
          break;
        case (2):
          Serial.println('2');
          time.gettime();
          if ((time.Hours + 1) > 23)
            time.settime(-1, -1, 0, -1, -1, -1);
          else time.settime(-1, -1, time.Hours + 1,  -1, -1, -1);
          break;
        case (3):
          Serial.println('3');
          time.gettime();
          if ((time.day + 1) > 31)
            time.settime(-1, -1, -1, 0, -1, -1);
          else time.settime(-1, -1, -1, time.day + 1,  -1, -1);
          break;
        case (4):
         
          Serial.println('4');
          time.gettime();
          if ((time.month + 1) > 12)
            time.settime(-1, -1, -1, -1, 0, -1);
          else time.settime(-1, -1, -1, -1, time.month + 1,   -1);
          break;
        case (5):
          Serial.println('5');
          time.gettime();
          if ((time.year + 1) > 70)
            time.settime(-1, -1, -1, -1, -1 , 10);
          else time.settime(-1, -1, -1, -1, -1, time.year + 1 );
          break;
        case (6) :
        time.settime(0);
      }
    timenow = millis();
  }
}



