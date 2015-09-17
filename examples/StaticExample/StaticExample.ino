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

Effect effectType = STATIC;  // Effect
int rangeStart = 0;          // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 15;           // # pixel (> 1 and < NUMPIXELS - 1)
unsigned long updateDelay = 100;   // millis
bool looping = true;         // boolean value
bool dir = FORWARD;    // FORWARD (true) or REVERSE (false)
EffectColor grey = {75, 75, 75};

NeoPixelEffects effect = NeoPixelEffects(&pixels, effectType, rangeStart, rangeEnd, 1, updateDelay, grey, looping, dir);

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  effect.update();
}
