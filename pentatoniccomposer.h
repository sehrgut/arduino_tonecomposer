#ifndef PENTATONICCOMPOSER_H
#define PENTATONICCOMPOSER_H

#include <Arduino.h>
#include "composer.h"

enum PentatonicScales {
  MINOR,
  MAJOR,
  EGYPTIAN,
  BLUES_MAJOR,
  BLUES_MINOR,
  PYTHAGOREAN_MINOR
};

enum PentatonicNoises {
  WHITENOISE,
  PINKNOISE,
  PINKNOISE_2
};

class PentatonicComposer: public Composer {
  private:
    byte _scale[6][6] = {
      {30, 36, 40, 45, 54, 60},
      {24, 27, 30, 36, 40, 48},
      {24, 27, 32, 36, 42, 48},
      {15, 18, 20, 24, 27, 30},
      {24, 27, 32, 36, 40, 48},
      {54, 64, 72, 81, 96, 108}
      };
    byte _scaleLen = 6;
    int _tonic;
    enum PentatonicScales _whichScale;
    enum PentatonicNoises _whichNoise;

    struct pinkrand_state _pitch_pink;
    struct pinkrand_state _duration_pink;

    byte nextPitch();
    int nextDuration();

  public:
    PentatonicComposer(const int tonic, const enum PentatonicScales whichScale, const enum PentatonicNoises whichNoise);
    struct Note next();
};

#endif

