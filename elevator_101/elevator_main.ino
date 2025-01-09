#include <LiquidCrystal.h>
const int pingPin = 18; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 19; // Echo Pin of Ultrasonic Sensor
int groundUP =22;
int firstUP =23;
int firstDown =24;
int secondUp =25;
int secondDown =26;
int thirdDown =27;
#define LCD_ROWS 4
#define LCD_COLS 20

int vgroundUP ;
int vfirstUP;
int vfirstDown ;
int vsecondUp ;
int vsecondDown ;
int vthirdDown ;
//int groundUP ;
char lcd_buf[LCD_ROWS][LCD_COLS];
char lcd_buf_old[LCD_ROWS][LCD_COLS];
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
int elevatorlocation =-1;
int buttonNotclikced =1;
int callReslut =-1;
int elevatorCall =-1;


  int motorDirectionn =-1;
  int  motorStepp = -1;

  
int motorDirection =-1;
int motorStep;
int insidekey = 1;
int motorforward =28;
int motorreverse =29;
int openD= 31;
int closeD = 32;
 int nowlocation =-1;
 int nowdestination = -1;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {39, 40, 41, 42}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {36, 37, 38}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{pinMode(pingPin, OUTPUT);
pinMode(echoPin, INPUT);


 lcd.begin(20, 4);
  lcd.setCursor(0,0);
   
pinMode(groundUP, INPUT);
pinMode(firstUP, INPUT);
pinMode(firstDown, INPUT);
pinMode(secondUp, INPUT);
pinMode(secondDown, INPUT);
pinMode(thirdDown, INPUT);

pinMode(motorforward, OUTPUT);
pinMode(motorreverse, OUTPUT);
pinMode(openD, OUTPUT);
pinMode(closeD, OUTPUT);
Serial.begin(9600); // Starting Serial Terminal
}

