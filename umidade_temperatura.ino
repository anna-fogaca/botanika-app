#include <LiquidCrystal.h>
#include "DHT.h"

#define PINODHT 8         
#define TIPODHT DHT11     
#define STATE_PIN 9    

DHT dht(PINODHT, TIPODHT);

// LCD nos pinos: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(STATE_PIN, INPUT); 
}

void loop() {
  int valorSensor = analogRead(sensorPin);
  int umidadePercentual = map(valorSensor, 1023, 0, 0, 100);

  float temperatura = dht.readTemperature();   
  float umidade = dht.readHumidity();

  int estadoBluetooth = digitalRead(STATE_PIN);

  // DEBUG
  Serial.print("Leitura: ");
  Serial.print(valorSensor);
  Serial.print(" | Umidade Solo: ");
  Serial.print(umidadePercentual);
  Serial.print("% | Amb: ");
  Serial.print(umidade);
  Serial.print("% | Temp: ");
  Serial.println(temperatura);

  // LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("U Solo: ");
  lcd.print(umidadePercentual);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("U:");
  lcd.print(umidade, 0);
  lcd.print("% T:");
  lcd.print(temperatura, 1);
  lcd.print("C");

  if (estadoBluetooth == HIGH) {
    Serial.print("BLUETOOTH LIGADO!");
    delay(5000);
  } else {
    Serial.print("BLUETOOTH DESLIGADO!");
    delay(5000);
  }

  delay(5000);

  if (valorSensor < 500) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Solo Seco!");
    delay(2000); 
  }
}
