# Arduino App - Open Ventilator Remote Monitoring Project
### Goal
Create a lightweight arduino library to run on the ventilator arduino board to send ventilator data to the raspberry pi. The raspberry pi will then in turn forward the data to the central monitoring dashboard (javascript web application) for the user to view.

### Caution
This software is currently only a concept - it is neither approved nor intended to be used in any medical setting. Currently, the application only outputs random demo/sample data.

### Why Arduino? 
Most of the rapidly manufacturable ventilator design teams we are talking to are using Arduino boards to control their circuits. Arduino's are cheap, easy to program, available in large quantities, locally soureable, and reliable (by consumer hardware standards).

### Current State of the App
**As of 3-Apr-2020:** Currently, the app is in demo/testing mode only. The arduino sketch simply responds to requests from the raspberry pi over USB Serial and returns an array of 5 parameters containing random (fake) data.

### How do I set up an Arduino for Development & Testing?
1. Obtain an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) or equivalent for about $23 USD. Arduino boards are widely available so shop around for quick shipping (check out [Amazon](https://www.amazon.com/s?k=arduino+uno+r3)). If you're new to Arduino develpoment, you might want to grab a starter kit containing an assortment of goodies/extras for a few more dollars.
2. Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software)
3. If you're new to Arduino, work through some of the [Built-in](https://www.arduino.cc/en/Tutorial/BuiltInExamples) tutorials to familize yourself with how Arduino works (especially those relating to Serial communication).
4. Download the code from this repo and upload it to your Arduino Board using the Arduino IDE
