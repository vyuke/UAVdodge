// uav.ino

#include<Servo.h>;
#define AIL1  5   //AIL fuyi
#define ELE2  6   //ELE shengjiang
#define LED   13
unsigned long INAIL;
unsigned long INELE;

int OUTAIL;
int OUTELE;

int delta = 0;

Servo AIL;
Servo ELE;

const int TrigPin = 2; 
const int EchoPin = 3; 
float distance; 

void setup()
{        
  pinMode(AIL1,0);
  pinMode(ELE2,0);
  pinMode(LED,1);

  AIL.attach(9);
  ELE.attach(10);

  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
} 

void loop()
{

  sr();

  if(distance<=130)
  {
    
    delta = 130 - distance;
    delta = delta/4;
  }

  INAIL = pulseIn(AIL1, 1);
  INELE = pulseIn(ELE2, 1);

  OUTAIL = map(INAIL,1000,2000,47,144);
  OUTELE = map(INELE,1000,2000,47,144);
  
  OUTELE = OUTELE - delta;

  AIL.write(OUTAIL);
  ELE.write(OUTELE);


  Serial.print("AIL=");
  Serial.print(INAIL);
  Serial.print(" ELE=");
  Serial.print(INELE);
  Serial.print("   ");
  
   Serial.print("outail= ");
  Serial.print(OUTAIL);
  Serial.print(" outele= ");
  Serial.print(OUTELE);
  Serial.print("   ");
  
  Serial.print("delta= ");
  Serial.print(delta);
  Serial.print("   ");

  digitalWrite(LED,0);
  delay(5);

}

void sr() 
{ 
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(LED,1); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW); 
  digitalWrite(LED,0);
  distance = pulseIn(EchoPin, HIGH , 8000) / 58.00;
  if(distance>=130 || distance==0)
  { 
    distance=130;
  }
  
  Serial.print(distance); 
  Serial.print("cm"); 
  Serial.println(); 
  delay(50); 
 
}


