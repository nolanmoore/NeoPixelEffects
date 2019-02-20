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
  NONE,
  COMET,
  LARSON,
  CHASE,
  PULSE,
  STATIC,
  FADE,
  FILLIN,
  GLOW,
  RAINBOWWAVE,
  STROBE,
  SINEWAVE,
  RANDOM,
  TALKING,
  TRIWAVE,
  // INVERSELARSON,	// Not currently implemented
  // FIREWORK,	// Not currently implemented
  // SPARKLEFILL,	// Not currently implemented
  NUM_EFFECT
};

enum EffectStatus {
  INACTIVE,
  ACTIVE,
  NUM_EFFECTSTATUS
};

class NeoPixelEffects {
  public:
    NeoPixelEffects(CRGB *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_crgb, bool looping, bool dir);
    NeoPixelEffects();
    ~NeoPixelEffects();

    void setEffect(Effect effect);  // Sets effect
    Effect getEffect();
    void setStatus(EffectStatus status);
    EffectStatus getStatus();
    void setColor(CRGB color_crgb);
    void setBackgroundColor(CRGB color_crgb);
    void setRange(int pixstart, int pixend);
    void setAreaOfEffect(int aoe);
    void setDelay(unsigned long delay_ms);
    void setDelayHz(int delay_hz);
    void setRepeat(bool repeat);
    void setDirection(bool direction);

    void update(); // Process effect
    void stop();
    void pause();
    void play();

    void clear();
    void fill_solid(CRGB color_crgb);
    void fill_gradient(CRGB color_crgb1, CRGB color_crgb2);

  private:
    void updateCometEffect(int subtype);
    void updateChaseEffect();
    void updatePulseEffect();
    void updateStaticEffect(int subtype);
    void updateFadeOutEffect();
    void updateFillInEffect();
    void updateSolidEffect();
    void updateGlowEffect();
    void updateRainbowWaveEffect();
    void updateStrobeEffect();
    void updateWaveEffect(int subtype);
    void updateTalkingEffect();
    // void initTalkingEffect();
    // void initTalkingEffect1(uint8_t &brightness_array, uint16_t &delay_array, uint8_t &maxb, uint8_t &minb, uint8_t &current_b);
    // void updateFireworkEffect();
    // void updateSparkleFillEffect();

    CRGB *_pixset;          // A reference to the one created in the user code
    CRGB _color_fg;
    CRGB _color_bg;
    Effect _effect;         // Your silly or awesome effect!
    EffectStatus _status;
    int
      _pixstart,            // First NeoPixel in range of effect
      _pixend,              // Last NeoPixel in range of effect
      _pixrange,            // Length of effect area
      _pixaoe,              // The length of the effect that takes place within the range
      _pixcurrent,          // Head pixel that indicates current pixel to base effect on
      _counter;
    uint8_t _subtype;          // Defines sub type to be used
    bool
      _repeat,              // Whether or not the effect loops in area
      _direction;           // Whether or not the effect moves from start to end pixel
    unsigned long
      _lastupdate,          // Last update time, in milliseconds since sys reboot
      _delay;               // Period at which effect should update, in milliseconds
};

#endif
