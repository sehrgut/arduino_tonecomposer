#include "tlrand.h"
#include "composer.h"
#include <stdlib.h>

#define srandom_r(seed, ctx) (*ctx = seed)

byte Composer::_rngPin = 0;

Composer::Composer(int tonic) :
  _tonic(tonic)
{
  srandom_r(tlrand(0), &_rand_ctx);
//  _rand_ctx = tlrand(_rngPin); //todo: allow passing rng-pin in
}

struct Note Composer::next() {
  int duration = 250;

  byte pos = random_r(&_rand_ctx) % _scaleLen;
  int freq = _tonic / _scale[0] * _scale[pos];
  
  duration *= (random_r(&_rand_ctx) % 4) + 1;

  return (struct Note){freq, duration};

}

byte Composer::getRngPin() {
  return _rngPin;
}

void Composer::setRngPin(byte pin) {
  _rngPin = pin;
}
