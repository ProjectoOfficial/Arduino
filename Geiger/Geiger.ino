/*
CC Daniel Rossi 21-02-2020

e-mail: miniprojectsofficial@gmail.com

References: https://youtube.com/c/ProjectoOfficial

il fattore di conversione è stato prelevato da questo forum: https://radioactivity.forumcommunity.net/?t=57429596

Lo smoke detector acquistato per testare il circuito ha una dose equivalente di 0.8uS in media

L'unita di misura in Output da arduino è in uS

*/

#define CONV_FACTOR 0.00812
#define SAMPLE_TIME 3000

#define in A0
#define light 7
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 disp = Adafruit_PCD8544(5,4,3);
int contrast=60;
boolean backlight = true;

unsigned long start = 0;
int cont = 0;

void setup() {
  
  Serial.begin(115200);
  pinMode(in, INPUT);
  pinMode(light,OUTPUT);

  if(backlight==true)
    digitalWrite(light,HIGH);
    else
    digitalWrite(light,LOW);

  disp.begin();
  disp.setContrast(contrast);
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(BLACK,WHITE);
  disp.setCursor(0,0);
  disp.print("RADIATION");
  disp.setCursor(0,15);
  disp.print("DETECTOR");
  disp.display();
  delay(1000);

  disp.clearDisplay();
  disp.setCursor(5,0);
  disp.print("MEASURE");
  disp.drawFastHLine(0,15,83,BLACK);
  disp.setCursor(0,30);
  disp.setTextSize(2);
  disp.print("0 us");
  disp.display();
 
  
  start=millis();
}

void updateDisplay(float sievert){
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setCursor(5,0);
  disp.print("MEASURE");
  disp.drawFastHLine(0,15,83,BLACK);
  disp.setCursor(0,30);
  disp.setTextSize(2);
  
  String s = String(sievert)+"uS";
  disp.print(s);
  disp.display();
  }

void loop() {
  int data = map(analogRead(in), 0, 1023, 0, 1000);
  
  if (data < 834)
    cont++;

  if (millis() - start > SAMPLE_TIME ){
    float sievert = cont*CONV_FACTOR;
    updateDisplay(sievert);
    start = millis();
    cont = 0;
  }




}
