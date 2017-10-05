#include "DHT.h"
#include <LiquidCrystal.h>
#include <DS3232RTC.h>     
#include <TimeLib.h>
#include <Wire.h>

DHT dht;
LiquidCrystal lcd(11, 10, 9, 8, 7, 5);
     
int i;
int humidity_sx;
int temperature_sx;
int humidity_dx;
int temperature_dx;

void setup()
{
  pinMode(0, OUTPUT); // Verde, filo viola
  pinMode(1, OUTPUT); // Rosso, filo grigio
  pinMode(3, OUTPUT); // Sinistra, spot 
  pinMode(4, OUTPUT); // Destra, neon
  pinMode(15, INPUT); // Destra
  pinMode(16, INPUT); // Sinistra

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  
  lcd.begin(16, 2);
  
  lcd.print("hello, world!");
  delay(1000);
  
  lcd.home();
  lcd.print("Tsx Usx Tdx Udx");
}

void loop()
{
  dht.setup(15);
  delay(dht.getMinimumSamplingPeriod());
  humidity_dx = dht.getHumidity();
  temperature_dx = dht.getTemperature();

  dht.setup(16);
  delay(dht.getMinimumSamplingPeriod());
  humidity_sx = dht.getHumidity();
  temperature_sx = dht.getTemperature();

  i = 0;

  SPOT();
  NEON();
  TEMP();
  HUM();
  STAMPA();
  LED();
}

void SPOT()
{
  if(hour() >= 10 && hour() <= 20)
  {
    digitalWrite(3, HIGH);
  }

  else 
  {
    digitalWrite(3, LOW);
  }
}

void NEON()
{
  if(hour() >= 9 && hour() <= 21)
  {
    digitalWrite(4, HIGH);
  }

  else 
  {
    digitalWrite(4, LOW);
  }
}

void TEMP()
{
  if(temperature_dx >= 40 && temperature_dx <= 50 && temperature_sx >= 20 && temperature_sx <= 30)
  i = i + 0;
  
  else
  i++;
}

void HUM()
{
  if(humidity_dx >= 30 && humidity_dx <= 40 && humidity_sx >= 30 && humidity_sx <= 40)
  i = i + 0;

  else
  i++;
}

void STAMPA()
{
  lcd.setCursor(0, 1);
  lcd.print(temperature_sx);
  lcd.setCursor(4, 1);
  lcd.print(humidity_sx);
  lcd.setCursor(8, 1);
  lcd.print(temperature_dx);
  lcd.setCursor(12, 1);
  lcd.print(humidity_dx);   
}

void LED()
{
  if(i == 0)
  {
    digitalWrite(0, HIGH);
    digitalWrite(1, LOW);
  }
  
  else
  {
    digitalWrite(1, HIGH);
    digitalWrite(0, LOW);
  }
}
