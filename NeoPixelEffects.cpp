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

NeoPixelEffects::NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, int redvalue, int greenvalue, int bluevalue, bool looping, bool dir) :
  _pix(pix), _looping(looping), _direction(dir)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(redvalue, greenvalue, bluevalue);
  initialize(effect);
}

NeoPixelEffects::NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, EffectColor ec, bool looping, bool dir) :
  _pix(pix), _looping(looping), _direction(dir)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(ec);
  initialize(effect);
}

NeoPixelEffects::NeoPixelEffects()
{
  *_pix = NULL;
  _effect = NONE;
  _pixstart = 0;
  _pixend = 0;
  _pixrange = 1;
  _pixaoe = 1;
  _pixcurrent = _pixstart;
  _delay = 0;
  _lastupdate = 0;
  _effectcolor = {0, 0, 0};
  _looping = true;
  _direction = FORWARD;
}

NeoPixelEffects::~NeoPixelEffects()
{
  *_pix = NULL;
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
      _pix->show();
    }
  }
}

// void NeoPixelEffects::updateCometEffect()
// {
//   EffectColor tailcolor = {0, 0, 0};
//
//   for (int j = 0; j <= _pixaoe; j++) {
//     float ratio = j / (float)_pixaoe;
//     tailcolor.r = (int)(_effectcolor.r * ratio);
//     tailcolor.g = (int)(_effectcolor.g * ratio);
//     tailcolor.b = (int)(_effectcolor.b * ratio);
//
//     int tpx;
//     bool showpix = true;
//
//     if (_direction == FORWARD) {
//       if (_looping) {
//         if (tpx > _pixend) {
//           tpx = _pixstart + _pixcurrent + j - _pixend - 1;
//         } else {
//           tpx = _pixcurrent + j;
//         }
//       } else {
//         if (tpx > _pixend) {
//           showpix = false;
//         } else {
//           tpx = _pixcurrent + j;
//         }
//       }
//     } else {
//       if (_looping) {
//         if (tpx < _pixstart) {
//           tpx = _pixend + (_pixcurrent - j) - _pixstart + 1;
//         } else {
//           tpx = _pixcurrent - j;
//         }
//       } else {
//         if (tpx < _pixstart) {
//           showpix = false;
//         } else {
//           tpx = _pixcurrent - j;
//         }
//       }
//     }
//
//     if (showpix) {
//       _pix->setPixelColor(tpx, _pix->Color(tailcolor.r, tailcolor.g, tailcolor.b));
//     }
//   }
//
//   if (_direction == FORWARD) {
//     _pixcurrent = (_pixcurrent + 1 > _pixend && _looping == true) ? _pixstart : _pixcurrent + 1;
//     if (_pixcurrent == _pixstart && !_looping) {
//       setEffect(NONE);
//     }
//   } else {
//     _pixcurrent = (_pixcurrent - 1 < _pixstart && _looping == true) ? _pixend : _pixcurrent - 1;
//     if (_pixcurrent == _pixend && !_looping) {
//       setEffect(NONE);
//     }
//   }
// }

void NeoPixelEffects::updateCometEffect()
{
  EffectColor tailcolor = {0, 0, 0};

  for (int j = 0; j <= _pixaoe; j++) {
    float ratio = j / (float)_pixaoe;
    tailcolor.r = (int)(_effectcolor.r * ratio);
    tailcolor.g = (int)(_effectcolor.g * ratio);
    tailcolor.b = (int)(_effectcolor.b * ratio);

    int tpx;
    bool showpix = true;
    if (_direction == FORWARD) {
      if (_pixcurrent + j > _pixend) {
        if (_looping) {
          tpx = _pixstart + (_pixcurrent + j) - _pixend - 1;
        } else {
          showpix = false;
        }
      } else {
        tpx = _pixcurrent + j;
      }
    } else {
      if (_pixcurrent - j < _pixstart) {
        if (_looping) {
          tpx = _pixend - (abs(_pixstart - (_pixcurrent - j)) + 1);
        } else {
          showpix = false;
        }
      } else {
        tpx = _pixcurrent - j;
      }
    }

    if (showpix) {
      _pix->setPixelColor(tpx, _pix->Color(tailcolor.r, tailcolor.g, tailcolor.b));
    }
  }

  if (_direction == FORWARD) {
    if (_pixcurrent + 1 > _pixend) {
      if (_looping) {
        _pixcurrent = _pixstart;
      } else {
        setEffect(NONE);
      }
    } else {
      _pixcurrent++;
    }
  } else {
    if (_pixcurrent - 1 < _pixstart) {
      if (_looping) {
        _pixcurrent = _pixend;
      } else {
        setEffect(NONE);
      }
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
        _pix->setPixelColor(j, _pix->Color(_effectcolor.r, _effectcolor.g, _effectcolor.b));
      } else {
        _pix->setPixelColor(j, _pix->Color(0, 0, 0));
      }
    } else {
      if (j % 2 == 0) {
        _pix->setPixelColor(j, _pix->Color(0, 0, 0));
      } else {
        _pix->setPixelColor(j, _pix->Color(_effectcolor.r, _effectcolor.g, _effectcolor.b));
      }
    }
  }
  even = !even;
}

