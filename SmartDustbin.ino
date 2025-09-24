



#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

unsigned char AT[]="AT";
unsigned char CMGS1[]="AT+CMGS=\"";
unsigned char CMGS3[]="\"";
unsigned char CMGF[]="AT+CMGF=1";
unsigned char Delete[]="AT+CMGD=1,4";
unsigned char EcoOFF[]="ATE0";
unsigned char MSG[]="Alert !\nDustbin full.";
unsigned char PB[]="AT+CPBF=\"SGPROJECTS\"";
unsigned char RST[]="AT+CFUN=1,1";

int i,state,key;
char SenderNumber[20];  // Sender Number of maximum 20 digit capacity
const int Signal_Pin = 8; 
int Signal_State = 0, counter=0;
int dustbin_LED = 12;    // This LED indicates the dustbin is full (optional)
int detection_LED = 13;    // This LED indicates the Signal and busy status (optional)
long time;

void setup()  
{
  pinMode(dustbin_LED,OUTPUT),pinMode(detection_LED,OUTPUT),pinMode(Signal_Pin, INPUT);
  digitalWrite(dustbin_LED, LOW),digitalWrite(detection_LED, HIGH);
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("GSM Based Smart Dustbin");
  Send(EcoOFF);Send(CMGF);
  state=0,key=0,i=0,time=millis();
  Repeat : Signal_State = digitalRead(Signal_Pin);  
  if(Signal_State==LOW || TimeDelay()<=60)goto Repeat;
  digitalWrite(detection_LED, LOW);
}

void loop() // run over and over
{
  if (digitalRead(Signal_Pin) == LOW){
    digitalWrite(dustbin_LED, HIGH);
    delay(250);
    counter++;
    if(counter>=20)counter=0,Signal_State=1;     
  }

  else {
    digitalWrite(dustbin_LED, LOW);
    delay(250);
    counter--;
    if(counter<=0)counter=0,Signal_State=0;    
   }
  
  if (Signal_State && !key)key=1,digitalWrite(detection_LED, HIGH),delay(1500),digitalWrite(detection_LED, LOW),time=millis(),Send(PB);
  else if (mySerial.available()){
    char CH = mySerial.read();
    Serial.print("*");Serial.print(CH);Serial.println("*");Serial.println();
    switch(state){
    case 0 :  if(CH==' ')state=1;
              break;  
    case 1 :  if(CH==',')state=11;
              break;          
    case 11 : if(CH=='"')i=0,state=12;       // If '"' detected, start searching the Sender Number
              else state=0;
              break; 
    case 12 : if(i<=12)SenderNumber[i]=CH,i++;  // Holding 13(0-12)digit Sender Number
              else if(CH=='"')state=0,TakeAction();
              break;
    default : state=0;
              break;
    }
  }
  else if(TimeDelay()>=60 && key==1)Serial.println(TimeDelay()),time=millis(),key=0,state=0,digitalWrite(detection_LED, LOW);    // Wait for new input
  else if(TimeDelay()>=300 && key==0)Serial.println(TimeDelay()),ResetModem(),time=millis();
}    


void SMS()
{
 TXD(CMGS1);mySerial.print(SenderNumber);Send(CMGS3);Send(MSG);
 mySerial.write(0x1a); 
}

void Send(unsigned char *cmd)
{
  while(*cmd){
    mySerial.write(*cmd++);
    delay(250);
  }
  mySerial.write("\r");delay(250);
}

void TXD(unsigned char *cmd)
{
  while(*cmd){
    mySerial.write(*cmd++);
    delay(250);
  }
}

int TimeDelay(){
 long t=millis()-time;
 t=t/1000;
 return t;
}

void ResetModem()
{
  Send(RST);
  delay(20000);
  Send(EcoOFF);Send(CMGF);
  state=0,key=0,i=0;
}

void TakeAction()
{
  digitalWrite(detection_LED, HIGH);
  SMS();
 }
