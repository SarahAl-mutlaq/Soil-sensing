
// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);

// Here we are setting up some water thersholds that we will 
// use later. Note that you will need to change these to match
// your soil type and environment. 

int thresholdUp = 400;
int thresholdDown = 250;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:

int sensorPin = 0;


void setup(){
  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:
  
  lcd.begin(16,2);
  
  // Data sent to the display will stay there until it's
  // overwritten or power is removed. This can be a problem
  // when you upload a new sketch to the Arduino but old data
  // remains on the display. Let's clear the LCD using the
  // clear() command from the LiquidCrystal library:
  
  lcd.clear();
}

void loop(){
  // Here we are declaring some strings, which are lines of words,
  // and we want DisplayWords to be the words displayed on
  // the LCD screen, and WaterLevel to be the value that the soil
  // moisture sensor is getting from the soil.
  
  String DisplayWords;
  String WaterLevel;
  
  // We need to set up a pin to get the value that the soil 
  // moisture sensor is outputting, so sensorValue will get the
  // analog value from the sensor pin A0 on the redboard that we 
  // set up earlier.
  
  int sensorValue;
  sensorValue = analogRead(sensorPin);
  
  // We would like to get the value from the soil moisture sensor to 
  // be kept as a string so that we can display that on the LCD, 
  // along with the words "Water Level:" before it, but on the
  // second row, which we use setCursor to place it there, and 
  // again to place the WaterLevel value after it:
  
  WaterLevel = String(analogRead(sensorPin), DEC);
  lcd.setCursor(0,1);
  lcd.print("Water Level:");
  lcd.setCursor(13,1);
  lcd.print(WaterLevel);
  
  // Now we are going to check if the water level is below a 
  // out thresholdDown value we set earlier, and if it is have 
  // words "Dry, Water it!" display one column over on the first 
  // row:
  
  if (sensorValue < thresholdDown){
    String DisplayWords = "Dry, Water it!";
    lcd.setCursor(1,0);
    lcd.print(DisplayWords);
    
  // If the value is not below our thresholdDown value we want to 
  // chack if it is above our thresholdUp value, and if it is 
  // change the display words to "Wet, Leave it!":
  
  } else if (sensorValue > thresholdUp){
    String DisplayWords = "Wet, Leave it!";
    lcd.setCursor(1,0);
    lcd.print(DisplayWords); 
  
  // Otherwise if it is inbetween the two values we want it to 
  // the display it had, so if our soil was really wet and drying 
  // the words would only change to "Dry, Water it!" when it got to the lower threshold
  // (thresholdDown), but if it was dry and getting wetter the words
  // would only change to "Wet, Leave it!" when it got to the upper 
  // threshold (thresholdUp_):
  
  } else {
    lcd.setCursor(1,0);
    lcd.print(DisplayWords);
  }
}


