//© GNU License - Daniel Rossi 2020
//https://youtube.com/c/ProjectoOfficial?sub_confirmation=1
#include <Servo.h>
#define servoPin 9
#define delay_ms 10
Servo myservo;

void setup() {
  myservo.attach(servoPin);

}

void loop() {
  for (int i = 0; i < 180; i++) {
    myservo.write(i);
    delay(delay_ms);
  }

  for (int i = 179; i >= 0; i--) {
    myservo.write(i);
    delay(delay_ms);
  }

}
