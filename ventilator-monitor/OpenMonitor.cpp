/*
Open Ventilator Monitor source.

TODO:
  Reconsider use of EEPROM, not all devices will have this.
  Write easy swap-out methods for different Serial libraries on different devices.
  Alter code design such that data-types of entries in each packet can be handled more easily. At the moment, only 16-bit types are able to be transmitted.
*/

#include "OpenMonitor.h"
unsigned char __omVentilatorData[OM_DATA_COUNT];
uint32_t __omReportTimeTracker = 0; //Specifically assigned as 32-bit long instead of relying on device bit depth.

/********BEGIN PUBLIC FUNCTIONS********/
void omInit(void)
{
  //This function must be called in setup() by the user.
  __omStartupCheck();
  Serial.print("Open Monitor Auto Report Interval: "); Serial.print(EEPROM.read(OM_AUTO_REPORT_INTERVAL_ADDR)); Serial.println(" Seconds");
}

void omAutoReport(void)
{
  //Here we take care of automatically reporting all the ventilator data periodically so the user only needs to call this function once per loop.
  //We should consider setting up an ISR on a timer that will trigger this periodically instead so the user only needs to call setup and we handle the rest.
  if(EEPROM.read(OM_AUTO_REPORT_STATUS_ADDR))
  {
    if(OM_DEBUG_ENABLED){Serial.print("OMDEBUG TIME SINCE LAST REPORT: "); Serial.println(millis() - __omReportTimeTracker);}

    //If the time since the last report passes the specified report interval, transmit the ventilator data packet again.
    if(millis() - __omReportTimeTracker >= 1000*EEPROM.read(OM_AUTO_REPORT_INTERVAL_ADDR))
    {
      if(OM_DEBUG_ENABLED){Serial.println("OMDEBUG TRANSMITTING DATA");}
      
      omTransmitData(); //Transmit ventilator data packet.
      
      if(OM_DEBUG_ENABLED){Serial.println();}
      
      __omReportTimeTracker = millis(); //Reset report time tracker.
    }
  }
}

void omUpdateVentilatorData(int ieRatio, int peakInspiratoryPressure, int tidalVolume, int respiratoryRate, int peep)
{
  //Update ventilator data buffer. The buffer is segmented into 8-bit chunks, so each 16-bit data point must be placed into two array entries.
  __omVentilatorData[OM_IE_RATIO_ADR] = ieRatio % 256;
  __omVentilatorData[OM_IE_RATIO_ADR+1] = (ieRatio >> 8) % 256;
  __omVentilatorData[OM_PEAK_INSP_PRESSURE_ADR] = peakInspiratoryPressure % 256;
  __omVentilatorData[OM_PEAK_INSP_PRESSURE_ADR+1] = (peakInspiratoryPressure >> 8) % 256;
  __omVentilatorData[OM_TIDAL_VOLUME_ADR] = tidalVolume % 256;
  __omVentilatorData[OM_TIDAL_VOLUME_ADR+1] = (tidalVolume >> 8) % 256;
  __omVentilatorData[OM_RESPIRATORY_RATE_ADR] = respiratoryRate % 256;
  __omVentilatorData[OM_RESPIRATORY_RATE_ADR+1] = (respiratoryRate >> 8) % 256;
  __omVentilatorData[OM_PEEP_ADR] = peep % 256;
  __omVentilatorData[OM_PEEP_ADR+1] = (peep >> 8) % 256;
}
void omTransmitData(void)
{
  __omWritePacket(__omVentilatorData, 0, 10); //This isn't great. We can only transmit 16-bit datatypes, and calls like this require us to specify data length in byte size instead of datatype size (i.e. this is 5 ints, but we need to call writePacket with 10 bytes).
}

/********END PUBLIC FUNCTIONS********/


/********BEGIN PRIVATE FUNCTIONS********/
void __omStartupCheck(void)
{
  int applicationId =  __omReadEEPROM(0,2);
  
  //If the application ID in EEPROM doesn't match our specified application ID, we need to re-write all the EEPROM data.
  if ((applicationId != OM_APPLCIATION_ID))
  {
    Serial.println("OpenMonitor discovered out-of-date EEPROM data. Updating to current version...");
    __omWriteEEPROM(OM_APPLICATION_ID_ADR, OM_APPLCIATION_ID, 2);
    __omWriteEEPROM(OM_HARDWARE_MODEL_ADR, OM_DEFAULT_HARDWARE_MODEL ,2);
    __omWriteEEPROM(OM_HARDWARE_SERIAL_ADR, OM_DEFAULT_SERIAL, 2);
    __omWriteEEPROM(OM_VENTILATOR_ID_ADR, OM_DEFAULT_ID, 2);
    __omWriteEEPROM(OM_FIRMWARE_VERSION_ADR, OM_FIRMWARE_VERSION, 2);
    __omWriteEEPROM(OM_CONTROL_TABLE_VERSION_ADR, OM_CONTROL_TABLE_VERSION, 2);
    __omWriteEEPROM(OM_AUTO_REPORT_STATUS_ADDR, OM_DEFAULT_AUTO_REPORT_STATUS, 2);
    __omWriteEEPROM(OM_AUTO_REPORT_INTERVAL_ADDR, OM_DEFAULT_AUTO_REPORT_INTERVAL, 2);
  }
}

long __omReadEEPROM(int address, int dataLength)
{
  //Here we just read and return some arbitrary data from EEPROM.
  long data = 0;
  for(int a = 0; a < dataLength ; a++)
  {
     data = data + (EEPROM.read(address + a) << (8*a)) ; 
  }
  return data;
}

void __omWriteEEPROM(int address, int data, int dataLength)
{
  //Write some arbitrary data to EEPROM.
  if(OM_DEBUG_ENABLED){Serial.print("OMDEBUG WRITING "); Serial.print(data); Serial.println(" TO EEPROM");}
  
  for(int a = 0; a < dataLength ; a++)
  {
     EEPROM.write(address + a, (data >> (8*a)) & 0xff);
  }
}

void __omWritePacket(unsigned char dataArray[], int dataStart, int dataLength)
{
  unsigned char checksum = 0 ;
  int tempChecksum = 0; //very simple checksum. Do not include header (so include everything after length, instruction, parameters, checksum)
  byte packetLength = OM_BASE_RETURN_PACKET_LENGTH + dataLength;

  tempChecksum = packetLength ;//start adding up the cheksum

  Serial.write(0xFF); //header 1
  Serial.write(0xFF); //header 2
  Serial.write(packetLength); //length of packet
  
  //Loop over each byte and transmit it over the serial line.
  for(int i = dataStart; i < dataStart + dataLength; i++)
  {
    tempChecksum = tempChecksum + dataArray[i];
    
    Serial.write(dataArray[i]); //write data parameters
  }

  checksum = ~(tempChecksum%256);

  Serial.write(checksum); //checksum
}
/********END PRIVATE FUNCTIONS********/


