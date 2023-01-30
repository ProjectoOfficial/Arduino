#include "DigiKeyboard.h"

void setup() {
}

void loop() {

  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(100);
  DigiKeyboard.println("1  !"); // !
  DigiKeyboard.println("2  £");
  DigiKeyboard.println("3  $"); // $
  DigiKeyboard.println("4  %"); // %
  DigiKeyboard.println("5  &"); // /
  DigiKeyboard.println("6  /"); // -
  DigiKeyboard.println("7  ("); // )
  DigiKeyboard.println("8  )"); // =
  DigiKeyboard.println("9  ?");

  DigiKeyboard.println("10  ^"); // &
  DigiKeyboard.println("11  '"); // à
  DigiKeyboard.println("12  ì"); // ga
  DigiKeyboard.println("13  é"); // g
  DigiKeyboard.println("14  è"); // g
  DigiKeyboard.println("15  +"); // ^
  DigiKeyboard.println("16  ç"); // g
  DigiKeyboard.println("17  °");
  DigiKeyboard.println("18  §");
  DigiKeyboard.println("19  ["); // è

  DigiKeyboard.println("20  ]"); // +
  DigiKeyboard.println("21  @"); // "
  DigiKeyboard.println("22  #"); // £
  DigiKeyboard.println("23  <"); // ;
  DigiKeyboard.println("24  >"); // :
  DigiKeyboard.println("25  |"); // §
  DigiKeyboard.println("26  *"); // (
  DigiKeyboard.println("27  ò"); // g
  DigiKeyboard.println("28  à"); // g
  DigiKeyboard.println("29  €"); // ca

  DigiKeyboard.println("30  -"); // '
  DigiKeyboard.println("31  _"); // ?
  DigiKeyboard.println("32  ."); // .
  DigiKeyboard.println("33  ,"); // ,
  DigiKeyboard.println("34  \\"); // ù
  DigiKeyboard.println("35  \""); // °
  DigiKeyboard.println("36  ~"); // |
  DigiKeyboard.println("37  {"); // è
  DigiKeyboard.println("38  }"); // *
  DigiKeyboard.println("39  `"); // \

  DigiKeyboard.println("41  ;"); // ò
  DigiKeyboard.println("40  :"); // ç
  DigiKeyboard.println("42  ="); // ì
  DigiKeyboard.println("43  ù"); // g
  DigiKeyboard.println("44  è"); //
  DigiKeyboard.println("45  ê"); // 4
  DigiKeyboard.println("46  ë"); // f
  DigiKeyboard.println("47  â"); // a
  DigiKeyboard.println("48  Ø"); //
  DigiKeyboard.println("49  …"); //
  DigiKeyboard.sendKeyStroke(100, MOD_SHIFT_LEFT);
  DigiKeyboard.delay(10000);
}
