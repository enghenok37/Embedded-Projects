#include <Servo.h>

#include <SoftwareSerial.h>


int motorOneFw = 9;
int motorOneRv = 10;
int motorTwoFw = 11;
int motorTwoRv = 12;
int ploughMotor = 7;
int led = 6;
char order;
int functionState = 0 ;
int servoState = 1;
Servo servoMech ;
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() 
{  
servoMech.attach(8);
  
pinMode(led, OUTPUT); 
pinMode(ploughMotor, OUTPUT); 
pinMode(motorOneFw, OUTPUT);
pinMode(motorOneRv, OUTPUT); 
pinMode(motorTwoFw, OUTPUT); 
pinMode(motorTwoRv, OUTPUT);  
Serial.begin(9600);
 mySerial.begin(57600);

mySerial.println(" ROBOT ::OFF ");
 servoMech.write(120); 
}

void loop()
{
  while (Serial.available() > 0)
  {
  order = Serial.read();
  mySerial.println(order);
  }
      
  if( order == 'F'&&  functionState == 1) // Forward
    {
              forward();
    }
  else if(order == 'B'&&  functionState == 1) // Backward
    {
              backward();
    }
  
    else if(order == 'L'&&  functionState == 1) //Left
    {     
               left();
    }
    else if(order == 'R'&&  functionState == 1) //Right
    {
            right();
    }
    
  else if(order == 'X') //Stop
    {

            Stop();
   
    }
    else if(order == 'M') //Stop
    {

           start();
   
    }
    else if(order == '0' &&  functionState == 1) //stop the move 
    {
           
            
                 digitalWrite(motorOneFw, LOW);
                 digitalWrite(motorOneRv, LOW);
                 digitalWrite(motorTwoFw, LOW);
                 digitalWrite(motorTwoRv, LOW); 
          

      
   
    }
     else if(order == 'P'&&  functionState == 1) //lower servo and gear 
    {
          int  temp = 1;
      if (servoState == 1 && temp ==1){
              temp ==0;
              servoState = 0;
               startPlough();
        
        
        }
        else if (servoState == 0 && temp ==1){
              temp ==0;
              servoState = 1;
              stopPlough();
          }
         
       
      
    }


    

}
void forward(){
       digitalWrite(motorOneFw, HIGH);
        digitalWrite(motorOneRv, LOW);
      digitalWrite(motorTwoFw, HIGH);
      digitalWrite(motorTwoRv, LOW); 
     mySerial.println(" ROBOT ::MOVED FORWARD");
  
  
  }
  void backward(){
    
      digitalWrite(motorOneFw, LOW);
      digitalWrite(motorOneRv, HIGH);
      digitalWrite(motorTwoFw, LOW);
      digitalWrite(motorTwoRv, HIGH); 
      mySerial.println(" ROBOT ::moved BACK ");
    }

     void left(){
    
    digitalWrite(motorOneFw, LOW);
    digitalWrite(motorOneRv, LOW);
    digitalWrite(motorTwoFw, HIGH);
    digitalWrite(motorTwoRv, LOW);
    mySerial.println(" ROBOT ::TURNED LEFT ");
    
    }



     void right(){
     digitalWrite(motorOneFw, HIGH);
    digitalWrite(motorOneRv, LOW);
    digitalWrite(motorTwoFw, LOW);
    digitalWrite(motorTwoRv, LOW); 
      mySerial.println(" ROBOT ::TURNED RIGHT ");
    
    
    }
    void Stop(){

       functionState =0;
         mySerial.println(" ROBOT ::STOPPED");
       digitalWrite(motorOneFw, LOW);
       digitalWrite(motorOneRv, LOW);
       digitalWrite(motorTwoFw, LOW);
       digitalWrite(motorTwoRv, LOW); 
        
                       
                     
                
                
                digitalWrite(ploughMotor, LOW);
                digitalWrite(led, LOW);

       
      }

      void start(){
       functionState =1;
       mySerial.println(" ROBOT ::TURNED ON ");
        digitalWrite(led, HIGH);

        
        
        }

 void  startPlough(){
          
           for(int i=120 ; i> 60; i --){
                         servoMech.write(i); 
                         delay(15);
                
                      } 
           
           digitalWrite(ploughMotor, HIGH); 

                      
          
        
          }  
          
 void   stopPlough(){

              for(int i=60 ; i< 120; i ++){
                         servoMech.write(i); 
                         delay(15);
                
                      } 
                digitalWrite(ploughMotor, LOW);
          
          
          }
