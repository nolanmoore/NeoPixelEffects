# NeoPixelEffects Library

A library made to complement the [FastLED](https://github.com/FastLED/FastLED/tree/master) library by Daniel Garcia by providing various visual effects, such as fading, sparkles, static, etc.

After downloading, rename folder to 'NeoPixelEffects' and install in Arduino Libraries folder. Restart Arduino IDE, then open File->Sketchbook->Library->NeoPixelEffects->CometEffectExample sketch.

## Functions
### Constructors/Destructors
~~~arduino
NeoPixelEffects(CRGB leds, Effect effect, int pixstart, int pixend, int aoe, unsigned long delay_ms, CRGB color_crgb, bool direction, bool looping);
~~~
### Public functions
~~~arduino
void setEffect(Effect effect);
Effect getEffect();
void setEffect(Effect effect);
EffectStatus getEffectStatus();
void setColor(CRGB color_crgb);
void setBackgroundColor(CRGB color_crgb);
void setRange(int pixstart, int pixend);
void setAreaOfEffect(int aoe);
void setDelay(unsigned long delay_ms);
void setDelayHz(int delay_hz);
void setLooping(bool value);
void setDirection(bool direction);

void update();
void stop();
void pause();
void play();
~~~
## Effect names and parameters
| Name | Range | AoE | Delay | Color | Looping | Direction | Description |
| ----: | :-----: | :-----: |  :---: | :-----: | :-------: | :---------: | :--- |
| COMET | Y | Y | Y | Y | Y | Y | A pixel moves across the range with a tail |
| LARSON | Y | Y | Y | Y | Y | Y | A pixel moves back and forth across the range |
| CHASE | Y | ? | Y | Y | N | Y | A theater chase effect |
| PULSE | Y | N | Y | Y | Y | N | Range slowly breathes on and off |
| STATIC | Y | N | Y | Y | N | N | TV fuzz effect |
| FADE | Y | N | Y | N | N | N | Range fades out to off and effect is paused |
| FILLIN | Y | N | Y | Y | N | Y | Range fills up from one end until full then stops |
| GLOW | Y | Y | Y | Y | N | N | The pixels in center of range glow and pulse |
| RAINBOWWAVE | Y | N | Y | N | N | Y | A moving rainbow gradient |
| STROBE | Y | N | Y | Y | N | N | Range flashes on and off |
| SINEWAVE | Y | N | Y | Y | N | Y | Creates a moving sine wave across the range |
| RANDOM | Y | N | Y | N | N | N | Each pixel is set to a random color and brightness with each update |
| TALKING | Y | N | Y | Y | N | N | Emulates a robotic "mouth" |
| TRIWAVE | Y | N | Y | Y | N | Y | Creates a moving sawtooth wave across the range |
