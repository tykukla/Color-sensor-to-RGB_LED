/*********************************************************/
// CODE MODIFIED FOR RGB SENSOR (RECEIVING DATA) BY T KUKLA (2022)
// Includes some original code from Adafruit IO Environmental Data Logger tutorial

/* DATA LOGGER HEADER: 
 *  Tutorial Link: https://learn.adafruit.com/adafruit-io-air-quality-monitor
 *  Adafruit invests time and resources providing this open source code. 
 *  Please support Adafruit and open source hardware by purchasing products from Adafruit!
 *  
 *  Written by Brent Rubell for Adafruit Industries 
 *  Copyright (c) 2018 Adafruit Industries 
 *  Licensed under the MIT license.
 */
/*********************************************************/

/************************** Adafruit IO Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/***************** NEOPIXEL *******************/
#include <Adafruit_NeoPixel.h>
#define NEOPIXEL_PIN 13 // NeoPixels are connected to this pin
#define NUM_LEDS    6   // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Board pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


/**************************** IO FEED ***************************************/
// set up the feeds for the sensor
AdafruitIO_Feed *rgbFeed = io.feed("rgb");


void setup() {
  Serial.begin(9600);

  // wait for serial monitor to open
  while (!Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'rgb' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  rgbFeed->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // initialize neopixel
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // collect data from feed?
  rgbFeed -> get();
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Serial.println(data);
}


// this function is called whenever a 'rgb' message
// is received from Adafruit IO. it was attached to
// the color feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {  // see: (https://learn.adafruit.com/adafruit-io-basics-color/arduino-code)

  // print RGB values and hex value
  Serial.println("Received HEX: ");
  Serial.println(data->value());

  long rgbFeed = data->toNeoPixel();

  for(int i=0; i<NUM_LEDS; ++i) { // print to pixel one at a time
    strip.setPixelColor(i, rgbFeed);
  }

  strip.show();

}
