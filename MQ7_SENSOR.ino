#define MQ7 A1

float data = 0;
int ppm = 0;
int maxx = 0;
void setup() {
  Serial.begin(9600);
  pinMode(MQ7, INPUT);
}

void loop() {
  data = analogRead(MQ7);
  ppm = map(data, 0, 1023, 300, 2000);
  if (ppm > maxx)maxx = ppm;
  Serial.print(ppm);
  Serial.print("ppm     valore massimo:");
  Serial.print(maxx);
  Serial.println("ppm");

}
