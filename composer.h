#ifndef COMPOSER_H
#define COMPOSER_H

#include <Arduino.h>

struct Note {
  int freq;
  int duration;
};

class Composer {
  private:
    const byte* _scale;
    const byte _scaleLen;
    const int _tonic;
    
  public:
    Composer(const byte* scale, const byte scaleLen, const int tonic);
    struct Note next();
};

#endif COMPOSER_H
