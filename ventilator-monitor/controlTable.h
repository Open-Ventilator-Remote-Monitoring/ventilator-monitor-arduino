//Configuration / EEPROM Register Addresses
#define APPLICATION_ID_ADR          0
#define CONTROL_TABLE_VERSION_ADR   2
#define HARDWARE_MODEL_ADR          4
#define HARDWARE_SERIAL_ADR         6
#define FIRMWARE_VERSION_ADR        8
#define COMM_PROTOCOL_VERSION_ADR   10
#define VENTILATOR_ID_ADR           12
#define AUTO_REPORT_STATUS_ADDR     14
#define AUTO_REPORT_INTERVAL_ADDR   16

//Variable Data / RAM register addresses
#define IE_RATIO_ADR                 0
#define PEAK_INSP_PRESSURE_ADR       2
#define TIDAL_VOLUME_ADR             4
#define RESPIRATORY_RATE_ADR         6
#define PEEP_ADR                     8
//#define 

#define COMMAND_BUFFER_SIZE          32
#define DATA_COUNT  4 //Number of data point to track


#define ACTION_PING 
#define ACTION_READ
#define ACTION_WRITE 
#define ACTION_REBOOT
#define ACTION_RESET




#define BASE_RETURN_PACKET_LENGTH  1
#define BASE_RECEIVED_PACKET_LENGTH  2

#define REG_RANGE_MIN 0
#define REG_RANGE_MAX 24

#define APPLCIATION_ID  30559
#define DEFAULT_HARDWARE_MODEL  1
#define DEFAULT_SERIAL          1
#define DEFAULT_ID              1
#define FIRMWARE_VERSION        1
#define CONTROL_TABLE_VERSION   1
#define COMM_PROTOCOL_VERSION   1


#define DEFAULT_AUTO_REPORT_INTERVAL           3
#define DEFAULT_AUTO_REPORT_STATUS             0
