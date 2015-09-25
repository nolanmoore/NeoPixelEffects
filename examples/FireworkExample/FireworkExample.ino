// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN            A0
#define NUM_LEDS       64

CRGB leds[NUM_LEDS];

// Firework stars parameters - currently unable to modify mortar params
Effect effectType = FIREWORK; // Effect
int rangeStart = 0;
int rangeEnd = NUM_LEDS - 1;
int stars_aoe = 7;
unsigned long updateDelay = 25; // millis
bool m_looping = false;         // Currently unused, auto-noloop
bool m_dir = FORWARD;           // Currently unused, auto-forward
CRGB stars_orange = CRGB{200, 133, 0};

NeoPixelEffects fw = NeoPixelEffects(leds, effectType, rangeStart, rangeEnd, stars_aoe, updateDelay, stars_orange, m_looping, m_dir);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  fw.update();
  FastLED.show();
}
