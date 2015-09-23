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
  _pixset(ledset), _color_fg(color_crgb), _color_bg(CRGB::Black), _repeat(repeat), _direction(dir), _counter(0), _subtype(0)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setEffect(effect);
  // *assoc_effects = NULL;
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
  _subtype = 0;
  _delay = 0;
  _lastupdate = 0;
  _color_fg = CRGB::Black;
  _color_bg = CRGB::Black;
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
  if (_direction == FORWARD) {
    _pixcurrent = _pixstart;
    _counter = 0;
  } else {
    _pixcurrent = _pixend;
    _counter = 100;
  }
  _lastupdate = 0;
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
        // case FIREWORK:
        //   updateFireworkEffect();
        //   break;
        // case SPARKLEFILL:
        //   updateSparkleFillEffect();
        //   break;
        case RAINBOWWAVE:
          updateRainbowWaveEffect();
          break;
        case STROBE:
          updateStrobeEffect();
          break;
        case SINEWAVE:
          updateSineWaveEffect(0);
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
    tailcolor.r = _color_fg.r * ratio;
    tailcolor.g = _color_fg.g * ratio;
    tailcolor.b = _color_fg.b * ratio;

    int tpx;
    bool showpix = true;
    if (_direction == FORWARD) {
      tpx = _pixcurrent + j;
      if (tpx > _pixend) {
        if (_repeat) {
          tpx = _pixcurrent + j - _pixrange + 1;
        } else {
          showpix = false;
        }
      }
    } else {
      tpx = _pixcurrent - j;
      if (tpx < _pixstart) {
        if (_repeat) {
          tpx = _pixcurrent - j + _pixrange;
        } else {
          showpix = false;
        }
      }
    }

    if (showpix) {
      _pixset[tpx] = tailcolor;
    }
  }

  if (_direction == FORWARD) {
    if (_pixcurrent == _pixend) {
      if (_repeat) {
        _pixcurrent = _pixstart;
      } else {
        setEffect(NONE);
        setStatus(INACTIVE);
      }
    } else {
      _pixcurrent++;
    }
  } else {
    if (_pixcurrent == _pixstart) {
      if (_repeat) {
        _pixcurrent = _pixend;
      } else {
        setEffect(NONE);
        setStatus(INACTIVE);
      }
    } else {
      _pixcurrent--;
    }
  }
}

void NeoPixelEffects::updateLarsonEffect()
{
  CRGB tailcolor;

  for (int j = 0; j <= _pixaoe; j++) {
    float ratio = j / (float)_pixaoe;
    tailcolor.r = _color_fg.r * ratio;
    tailcolor.g = _color_fg.g * ratio;
    tailcolor.b = _color_fg.b * ratio;

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
    if (_pixcurrent == _pixend) {
      setDirection(REVERSE);
    } else {
      _pixcurrent++;
    }
  } else {
    if (_pixcurrent == _pixstart) {
      setDirection(FORWARD);
    } else {
      _pixcurrent--;
    }
  }
}

void NeoPixelEffects::updateChaseEffect()
{
  for (int j = _pixstart; j <= _pixend; j++) {
    if (_counter % 2 == 0) {
      if (j % 2 == 0) {
        // TODO show foreground color
        _pixset[j] = _color_fg;
      } else {
        // TODO show background color
        _pixset[j] = _color_bg;
      }
    } else {
      if (j % 2 == 0) {
        // TODO show background color
        _pixset[j] = _color_bg;
      } else {
        // TODO show foreground color
        _pixset[j] = _color_fg;
      }
    }
  }
  _counter++;
}

void NeoPixelEffects::updatePulseEffect()
{
  CRGB pulsecolor;

  float ratio = _counter / 100.0;
  pulsecolor.r = _color_fg.r * ratio;
  pulsecolor.g = _color_fg.g * ratio;
  pulsecolor.b = _color_fg.b * ratio;

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
  random16_add_entropy(random(65535));

  for (int i = _pixstart; i <= _pixend; i++) {
    float random_ratio = random8(101) / 100.0;
    _pixset[i].setRGB(_color_fg.r * random_ratio, _color_fg.g * random_ratio, _color_fg.b * random_ratio);
  }
}

