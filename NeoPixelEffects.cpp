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

#include <NeoPixelEffects.h>

NeoPixelEffects::NeoPixelEffects(CRGB *ledset, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_crgb, bool repeat, bool dir) :
  _pixset(ledset), _effectcolor(color_crgb), _repeat(repeat), _direction(dir), _counter(0)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setEffect(effect);
}

NeoPixelEffects::NeoPixelEffects()
{
  *_pixset = NULL;
  _effect = NONE;
  _status = INACTIVE;
  _pixstart = 0;
  _pixend = 0;
  _pixrange = 1;
  _pixaoe = 1;
  _pixcurrent = _pixstart;
  _counter = 0;
  _delay = 0;
  _lastupdate = 0;
  _effectcolor = CRGB::Black;
  _repeat = true;
  _direction = FORWARD;
}

NeoPixelEffects::~NeoPixelEffects()
{
  *_pixset = NULL;
}

void NeoPixelEffects::setEffect(Effect effect)
{
  _effect = effect;
  _lastupdate = millis();
  if (_direction == FORWARD) {
    _pixcurrent = _pixstart;
    _counter = 0;
  } else {
    _pixcurrent = _pixend;
    _counter = 100;
  }
}

void NeoPixelEffects::update()
{
  if (_effect != NONE || _status == ACTIVE) {
    unsigned long timenow = millis();
    if (timenow - _lastupdate > _delay) {
      _lastupdate = timenow;
      switch (_effect) {
        case COMET:
          updateCometEffect();
          break;
        case LARSON:
          updateLarsonEffect();
          break;
        case CHASE:
          updateChaseEffect();
          break;
        case PULSE:
          updatePulseEffect();
          break;
        case STATIC:
          updateStaticEffect();
          break;
        case FADE:
          updateFadeOutEffect();
          break;
        case FILLIN:
          updateFillInEffect();
          break;
        case GLOW:
          updateGlowEffect();
          break;
        case FIREWORK:
          updateFireworkEffect();
          break;
        case SPARKLEFILL:
          updateSparkleFillEffect();
          break;
        case RAINBOWWAVE:
          updateRainbowWaveEffect();
          break;
        default:
          break;
      }
    }
  }
}

void NeoPixelEffects::updateCometEffect()
{
  CRGB tailcolor;

  for (int j = 0; j <= _pixaoe; j++) {
    float ratio = j / (float)_pixaoe;
    tailcolor.r = (uint8_t)(_effectcolor.r * ratio);
    tailcolor.g = (uint8_t)(_effectcolor.g * ratio);
    tailcolor.b = (uint8_t)(_effectcolor.b * ratio);

    int tpx;
    bool showpix = true;
    if (_direction == FORWARD) {
      if (_pixcurrent + j > _pixend) {
        if (_repeat) {
          tpx = _pixstart + (_pixcurrent + j) - _pixend - 1;
        } else {
          showpix = false;
        }
      } else {
        tpx = _pixcurrent + j;
      }
    } else {
      if (_pixcurrent - j < _pixstart) {
        if (_repeat) {
          tpx = _pixend - (abs(_pixstart - (_pixcurrent - j)) + 1);
        } else {
          showpix = false;
        }
      } else {
        tpx = _pixcurrent - j;
      }
    }

    if (showpix) {
      _pixset[tpx] = tailcolor;
    }
  }

  if (_direction == FORWARD) {
    if (_pixcurrent + 1 > _pixend) {
      if (_repeat) {
        _pixcurrent = _pixstart;
      } else {
        setEffect(NONE);
      }
    } else {
      _pixcurrent++;
    }
  } else {
    if (_pixcurrent - 1 < _pixstart) {
      if (_repeat) {
        _pixcurrent = _pixend;
      } else {
        setEffect(NONE);
      }
    } else {
      _pixcurrent--;
    }
  }
}

