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

//Setup runs once only. It will happen on boot or reset.
void setup() 
{  
  //Initialize Serial port at 9600 baud.
  Serial.begin(9600);

  //Initialize the OpenMonitor library.
  omInit();
}

//Loop cycles forever. First loop call happens immediately after setup().
void loop() 
{
  //Re-assign fake data.
  ieRatio = random(1, 4);
  peakInspiratoryPressure = random(300, 800);
  tidalVolume = random(300, 800);
  respiratoryRate = random(8, 35);
  peep = random(5, 10);
  
  omUpdateVentilatorData(ieRatio, peakInspiratoryPressure, tidalVolume, respiratoryRate, peep); //Update OpenMonitor ventilator data buffer.
  
  omAutoReport(); //Tell OpenMonitor to automatically report its data, if enabled.
  
  delay(500); //Delay for debugging purposes.
}