void NeoPixelEffects::updateFadeOutEffect()
{
  CRGB fadecolor;

  if (_counter == 0) _counter = 100;
  float ratio = _counter / 100.0;

  for (int i = _pixstart; i <= _pixend; i++) {
    fadecolor.r = _pixset[i].r * ratio;
    fadecolor.g = _pixset[i].g * ratio;
    fadecolor.b = _pixset[i].b * ratio;
    _pixset[i] = fadecolor;
  }

  _counter--;

  if (_counter <= 0 || fadecolor == CRGB(0,0,0)) {
    setEffect(NONE);
    setStatus(INACTIVE);
  }
}

void NeoPixelEffects::updateFillInEffect()
{
  _pixset[_pixcurrent] = _color_fg;
  if (_direction == FORWARD) {
    if (_pixcurrent != _pixend) {
      _pixcurrent++;
    } else {
      setEffect(NONE);
      setStatus(INACTIVE);
    }
  } else {
    if (_pixcurrent != _pixstart) {
      _pixcurrent--;
    } else {
      setEffect(NONE);
      setStatus(INACTIVE);
    }
  }
}

void NeoPixelEffects::updateGlowEffect()
{
  CRGB glowcolor;

  float ratio = _counter / 100.0;
  glowcolor.r = _color_fg.r * ratio;
  glowcolor.g = _color_fg.g * ratio;
  glowcolor.b = _color_fg.b * ratio;

  if (_direction == FORWARD) {
    _counter++;
    if (_counter >= 100) setDirection(REVERSE);
  } else {
    _counter--;
    if (_counter <= 0) {
      setDirection(FORWARD);
      if (!_repeat) {
        setEffect(NONE);
        setStatus(INACTIVE);
      }
    }
  }

  int glow_area_half = (_pixrange - _pixaoe) / 2;
  for (int i = 0; i < glow_area_half ; i++) {
    _pixset[_pixrange + i].r = glowcolor.r * i / glow_area_half;
    _pixset[_pixrange + i].g = glowcolor.g * i / glow_area_half;
    _pixset[_pixrange + i].b = glowcolor.b * i / glow_area_half;
  }
  _pixset[_pixstart + glow_area_half] = glowcolor;
  _pixset[_pixstart + glow_area_half + 1] = glowcolor;
  for (int i = glow_area_half - 1; i >= 0 ; i--) {
    _pixset[_pixend - i].r = glowcolor.r * i / glow_area_half;
    _pixset[_pixend - i].g = glowcolor.g * i / glow_area_half;
    _pixset[_pixend - i].b = glowcolor.b * i / glow_area_half;
  }
}

// void NeoPixelEffects::updateFireworkEffect()
// {
//   static NeoPixelEffects *m = new NeoPixelEffects(_pixset, COMET, _pixstart,                  _pixend - _pixaoe - 4, 2,         25,     CRGB::White,  false, FORWARD);
//   static NeoPixelEffects *s1 = new NeoPixelEffects(_pixset, NONE, _pixend - 2 * _pixaoe - 4,  _pixend - _pixaoe - 2, stars_aoe, _delay, _color_fg, false, REVERSE);
//   static NeoPixelEffects *s2 = new NeoPixelEffects(_pixset, NONE, _pixend - _pixaoe - 2,      stars_end,             stars_aoe, _delay, _color_fg, false, FORWARD);
//   static NeoPixelEffects *sf = new NeoPixelEffects(_pixset, NONE, _pixend - 2 * _pixaoe - 4,  _pixend,               1,         7,      _color_fg, false, REVERSE);
//
//   if (_counter == 0 && m->getEffect() == NONE) {
//     delay(200);
//     s1->setEffect(FILLIN);
//     s2->setEffect(FILLIN);
//     _counter = 1;
//   } else if (_counter == 1 && s1->getEffect() == NONE && s2->getEffect() == NONE) {
//     delay(200);
//     sf->setEffect(FADE);
//     _counter = 2;
//   } else if (_counter == 2 && sf->getEffect() == NONE) {
//     delete(m);
//     delete(s1);
//     delete(s2);
//     delete(sf);
//     setEffect(NONE);
//   }
//
//   m->update();
//   s1->update();
//   s2->update();
//   sf->update();
// }

