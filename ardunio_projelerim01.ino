#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int ledSari = 2;
const int ledYesil = 3;
const int buzzerPin = 4;
const int lazerPin = 5;
const int gazSensor = A0; 

void setup() {
  pinMode(ledSari, OUTPUT);
  pinMode(ledYesil, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lazerPin, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  int deger = analogRead(gazSensor); // MQ-135'ten gelen canlı veri
  
  display.clearDisplay();
  
  // Üst Başlık
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("HAVA KALITESI: ");
  display.println(deger); // Sayısal değeri buraya ekledik

  // Çizgi Çizerek Ekranı Bölüyoruz (Görsel şov için)
  display.drawLine(0, 12, 128, 12, WHITE);

  if(deger > 450) { // Eşik değerini duruma göre buradan ayarla
    display.setCursor(15, 30);
    display.setTextSize(2);
    display.println("ALARM!!!");
    
    // Tehlike anında her şey aktif
    digitalWrite(lazerPin, HIGH);
    digitalWrite(buzzerPin, LOW); // Aktif düşük buzzer için
    digitalWrite(ledSari, HIGH);
    delay(150);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledSari, LOW);
    delay(150);
  } else {
    display.setCursor(10, 35);
    display.setTextSize(1);
    display.println("DURUM: TEMIZ");
    
    digitalWrite(lazerPin, LOW);
    digitalWrite(buzzerPin, HIGH); // Sustur
    digitalWrite(ledSari, LOW);
    
    // Normal çalışma ışığı
    digitalWrite(ledYesil, HIGH);
    delay(500);
    digitalWrite(ledYesil, LOW);
    delay(500);
  }
  display.display();
}