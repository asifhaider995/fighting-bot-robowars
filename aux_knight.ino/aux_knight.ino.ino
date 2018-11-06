///////////////////////////////////////////////////
////-----------------------------------------//////
////|         Sketch Created By             |/////
////|         Asif Haider Khan              |/////
////|       Sketch for AUX_KNIGHT           |/////
////|     Arduino UNO r3, BTS 7960          |/////
////|  Radio Frequency (RF) Receiver Module |/////
////|         BATTLE BOT (Robowars)         |/////
//////////////////////////////////////////////////

//Defined pins are for RF receiver module
#define rfVCC 13
//Defined pins for BTS 7960
#define lm_F 2    //Left Motor Forward
#define lm_B 3    //Left Motor Backward
#define lm_PWM 4  //Left Motor PWM
#define rm_F 5    //Right Motor Forward
#define rm_B 6    //Right Motor Backward
#define rm_PWM 7  //Right Motor PWM
#define MAX_CH 3
int CH1pin = 10;   //Channel1 Pin in Arduino
int CH2pin = 11;   //Channel2 Pin in Arduino
int CH3pin = 12;   //Channel3 Pin in Arduino

int RFdata[MAX_CH]; //Variable to store Radio Channel data

//function definitions

//Going forward
void goForward(){
  digitalWrite(lm_F,HIGH); 
  digitalWrite(lm_B,LOW);
  digitalWrite(rm_F,HIGH);
  digitalWrite(rm_B,LOW);
}
//Going Backward
void goBack(){
  digitalWrite(lm_B,HIGH);
  digitalWrite(lm_F,LOW);
  digitalWrite(rm_B,HIGH);
  digitalWrite(rm_F,LOW);
}
//Turning or Spinning Right
void goRight(){
  digitalWrite(lm_F,HIGH);
  digitalWrite(lm_B,LOW);
  digitalWrite(rm_F,LOW);
  digitalWrite(rm_B,HIGH);
}
//Turning or Spinning Left
void goLeft(){
  digitalWrite(lm_F,LOW);
  digitalWrite(lm_B,HIGH);
  digitalWrite(rm_F,HIGH);
  digitalWrite(rm_B,LOW);
}

//Configure the pin states
void pinConfig(){
  //RF Channel pins
  pinMode(CH1pin,INPUT); //Channel 1 pin
  pinMode(CH2pin,INPUT); //Channel 2 pin 
  pinMode(CH3pin,INPUT); //Channel 3 pin
  //RF VCC 5V pin, OUTPUT
  pinMode(rfVCC,OUTPUT); 
  //BTS pins all set for output
  pinMode(lm_F,OUTPUT); 
  pinMode(rm_F,OUTPUT);
  pinMode(lm_B,OUTPUT);
  pinMode(rm_B,OUTPUT);
  pinMode(lm_PWM,OUTPUT);
  pinMode(rm_PWM,OUTPUT);
  
}


//Calibrate RF Controller data
void CalibrateController(){
  
}

//Func to take RF inputs from Receiver
void takeInputs(){
  for(int i=0;i < MAX_CH;i++){
    RFdata[i] = pulseIn(CH1pin+i,HIGH,250000);
  }
}

//Conditional Boolean functions
//Condition A describes all readings are 0
boolean condA(){
  return ( (RFdata[0] == 0) && (RFdata[1] == 0) && 
  (RFdata[2] == 0));
}
//Condition B describes valid readings are given
boolean condB(){
  return ( (RFdata[0] > 0) && (RFdata[1] > 0) && 
  (RFdata[2] > 0));
}

//Following Boolean functions for Controller Cmd
//Boolean condition for 'Up' Command
boolean Up(int *data){
  return (true);
}
//Boolean condition for 'Down' Command
boolean Down(int *data){
  return (true);
}
//Boolean condition for 'Left' Command
boolean Left(int *data){
  return (true);
}
//Boolean condition for 'Right' Command
boolean Right(int *data){
  return (true);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
