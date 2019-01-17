//www.elegoo.com
//2016.12.9

#include "IRremote.h"
#define ENABLE 5
#define DIRA 3
#define DIRB 4
void onMotor(String f){
  if (f == "clockwise"){
  digitalWrite(DIRA,HIGH); //clockwise
  digitalWrite(DIRB,LOW);
  analogWrite(ENABLE,255); //enable on
    }
  if (f == "counterclockwise"){
  digitalWrite(DIRA,LOW); // counter clockwise
  digitalWrite(DIRB,HIGH);
  analogWrite(ENABLE,255); //enable on
    }
  if (f == "off"){
    digitalWrite(ENABLE,LOW);
    }
  }
 
/*-----( Global Constants )-----*/
const int receiver = 11;      // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 

  switch(results.value){
    
    case 0xFFE01F: Serial.println("DOWN"); onMotor("clockwise");   break; //down
    case 0xFF906F: Serial.println("UP"); onMotor("counterclockwise");  break; //up
    case 0xFF6897:  Serial.println("0"); onMotor("off");    break; //0
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
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();           // Start the receiver
 

} // end setup

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
  
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    translateIR(); 
    delay(500);                 // Do not get immediate repeat
    irrecv.resume();            // receive the next value
  }  
}/* --(end main loop )-- */
