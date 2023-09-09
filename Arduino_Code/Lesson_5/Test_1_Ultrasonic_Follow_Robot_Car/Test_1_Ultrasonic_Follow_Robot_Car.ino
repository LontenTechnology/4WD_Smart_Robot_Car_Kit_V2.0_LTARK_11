
#include <Servo.h>

volatile int D_mix;
volatile int D_mid;
volatile int D_max;

#define ENA  2              //pin of controlling speed---- ENA of motor driver board
#define ENB  3              //pin of controlling speed---- ENB of motor driver board
int pinLB=4;              //pin of controlling turning---- IN1 of motor driver board
int pinLF=5;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=6;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board

Servo myservo;
float checkdistance() {
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  float distance = pulseIn(9, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Ultrasonic_Follow() {
  int Infrared_Trigger_Flag = 0;
  int Front_Distance = 0;
  int Left_Distance = 0;
  int Right_Distance = 0;
  int Right_IR_Value = 1;
  int Left_IR_Value = 1;
  Left_IR_Value = digitalRead(A3);
  Right_IR_Value = digitalRead(A2);
  Front_Distance = checkdistance();
  if (Front_Distance < D_mix && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    stopp();
  } else if (Front_Distance < D_mix && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    turnLeft();
    Set_Speed(150);
  } else if (Front_Distance < D_mix && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    turnRight();
    Set_Speed(150);
  } else if (Front_Distance < D_mix && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    stopp();
  } else if (Front_Distance > D_mid && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    advance();
    Set_Speed(150);
  } else if (Front_Distance > D_mid && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    turnLeft();
    Set_Speed(150);
  } else if (Front_Distance > D_mid && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    turnRight();
    Set_Speed(150);
  } else if ((D_mix <= Front_Distance && Front_Distance <= D_mid) && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    turnR();
    Set_Speed(150);
  } else if ((D_mix <= Front_Distance && Front_Distance <= D_mid) && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    turnL();
    Set_Speed(150);
  } else if ((D_mix <= Front_Distance && Front_Distance <= D_mid) && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    stopp();
  }
}

void setup(){
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Serial.begin(9600);
  myservo.attach(13);
  myservo.write(90);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);

  pinMode(ENA,OUTPUT);    // pin 2(PWM) 
  pinMode(ENB,OUTPUT);    // pin 3(PWM) 
  pinMode(pinLB,OUTPUT);  // pin 4
  pinMode(pinLF,OUTPUT);  // pin 5
  pinMode(pinRB,OUTPUT);  // pin 6
  pinMode(pinRF,OUTPUT);  // pin 7
}

void loop(){
  Ultrasonic_Follow();
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
