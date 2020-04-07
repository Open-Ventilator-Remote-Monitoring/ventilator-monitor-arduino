#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#endif

#include <EEPROM.h>

//Configuration / EEPROM Register Addresses
#define OM_APPLICATION_ID_ADR          0
#define OM_CONTROL_TABLE_VERSION_ADR   2
#define OM_HARDWARE_MODEL_ADR          4
#define OM_HARDWARE_SERIAL_ADR         6
#define OM_FIRMWARE_VERSION_ADR        8
#define OM_COMM_PROTOCOL_VERSION_ADR   10
#define OM_VENTILATOR_ID_ADR           12
#define OM_AUTO_REPORT_STATUS_ADDR     14
#define OM_AUTO_REPORT_INTERVAL_ADDR   16

//Variable Data / RAM register addresses
#define OM_IE_RATIO_ADR                 0
#define OM_PEAK_INSP_PRESSURE_ADR       2
#define OM_TIDAL_VOLUME_ADR             4
#define OM_RESPIRATORY_RATE_ADR         6
#define OM_PEEP_ADR                     8
//#define 

#define OM_COMMAND_BUFFER_SIZE          32
#define OM_DATA_COUNT  10 //Number of data point to track

#define OM_BASE_RETURN_PACKET_LENGTH  1
#define OM_BASE_RECEIVED_PACKET_LENGTH  2

#define OM_REG_RANGE_MIN 0
#define OM_REG_RANGE_MAX 24

#define OM_APPLCIATION_ID  30560
#define OM_DEFAULT_HARDWARE_MODEL  1
#define OM_DEFAULT_SERIAL          1
#define OM_DEFAULT_ID              1
#define OM_FIRMWARE_VERSION        1
#define OM_CONTROL_TABLE_VERSION   1
#define OM_COMM_PROTOCOL_VERSION   1


#define OM_DEFAULT_AUTO_REPORT_INTERVAL           3
#define OM_DEFAULT_AUTO_REPORT_STATUS             1

#define OM_DEBUG_ENABLED 1

/********BEGIN PUBLIC FUNCTIONS********/
void omInit(void);
void omUpdateVentilatorData(int ieRatio, int peakInspiratoryPressure, int tidalVolume, int respiratoryRate, int peep);
void omAutoReport(void);
void omTransmitData(void);
/********END PUBLIC FUNCTIONS********/


/********BEGIN PRIVATE FUNCTIONS********/
void __omStartupCheck(void);
long __omReadEEPROM(int address, int dataLength);
void __omWriteEEPROM(int address, int data, int dataLength);
void __omWritePacket(unsigned char dataArray[], int dataStart, int dataLength);
/********END PRIVATE FUNCTIONS********/
