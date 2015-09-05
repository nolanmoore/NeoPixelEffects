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

enum Effect {
  TRAIL,
  SPARKLE,
  RANDOM,
  NONE
};

class EffectColor {
  public:
    EffectColor(uint8_t r, uint8_t g, uint8_t b);
    EffectColor(char color);
    EffectColor(void);
    ~EffectColor();

  private:
    uint8_t 
      _r,  // Red value
      _g,  // Green value
      _b;  // Blue value
};

class NeoPixelEffects {
  public:
    NeoPixelEffects(Adafruit_NeoPixel *pixelset, Effect effect, uint16_t range, EffectColor ec1, EffectColor ec2, EffectColor ec3);
    NeoPixelEffects(void);
    ~NeoPixelEffects();

    int initializeEffect();
    int updateEffect();
    int updateTrailEffect();
    void setEffect(Effect effect);

  private:
    Adafruit_NeoPixel *_pix;  // A reference to the one created in the user code
    Effect _effect;           // Your silly or awesome effect
    uint16_t _range;          // Length of effect in pixels
    EffectColor
      _effectcolor1,          // Up to 3 colors used in the effects
      _effectcolor2,
      _effectcolor3;
};
