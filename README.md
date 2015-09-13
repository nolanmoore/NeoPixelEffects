# NeoPixelEffects Library

A library made to complement the [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library by Adafruit by providing various visual effects, such as fading, sparkles, static, etc.

After downloading, rename folder to 'NeoPixelEffects' and install in Arduino Libraries folder. Restart Arduino IDE, then open File->Sketchbook->Library->NeoPixelEffects->TrailEffectExample sketch.

## Functions
### Constructors/Destructors
~~~arduino
NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, int redvalue, int greenvalue, int bluevalue);
~~~
### Public Functions
~~~arduino
int initialize(Effect effect)
void update()
void setEffect(Effect effect)
int setRange(int startpixel, int endpixel)
int setAreaOfEffect(int areaofeffect)
void setDelay(unsigned long delay)
int setColor(int redValue, int greenValue, int blueValue)
void setColor(EffectColor color)
void setLooping(bool setloop)
void setDirection(bool direction)
~~~
## Effect values
* CHASE
* SPARKLE
* WAVE
