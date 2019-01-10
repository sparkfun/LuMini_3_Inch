#include <FastLED.h>

// How many leds in your strip? Uncomment the corresponding line
#define NUM_LEDS 80 //3 Inch
//#define NUM_LEDS 40 //2 Inch
//#define NUM_LEDS 20 //1 Inch

// The LuMini rings need two data pins connected
#define DATA_PIN 16
#define CLOCK_PIN 17
#define interruptPin 0

uint8_t pattern = 0;

// Define the array of leds
CRGB ring[NUM_LEDS];
uint8_t ringMap[255];
uint8_t rotation = 0;
uint8_t brightness = 255;

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

float angleRangePerLED = 256.0 / 60.0; //A single LED will take up a space this many degrees wide.

void populateMap () //we map LED's to a 360 degree circle where 360 == 255
{
  for (int ledNum = 0; ledNum < 60; ledNum++) //Loops through each LED and assigns it to it's range of angles
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

void example1()
{
  static uint8_t hue = 0;
  //Rotate around the circle
  for (int i = 20; i < NUM_LEDS; i++) {
    // Set the i'th led to the current hue
    ring[i] = CHSV(hue++, 150, 255); //display the current hue, then increment it.
    // Show the leds
    FastLED.show();
    fadeAll();//Reduce the brightness of all LEDs so our LED's fade off with every frame.
    // Wait a little bit before we loop around and do it again
    delay(5);
  }
}

void example4 ()
{
  for (int i = 0; i < 3; i++)
  {
    uint8_t angle = round(i * 85.3333) + rotation;
    ring[ringMap[angle] + 20] = CHSV(angle, 127, 255);
  }
  FastLED.show();
  rotation++;
  fadeAll(248);
  delay(5);
}

void example5 ()
{
  for (uint8_t i = 0; i < 255; i++)
  {
    uint8_t gradientIndex = i + rotation;
    ring[ringMap[i] + 20] = ColorFromPalette(currentPalette, gradientIndex, brightness, currentBlending);
  }
  FastLED.show();
  rotation++;
  delay(30);
}

void changePattern ()
{
  pattern++;
}

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), changePattern, FALLING);

  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  //LEDS.setBrightness(32);
  populateMap();
}

void loop() {
  uint8_t truePattern = pattern % 3;
  switch (truePattern)
  {
    case 0:
      example1();
      break;
    case 1:
      example4();
      break;
    case 2:
      example5();
      break;
  }
}
