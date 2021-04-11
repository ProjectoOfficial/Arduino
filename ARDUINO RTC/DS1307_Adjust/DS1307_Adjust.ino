#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;

#define __tempo__ 11,46,00
#define __data__ 11,04,21

/*domenica=1; lunedi=2, martedi=2, mercoledi=4, giovedi=5, venerdi=6, sabato=7*/
#define __giornosettimana__ 1

void setup()
{
  Serial.begin(9600);
  RTC.begin();

  Serial.println("imposto il tempo");
  //RTC.setHourMode(CLOCK_H12);
  RTC.setHourMode(CLOCK_H24);
  RTC.setWeek(__giornosettimana__);
  RTC.setDate(__data__);
  RTC.setTime(__tempo__);
  Serial.println("Nuovo tempo impostato");
  RTC.startClock();

}

void loop()
{
  Serial.println();
  Serial.println("Verifica del tempo:");
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
  Serial.print("");

  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem()) {
      case HOUR_AM:
        Serial.print(" AM");
        break;
      case HOUR_PM:
        Serial.print(" PM");
        break;
    }
  }
  Serial.println("");
  delay(1000);

}
