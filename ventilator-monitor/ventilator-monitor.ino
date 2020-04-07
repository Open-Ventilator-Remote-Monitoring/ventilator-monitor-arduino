/*
Remote Ventilator Usage Demo.

Demo code only

*/
#include "OpenMonitor.h"

int ieRatio = 0;
int peakInspiratoryPressure = 0;
int tidalVolume = 0;
int respiratoryRate = 0;
int peep = 0;

// the setup function runs once when you press reset or power the board
void setup() 
{  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //Initialize OpenMonitor library.
  omInit();
}

// the loop function runs over and over again forever
void loop() 
{
  ieRatio = random(1, 4);
  peakInspiratoryPressure = random(300, 800);
  tidalVolume = random(300, 800);
  respiratoryRate = random(8, 35);
  peep = random(5, 10);
  
  omUpdateVentilatorData(ieRatio, peakInspiratoryPressure, tidalVolume, respiratoryRate, peep); //Update OpenMonitor ventilator data buffer.
  omAutoReport();
  
  delay(500);
}
