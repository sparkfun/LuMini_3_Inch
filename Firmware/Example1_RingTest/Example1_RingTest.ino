#include <FastLED.h>

// How many leds in your strip? Uncomment the corresponding line
#define NUM_LEDS 60 //3 Inch
//#define NUM_LEDS 40 //2 Inch
//#define NUM_LEDS 20 //1 Inch

// The LuMini rings need two data pins connected
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds
CRGB ring[NUM_LEDS];

void fadeAll(uint8_t scale = 250)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    ring[i].nscale8(scale);
  }
}

void setup() {
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  LEDS.setBrightness(32);
}

void loop() {
  static uint8_t hue = 0;
  //Rotate around the circle
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to the current hue
    ring[i] = CHSV(hue++, 150, 255); //display the current hue, then increment it.
    // Show the leds
    FastLED.show();
    fadeAll();//Reduce the brightness of all LEDs so our LED's fade off with every frame.
    // Wait a little bit before we loop around and do it again
    delay(5);
  }
}
