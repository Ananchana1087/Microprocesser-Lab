#include<string.h>
float previous_error;
float integral;
float error;
float derivative;
float setpoint=1;
float kp=0.5,ki=0.2,kd=1.5;
float speed=0,C,B,dis,fs,s;
const byte interruptPin2 = 2;
const byte interruptPin3 = 3;
int timer1_counter;
String a,buff;
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin2),S,RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3),D,RISING);
  Serial.begin(9600);
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 59286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec)
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

void loop()
{
  if(Serial.available())
  {
    a = Serial.readString();
    setpoint = a.toInt();
    Serial.print(setpoint); 
  }
 if(setpoint>0)
 {
 s=setpoint;
 FOW(speed);
 Serial.print(setpoint);
 Serial.print(",");
 Serial.println(fs);
 }
 else
 {
 s=setpoint*-1;
 BACK(speed); 
 Serial.print(setpoint);
 Serial.print(",-");
 Serial.println(fs);
 }
 error=s-fs;
 integral=integral+error; 
 derivative= error - previous_error;
 speed=(kp*error)+(ki*integral)+(kd*derivative);
 previous_error=error;
  if(speed>255)
    speed=255;
  if(speed<0)
    speed=0;
}
void FOW(int A)
{
 digitalWrite(4,HIGH);
 digitalWrite(5,LOW);
 analogWrite(6,A);
}
void BACK(int D)
{
 digitalWrite(4,LOW);
 digitalWrite(5,HIGH);
 analogWrite(6,D);
}
void D() 
{
  B = digitalRead(interruptPin2);
  C = digitalRead(interruptPin3);
  if((B==0)&&(C==1))
    dis++;
}
void S() 
{
  B = digitalRead(interruptPin2);
  C = digitalRead(interruptPin3);
  if((B==1)&&(C==0))
    dis++;
}
ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1sec
  {
    TCNT1 = timer1_counter;   // set timer
    fs = 2.0*60.0*(dis/5500.0)/0.1;  //calculate motor speed, unit is rpm
    dis=0;
  }
