#include "blink.h"
#include "wdtrand.h"
#include "composer.h"

#define PWM_PIN 8

byte scale[] = {30, 36, 40, 45, 54, 60};
byte scaleLen = 6;
int tonic = 440;
Composer* cp;

void play(struct Note n) {
  tone(PWM_PIN, n.freq, n.duration);
  delay(n.duration*1.01);
}

void setup() {
  randomSeed(wdtrand(16));
  cp = new  Composer(scale, scaleLen, tonic);
}

void loop() {
  play(cp->next());
}
