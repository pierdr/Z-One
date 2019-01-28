/*
* Z-One 
* Microcontroller sketch that works with the Z-One Animator software
* Made by Pierluigi Dalla Rosa -- www.pierdr.com
*/
#include "zone.h"

#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ZONE_NUM_LEDS, ZONE_LED_PIN, NEO_GRB + NEO_KHZ800);


String inputString = "";         // a String to hold incoming data
bool stringComplete = false; 
unsigned int pixelDescriptor = 0;

#define C_RED 13
#define C_GRN 6
#define C_BLU 4

#define C_MULTI 1

void setup() {
  
  Serial.begin(115200);
  Serial.println("test");
  
  pixels.begin();
  for(int i=0;i<ZONE_NUM_LEDS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,5,0));
    pixels.show();
    delay(50);
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
  inputString.reserve(200);
  
}

void loop() {

   if (stringComplete) {
      pixels.clear();
    
      for(int i=0;i<ZONE_NUM_LEDS;i++)
      {
          pixels.setPixelColor(i, pixels.Color(bitRead(pixelDescriptor, i)*C_RED*C_MULTI,bitRead(pixelDescriptor, i)*C_GRN*C_MULTI,bitRead(pixelDescriptor, i)*C_BLU*C_MULTI));
      }
      pixels.show();
    
      inputString = "";
      stringComplete = false;
  }
  serialEvent();
}

void serialEvent() {
  while (Serial.available()) {

    char inChar = (char)Serial.read();
   
    inputString += inChar;
   
    if (inChar == '-') {
      stringComplete = true;
      pixelDescriptor = atol(inputString.c_str());
    }
  }
}
