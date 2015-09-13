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

NeoPixelEffects::NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, int redvalue, int greenvalue, int bluevalue) :
  _pix(pix)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(redvalue, greenvalue, bluevalue);
  _looping = true;
  _direction = FORWARD;
  initialize(effect);
}

NeoPixelEffects::NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, EffectColor ec) :
  _pix(pix)
{
  setRange(pixstart, pixend);
  setAreaOfEffect(aoe);
  setDelay(delay);
  setColor(ec);
  _looping = true;
  _direction = FORWARD;
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
  _pixcurrent = 0;
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

  update();
}

void NeoPixelEffects::update()
{
  if (_effect != NONE) {
    unsigned long timenow = millis();
    if (timenow - _lastupdate > _delay) {
      _lastupdate = timenow;
      switch (_effect) {
        case CHASE:
          updateChaseEffect();
          break;
        case PULSE:
          updatePulseEffect();
          break;
        default:
          break;
      }
      _pix->show();
    }
  }
}

void NeoPixelEffects::updateChaseEffect()
{
  // Get fraction
  int maxb = max(_effectcolor.r, max(_effectcolor.g, _effectcolor.b));
  float ratio = maxb / _pixaoe;

  for (int j = 0; j < _pixaoe; j++) {
    int redvalue =    (ratio * j / maxb) * _effectcolor.r;
    int greenvalue =  (ratio * j / maxb) * _effectcolor.g;
    int bluevalue =   (ratio * j / maxb) * _effectcolor.b;

    int temppixel;
    if (_direction == FORWARD) {
      temppixel = (_pixcurrent + j > _pixend && _looping == true) ? _pixstart + (_pixcurrent + j) - _pixend - 1 : _pixcurrent + j;
    } else {
      temppixel = (_pixcurrent - j < _pixstart && _looping == true) ? _pixend - (abs(_pixstart - (_pixcurrent - j)) + 1) : _pixcurrent - j;
    }

    _pix->setPixelColor(temppixel, _pix->Color(redvalue, greenvalue, bluevalue));
  }

  if (_direction == FORWARD) {
    _pixcurrent = (_pixcurrent + 1 > _pixend && _looping == true) ? _pixstart : _pixcurrent + 1;
  } else {
    _pixcurrent = (_pixcurrent - 1 < _pixstart && _looping == true) ? _pixend : _pixcurrent - 1;
  }
}

void NeoPixelEffects::updatePulseEffect()
{
  Serial.println("updating pulse effect now");
  static EffectColor pulsecolor = _effectcolor;
  Serial.print(pulsecolor.r);
  Serial.print(" ");
  Serial.print(pulsecolor.g);
  Serial.print(" ");
  Serial.print(pulsecolor.b);
  Serial.println(" ");
  static int count = 0;
  Serial.println(count);

  pulsecolor.r = _effectcolor.r * count / 100;
  pulsecolor.g = _effectcolor.g * count / 100;
  pulsecolor.b = _effectcolor.b * count / 100;
  setColor(pulsecolor.r, pulsecolor.g, pulsecolor.b);

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

void NeoPixelEffects::setEffect(Effect effect)
{
  _effect = effect;
  NeoPixelEffects::update();
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
