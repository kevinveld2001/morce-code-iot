#include <Arduino.h>
#include <morse/morceService.h>
#include <morse/morse.h>

void setLeds(bool state) {
  digitalWrite(LED_BUILTIN, state);
  digitalWrite(12, state);
  digitalWrite(11, state);
  digitalWrite(10, state);
}



void blinkMorse(char letter) {

  if (islower(letter)) {
      letter -= 'a';
  } else if (isupper(letter)) {
      letter -= 'A';
  } else if (isDigit(letter)) {
      letter -= 22;
  }

  uint16_t encodedMorse = morseCodeMapping[letter];
  uint16_t mask = 0b1100000000000000;
  uint16_t maskedMorse = encodedMorse & mask;
  while (maskedMorse != 0) {
    if (maskedMorse == 0b1100000000000000) {
      setLeds(true);
      delay(UNITTIME * 3);
    } else if (maskedMorse == 0b1000000000000000) {
      setLeds(true);
      delay(UNITTIME);
    }
    setLeds(false);
    encodedMorse = encodedMorse << 2;
    maskedMorse = encodedMorse & mask;
    delay(UNITTIME);
  }

  delay(UNITTIME * 2);
}


