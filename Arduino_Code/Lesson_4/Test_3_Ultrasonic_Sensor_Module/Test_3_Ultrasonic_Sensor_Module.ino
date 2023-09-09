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
void Ultrasonic_Sensor_Module() {
  int Distance = 0;
  Distance = checkdistance();
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.println("CM");
  delay(100);
}
void setup(){
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
}
void loop(){
  Ultrasonic_Sensor_Module();

}
