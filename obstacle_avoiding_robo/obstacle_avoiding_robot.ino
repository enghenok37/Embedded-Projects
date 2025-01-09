#include <Servo.h>
int start =26;

int  trigPinmiidle= 8;
int echoPinmiddle= 9;
int  trigPinright= 10;
int echoPinright= 11;
int  trigPinleft= 12;
int echoPinileft= 13;


//L29D motor control pins
 int LeftMotorForward = 4;
 int LeftMotorBackward = 5;
 int RightMotorForward = 6;
 int RightMotorBackward = 7;

int motor = 18;
int servo =19;
int led = 20;
Servo pedalServo;
int count;
int startprocess;
long duration, distance;
int motorstep = 500;
void setup() {
   

 
  pinMode(trigPinmiidle, OUTPUT);
  pinMode(echoPinmiddle, INPUT);
   pinMode(trigPinright, OUTPUT);
  pinMode(echoPinright, INPUT);
   pinMode(trigPinleft, OUTPUT);
  pinMode(echoPinileft, INPUT);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

Serial.begin(9600);

}

void loop() {
  
 int  leftstate =  getDistance(3);
 Serial.print(" sensor left:");
 Serial.println(leftstate);
  delay(200);
  
 int middleState = getDistance(4);
 Serial.print(" sensor miidle :");
 Serial.println(middleState);
  delay(200);

 int rightstate = getDistance(5);
 Serial.print(" sensor right:");
 Serial.println(rightstate);
   delay(200);
   if(middleState <40){
     Serial.println("middle block found ");
               leftstate =  getDistance(3);
               rightstate = getDistance(5);
               
              if(leftstate < rightstate){
                   Serial.println(" turrnig right");
                robot_turnRight();
              }
              else if(leftstate > rightstate ){
                   
                           Serial.println(" turrnig left");
                            robot_turnLeft();
                      
                      
                
                }
             else if(leftstate == rightstate){
                 Serial.println(" equal right");
                  robot_turnRight();
                  } 
              
              } 
      else{
                
                
                
                         Serial.println(" no block in the middle");
                          robot_goForward(); 
                  
                           Serial.println(" check sensor");
                        
                
              
      }

}
void  robot_goForward(){
Serial.println("robot moving forward");
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(motorstep);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void robot_turnLeft(){

  digitalWrite(RightMotorForward, LOW);
 
  digitalWrite(RightMotorBackward, LOW); 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  
  delay(motorstep);
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW); 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
 
  
}
void  robot_turnRight(){

  digitalWrite(LeftMotorForward , LOW);
 
  digitalWrite(RightMotorBackward, LOW); 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  
  delay(motorstep);
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW); 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
 
}


  



  
int getDistance(int sensor)                                   
{
  long duration, cm;                      
  int distance; 
  if (sensor == 3){
    sensor = 0;
    digitalWrite(trigPinmiidle, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinmiidle, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinmiidle, LOW);


    duration = pulseIn(echoPinmiddle, HIGH);
    cm = duration / 29 / 2;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
        } 
     else if (sensor == 4){ ////////////right 
          sensor = 0;
    digitalWrite(trigPinright, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinright, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinright, LOW);


    duration = pulseIn(echoPinright, HIGH);
    cm = duration / 29 / 2;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    }
     if (sensor == 5){{
        sensor = 0;
    digitalWrite(trigPinleft, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinleft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinleft, LOW);


    duration = pulseIn(echoPinileft, HIGH);
    cm = duration / 29 / 2;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  
    
    }
  }
              distance = cm;
 return distance;
}
