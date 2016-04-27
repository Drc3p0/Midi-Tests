#include <SoftwareSerial.h>
//trying to use get midi to cycle up and down throgh melody notes...then add a potentiometer that is mapped to cycle through the melody array.

    // notes in the melody:
int melody[] = {60, 61, 65, 67, 68, 72, 73, 77, 79, 80, 84};   /////////JAPANESE SCALE ACCORDING TO KYUB
int melodyAmount = 11;
int lastSwitchState = 0;    // state of the switch during previous time through the main loop
int currentSwitchState = 0;
const int switchPin = 10;  // The switch is on Arduino pin 10
const int LEDpin = 13;     //  Indicator LED

//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX
 

void setup(){
 //  set the states of the I/O pins:
  pinMode(switchPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);     //  Set MIDI baud rate:
   blink(3);
 
    midiSerial.begin(31250);

}

void loop(){

currentSwitchState = digitalRead(switchPin);
for (int thisNote = 0; thisNote < melodyAmount; thisNote++) 

//  melody[] = thisNote;
   // Check to see that the switch is pressed:
   if (currentSwitchState == 1) {
     //  check to see that the switch wasn't pressed last time through the main loop: 
     if (lastSwitchState == 0) {
    // start a note via softwareMIDI (note, velocity, channel);
    for (int thisNote = 0; thisNote < melodyAmount; thisNote++) {

             usbMIDI.sendNoteOn(melody[thisNote], 0x90, 0x40);
delay(100); 
             usbMIDI.sendNoteOn(melody[thisNote], 0x90, 0x40);
    }
         //    delay(100);
for (int thisNote = melodyAmount - 1; thisNote >= 0; thisNote--){
 usbMIDI.sendNoteOn(melody[thisNote], 0x90, 0x40);
delay(100); 
             usbMIDI.sendNoteOn(melody[thisNote], 0x90, 0x40);
}
       // save the note we played, so we can turn it off:
 //      lastNotePlayed = note;
       digitalWrite(LEDpin, HIGH);
     }
   }

     else {   // if the switch is not pressed:
     //  but the switch was pressed last time through the main loop:
     if (lastSwitchState == 1) {
       //  stop the last note played:
  
                   //    (note, velocity, channel);
        usbMIDI.sendNoteOff(melody[thisNote], 0x90, 0x40);

       digitalWrite(LEDpin, LOW);
      } 
    }
    lastSwitchState = currentSwitchState;

}

//  plays a MIDI note.  Doesn't check to see that
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
/*
////////////////MILLIS MATH///////////////////
currentMillis = analogRead(A1);
currentMillis = millis();  // capture current "time"
// all time related variable are unsigned long
elapsedMillis = currentMillis - previousMillis; // see how much time has passed
if (elapsedMillis >= duration){ // time for next occurrence of event?
previousMillis = previousMillis + duration;  // set up time for next occurrence of event
arrayIndex = arrayIndex +1; // increment pointer
if (arrayIndex == arrayEnd){ 
arrayIndex = 0;  // reset to beginning
}
// do action based on value stored at dataArray[arrayIndex];
}



      
               //              (note, velocity, channel);
    //         usbMIDI.sendNoteOn(melody[], 0x90, 0x40);
             //MILLIS DELAY = TO NOTEDURATIONS
      //       usbMIDI.sendNoteOff(melody[], 0x90, 0x40);
             //MILLIS DELAY = TO NOTEDURATIONS

    
 //noteDurations[] = analogRead (A1);
 // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:

     //  int noteDuration = 1000 / noteDurations[];
       
         //              (note, velocity, channel);
    //         usbMIDI.sendNoteOn(note, 0x90, 0x40);

   // tone(8, melody[thisNote], noteDuration);

   */
