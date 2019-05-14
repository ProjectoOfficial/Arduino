#include <math.h>
#define intervallo 20
#define samples 22
#define sensore A5

#define affidabilita 50

long contatore = 0; 
double BPM =0; 
double BPM_calibrata = 0; 

double start_time = 0; 
double end_time = 0;



void setup() {
  Serial.begin(9600);
}

int differenza_campioni(){
  float primo_campione = read_sample();
  delay (intervallo);
  float secondo_campione = read_sample();
  float differenza = secondo_campione - primo_campione; 
  return differenza;
}

float read_sample(){
  float somma=0;
  for(int i=0;i<samples;i++)
    somma+=analogRead(sensore);

  return somma/samples;
}


void loop() {

  float differenza= differenza_campioni();
  if (differenza>0) // f(x+1)>f(x) ==> funzione crescente 
  {
    while (differenza>0)
    {
    differenza= differenza_campioni();
    } 
    contatore++; 
    if (contatore == 1) 
    {
    start_time = millis(); 
    }
  }
  else // f(x+1)<f(x) ==> abbiamo raggiunto un picco di massimo/minimo - funzione decrescente
  {
    while (differenza<=0)
    {
    differenza= differenza_campioni();
    } 
    
    contatore++; 
    if (contatore == 1)
    {
    start_time = millis(); // time at the time of first pick
    }
  }

  
  if (contatore==affidabilita) 
  {
    end_time = millis(); 
    BPM = ((contatore*30000))/((end_time-start_time)) ; 
    BPM_calibrata=BPM*0.19-12.56;
    if(BPM_calibrata<120 && BPM_calibrata >55){
    Serial.print("picchi: ");
    Serial.print(contatore/2);
    Serial.print("; tempo: ");
    Serial.print(end_time-start_time);
    Serial.print ("; BPM: ");  
    Serial.println(BPM_calibrata);
    delay (10); 
    }
    else{
    Serial.println("sensore disconnesso");
    }
    contatore  = 0; 
    
  }
  }
