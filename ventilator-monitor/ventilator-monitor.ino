/*
Remote Ventilator

Demo code only

*/

#include <EEPROM.h>
#include "controlTable.h"
// the setup function runs once when you press reset or power the board
void setup() {


  startupCheck();

  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  startupCheck();
}

// the loop function runs over and over again forever
void loop() {

  if (Serial.available() > 0) {

    String data = Serial.readStringUntil('\n');

    //Serial.println('Recieved: ' + data);

    if(data == "getStats") {

      int ieRatio = random(1, 4);
      int peakInspiratoryPressure = random(60, 80);
      int peep = random(5, 10);
      int respiratoryRate = random(8, 35);
      int tidalVolume = random(300, 800);
      
      String output = "";
    
      output += "{";
      output +=   "\"ventilator\": [";
      output +=     "{";
      output +=       "\"ieRatio\": \"1:";
      output +=         ieRatio;
      output +=       "\",";
      output +=       "\"peakInspiratoryPressure\": \"";
      output +=         peakInspiratoryPressure;
      output +=         "\",";
      output +=       "\"peep\": \"";
      output +=         peep;
      output +=       "\",";
      output +=       "\"respiratoryRate\": \"";
      output +=         respiratoryRate;
      output +=       "\",";
      output +=       "\"tidalVolume\": \"";
      output +=         tidalVolume;
      output +=       "\"";
      output +=     "}";
      output +=   "]";
      output += "}";
  
      Serial.println(output);
  
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     
    }    
  }
}


void startupCheck()
{
  int applicationId1 =  readEEPROM(0,2);
  int applicationId2 =  readEEPROM(14,2);
  
  Serial.print("App ID1 " );
  Serial.print(applicationId1);
  Serial.print("App ID2 ");
  Serial.println(applicationId2);

  if ((applicationId1 != APPLCIATION_ID) && (applicationId2 != APPLCIATION_ID ))
  {
    Serial.println("Error Loading Control Table, Rewriting Control Cable");
    Serial.println(APPLCIATION_ID);
    writeEEPROM(REG_APPLICATION_ID,APPLCIATION_ID,2);
    writeEEPROM(REG_APPLICATION_ID_2,APPLCIATION_ID,2);
    writeEEPROM(REG_HARDWARE_MODEL,DEFAULT_HARDWARE_MODEL,2);
    writeEEPROM(REG_HARDWARE_SERIAL,DEFAULT_SERIAL,2);
    writeEEPROM(REG_VENTILATOR_ID,DEFAULT_ID,2);
    writeEEPROM(REG_FIRMWARE_VERSION,FIRMWARE_VERSION,2);
    writeEEPROM(REG_CONTROL_TABLE_VERSION,CONTROL_TABLE_VERSION,2);
  }
  
}

void initEEPROM()
{

}

long readEEPROM(int address, int dataLength)
{

  long data = 0;
  for(int a = 0; a < dataLength ; a++)
  {
     data = data + (EEPROM.read(address + a) << (8*a)) ; 

  }

  return data;
  
}

long writeEEPROM(int address, int data, int dataLength)
{

     Serial.println(data ) ;

  for(int a = 0; a < dataLength ; a++)
  {
     EEPROM.write(address + a, (data >> (8*a)) & 0xff);

  }
  
}

