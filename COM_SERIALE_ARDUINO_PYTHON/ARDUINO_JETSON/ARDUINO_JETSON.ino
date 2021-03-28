/*
   DANIEL ROSSI 2021 © GPLK V3
   ENGINEERING DEPARTMENT - UNIVERSITY OF MODENA AND REGGIO EMILIA
   REV-21 ECU FIRMWARE
*/

#include <SPI.h>
#include <mcp2515.h>
#include <MFRC522.h>

/************************* RFID INIT ***********************/
#define RFID_CS 3
#define RFID_RST 4

#define USERS 3
#define AUTHDELAY 200
MFRC522 RFID(RFID_CS, RFID_RST);

String users[USERS] = {"2651253128", "677822862", "519619362"};
bool auth[USERS] = {false, false, false};

bool isAuthenticated = false;


/************************* MCP2515 INIT ***********************/
#define MCP_CS 10

#define CANDELAY 10
struct can_frame canMsg;
MCP2515 mcp2515(MCP_CS);


/************************* USB COMUNICATION INIT ***********************/
#define USBDELAY 50
bool receive = 0;

typedef struct packet {
  uint8_t bat_temp;
  uint8_t bat_volt;
  uint8_t throttle;
};


/************************* VOID SETUP ***********************/
void setup()
{
  SPI.begin();
  Serial.begin(9600);
pinMode(12, OUTPUT);
  RFID.PCD_Init();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}


/************************* SEND DATA BY CAN BUS ***********************/
void CANTransmit() {
  canMsg.can_id  = 0x036;
  canMsg.can_dlc = 8;
  canMsg.data[0] = isAuthenticated;
  canMsg.data[1] = random(0, 50);
  canMsg.data[2] = random(50, 100);
  canMsg.data[3] = random(100, 150);
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);
  delay(CANDELAY);
}


/************************* GET RFID CARD UID ***********************/
String getUID() {
  if (!RFID.PICC_IsNewCardPresent())
    return "";
  if (!RFID.PICC_ReadCardSerial())
    return "";

  String UID = "";

  for (int i = 0; i < RFID.uid.size; i++) {
    byte b = RFID.uid.uidByte[i];
    UID += (String)b;
  }
  return UID;
}


/************************* CARD UID AUTH ***********************/
void authenticate(String UID) {
  for (int i = 0; i < USERS; i++) {
    if (UID == users[i] & auth[i] == false) {
      auth[i] = true;
      isAuthenticated = true;
      return;
    }
  }
  delay(AUTHDELAY);
}


/************************* CARD UID DEAUTH ***********************/
void deauthenticate(String UID) {
  for (int i = 0; i < USERS; i++) {
    if (UID == users[i] & auth[i] == true) {
      auth[i] = false;
      isAuthenticated = false;
      return;
    }
  }
  delay(AUTHDELAY);
}


/************************* SEND DATA TO JETSON ***********************/
int USBTransmit(int v1, int v2, int v3) {
  if (!Serial.availableForWrite())
    return 0;
  packet pack;
  pack.bat_temp = v1;
  pack.bat_volt = v2;
  pack.throttle = v3;
  size_t x = Serial.write((byte*) &pack, sizeof(pack));
  Serial.flush();

  if (x == sizeof(pack)) return 1;
  else return 0;
}


/************************* RECEIVE DATA FROM JETSON ***********************/
int USBReceive() {
  Serial.flush();
  if (!Serial.available())
    return 0;
  size_t bytes = 3;
  byte buff[bytes];
  int x = Serial.readBytes(buff, bytes);
  if (x != bytes) return 0;
  return 1;
}

//ISCRIVITI :)

/************************* VOID LOOP ***********************/
void loop()
{
  if (!receive) {
    if (USBTransmit(random(50, 60), random(40, 48), random(20, 100)))
      receive = 1;
    digitalWrite(12,HIGH);
    delay(USBDELAY);
  } else
  {
    if (USBReceive())
      receive = 0;
    digitalWrite(12,LOW);
    delay(USBDELAY);
  }


  /*CANTransmit();
    String UID = getUID();
    if (!isAuthenticated)
    authenticate(UID);
    else
    deauthenticate(UID);
  */
}
