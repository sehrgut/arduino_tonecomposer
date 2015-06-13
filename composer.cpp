#include "tlrand.h"
#include "composer.h"
#include <stdlib.h>
#include <math.h>

#define srandom_r(seed, ctx) (*ctx = seed)

byte Composer::_rngPin = 0;

Composer::Composer() {
  srandom_r(tlrand(_rngPin), &_rand_ctx);
}

byte Composer::getRngPin() {
  return _rngPin;
}

void Composer::setRngPin(byte pin) {
  _rngPin = pin;
}
