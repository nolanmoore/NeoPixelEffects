// NeoPixel Effects library Chase effect test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include "FastLED.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN            A0
#define NUM_LEDS      143

CRGB leds[NUM_LEDS];
CRGB color_val;

int hue = 0;

unsigned long delay_ms = 50;
bool dir = FORWARD;
bool state_e5 = true;
bool state_e6 = true;

NeoPixelEffects effects[9];

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  color_val.setHue(hue);
  effects[0] = NeoPixelEffects(leds, CHASE, 0, 15, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[1] = NeoPixelEffects(leds, COMET, 16, 31, 8, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[2] = NeoPixelEffects(leds, LARSON, 32, 47, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[3] = NeoPixelEffects(leds, PULSE, 48, 63, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[4] = NeoPixelEffects(leds, STATIC, 64, 79, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[5] = NeoPixelEffects(leds, FILLIN, 80, 95, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[6] = NeoPixelEffects(leds, FILLIN, 96, 111, 1, delay_ms, color_val, true, dir);
  hue += 32;
  color_val.setHue(hue);
  effects[7] = NeoPixelEffects(leds, NONE, 112, 127, 1, delay_ms, color_val, true, dir);
  effects[7].fill_gradient(color_val, CHSV(96, 255, 255));
  hue += 32;
  color_val.setHue(hue);
  effects[8] = NeoPixelEffects(leds, RAINBOWWAVE, 128, 142, 1, delay_ms, color_val, true, dir);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 9; i++) {
    if (i != 7) {
      effects[i].update();
    }
  }
  if (effects[5].getEffect() == NONE) {
    if (state_e5) {
      effects[5].setEffect(FADE);
    } else {
      effects[5].setEffect(FILLIN);
    }
    state_e5 = !state_e5;
  }

  if (effects[6].getEffect() == NONE) {
    if (state_e6) {
      effects[6].setColor(CHSV(64, 255, 255));
      effects[6].setEffect(FILLIN);
    } else {
      effects[6].setColor(CHSV(192, 255, 255));
      effects[6].setEffect(FILLIN);
    }
    state_e6 = !state_e6;
  }

  FastLED.show();
}
