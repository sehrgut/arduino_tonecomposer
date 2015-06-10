#include "composer.h"

Composer::Composer(const byte* scale, byte scaleLen, int tonic) :
  _scale(scale), _scaleLen(scaleLen), _tonic(tonic)
{
}

struct Note Composer::next() {
  int duration = 250;

  byte pos = random(0, _scaleLen);
  int freq = _tonic / _scale[0] * _scale[pos];
  
  duration *= random(1,4);

  return (struct Note){freq, duration};

}

