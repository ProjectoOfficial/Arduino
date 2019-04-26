#include <SevSeg.h>
SevSeg sevseg;
#define pot A0
int B = 2;
int tre = 3;
int due = 4;
int F = 5;
int A = 6;
int uno = 7;
int quattro = 8;
int G = 9;
int C = 10;
int punto = 11;
int D = 12;
int E = 13;
void setup() {
byte numDigits = 4;
byte digitPins[] = {uno, due, tre, quattro};
byte segmentPins[] = {A, B, C, D, E, F, G, punto};
bool resistorOnSegments = false;
byte hardwareConfig = COMMON_CATHODE;
bool updateWithDelays = false;
bool leadingZeros = false;
sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins,
resistorOnSegments, updateWithDelays, leadingZeros);
sevseg.setBrightness(90);
Serial.begin(9600);
}
void loop() {
int val = analogRead(pot);
int scale = map(val, 0, 1023, 0, 5000);
sevseg.setNumber(scale, 3);
sevseg.refreshDisplay();
Serial.println(scale);
}
