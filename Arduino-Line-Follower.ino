/**********RoccoMathijn***********\
**********************************
***************2015***************
**********************************
**********LINE FOLLOWER***********
**********************************
\********************************/

//Motor inputs
int inp1 = 2;
int inp2 = 3;
int inp3 = 4;
int inp4 = 5;
int inp5 = 6;
int inp6 = 7;
int inp7 = 8;
int inp8 = 9;

//Engine PWM  control
int enLA  = 10;
int enRA  = 11;
int enLV  = 12;
int enRV  = 13;

//Line sensor inputs
int lineSensR = 48;
int lineSensM = 50;
int lineSensL = 52;

//PWM for motors on left side and on right side
int speedL;
int speedR;

//Direction of each motor A/B for left side. C/D for motors on right side
int directionA;
int directionB;
int directionC;
int directionD;

int lastState;

int initialize = 1;
void setup() {

Serial.begin(9600);
pinMode(lineSensR, INPUT);
pinMode(lineSensM, INPUT);
pinMode(lineSensL, INPUT);

}

void loop() {

  //Read tracking sensors
int lineSensvalR = digitalRead(lineSensR);
int lineSensvalM = digitalRead(lineSensM);
int lineSensvalL = digitalRead(lineSensL);

//Initialisation:
  while(initialize){
    countdown();
   }

//Set speed (0-255)
speedL = 200;
speedR = 200;

//Line tracking:



  if (lineSensvalL == 1 && lineSensvalM == 0 && lineSensvalR == 1){
  forward();
}
  else if (lineSensvalL == 0 && lineSensvalM == 0 && lineSensvalR == 0){
    forward();
      }
  else if (lineSensvalL == 0 && lineSensvalM == 0 && lineSensvalR == 1){
    softLeft();
    lastState = 1;
      }
  else if (lineSensvalL == 1 && lineSensvalM == 0 && lineSensvalR == 0){
    softRight();
    lastState = 2;
      }
  else if (lineSensvalL == 1 && lineSensvalM == 1 && lineSensvalR == 0){
    mediumRight();
  }
  else if (lineSensvalL == 0 && lineSensvalM == 1 && lineSensvalR == 1){
    mediumLeft();
  }
  else if (lineSensvalL == 1 && lineSensvalM == 1 && lineSensvalR == 1){
        if (lastState == 1){
          while(digitalRead(lineSensM) == 1){
          hardLeft();
          }
        }
        else if (lastState == 2){
          while(digitalRead(lineSensM) == 1){
          hardRight();
          }
          
        }
    }
  else stopCar();

//Debugging:
//Serial.println(lineSensvalR);
//Serial.println(lineSensvalM);
//Serial.println(lineSensvalL);
//Serial.println(lastState);

}

void forward(){
  wheelsLeft(speedL, 1, 0);
  wheelsRight(speedR, 1, 0);
}

void softLeft(){
  speedR = 255;
  wheelsLeft(speedL, 0, 0);
  wheelsRight(speedR, 1, 0);
}

void softRight(){
  speedL = 255;
  wheelsLeft(speedL, 1, 0);
  wheelsRight(speedR, 0, 0);
}

void mediumLeft(){
    wheelsLeft(speedL, 0, 1);
    wheelsRight(speedR, 1, 0);
}
void mediumRight(){
    wheelsLeft(speedL, 1, 0);
    wheelsRight(speedR, 0, 1);
}

void hardLeft(){
    speedL = 255;
    speedR = 125;
    wheelsLeft(speedL, 0, 1);
    wheelsRight(speedR, 1, 0);
}
void hardRight(){
    speedL = 125;
    speedR = 255;
    wheelsLeft(speedL, 1, 0);
    wheelsRight(speedR, 0, 1);
}

void stopCar(){
    wheelsLeft(speedL, 0, 0);
    wheelsRight(speedR, 0, 0);
}

void countdown(){
  if (digitalRead(lineSensL) == 1 && digitalRead(lineSensM) == 0 && digitalRead(lineSensR) == 1){
    for(int i = 0; i < 3; i++){
    wheelsLeft(30, 1, 0);
    wheelsRight(30, 1, 0);
    delay(500);
    stopCar();
    delay(500);
    }
    wheelsLeft(30, 1, 0);
    wheelsRight(30, 1, 0);
    delay(1200);
    initialize = 0;  
   }
    else stopCar();

}

void wheelsLeft(int PWM, int dir1, int dir2)
{ 
  analogWrite(enLA, PWM);
  analogWrite(enLV, PWM);
  digitalWrite(inp1, dir1);
  digitalWrite(inp2, dir2);
  digitalWrite(inp7, dir2);
  digitalWrite(inp8, dir1);
}

void wheelsRight(int PWM, int dir1, int dir2)
{ 
  analogWrite(enRA, PWM);
  analogWrite(enRV, PWM);
  digitalWrite(inp3, dir1);
  digitalWrite(inp4, dir2);
  digitalWrite(inp5, dir2);
  digitalWrite(inp6, dir1);
}



