#include <Servo.h>
// spcify inputs
int startbutton = 12;
int stopbutton = 11;
int proximityone = 20;
int proximityTwo = 21;
int tempraturesenosrOne = 53; 
int tempraturesenosrTwo = 52; 
int cameralow =22;
int camerahigh =23;
// specify outputs
int rollertwo = 2;
int rollerone = 3;
int conveyortwo = 4;
int conveyorone = 5;
int vacuumPump = 6;
int retracthor = 7;
int retractver = 8;
int extendvermotor = 9;
int extendhormotor = 10;
int rollerthree = 14;
int rollerfour = 15;
int heaterOne = 16;
int heatertwo = 17;
int cutterServopin = 18;
int pressureservopin = 45;
int pressureSensor =19; // set pin for interrupt
int flag = 1;
int state = 0;

int startbuttonlatch =0;
Servo cutterServo;
int conveyorTime;
int heatingtime;
Servo pressureservo;



int extendtime = 1000;
int retracttime = 1000;
int Athree;
int Afour;
int delaytime;

void setup() {
    attachInterrupt(digitalPinToInterrupt(pressureSensor),setpressure,RISING);
 pressureservo.attach(pressureservopin);
 cutterServo.attach(cutterServopin);
  pinMode(startbutton,INPUT);
  pinMode(stopbutton,INPUT);
  pinMode(proximityone,INPUT);
  pinMode(proximityTwo,INPUT);
  pinMode(tempraturesenosrOne,INPUT);
  pinMode(tempraturesenosrTwo,INPUT);
    pinMode(cameralow,INPUT);
    pinMode(camerahigh,INPUT);
      pinMode(startbutton,INPUT);
      pinMode(pressureSensor,INPUT);


      pinMode(rollertwo,OUTPUT);
      pinMode(rollerone,OUTPUT);
       pinMode(conveyortwo,OUTPUT);
      pinMode(conveyorone,OUTPUT);
      pinMode(vacuumPump,OUTPUT);
      pinMode(retracthor,OUTPUT);
      pinMode(retractver,OUTPUT);
      pinMode(extendvermotor,OUTPUT);
      pinMode(extendhormotor,OUTPUT);
      pinMode(rollerthree,OUTPUT);
      pinMode(rollerfour,OUTPUT);
      pinMode(heaterOne,OUTPUT);
      pinMode(heatertwo,OUTPUT);
 Serial.begin(9600);
}

void loop() {
   int start =  digitalRead(startbutton);
   if(start == 1){
    startbuttonlatch =1;
    }
    while(startbuttonlatch ==HIGH){
       int paperstauts =  digitalRead(proximityone);
      if(paperstauts ==HIGH){
        feederStart();
        paperstauts = 0;
        }
        else{
          Serial.println("there is no paper to laminate");
          }
      }

 

}  
void feederStart(){
     
       cylinderMechanisim();
       int   temp_one = digitalRead(tempraturesenosrOne);
          Serial.println(temp_one);
       int   temp_two = digitalRead(tempraturesenosrTwo);
          Serial.println(temp_two);
                while( temp_one != 1 || temp_two !=1){
                  Serial.println("Heating the laminator");
                 delay(1000);

                    int   temp_one = digitalRead(tempraturesenosrOne);                            
                     Serial.print(temp_one);
                     Serial.println("degree");
                      int   temp_two = digitalRead(tempraturesenosrTwo);
                       Serial.println(temp_two);
                  
                  }
                 
                  call_camera();
                    
                  
       
  
  
  }

 void cylinderMechanisim(){

  digitalWrite(extendhormotor,HIGH);
        delay(extendtime);
        digitalWrite(extendhormotor,LOW);
        digitalWrite(extendvermotor,HIGH);
        delay(extendtime);
         digitalWrite(extendvermotor,LOW);
        digitalWrite(vacuumPump,HIGH);
        delay(500);
        digitalWrite(retractver,HIGH);
        delay(retracttime);
          digitalWrite(retractver,LOW);
        digitalWrite(retracthor,HIGH);
        delay(retracttime);
         digitalWrite(retracthor,LOW);
          digitalWrite(vacuumPump,LOW);
        delay(500);

  }
 void  call_camera(){
        while(flag ==1){
           Serial.println("i am here ");
           
          int aFourpaper  = digitalRead(cameralow);
          int aThreepaper  = digitalRead(camerahigh);
           Serial.println("i am here ");
             Serial.println(aFourpaper);
               Serial.println(aThreepaper);
           
                  delay(4000);
          if(aFourpaper == 1 && aThreepaper ==0){
            // a4 size paper
                  delaytime = 2500;
                    Serial.println("paper size :A4");
                    flag = 0;
            
            }
         else   if(aFourpaper == 0 && aThreepaper ==1){

            // a3 size paper
                  delaytime = 5000;
                 Serial.println("paper size :A3");
                  flag = 0;

                  }
                  else {
                    Serial.println("detecting paper size");
                    }

          }
          call_laminator();
          
    
    
    }
    void call_laminator(){
                  digitalWrite(conveyorone,HIGH);
                  delay(4000);
                  digitalWrite(conveyorone,LOW);   
                    int proximitystatus  = digitalRead(proximityTwo);
                    Serial.println("proximity");
                    Serial.println(proximitystatus);
                    delay(300);
                  if(proximitystatus == 1){
                     digitalWrite(conveyortwo,HIGH);
                                         Serial.println("conveyor");
                                         delay(100);
                     digitalWrite(rollerone,HIGH);
                       Serial.println("roller");
                                         delay(100);
                     digitalWrite(rollertwo,HIGH);
                     digitalWrite(rollerthree,HIGH);
                     digitalWrite(rollerfour,HIGH);
                     delay(3000);
                     delay(delaytime);
                     for(int i=0 ; i <90; i ++){
                         cutterServo.write(i); 
                         delay(15);
                      }
                       for(int i =50 ; i >0; i --){
                          cutterServo.write(i);
                         delay(15);
                      }
                        Serial.println("servo");
                                         delay(100);
                  
                   
                   
                     digitalWrite(conveyortwo,LOW);
                      digitalWrite(rollerone,LOW);
                     digitalWrite(rollertwo,LOW);
                     digitalWrite(rollerthree,LOW);
                     digitalWrite(rollerfour,LOW);
                    }
      
      } void setpressure(){
        Serial.println("interrupted succes");

         if(state == 0){
                   for(int i=45 ; i <90; i ++){
                         pressureservo.write(i); 
                         delay(15);
                      }
              Serial.println("got in state 0 succes");
                      state =1;
          }
          else if(state == 1){
             for(int i=90 ; i< 130; i ++){
                         pressureservo.write(i); 
                         delay(15);
                
                      } 

                 Serial.println("got in state 1 succes");

                      state = 2;
            }
             else if(state == 2){
             for(int i=130 ; i< 180; i ++){
                         pressureservo.write(i); 
                         delay(15);
                
                      } 

                 Serial.println("got in state 2 succes");

                      state = 0;
            }
            else{
              state = 0;
              }
        
        }
