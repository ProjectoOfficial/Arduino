#define LED_PIN_0 13 // il pin 13 ha un led incorporato sul PCB di arduino
#define LED_PIN_1 3
#define LED_PIN_2 4


void setup() {
  // Il codice inserito qui dentro verrà eseguito per primo quando Arduino si accende, e verrà eseguito una sola volta
  Serial.begin(9600); //Inizializza il protocollo che permette di scrivere testo o numeri sul serial monitor
  pinMode(LED_PIN_0, OUTPUT); // Definisce che il pin a cui fa riferimento LED_PIN diventa un ouput, il microcontrollore sa che lo utilizzeremo per inviare segnali o dati
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  // START: Il codice inserito tra queste parentesi graffe, invece, verrà eseguito all'infinito, finché arduino è acceso.

  /* QUESTO CODICE NON SERVE PIU'
    digitalWrite(LED_PIN, HIGH); // digitalWrite è una funzione che ci permette di impostare lo stato del pin | la funzione prende come parametro: il pin da modificare, lo stato da impostare (HIGH = acceso, LOW = spento)
    delay(500); // il delay mette in pausa arduino dal continuare dopo questa riga di codice, in questo caso lo fa aspettare qua per 500ms, per poi continuare fino in fondo
    digitalWrite(LED_PIN, LOW);
    delay(500);
  */

  if (Serial.available()) { // controlliamo se arrivano dati dal cavo che collega arduino al PC
    char c = Serial.read(); // Se ci sono dati, allora li leggiamo
    if (c == '0') {
      digitalWrite(LED_PIN_0, HIGH);
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, LOW);
    }
    else if (c == '1') {
      digitalWrite(LED_PIN_0, LOW);
      digitalWrite(LED_PIN_1, HIGH);
      digitalWrite(LED_PIN_2, LOW);
    }
    else if (c == '2') {
      digitalWrite(LED_PIN_0, LOW);
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, HIGH);
    }
    else {
      digitalWrite(LED_PIN_0, LOW);
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, LOW);
    }
    Serial.println(c);
  }
  // quando l'esecuzione arriva qui in fondo, riparte dall'inizio --> START
}
