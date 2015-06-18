#include <Arduino.h>
#include <stdlib.h>
#include "unirand.h"

long unirand(long boundA, long boundB, unsigned long* random_r_ctx) {
  long minval = min(boundA, boundB);
  long maxval = max(boundA, boundB);
  
  unsigned long delta = maxval - minval + 1;
  unsigned long rand_ceil = RANDOM_MAX - (RANDOM_MAX % delta);
  
  int i = 0;
  unsigned long r;
  do {
    r = random_r(random_r_ctx);
    i++;
  } while (r >= rand_ceil);
  
  return (r % delta) + minval;
}