void NeoPixelEffects::updateLarsonEffect()
{
  CRGB tailcolor = CRGB::Black;

  for (int j = 0; j <= _pixaoe; j++) {
    float ratio = j / (float)_pixaoe;
    tailcolor.r = _effectcolor.r * ratio;
    tailcolor.g = _effectcolor.g * ratio;
    tailcolor.b = _effectcolor.b * ratio;

    int tpx;
    bool showpix = true;
    if (_direction == FORWARD) {
      if (_pixcurrent + j > _pixend) {
        showpix = false;
        // _pixaoe--;
      } else {
        tpx = _pixcurrent + j;
      }
    } else {
      if (_pixcurrent - j < _pixstart) {
        showpix = false;
        // _pixaoe--;
      } else {
        tpx = _pixcurrent - j;
      }
    }

    if (showpix) {
      _pixset[tpx] = tailcolor;
    }
  }

  if (_direction == FORWARD) {
    if (_pixcurrent + 1 > _pixend) {
      setDirection(REVERSE);
    } else {
      _pixcurrent++;
    }
  } else {
    if (_pixcurrent - 1 < _pixstart) {
      setDirection(FORWARD);
    } else {
      _pixcurrent--;
    }
  }
}

void NeoPixelEffects::updateChaseEffect()
{
  static bool even = true;
  for (int j = _pixstart; j <= _pixend; j++) {
    if (even) {
      if (j % 2 == 0) {
        _pixset[j] = _effectcolor;
      } else {
        _pixset[j] = CRGB::Black;
      }
    } else {
      if (j % 2 == 0) {
        _pixset[j] = CRGB::Black;
      } else {
        _pixset[j] = _effectcolor;
      }
    }
  }
  even = !even;
}

void NeoPixelEffects::updatePulseEffect()
{
  CRGB pulsecolor;

  float ratio = _counter / 100.0;
  pulsecolor.r = _effectcolor.r * ratio;
  pulsecolor.g = _effectcolor.g * ratio;
  pulsecolor.b = _effectcolor.b * ratio;

  if (_direction == FORWARD) {
    _counter++;
    if (_counter >= 100) setDirection(REVERSE);
  } else {
    _counter--;
    if (_counter <= 0) setDirection(FORWARD);
  }

  for (int i = _pixstart; i <= _pixend; i++) {
    _pixset[i] = pulsecolor;
  }
}

void NeoPixelEffects::updateStaticEffect()
{
  random16_add_entropy(random());
  CRGB staticcolor;
  for (int i = _pixstart; i <= _pixend; i++) {
    float random_ratio = random8(101) / 100.0;
    _pixset[i].setRGB(_effectcolor.r * random_ratio, _effectcolor.g * random_ratio, _effectcolor.b * random_ratio);
  }
}

/*
 *  updateFadeEffect
 *  Does not utilize AOE, CURR, LOOP
 */

// void NeoPixelEffects::updateFadeEffect()
// {
//   // TODO use pointers for counters and other static vars like ratio instead of statics
//   CRGB fadecolor;
//   static int count = (_direction == FORWARD) ? 0 : 100;
//
//   float ratio = count / 100.0;
//   fadecolor.r = _effectcolor.r * ratio;
//   fadecolor.g = _effectcolor.g * ratio;
//   fadecolor.b = _effectcolor.b * ratio;
//
//   if (_direction == FORWARD) {
//     count++;
//     if (count >= 100) setEffect(NONE);
//   } else {
//     count--;
//     if (count <= 0) setEffect(NONE);
//   }
//
//   for (int i = _pixstart; i <= _pixend; i++) {
//     _pixset[i] = fadecolor;
//   }
// }

