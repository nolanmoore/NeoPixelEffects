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

// Mortar
Effect m_effectType = COMET;  // Effect
int m_rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int m_rangeEnd = 47;          // # pixel (> 1 and < NUMPIXELS - 1)
int m_areaOfEffect = 6;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long m_updateDelay = 25;   // millis
bool m_looping = false;        // boolean value
bool m_dir = FORWARD;    // FORWARD (true) or REVERSE (false)
EffectColor grey = {50, 50, 50};

// Sparks 1
Effect s1_effectType = NONE;  // Effect
int s1_rangeStart = 47;         // # pixel (> 0 and < NUMPIXELS - 2)
int s1_rangeEnd = 35;          // # pixel (> 1 and < NUMPIXELS - 1)
int s1_areaOfEffect = 6;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long s1_updateDelay = 25;   // millis
bool s1_looping = false;        // boolean value
bool s1_dir = REVERSE;    // FORWARD (true) or REVERSE (false)
EffectColor orange = {150, 100, 0};

// Sparks 2
Effect s2_effectType = NONE;  // Effect
int s2_rangeStart = 59;         // # pixel (> 0 and < NUMPIXELS - 2)
int s2_rangeEnd = 47;          // # pixel (> 1 and < NUMPIXELS - 1)
int s2_areaOfEffect = 6;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long s2_updateDelay = 25;   // millis
bool s2_looping = false;        // boolean value
bool s2_dir = FORWARD;    // FORWARD (true) or REVERSE (false)

NeoPixelEffects m = NeoPixelEffects(&pixels, m_effectType, m_rangeStart, m_rangeEnd, m_areaOfEffect, m_updateDelay, grey, m_looping, m_dir);
NeoPixelEffects s1 = NeoPixelEffects(&pixels, s1_effectType, s1_rangeStart, s1_rangeEnd, s1_areaOfEffect, s1_updateDelay, orange, s1_looping, s1_dir);
NeoPixelEffects s2 = NeoPixelEffects(&pixels, s2_effectType, s2_rangeStart, s2_rangeEnd, s2_areaOfEffect, s2_updateDelay, orange, s2_looping, s2_dir);

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  if (!m.getEffect() == NONE) {
    m.update()
  } else {
    
  }
}
