#ifndef COMPOSER_H
#define COMPOSER_H

#include <Arduino.h>
#include "pinkrand.h"

struct Note {
  int freq;
  int duration;
};

// todo: namespace
// todo: 12-bar and twelvetone-composers

class Composer {
  protected:
    unsigned long _rand_ctx;
    
    static byte _rngPin;
    static long pinkint(long boundA, long boundB, struct pinkrand_state* ctx);
    static long pinkint2(long boundA, long boundB, struct pinkrand_state* ctx);
    
  public:
    Composer();
    virtual struct Note next() = 0;

    static byte getRngPin();
    static void setRngPin(byte pin);
    
};

#endif COMPOSER_H