void NeoPixelEffects::updateFadeOutEffect()
{
  // TODO use pointers for counters and other static vars like ratio instead of statics
  CRGB fadecolor;

  float ratio = _counter / 100.0;

  if (_counter <= 0) {
    _counter = 100;
    setEffect(NONE);
  } else {
    _counter--;
  }

  for (int i = _pixstart; i <= _pixend; i++) {
    fadecolor.r = _pixset[i].r * ratio;
    fadecolor.g = _pixset[i].g * ratio;
    fadecolor.b = _pixset[i].b * ratio;
    _pixset[i] = fadecolor;
  }
}

void NeoPixelEffects::updateFillInEffect()
{
  _pixset[_pixcurrent] = _effectcolor;
  if (_direction == FORWARD) {
    if (_pixcurrent != _pixend) {
      _pixcurrent++;
    } else {
      setEffect(NONE);
    }
  } else {
    if (_pixcurrent != _pixstart) {
      _pixcurrent--;
    } else {
      setEffect(NONE);
    }
  }
}

void NeoPixelEffects::updateGlowEffect()
{
  CRGB glowcolor;

  float ratio = _counter / 100.0;
  glowcolor.r = _effectcolor.r * ratio;
  glowcolor.g = _effectcolor.g * ratio;
  glowcolor.b = _effectcolor.b * ratio;

  if (_direction == FORWARD) {
    _counter++;
    if (_counter >= 100) setDirection(REVERSE);
  } else {
    _counter--;
    if (_counter <= 0) {
      setDirection(FORWARD);
      if (!_repeat) {
        setEffect(NONE);
      }
    }
  }

  int glow_area_half = (_pixrange - _pixaoe) / 2;
  for (int i = 0; i < glow_area_half ; i++) {
    _pixset[i].r = glowcolor.r * i / glow_area_half;
    _pixset[i].g = glowcolor.g * i / glow_area_half;
    _pixset[i].b = glowcolor.b * i / glow_area_half;
  }
  _pixset[_pixstart + glow_area_half] = glowcolor;
  _pixset[_pixstart + glow_area_half + 1] = glowcolor;
  for (int i = glow_area_half - 1; i >= 0 ; i--) {
    _pixset[_pixend - i].r = glowcolor.r * i / glow_area_half;
    _pixset[_pixend - i].g = glowcolor.g * i / glow_area_half;
    _pixset[_pixend - i].b = glowcolor.b * i / glow_area_half;
  }
}

void NeoPixelEffects::updateFireworkEffect()
{
  // static NeoPixelEffects *m = new NeoPixelEffects(_pixset, COMET, _pixstart,                  _pixend - _pixaoe - 4, 2,         25,     CRGB::White,  false, FORWARD);
  // static NeoPixelEffects *s1 = new NeoPixelEffects(_pixset, NONE, _pixend - 2 * _pixaoe - 4,  _pixend - _pixaoe - 2, stars_aoe, _delay, _effectcolor, false, REVERSE);
  // static NeoPixelEffects *s2 = new NeoPixelEffects(_pixset, NONE, _pixend - _pixaoe - 2,      stars_end,             stars_aoe, _delay, _effectcolor, false, FORWARD);
  // static NeoPixelEffects *sf = new NeoPixelEffects(_pixset, NONE, _pixend - 2 * _pixaoe - 4,  _pixend,               1,         7,      _effectcolor, false, REVERSE);
  //
  // if (_counter == 0 && m->getEffect() == NONE) {
  //   delay(200);
  //   s1->setEffect(FILLIN);
  //   s2->setEffect(FILLIN);
  //   _counter = 1;
  // } else if (_counter == 1 && s1->getEffect() == NONE && s2->getEffect() == NONE) {
  //   delay(200);
  //   sf->setEffect(FADE);
  //   _counter = 2;
  // } else if (_counter == 2 && sf->getEffect() == NONE) {
  //   delete(m);
  //   delete(s1);
  //   delete(s2);
  //   delete(sf);
  //   setEffect(NONE);
  // }
  //
  // m->update();
  // s1->update();
  // s2->update();
  // sf->update();
}

