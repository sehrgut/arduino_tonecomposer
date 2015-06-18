#include <stdlib.h>
#include <math.h>
#include <Arduino.h>
#include "unirand.h"
#include "pinkrand.h"

#define LCG_M 2147483647
#define LCG_A 48271
#define LCG_Q ( M / A )
#define LCG_R ( M % A )

double random_double(unsigned long* ctx) {
  return (double)random_r(ctx) / (double)RANDOM_MAX;
}

void dump_state(struct pinkrand_state* ctx) {
  Serial.println(F("struct pinkrand_state"));
  
  Serial.print(F("  states = ["));
  int i;
  for(i=0; i<ctx->depth; i++) {
    Serial.print(ctx->states[i]);
    if (i < ctx->depth - 1)
      Serial.print(F(","));
  }
  Serial.println(F("]"));
  
  Serial.print(F("  depth = "));
  Serial.println(ctx->depth);
  
  Serial.print(F("  seed = "));
  Serial.println(ctx->rand_ctx);
}

// http://www.firstpr.com.au/dsp/pink-noise/#Vossx
void pinkrand_seed(unsigned long seed, byte depth, struct pinkrand_state* ctx) {

  int i;
  for(i=0; i<depth; i++)
    ctx->states[i] = random_double(&seed);
  
  ctx->depth = depth;
  ctx->rand_ctx = seed;

  dump_state(ctx);
}

double pinkrand(struct pinkrand_state* state) {
  byte depth = unirand(0, state->depth - 1, &state->rand_ctx);
  //Serial.print("Permuting pink by depth = "); Serial.println(depth);
  
  int i;

  for (i=0; i<depth; i++) {
    state->states[i] = random_double(&(state->rand_ctx));
  }

  double out = 0.0;
  for(i=0; i<state->depth; i++) {
    out += state->states[i];
  }
  
  out /= state->depth;
  
  //Serial.print("Found pink = "); Serial.println(out);
  
  //dump_state(state);
  
  return out;
  
}

double pinkrand_2(struct pinkrand_state* state) {
  static byte counter = 0;
  byte k = (counter ? __builtin_ctz (counter) : state->depth); //state must be power of two
  k = k & (state->depth - 1);
  state->states[k] = random_double(&state->rand_ctx);
  
  int i;
  double out = 0.0;
  for(i=0; i<state->depth; i++) {
    out += state->states[i];
  }
  
  out /= state->depth;

  return out;
}
