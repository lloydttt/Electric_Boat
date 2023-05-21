
#include <PS2X_lib.h>  //for v1.6

/****************************************************************** * set pins connected to PS2 controller: * - 1e column: original * - 2e colmun: Stef? * replace pin numbers by the ones you use ******************************************************************/
#define PS2_DAT        13  //14 
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17


#define ENABLE_L 3
#define MOPIN_L1 4
#define MOPIN_L2 5

#define ENABLE_R 9
#define MOPIN_R1 7
#define MOPIN_R2 8

/****************************************************************** * select modes of PS2 controller: * - pressures = analog reading of push-butttons * - rumble = motor rumbling * uncomment 1 of the lines for each mode selection ******************************************************************/
//#define pressures true
#define pressures   false
//#define rumble true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

// Reset func 
void (* resetFunc) (void) = 0;


  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(600);
  pinMode(ENABLE_L,OUTPUT);
  pinMode(ENABLE_R,OUTPUT);
  pinMode(MOPIN_L1,OUTPUT);
  pinMode(MOPIN_L2,OUTPUT); 
  pinMode(MOPIN_R1,OUTPUT);
  pinMode(MOPIN_R2,OUTPUT); 
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
    case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
   }

}

void loop() {
  // put your main code here, to run repeatedly:
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    if(ps2x.Button(PSB_PAD_UP)){
      //straight_go();
      Serial.println("Go!");
        digitalWrite(ENABLE_L,HIGH);
        digitalWrite(ENABLE_R,HIGH);
        digitalWrite(MOPIN_L1,HIGH);
        digitalWrite(MOPIN_L2,LOW);
        digitalWrite(MOPIN_R1,HIGH);
        digitalWrite(MOPIN_R2,LOW);
        delay(100);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      //down_go();
      Serial.println("Back!");
      digitalWrite(ENABLE_L,HIGH);
      digitalWrite(ENABLE_R,HIGH);
      digitalWrite(MOPIN_L1,LOW);
      digitalWrite(MOPIN_L2,HIGH);
      digitalWrite(MOPIN_R1,LOW);
      digitalWrite(MOPIN_R2,HIGH);
              delay(100);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      //left_turn();
      Serial.println("Left!");
      digitalWrite(ENABLE_L,HIGH);
      digitalWrite(ENABLE_R,HIGH);
      digitalWrite(MOPIN_L1,LOW);
      digitalWrite(MOPIN_L2,HIGH);
      digitalWrite(MOPIN_R1,HIGH);
      digitalWrite(MOPIN_R2,LOW);  
              delay(100);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      //right_turn();
      Serial.println("Right!");
      digitalWrite(ENABLE_L,HIGH);
      digitalWrite(ENABLE_R,HIGH);
      digitalWrite(MOPIN_R1,LOW);
      digitalWrite(MOPIN_R2,HIGH);
      digitalWrite(MOPIN_L1,HIGH);
      digitalWrite(MOPIN_L2,LOW); 
              delay(100);
    }
    if(ps2x.ButtonPressed(PSB_CIRCLE)){               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
      digitalWrite(ENABLE_L,LOW);
      digitalWrite(ENABLE_R,LOW);
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
