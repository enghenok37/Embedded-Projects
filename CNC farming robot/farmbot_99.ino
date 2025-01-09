#include <Servo.h>

#include <Stepper.h>

const int stepsPerRevolution = 200;  

// initialize the stepper library on pins 8 through 11:
Stepper XStepper(stepsPerRevolution,  30, 31, 32, 33);
Stepper YStepper(stepsPerRevolution,  34, 35, 36, 37);
Stepper ZStepper(stepsPerRevolution,  38, 39, 40, 41);
int moistureTable [100][100];
 Servo postionSevo;
const int tigger = 2; 
const int answer = 3; 
long times, distance;
int average;
int count;
int firstrun =1;
int xlocation ;
int ylocation;
int zlocation;
int rasberrypi = 52;
int rasberrypiReaspone = 53;
    int xmoves;
    int Ymoves;
    int Zmoves;

   int  ylimit = 10000;
   int xlimit =200000;
int zeroloaction;
 int stepsPermm =2000;
 int seeddistance = 50;
int waterneed = 0;
 int vaccumPUMP = 44;
 int moisturesensorPIN = A0;   // declaring moisture  sensor pin
    int tempratureSensor=A1;       //declaring temprature  sensor pin
    int pumpPIN =12; 
    int buzzerPIN= 13;
    int activityPIN=4;    //  activity of the whole system @ notify
    int fullLedPIN=5;
    int balancedLedPIN =6;
    int alertLedPIN= 7;        // notfication LEDs declaring
   
    
    int completelyDry;   //level of water of soil variable
    int mediumMoist;
    int completelyMoist;
    int good;
    int moreWater;  //water to supply
    int mediumWater;
    int noWater;
    int lessWater;
   
void setup() {


   // set the speed at 60 rpm:
  XStepper.setSpeed(60); 
  YStepper.setSpeed(60);  
  ZStepper.setSpeed(60);
 
 postionSevo.attach(25);
   pinMode(tigger, OUTPUT);
   pinMode(answer, INPUT);
 /*declaring pins to digital out put and input */
      pinMode(rasberrypiReaspone, INPUT);

    pinMode( vaccumPUMP,OUTPUT);
      pinMode(pumpPIN,OUTPUT);
    pinMode(alertLedPIN,OUTPUT);
    pinMode(fullLedPIN,OUTPUT);
    pinMode(balancedLedPIN,OUTPUT);
    pinMode(buzzerPIN,OUTPUT);
    pinMode(activityPIN,OUTPUT);

     pinMode(rasberrypi, OUTPUT);
  // initialize serial communication  with the computer 
  Serial.begin(9600);
}

void loop() {

  xlocation = getToolMountLOcation(1);
  ylocation = getToolMountLOcation(2);
  zlocation = getToolMountLOcation(3);


  if((xlocation !=0) || (ylocation != 0) || ( zlocation !=0)  ){
    
     xmoves = stepsPermm * xlocation*(-1);
     Ymoves = stepsPermm * ylocation*(-1);
     Zmoves = stepsPermm * zlocation*(-1);
      runToLocation(xmoves ,Ymoves ,Zmoves);   
    }
    if(firstrun =1){
      firstrun =0;
      call_Seeder();
      }

   else{
     waterneed = run_moisutre_check();
      if(waterneed >500 ){
        go_watering();
        }
        else {
          
          run_image_proceesing ();
            
            
            
          
     
    }


}
} 

void run_image_proceesing (){
       int tool = 4;
       grab_Tool( tool);
        int cameraRespone;
        for(int y = 0 ; y < ylimit; y++){
        YStepper.step(seeddistance);
          for( int x = 0 ; x < xlimit; x++){
                    XStepper.step(seeddistance);
                     digitalWrite(rasberrypi , HIGH);
                        delay(2000);
                      cameraRespone  =   digitalRead(rasberrypiReaspone);
                      if(cameraRespone ==1 ){   // there is weed;
                        ZStepper.step(-150);  
                        delay(10);
                        ZStepper.step(150);  
                        delay(10);

                        ZStepper.step(-150);  
                        delay(10);
                        ZStepper.step(150);  
                        delay(10);
                        ZStepper.step(-150);  
                        delay(10);
                        ZStepper.step(150);  
                        delay(10);
                        }

      }
    
    }
   

        
        
        
        
        
       
             
  
  }
