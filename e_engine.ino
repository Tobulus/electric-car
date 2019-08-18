#include "IRremote.h"

// IR
int receiver = 8;
IRrecv irrecv(receiver);
decode_results results;
unsigned long lastSignal = 0;
unsigned long lastSignalMillis;

//Engine
#define In1_1 52
#define In2_1 50
#define In3_1 48
#define In4_1 46

#define In1 53
#define In2 51
#define In3 49
#define In4 47
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(In1_1, OUTPUT);
  pinMode(In2_1, OUTPUT);
  pinMode(In3_1, OUTPUT);
  pinMode(In4_1, OUTPUT);
}

void move(unsigned long direction){
  if (direction == 0xFF18E7){
    forward();
  } else if (direction == 0xFF10EF) {
    left();
  } else if (direction == 0xFF5AA5){
    right();
  } else if (direction == 0xFF4AB5){
    backward();
  }
}

void forward() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In1_1, HIGH);
  digitalWrite(In2_1, LOW);
  
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In3_1, LOW);
  digitalWrite(In4_1, HIGH);
}

void backward(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In1_1, LOW);
  digitalWrite(In2_1, HIGH);
  
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In3_1, HIGH);
  digitalWrite(In4_1, LOW);
}

void left() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In1_1, LOW);
  digitalWrite(In2_1, HIGH);
  
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In3_1, HIGH);
  digitalWrite(In4_1, LOW);
}

void right(){
 digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In1_1, HIGH);
  digitalWrite(In2_1, LOW);
  
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In3_1, LOW);
  digitalWrite(In4_1, HIGH);
}

void turnOff(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);

  digitalWrite(In1_1, LOW);
  digitalWrite(In2_1, LOW);  
  digitalWrite(In3_1, LOW);
  digitalWrite(In4_1, LOW);
}

void translateIR() {
  switch(results.value) {
    case 0xFF18E7: Serial.println("2"); move(results.value); lastSignal = 0xFF18E7;  break;
    case 0xFF10EF: Serial.println("4"); move(results.value); lastSignal = 0xFF10EF;  break;
    case 0xFF5AA5: Serial.println("6"); move(results.value); lastSignal = 0xFF5AA5;  break;
    case 0xFF4AB5: Serial.println("8"); move(results.value); lastSignal = 0xFF4AB5;  break;
    case 0xFFFFFFFF: Serial.println(" REPEAT"); move(lastSignal); break;  
  
    default: 
      Serial.println(" other button   ");
  }
}

void loop()
{
  if (irrecv.decode(&results)) {
    lastSignalMillis = millis();
    translateIR(); 
    irrecv.resume(); // receive the next value
  } else if (millis() - lastSignalMillis > 200) {
    turnOff();
  }
}
