#define ENA  2              //pin of controlling speed---- ENA of motor driver board
#define ENB  3              //pin of controlling speed---- ENB of motor driver board
int pinLB=4;              //pin of controlling turning---- IN1 of motor driver board
int pinLF=5;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=6;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board

void setup()
{
  pinMode(ENA,OUTPUT);    // pin 2(PWM) 
  pinMode(ENB,OUTPUT);    // pin 3(PWM) 
  pinMode(pinLB,OUTPUT);  // pin 4
  pinMode(pinLF,OUTPUT);  // pin 5
  pinMode(pinRB,OUTPUT);  // pin 6
  pinMode(pinRF,OUTPUT);  // pin 7
}
void loop()
{
  advance();
  Set_Speed(200);//setting speed 200
  delay(2000);//waiting 2 seconds
  back();
  Set_Speed(200);
  delay(2000);
  turnL();
  Set_Speed(200);
  delay(2000);
  turnR();
  Set_Speed(200);
  delay(2000);
  stopp();
}

void Set_Speed(unsigned char pwm) //function of setting speed
{
  analogWrite(ENA,pwm);
  analogWrite(ENB,pwm);
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
