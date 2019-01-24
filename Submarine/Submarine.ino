//www.elegoo.com
//2016.12.9

#include "IRremote.h"

/*-----( Global Constants )-----*/
const int receiver = 11;      // Signal Pin of IR receiver to Arduino Digital Pin 11
int x = 0;
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
void fill(int b) {
  digitalWrite(5, HIGH);
  delay(b*1000);
  digitalWrite(5, LOW);
 }

 void empty(int c) {
  digitalWrite(9, HIGH);
  delay(c*1000);
  digitalWrite(9, LOW);
  }

void pump(int z){
  Serial.print(z);
  int y = 1000*z;
   for (int i=0; i<=z; i++){
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
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE"); empty(x); x=0;    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");   x+= 1; break;
    case 0xFF9867: Serial.println("EQ");   pump(x); x=0; break;
    case 0xFFB04F: Serial.println("ST/REPT");Serial.println(x); x=0; fill(x); break;
    case 0xFF6897: Serial.println("0");    break;
    case 0xFF30CF: Serial.println("1");  x+=10;  break;
    case 0xFF18E7: Serial.println("2");  x+=20;  break;
    case 0xFF7A85: Serial.println("3"); x+=30;   break;
    case 0xFF10EF: Serial.println("4"); x+=40;   break;
    case 0xFF38C7: Serial.println("5"); x+=50;   break;
    case 0xFF5AA5: Serial.println("6"); x+=60;   break;
    case 0xFF42BD: Serial.println("7"); x+=70;   break;
    case 0xFF4AB5: Serial.println("8"); x+=80;   break;
    case 0xFF52AD: Serial.println("9"); x+=90;   break;
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
    delay(500);                 // Do not get immediate repeat
    irrecv.resume();            // receive the next value
  }  
}/* --(end main loop )-- */
