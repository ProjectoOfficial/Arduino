#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;

void setup()
{
  Serial.begin(9600);
  RTC.begin();

  Serial.println();
  Serial.print("Controllo funzionamento modulo : ");
  if (RTC.isRunning())
    Serial.println("funziona!");
  else
    Serial.println("non funziona, l'orario potrebbe essere sbagliato");
    
  Serial.print("Modalità orario: ");
  if (RTC.getHourMode() == CLOCK_H24)
    Serial.println("24 ore");
  else
    Serial.println("12 ore");
    
  Serial.print("controllo abilitazione pin out: ");
  if (RTC.isOutPinEnabled())
    Serial.println("abilitato");
  else
    Serial.println("non abilitato");

  Serial.print("controllo abillitazione SQWE : ");
  if (RTC.isSqweEnabled())
    Serial.println("abilitato");
  else
    Serial.println("non abilitato");


}

void loop()
{

  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("DOMENICA");
      break;
    case 2:
      Serial.print("LUNEDI");
      break;
    case 3:
      Serial.print("MARTEDI");
      break;
    case 4:
      Serial.print("MERCOLEDI");
      break;
    case 5:
      Serial.print("GIOVEDI");
      break;
    case 6:
      Serial.print("VENERDI");
      break;
    case 7:
      Serial.print("SABATO");
      break;
  }
  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("/");
  Serial.print(RTC.getMonth());
  Serial.print("/");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  
  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem())
    {
      case HOUR_AM :
        Serial.print(" AM");
        break;
      case HOUR_PM :
        Serial.print(" PM");
        break;
    }
  }
  Serial.println();
  delay(1000);


}
