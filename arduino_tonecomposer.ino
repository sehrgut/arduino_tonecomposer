#include "blink.h"
#include "tlrand.h"
#include "composer.h"

#define MOTD "Welcome to ToneComposer"

#define PWM_PIN 8
#define RAND_PIN 0

byte scale[] = {30, 36, 40, 45, 54, 60};
byte scaleLen = 6;
int tonic = 440;
Composer* cp;

void logNote(struct Note n) {
  Serial.print(n.freq);
  Serial.print("Hz ");
  Serial.print(n.duration);
  Serial.println("ms");
}

void play(struct Note n) {
  logNote(n);
  tone(PWM_PIN, n.freq, n.duration);
  delay(n.duration*1.01);
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println(MOTD);

  randomSeed(tlrand(RAND_PIN));
  cp = new  Composer(scale, scaleLen, tonic);
  Serial.println("The maestro is ready.");
}

void loop() {
  play(cp->next());
}
