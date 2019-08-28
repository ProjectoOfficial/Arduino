#include <SD.h>
#include <SPI.h>
#define CS 10

File testFile;
void setup() {
  Serial.begin(9600);
  pinMode(CS,OUTPUT);

  if(SD.begin()){
    Serial.println("Scheda SD pronta!");
    }else
    {
    Serial.println("Errore inizializzazione SD");
    return;
      }

  testFile = SD.open("test.txt",FILE_WRITE);

  if(testFile){
    Serial.println("Scrivo nel file...");
    testFile.println("zdfghadthsrtjhsghns");
    Serial.println("Fatto!");
    }else
      Serial.println("Errore di apertura del file");
      
   testFile.close();
   Serial.println("Lettura del file");
   
   testFile = SD.open("test.txt",FILE_READ);
   if(testFile){
        Serial.println("Sto leggendo...");
      while(testFile.available())
        Serial.print((char)testFile.read());
      Serial.println("");
    }else
      Serial.println("Errore di apertura del file");

     testFile.close();

     SD.remove("test.txt");
     if(!SD.exists("test.txt"))
     Serial.println("File rimosso");
     else
     Serial.println("Errore di cancellazione del file");
}

void loop() {
 //void loop vuoto perche eseguo il codice solo una volta nel void setup
}