void loop()
{
 elevatorlocation = getElevatorLocation();
 delay(200);
 elevatorlocation = getElevatorLocation();  // recheck
 lcd.clear();
 lcd.setCursor(0,0);
  lcd.print("Location");
  lcd.setCursor(10,0);
 lcd.print(elevatorlocation);
Serial.println(elevatorlocation);
    elevatorCall =  getCallLocation();
      runToLocation(elevatorCall);
       deliverPerson();
  
} 
 void  runToDestination( int nowlocation ,  int nowdestination){
    
   // buttonNotclikced =1;
 
    Serial.print("call from");
    Serial.println(nowdestination); // 1
      Serial.print("location ");
    Serial.println(nowlocation); // 22
    
    

                           if(nowdestination ==0 && (nowlocation== 1 ||nowlocation ==11)){
                             Serial.println(" going from 1 to 0");
                             motorDirectionn =0;
                             motorStepp =1;
                                  lcd.setCursor(10,1);
                                  lcd.print(1);
                             runElevatorr(motorDirectionn , motorStepp);  
                             openElevatorDoor();                  
                            }
                          if(nowdestination ==0 && (nowlocation== 2 ||nowlocation ==22)){
                              Serial.println(" going from 2 to 0");
                              motorDirectionn =0;
                               motorStepp =1;
                               lcd.setCursor(8,1);
                                  lcd.print(2);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                  if( digitalRead(firstDown)){     
                                    openElevatorDoor();
                                    }
                                    lcd.setCursor(8,1);
                                    lcd.print(1);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                           
                            }
                          if(nowdestination ==0 && nowlocation== 3 ){
                               Serial.println("going from 3 to 0");
                               motorDirectionn =0;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(3);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                    Serial.println("making sure"); 
                                  if( digitalRead(firstDown) == 1){ 
                                    Serial.println(" yup it is HIgh "); 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(2);
                                   runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                  if(digitalRead(secondDown) == 1){ 
                                      Serial.println(" yup it is HIgh "); 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(1);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                          
                            }

                            if(nowdestination ==0 && nowlocation== 0 ){
                               Serial.println("elevator door open ");
                              openElevatorDoor();
                               deliverPerson();
                            }
                          if(nowdestination ==1 && nowlocation== 0 ){
                             Serial.println(" going from 0 to 1");
                             motorDirectionn =1;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(0);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  openElevatorDoor();
                            }

                            if(nowdestination ==1 && (nowlocation== 1 ||nowlocation ==11)){
                             Serial.println("elevator open : floor 1 ");
                             openElevatorDoor();
                               deliverPerson();
                            }
                            
                          if(nowdestination ==1 && (nowlocation== 2 ||nowlocation ==22)){
                             Serial.println(" going from 2 to 1 ");
                             motorDirectionn =0;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(2);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  openElevatorDoor();
                            }
                          if(nowdestination ==1 && nowlocation== 3){
                             Serial.println(" going from 3 to 1");
                             motorDirectionn =0;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(3);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  if(digitalRead(secondUp) == 1){ //////////////////////////////////////////////////////////
                                    openElevatorDoor();
                                    }

                                  
                                  delay(200);
                                   lcd.setCursor(8,1);
                                    lcd.print(2);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                                  
                            }
                          if(nowdestination ==2 && nowlocation== 0 ){
                             Serial.println(" going from 0 to 2");
                             motorDirectionn =1;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(0);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                  if(digitalRead(firstDown) == 1){ //////////////////////////////////////////////////////////
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(1);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                            }
                          if(nowdestination ==2 && (nowlocation== 1 ||nowlocation ==11)){
                             Serial.println(" going from 1 to 2");
                             motorDirectionn =1;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(1);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  openElevatorDoor();
                            }

                             if(nowdestination ==2 && (nowlocation== 2 ||nowdestination ==22)){
                             Serial.println("elevator door open: floor 2");
                              openElevatorDoor();
                               deliverPerson();
                            }


                            
                           if(nowdestination ==2 && nowlocation== 3){
                             Serial.println(" going from 3 to 2");
                             motorDirectionn =0;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(3);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  openElevatorDoor();
                            }


                            
                           if(nowdestination ==3 && nowlocation== 0 ){
                             Serial.println(" going from 0 to 3");
                             motorDirectionn =1;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(0);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                   if(digitalRead(secondDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(1);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   delay(200);
                                    if(digitalRead(firstDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(2);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                                  delay(200);
                                 
                            }
                           if(nowdestination ==3 && (nowlocation== 1 ||nowlocation ==11)){
                             Serial.println(" going from 1 to 3");
                             motorDirectionn =1;
                               motorStepp =1; 
                                 lcd.setCursor(8,1);
                                    lcd.print(1);
                                    runElevatorr(motorDirectionn , motorStepp);
                                  delay(200);
                                   if(digitalRead(secondDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(8,1);
                                    lcd.print(2);
                                   runElevatorr(motorDirectionn , motorStepp);
                                   openElevatorDoor();
                            }
                            if(nowdestination ==3 && (nowlocation== 2 ||nowlocation ==22)){
                               Serial.println(" going from 2 to 3");
                               motorDirectionn =1;
                               motorStepp =1;
                                lcd.setCursor(8,1);
                                    lcd.print(2);
                                  runElevatorr(motorDirectionn , motorStepp);
                                  openElevatorDoor();
                                  
                              
                              }
                              if(nowdestination ==3 && nowlocation== 3 ){
                             Serial.println("elevator door open : floor 3");
                              openElevatorDoor();
                               deliverPerson();
                            }
                            else{
                               Serial.println("not success");
                              
                              }
                            
                            
                    
  
 // return 0;
  elevatorlocation = nowlocation;
  elevatorCall = nowdestination;
  }
void deliverPerson(){
    Serial.println("delivering frommma");
    
    
                                                          if (elevatorCall == 11){nowlocation =1; }
                                                          if (elevatorCall == 22){nowlocation =2; }
                                                          if (elevatorCall == 33){nowlocation =3; }
                                                          else{nowlocation =elevatorCall; }
     nowdestination = -1;
    Serial.println(nowlocation);
        while(insidekey)
        {
         Serial.println("we made it here");  
            char key = keypad.getKey();

            if (key == '0') {
                                 // elevatorlocation = elevatorCall;
                                  nowdestination = 0;
                                      lcd.clear();
                                     lcd.setCursor(5,2);
                                      lcd.print("destination");
                                     lcd.print(key);
                                  Serial.println(key);  
                                  delay(1000);
                                  insidekey = false;
                                   runToDestination(nowlocation , nowdestination);
              
              }
            if (key == '1') {
                                  //elevatorlocation = elevatorCall;
                                  nowdestination = 1;
                                   lcd.clear();
                                     lcd.setCursor(5,2);
                                      lcd.print("destination");
                                     lcd.print(key);
                                  Serial.println(nowdestination);
                                   delay(1000);
                                 insidekey = false;
                                  runToDestination(nowlocation , nowdestination);
              }
            if (key == '2') {
                                //elevatorlocation = elevatorCall;
                                  nowdestination = 2;
                                   lcd.clear();
                                     lcd.setCursor(5,2);
                                      lcd.print("destination");
                                     lcd.print(key);
                                  Serial.println(key);
                                   delay(1000);
                                  insidekey = false;
                                  runToDestination(nowlocation , nowdestination);
              }
            if (key =='3') {
                                // elevatorlocation = elevatorCall;
                                  nowdestination = 3;
                                   lcd.clear();
                                     lcd.setCursor(5,2);
                                      lcd.print("destination");
                                     lcd.print(key);
                                  Serial.print(key);
                                   delay(1000);
                                  insidekey = false;
                                 runToDestination(nowlocation , nowdestination);
                                    Serial.println("walk on");
                        }
    
              
      }

      insidekey = 1;

}


  


void  openElevatorDoor(){
            digitalWrite(openD, HIGH);
            digitalWrite(closeD, LOW);
             lcd.clear();
                                     lcd.setCursor(0,2);
                                      lcd.print("door opening");
                                     //lcd.println(key);
            delay(2000);
             digitalWrite(openD, LOW);
            digitalWrite(closeD, LOW);
            delay(2000);
             lcd.clear();
                                     lcd.setCursor(0,2);
                                      lcd.print("door closing");
                                    // lcd.println(key);
            digitalWrite(openD, LOW);
            digitalWrite(closeD, HIGH);
                        delay(2000);
                        lcd.clear();
                         digitalWrite(openD, LOW);
                         digitalWrite(closeD, LOW);
                       

                        

  
  
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int runElevatorr(  int motorDirectionn ,int  motorStepp  ){  
  /// run the motor of the elevator car 
  
  motorStepp = motorStepp *4000;
  Serial.print(motorDirectionn);
  Serial.println(motorStepp);
  
  if(motorDirectionn == 1){  // forward
               Serial.print(" motor dxnnnnnnnnnnnnnn" );
               Serial.print(motorDirectionn );

                  // lcd.clear();
                                     lcd.setCursor(0,3);
                                      lcd.print(" going up");
                                     //lcd.println(motorStep/4000);
            digitalWrite(motorforward, HIGH);
            digitalWrite(motorreverse, LOW);
            delay(motorStepp);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
           // openElevatorDoor();
    }
    else if(motorDirectionn ==0){   // reverse
                Serial.print(" motor dxnnnnnnnnnnnnnnnnnnn" );
                Serial.print(motorDirectionn );
                 lcd.setCursor(0,3);
                                      lcd.print(" going down");
                                    // lcd.println(motorStep/4000);
           digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, HIGH);
            delay(motorStepp);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
             // openElevatorDoor();

      }
}
      
int runElevator(int motorDirection ,int  motorStep){  
  /// run the motor of the elevator car 
  //motorDirection = motorDirection;
  motorStep = motorStep *4000;
  Serial.print(motorDirection);
  Serial.println(motorStep);
  
  if(motorDirection == 1){  // forward
               Serial.print(" motor dxn" );
               Serial.print(motorDirection );

                   //lcd.clear();
                                     lcd.setCursor(0,3);
                                      lcd.print(" going up");
                                     //lcd.println(motorStep/4000);
            digitalWrite(motorforward, HIGH);
            digitalWrite(motorreverse, LOW);
            delay(motorStep);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
            openElevatorDoor();
    }
    else if(motorDirection ==0){   // reverse
                Serial.print(" motor dxn" );
                Serial.print(motorDirection );
                 lcd.setCursor(6,3);
                                      lcd.print(" going down");
                                    // lcd.println(motorStep/4000);
           digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, HIGH);
            delay(motorStep);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
              openElevatorDoor();

      }
      
        //Serial.print("jumped here");
     motorDirection = -1; ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //   motorStep = 0;

      
    
    
  
  
  }

int runToLocation(int elevatorCall){  // run to the elevator car to the callev locaTION
  buttonNotclikced =1;
  Serial.print("call from");
  Serial.println(elevatorCall);

                          if(elevatorlocation ==0 && (elevatorCall== 1 || elevatorCall ==11)){
                             Serial.println(" call from first to 0");
                             motorDirection =1;
                             motorStep =1;
                                  lcd.setCursor(10,1);
                                    lcd.print(0);
                             runElevator(motorDirection , motorStep);                    
                            }
                          if(elevatorlocation ==0 && (elevatorCall== 2 ||elevatorCall ==22)){
                              Serial.println("call from second to zero");
                              motorDirection =1;
                               motorStep =1;
                              lcd.setCursor(10,1);
                                    lcd.print(0);
                                  runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                  if( digitalRead(firstUP)){     
                                    openElevatorDoor();
                                    }
                                  lcd.setCursor(10,1);
                                    lcd.print(1);
                                   runElevator(motorDirection , motorStep);
                           
                            }
                          if(elevatorlocation ==0 && elevatorCall== 33 ){
                               Serial.println("call from third to zero");
                               motorDirection =1;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print('0');
                                    delay(200);
                                  runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                  if( digitalRead(firstUP) == 1){   
                                    openElevatorDoor();
                                    }
                                 lcd.setCursor(10,1);
                                    lcd.print(1);
                                   runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                  if(digitalRead(secondUp) == 1){ 
                                    openElevatorDoor();
                                    }
                                 lcd.setCursor(10,1);
                                    lcd.print(2);
                                   runElevator(motorDirection , motorStep);
                          
                            }

                            if(elevatorlocation ==0 && elevatorCall== 0 ){
                               Serial.println("elevator door open ");
                              openElevatorDoor();
                               deliverPerson();
                            }
                          if(elevatorlocation ==1 && elevatorCall== 0 ){
                             Serial.println("call ground first to 1");
                             motorDirection =0;
                               motorStep =1;
                                 lcd.setCursor(10,1);
                                    lcd.print(1);
                                  runElevator(motorDirection , motorStep);
                            }

                            if(elevatorlocation ==1 && (elevatorCall== 1 ||elevatorCall ==11)){
                             Serial.println("elevator open : floor 1 ");
                             openElevatorDoor();
                               deliverPerson();
                            }
                            
                          if(elevatorlocation ==1 && (elevatorCall== 2 ||elevatorCall ==22)){
                             Serial.println("call from second to 1 ");
                             motorDirection =1;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(1);
                                  runElevator(motorDirection , motorStep);
                            }
                          if(elevatorlocation ==1 && elevatorCall== 33){
                             Serial.println("call from third to 1");
                             motorDirection =1;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(1);
                                  runElevatorTemp(motorDirection , motorStep);
                                  if(digitalRead(secondUp) == 1){ 
                                    openElevatorDoor();
                                    }
                                  delay(200);
                                 lcd.setCursor(10,1);
                                    lcd.print(2);
                                   runElevator(motorDirection , motorStep);
                                  
                            }
                          if(elevatorlocation ==2 && elevatorCall== 0 ){
                             Serial.println("call from zero to 2");
                             motorDirection =0;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(2);
                                  runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                  if(digitalRead(firstDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                    lcd.setCursor(10,1);
                                    lcd.print(1);
                                   runElevator(motorDirection , motorStep);
                            }
                          if(elevatorlocation ==2 && (elevatorCall== 1 ||elevatorCall ==11)){
                             Serial.println("call from first to 2");
                             motorDirection =0;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(2);
                                  runElevator(motorDirection , motorStep);
                            }

                             if(elevatorlocation ==2 && (elevatorCall== 2 ||elevatorCall ==22)){
                             Serial.println("elevator door open: floor 2");
                              openElevatorDoor();
                               deliverPerson();
                            }


                            
                           if(elevatorlocation ==2 && elevatorCall== 33){
                             Serial.println("call from third to 2");
                             motorDirection =1;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(2);
                                  runElevator(motorDirection , motorStep);
                            }


                            
                           if(elevatorlocation ==3 && elevatorCall== 0 ){
                             Serial.println("call from zero to 3");
                             motorDirection =0;
                               motorStep =1;
                            lcd.setCursor(10,1);
                                    lcd.print(3);
                                  runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                   if(digitalRead(secondDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                 lcd.setCursor(10,1);
                                    lcd.print(2);
                                   runElevatorTemp(motorDirection , motorStep);
                                   delay(200);
                                    if(digitalRead(firstDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                     lcd.setCursor(10,1);
                                    lcd.print(1);
                                   runElevator(motorDirection , motorStep);
                                  delay(200);
                                 
                            }
                           if(elevatorlocation ==3 && (elevatorCall== 1 ||elevatorCall ==11)){
                             Serial.println("call from first to 3");
                             motorDirection =0;
                               motorStep =1; 
                               lcd.setCursor(10,1);
                                    lcd.print(3);
                                    runElevatorTemp(motorDirection , motorStep);
                                  delay(200);
                                   if(digitalRead(secondDown) == 1){ 
                                    openElevatorDoor();
                                    }
                                  lcd.setCursor(10,1);
                                    lcd.print(2);
                                   runElevator(motorDirection , motorStep);
                            }
                            if(elevatorlocation ==3 && (elevatorCall== 2 ||elevatorCall ==22)){
                               Serial.println("call from second to 3");
                               motorDirection =0;
                               motorStep =1;
                             lcd.setCursor(10,1);
                                    lcd.print(3);
                                  runElevator(motorDirection , motorStep);
                              
                              }
                              if(elevatorlocation ==3 && elevatorCall== 33 ){
                             Serial.println("elevator door open : floor 3");
                              openElevatorDoor();
                               deliverPerson();
                            }
                            
                            
                    
  
 // return 0;
  
  
  }

  
int  getCallLocation(){


         while(buttonNotclikced){ 
        vgroundUP =  digitalRead(groundUP);
        vfirstUP =  digitalRead(firstUP);
        vfirstDown =  digitalRead(firstDown);
        vsecondUp =  digitalRead(secondUp);
        vsecondDown =  digitalRead(secondDown);
        vthirdDown =  digitalRead(thirdDown);
               if(vgroundUP ==1){
                callReslut =0;
                buttonNotclikced =0;
                }
                 if(vfirstUP ==1){
                callReslut =1;
                buttonNotclikced =0;
                }
                if(vfirstDown ==1){
                callReslut =11;
                buttonNotclikced =0;
                }
                if(vsecondUp ==1){
                callReslut =2;
                buttonNotclikced =0;
                }
                if(vsecondDown ==1){
                callReslut =22;
                buttonNotclikced =0;
                }
                if(vthirdDown ==1){
                callReslut =33;
                buttonNotclikced =0;
                }
          }
         
  return callReslut;
  }


int getElevatorLocation(){   // know where the elevator is located

  long duration, cm;

digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);


duration = pulseIn(echoPin, HIGH);
cm = duration / 29 / 2;
Serial.print(cm);
Serial.print("cm");
Serial.println();
int flag =1;
delay(100);
    while(flag){
      if(cm >57 && cm < 69){
        elevatorlocation = 0;
        flag =0;
        }
        if(cm <50 && cm >45 ){
        elevatorlocation = 1;
                flag =0;

        }
        if(cm >30 && cm <35){
        elevatorlocation = 2;
                flag =0;

        }
        if(cm >15 && cm < 20){
        elevatorlocation = 3;
                flag =0;

        
        }
        
       
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);


duration = pulseIn(echoPin, HIGH);
cm = duration / 29 / 2;
Serial.print(cm);
Serial.print("cm");
Serial.println();
}
  return elevatorlocation;
  
  }
  
  int runElevatorTemp(int motorDirection ,int  motorStep){
  motorDirection = motorDirection;
  motorStep = motorStep *4000;
  Serial.print(motorDirection);
  Serial.println(motorStep);
  
  if(motorDirection == 1){  // forward
               Serial.print(" right here" );
                   lcd.clear();
                                     lcd.setCursor(0,3);
                                      lcd.print(" going up");
                                     //lcd.println(motorStep/4000);
            digitalWrite(motorforward, HIGH);
            digitalWrite(motorreverse, LOW);
            delay(motorStep);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
           
    }
    else if(motorDirection ==0){   // reverse
               Serial.print(" OR  here" );
                 lcd.setCursor(0,3);
                                      lcd.print(" going down");
                                    // lcd.println(motorStep/4000);
           digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, HIGH);
            delay(motorStep);
            digitalWrite(motorforward, LOW);
            digitalWrite(motorreverse, LOW);
             
    }
      }
