//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-midi-output-using-an-arduino/
#include <SoftwareSerial.h>
 
const int switchPin = 10;  // The switch is on Arduino pin 10
const int LEDpin = 13;     //  Indicator LED
 
 // Variables:
 byte note = 0;              // The MIDI note value to be played
 int AnalogValue = 0;        // value from the analog input
 int lastNotePlayed = 0;     // note turned on when you press the switch
 int lastSwitchState = 0;    // state of the switch during previous time through the main loop
 int currentSwitchState = 0;

//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX
 
 void setup() {
   //  set the states of the I/O pins:
   pinMode(switchPin, INPUT);
   pinMode(LEDpin, OUTPUT);
   //  Set MIDI baud rate:
  Serial.begin(9600);
   blink(3);
 
    midiSerial.begin(31250);
 
 }
 
 void loop() {
  //unsigned int switchPressTime = 0;   //DH

   //  My potentiometer gave a range from 0 to 1023:
   AnalogValue = analogRead(A0);
   //  convert to a range from 0 to 127:
   note = AnalogValue/8;
   currentSwitchState = digitalRead(switchPin);
   // Check to see that the switch is pressed:
   if (currentSwitchState == 1) {
     //  check to see that the switch wasn't pressed last time
     //  through the main loop:
     if (lastSwitchState == 0) {
      //switchPressTime = millis();  //DH
      
       // set the note value based on the analog value, plus a couple octaves:
       // note = note + 60;
       
    // hardwaremidi (velocity, note, channel);
    //   noteOn(0x90, note, 0x40);
    
    // softwaremidi (note, velocity, channel);
      usbMIDI.sendNoteOn(note, 0x90, 0x40);

       // save the note we played, so we can turn it off:
       lastNotePlayed = note;
       digitalWrite(LEDpin, HIGH);
     }
   }
   else {   // if the switch is not pressed:
     //  but the switch was pressed last time through the main loop:
     if (lastSwitchState == 1) {
       //  stop the last note played:

   //    hardwareMidi  (velocity, note, channel);
   //     noteOn(0x90, lastNotePlayed, 0x00);
           //  softwareMidi  (note, velocity, channel);
        usbMIDI.sendNoteOff(lastNotePlayed, 0x90, 0x00);

        digitalWrite(LEDpin, LOW);
       

        }
   }
/*
 * 
     if (switchPressTime != 0 && switchPressTime + 500 < millis())
     {
        noteOn(0x90, lastNotePlayed, 0x00);
        digitalWrite(LEDpin, LOW);
        switchPressTime = 0;
     }
 */
   //  save the state of the switch for next time
   //  through the main loop:
   lastSwitchState = currentSwitchState;
 }
 /*
 //  plays a hardware MIDI note.  Doesn't check to see that
 //  cmd is greater than 127, or that data values are  less than 127:
 void noteOn(byte cmd, byte data1, byte  data2) {
   midiSerial.write(cmd);
  midiSerial.write(data1);
   midiSerial.write(data2);
 
  //prints the values in the serial monitor so we can see what note we're playing
   Serial.print("cmd: ");
    Serial.print(cmd);
      Serial.print(", data1: ");
  Serial.print(data1);
     Serial.print(", data2: ");
   Serial.println(data2);
 }
*/ 
 // Blinks an LED 3 times
 void blink(int howManyTimes) {
   int i;
   for (i=0; i< howManyTimes; i++) {
     digitalWrite(LEDpin, HIGH);
     delay(100);
     digitalWrite(LEDpin, LOW);
     delay(100);
   }
 }
