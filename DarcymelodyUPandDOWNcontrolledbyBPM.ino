/* 
 adapted from BlinkWithoutDelay example code
 by Oguz Yetkin and Darcy Neal
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 button allows the array to increment up and down while the button is held down, 
 and BPM is controlled by analog input
 */
#include <SoftwareSerial.h>
//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX


int melody[] = {60, 61, 65, 67, 68, 72, 73, 77, 79, 80, 84};   /////////JAPANESE SCALE ACCORDING TO KYUB
int melodyAmount = 11;
const int minBPM = 20;
const int maxBPM = 600;
const int switchPin = 9;  // The switch is on Arduino pin 10
const int ledPin =  13;      // the number of the LED pin
int dir = 1;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
int segment_to_play = 0;


//Warning: nsegments should always be >= 1
int segment(int current_val, int minval, int maxval, int nsegments){
  if(nsegments <=0){
    nsegments = 1;
  }
  int value_step = (maxval - minval)/nsegments;
  int curr_segment = (current_val/value_step) - 1;
  if(curr_segment < 0){
    curr_segment = 0;
  }
  if(curr_segment > nsegments - 1){
    curr_segment = nsegments - 1;
  }
  return curr_segment;
}


  

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT); 
  pinMode(switchPin, INPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
      midiSerial.begin(31250);
     
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
  
  int BPM = map(analogRead(A0), 0, 1023, minBPM, maxBPM);
  Serial.println(BPM);
  
  long interval = (1000/(BPM/60.0));

//plays scale automatically
//if(currentMillis - previousMillis > interval) {
//plays scale only if digitalRead = TRUE  
  if(currentMillis - previousMillis > interval  && digitalRead (switchPin)) {  
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

     usbMIDI.sendNoteOn(melody[segment_to_play], 0x90, 0x40);
     segment_to_play += dir;  //increments... means s.t.p. = s.t.p. + dir
   
    if ((segment_to_play==melodyAmount-1) || (segment_to_play<=0)){
     dir*=-1;  //  means dir = dir * -1  (reverse direction shortcut)
     Serial.print ("segment_to_play  ");
     Serial.println (segment_to_play);
   }
   

    segment_to_play %= melodyAmount; //s.t.p. = s.t.p. % m.A. 

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
     else
       ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

