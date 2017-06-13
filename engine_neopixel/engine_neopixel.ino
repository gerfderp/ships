#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 1
const int hold = 500;
const int fade = 25;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_RGBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.setBrightness(20);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  setStrand(0, 255, 0);
  fadeStrand(0, 255, 0); //Red
  fadeStrand(48, 255, 48);//Hot Pink
}

void loop() {
  fadeStrand(0, 255, 0); //Red
//  fadeStrand(128, 255, 0); //orange
//  fadeStrand(255, 255, 0); //yellow
  //fadeStrand(165, 255, 0); //orange
//  fadeStrand(255, 255, 0); //yellow
//  rainbow(10);
  // Some example procedures showing how to display to the pixels:
  fadeStrand(255, 0, 255);//lightBlue
//  colorWipe(strip.Color(255, 0, 0), 50); // Green
//  colorWipe(strip.Color(48, 255, 48, 10), 50); // Hot Pink
//  colorWipe(strip.Color(0, 255, 0, 10), 50); // Red
//  colorWipe(strip.Color(165, 255, 0, 10), 50); // Orange
//  colorWipe(strip.Color(255, 255, 0, 10), 50); // Yellow
//    colorWipe(strip.Color(48, 255, 48, 10), 50); // Hot Pink
//colorWipe(strip.Color( 64,0, 0, 64), 50);
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

void setStrand(int G, int R, int B) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(G, R, B)); 
  }
  strip.show();
  delay(hold);
}

void fadeStrand(int G, int R, int B) {
  uint32_t oldColor = strip.getPixelColor(11);
  
  int oldG = green(oldColor);
  int oldR = red(oldColor);
  int oldB = blue(oldColor);

  int currentR = oldR;
  int currentG = oldG;
  int currentB = oldB;
  while( currentB != B || currentG != G || currentR != R){
    if (currentB != B){
      if (oldB > B){
        currentB--;
      } else {
        currentB++;
      }
    }
    if (currentR != R){
      if (oldR > R){
        currentR--;
      } else {
        currentR++;
      }
    }
    if (currentG != G){
      if (oldG > G){
        currentG--;
      } else {
        currentG++;
      }
    }
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, currentG, currentR, currentB); 
    }

    strip.show();
    delay(fade);
  }
  

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(G, R, B)); 
  }
  strip.show();
  delay(hold);
}

uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
