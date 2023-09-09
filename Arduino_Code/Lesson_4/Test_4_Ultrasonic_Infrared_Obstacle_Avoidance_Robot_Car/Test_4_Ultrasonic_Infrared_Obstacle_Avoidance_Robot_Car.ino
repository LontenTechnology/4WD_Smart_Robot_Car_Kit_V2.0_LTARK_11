
#include <Servo.h>
#define ENA  2              //pin of controlling speed---- ENA of motor driver board
#define ENB  3              //pin of controlling speed---- ENB of motor driver board
int pinLB=4;              //pin of controlling turning---- IN1 of motor driver board
int pinLF=5;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=6;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board
int mySpeed=130;
volatile int D_mix;
volatile int D_mid;
volatile int D_max;
volatile int Front_Distance;
volatile int Left_Distance;
volatile int Right_Distance;
volatile int Right_IR_Value;
volatile int Left_IR_Value;

void Ultrasonic_obstacle_avoidance() {
  if (Front_Distance <= D_mid) {
    stopp();
    if (Front_Distance <= D_mid && (Left_IR_Value == 0 && Right_IR_Value == 0)) {
      back();
      Set_Speed(mySpeed);
      delay(300);
      stopp();
    }
    stopp();
    Detect_Left_and_Right__distance();
    if (Left_IR_Value <= D_mid || Right_IR_Value <= D_mid) {
      if (Left_IR_Value > Right_IR_Value) {
        turnLeft();
        Set_Speed(mySpeed);
        delay(300);
        stopp();
      } else {
        turnRight();
        Set_Speed(mySpeed);
        delay(300);
        stopp();
      }   
    }
    else {
      advance();
      Set_Speed(mySpeed);
     }
   }
}

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

void Detect_Left_and_Right__distance() {
  myservo.write(165);
  delay(500);
  //Serial.println(Left_Distance);
  delay(100);
  Left_Distance = checkdistance();
  myservo.write(15);
  delay(500);
  //Serial.println(Right_Distance);
  delay(100);
  Right_Distance = checkdistance();
  myservo.write(90);
}

void Obstacle_Avoidance_Main() {
  Left_IR_Value = digitalRead(A3);
  Right_IR_Value = digitalRead(A2);
  Front_Distance = checkdistance();
  //Serial.println(Front_Distance);
  Infrared_Obstacle_Avoidance();
}

void Infrared_Obstacle_Avoidance() {
  if (Left_IR_Value == 0 && Right_IR_Value == 1) {
   turnRight();
   Set_Speed(mySpeed);
   delay(300);
   stopp();
  } else if (Left_IR_Value == 1 && Right_IR_Value == 0) {
    turnLeft();
    Set_Speed(mySpeed);
    delay(300);
    stopp();
  } else if (Left_IR_Value == 1 && Right_IR_Value == 1){
    //There are no obstacles on either side
    Ultrasonic_obstacle_avoidance();
    advance();
    Set_Speed(mySpeed);
  }
}

void setup(){
  pinMode(ENA,OUTPUT);    // pin 2(PWM) 
  pinMode(ENB,OUTPUT);    // pin 3(PWM) 
  pinMode(pinLB,OUTPUT);  // pin 4
  pinMode(pinLF,OUTPUT);  // pin 5
  pinMode(pinRB,OUTPUT);  // pin 6
  pinMode(pinRF,OUTPUT);  // pin 7
  myservo.attach(13);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Front_Distance = 0;
  Left_Distance = 0;
  Right_Distance = 0;
  Right_IR_Value = 1;
  Left_IR_Value = 1;
  myservo.write(90);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop(){
  Obstacle_Avoidance_Main();
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
     digitalWrite(pinRB,LOW);
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,LOW);
     digitalWrite(pinLF,LOW);
 }