// void NeoPixelEffects::updateSparkleFillEffect()
// {
//   static NeoPixelEffects *sparkles = new NeoPixelEffects(_pixset, STATIC, (_direction==FORWARD)?_pixstart,  (_direction==FORWARD)?_pixstart:_pixend, 1, _delay, _color_fg, false, _direction);
//
//   sparkles->update();
//
//   if (_direction == FORWARD) {
//     if (_pixcurrent != _pixend) {
//       _pixcurrent++;
//       sparkles->setRange(_pixstart, _pixcurrent);
//     }
//   } else {
//     if (_pixcurrent != _pixstart) {
//       _pixcurrent--;
//       sparkles->setRange(_pixcurrent, _pixend);
//     }
//   }
//
//   if (_status == INACTIVE) {
//     delete(sparkles);
//     clear();
//     setEffect(NONE);
//   }
// }

void NeoPixelEffects::updateRainbowWaveEffect()
{
  float ratio = 255.0  / _pixrange;

  for (int i = _pixstart; i <= _pixend; i++) {
    CRGB color = CHSV((uint8_t)((_counter + i) * ratio), 255, 255);
    _pixset[i] = color;
  }
  _counter = (_direction) ? _counter + 1 : _counter - 1;
}

void NeoPixelEffects::updateStrobeEffect()
{
  CRGB strobecolor;
  if (_counter % 2 == 0) {
    // TODO show foreground color
    strobecolor = _color_fg;
  } else {
    // TODO show background color
    strobecolor = _color_bg;
  }

  for (int j = _pixstart; j <= _pixend; j++) {
    _pixset[j] = strobecolor;
  }
  _counter++;
}

void NeoPixelEffects::updateSineWaveEffect()
{
  CRGB wavecolor;
  for (int i = _pixstart; i <= _pixend; i++) {
    float ratio;
    if (!_subtype) {
      ratio = sin8(_counter + (i - _pixstart) * 200 / _pixrange) / 255.0;
    } else {
      ratio = triwave8(_counter + (i - _pixstart) * 200 / _pixrange) / 255.0;
    }
    wavecolor.r = _color_fg.r * ratio;
    wavecolor.g = _color_fg.g * ratio;
    wavecolor.b = _color_fg.b * ratio;
    _pixset[i] = wavecolor;
  }
  _counter = (_direction) ? _counter + 1 : _counter - 1;
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
  _lastupdate = 0;
}

void NeoPixelEffects::setAreaOfEffect(int aoe)
{
  if (aoe > 0 && aoe <= _pixrange) {
    _pixaoe = aoe;
  }
  _lastupdate = 0;
}

void NeoPixelEffects::setDelayHz(int delay_hz)
{
  if (delay_hz > 0) {
    _delay = (unsigned long)(1.0 / delay_hz * 1000);
  }
  update();
}

void NeoPixelEffects::setDelay(unsigned long delay_ms)
{
  _delay = delay_ms;
  _lastupdate = 0;
  update();
}

void NeoPixelEffects::setColorRGB(uint8_t color_red, uint8_t color_green, uint8_t color_blue)
{
  if (color_red > -1 && color_green > -1 && color_blue > -1) {
    _color_fg.r = (color_red > 255) ? 255 : color_red;
    _color_fg.g = (color_green > 255) ? 255 : color_green;
    _color_fg.b = (color_blue > 255) ? 255 : color_blue;
  }
  _lastupdate = 0;
}

void NeoPixelEffects::setColor(CRGB color_crgb)
{
  _color_fg = color_crgb;
  _lastupdate = 0;
}

void NeoPixelEffects::setBackgroundColor(CRGB color_crgb)
{
  _color_bg = color_crgb;
  _lastupdate = 0;
}

void NeoPixelEffects::setStatus(EffectStatus status)
{
  _status = status;
  _lastupdate = 0;
}

EffectStatus NeoPixelEffects::getStatus()
{
  return(_status);
}

void NeoPixelEffects::setRepeat(bool repeat)
{
  _repeat = repeat;
  _lastupdate = 0;
}

void NeoPixelEffects::setDirection(bool direction)
{
  _direction = direction;
  _lastupdate = 0;
}

void NeoPixelEffects::setSubtype(uint8_t subtype)
{
  _subtype = subtype;
  _lastupdate = 0;
}

void NeoPixelEffects::clear()
{
  fill_solid(CRGB::Black);
}

void NeoPixelEffects::fill_solid(CRGB color_crgb)
{
  for (int i = _pixstart; i <= _pixend; i++) {
    _pixset[i] = color_crgb;
  }

  setEffect(NONE);
  setStatus(INACTIVE);
}

void NeoPixelEffects::fill_gradient(CRGB color_crgb1, CRGB color_crgb2)
{
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

  setEffect(NONE);
  setStatus(INACTIVE);
}
