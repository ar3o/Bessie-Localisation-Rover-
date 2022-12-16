int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control
int trigPin = 3;
int echoPin = 4;
long duration, x, maxValue, distance;
const byte maxlights = 150;
int lights[maxlights ];
int LDRPin = A5;
bool right_or_left ; //right = true

int c = 0;
byte maxIndex = 0;
int ldrprinter = analogRead(A5);

void setup(void) {
  pinMode(LDRPin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  delay(3000);
  for (int i = 0; i <150; i++){
    lights[i] = 0;
}
  int i;
  for(i=5;i<=8;i++)
  pinMode(i, OUTPUT);
  Serial.begin(9600);
  Serial.println("setup");

}

void loop() {

for(int i=0; i<150; i++){
  for(c=1;c<=2;c++){ 
      turn_right();}
      lights[i] = analogRead(LDRPin);
      Serial.println(lights[i]);
  }


 byte lights_list_size = sizeof(lights) / sizeof(lights[0]);    // how many values are in the list
  int peak = -999999;    // starting condition for max voltage (very small value)
  for (int index=0; index <  lights_list_size ; index++)   // for each value in the list
  {
    if (lights[index] > peak)    // if current value is greater than the max value
      {
        peak = lights[index];    // save new max value
      }
  }
  Serial.print(peak);    // print the max value for light voltage
  maxValue = peak;    //  max value is the peak

while ((analogRead(LDRPin)) < ((maxValue)-80)){
  for(int c=1;c<=2;c++){ 
        turn_left();

        Serial.println("searching");
        Serial.println("current is " + String(analogRead(A5)));
        Serial.println("max is " + String(maxValue));

  }
}      

stop();

delay(1000);
checkdist();
right_or_left = false;
  
while(distance >10){
checkdist();

  x = analogRead(LDRPin);
  while (x < maxValue-80) {
    if (right_or_left == true){
      right_or_left = false;
      Serial.println("SWITCH LEFT");
      } else {
      right_or_left = true;
      Serial.println("SWITCH RIGHT");
      }
   
    
    while ((right_or_left == true) and (x < maxValue-80)) {

          

          x = analogRead(LDRPin);
          Serial.println("right");

          Serial.println("current is " + String(analogRead(A5)));
          Serial.println("max is " + String(maxValue));
          checkdist();
          if((distance)<10){ 
            stop();
            Serial.println("end");
            delay(2000);
            exit(1);
          }
          Serial.println("search again");
          turn_right();
          
    }
    while ((right_or_left == false ) and (x < maxValue-80)) {

          

          x = analogRead(LDRPin);
          Serial.println("left");
 
          Serial.println("current is " + String(analogRead(A5)));
          Serial.println("max is " + String(maxValue));
          checkdist();
          if((distance)<10){ 
            stop();
            Serial.println("end");
            delay(2000);
            exit(1);
          }
          Serial.println("search again");
          turn_left();
          
    }
          
        }   
  for(c=1;c<=3;c++){ 
  forward();
  delay(100);
    if((distance)<10){ 
        stop();
        Serial.println("end");
        delay(2000);
        exit(1);
    }
  }
  Serial.println("forward");
  checkdist();  
   }
        


stop();
  

delay(20000);

}




void checkdist() {
  
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034 / 2;
    Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void stop(void)          //Stop subroutine
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
  Serial.println("stop");
}



void forward (void)     //forward subroutine
{
  analogWrite (E1,127);   //Motor 1 half speed (value of 127 = half speed)
  digitalWrite(M1,LOW);  //Motor 1 direction control
  analogWrite (E2,121);   //Motor 2 half speed (value of 127 = half speed)
  digitalWrite(M2,LOW);   //Motor 2 direction control
  delay(50);
  
}

void turn_left (void)     //turn_left subroutine
{
  analogWrite (E1,127);   //Motor 1 half speed (value of 127 = half speed)
  digitalWrite(M1,HIGH);  //Motor 1 direction control
  analogWrite (E2,127);   //Motor 2 half speed (value of 127 = half speed)
  digitalWrite(M2,LOW);   //Motor 2 direction control
  delay(20);
}


void turn_right (void){    //turn_right subroutine

  analogWrite (E1,127);   //Motor 1 half speed (value of 127 = half speed)
  digitalWrite(M1,LOW);   //Motor 1 direction control
  analogWrite (E2,127);   //Motor 2 half speed (value of 127 = half speed)
  digitalWrite(M2,HIGH);  //Motor 2 direction control;
  delay(20);
}
