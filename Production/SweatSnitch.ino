#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_HDC1000.h>  // For HDC1080 sensor; same lib

// OLED configs
#define SCREEN_WIDTH_64 128
#define SCREEN_HEIGHT_64 64
#define SCREEN_WIDTH_32 128
#define SCREEN_HEIGHT_32 32

// Mux control pins (connected to Xiao GPIO26, 27, 28)
#define A0_PIN 26
#define A1_PIN 27
#define A2_PIN 28

// I2C address of HDC1080
#define HDC1080_ADDR 0x40

// Create OLED objects (use same I2C addr, mux switches channel)
Adafruit_SSD1306 display64(SCREEN_WIDTH_64, SCREEN_HEIGHT_64, &Wire, -1);
Adafruit_SSD1306 display32(SCREEN_WIDTH_32, SCREEN_HEIGHT_32, &Wire, -1);

// Create HDC1080 sensor object
Adafruit_HDC1000 hdc1080;

// Time tracking for display inversion flip (prevent burn-in)
unsigned long lastInvertTime = 0;
const unsigned long invertInterval = 10000; // 10 sec invert toggle

// Inversion state flags
bool display64Inverted = false;
bool display32Inverted = false;

// Mux channel select function using GPIOs
void selectMuxChannel(uint8_t channel) {
  digitalWrite(A0_PIN, channel & 0x01);
  digitalWrite(A1_PIN, (channel >> 1) & 0x01);
  digitalWrite(A2_PIN, (channel >> 2) & 0x01);
}

// Draw border on display64 according to temp
void drawTempBorder(float temp) {
  uint8_t borderSize = 0;
  if (temp > 40.0) borderSize = 4;
  else if (temp > 30.0) borderSize = 1;

  if (borderSize == 0) return;

  // Draw rectangle border (affected by inversion)
  display64.drawRect(0, 0, SCREEN_WIDTH_64, SCREEN_HEIGHT_64, SSD1306_WHITE);
  if (borderSize > 1) {
    for (uint8_t i = 1; i < borderSize; i++) {
      display64.drawRect(i, i, SCREEN_WIDTH_64 - 2 * i, SCREEN_HEIGHT_64 - 2 * i, SSD1306_WHITE);
    }
  }
}

// Draw humidity inversion on display32 from left to right
void drawHumidityInvert(float humidity) {
  uint8_t invertWidth = (uint8_t)((humidity / 100.0) * SCREEN_WIDTH_32);

  if (invertWidth == 0) return;

  // Invert left portion by drawing filled rect with INVERSE color
  display32.fillRect(0, 0, invertWidth, SCREEN_HEIGHT_32, SSD1306_INVERSE);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Setup mux control pins as outputs
  pinMode(A0_PIN, OUTPUT);
  pinMode(A1_PIN, OUTPUT);
  pinMode(A2_PIN, OUTPUT);

  Wire.begin();

  // Init sensor on mux channel 0
  selectMuxChannel(0);
  if (!hdc1080.begin(HDC1080_ADDR)) {
    Serial.println("HDC1080 sensor not found");
    while (1);
  }

  // Init OLED 64x64 on mux channel 1
  selectMuxChannel(1);
  if (!display64.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("64x64 OLED init failed");
    while (1);
  }
  display64.clearDisplay();
  display64.display();

  // Init OLED 128x32 on mux channel 2
  selectMuxChannel(2);
  if (!display32.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("32x128 OLED init failed");
    while (1);
  }
  display32.clearDisplay();
  display32.display();

  lastInvertTime = millis();
}

void loop() {
  // Read sensor values on mux channel 0
  selectMuxChannel(0);
  float tempC = hdc1080.readTemperature();
  float humidity = hdc1080.readHumidity();

  // Clamp humidity between 0-100 just in case
  if (humidity < 0) humidity = 0;
  if (humidity > 100) humidity = 100;

  // Handle 64x64 OLED (temp display + border + invert)
  selectMuxChannel(1);
  display64.clearDisplay();

  // Flip inversion every invertInterval milliseconds to avoid burn-in
  if (millis() - lastInvertTime > invertInterval) {
    display64Inverted = !display64Inverted;
    display64.invertDisplay(display64Inverted);
  }

  // Draw temp border if needed
  drawTempBorder(tempC);

  // Draw temperature text
  display64.setTextSize(3);
  display64.setTextColor(SSD1306_WHITE);
  display64.setCursor(10, 20);
  display64.print(tempC, 1);
  display64.print(" C");
  display64.display();

  // Handle 128x32 OLED (humidity display with left invert portion)
  selectMuxChannel(2);
  display32.clearDisplay();

  // Clear inversion every cycle
  display32.invertDisplay(false);

  // Draw humidity percentage text
  display32.setTextSize(3);
  display32.setTextColor(SSD1306_WHITE);
  display32.setCursor(10, 5);
  display32.print(humidity, 0);
  display32.print(" %");

  // Now draw left invert portion proportional to humidity
  drawHumidityInvert(humidity);

  display32.display();

  delay(1000); // 1 sec delay between updates
}
