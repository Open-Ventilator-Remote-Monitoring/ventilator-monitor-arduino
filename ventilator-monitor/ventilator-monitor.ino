/*
Remote Ventilator

Demo code only

*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
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
