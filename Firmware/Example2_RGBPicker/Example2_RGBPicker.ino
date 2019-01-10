#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60 //3 Inch
//#define NUM_LEDS 40 //2 Inch
//#define NUM_LEDS 20 //1 Inch

//Data and Clock Pins
#define DATA_PIN 16
#define CLOCK_PIN 17

CRGB color;
char colorToEdit;

// Define the array of leds
CRGB ring[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial.println("resetting");
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  LEDS.setBrightness(32);

  //Display our current color data
  Serial.print("Red Value: ");
  Serial.println(color[0]);
  Serial.print("Green Value: ");
  Serial.println(color[1]);
  Serial.print("Blue Value: ");
  Serial.println(color[2]);
  Serial.println();
}

void loop()
{
  if (Serial.available()) //Check to see if we have new Serial data.
  {
    colorToEdit = Serial.read();
    switch (colorToEdit)
    {
      case 'R':
      case 'r':
        color[0] = Serial.parseInt();
        break;
      case 'G':
      case 'g':
        color[1] = Serial.parseInt();
        break;
      case 'B':
      case 'b':
        color[2] = Serial.parseInt();
        break;
    }
    //Display our current color data
    Serial.print("Red Value: ");
    Serial.println(color[0]);
    Serial.print("Green Value: ");
    Serial.println(color[1]);
    Serial.print("Blue Value: ");
    Serial.println(color[2]);
    Serial.println();
    for (int i = 0; i < NUM_LEDS; i++)
    {
      ring[i] = color;
      FastLED.show();
      delay(10);
    }
  }
}
