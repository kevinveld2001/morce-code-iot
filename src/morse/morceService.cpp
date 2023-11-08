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

  if (letter == ' ' || letter == '\n') {
    delay(UNITTIME * 7);
    Serial.print(" / ");
    return;
  }

  if (islower(letter)) {
      letter -= 'a';
  } else if (isupper(letter)) {
      letter -= 'A';
  } else if (isDigit(letter)) {
      letter -= 22;
  }

  uint16_t encodedMorse = morseCodeMapping[(int)letter];
  #define DECODE_MASK 0b1100000000000000;
  uint16_t maskedMorse = encodedMorse & DECODE_MASK;

  while (maskedMorse != 0) {
    setLeds(true);
    if (maskedMorse == 0b1100000000000000) {
      delay(UNITTIME * 3);
      Serial.print("-");
    } else if (maskedMorse == 0b1000000000000000) {
      delay(UNITTIME);
      Serial.print(".");
    }
    setLeds(false);
    encodedMorse = encodedMorse << 2;
    maskedMorse = encodedMorse & DECODE_MASK;
    delay(UNITTIME);
  }
  Serial.print(" "); 
  delay(UNITTIME * 3);
}


