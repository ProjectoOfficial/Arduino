
#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.h>

#define FRANCO 9
#define IR_RECEIVE_PIN 2

void setup() {
  pinMode(FRANCO, OUTPUT);
  TCCR1B = (TCCR1B & 0b11111000 | 0x02);
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN);

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}


unsigned long last = millis();
int ledStatus = 0;
int pwm = 255;

void loop() {
  if (IrReceiver.decode()) {
    if (millis() - last > 250) {

      switch (IrReceiver.decodedIRData.command) {
        case 0x43: ledStatus = !ledStatus;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          else
            analogWrite(FRANCO, 0);
          break;
        case 0x7: if (pwm > 1) {
            pwm -= 5;
            if (ledStatus)
              analogWrite(FRANCO, pwm);
          }
          break;
        case 0x15:
          if (pwm < 254) {
            pwm += 5;
            if (ledStatus)
              analogWrite(FRANCO, pwm);
          }
          break;
        case 0xC:
          pwm = 30;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x18:
          pwm = 60;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x5E:
          pwm = 90;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x8:
          pwm = 120;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x1C:
          pwm = 150;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x5A:
          pwm = 180;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x42:
          pwm = 210;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x52:
          pwm = 232;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x4a:
          pwm = 255;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
        case 0x16:
          pwm = 0;
          if (ledStatus)
            analogWrite(FRANCO, pwm);
          break;
      }

      IrReceiver.printIRResultShort(&Serial);
      Serial.println(pwm);
    }
    IrReceiver.resume();
    last = millis();
  }
}
