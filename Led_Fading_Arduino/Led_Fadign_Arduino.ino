const int Red = 11;
const int Green = 10;
const int Blue = 9;

int RedVal = 0;
int GreenVal = 0;
int BlueVal = 0;
int fade = 10;

int RedVal1 = 186;
int GreenVal1 = 0;
int BlueVal1 = 255;

int RedVal2 = 9;
int GreenVal2 = 239;
int BlueVal2 = 26;

int RedVal3 = 255;
int GreenVal3 = 120;
int BlueVal3 = 0;

int RedVal4 = 0;
int GreenVal4 = 255;
int BlueVal4 = 78;

int mode = 1;

void setup()
{

  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  analogWrite(Red, RedVal);
  analogWrite(Green, GreenVal);
  analogWrite(Blue, BlueVal);

}

int Fade(int val, int nextval) {
  if (val < nextval) {
    val ++;
  } else if (val > nextval) {
    val --;
  }
  return val;
}

void loop()

{
  while (mode == 1) {
    RedVal = Fade(RedVal, RedVal1);
    BlueVal = Fade(BlueVal, BlueVal1);
    GreenVal = Fade(GreenVal, GreenVal1);

    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);

    if (RedVal == RedVal1 && GreenVal == GreenVal1 && BlueVal == BlueVal1) {
      delay(1500);
      mode = 2;
    }
  }

  while (mode == 2) {
    RedVal = Fade(RedVal, RedVal2);
    BlueVal = Fade(BlueVal, BlueVal2);
    GreenVal = Fade(GreenVal, GreenVal2);

    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);

    if (RedVal == RedVal2 && GreenVal == GreenVal2 && BlueVal == BlueVal2) {
      delay(1500);
      mode = 3;

    }
  }

  while (mode == 3) {
    RedVal = Fade(RedVal, RedVal3);
    BlueVal = Fade(BlueVal, BlueVal3);
    GreenVal = Fade(GreenVal, GreenVal3);
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);

    if (RedVal == RedVal3 && GreenVal == GreenVal3 && BlueVal == BlueVal3) {
      delay(1500);
      mode = 4;

    }
  }

  while (mode == 4) {
    RedVal = Fade(RedVal, RedVal4);
    BlueVal = Fade(BlueVal, BlueVal4);
    GreenVal = Fade(GreenVal, GreenVal4);
    analogWrite(Red, RedVal);
    analogWrite(Green, GreenVal);
    analogWrite(Blue, BlueVal);
    delay(fade);

    if (RedVal == RedVal4 && GreenVal == GreenVal4 && BlueVal == BlueVal4) {
      delay(1500);
      mode = 1;

    }
  }

}
