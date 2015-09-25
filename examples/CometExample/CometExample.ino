// NeoPixel Effects library Comet effect test (c) 2015 Nolan Moore
// released under the GPLv3 license

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN      A0
#define NUM_LEDS      144

CRGB leds[NUM_LEDS];

Effect effect_type = COMET;
int aoe = 8;
unsigned long delay_ms = 25;
bool set_repeat = true;
bool set_direction = FORWARD;

int effect1_start = 0;
int effect1_end = 47;

int effect2_start = 48;
int effect2_end = 95;

int effect3_start = 96;
int effect3_end = 143;

NeoPixelEffects effect1 = NeoPixelEffects(leds, effect_type, effect1_start, effect1_end, aoe, delay_ms, CRGB::Magenta, set_repeat, set_direction);
NeoPixelEffects effect2 = NeoPixelEffects(leds, effect_type, effect2_start, effect2_end, aoe, delay_ms, CRGB::Yellow, set_repeat, set_direction);
NeoPixelEffects effect3 = NeoPixelEffects(leds, effect_type, effect3_start, effect3_end, aoe, delay_ms, CRGB::Cyan, set_repeat, set_direction);

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  effect1.update();
  effect2.update();
  effect3.update();
  FastLED.show();
}