void go_watering(){

int tool = 5;
  grab_Tool( tool);
 for(int y = 0 ; y < ylimit; y++){
        YStepper.step(seeddistance);
          for( int x = 0 ; x < xlimit; x++){
                    XStepper.step(seeddistance);
                     runWatering();
                     XStepper.step(seeddistance);               
      }  
  
  }

    return_Tool( tool);
    
}

int run_moisutre_check(){

 int tool = 3;  // 3 for sensor
 
   go_to_Toolbay();
   grab_Tool(tool);    
     for(int y = 0 ; y < ylimit; y++){
        YStepper.step(seeddistance);
          for( int x = 0 ; x < xlimit; x++){
                    XStepper.step(seeddistance);
                     int   moisture =  digitalRead(moisturesensorPIN);
                      moistureTable[x][y] = moisture;
                         ZStepper.step(-100);  
                     XStepper.step(seeddistance); 
                      ZStepper.step(100);  
                     
                     
      }
    
    }
    for(int i = 0 ; i <100 ; i ++){
      
      for(int j = 0 ; j < 100 ; j ++){
         average = average +  moistureTable[i][j];
         count = count +1;
        
        }}
       int  result = average /count;


           return_Tool( tool);
    return result;
   
 
  
  
  
  
  }
int  grab_Tool(int tool){
      if(tool == 1){   // seeder
           YStepper.step(-200);
           ZStepper.step(-100);
           XStepper.step(0);
          YStepper.step(400);
          ZStepper.step(100);      
    }
    else if (tool == 2){  // seed grab

           
           ZStepper.step(-100);
           XStepper.step(0);
           digitalWrite(vaccumPUMP ,HIGH);
           ZStepper.step(100);
      
      }
      else if (tool == 3){  // moisture 
          YStepper.step(-200);
           ZStepper.step(-100);
           XStepper.step(200);
          YStepper.step(400);
          ZStepper.step(100);
      
      }
       else if (tool == 4){   // weeder
         YStepper.step(-200);
           ZStepper.step(-100);
           XStepper.step(400);
          YStepper.step(400);
          ZStepper.step(100);
      
      }
        else if (tool == 5){   // waterer
         YStepper.step(-200);
           ZStepper.step(-100);
           XStepper.step(600);
          YStepper.step(400);
          ZStepper.step(100);
      
      }
  
  
  }
  int  return_Tool(int tool){
      if(tool == 1){   // seeder
           YStepper.step(200);
           ZStepper.step(-100);
           XStepper.step(0);
          YStepper.step(-400);
          ZStepper.step(100);      
    }
   
      else if (tool == 3){  // moisture 
          YStepper.step(200);
           ZStepper.step(-100);
           XStepper.step(200);
          YStepper.step(-400);
          ZStepper.step(100);
      
      }
       else if (tool == 4){   // weeder
         YStepper.step(200);
           ZStepper.step(-100);
           XStepper.step(400);
          YStepper.step(-400);
          ZStepper.step(100);
      
      }
       else if (tool == 5){   // waterer
           YStepper.step(200);
           ZStepper.step(-100);
           XStepper.step(600);
          YStepper.step(-400);
          ZStepper.step(100);
      
      }
  
  
  }

void go_to_Toolbay(){
  int xtoolbay = 10000;
  int ytoolbay = 7800;
  int ztoolbay = 2000;
     XStepper.step(xtoolbay);
     YStepper.step(ytoolbay);
     ZStepper.step(ztoolbay);
  
  }

 void call_Seeder(){
  int tool = 1;  // 1 for seeder
  int seed = 2;
   go_to_Toolbay();
   grab_Tool(tool);
   for(int y = 0 ; y < ylimit; y++){
        YStepper.step(seeddistance);
          for( int x = 0 ; x < xlimit; x++){
                    XStepper.step(seeddistance);
                    digitalWrite(vaccumPUMP ,LOW);
                     go_to_Toolbay();  
                     XStepper.step(seeddistance); 
                     YStepper.step(seeddistance);
                     
                     
      }
    
    }
    return_Tool( tool);
 
  
  
  }
 
 int  runToLocation(int xmoves , int Ymoves ,  int Zmoves){{
     // step one revolution  in one direction:
               Serial.println("LOCation::Field");
               Serial.println("moving xstepper= TOOLMOUNT");
               Serial.println("moving ystepper= TOOLMOUNT");
               Serial.println("moving zstepper= TOOOLMOUNT");

                    XStepper.step(xmoves);
                      delay(2000);
                    YStepper.step(Ymoves);
                      delay(2000);
                    ZStepper.step(6600);
                      delay(Zmoves);
    
    }
  }
  

