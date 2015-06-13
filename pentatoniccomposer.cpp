#include "pentatoniccomposer.h"

PentatonicComposer::PentatonicComposer(int tonic, enum PentatonicScales whichScale) :
  _tonic(tonic),
  _whichScale(whichScale)
{
  ;
}

struct Note PentatonicComposer::next() {
  int duration = 250;

  byte pos = random_r(&_rand_ctx) % _scaleLen;
  int freq = round((float)_tonic / (float)_scale[_whichScale][0] * (float)_scale[_whichScale][pos]);
  
  duration *= (random_r(&_rand_ctx) % 4) + 1;

  return (struct Note){freq, duration};

}

