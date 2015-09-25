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

Effect effectType = GLOW;  // Effect
int rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 15;          // # pixel (> 1 and < NUMPIXELS - 1)
int areaOfEffect = 2;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long delay_ms = 20;   // millis
CRGB grey = CHSV{0, 255, 255};
bool looping = false;
bool dir = FORWARD;

uint8_t hueval = 0;

NeoPixelEffects effect = NeoPixelEffects(leds, effectType, rangeStart, rangeEnd, areaOfEffect, delay_ms, grey, looping, dir);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  grey.setHue(hueval);
  Serial.begin(9600);
}

void loop() {
  effect.update();
  if (effect.getEffect() == NONE) {
    hueval += 32;
    grey.setHue(hueval);
    effect.setColor(grey);
    effect.resetEffect();
    effect.setEffect(GLOW);
  }
  FastLED.show();
}
