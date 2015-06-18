#include "blink.h"
#include "pentatoniccomposer.h"

#define BUFLEN 16
char buf[BUFLEN + 1];
boolean haveCmd = false;
int bufpos = 0;

#define MOTD "Welcome to ToneComposer"

#define PWM_PIN 8
#define RAND_PIN 1

int tonic = 440;
Composer* cp;

void logNote(struct Note n) {
  Serial.print(n.freq);
  Serial.print("Hz ");
  Serial.print(n.duration);
  Serial.println("ms");
}

void play(struct Note n) {
  tone(PWM_PIN, n.freq, n.duration);
  logNote(n);
}

void do_sequencer() {
  static struct Note next_note = cp->next();
  static unsigned long next_time;
  
  if (millis() >= next_time) {
    play(next_note);
    next_time = millis() + (next_note.duration);
    next_note = cp->next();
  }
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println(MOTD);

  pinMode(PWM_PIN, OUTPUT);
  Composer::setRngPin(RAND_PIN);
  cp = new  PentatonicComposer(tonic, BLUES_MINOR, PINKNOISE_2);
  Serial.println("The maestro is ready.");
}

void loop() {
  static boolean playing = true;
  
  if (playing) {
    do_sequencer();
  }

  if (haveCmd) {
    haveCmd = false;
    if (!strcmp("pause", buf)) {
      playing = false;
    } else if(!strcmp("help", buf)) {
      Serial.println("Type play, pause, or help");
    } else if(!strcmp("play", buf)) {
      playing = true;
    }
  }
 
}

// todo: differentiate b/w "buffer full" and "line complete"
void serialEvent() {
  while (Serial.available() && bufpos < BUFLEN) {
    char in = (char)Serial.read();
    
    if (in == '\n') {
      buf[bufpos] = '\0';
      haveCmd = true;
      bufpos = 0;
      break;
    } else {
      buf[bufpos++] = in;
    }
    
  }
}

