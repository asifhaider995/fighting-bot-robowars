///////////////////////////////////////////////////
////-----------------------------------------//////
////|         Sketch Created By             |/////
////|         Asif Haider Khan              |/////
////|       Sketch for AUX_KNIGHT           |/////
////|     Arduino UNO r3, BTS 7960          |/////
////|  Radio Frequency (RF) Receiver Module |/////
////|         BATTLE BOT (Robowars)         |/////
//////////////////////////////////////////////////

//Defined pins are for BTS 7960 module
//a --> Right Motor
//b --> Left Motor
#define R_ENa 2
#define L_ENa 4
#define R_PWMa 3
#define L_PWMa 5
#define R_ENb 8 
#define L_ENb 7
#define R_PWMb 6
#define L_PWMb 9
#define liftA 10
#define liftB 14  //Pin A0

#define MAX_CH 3  //Max number of Channels
//#define vccPin 13 //RF Receiver module VCC pin
int CH1pin = 11;  // RF Channel 1
int CH2pin = 12;  // RF channel 2
int CH3pin = 13;  // RF Channel 3
int RFData[3];    // array to store RF data
int accelerationA = 1; //Right motor Acceleration
int accelerationB = 1; //Left motor Acceleration

//Function to Accelerate Right Motor forward
void accelerateA(){
    digitalWrite(R_ENa,HIGH);
    digitalWrite(L_ENa,HIGH);
    for(int i=0;i<=255;i+=accelerationA){
      analogWrite(R_PWMa,i);
    }
}
//Function to Accelerate Left Motor forward
void accelerateB(){
    digitalWrite(R_ENb,HIGH);
    digitalWrite(L_ENb,HIGH);
    for(int i=0;i<=255;i+=accelerationB){
      analogWrite(R_PWMb,i);
    }
}

//Function to Decelerate RMotor moving in back dir
void deccelerateA(){
  digitalWrite(R_ENa,LOW);
  digitalWrite(L_ENa,LOW);
  for(int i=255;i>=0;i-=accelerationA){
    analogWrite(R_PWMa,i);
  }
}


//Function to Decelerate LeftMotor moving in back dir
void deccelerateB(){
  digitalWrite(R_ENb,LOW);
  digitalWrite(L_ENb,LOW);
  for(int i=255;i>=0;i-=accelerationB){
    analogWrite(R_PWMb,i);
  }
}

//Func to Accelerate Right Motor Backward
void RevAccelerateA(){
    digitalWrite(R_ENa,HIGH);
    digitalWrite(L_ENa,HIGH);
    for(int i=0;i<=255;i+=accelerationA){
      analogWrite(L_PWMa,i);
    }
}

//Func to Accelerate Left Motor Backward
void RevAccelerateB(){
    digitalWrite(R_ENb,HIGH);
    digitalWrite(L_ENb,HIGH);
    for(int i=0;i<=255;i+=accelerationB){
      analogWrite(L_PWMb,i);
    }
}

//Func to Deceleration RM moving in backward dir
void RevDeccelerateA(){
  digitalWrite(R_ENa,LOW);
  digitalWrite(L_ENa,LOW);
  for(int i=255;i>=0;i-=accelerationA){
    analogWrite(L_PWMa,i);
  }
}


//Func to Deceleration RM moving in backward dir
void RevDeccelerateB(){
  digitalWrite(R_ENb,LOW);
  digitalWrite(L_ENb,LOW);
  for(int i=255;i>=0;i-=accelerationB){
    analogWrite(L_PWMb,i);
  }
}

//Function for going forward 
void goForward(int x){  // x --> delay variable
   accelerateA();
   accelerateB();
   delay(x); 
   deccelerateA();
   deccelerateB(); 

}

//Func for going back 
void goBack(int x){ // x --> delay variable
  RevAccelerateA();
  RevAccelerateB();
  delay(x);
  RevDeccelerateA();   //Right Motor
  RevDeccelerateB();  //Left motor
  //delay(1000);
  

}

//Function for going right
void goRight(int x) { //x ---> delay variable
   RevAccelerateA();   //Right Motor
   accelerateB();     //Left Motor
   delay(x); 
   RevDeccelerateA();
   deccelerateB();
}

