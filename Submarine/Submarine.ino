#include "IRremote.h"       // Library for IR Transmitter and Reciever

const int receiver = 3;      // Signal Pin of IR receiver to Arduino Pin 3
int totalseconds = 0;       // Variable for run time of pumps
int emptyPin = 11;          // Signal Pin from Arduino Pin 11 to Empty Pump
int fillPin = 12;           // Signal Pin from Arduino Pin 12 to Fill Pump

IRrecv irrecv(receiver);     // Create instance of 'irrecv'
decode_results results;      // Create instance of 'decode_results'
void fill(int fillTime) {    // Function to fill tanks
  digitalWrite(fillPin, HIGH);
  delay(fillTime*1000);
  digitalWrite(fillPin, LOW);
 } // End Fill Function

 void empty(int emptyTime) { // Function to empty tanks
  digitalWrite(emptyPin, HIGH);
  delay(emptyTime*1000);
  digitalWrite(emptyPin, LOW);
  } // End Empty Function

void pump(int pumpTime){     // Function to fill tank, wait, then empty tank
  digitalWrite(fillPin, HIGH);
  delay(1000*pumpTime);
  digitalWrite(fillPin, LOW);
  delay(45000);
  digitalWrite(emptyPin, HIGH);
  delay(30000);
  digitalWrite(emptyPin, LOW);
  } // End Pump Function
void translateIR() {          // Interprets IR signal and takes action
// describing Remote IR codes 

  switch(results.value){
    case 0xFF9867:   pump(totalseconds); totalseconds=0;  break;//eq button
    case 0xFF02FD: empty(totalseconds); totalseconds = 0; break; //pause button
    case 0xFFB04F:    fill(totalseconds); totalseconds=0; break; //st/rept button
    case 0xFF906F:    totalseconds+= 1; break;
    case 0xFF6897:    break;
    case 0xFF30CF:   totalseconds+=10;  break; // 1
    case 0xFF18E7:   totalseconds+=20;  break; // 2
    case 0xFF7A85:  totalseconds+=30;   break; // 3
    case 0xFF10EF:  totalseconds+=40;   break; // 4
    case 0xFF38C7:  totalseconds+=50;   break; // 5
    case 0xFF5AA5:  totalseconds+=60;   break; // 6
    case 0xFF42BD:  totalseconds+=70;   break; // 7
    case 0xFF4AB5:  totalseconds+=80;   break; // 8
    case 0xFF52AD:  totalseconds+=90;   break; // 9
    case 0xFFFFFFFF: break;  

  default: 
    digitalWrite(6, HIGH);

  }// End Case

} //End translateIR


void setup(){  // Start Setup
  pinMode(fillPin, OUTPUT);      // Enable pin for Fill Pump
  pinMode(emptyPin, OUTPUT);     // Enable pin for Empty Pump
  irrecv.enableIRIn();           // Start the receiver

} // End Setup

void loop(){   
 
  if (irrecv.decode(&results))   // Checks for IR signal
  {
    translateIR();
    delay(500);
    irrecv.resume();
  }  

} // End Loop
