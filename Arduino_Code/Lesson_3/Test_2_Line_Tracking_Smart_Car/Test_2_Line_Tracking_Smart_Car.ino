#define ENA  2              //pin of controlling speed---- ENA of motor driver board
#define ENB  3              //pin of controlling speed---- ENB of motor driver board
int pinLB=4;              //pin of controlling turning---- IN1 of motor driver board
int pinLF=5;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=6;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board

void Infrared_Tracing() {
  int Left_Tra_Value = 1;
  int Center_Tra_Value = 1;
  int Right_Tra_Value = 1;
  int Black = 1;
  Left_Tra_Value = digitalRead(10);
  Center_Tra_Value = digitalRead(11);
  Right_Tra_Value = digitalRead(12);
  if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {//010
    advance();
    Set_Speed(150);//setting speed 150
  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {//110
    turnLeft();
    Set_Speed(150);//setting speed 150
  } else if (Left_Tra_Value == Black && (Center_Tra_Value != Black && Right_Tra_Value != Black)) {//100
    turnL();
    Set_Speed(150);//setting speed 150
  } else if (Left_Tra_Value != Black && (Center_Tra_Value != Black && Right_Tra_Value == Black)) {//001
    turnR();
    Set_Speed(150);//setting speed 150
  } else if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {//011
    turnRight();
    Set_Speed(150);//setting speed 150
  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)){//111
    stopp();
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(ENA,OUTPUT);    // pin 2(PWM) 
  pinMode(ENB,OUTPUT);    // pin 3(PWM) 
  pinMode(pinLB,OUTPUT);  // pin 4
  pinMode(pinLF,OUTPUT);  // pin 5
  pinMode(pinRB,OUTPUT);  // pin 6
  pinMode(pinRF,OUTPUT);  // pin 7
}

void loop(){
  Infrared_Tracing();

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
