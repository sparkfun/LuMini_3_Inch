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

TBlendType    currentBlending = LINEARBLEND;
CRGBPalette16 currentPalette = {
  CHSV(5, 190, 255),
  CHSV(0, 190, 255),
  CHSV(245, 255, 255),
  CHSV(235, 235, 255),
  CHSV(225, 235, 255),
  CHSV(225, 150, 255),
  CHSV(16, 150, 255),
  CHSV(16, 200, 255),
  CHSV(16, 225, 255),
  CHSV(0, 255, 255),
  CHSV(72, 200, 255),
  CHSV(115, 225, 255),
  CHSV(40, 255, 255),
  CHSV(35, 255, 255),
  CHSV(10, 235, 255),
  CHSV(5, 235, 255)
};

//currentPalette = RainbowColors_p;
//currentPalette =  RainbowStripeColors_p;
//currentPalette = OceanColors_p;
//currentPalette = CloudColors_p;
//currentPalette = LavaColors_p;
//currentPalette = ForestColors_;
//currentPalette = PartyColors_p;

uint8_t ringMap[255];
uint8_t rotation = 0;
uint8_t brightness = 255;

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

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  FastLED.setBrightness(32);
  populateMap();
}

void loop() {
  for (uint8_t i = 0; i < 255; i++)
  {
    uint8_t gradientIndex = i + rotation;
    ring[ringMap[i]] = ColorFromPalette(currentPalette, gradientIndex, brightness, currentBlending);
  }
  FastLED.show();
  rotation++;
  delay(30);
}
