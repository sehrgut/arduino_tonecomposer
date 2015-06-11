#include "tlrand.h"

uint32_t tlrand(int pin) {
  uint32_t out = 0;
  byte bits = 32;
  while(bits) {
    int a = analogRead(pin);
    int b = analogRead(pin);

    boolean aa = (a&1^(a>>1)&1);
    boolean bb = (b&1^(b>>1)&1);
    if (aa ^ bb) {
      --bits;
      out |= ((uint32_t)aa) << bits;
    }
    
  }
  return out;
}

