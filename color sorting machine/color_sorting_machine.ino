#include <Servo.h>



int conveyorReverse = 2;
int openerServopin = 13;
int yellowServopin = 12;
int blueServopin = 11;
int greenServopin = 10;
int redServopin = 9;

int conveyor = 8;

int redObject =7;
int GreenObject =6;
int blueObject =5;
int yellowObject =4;
int otherObject =3;

int redvalue ;
int Greenvalue;
int bluevalue;
int yellowValue;
int other;

int redd ;
int greenn;
int bluee;
int yelloww;
int otherr;
Servo openerServo;

Servo yellowServo;
Servo blueServo;
Servo greenServo;
Servo redServo;

int objectNotdetected =1;
int count =0;
void setup() {
openerServo.attach(openerServopin);

yellowServo.attach(yellowServopin);
blueServo.attach(blueServopin);
greenServo.attach(greenServopin);
redServo.attach(redServopin);

 pinMode(conveyor , OUTPUT);
  pinMode(conveyorReverse , OUTPUT);

 pinMode(redObject , INPUT);
 pinMode(GreenObject , INPUT);
 pinMode(blueObject , INPUT);
 pinMode(yellowObject , INPUT);
 pinMode(otherObject , INPUT);
for(int i = 0; i<85 ;i++){
    openerServo.write(i);
    delay(15);
    }
yellowServo.write(90);
blueServo.write(90);
greenServo.write(90);
redServo.write(90);
Serial.begin(9600);
 Serial.println(" MACHINE STARTING ... ");
 digitalWrite(conveyor,HIGH);
  digitalWrite(conveyorReverse,LOW);
  delay(6000);
}

void loop() {
  
  for(int i = 0; i<85 ;i++){
    openerServo.write(i);
    delay(10);
    }
     for(int i = 85; i>0 ;i--){
    openerServo.write(i);
    delay(10);
    }
  while(objectNotdetected){
     redvalue = digitalRead(redObject);
     Greenvalue = digitalRead(GreenObject);
     bluevalue = digitalRead(blueObject);
     yellowValue = digitalRead(yellowObject);
    other = digitalRead(otherObject);
    Serial.println("next object ");
    if(redvalue ||Greenvalue ||bluevalue || yellowValue|| other){
      objectNotdetected =0;
       Serial.println(" object detected ");
      }
     
    }
     objectNotdetected =1;
   
    if(redvalue ==1){
        redd = 1;
           Serial.println(" object detected :: red");
      }
      if(Greenvalue ==1){
        greenn = 2;
          Serial.println(" object detected :: green");
      }
       if(bluevalue ==1){
        bluee = 3;
          Serial.println(" object detected :: blue");
      }
       if(yellowValue ==1){
        yelloww = 4;
          Serial.println(" object detected :: white");
      }
       if(other ==1){
        otherr = 5;
          Serial.println(" object detected :: other");
      }
         count = count +1;
        redd  = redd -1;
        greenn = greenn -1;
        bluee = bluee-1;
        yelloww = yelloww -1;
        otherr = otherr -1;        

          delay(4000);
    if(redd ==0){
            for(int i = 90; i<180 ;i++){
                  redServo.write(i);
                    delay(10);
                 }
             for(int i = 180; i>90 ;i--){
                  redServo.write(i);
                    delay(10);
                 }
         Serial.println("red out ");



      }
      if(greenn ==0){
        for(int i = 90; i<180 ;i++){
                  greenServo.write(i);
                    delay(10);
                 }
          for(int i = 180; i>90 ;i--){
                  openerServo.write(i);
                    delay(10);
                 }
       Serial.println("green out ");
        
      }
       if(bluee ==0){

        for(int i = 90; i<180 ;i++){
                  blueServo.write(i);
                    delay(10);
                 }

          for(int i = 180; i>90 ;i--){
                  blueServo.write(i);
                    delay(10);
                 }
       Serial.println("blue out ");
      }
       if(yelloww ==0){

        for(int i = 90; i<180 ;i++){
                  yellowServo.write(i);
                    delay(10);
                 }
        for(int i = 180; i>90 ;i--){
                  yellowServo.write(i);
                    delay(10);
                 }
                   Serial.println("white out ");
      }
       if(otherr ==0){
       Serial.println("other out ");
      }
 


}
