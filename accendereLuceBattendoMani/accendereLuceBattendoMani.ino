/*
codice scritto da Daniel Rossi, studente di ingegneria informatica
Copyright: GNU Licence

link: https://youtube.com/c/ProjectoOfficial

*/

#define del 500
#define mic A0
#define add 10

int soglia = 65;
int cont = 0;
int azzera = 200;
bool stato = 0;


void setup() {
  pinMode(mic,INPUT);
  pinMode(add,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  Serial.println(analogRead(mic));
  if(analogRead(mic)>soglia){
    cont++;
    delay(del);
  }
  
  if(azzera == 0){
    azzera = 100;
    cont = 0;
  }

  if(cont == 2 ){
    azzera = 100;
    digitalWrite(add, !digitalRead(add));
    stato = !stato;
    cont = 0;
  }

azzera--;

}
