#include <DNSServer.h>

#include <DNSServer.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClosedCube_HDC1080.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ClosedCube_HDC1080 hdc1080;

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
  hdc1080.begin(0x40);  // Default address for HDC1080
}

void loop() {
  unsigned long currentMillis = millis();
  float temperature = hdc1080.readTemperature();
  float humidity = hdc1080.readHumidity();

  // Every 60 seconds flash the whole screen white for 1 second
  if (currentMillis - lastFlashMillis >= 60000) {
    display.clearDisplay();
    display.fillScreen(WHITE);
    display.display();
    delay(1000);
    lastFlashMillis = currentMillis;
    return;
  }

  // Temperature flashing logic for > 40C
  if (temperature > 40) {
    if (currentMillis - lastTempFlashMillis >= 500) {
      tempFlashState = !tempFlashState;
      lastTempFlashMillis = currentMillis;
    }

    display.clearDisplay();

    // Left side - humidity plain
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.print((int)humidity);
    display.print("%");

    // Right side - temperature flashing big
    if (tempFlashState) {
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(70, 20);
      display.print((int)temperature);
      display.print(" C");
    }

    display.display();
    flashingFor30to40 = false;
    return;
  }
  // Temperature flashing for 30-40C for 5 seconds
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

      // Left side - humidity plain
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.print((int)humidity);
      display.print("%");

      // Right side - temp flashing
      if (tempFlashState) {
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(70, 20);
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

  // Normal display mode
  display.clearDisplay();

  // Left side - humidity plain
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print((int)humidity);
  display.print("%");

  // Right side - temperature normal
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(70, 20);
  display.print((int)temperature);
  display.print(" C");

  display.display();
}
