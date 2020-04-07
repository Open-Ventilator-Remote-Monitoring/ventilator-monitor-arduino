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
  Serial.println(EEPROM.read(AUTO_REPORT_INTERVAL_ADDR));
}

// the loop function runs over and over again forever
void loop() {
      unsigned char ventilatorData[DATA_COUNT];
      unsigned char commandBuffer[COMMAND_BUFFER_SIZE];

  
      int ieRatio = random(1, 4);
      int peakInspiratoryPressure = random(300, 800);
      int tidalVolume = random(300, 800);
      int respiratoryRate = random(8, 35);
      int peep = random(5, 10);
      static unsigned long lastReportTime = 0;


      updateControlTable(ventilatorData, ieRatio, peakInspiratoryPressure, tidalVolume, respiratoryRate, peep);
      //if(EEPROM.read(AUTO_REPORT_STATUS_ADDR) == 1) //check if auto reporting is on
      //OVERIDE FOR TESTING
      if(1==1) //check if auto reporting is on 
      {
        if (millis() > ( lastReportTime + ( 1000*EEPROM.read(AUTO_REPORT_INTERVAL_ADDR)) ) ) //check if its' been longer than the predfined interval to send a message
        {
          writePacket(ventilatorData, 0, 10); // write all data
          lastReportTime = millis();
        }
        
      }
  
    checkForCommands(commandBuffer);


}


void startupCheck()
{
  int applicationId =  readEEPROM(0,2);

  if ((applicationId != APPLCIATION_ID))
  {
    Serial.println("Error Loading Control Table, Rewriting Control Cable");
    writeEEPROM(APPLICATION_ID_ADR,APPLCIATION_ID,2);

    writeEEPROM(HARDWARE_MODEL_ADR,DEFAULT_HARDWARE_MODEL,2);
    writeEEPROM(HARDWARE_SERIAL_ADR,DEFAULT_SERIAL,2);
    writeEEPROM(VENTILATOR_ID_ADR,DEFAULT_ID,2);
    writeEEPROM(FIRMWARE_VERSION_ADR,FIRMWARE_VERSION,2);
    writeEEPROM(CONTROL_TABLE_VERSION_ADR,CONTROL_TABLE_VERSION,2);
    writeEEPROM(AUTO_REPORT_STATUS_ADDR,DEFAULT_AUTO_REPORT_STATUS,2);
    writeEEPROM(AUTO_REPORT_INTERVAL_ADDR,DEFAULT_AUTO_REPORT_INTERVAL,2);
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


void writePacket(unsigned char dataArray[], int dataStart, int dataLength)
{
  unsigned char checksum = 0 ;
  int tempChecksum = 0; //very simple checksum. Do not include header (so include everything after length, instruction, parameters, checksum)
  byte packetLength = BASE_RETURN_PACKET_LENGTH + dataLength;

  tempChecksum = packetLength ;//start adding up the cheksum

  Serial.write(0xFF); //header 1
  Serial.write(0xFF); //header 2
  Serial.write(packetLength); //length of packet
  

  for(int i = dataStart; i < dataStart + dataLength; i++)
  {
    tempChecksum = tempChecksum + dataArray[i];
    
    Serial.write(dataArray[i]); //write data parameters
  }

  checksum = ~(tempChecksum%256);

  Serial.write(checksum); //checksum


}

void updateControlTable(unsigned char ventilatorData[], int ieRatio, int peakInspiratoryPressure, int tidalVolume, int respiratoryRate, int peep)
{
  ventilatorData[IE_RATIO_ADR] = ieRatio % 256;
  ventilatorData[IE_RATIO_ADR+1] = (ieRatio >> 8) % 256;
  ventilatorData[PEAK_INSP_PRESSURE_ADR] = peakInspiratoryPressure % 256;
  ventilatorData[PEAK_INSP_PRESSURE_ADR+1] = (peakInspiratoryPressure >> 8) % 256;
  ventilatorData[TIDAL_VOLUME_ADR] = tidalVolume % 256;
  ventilatorData[TIDAL_VOLUME_ADR+1] = (tidalVolume >> 8) % 256;
  ventilatorData[RESPIRATORY_RATE_ADR] = respiratoryRate % 256;
  ventilatorData[RESPIRATORY_RATE_ADR+1] = (respiratoryRate >> 8) % 256;
  ventilatorData[PEEP_ADR] = peep % 256;
  ventilatorData[PEEP_ADR+1] = (peep >> 8) % 256;

}


int checkForCommands(unsigned char commandBuffer[])
{
  static unsigned char offset = 0;
  unsigned char packetStatus = 0; //0 = no new data, 1 = in status, 2 = complete, 3 = new packet
  unsigned char data;
  while(Serial.available() > 0)
  {
    data = Serial.read();
    if (offset == 0 && data == 0xFF)  //check for first header
    {
        offset = offset + 1;
        packetStatus = 1;
    }

    else if (offset == 1 && data == 0xFF)  //check for first header
    {
        offset = offset + 1;
        packetStatus = 1;
    }

    else if (offset == 2)  //check for length
    {
        commandBuffer[offset] = data;
        offset = offset + 1;
        packetStatus = 1;
    }

    else if ( (offset >= 3) && (offset < (commandBuffer[2] - 2)) )
    {
      
        commandBuffer[offset] = data;
        offset = offset + 1;
        packetStatus = 1;
    }

       
    else if  (offset == (2 + commandBuffer[2]) )  //check for checksum
    {
        commandBuffer[offset] = data;
        offset = 0;
        //verify checksum
        //report if packet is good or not
        
    }

    
  } //end while

} //end function