void NeoPixelEffects::updatePulseEffect()
{
  EffectColor pulsecolor;
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
    _pix->setPixelColor(i, _pix->Color(pulsecolor.r, pulsecolor.g, pulsecolor.b));
  }
}

void NeoPixelEffects::updateStaticEffect()
{
  static float redratio = _effectcolor.r / 100.0;
  static float greenratio = _effectcolor.g / 100.0;
  static float blueratio = _effectcolor.b / 100.0;

  for (int i = _pixstart; i <= _pixend; i++) {
    long randnum = random(101);
    _pix->setPixelColor(i, (uint8_t)(randnum * redratio), (uint8_t)(randnum * greenratio), (uint8_t)(randnum * blueratio));
  }
}

/*
 *  updateFadeEffect
 *  Does not utilize AOE, CURR, LOOP
 */

void NeoPixelEffects::updateFadeEffect()
{
  // TODO use pointers for counters and other static vars like ratio instead of statics
  EffectColor fadecolor;
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
    _pix->setPixelColor(i, _pix->Color(fadecolor.r, fadecolor.g, fadecolor.b));
  }

  // TODO Determine if we should change these private update functions to return ints
}

void NeoPixelEffects::updateFillEffect()
{
  _pix->setPixelColor(_pixcurrent, _pix->Color(_effectcolor.r, _effectcolor.g, _effectcolor.b));
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
  _pix->setPixelColor(_pixcurrent, _pix->Color(0, 0, 0));
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
  EffectColor grey = {2, 2, 2};

  // Stars parameters
  int stars_start = _pixend - 2 * _pixaoe - 4;
  int stars_center = _pixend - _pixaoe - 2;
  int stars_end = _pixend;
  int stars_aoe = _pixaoe;
  unsigned long stars_delay = 25;   // millis
  EffectColor stars_orange = _effectcolor;

  // Stars Fade parameters
  int sf_rangeStart = _pixend - 2 * _pixaoe - 4;
  int sf_rangeEnd = _pixend;
  unsigned long sf_updateDelay = 7;   // millis

  static NeoPixelEffects *m = new NeoPixelEffects(_pix, COMET, m_rangeStart, m_rangeEnd, m_areaOfEffect, m_updateDelay, grey, false, FORWARD);
  static NeoPixelEffects *s1 = new NeoPixelEffects(_pix, NONE, stars_start, stars_center, stars_aoe, stars_delay, stars_orange, false, REVERSE);
  static NeoPixelEffects *s2 = new NeoPixelEffects(_pix, NONE, stars_center, stars_end, stars_aoe, stars_delay, stars_orange, false, FORWARD);
  static NeoPixelEffects *sf = new NeoPixelEffects(_pix, NONE, sf_rangeStart, sf_rangeEnd, 1, sf_updateDelay, stars_orange, false, REVERSE);

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
  if (pixstart >= 0 && pixstart <= pixend && pixend < _pix->numPixels()) {
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

void NeoPixelEffects::setDelay(unsigned long updateDelay)
{
  _delay = updateDelay;
}

int NeoPixelEffects::setColor(int redvalue, int greenvalue, int bluevalue)
{
  if (redvalue > -1 && greenvalue > -1 && bluevalue > -1) {
    // TODO determine if better to set to value mod 255 than max at 255
    _effectcolor.r = (redvalue > 255) ? 255 : redvalue;
    _effectcolor.g = (greenvalue > 255) ? 255 : greenvalue;
    _effectcolor.b = (bluevalue > 255) ? 255 : bluevalue;
    return 1;
  } else {
    // Arguments out of range
    return 0;
  }
}

void NeoPixelEffects::setColor(EffectColor color)
{
  _effectcolor = color;
}

void NeoPixelEffects::setLooping(bool looping)
{
  _looping = looping;
}

void NeoPixelEffects::setDirection(bool dir)
{
  _direction = dir;
}

void NeoPixelEffects::resetEffect()
{
  for (int i = _pixstart; i <= _pixend; i++) {
    _pix->setPixelColor(i, _pix->Color(0,0,0));
  }
}

int NeoPixelEffects::getPixRemaining()
{
  if (_direction == FORWARD) {
    return (_pixend - _pixcurrent);
  } else {
    return (_pixcurrent - _pixstart);
  }
}
