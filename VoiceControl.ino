#include <SoftwareSerial.h>

#define rxPin 9
#define txPin 8
#define led 10

String messaggio;

SoftwareSerial mySerial(txPin,rxPin);


void setup() {
  Serial.begin(38400);
  mySerial.begin(38400);

  pinMode(led,OUTPUT);

  digitalWrite(led,LOW);
}


void lampeggia(){
  for(int i=0;i<10;i++)
  {
    digitalWrite(led,!digitalRead(led));
    delay(500);
  }
  return;
}


void loop() {

 int i=0;
 char ch;
 messaggio="";
  while(mySerial.available()>0){
    ch=mySerial.read();
    if(ch=='#')
    break;
    messaggio+=ch;
 }
  messaggio.toLowerCase();
  if(messaggio!="")
 Serial.println(messaggio);

 if(messaggio=="accendi la luce" && digitalRead(led)==LOW)
    digitalWrite(led,HIGH);
 if(messaggio=="spegni la luce" && digitalRead(led)==HIGH)
    digitalWrite(led,LOW);  
 if(messaggio=="lampeggia")   
    lampeggia();      
 
    
  }
