#include "blink.h"

void blink(byte pin, unsigned int n, unsigned int interval) {
  while(n--) {
    digitalWrite(pin, HIGH);
    delay(interval);
    digitalWrite(pin, LOW);
    delay(interval);
  }
}


