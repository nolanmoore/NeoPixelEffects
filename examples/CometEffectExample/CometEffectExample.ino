// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A0

#define NUMPIXELS      144

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Effect effectType = COMET;  // Effect
int rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 47;          // # pixel (> 1 and < NUMPIXELS - 1)
int areaOfEffect = 10;       // # pixels (> 0 and < rangeEnd - rangeStart)
unsigned long updateDelay = 10;   // millis
int redValue = 200;           // 0 to 255
int greenValue = 75;       // 0 to 255
int blueValue = 0;          // 0 to 255
bool looping = true;        // boolean value
bool direction = FORWARD;    // FORWARD (true) or REVERSE (false)

EffectColor cyan = {0, 150, 150};
EffectColor magenta = {150, 0, 150};
EffectColor yellow = {150, 150, 0};

NeoPixelEffects effect1 = NeoPixelEffects(&pixels, effectType, rangeStart, rangeEnd, areaOfEffect, updateDelay, cyan);
NeoPixelEffects effect2 = NeoPixelEffects(&pixels, effectType, rangeStart + 48, rangeEnd + 48, areaOfEffect, updateDelay, magenta);
NeoPixelEffects effect3 = NeoPixelEffects(&pixels, effectType, rangeStart + 96, rangeEnd + 96, areaOfEffect, updateDelay, yellow);

//NeoPixelEffects effect4 = NeoPixelEffects(&pixels, effectType, rangeStart, rangeEnd, areaOfEffect, updateDelay, 150, 0, 0);
//NeoPixelEffects effect5 = NeoPixelEffects(&pixels, effectType, rangeStart + 48, rangeEnd + 48, areaOfEffect, updateDelay, 0, 150, 0);
//NeoPixelEffects effect6 = NeoPixelEffects(&pixels, effectType, rangeStart + 96, rangeEnd + 96, areaOfEffect, updateDelay, 0, 0, 150);


void setup() {
  pixels.begin();
  Serial.begin(9600);
//  effect4.setDirection(REVERSE);
//  effect5.setDirection(REVERSE);
//  effect6.setDirection(REVERSE);
}

void loop() {
  effect1.update();
  effect2.update();
  effect3.update();

//  effect4.update();
//  effect5.update();
//  effect6.update();
}
