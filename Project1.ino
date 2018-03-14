#include <Adafruit_NeoPixel.h>
int LED_COUNT = 8;
int pixelPin = 8;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, pixelPin, NEO_GRB + NEO_KHZ800);

int momPin1 = 2;
int momPin2 = 4;
int momPin3 = 6;
int lightSpeed = 50;
// I <3 bools: Conditions for turning on and off LEDs
bool cond1 = false;
bool cond2 = false;
bool cond3 = false;
bool cond4 = false;
bool cond5 = false;
bool cond6 = false;
bool on = false;
bool off = true;
bool colorChange = false;

//Variables for changing the LED color
long onTime = 0;
int lastVal1 = LOW;
int lastVal2 = LOW;
int lastVal3 = LOW;
int bounceTime = 50;
int holdTime = 250;

void setup() {
  Serial.begin(9600);
  pinMode(momPin1, INPUT);
  pinMode(momPin2, INPUT);
  pinMode(momPin3, INPUT);
  leds.begin();  // Start up the LED strip
  leds.show();   // LEDs don't actually update until you call this function
}

void loop() {
  int momVal1 = digitalRead(momPin1);
  int momVal2 = digitalRead(momPin2);
  int momVal3 = digitalRead(momPin3);

  //**********TURN ON LED************
  if (momVal1 && off) { //If button 1 pressed and lights are off...
    cond1 = true;
  }
  if (cond1) {
    if (momVal3) { //Then button 3...
      cond2 = true;
      cond1 = false;
    }
  }
  if (cond2) {
    if (momVal2) { //And then button 2.
      cond3 = true;
      cond2 = false;
    }
  }
  if (cond3) {
    for (int i = 0; i < LED_COUNT; i++) //Turn on lights
    {
      //Set the pixel to BLUE
      leds.setPixelColor(i, 0, 0, 255);
      leds.show();
      delay(lightSpeed);
    }
    cond3 = false;
    off = false;
    on = true;
    momVal1 = 0; //Reset the values just in case
    momVal2 = 0;
    momVal3 = 0;
  }

  //**********TURN OFF LED************
  if (momVal2 && on) { //If button 2 is pressed and lights are on...
    cond4 = true;
  }
  if (cond4) {
    if (momVal3) { //Then button 3...
      cond5 = true;
      cond4 = false;
    }
  }
  if (cond5) {
    if (momVal1) { //And then button 1.
      cond6 = true;
      cond5 = false;
    }
  }
  if (cond6) {
    for (int x = 0; x < LED_COUNT; x++) //Turn off lights
    {
      int y = LED_COUNT - x;
      leds.setPixelColor((y - 1), 0, 0, 0);
      leds.show();
      delay(lightSpeed);
    }
    cond6 = false;
    off = true;
    on = false;
    momVal1 = 0; //Reset the values just in case
    momVal2 = 0;
    momVal3 = 0;
  }

  //**********Change LED Color To BLUE************

  if (momVal1 == HIGH && lastVal1 == LOW && on) {
    onTime = millis();
  }

  if (momVal1 == HIGH && lastVal1 == HIGH && on) {
    if ((millis() - onTime) > holdTime) {
      for (int i = 0; i < LED_COUNT; i++) //Changes light color
      {
        //Set the pixel to BLUE
        leds.setPixelColor(i, 0, 0, 255);
        leds.show();
        delay(lightSpeed);
      }
    }
  }

  //**********Change LED Color To RED************

  if (momVal2 == HIGH && lastVal2 == LOW && on) {
    onTime = millis();
  }

  if (momVal2 == HIGH && lastVal2 == HIGH && on) {
    if ((millis() - onTime) > holdTime) {
      for (int i = 0; i < LED_COUNT; i++) //Changes light color
      {
        //Set the pixel to RED
        leds.setPixelColor(i, 255, 0, 0);
        leds.show();
        delay(lightSpeed);
      }
    }
  }

  //**********Change LED Color To GREEN************

  if (momVal3 == HIGH && lastVal3 == LOW && on) {
    onTime = millis();
  }

  if (momVal3 == HIGH && lastVal3 == HIGH && on) {
    if ((millis() - onTime) > holdTime) {
      for (int i = 0; i < LED_COUNT; i++) //Changes light color
      {
        //Set the pixel to GREEN
        leds.setPixelColor(i, 0, 255, 0);
        leds.show();
        delay(lightSpeed);
      }
    }
  }
  
  lastVal1 = momVal1;
  lastVal2 = momVal2;
  lastVal3 = momVal3;
}
