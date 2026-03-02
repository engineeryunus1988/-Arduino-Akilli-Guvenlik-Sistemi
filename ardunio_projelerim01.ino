#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED ekran genişlik ve yükseklik
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// OLED reset pini (bazı modellerde -1 yerine 4 gerekebilir ama genelde -1'dir)
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pinler
const int ledSari = 2;
const int ledYesil = 3;
const int buzzerPin = 4;
const int lazerPin = 5;
const int gazSensor = A0; 

void setup() {
  Serial.begin(9600); // Hata ayıklama için seri portu açalım
  
  pinMode(ledSari, OUTPUT);
  pinMode(ledYesil, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lazerPin, OUTPUT);

  // OLED ekranı başlat
  // 0x3C adresi çalışmazsa 0x3D dene!
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED ekran bulunamadi!"));
    for(;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("SISTEM HAZIR!");
  display.display();
  delay(2000);
}

void loop() {
  int deger = analogRead(gazSensor); // Gaz değerini oku
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Gaz Seviyesi: ");
  display.println(deger);

  if(deger > 350) { // Gaz eşiği
    display.setCursor(0,20);
    display.setTextSize(2);
    display.println("ALARM!!!");
    
    // Alarm kısmındaki bu bölümü şöyle değiştir:
if(deger > 350) { 
    digitalWrite(buzzerPin, LOW); // Aktif düşük olduğu için LOW ses çıkarır
    digitalWrite(lazerPin, HIGH);
    delay(500);                   // Sesi yarım saniye boyunca tut (daha belirgin olur)
    digitalWrite(buzzerPin, HIGH); // Sustur
    digitalWrite(lazerPin, LOW);
    delay(100);                   // Kısa ara
}
  } else {
    display.setCursor(0,20);
    display.setTextSize(1);
    display.println("Hava Temiz.");
    
    digitalWrite(lazerPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledSari, LOW);
    
    // Normal durumda yeşil yansın
    digitalWrite(ledYesil, HIGH);
    delay(500);
    digitalWrite(ledYesil, LOW);
    delay(500);
  }
  display.display();
}