#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <stdlib.h>

#define PIN 6
#define LEDNUM 120

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Each NeoPixel can draw up to 60mA when displaying bright 
  // white (red AND green AND blue LEDs at full brightness).
  // Care should be taken to ensure average current drawn from 
  // the Bean+ battery is less than 600mA when using the NeoPixel strip.

  // We set the brightness to 32 here to minimize current draw.
  //colorWipe(strip.Color(0, 32, 0), 50); // Green
  //colorWipeReverse(strip.Color(0, 0, 0), 50); // Turn off LEDs
  //staticRand();
  //randSweep();
  //lightSweep();
  //repeat();
  staticRand();
  more_steps(32, 200);
  repeatColors();
  more_steps(32, 200);
  blink(32, 0, 0, 2, 200);
  blink(0, 32, 0, 2, 200);
  blink(8, 0, 8, 2, 200);
}

void blink(uint16_t r, uint16_t g, uint16_t b, uint16_t n, uint32_t t) {
  uint16_t i;

  for (i = 0; i < n; i++) {
    setAll(r, g, b);
    delay(t);
    setAll(0, 0, 0);
    delay(t);
  }
}

void setAll(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t i;
  
  for (i = 0; i < LEDNUM; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void more_steps(uint16_t n, uint32_t t) {
  uint16_t i;
  
  for (i = 0; i < n; i++) {
    delay(t);
    step();
  }
}

void step(void) {
  uint16_t i;
  uint32_t prv, cur;
  
  prv = strip.getPixelColor(LEDNUM - 1);
  for (i = 0; i < LEDNUM; i++) {
    cur = strip.getPixelColor(i);
    strip.setPixelColor(i, prv);
    prv = cur;
  }
  strip.show();
}

void repeatColors(void) {
  uint16_t i;

  for (i = 0; i < LEDNUM / 12; i++) {
    strip.setPixelColor(i*12 + 0, strip.Color(0, 0, 0));
    strip.setPixelColor(i*12 + 1, strip.Color(0, 0, 0));
    strip.setPixelColor(i*12 + 2, strip.Color(0, 0, 0));

    strip.setPixelColor(i*12 + 3, strip.Color(32, 0, 0));
    strip.setPixelColor(i*12 + 4, strip.Color(32, 0, 0));
    strip.setPixelColor(i*12 + 5, strip.Color(32, 0, 0));
    strip.setPixelColor(i*12 + 6, strip.Color(0, 32, 0));
    strip.setPixelColor(i*12 + 7, strip.Color(0, 32, 0));
    strip.setPixelColor(i*12 + 8, strip.Color(0, 32, 0));

    strip.setPixelColor(i*12 + 9, strip.Color(16, 0, 16));
    strip.setPixelColor(i*12 + 10, strip.Color(16, 0, 16));
    strip.setPixelColor(i*12 + 11, strip.Color(16, 0, 16));
    /*
    switch (i % 4) {
    case 0:
      strip.setPixelColor(i*12 + 0, strip.Color(0, 0, 0));
      strip.setPixelColor(i*12 + 1, strip.Color(0, 0, 0));
      strip.setPixelColor(i*12 + 2, strip.Color(0, 0, 0));
      break;
    case 1:
      strip.setPixelColor(i*12 + 3, strip.Color(32, 0, 0));
      strip.setPixelColor(i*12 + 4, strip.Color(32, 0, 0));
      strip.setPixelColor(i*12 + 5, strip.Color(32, 0, 0));
      break;
    case 2:
      strip.setPixelColor(i*12 + 6, strip.Color(0, 32, 0));
      strip.setPixelColor(i*12 + 7, strip.Color(0, 32, 0));
      strip.setPixelColor(i*12 + 8, strip.Color(0, 32, 0));
      break;
    case 3:
      strip.setPixelColor(i*12 + 9, strip.Color(16, 0, 16));
      strip.setPixelColor(i*12 + 10, strip.Color(16, 0, 16));
      strip.setPixelColor(i*12 + 11, strip.Color(16, 0, 16));
      break;
    }
    */
  }

  strip.show();
}

void lightSweep(void) {
  uint16_t i;
  uint32_t now, prv;

  for (i = 0; i < LEDNUM; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(32, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 32, 0));
  strip.setPixelColor(3, strip.Color(16, 0, 16));
  strip.show();

  for (i = 1; i < LEDNUM - 1; i++) {
    now = strip.getPixelColor(i + 1);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(i + 1, now);
    strip.show();
    delay(2000);
  }
}

void randSweep(void) {
  uint16_t i;

  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(rand() % 32, rand() % 32, rand() % 32));
  }
  strip.show();

  for (i = 0; i < strip.numPixels(); i += 3) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(i + 1, strip.Color(0, 0, 0));
    strip.setPixelColor(i + 2, strip.Color(0, 0, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(rand() % 32, rand() % 32, rand() % 32));
    strip.setPixelColor(i + 1, strip.Color(rand() % 32, rand() % 32, rand() % 32));
    strip.setPixelColor(i + 2, strip.Color(rand() % 32, rand() % 32, rand() % 32));
    strip.show();
  }
}

void staticRand(void) {
  uint16_t i;
  uint32_t a, b, c;

  srand(time(NULL));
  for (i = 0; i < strip.numPixels(); i++) {
    a = rand() % 32;
    b = rand() % 32;
    c = rand() % 32;
    strip.setPixelColor(i, strip.Color(a, b, c));
  }
  strip.show();
}

// Fill dots one after the other with a color
// Skip every other dot to minimize current draw from the battery on Bean+
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
// Skip every other dot to minimize current draw from the battery on Bean+
void colorWipeReverse(uint32_t c, uint8_t wait) {
  for(int16_t i=(strip.numPixels()); i>=0; i=i-2) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