//Function for going left
void goLeft(int x)  {
  RevAccelerateB();  //Left Motor
  accelerateA();  //Right Motor
  delay(x);
  RevDeccelerateB();
  deccelerateA();
}
//function for stopping motor rotation
void Stop(int x){
  digitalWrite(R_ENa,LOW);
  digitalWrite(L_ENa,LOW);
  digitalWrite(R_ENb,LOW);
  digitalWrite(L_ENb,LOW);
  deccelerateA();
  deccelerateB();
  RevDeccelerateA();
  RevDeccelerateB();
  delay(x*2);
}

//function for Lifter
//Function for Lifter UP
void liftUp(){
  digitalWrite(liftA,LOW);
  digitalWrite(liftB,HIGH);
}
void liftDown(){
  digitalWrite(liftA,HIGH);
  digitalWrite(liftB,LOW);
}
void liftStop(){
  digitalWrite(liftA,HIGH);
  digitalWrite(liftB,HIGH);
}
//Function for Arduino pin configuration
void pinConfig(){
  for(int i=0;i < MAX_CH;i++){
    pinMode(i+11,INPUT);
  }
  //pinMode(vccPin,OUTPUT);
  pinMode(R_ENa,OUTPUT);
  pinMode(L_ENa,OUTPUT);
  pinMode(R_PWMa,OUTPUT);
  pinMode(L_PWMa,OUTPUT);
  pinMode(liftA,OUTPUT);
  pinMode(liftB,OUTPUT);
}

//Function for taking readings from 
//Radio Freq receiver module
void takeReadings(int *data){
  for(int i=0;i < MAX_CH;i++){
    data[i] = pulseIn(CH1pin+i,HIGH,250000);
  } //Radio data stored in data ref array
}

//Function for printing the data readings
void PrintReadings(int *data){
  for(int i=0;i < MAX_CH;i++){
    Serial.print(data[i]);
    Serial.print("\t");
  }
  Serial.println();
}

//Boolean functions
//Boolean condition for 'Up' command
//returns true if Right Stick 'Up' is pressed
boolean rsUp(int *data){
  return (data[1] > 1750 && data[1] < 2000);
}
//Boolean condition for 'Down' Command
//returns true if Right Stick 'Down' is pressed
boolean rsDown(int *data){
  return (data[1] > 1100 && data[1] < 1200);
}
//Boolean condition for 'Right' Command
//returns true if Right Stick 'Left' is pressed
boolean rsRight(int *data){
  return (data[0] > 1750 && data[0] < 2000);
}
//Boolean condition for 'Left' Command
//returns true if Right Stick 'Left' is pressed
boolean rsLeft(int *data){
  return (data[0] > 1100 && data[0] < 1200);
}

//Boolean condition for left stick 'Up' command
//returns true if Right Stick 'Up' is pressed
boolean lsUp(int *data){
  return (data[2] > 1750 && data[2] < 2000);
}
//Boolean condition for left stick 'Down' Command
//returns true if left Stick 'Down' is pressed
boolean lsDown(int *data){
  return (data[2] > 1100 && data[2] < 1200);
}

//Setup function
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//digitalWrite(vccPin,HIGH);
pinConfig();
takeReadings(RFData);
PrintReadings(RFData);
}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.begin(9600);
//digitalWrite(vccPin,HIGH);
pinConfig();
takeReadings(RFData);
if(rsUp(RFData)){
  Serial.println("-----Going---Forward----------");
  goForward(100);
  
}
else if(rsDown(RFData)){
  Serial.println("----Going---Back-----------");
  goBack(100);
}
else if(rsRight(RFData)){
  goRight(100);
  Serial.println("----Going---Right-----------");
}
else if(rsLeft(RFData)){
  goLeft(100);
  Serial.println("----Going---Left----------");
}
else if(lsUp(RFData)){
  liftUp();
  Serial.println("-----Lifter-Up---------");
}
else if(lsDown(RFData)){
  liftDown();
  Serial.println("----Lifter--Down----------");
}
else{
  liftStop();
  Stop(50);
  PrintReadings(RFData);
}

}
