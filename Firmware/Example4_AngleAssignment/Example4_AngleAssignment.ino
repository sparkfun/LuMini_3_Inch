#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60 //3 Inch
//#define NUM_LEDS 40 //2 Inch
//#define NUM_LEDS 20 //1 Inch

//Data and Clock Pins
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds
CRGB ring[NUM_LEDS];
uint8_t ringMap[255];
uint8_t rotation = 0;

float angleRangePerLED = 256.0 / NUM_LEDS; //A single LED will take up a space this many degrees wide.

void populateMap () //we map LED's to a 360 degree circle where 360 == 255
{
  for (int ledNum = 0; ledNum < NUM_LEDS; ledNum++) //Loops through each LED and assigns it to it's range of angles
  {
    for (int j = round(ledNum * angleRangePerLED); j < round((ledNum + 1) * angleRangePerLED); j++)
    {
      ringMap[j] = ledNum;
    }
  }
}

void fadeAll(uint8_t scale = 250)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    ring[i].nscale8(scale);
  }
}

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  FastLED.setBrightness(32);
  populateMap();
}

void loop()
{
  for (int i = 0; i < 3; i++)
  {
    uint8_t angle = round(i * 85.3333) + rotation;
    ring[ringMap[angle]] = CHSV(angle, 127, 255);
  }
  FastLED.show();
  rotation++;
  fadeAll(248);
  delay(5);
}
