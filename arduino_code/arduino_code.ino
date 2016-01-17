#include <SoftwareSerial.h>

int SERIAL_RX = 2;
int SERIAL_TX = 3;
int PL_ = 4;
int CP = 5;
int Q7 = 6;

SoftwareSerial midiSerial(SERIAL_RX, SERIAL_TX);

int LOWEST_MIDI_NOTE = 29;

void noteOn(byte cmd, byte data1, byte data2) {
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);
}

void setup() {
  Serial.begin(9600);
  midiSerial.begin(31250);
  pinMode(PL_, OUTPUT);         // shift register PL
  pinMode(CP, OUTPUT);          // shift register CP
  pinMode(Q7, INPUT);           // shift register Q7
}

void loop() {

  // load in shift register
  digitalWrite(PL_, LOW);
  digitalWrite(CP, LOW);
  delay(1);
  digitalWrite(PL_, HIGH);

  delay(1);
  int NIN = 8;
  int inputs[NIN];

  for(int i = NIN - 1; i >= 0; i--) {

    // read
    int newValue = digitalRead(Q7);
    int oldValue = inputs[i];
    if(newValue != oldValue) {
      if(newValue == HIGH)
        noteOn(0x90, LOWEST_MIDI_NOTE + i, 127);
      else
        noteOn(0x90, LOWEST_MIDI_NOTE + i, 0);
      inputs[i] = newValue;
    }

    // shift
    digitalWrite(CP, LOW);
    digitalWrite(CP, HIGH);
  }

  delay(10);
}
