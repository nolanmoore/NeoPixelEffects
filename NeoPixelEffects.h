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

#include <FastLED.h>

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#define FORWARD true
#define REVERSE false

enum Effect {
  COMET,
  LARSON,
  CHASE,
  PULSE,
  STATIC,
  FADE,
  FILL,
  EMPTY,
  FIREWORK,
  NONE
};

enum EffectStatus {
  ACTIVE,
  PAUSED,
  INACTIVE
};

class NeoPixelEffects {
  public:
    NeoPixelEffects(CRGB *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_crgb, bool looping, bool dir);
    NeoPixelEffects(CRGB *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CHSV color_chsv, bool looping, bool dir);
    NeoPixelEffects();
    ~NeoPixelEffects();

    void initialize(Effect effect); // Initializes effect
    void update(); // Process effect
    Effect getEffect();
    void setEffect(Effect effect);  // Sets effect
    EffectStatus getStatus();
    void setStatus(EffectStatus status);
    void setColor(int color_red, int color_green, int color_blue);
    void setColor(CRGB color_crgb);
    int setRange(int pixstart, int pixend);
    int setAreaOfEffect(int aoe);
    void setDelay(unsigned long delay_ms);
    void setDelay(int delay_hz);
    void setRepeat(bool repeat);
    void setDirection(bool direction);
    void resetEffect();
    // void transferPixels(CRGB *newpixelset);

  private:
    void updateCometEffect();
    void updateLarsonEffect();
    void updateChaseEffect();
    void updatePulseEffect();
    void updateStaticEffect();
    void updateFadeEffect();
    void updateFillEffect();
    void updateEmptyEffect();
    void updateFireworkEffect();

    CRGB *_pixset;  // A reference to the one created in the user code TODO is this needed?
    Effect _effect;           // Your silly or awesome effect!
    EffectStatus _status;
    CRGB _effectcolor;           // Up to 2 colors used in the effects, refer to struct
    int
      _pixstart,              // First NeoPixel in range of effect
      _pixend,                // Last NeoPixel in range of effect
      _pixrange,              // Length of effect area
      _pixaoe,                // The length of the effect that takes place within the range
      _pixcurrent;
    bool
      _repeat,               // Whether or not the effect loops in area
      _direction;               // Whether or not the effect moves from start to end pixel
    unsigned long
      _lastupdate,            // Last update time, in milliseconds since sys reboot
      _delay;                 // Period at which effect should update, in milliseconds
};

#endif
