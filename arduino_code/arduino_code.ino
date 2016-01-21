#include <SoftwareSerial.h>

#define NIN 16

int SERIAL_RX = 8;
int SERIAL_TX = 9;
int PL_ = 4;
int CP = 5;
int Q7 = 6;

SoftwareSerial midiSerial(SERIAL_RX, SERIAL_TX);

int LOWEST_MIDI_NOTE = 41;
int inputs[NIN];

void noteOn(byte cmd, byte data1, byte data2) {
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);
//  Serial.print("midi: ");
//  Serial.print(data1);
//  Serial.print(" ");
//  Serial.println(data2);
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
  delayMicroseconds(500);
  digitalWrite(CP, LOW);
  delayMicroseconds(500);
  digitalWrite(PL_, HIGH);
  delayMicroseconds(500);


  for(int i = NIN - 1; i >= 0; i--) {

    // read
    int newValue = digitalRead(Q7);

    int oldValue = inputs[i];
    if(newValue != oldValue) {
      delayMicroseconds(10);    
      if(newValue == HIGH)
        noteOn(0x90, LOWEST_MIDI_NOTE + i, 127);
      else
        noteOn(0x90, LOWEST_MIDI_NOTE + i, 0);
    }
    
    inputs[i] = newValue;
    
    // shift
    delayMicroseconds(10);
    digitalWrite(CP, LOW);
    delayMicroseconds(10);
    digitalWrite(CP, HIGH);
    delayMicroseconds(10);
  }

  delay(2);
}
