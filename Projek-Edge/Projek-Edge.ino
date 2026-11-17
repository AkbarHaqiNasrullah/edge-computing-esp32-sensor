#include <Wire.h>
#include <DHT.h>

const int ldrPin = 4;
const int MQ135_PIN = 2;

#define DHT_PIN 15
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();  // wajib dipanggil agar sensor DHT siap dibaca
  pinMode(13, OUTPUT);

  Serial.println(F("Edge Computing"));
  Serial.println(F("Kelompok 11"));
  delay(5000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%"));
  Serial.print(F(","));
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C"));

  int ldrValue = analogRead(ldrPin);

  Serial.print(F("Intensitas Cahaya: "));
  Serial.print(ldrValue);
  Serial.print(F(","));
  Serial.print(F(" Ruangan: "));

  String lightStatus;
  if (ldrValue <= 30) {
    lightStatus = F("Terang");
  } else if (ldrValue > 30 && ldrValue <= 100) {
    lightStatus = F("Redup");
  } else {
    lightStatus = F("Gelap");
  }
  Serial.println(lightStatus);

  int mq135Value = analogRead(MQ135_PIN);

  Serial.print("MQ-135 Sensor Value: ");
  Serial.println(mq135Value);

  delay(1000);  // jeda 1 detik antar pembacaan
}
