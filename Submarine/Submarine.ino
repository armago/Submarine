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
  Serial.print(pumpTime);
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
  delay(60000);
  Serial.println("Stage 1");
  digitalWrite(9, HIGH);
  Serial.println("Stage 2");
  delay(30000);
  digitalWrite(9, LOW);
  Serial.println("Stage 3");
  }/*-----( Function )-----*/
void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 

  switch(results.value){
    case 0xFF9867: Serial.println("EQ");   break; pump(totalseconds); totalseconds=0;
    case 0xFFB04F: Serial.println("ST/REPT");   break; fill(totalseconds); totalseconds=0;
    case 0xFF906F: Serial.println("UP");   totalseconds+= 1; break;
    case 0xFF6897: Serial.println("0");    break;
    case 0xFF30CF: Serial.println("1");  totalseconds+=10;  break;
    case 0xFF18E7: Serial.println("2");  totalseconds+=20;  break;
    case 0xFF7A85: Serial.println("3"); totalseconds+=30;   break;
    case 0xFF10EF: Serial.println("4"); totalseconds+=40;   break;
    case 0xFF38C7: Serial.println("5"); totalseconds+=50;   break;
    case 0xFF5AA5: Serial.println("6"); totalseconds+=60;   break;
    case 0xFF42BD: Serial.println("7"); totalseconds+=70;   break;
    case 0xFF4AB5: Serial.println("8"); totalseconds+=80;   break;
    case 0xFF52AD: Serial.println("9"); totalseconds+=90;   break;
    case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.print(" other button   ");
    Serial.println(results.value);

  }// End Case

} //END translateIR


void setup(){   /*----( SETUP: RUNS ONCE )----*/
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();           // Start the receiver

}/*--(end setup )---*/

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
 
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    translateIR();
    delay(500);
    irrecv.resume();
  }  
  Serial.println(totalseconds);

}/* --(end main loop )-- */
