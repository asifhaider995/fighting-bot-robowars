///////////////////////////////////////////////////
////-----------------------------------------//////
////|         Sketch Created By             |/////
////|         Asif Haider Khan              |/////
////|       Sketch for AUX_KNIGHT           |/////
////|     Arduino AtMEGA 2560, BTS 7960     |/////
////|  Radio Frequency (RF) Receiver Module |/////
////|         BATTLE BOT (Robowars)         |/////
//////////////////////////////////////////////////

// Source Code starts...
#define ren_rm 10  //Enable pins for Right Motor
#define len_rm 11
#define rpwm_rm 12  //PWM pins for Right Motor
#define lpwm_rm 13  
#define ren_lm 4   //Enable pins for Left Motor
#define len_lm 5
#define rpwm_lm 6  //PWM pins for Right Motor
#define lpwm_lm 7
#define ren_wm $
#define len_wm $
#define rpwm_wm $
#define lpwm_wm $
#define ch1pin 51   //RF channel 1 pin
#define ch2pin 48   //RF channel 2 pin
#define ch3pin 50   //RF channel 3 pin
#define vcc 52

int acc = 2; //Acceleration
int topSpeed = 255; // Top Speed
int ch1 = 0;
int ch2 = 0;
int ch3 = 0;

//Function to Accelerate Right Motor forward
void accRM(){
    digitalWrite(ren_rm,HIGH);
    digitalWrite(len_rm,HIGH);
    for(int i=0;i<=topSpeed;i+=acc){
      analogWrite(rpwm_rm,i);
    }
}

//Function to accelerate left motor forward
void accLM(){
    digitalWrite(ren_lm,HIGH);
    digitalWrite(len_lm,HIGH);
    for(int i=0;i<=topSpeed;i+=acc){
      analogWrite(rpwm_lm,i);
    }
}
//Function to accelerate Weapon Motor forward
void accWM(){
    digitalWrite(ren_wm,HIGH);
    digitalWrite(len_wm,HIGH);
    for(int i=0; i <= 155;i+=acc){
        analogWrite(rpwm_wm,i);
    }
}
//Function to deccelerate Weapon Motor forward
void deccWM(){
    digitalWrite(ren_wm,LOW);
    digitalWrite(len_wm,LOW);
    for(int i=155;i>=0;i-=acc){
        analogWrite(rpwm_wm,i);
    }
}

//Function to Decelerate Right Motor 
void deccRM(){
  digitalWrite(ren_rm,LOW);
  digitalWrite(len_rm,LOW);
  for(int i=topSpeed;i>=0;i-=acc){
    analogWrite(rpwm_rm,i);
  }
}


//Function to Decelerate Left Motor 
void deccLM(){
  digitalWrite(ren_lm,LOW);
  digitalWrite(len_lm,LOW);
  for(int i=topSpeed;i>=0;i-=acc){
    analogWrite(rpwm_lm,i);
  }
}

//Func to Accelerate Right Motor Backward
void _accRM(){
    digitalWrite(ren_rm,HIGH);
    digitalWrite(len_rm,HIGH);
    for(int i=0;i<=topSpeed;i+=acc){
      analogWrite(lpwm_rm,i);
    }
}

//Function to Accelerate left Motor Backward
void _accLM(){
    digitalWrite(ren_lm,HIGH);
    digitalWrite(len_lm,HIGH);
    for(int i=0;i<=topSpeed;i+=acc){
      analogWrite(lpwm_lm,i);
    }
}
//Function to Accelerate Weapon Motor backward
void _accWM(){
    digitalWrite(ren_wm,HIGH);
    digitalWrite(len_wm,HIGH);
    for(int i=0;i<=155;i+=acc){
        analogWrite(lpwm_wm,i);
    }    
}

//function to Deccelerate Weapon Motor Backward
void _deccWM(){
    digitalWrite(ren_wm,LOW);
    digitalWrite(len_wm,LOW);
    for(int i=155;i>=0;i-=acc){
        analogWrite(lpwm_wm,i);
    }
}

//Func to Decelerate Right Motor 
//moving in backward dir
void _deccRM(){
  digitalWrite(ren_rm,LOW);
  digitalWrite(ren_rm,LOW);
  for(int i=topSpeed;i>=0;i-=acc){
    analogWrite(lpwm_rm,i);
  }
}


