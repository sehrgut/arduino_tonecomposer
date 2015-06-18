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

// todo: this is a terrible way to get a pink in a range, but need to get out of float pink generation first
long Composer::pinkint(long boundA, long boundB, struct pinkrand_state* ctx) {
  long minval = min(boundA, boundB);
  long maxval = max(boundA, boundB);
  
  unsigned long delta = maxval - minval + 1;
  double r = pinkrand(ctx);
  return (unsigned long)(r * delta) + minval;
}

long Composer::pinkint2(long boundA, long boundB, struct pinkrand_state* ctx) {
  long minval = min(boundA, boundB);
  long maxval = max(boundA, boundB);
  
  unsigned long delta = maxval - minval + 1;
  double r = pinkrand_2(ctx);
  return lround((r * delta)) + minval;
}
