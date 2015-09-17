// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            A0
#define NUMPIXELS      144

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Firework parameters - currently unable to modify mortar params
Effect effectType = FIREWORK; // Effect
int rangeStart = 0;
int rangeEnd = 61;
int stars_aoe = 7;
unsigned long updateDelay = 25; // millis
bool m_looping = false;         // Currently unused, auto-noloop
bool m_dir = FORWARD;           // Currently unused, auto-forward
EffectColor stars_orange = {200, 133, 0};

NeoPixelEffects fw = NeoPixelEffects(&pixels, effectType, rangeStart, rangeEnd, stars_aoe, updateDelay, stars_orange, m_looping, m_dir);

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  fw.update();
}
