/*********************************************************/
// CODE MODIFIED FOR RGB SENSOR (SENDING DATA) BY T KUKLA (2022)
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

/**************************** Sensor Configuration ***************************************/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

/**************************** Example ***************************************/
// Delay between sensor reads, in seconds
#define READ_DELAY 25

// set up the feeds for the sensor
AdafruitIO_Feed *rgbFeed = io.feed("rgb");


void setup() {
  Serial.begin(9600);

  // wait for serial monitor to open
  while (!Serial);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  Serial.println("Adafruit IO RGB Sensor");

  
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  Serial.println("Reading Sensors...");

  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  // print to serial
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  // ... [OPTION 1]: Send AIO a string with R G B C values that are parsed by the receive script (not yet set up) (uncomment everything w/o "...")
  // ... get into string form 
  // ... RED
  // String rst = "r: ";
  // String rstdat = rst + r;
  // String rout = rstdat + " ";
  // ... GREEN
  // String gst = "g: ";
  // String gstdat = gst + g;
  // String gout = gstdat + " ";
  // ... BLUE
  // String bst = "b: ";
  // String bstdat = bst + b;
  // String bout = bstdat + " ";
  // ... CLEAR
  // String cst = "c: ";
  // String cstdat = cst + c;
  // String cout = cstdat + " ";

  // ... bring together 
  // String stringOne = rout + gout;    //... not sure if you can just add all at once
  // String stringTwo = stringOne + bout;
  // String stringSend = stringTwo + cout; 

  // ... [OPTION 2]: Send AIO a hex string
  // ... convert RGB to HEX (see reply #7 of: https://forum.arduino.cc/t/hex-to-rgb-and-rgb-to-hex/159003/6)
  byte r2, g2, b2;
  r2 = r;
  g2 = g;
  b2 = b;
  char hexout[8];
  sprintf(hexout,"#%02x%02x%02x",r2,g2,b2);
  Serial.println(hexout);

  // send data to Adafruit IO feeds
  // rgbFeed->save(stringSend);   // ... [OPTION 1]
  rgbFeed->save(hexout);          // ... [OPTION 2]

  
  // delay the loop (millis * 1000 = seconds)
  delay(READ_DELAY * 1000);
}
