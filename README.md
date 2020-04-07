## Open Ventilator Remote Monitoring Project - Arduino App

This git repo is for the code on the **Ventilator (Arduino)**

### Architecture Overview
| [Heroku Cloud Server & Web Browser Repo](https://github.com/Open-Ventilator-Remote-Monitoring/ventilator-remote-monitoring) | [Raspberry Pi (Network Adapter) Repo](https://github.com/Open-Ventilator-Remote-Monitoring/remote-ventilator-monitor-pi) | Ventilator (Arudino) Repo |
| ----------- | ----------- | ----------- |
| Ruby on Rails | Flask | Arduino Board |
| Javascript | Python | C++ |

### Goal
Create a lightweight arduino library to run on the ventilator arduino board to send ventilator data to the raspberry pi. The raspberry pi will then in turn forward the data to the central monitoring dashboard (javascript web application) for the user to view.

### Caution
This software is currently only a concept - it is neither approved nor intended to be used in any medical setting. Currently, the application only outputs random demo/sample data.

### Why Arduino? 
Most of the rapidly manufacturable ventilator design teams we are talking to are using Arduino boards to control their circuits. Arduino's are cheap, easy to program, available in large quantities, locally soureable, and reliable (by consumer hardware standards).

### Current State of the App
**As of 3-Apr-2020:** Currently, the app is in demo/testing mode only. The arduino sketch simply responds to requests from the raspberry pi over USB Serial and returns an array of 5 parameters containing random (fake) data.

### How do I set up an Arduino for Development & Testing?
1. Obtain an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) or equivalent (~$23 USD). Arduino boards are widely available so shop around for quick shipping (check out [Amazon](https://www.amazon.com/s?k=arduino+uno+r3)). If you're new to Arduino develpoment, you might want to grab a starter kit containing an assortment of goodies/extras for a few more dollars. Be sure to pick up a standard [USB A-to-B Cable](https://store.arduino.cc/usa/usb-2-0-cable-type-a-b) if you don't already have one.
2. Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software)
3. If you're new to Arduino, work through some of the [Built-in](https://www.arduino.cc/en/Tutorial/BuiltInExamples) tutorials to familize yourself with how Arduino works (especially those relating to Serial communication).
4. Download/Clone the code from this repo and upload it to your Arduino Board using the Arduino IDE
5. You can power the arduino by either plugging in a standard [9V power supply](https://www.amazon.com/Arduino-Power-Supply-Adapter-110V/dp/B018OLREG4) to the power plug or by plugging it into a USB port. Plugging your Arduino into a Raspberry Pi via the USB cable should give it sufficent power to run, provided that the Raspberry Pi itself is plugged in to a power supply with sufficient amperage to run both the Pi and the Arduino.





*** Byte based Comms

Inspired by ROBOTIS DYNAMIXEL 1.0 protocol

http://emanual.robotis.com/docs/en/dxl/protocol1/

####Data Register Table (RAM)

|Data | Register | Size(Bytes) | Description|
| --- | --- | --- | --- |
|IE Ratio |0| 2|
|Peak Inspiratory Pressure |2| 2|
|Tidal Volume		 |4| 2|
|Respiratory Rate		 |6| 2|
|PEEP		 |8| 2|



####Config Register Table (EEPROM)
|Data | Register | Size(Bytes) | Description|
| --- | --- | --- | --- |
|EEPROM | 
|Application Identifier |0| 2| Used internally to verify data table has been written at least ones |
|Control Table Version |2| 2| Use to verify control table matches with what software is expecting|
|Harware Model |4| 2| ID of hardware model running( i.e. Arduino Uno, Arduino Mega, etc)|
|Harware Serial |6| 2| Serial nunber assigned to HW|
|Firmware Version |8| 2|
|Communication Protocol Version |10| 2|
|Ventilator ID |12| 2|
|Auto Report Status |14| 2|
|Auto Report Interval|16| 2|



####Host Packet (from Pi)

|Header 1| Header 2 | Length | Instruction | Param 1 | ... | Param N | Checksum|
| ---  | --- | --- | --- | --- | --- | --- | --- |
|0xFF | 0xFF | Length | Instruction | Param 1 | Params | Param N | Checksum


####Reply Packet (From Arduino)

|Header 1| Header 2 | Length | Error | Param 1 | ... | Param N | Checksum|
| ---  | --- | --- | --- | --- | --- | --- | --- |
|0xFF | 0xFF | Length | Error | Param 1 | Params | Param N | Checksum



####Instructions
|Instruction | Data |
| --- | --- |
|Ping | 0x01|
|Read Data | 0x02|
|Reboot | 0x03|
|Reset | 0x04|
|Read Config | 0x05|
|Write Config | 0x06|