void NeoPixelEffects::updateSparkleFillEffect()
{
  static NeoPixelEffects *sparkles = new NeoPixelEffects(_pixset, STATIC, _pixstart,  _pixstart, 1, _delay, _effectcolor, false, _direction);

  sparkles->update();
  if (_pixcurrent != _pixend) {
    _pixcurrent++;
    sparkles->setRange(_pixstart, _pixcurrent);
  }
}

void NeoPixelEffects::updateRainbowWaveEffect()
{
  static uint8_t hueval = 0;
  static float ratio = 255.0  / _pixrange;

  for (int i = _pixstart; i < _pixend; i++) {
    CRGB color = CHSV((uint8_t)((hueval + i) * ratio), 255, 255);
    _pixset[i] = color;
  }
  hueval++;
}

Effect NeoPixelEffects::getEffect()
{
  return _effect;
}

void NeoPixelEffects::setRange(int pixstart, int pixend)
{
  if (pixstart >= 0 && pixstart <= pixend) {
    _pixstart = pixstart;
    _pixend = pixend;
    _pixrange = _pixend - _pixstart + 1;
  }
  if (_direction == FORWARD) {
    _pixcurrent = _pixstart;
  } else {
    _pixcurrent = _pixend;
  }
}

void NeoPixelEffects::setAreaOfEffect(int aoe)
{
  if (aoe > 0 && aoe <= _pixrange) {
    _pixaoe = aoe;
  }
}

void NeoPixelEffects::setDelayHz(int delay_hz)
{
  if (delay_hz > 0) {
    _delay = (unsigned long)(1.0 / delay_hz * 1000);
  }
}

void NeoPixelEffects::setDelay(unsigned long delay_ms)
{
  _delay = delay_ms;
}

void NeoPixelEffects::setColorRGB(uint8_t color_red, uint8_t color_green, uint8_t color_blue)
{
  if (color_red > -1 && color_green > -1 && color_blue > -1) {
    _effectcolor.r = (color_red > 255) ? 255 : color_red;
    _effectcolor.g = (color_green > 255) ? 255 : color_green;
    _effectcolor.b = (color_blue > 255) ? 255 : color_blue;
  }
}

void NeoPixelEffects::setColor(CRGB color_crgb)
{
  _effectcolor = color_crgb;
}

void NeoPixelEffects::setStatus(EffectStatus status)
{
  _status = status;
}

void NeoPixelEffects::setRepeat(bool repeat)
{
  _repeat = repeat;
}

void NeoPixelEffects::setDirection(bool direction)
{
  _direction = direction;
}

void NeoPixelEffects::clear()
{
  for (int i = _pixstart; i <= _pixend; i++) {
    _pixset[i] = CRGB::Black;
  }
  setEffect(NONE);
  setStatus(INACTIVE);
}

void NeoPixelEffects::fill_solid(CRGB color_crgb)
{
  if (_effect == NONE || _status == INACTIVE) {
    for (int i = _pixstart; i <= _pixend; i++) {
      _pixset[i] = color_crgb;
    }
  }
}

void NeoPixelEffects::fill_gradient(CRGB color_crgb1, CRGB color_crgb2)
{
  if (_effect == NONE || _status == INACTIVE) {
    int delta_red = color_crgb1.r - color_crgb2.r;
    int delta_green = color_crgb1.g - color_crgb2.g;
    int delta_blue = color_crgb1.b - color_crgb2.b;

    for (int i = _pixstart; i <= _pixend; i++) {
      float part = (float)(i - _pixstart) / _pixrange;
      uint8_t grad_red = color_crgb1.r - (delta_red * part);
      uint8_t grad_green = color_crgb1.g - (delta_green * part);
      uint8_t grad_blue = color_crgb1.b - (delta_blue * part);
      _pixset[i] = CRGB(grad_red, grad_green, grad_blue);
    }
  }
}
