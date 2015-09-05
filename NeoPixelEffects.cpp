/*-------------------------------------------------------------------------
  Arduino library to provide a variety of effects when using Adafruit's
  NeoPixel library along with NeoPixels and other compatible hardware.
  This library is a work in progress and it's main purpose to help get
  my coding back on track after a long absence. Wish me luck!
  Written by Nolan Moore.
  -------------------------------------------------------------------------
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
  -------------------------------------------------------------------------*/

#include "NeoPixelEffects.h"

EffectColor::EffectColor(uint8_t r, uint8_t g, uint8_t b) {
  _r = r;
  _g = g;
  _b = b;
}

EffectColor::EffectColor(char color) {
  switch (color) {
    case COLOR_RED:
      _r = 255;
      _g = 0;
      _b = 0;
      break;
    case COLOR_YELLOW:
      _r = 255;
      _g = 255;
      _b = 0;
      break;
    case COLOR_GREEN:
      _r = 0;
      _g = 255;
      _b = 0;
      break;
    case COLOR_CYAN:
      _r = 0;
      _g = 255;
      _b = 255;
      break;
    case COLOR_BLUE:
      _r = 0;
      _g = 0;
      _b = 255;
      break;
    case COLOR_MAGENTA:
      _r = 255;
      _g = 0;
      _b = 255;
      break;
    case COLOR_WHITE:
      _r = 255;
      _g = 255;
      _b = 255;
      break;
    default:
      _r = 0;
      _g = 0;
      _b = 0;
  }
}

EffectColor::EffectColor(void) {
  EffectColor(COLOR_BLACK); // Initialize as black
}

EffectColor::~EffectColor() {
  // DESTROY nothing.
}

NeoPixelEffects::NeoPixelEffects(Adafruit_NeoPixel *pixelset, Effect effect, uint16_t range, EffectColor ec1, EffectColor ec2, EffectColor ec3) :
  _pix(pixelset), _effect(effect), _range(range), _effectcolor1(ec1), _effectcolor2(ec2), _effectcolor3(ec3)
{

}

NeoPixelEffects::NeoPixelEffects() :
  _effect(NONE), _range(0)
{
  _pix = new Adafruit_NeoPixel();
  _effectcolor1 = EffectColor();
  _effectcolor2 = EffectColor();
  _effectcolor3 = EffectColor();
}

NeoPixelEffects::~NeoPixelEffects() {
  *_pix = NULL;
}

int NeoPixelEffects::initializeEffect() {
  return 0;
}

int NeoPixelEffects::updateEffect() {
  switch (_effect) {
    case TRAIL:
      updateTrailEffect();
      break;
    default:
      int i = 0;
  }
  return 0;
}

int NeoPixelEffects::updateTrailEffect() {
  return 0;
}
void NeoPixelEffects::setEffect(Effect effect) {
  _effect = effect;
}
