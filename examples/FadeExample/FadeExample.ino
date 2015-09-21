// NeoPixel Effects library Chase effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN  A0
#define NUM_LEDS  16

CRGB leds[NUM_LEDS];

Effect effectType = FADE;  // Effect
int rangeStart = 0;         // # pixel (> 0 and < NUMPIXELS - 2)
int rangeEnd = 7;          // # pixel (> 1 and < NUMPIXELS - 1)
unsigned long delay_ms = 50;   // millis
CRGB hueval = CHSV{0, 255, 255};
bool looping = false;
bool dir = FORWARD;

int state = 0;

NeoPixelEffects effect = NeoPixelEffects(leds, FILL, rangeStart, rangeEnd, 1, delay_ms, hueval, looping, dir);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {
  if (state == 0 && effect.getEffect() == NONE) {
    effect.setEffect(FILL);
    effect.setRange(8, 15);
    effect.setColor(CHSV(127, 255, 255));
    state = 1;
  } else if (state == 1 && effect.getEffect() == NONE) {
    effect.setDirection(REVERSE);
    effect.setEffect(FADE);
    effect.setRange(0, 15);
    state = 2;
  }

  effect.update();
}
