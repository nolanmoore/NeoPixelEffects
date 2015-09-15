# NeoPixelEffects Library

A library made to complement the [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library by Adafruit by providing various visual effects, such as fading, sparkles, static, etc.

After downloading, rename folder to 'NeoPixelEffects' and install in Arduino Libraries folder. Restart Arduino IDE, then open File->Sketchbook->Library->NeoPixelEffects->TrailEffectExample sketch.

## Functions
### Constructors/Destructors
~~~arduino
NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, int redvalue, int greenvalue, int bluevalue, bool direction, bool looping);
NeoPixelEffects(Adafruit_NeoPixel *pix, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay, EffectColor color, bool direction, bool looping);
~~~
### Public functions
~~~arduino
int  initialize(Effect effect);
void update();
void setEffect(Effect effect);
Effect getEffect();
int  setRange(int pixstart, int pixend);
int  setAreaOfEffect(int areaofeffect);
void setDelay(unsigned long delay);
int  setColor(int redvalue, int greenvalue, int bluevalue);
void setColor(EffectColor color);
void setLooping(bool value);
void setDirection(bool direction);
~~~
## Effect names and parameters
| Name | Range | AoE | Delay | Color | Looping | Direction | Description |
| ----: | :-----: | :-----: |  :---: | :-----: | :-------: | :---------: | :--- |
| COMET | Y | Y | Y | Y | Y | Y | A pixel moves across the range with a tail |
| CHASE | Y | ? | Y | Y | N | Y | A marquee chase effect |
| PULSE | Y | N | Y | Y | Y | N | Range pulses on and off |
| STATIC | Y | N | Y | Y | N | N | TV fuzz effect |
| FADE | Y | N | Y | Y | N | Y | Range fades up or down to set color then stops |
| FILL | Y | N | Y | Y | N | Y | Range fills up from one end until full then stops |
| EMPTY | Y | N | Y | Y | N | Y | Range empties from one end until empty then stops |
| FIREWORK | Y | Y | Y | Y | ? | Y | Mortar fires from one side then explodes into 2 non-looping COMETS |