//Func to Decelerate left Motor 
// moving in backward dir
void _deccLM(){
  digitalWrite(ren_lm,LOW);
  digitalWrite(ren_lm,LOW);
  for(int i=topSpeed;i>=0;i-=acc){
    analogWrite(lpwm_lm,i);
  }
}

//Going Forward Right Motor
void goFwdRM(){ 
  accRM();
}

//Going Forward Left Motor 
void goFwdLM(){ 
   accLM();
}

//Going Backward Right Motor
void goBckRM(){
  _accRM();
}

//Going Backward Left Motor
void goBckLM(){
  _accLM();
}

//Going up Weapon Motor
void goUpWM(){
    accWM();
}

//Going down Weapon Motor
void goDownWM(){
    _accWM();
}

//Stop motor weapon
void StopWM(int x){
    deccWM();
    _deccWM();
    delay(x);
}

//Stop all motors
void Stop(int x){
  digitalWrite(ren_rm,LOW);
  digitalWrite(len_rm,LOW);
  deccRM();
  _deccRM();
  deccLM();
  _deccLM();
  delay(x);
}

//Take RF signal values
void getReadings(){
  ch1 = pulseIn(ch1pin,HIGH,250000);
  ch2 = pulseIn(ch2pin,HIGH,250000);
  ch3 = pulseIn(ch3pin,HIGH,250000);
}

//Print RF values
void printReadings(){
  Serial.print(ch1);
  Serial.print("\t\t");
  Serial.print(ch2);
  Serial.print("\t\t");
  Serial.print(ch3);
  Serial.println();
}


//Decode RF signal values
int Decode(int a,int b,int c){
  if(a > 1700 && a < 1850){  //Up
    return 1;
    if(b > 1700 && b < 1900){  //Right
        return 13;
    }
    else if(b > 1100 && b < 1250){  //Left
        return 14;
    }
    if(c > 1700 && c < 1850){
      return 15;
    }
    else if(c > 1100 && c < 1250){
      return 16;
    }
  }
  else if(a > 1120 && a < 1250){  //Down
    return 2;
    if(b > 1700 && b < 1900){  //Right
        return 23;
    }
    else if(b > 1100 && b < 1250){  //Left
        return 24;
    }
  }
  else if(b > 1700 && b < 1900){  //Right
    return 3;
  }
  else if(b > 1100 && b < 1250){  //Left
    return 4;
  }
  else if(c > 1700 && c < 1850){
      return 5;
  }
  else if(c > 1100 && c < 1250){
      return 6;
  }
  else if((b < 1000 && b > 0) || (a < 1000 && a > 0)){
    return -1;
  }
  else {
    return 0;
  }
  
}

//Configue Pins
void pinConfig(){
  pinMode(ch1pin,INPUT);
  pinMode(ch2pin,INPUT);
  pinMode(ch3pin,INPUT);
  pinMode(ren_rm,OUTPUT);
  pinMode(len_rm,OUTPUT);
  pinMode(rpwm_rm,OUTPUT);
  pinMode(lpwm_rm,OUTPUT);
  pinMode(ren_lm,OUTPUT);
  pinMode(len_lm,OUTPUT);
  pinMode(rpwm_lm,OUTPUT);
  pinMode(lpwm_lm,OUTPUT);
  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinConfig();
  getReadings();
  printReadings();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(vcc,HIGH);
  getReadings();
  //printReadings();
  int val = Decode(ch2,ch1,ch3);
  switch(val){
    case 0: Serial.println("Stop!");Stop(10);break;
    case 1: Serial.println("Go Forward!");
            goFwdRM();
            goFwdLM();
            break;
    case 2: Serial.println("Go Back!");
            goBckRM();
            goBckLM();
            break;
    case 3: Serial.println("Go Right!");
            goBckRM();
            goFwdLM();
            break;
    case 4: Serial.println("Go Left!");
            goFwdRM();
            goBckLM();
            break;
    default: Serial.println("Stop!");Stop(10);break; 
  }

}

//End Source Code




///////////////////// Thank You ////////////////////
