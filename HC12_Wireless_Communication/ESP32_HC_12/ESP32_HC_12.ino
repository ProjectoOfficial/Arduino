#include <SoftwareSerial.h>

// HC-12 TX pin must be connected to ESP32 RX pin, and viceversa
SoftwareSerial HC12(16, 17); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);             // Serial port initialization to communicate with pc
  HC12.begin(9600);               // Serial port init to communicate with HC12

}

void loop() {
  while (HC12.available()) {        // If HC-12 has data
    Serial.write(HC12.read());      // print data on the Serial monitor
  }
  while (Serial.available()) {      // If Serial communication has data
    HC12.write(Serial.read());      // Send data to HC-12 wireless communication
  }
}
