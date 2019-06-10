#define sensor 9
#define buzzer 6

#define minFreq 466
#define maxFreq 662

void setup() {
  Serial.begin(9600);
  pinMode(sensor,INPUT);
  pinMode(buzzer,OUTPUT);
}

void alarm(){
  for(int i=minFreq;i<maxFreq;i++){
  tone(buzzer,i);
  }
  for(int i=maxFreq;i>minFreq;i--){
  tone(buzzer,i);
  }
}

void loop() {
  
  Serial.println(digitalRead(buzzer));
  if(digitalRead(sensor)==1){
    for(int i=0;i<3;i++){
    alarm();
    delay(100);
    }
  }else{
    tone(buzzer,-1000);
    digitalWrite(buzzer,LOW);
  }
}
