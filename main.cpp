#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHTesp.h>

#define DHTPIN    15
#define DHTTYPE   DHTesp::DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dht;

void setup() {
  Serial.begin(115200);
  dht.setup(DHTPIN, DHTTYPE);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Temp/Humidity ");
  lcd.setCursor(0, 1);
  lcd.print("   Starting...  ");
  delay(2000);
}

void loop() {
  delay(2000);

  float humidity = dht.getHumidity();
  float tempC    = dht.getTemperature();

  if (isnan(humidity) || isnan(tempC)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring... ");
    Serial.println("DHT read failed!");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(humidity, 1);
  lcd.print("%");

  Serial.print("Temp: "); Serial.print(tempC); Serial.print("C  ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
}
