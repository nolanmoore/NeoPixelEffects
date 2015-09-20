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

NeoPixelEffects::NeoPixelEffects(CRGB *ledset, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CHSV color_chsv, bool repeat, bool dir) :
  _pixset(ledset), _repeat(repeat), _direction(dir)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(color_chsv);
  initialize(effect);
}

NeoPixelEffects::NeoPixelEffects(CRGB *ledset, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, CRGB color_effectcolor, bool repeat, bool dir) :
  _pixset(ledset), _repeat(repeat), _direction(dir)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(color_effectcolor);
  initialize(effect);
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

void NeoPixelEffects::initialize(Effect effect)
{
  _effect = effect;
  _lastupdate = millis();
  if (_direction == FORWARD) {
    _pixcurrent = _pixstart;
  } else {
    _pixcurrent = _pixend;
  }
}

void NeoPixelEffects::update()
{
  if (_effect != NONE) {
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
          updateFadeEffect();
          break;
        case FILL:
          updateFillEffect();
          break;
        case EMPTY:
          updateEmptyEffect();
          break;
        case FIREWORK:
          updateFireworkEffect();
          break;
        default:
          break;
      }
      FastLED.show();
    }
  }
}

void NeoPixelEffects::updateCometEffect()
{
  CRGB tailcolor;

  for (int j = 0; j <= _pixaoe; j++) {
    float ratio = j / (float)_pixaoe;
    tailcolor.r = (int)(_effectcolor.r * ratio);
    tailcolor.g = (int)(_effectcolor.g * ratio);
    tailcolor.b = (int)(_effectcolor.b * ratio);

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
    tailcolor.r = (int)(_effectcolor.r * ratio);
    tailcolor.g = (int)(_effectcolor.g * ratio);
    tailcolor.b = (int)(_effectcolor.b * ratio);

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
  static int count = 0;

  float ratio = count / 100.0;
  pulsecolor.r = _effectcolor.r * ratio;
  pulsecolor.g = _effectcolor.g * ratio;
  pulsecolor.b = _effectcolor.b * ratio;

  if (_direction == FORWARD) {
    if (count >= 100) setDirection(REVERSE);
  } else {
    if (count <= 0) setDirection(FORWARD);
  }
  count = (_direction == FORWARD) ? count + 1 : count - 1;

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

void NeoPixelEffects::updateFadeEffect()
{
  // TODO use pointers for counters and other static vars like ratio instead of statics
  CRGB fadecolor;
  static int count = (_direction == FORWARD) ? 0 : 100;

  float ratio = count / 100.0;
  fadecolor.r = _effectcolor.r * ratio;
  fadecolor.g = _effectcolor.g * ratio;
  fadecolor.b = _effectcolor.b * ratio;

  if (_direction == FORWARD) {
    if (count >= 100) setEffect(NONE);
  } else {
    if (count <= 0) setEffect(NONE);
  }
  count = (_direction == FORWARD) ? count + 1 : count - 1;

  for (int i = _pixstart; i <= _pixend; i++) {
    _pixset[i] = fadecolor;
  }
}

void NeoPixelEffects::updateFillEffect()
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


void NeoPixelEffects::updateEmptyEffect()
{
  _pixset[_pixcurrent] = CRGB::Black;
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

void NeoPixelEffects::updateFireworkEffect()
{
  // Mortar
  int m_rangeStart = _pixstart;
  int m_rangeEnd = _pixend - _pixaoe - 4;
  int m_areaOfEffect = 2;
  unsigned long m_updateDelay = 25;   // millis
  CRGB grey = CRGB::White;

  // Stars parameters
  int stars_start = _pixend - 2 * _pixaoe - 4;
  int stars_center = _pixend - _pixaoe - 2;
  int stars_end = _pixend;
  int stars_aoe = _pixaoe;

  // Stars Fade parameters
  int sf_rangeStart = _pixend - 2 * _pixaoe - 4;
  int sf_rangeEnd = _pixend;
  unsigned long sf_updateDelay = 7;   // millis

  static NeoPixelEffects *m = new NeoPixelEffects(_pixset, COMET, m_rangeStart,   m_rangeEnd, m_areaOfEffect, m_updateDelay, grey, false, FORWARD);
  static NeoPixelEffects *s1 = new NeoPixelEffects(_pixset, NONE, stars_start,    stars_center, stars_aoe, _delay, _effectcolor, false, REVERSE);
  static NeoPixelEffects *s2 = new NeoPixelEffects(_pixset, NONE, stars_center,   stars_end, stars_aoe, _delay, _effectcolor, false, FORWARD);
  static NeoPixelEffects *sf = new NeoPixelEffects(_pixset, NONE, sf_rangeStart,  sf_rangeEnd, 1, sf_updateDelay, _effectcolor, false, REVERSE);

  static int justonce = 0;

  if (m->getEffect() != NONE) {
    m->update();
  } else {
    if (s1->getEffect() == NONE && s2->getEffect() == NONE) {
      if (justonce == 0) {
        delay(200);
        s1->initialize(FILL);
        s2->initialize(FILL);
        justonce = 1;
      } else if (justonce == 1) {
        delay(200);
        sf->initialize(FADE);
        justonce = 2;
      } else if (justonce == 2){
        sf->update();
        if (sf->getEffect() == NONE) {
          delete(m);
          delete(s1);
          delete(s2);
          delete(sf);
          setEffect(NONE);
        }
      }
    } else {
      s1->update();
      s2->update();
    }
  }
}

void NeoPixelEffects::setEffect(Effect effect)
{
  _effect = effect;
  NeoPixelEffects::update();
}

Effect NeoPixelEffects::getEffect()
{
  return _effect;
}

int NeoPixelEffects::setRange(int pixstart, int pixend)
{
  if (pixstart >= 0 && pixstart <= pixend && pixend < FastLED.size()) {
    _pixstart = pixstart;
    _pixend = pixend;
    _pixrange = _pixend - _pixstart + 1;
    return 1;
  } else {
    // Arguments out of range
    return 0;
  }
}

int NeoPixelEffects::setAreaOfEffect(int aoe)
{
  if (aoe > 0 && aoe <= _pixrange) {
    _pixaoe = aoe;
    return 1;
  } else {
    // Arguments out of range
    return 0;
  }
}

void NeoPixelEffects::setDelay(int delay_hz)
{
  if (delay_hz > 0) {
    _delay = (unsigned long)(1.0 / delay_hz * 1000);
  }
}

void NeoPixelEffects::setDelay(unsigned long delay_ms)
{
  _delay = delay_ms;
}

void NeoPixelEffects::setColor(int color_red, int color_green, int color_blue)
{
  if (color_red > -1 && color_green > -1 && color_blue > -1) {
    // TODO determine if better to set to value mod 255 than max at 255
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

void NeoPixelEffects::resetEffect()
{
  for (int i = _pixstart; i <= _pixend; i++) {
    _pixset[i] = CRGB::Black;
  }
}
