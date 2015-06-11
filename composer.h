#ifndef COMPOSER_H
#define COMPOSER_H

#include <Arduino.h>

struct Note {
  int freq;
  int duration;
};

// todo: make abstract, and derive pentatonic-composer and twelvetone-composer

class Composer {
  private:
    byte _scale[6] = {30, 36, 40, 45, 54, 60};
    byte _scaleLen = 6;
    int _tonic;
    unsigned long _rand_ctx;

    static byte _rngPin;
    
  public:
    
    Composer(const int tonic);
    struct Note next();

    static byte getRngPin();
    static void setRngPin(byte pin);
};

#endif COMPOSER_H

