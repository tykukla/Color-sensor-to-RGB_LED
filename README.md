# Color-sensor-to-RGB_LED

## Overview
This is a hobby project, no science here! 

This project uses a **TCS34725** RGB sensor from Adafruit to detect the color of a light source (within the visible spectrum) and send the color data to a receiver attached to an RGB LED **WS2812 Neopixel** strip. 

I use the project to set the color of a lamp's light in Tennessee based on the color out of a window in California. 

This project is inspired by a Master's project that I read about in a NY Times article where a student built a similar setup to share the color of a specific location in a lamp they made for their mother. (I believe it was a RISD Master's project, but I can't find the original article). If you know of the article, please let me know so I can cite it here! 

There are other, similar projects around the web. One is by Emmanuel Zambrano, who developed Project Aura to share color data with web design features such as the background of a website. See an article here: https://appliedtech.iit.edu/smart-lab/projects/aura and github link: https://github.com/illinoistech-itm/aura.


## How it works
The project is run by two Adafruit HUZZAH32 Feather boards with ESP32 MCU chips with wifi capabilities. One Feather board is connected to an RGB light sensor to detect the color of the light. This board sends the light color to Adafruit IO, where users can set up a free account to send, receive, and store data. The second Feather board reads the Adafruit IO light color data and displays it on an RGB LED strip. The two Feather boards do not need to be connected to the same wifi network, allowing color data in one location to be transferred anywhere in the world where wifi is available. 



## What you'll find here
This project includes the fritzing wiring schematics and code for each Feather board (sender and receiver) as well as a bill of materials. Much of the color sensor code is adapted from Adafruit's TCS34725 sensor Arduino tutorials, which are fantastic. I'm sure my code is not the most elegant, but it works and may serve as a helpful starting point for others. 


## Room for improvement
There are many changes that would improve the design and function! I would love to hear about any improvements you make and include them here (with credit and explicit permission). Here are just a couple things that can be immediately improved. 

* **Color transitions**: The RGB LED abruptly changes from one color to the next when new data is collected. It would be nice to write a function that remembers the previous color and fades between that and the new color over some set amount of time (maybe scaled to the distance between the two colors).
* **Brightness**: The LED's brightness is set by the RGB values, but a greater range of brightness variability could be achieved by using the "lux" data to control the LED brightness parameter. 
* **Sensor LED**: The TCS34725 has a bright white LED to illuminate an object. I've connected the LED to ground to turn it off because I'm interested in sensing environmental light and the tiny LED can't illuminate my backyard. However, one could add a switch here to turn this light on and off as needed.  

Please reach out if you have any questions! 
