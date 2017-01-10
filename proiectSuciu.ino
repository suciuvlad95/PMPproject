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
int b0, b1, b2, b3;

int cont = 10;
int newtemp = 22;
void setup() {
  // configurare pini pentru butoane, intrare
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("BME280 test"));
  lcd.begin(16, 2);
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
// variabila pentru compunerea numarului de transmis
int stat = 20; float temp;
char tmp[8];
void loop() {

  // citire stare butoane
  b0 = digitalRead(8);
  b1 = digitalRead(9);
  b2 = digitalRead(10);
  b3 = digitalRead(11);
  Serial.print("Temperature = ");
  temp = bme.readTemperature();

  sprintf(tmp, "%.1f", temp);
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
  if (b0 == HIGH)
    stat++;
  else if (b1 == HIGH)
    stat--;
   lcd.setCursor(0, 1);
    lcd.print("from ");
    lcd.print(temp);
    lcd.print(" to ");
    //b0 = digitalRead(8);
    //b1 = digitalRead(9);

    lcd.print(stat);


    //}  lcd.print("Proccesing");
  
  if (b2 ==HIGH)
  {
     lcd.setCursor(0, 1);
     if(stat<temp)
      {
        
        lcd.print("Cooling         ");
        digitalWrite(LED_BUILTIN, HIGH);
         delay(5000);
        lcd.setCursor(0, 1);
        lcd.print("Good Temp         ");
        delay(1000);
        lcd.setCursor(0, 1);
        int k=stat-temp;
        lcd.print(k);
         lcd.print(" degree cool         ");
        delay(1000);
      }
      else {lcd.print("Heating            ");
        delay(5000);
        lcd.setCursor(0, 1);
        lcd.print("Good Temp      ");
        delay(1000);
        lcd.setCursor(0, 1);
         int v=stat-temp;  
         lcd.print(v); 
         lcd.print(" degree heat         ");
        delay(1000);
      }
  }

  Serial.println(stat);
  Serial.println();//enter
  //lcd.print(stat);
  delay(1000);
  lcd.setCursor(0, 0);
  //lcd.clear();
}
