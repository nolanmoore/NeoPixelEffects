// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            A0
#define NUMPIXELS      144

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Effect effectType = PULSE;  // Effect
int rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 47;          // # pixel (> 1 and < NUMPIXELS - 1)
unsigned long updateDelay = 5;   // millis
int redValue = 200;           // 0 to 255
int greenValue = 75;       // 0 to 255
int blueValue = 0;          // 0 to 255
bool looping = true;        // boolean value
bool direction = FORWARD;    // FORWARD (true) or REVERSE (false)
EffectColor cyan = {0, 150, 150};

NeoPixelEffects pulseEffect = NeoPixelEffects(&pixels, effectType, rangeStart, rangeEnd, 1, updateDelay, cyan);

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  pulseEffect.update();
}
