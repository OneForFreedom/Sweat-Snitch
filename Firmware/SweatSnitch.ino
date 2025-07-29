#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SHT2x.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SHT2x sht;

unsigned long lastFlashMillis = 0;      
unsigned long lastTempFlashMillis = 0;  
bool tempFlashState = false;
bool flashingFor30to40 = false;
unsigned long flashStartMillis = 0;

void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  sht.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  float temperature = sht.readTemperature();
  float humidity = sht.readHumidity();

  
  if (currentMillis - lastFlashMillis >= 60000) {
    display.clearDisplay();
    display.fillScreen(WHITE);
    display.display();
    delay(1000);  
    lastFlashMillis = currentMillis;
    return; 
  }

  
  if (temperature > 40) {
    
    if (currentMillis - lastTempFlashMillis >= 500) {
      tempFlashState = !tempFlashState;
      lastTempFlashMillis = currentMillis;
    }

    display.clearDisplay();
    if (tempFlashState) {
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.print((int)temperature);
      display.print(" C");
    }
    display.display();
    flashingFor30to40 = false;  
    return; 
  } 
  else if (temperature > 30) {
   
    if (!flashingFor30to40) {
      flashingFor30to40 = true;
      flashStartMillis = currentMillis;
      tempFlashState = true;
      lastTempFlashMillis = currentMillis;
    }

    if (currentMillis - flashStartMillis <= 5000) {
      if (currentMillis - lastTempFlashMillis >= 500) {
        tempFlashState = !tempFlashState;
        lastTempFlashMillis = currentMillis;
      }

      display.clearDisplay();
      if (tempFlashState) {
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(0, 20);
        display.print((int)temperature);
        display.print(" C");
      }
      display.display();
      return; 
    } else {
      flashingFor30to40 = false; 
    }
  } else {
    flashingFor30to40 = false; 
  }

  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print((int)temperature);
  display.print(" C");
  display.display();
}
