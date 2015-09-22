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
  // FIREWORK,
  // SPARKLEFILL,
  RAINBOWWAVE,
  // STROBE,
  INVERSELARSON,
  NUM_EFFECT
};

enum EffectStatus {
  ACTIVE,
  PAUSED,
  INACTIVE,
  NUM_EFFECTSTATUS
};

class NeoPixelEffects {
  public:
    NeoPixelEffects(CRGB *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_crgb, bool looping, bool dir);
    NeoPixelEffects();
    ~NeoPixelEffects();

    void initialize(Effect effect); // Initializes effect
    void update(); // Process effect
    Effect getEffect();
    void setEffect(Effect effect);  // Sets effect
    EffectStatus getStatus();
    void setStatus(EffectStatus status);
    void setColorRGB(uint8_t color_red, uint8_t color_green, uint8_t color_blue);
    void setColor(CRGB color_crgb);
    void setRange(int pixstart, int pixend);
    void setAreaOfEffect(int aoe);
    void setDelay(unsigned long delay_ms);
    void setDelayHz(int delay_hz);
    void setRepeat(bool repeat);
    void setDirection(bool direction);

    void clear();
    void fill_solid(CRGB color_crgb);
    void fill_gradient(CRGB color_crgb1, CRGB color_crgb2);

  private:
    void updateCometEffect();
    void updateLarsonEffect();
    void updateChaseEffect();
    void updatePulseEffect();
    void updateStaticEffect();
    void updateFadeOutEffect();
    void updateFillInEffect();
    void updateSolidEffect();
    void updateGlowEffect();
    // void updateFireworkEffect();
    // void updateSparkleFillEffect();
    void updateRainbowWaveEffect();
    // void updateStrobeEffect();

    // AssociatedEffects* createAssocEffect(CRGB pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_crgb, bool looping, bool dir);

    CRGB *_pixset;          // A reference to the one created in the user code
    Effect _effect;         // Your silly or awesome effect!
    EffectStatus _status;
    CRGB _effectcolor;      // Up to 2 colors used in the effects, refer to struct
    int
      _pixstart,            // First NeoPixel in range of effect
      _pixend,              // Last NeoPixel in range of effect
      _pixrange,            // Length of effect area
      _pixaoe,              // The length of the effect that takes place within the range
      _pixcurrent,          // Head pixel that indicates current pixel to base effect on
      _counter,
      _type;
    bool
      _repeat,              // Whether or not the effect loops in area
      _direction;           // Whether or not the effect moves from start to end pixel
    unsigned long
      _lastupdate,          // Last update time, in milliseconds since sys reboot
      _delay;               // Period at which effect should update, in milliseconds
    // AssociatedEffects *assoc_effects;
    // AssociatedEffects *aeptr;
};

// struct AssociatedEffects {
//   NeoPixelEffects effect;
//   AssociatedEffects *next;
// };

#endif
