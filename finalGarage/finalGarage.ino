#include <TFMPlus.h>
#include <HardwareSerial.h>
#include <Adafruit_NeoPixel.h>

// TFMini Plus Setup 
TFMPlus tfmP;
HardwareSerial tfSerial(1);  // Using UART1 on Nano ESP32
const int RX_PIN = 43;       // White wire on TFMini Plus -> GPIO43 (RX0 on board)
const int TX_PIN = 44;       // Green wire on TFMini Plus -> GPIO44 (TX1 on board)

// WS2812B LED Setup
#define LED_PIN     5         // D2 on Nano ESP32 = GPIO5 (signal pin that goes to the resistor and then the LED strip)
#define NUM_LEDS    60        // Number of LEDs on WS2812B strip
#define BRIGHTNESS  40    
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Distance Thresholds for Different Color Stages
const int MIN_DISTANCE = 167.64;   // 66 in - perfect spot (red)
const int MID_DISTANCE = 210.82;   // 83 in - moderate range (yellow)
const int MAX_DISTANCE = 254;   // 100 in - (off)

// Timing and parking detection
unsigned long lastReadTime = 0;
const unsigned long readInterval = 250; // read sensor every 250ms

// Variables for parked detection (checks if system should stop)
int16_t lastDist = -1;            // last measured distance
unsigned long lastChangeTime = 0; // last time distance changed
const unsigned long parkedTimeout = 3000; // 3 seconds parked timeout to ensure clarity for driver

void setup() {
  Serial.begin(115200);
  delay(500);

  // Start TFMini Plus sensor
  tfSerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(500);

  if (tfmP.begin(&tfSerial)) {
    Serial.println("TFMini Plus connected!");
    tfmP.sendCommand(SET_FRAME_RATE, FRAME_100);
    tfmP.sendCommand(SAVE_SETTINGS, 0);
  } else {
    Serial.println("TFMini Plus connection failed.");
  }

  // Initialize LED strip
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Turn off all LEDs initially
}

void loop() {
  if (millis() - lastReadTime >= readInterval) {
    lastReadTime = millis();
    
    int16_t dist;

    if (tfmP.getData(dist)) { 
      Serial.print("Distance: ");  // displays to Serial Monitor for feedback
      Serial.print(dist);
      Serial.println(" cm");

      //  LED Color Logic
      if (dist > MAX_DISTANCE) {
        setAllLeds(strip.Color(0, 0, 0));            // off
      } 
      else if (dist < MIN_DISTANCE && dist != 0) {   // Distance cannot equal 0 for the red stage since 0 is returned when the sensor detects the windshield
        // Significant change detection, helps turn off LEDs after short time (keeps system automatic)
        int delta = abs(dist - lastDist);
        const int MIN_CHANGE = 3; // cm sensitivity threshold

        if (delta >= MIN_CHANGE) {
          lastChangeTime = millis();  // Only reset timer on real movement
          setAllLeds(strip.Color(255, 0, 0));        // red
        } 
        else if (millis() - lastChangeTime < parkedTimeout) {
          setAllLeds(strip.Color(255, 0, 0));        // stays red
        } 
        else {
          setAllLeds(strip.Color(0, 0, 0));          // Turn off if car stops moving (truly parked)
        }
      } 
      else if (dist < MID_DISTANCE || dist == 0) {   // When sensor detects the glass of the windshield (when the LED should be yellow), the distance returned is 0
        setAllLeds(strip.Color(255, 165, 0));        // orange (appears yellow)
      } 
      else {
        setAllLeds(strip.Color(0, 255, 0));          // green
      }

      lastDist = dist; // update distance after all logic for iteration
    } 
    else {
      Serial.print("Error: ");
      Serial.println(tfmP.status);
      setAllLeds(strip.Color(0, 0, 0)); // Turn off on error
    }
  }
}

void setAllLeds(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
