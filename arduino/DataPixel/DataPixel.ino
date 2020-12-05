// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        D3 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(9600);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

uint32_t createDataColor(boolean clockColor, boolean dataBitColor, boolean syncBitColor) {

  return (clockColor * 0x000000FF) << 16 |
         (dataBitColor * 0x000000FF) << 8 |
         (syncBitColor * 0x000000FF);
}

uint16_t myData = 4567;
uint32_t syncPixelColor = 0xFFFFFF;
uint32_t dataPixelColor = 0x00;
uint8_t dataBit0 = 0;
uint8_t dataBit1 = 0;
uint8_t clockBit = 0;
uint8_t bitCount = 0;

void loop() {
  clockBit = !clockBit;

  if (clockBit) {
    if (bitCount > 0) {
      dataBit0 = (myData & (1 << bitCount)) >> bitCount;
      dataBit1 = !dataBit0;
      dataPixelColor = createDataColor(clockBit, dataBit0, dataBit1);      
    }
    else {
      dataPixelColor = createDataColor(1, 1, 1);
    }
    bitCount = (bitCount + 1) % 17;
  }
  else
    dataPixelColor = createDataColor(clockBit, 0, 0);

  pixels.clear(); // Set all pixel colors to 'off'
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, dataPixelColor);
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
}
