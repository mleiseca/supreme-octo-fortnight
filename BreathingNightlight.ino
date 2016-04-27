/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
#include <math.h>


int GREEN = 9;
int YELLOW = 10;
int RED = 11;
float NINE_HOURS = 1000.0 * 60 * 60 * 9;
float TEN_MINUTES = 1000.0 * 60 * 10 ;
float ONE_MINUTE = 1000.0 * 60 ;
float DURATION = NINE_HOURS;
float YELLOW_INTERVAL = 3.0/4.0; 

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  Serial.begin(9600);
}

float blend (float val, float blend_value) {
  if (blend_value > 1) {
    return val;
  }
  if (blend_value < 0) {
    return 0;
  }
  return val * blend_value;
}

// the loop function runs over and over again forever
void loop() {
  // adapted from https://jsfiddle.net/nfj68km7/6/
  float val = (exp(sin(millis()/1000.0))- 0.36787944)*0.36787944 * 108.0;

  // from http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
  //float val = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  float x = millis() / DURATION;
  float yellow_val = (x > YELLOW_INTERVAL && x < 1) ? val : 0;
  float green_val = x > 1 ? val : 0;
  float red_val = blend(val, log((-x * 3 ) + 3)+ 1.5); 

  if (false && millis() % 1000  == 0) { 
    Serial.println("*****");
    Serial.println(x);

    Serial.println(red_val);
    Serial.println(yellow_val);
    Serial.println(green_val);
  }
  analogWrite(GREEN, green_val);
  analogWrite(YELLOW, yellow_val);
  analogWrite(RED, red_val);
}
