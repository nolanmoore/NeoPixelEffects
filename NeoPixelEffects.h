/*--------------------------------------------------------------------
  This file is part of the NeoPixel Effects library.
  NeoPixel is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.
  NeoPixel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with NeoPixel.  If not, see
  <http://www.gnu.org/licenses/>.
  --------------------------------------------------------------------*/

#ifndef NEOPIXELEFFECTS_H
#define NEOPIXELEFFECTS_H

#include <Adafruit_NeoPixel.h>

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#define COLOR_RED      'R'
#define COLOR_YELLOW   'Y'
#define COLOR_GREEN    'G'
#define COLOR_CYAN     'C'
#define COLOR_BLUE     'B'
#define COLOR_MAGENTA  'M'
#define COLOR_WHITE    'W'
#define COLOR_BLACK    '0'
#define COLOR_CUSTOM   'X'

#define FORWARD true
#define REVERSE false

enum Effect {
  COMET,
  CHASE,
  PULSE,
  STATIC,
  FADE,
  FILL,
  EMPTY,
  NONE
};

struct EffectColor {
  int r;
  int g;
  int b;
};

class NeoPixelEffects {
  public:
    NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, int redvalue, int greenvalue, int bluevalue, bool dir, bool looping);
    NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, EffectColor ec, bool dir, bool looping);
    NeoPixelEffects();
    ~NeoPixelEffects();

    void initialize(Effect effect); // Initializes effect
    void update(); // Process effect
    void setEffect(Effect effect);  // Sets effect
    Effect getEffect();
    int setColor(int redvalue, int greenvalue, int bluevalue);
    void setColor(EffectColor ec);
    int setRange(int pixstart, int pixend);
    int setAreaOfEffect(int aoe);
    void setDelay(unsigned long delay);
    void setLooping(bool looping);
    void setDirection(bool dir);
    void resetEffect();
    // void transferPixels(Adafruit_NeoPixel *newpixelset);

  private:
    void updateCometEffect();
    void updateChaseEffect();
    void updatePulseEffect();
    void updateStaticEffect();
    void updateFadeEffect();
    void updateFillEffect();
    void updateEmptyEffect();

    Adafruit_NeoPixel *_pix;  // A reference to the one created in the user code TODO is this needed?
    Effect _effect;           // Your silly or awesome effect!
    int
      _pixstart,              // First NeoPixel in range of effect
      _pixend,                // Last NeoPixel in range of effect
      _pixrange,              // Length of effect area
      _pixaoe,                // The length of the effect that takes place within the range
      _pixcurrent;
    bool
      _looping,               // Whether or not the effect loops in area
      _direction;               // Whether or not the effect moves from start to end pixel
    unsigned long
      _lastupdate,            // Last update time, in milliseconds since sys reboot
      _delay;                 // Period at which effect should update, in milliseconds
    EffectColor
      _effectcolor;           // Up to 2 colors used in the effects, refer to struct
};

#endif
