
#define ENABLE_L 3
#define MOPIN_L1 4
#define MOPIN_L2 5

#define ENABLE_R 9
#define MOPIN_R1 7
#define MOPIN_R2 8

#include <SoftwareSerial.h>
SoftwareSerial BT(10,11);
char val;
static char state_move;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("BlueT is ready.");
  BT.begin(9600);
  pinMode(ENABLE_L,OUTPUT);
  pinMode(ENABLE_R,OUTPUT);
  pinMode(MOPIN_L1,OUTPUT);
  pinMode(MOPIN_L2,OUTPUT); 
  pinMode(MOPIN_R1,OUTPUT);
  pinMode(MOPIN_R2,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    val = Serial.read();
    BT.print(val);
  }
  if(BT.available()){
    val = char(BT.read());
    Serial.println(val);

    state_move = val;
    if(state_move == 'u'){
      straight_go();
    }else if(state_move == 'd'){
      down_go();
    }else if(state_move == 'l'){
      left_turn();
    }else if(state_move == 'r'){
      right_turn();
    }else if(state_move == 'o'){
      stop_off();
    }
    
  }
}

void straight_go(){
  digitalWrite(ENABLE_L,HIGH);
  digitalWrite(ENABLE_R,HIGH);
  digitalWrite(MOPIN_L1,HIGH);
  digitalWrite(MOPIN_L2,LOW);
  digitalWrite(MOPIN_R1,HIGH);
  digitalWrite(MOPIN_R2,LOW);
}

void down_go(){
  digitalWrite(ENABLE_L,HIGH);
  digitalWrite(ENABLE_R,HIGH);
  digitalWrite(MOPIN_L1,LOW);
  digitalWrite(MOPIN_L2,HIGH);
  digitalWrite(MOPIN_R1,LOW);
  digitalWrite(MOPIN_R2,HIGH);
  
}

void left_turn(){
  digitalWrite(ENABLE_L,HIGH);
  digitalWrite(ENABLE_R,HIGH);
  digitalWrite(MOPIN_L1,LOW);
  digitalWrite(MOPIN_L2,HIGH);
  digitalWrite(MOPIN_R1,HIGH);
  digitalWrite(MOPIN_R2,LOW);  
  
}

void right_turn(){
  digitalWrite(ENABLE_L,HIGH);
  digitalWrite(ENABLE_R,HIGH);
  digitalWrite(MOPIN_R1,LOW);
  digitalWrite(MOPIN_R2,HIGH);
  digitalWrite(MOPIN_L1,HIGH);
  digitalWrite(MOPIN_L2,LOW); 
}

void stop_off(){
  digitalWrite(ENABLE_L,LOW);
  digitalWrite(ENABLE_R,LOW);
}
