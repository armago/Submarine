//www.elegoo.com
//2016.12.9

#include "IRremote.h"
#include <Servo.h>
int pos = 90;
 Servo hydro; //make servo object
/*-----( Global Constants )-----*/
const int receiver = 11;      // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 

  switch(results.value){
    
    case 0xFFE01F: Serial.println("DOWN"); pos -= 20; hydro.write(pos);    break; //down
    case 0xFF906F: Serial.println("UP"); pos += 20;  hydro.write(pos);  break; //up
    case 0xFF6897:  Serial.println("0"); pos = 90; hydro.write(pos);    break; //0
    case 0xFF30CF: Serial.println("1");    break; //1
    case 0xFF18E7: Serial.println("2");    break; //2
    case 0xFF7A85: Serial.println("3");    break; //3
    case 0xFF10EF: Serial.println("4");    break; //4
    case 0xFF38C7: Serial.println("5");    break; //5
    case 0xFF5AA5: Serial.println("6");    break; //6
    case 0xFF42BD: Serial.println("7");    break; //7
    case 0xFF4AB5: Serial.println("8");    break; //8
    case 0xFF52AD: Serial.println("9");    break; //9
    case 0xFFFFFFFF: Serial.println(" REPEAT");break; //repeat  

  default: 
    Serial.print(" other button   ");
    Serial.println(results.value);

  }// End Case

} //END translateIR

void setup(){   /*----( SETUP: RUNS ONCE )----*/
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();           // Start the receiver
  hydro.attach(9); // servo is on pin 3

} // end setup

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
  
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    translateIR(); 
    delay(500);                 // Do not get immediate repeat
    irrecv.resume();            // receive the next value
  }  
}/* --(end main loop )-- */
