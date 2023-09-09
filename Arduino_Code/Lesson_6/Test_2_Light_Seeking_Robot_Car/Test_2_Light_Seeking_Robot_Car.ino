#define ENA  2              //pin of controlling speed---- ENA of motor driver board
#define ENB  3              //pin of controlling speed---- ENB of motor driver board
int pinLB=4;              //pin of controlling turning---- IN1 of motor driver board
int pinLF=5;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=6;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board

volatile float leftSensorValue;
volatile float rightSensorValue;
volatile int speed_value;

void Light_Seeking() {
  leftSensorValue = analogRead(A1);
  rightSensorValue = analogRead(A0);
  if (leftSensorValue < 100 && rightSensorValue < 100) {
    // Light is detected on both sides, and the car is moving forward
    advance();
    Set_Speed(speed_value);
  } else if (leftSensorValue < 50) {
    // Light detected on the left side, car turning left
    turnLeft();
    Set_Speed(speed_value);
  } else if (rightSensorValue < 50) {
    // Light detected on the right side, car turning right
      turnRight();
      Set_Speed(speed_value);
  } else {
    // No light detected on both sides, the car stopped
    stopp();
  }
}

void setup(){
  leftSensorValue = 0;
  rightSensorValue = 0;
  speed_value = 150;
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(ENA,OUTPUT);    // pin 2(PWM) 
  pinMode(ENB,OUTPUT);    // pin 3(PWM) 
  pinMode(pinLB,OUTPUT);  // pin 4
  pinMode(pinLF,OUTPUT);  // pin 5
  pinMode(pinRB,OUTPUT);  // pin 6
  pinMode(pinRF,OUTPUT);  // pin 7
}

void loop(){
  Light_Seeking();

}
void Set_Speed(int speedPWM) //function of setting speed
{
  analogWrite(ENA,speedPWM);
  analogWrite(ENB,speedPWM);
}
void advance()    //  going forward
   {
     digitalWrite(pinRB,LOW);  
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,LOW);  
     digitalWrite(pinLF,HIGH); 
   }
void back()         //back up
   {
     digitalWrite(pinRB,HIGH);   
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);  
     digitalWrite(pinLF,LOW);
   }
void turnLeft()      //turn left
  {
     digitalWrite(pinRB,LOW);  
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);  
  }
void turnRight()     //turn right
  {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );   
     digitalWrite(pinLB,LOW);   
     digitalWrite(pinLF,LOW);
  }
void turnR()         //turn right in place
 {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );   
     digitalWrite(pinLB,LOW);   
     digitalWrite(pinLF,HIGH);
 }
void turnL()        //turn left in place
 {
     digitalWrite(pinRB,LOW);  
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW); 
 }    
void stopp()        //stop
 {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
 }

