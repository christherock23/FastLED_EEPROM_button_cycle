//Based on FastLED 100 lines of code demo reel by Mark Kriegsman
//Please join the FastLED community on Google+ these guys rock!

//If this is your first time using EEPROM the LEDS will be 
//blank at first, simply press the button to store the new 
//pattern value which will be the second on the list. There
//should be no problems after this, this is due to the default
//value being 255 (or atleast thats the default value on the 
//Atmega32u4.

//Include these files if you want your code to work!
#include "FastLED.h"
#include "Patterns.h"
#include "Buttons.h"
#include <EEPROM.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    17        //Pin your LEDS are connected to
#define LED_TYPE    WS2812B   //Type of LEDS you are using
#define COLOR_ORDER GRB       //Order of LEDS inside your LEDS, GRB for WS2812B

#define BRIGHTNESS          96  //set brightness between 0 and 255, you can also
                                //add another button to save this value but for 
                                //the sake of simplicity brightness is a set value
                                //in this program
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { 
rainbow,
rainbowWithGlitter,
confetti,
sinelon,
juggle,
bpm
};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
  
void loop()
{
  //Call the pattern currently stored in EEPROM address 1
  gCurrentPatternNumber = EEPROM.read(1);
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
  if(buttonListener()) { nextPattern(); } //Check if the buttom has been pressed
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  EEPROM.write(1, gCurrentPatternNumber); //Save new pattern to EEPROM address 1
}
