// NeoPixel Effects library Chase effect test (c) 2015 Nolan Moore
// released under the GPLv3 license

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN            A0
#define NUM_LEDS      144

CRGB leds[NUM_LEDS];

Effect effectType = CHASE;
int rangeStart = 0;
int rangeEnd = 31;
unsigned long delay_ms = 500;
CRGB grey = 0xFF0000;

NeoPixelEffects effect = NeoPixelEffects(leds, effectType, rangeStart, rangeEnd, 1, delay_ms, grey, true, true);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  effect.update();
  FastLED.show();
}
