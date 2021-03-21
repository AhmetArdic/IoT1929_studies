
#include "DHT.h"
#define DHTPIN 3

#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  dht.begin();
}

void loop() {
  delay(1500);

  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float k = ((f - 32)/1.8) + 273.15;

  if (isnan(h) || isnan(f) || isnan(k)) {
    Serial.println("Okuma isleminde hata var, tekrar deneniyor..");
    return;
  }


  Serial.print("Nem: ");
  Serial.print(h);
  Serial.print("%  Sicaklik: ");
  Serial.print(f);
  Serial.print("°F ");
  Serial.print(k);
  Serial.println("°K");
}
