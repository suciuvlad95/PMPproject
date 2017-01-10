#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);



#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);
//buton
int b1;
int b2;
int b3;
int newtemp=22;
void setup() {
  // configurare pini pentru butoane, intrare
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
  Serial.println(F("BME280 test"));
  lcd.begin(16,2);
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
// variabila pentru compunerea numarului de transmis
int stat = 0; float temp;
char tmp[8];
void loop() {

  // citire stare butoane
  b1 = digitalRead(8);
  b2 = digitalRead(9);
  b3 = digitalRead(10);

  Serial.print("Temperature = ");
  temp = bme.readTemperature();

  //sprintf(tmp, "%.1f", temp);
  Serial.println(" *C");
  lcd.print("tmp=");
  //lcd.setCursor(6,0);
  lcd.print(temp);
  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  if (b1 == HIGH)
    stat++;
  else if (b2 == HIGH)
    stat--;
  if (b3 == HIGH)
  { lcd.setCursor(0, 1);
    lcd.print("new temp:");
  }
  
  Serial.println(stat);
  Serial.println();
  //lcd.print(stat);
  delay(1500);
 // lcd.clear();
}
