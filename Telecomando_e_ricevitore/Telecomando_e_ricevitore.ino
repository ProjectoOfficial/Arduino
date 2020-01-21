#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 3;
int BUTTON_PIN = 7;
int STATUS_PIN = 13;
int r = 4;
int g = 5;
int b = 6;

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(STATUS_PIN, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}
// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw

unsigned int rawCodes[RAWBUF]; // The durations if raw
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state
// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results) {
  codeType = results->decode_type;
  int count = results->rawlen;
  if (codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
  }
  else {
    if (codeType == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    }
    else if (codeType == SONY) {
      Serial.print("Received SONY: ");
    }
    else if (codeType == RC5) {
      Serial.print("Received RC5: ");
    }
    else if (codeType == RC6) {
      Serial.print("Received RC6: ");
    }
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;
  }
}

int lastButtonState;

void loop() {

  if (irrecv.decode(&results)) {
    digitalWrite(STATUS_PIN, HIGH);
    storeCode(&results);
    //Serial.println(results->value,HEX);
    if (codeValue == 16724175) {
      digitalWrite(r, LOW);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      Serial.println("spento");
    }
    if (codeValue == 16718055) {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
    }
    if (codeValue == 16743045) {
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
    }
    if (codeValue == 16716015) {
      digitalWrite(r, LOW);
      digitalWrite(g, LOW);
      digitalWrite(b, HIGH);
    }
    if (codeValue == 16726215) {
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, HIGH);
    }
    if (codeValue == 16734885) {
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
    }
    if (codeValue == 16728765) {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, HIGH);
    }
    if (codeValue == 16730805) {
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, HIGH);
    }
    irrecv.resume(); // resume receiver
    digitalWrite(STATUS_PIN, LOW);
  }
}
