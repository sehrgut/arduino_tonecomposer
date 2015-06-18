#ifndef PINKRAND_H
#define PINKRAND_H

#define PINK_MAXDEPTH 16

struct pinkrand_state {
  double states[PINK_MAXDEPTH];
  byte depth;
  unsigned long rand_ctx;
};

void pinkrand_seed(unsigned long seed, byte depth, struct pinkrand_state* ctx);
double pinkrand(struct pinkrand_state* state);
double pinkrand_2(struct pinkrand_state* state);

#endif