int getToolMountLOcation(int i ) {

  if (i ==1){
               postionSevo.write(0);
              digitalWrite(tigger, LOW);
              delayMicroseconds(2);
              digitalWrite(tigger, HIGH);
              delayMicroseconds(10);
              digitalWrite(tigger, LOW);
              
              
              times = pulseIn(answer, HIGH);
              distance = times / 29 / 2;
              Serial.print(distance);
              Serial.println("X distance");
    }
    else if(i ==2){
               postionSevo.write(90);
              digitalWrite(tigger, LOW);
              delayMicroseconds(2);
              digitalWrite(tigger, HIGH);
              delayMicroseconds(10);
              digitalWrite(tigger, LOW);
              
              
              times = pulseIn(answer, HIGH);
              distance = times / 29 / 2;
              Serial.print(distance);
              Serial.println("Y Distance");
      
      }
      else {
               postionSevo.write(45);
              digitalWrite(tigger, LOW);
              delayMicroseconds(2);
              digitalWrite(tigger, HIGH);
              delayMicroseconds(10);
              digitalWrite(tigger, LOW);
              
              
              times = pulseIn(answer, HIGH);
              distance = times / 29 / 2;
              Serial.print(distance);
              Serial.println("Z distance");
      
      
      }



return distance;

}
void runWatering() {

  
    //light up the devices activity LED always to be on
       digitalWrite(activityPIN,HIGH);

  // read the input on analog pin 0 from the moisture sonsor:
        int sensorReading=analogRead(moisturesensorPIN);
        
  // if there is no water on the soil at the reading
    if (sensorReading>= 5 && sensorReading<=completelyDry)
    {
        digitalWrite(alertLedPIN,HIGH); 
        digitalWrite(pumpPIN,HIGH);
        digitalWrite(fullLedPIN ,LOW); 
        digitalWrite(balancedLedPIN ,LOW); 
        digitalWrite(buzzerPIN ,LOW); 
        delay(moreWater);
       int  sensorCheck=analogRead(moisturesensorPIN);
        if (sensorCheck > sensorReading && sensorCheck >completelyDry )
        {
          digitalWrite(pumpPIN, LOW);
        }
        else
        {
                beep(100);
               delay(2000);
          return;
          }
       
  }
   //if the amount of water is dry but with some moisture meaning not completly dry 
     else if(sensorReading>=completelyDry &&  sensorReading<=mediumMoist)
    {
          digitalWrite(alertLedPIN ,LOW);  
          digitalWrite(pumpPIN,HIGH); 
          digitalWrite(fullLedPIN,LOW);    
          digitalWrite(balancedLedPIN,HIGH);  
          digitalWrite(buzzerPIN ,LOW);   
          delay(mediumWater);

        int  sensorCheck=analogRead(moisturesensorPIN);
           if (sensorCheck > sensorReading && sensorCheck > mediumMoist )
        {
          digitalWrite(pumpPIN, LOW);
        }
        else
        {
           beep(100);
               delay(2000);
          return;
          }

     
    }
      //if the amount of moisture is about 80%  
   
   //if the amount of moisture is full
    else if(sensorReading > mediumMoist && sensorReading<=completelyMoist)
    {
          digitalWrite(pumpPIN ,LOW); 
          digitalWrite( alertLedPIN,LOW); 
          digitalWrite(fullLedPIN,HIGH);
          digitalWrite(balancedLedPIN,LOW);  
          digitalWrite(buzzerPIN,LOW);  
          delay(noWater);
          
     }
    
             // check status every two minutes of time   
               delay(12000);
    
          // print out the value you read:
        Serial.println(sensorReading);
               delay(1);        // delay in between reads for stability
}



void beep(unsigned char delayms){
 for(int i=0; i<30;i++){
   
  analogWrite(buzzerPIN, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(buzzerPIN, 0);       // 0 turns it off
  delay(delayms); 
   
  
  
  }// wait for a delayms ms   
}  
 
