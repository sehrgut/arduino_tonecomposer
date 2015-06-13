#include "blink.h"
#include "pentatoniccomposer.h"

#define BUFLEN 255
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
  logNote(n);
  tone(PWM_PIN, n.freq, n.duration);
  delay(n.duration*1.01);
}

// doesn't work on pwm_pin
void tone_pwm(byte pin, int freq, int duration) {
  int endTime = millis() + duration;
  int mcs = 1000000 / freq / 2;
  
  while (millis() <= endTime) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(mcs);
    digitalWrite(pin, LOW);
    delayMicroseconds(mcs);
  }
}

void playTest() {
  static byte i = 1;
  static boolean up = true;
  
  if (i == 0xFF) up = false;
  else if (i == 0x01) up = true;
  
  analogWrite(PWM_PIN, (up ? i++ : i--));
  delay(i%10);
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
  cp = new  PentatonicComposer(tonic, BLUES_MINOR);
  Serial.println("The maestro is ready.");
}

void loop() {
  static boolean playing = true;
  
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
 
  if (playing) {
    play(cp->next());
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

