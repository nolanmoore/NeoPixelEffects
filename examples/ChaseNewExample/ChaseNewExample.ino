// NeoPixel Effects library Chase effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN            A0
#define NUM_LEDS      144

CRGB leds[NUM_LEDS];

Effect effectType = LARSON;  // Effect
int rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 31;          // # pixel (> 1 and < NUMPIXELS - 1)
int areaOfEffect = 1;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long delay_ms = 30;   // millis
int delay_hz = 4;
CRGB grey = 0xFF0000;
bool looping = true;
bool dir = FORWARD;

NeoPixelEffects effect = NeoPixelEffects(leds, effectType, rangeStart, rangeEnd, areaOfEffect, delay_ms, grey, looping, dir);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  effect.update();
}
