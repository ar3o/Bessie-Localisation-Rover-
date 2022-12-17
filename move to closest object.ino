int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control
int trigPin = 3;    // Trigger
int echoPin = 4;    // Echo
long duration, cm;
int leftspeed = 255; //default speeds, 255 is maximum speed, ~75 lowest
int rightspeed = 255;
int distances[15];


void setup(void)

{
  int i;
  for(i=5;i<=8;i++)
  pinMode(i, OUTPUT);
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 15; i++){
    distances[i] = 99999;
  }

}

void loop()
{
  
  uint32_t period1 = 5 * 1000L;       // 5 secs
  uint32_t period2 = 300L;           //0.3sec
  //for( uint32_t tStart = millis();  (millis()-tStart) < period1;  ){
  for (int i = 0; i < 15; i++){
    for( uint32_t tStart = millis();  (millis()-tStart) < period2;  ){
    right(leftspeed, rightspeed);
    }
    delay(200);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // Convert the time into a distance
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    Serial.print(cm);
    Serial.print("cm");
    distances[i] = cm;
    Serial.println();
    if ((cm) < 4)
      stop();
    
  }
  byte NUMBER_OF_ELEMENTS = sizeof(distances) / sizeof(distances[0]);
  int min = 32000;  //start with a huge value
  for (int index = 0; index < NUMBER_OF_ELEMENTS; index++)
  {
    if (distances[index] < min)
    {
      min = distances[index]; //save the new minimum *value*
    }
  }
  Serial.print(min);
  
  delay(3000);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  while ((cm) > (min+2)){
    
    right(leftspeed, rightspeed);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // Convert the time into a distance
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    while ((cm) < 4)
      stop();
  
  }
  stop();
  //leftspeed = 150; //default speeds, 255 is maximum speed, ~75 lowest
  //rightspeed = 150;
  while ((cm) > 6){
     digitalWrite(trigPin, LOW);
     delayMicroseconds(5);
     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin, LOW);
     pinMode(echoPin, INPUT);
     duration = pulseIn(echoPin, HIGH);
     // Convert the time into a distance
     cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
     Serial.print(cm);
     Serial.print("cm");
     Serial.println();
     Serial.print(min);
     Serial.print(cm);
     Serial.print("cm");
     forward(leftspeed, rightspeed);
  }
  stop();
  delay(20000);
}


void stop(void) //Stop
  {
    digitalWrite(E1,LOW);
    digitalWrite(E2,LOW);
    Serial.println("stop");
  }


void forward(char a,char b)
  {
    
    for (int i = 0; i < 4; i++){
    analogWrite (E1,a);
    digitalWrite(M1,LOW);
    analogWrite (E2,b);
    digitalWrite(M2,LOW);
    Serial.println("forward");
    stop();
    }
  }
  
void reverse (char a,char b)
  {
    analogWrite (E1,a);
    digitalWrite(M1,HIGH);
    analogWrite (E2,b);
    digitalWrite(M2,HIGH);
    Serial.println("reverse");
  }
  
void left (char a,char b)
  {
    analogWrite (E1,a);
    digitalWrite(M1,HIGH);
    analogWrite (E2,b);
    digitalWrite(M2,LOW);
    Serial.println("left");
  }
  
void right (char a,char b)
  {
    for (int i = 0; i < 4; i++){
    analogWrite (E1,a);
    digitalWrite(M1,LOW);
    analogWrite (E2,b);
    digitalWrite(M2,HIGH);
    Serial.println("right");
    stop();
    }
  }
  
