#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60 //3 Inch
//#define NUM_LEDS 40 //2 Inch
//#define NUM_LEDS 20 //1 Inch

//Data and Clock Pins
#define DATA_PIN 16
#define CLOCK_PIN 17

CHSV color = CHSV(0, 255, 255);
char colorToEdit;

// Define the array of leds
CRGB ring[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial.println("resetting");
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(ring, NUM_LEDS);
  LEDS.setBrightness(32);
  
  //Display our current color data
  Serial.print("Hue: ");
  Serial.println(color.hue);
  Serial.print("Saturation: ");
  Serial.println(color.sat);
  Serial.print("Value: ");
  Serial.println(color.val);
  Serial.println();
}

void loop()
{
  if (Serial.available()) //Check to see if we have new Serial data.
  {
    colorToEdit = Serial.read();
    switch (colorToEdit)
    {
      case 'H':
      case 'h':
        color.hue = Serial.parseInt();
        break;
      case 'S':
      case 's':
        color.sat = Serial.parseInt();
        break;
      case 'V':
      case 'v':
        color.val = Serial.parseInt();
        break;
    }
    //Display our current color data
    Serial.print("Hue: ");
    Serial.println(color.hue);
    Serial.print("Saturation: ");
    Serial.println(color.sat);
    Serial.print("Value: ");
    Serial.println(color.val);
    Serial.println();

    for (int i = 0; i < NUM_LEDS; i++)
    {
      ring[i] = color;
      FastLED.show();
      delay(10);
    }
  }
}
