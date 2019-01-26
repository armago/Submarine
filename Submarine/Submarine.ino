#include "IRremote.h"

/*-----( Global Constants )-----*/
const int receiver = 11;      // Signal Pin of IR receiver to Arduino Digital Pin 11
int totalseconds = 0;
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
void fill(int fillTime) {
  digitalWrite(5, HIGH);
  delay(fillTime*1000);
  digitalWrite(5, LOW);
 }

 void empty(int emptyTime) {
  digitalWrite(9, HIGH);
  delay(emptyTime*1000);
  digitalWrite(9, LOW);
  }

void pump(int pumpTime){
  int y = 1000*pumpTime;
   for (int i=0; i<=pumpTime; i++){
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
    }
  digitalWrite(5, HIGH);
  delay(y);
  digitalWrite(5, LOW);
  delay(45000);
  digitalWrite(9, HIGH);
  delay(30000);
  digitalWrite(9, LOW);
  }/*-----( Function )-----*/
void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 

  switch(results.value){
    case 0xFF9867:   break; pump(totalseconds); totalseconds=0;
    case 0xFFB04F:   break; fill(totalseconds); totalseconds=0;
    case 0xFF906F:    totalseconds+= 1; break;
    case 0xFF6897:    break;
    case 0xFF30CF:   totalseconds+=10;  break;
    case 0xFF18E7:   totalseconds+=20;  break;
    case 0xFF7A85:  totalseconds+=30;   break;
    case 0xFF10EF:  totalseconds+=40;   break;
    case 0xFF38C7:  totalseconds+=50;   break;
    case 0xFF5AA5:  totalseconds+=60;   break;
    case 0xFF42BD:  totalseconds+=70;   break;
    case 0xFF4AB5:  totalseconds+=80;   break;
    case 0xFF52AD:  totalseconds+=90;   break;
    case 0xFFFFFFFF: break;  

  default: 
    

  }// End Case

} //END translateIR


void setup(){   /*----( SETUP: RUNS ONCE )----*/
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  irrecv.enableIRIn();           // Start the receiver

}/*--(end setup )---*/

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
 
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    translateIR();
    delay(500);
    irrecv.resume();
  }  

}/* --(end main loop )-- */
