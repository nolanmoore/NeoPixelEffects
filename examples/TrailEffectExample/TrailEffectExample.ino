// NeoPixel Effects library test (c) 2015 Nolan Moore
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "NeoPixelEffects.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A0

#define NUMPIXELS      143

#define MAXBRIGHTNESS  75
#define MAXTRAILLENGTH 10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

NeoPixelEffects effect = NeoPixelEffects();

int delayval = 10; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < NUMPIXELS; i++){
//    if (trail(i, 10, 150, COLOR_RED)) {
//      Serial.println("Enter a length less then the number of pixels available");
//    } else {
    {
      int res = trail(23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_RED);
      res = trail(2 * 23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_YELLOW);
      res = trail(3 * 23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_GREEN);
      res = trail(4 * 23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_CYAN);
      res = trail(5 * 23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_BLUE);
      res = trail(6 * 23 + i, MAXTRAILLENGTH, MAXBRIGHTNESS, COLOR_MAGENTA);
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

int trail(int p, int tlen, int maxb, int c) {
  // Sanity check
  if (NUMPIXELS - tlen <= 0) return -1;
  if (p < 0) {
    p = NUMPIXELS + p; // Can trail behind other trails
  }
  if (p > NUMPIXELS) {
    int octaves = p / NUMPIXELS;
    p -= octaves * NUMPIXELS;
  }
  
  // Get fraction
  int sub = maxb / tlen;
  while (sub * tlen > maxb) {
    sub--;
  }

  // Blaze trail
  for (int j = 0; j < tlen; j++) {
    int color = (j == tlen - 1) ? 0 : maxb - sub * j;
    int pin = (p - j < 0) ? NUMPIXELS + p - j : p - j;
    switch (c){
      case COLOR_RED:
        pixels.setPixelColor(pin, pixels.Color(color,0,0));
        break;
      case COLOR_YELLOW:
        pixels.setPixelColor(pin, pixels.Color(color,color,0));
        break;
      case COLOR_GREEN:
        pixels.setPixelColor(pin, pixels.Color(0,color,0));
        break;
      case COLOR_CYAN:
        pixels.setPixelColor(pin, pixels.Color(0,color,color));
        break;
      case COLOR_BLUE:
        pixels.setPixelColor(pin, pixels.Color(0,0,color));
        break;
      case COLOR_MAGENTA:
        pixels.setPixelColor(pin, pixels.Color(color,0,color));
        break;
      default:
        pixels.setPixelColor(pin, pixels.Color(color,color,0));
    }
  }

  return 0;
}

