// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN            A0
#define NUM_LEDS            32

CRGB leds[NUM_LEDS];

Effect effectType = SPARKLETRAIL;  // Effect
int rangeStart = 0;          // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = NUM_LEDS - 1;           // # pixel (> 1 and < NUMPIXELS - 1)
unsigned long updateDelay = 250;   // millis
CRGB grey = CRGB(75, 75, 75);

NeoPixelEffects effect = NeoPixelEffects(leds, effectType, rangeStart, rangeEnd, 1, updateDelay, grey, true, true);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  effect.update();
  FastLED.show();
}
