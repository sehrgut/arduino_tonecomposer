#include <math.h>
#include "pentatoniccomposer.h"
#include "tlrand.h"

PentatonicComposer::PentatonicComposer(int tonic, enum PentatonicScales whichScale, enum PentatonicNoises whichNoise) :
  _tonic(tonic),
  _whichScale(whichScale),
  _whichNoise(whichNoise)
{
  pinkrand_seed(tlrand(_rngPin), 4, &_pitch_pink);
  pinkrand_seed(tlrand(_rngPin), 4, &_duration_pink);
}

byte PentatonicComposer::nextPitch() {
  byte pos;
  
  switch(_whichNoise) {
    case WHITENOISE:
      pos = unirand(0, _scaleLen - 1);
      break;
    case PINKNOISE:
      pos = pinkint(0, _scaleLen - 1, &_pitch_pink);
      break;
  }
  
  return pos;
}

int PentatonicComposer::nextDuration() {
  int duration = 250;
  
  switch(_whichNoise) {
    case WHITENOISE:
      duration *= unirand(1, 4);
      break;
    case PINKNOISE:
      duration *= pinkint(1, 4, &_duration_pink);
      break;
  }
  
  return duration;
}

struct Note PentatonicComposer::next() {
  int duration = 250;

  byte pos = nextPitch();//pinkint(0, _scaleLen - 1, &_pitch_pink);
  int freq = round((float)_tonic / (float)_scale[_whichScale][0] * (float)_scale[_whichScale][pos]);
  
  duration = nextDuration();//*= pinkint(1, 4, &_duration_pink);

  return (struct Note){freq, duration};

}

