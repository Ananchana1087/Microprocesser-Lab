#include<SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
int kp=10,ki=20,kd=55;
int speed=100,C,B,dis=1089;
int G,F,H,J;
const byte interruptPin2 = 2;
const byte interruptPin3 = 3;
int num[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,
           0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
void setup()
{ pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
 FOW(speed);
 //BACK(speed);
 B = digitalRead(interruptPin2);
 C = digitalRead(interruptPin3);
   G=dis/1000;
   F=(dis%1000)/100;
   shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[F]); 
   shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[G]); 
   digitalWrite(15,HIGH);
   digitalWrite(A2,HIGH);
  Serial.println(dis);
}
void FOW(int A)
{
 digitalWrite(4,HIGH);
 digitalWrite(5,LOW);
 analogWrite(6,A);
 if((B==0)&&(C==1))
 dis++;
}
void BACK(int A)
{
 digitalWrite(4,LOW);
 digitalWrite(5,HIGH);
 analogWrite(6,A);
 if((B==0)&&(C==1))
 dis--;
}
