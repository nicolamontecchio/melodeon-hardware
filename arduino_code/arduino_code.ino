#include <SoftwareSerial.h>

int PL_ = 4;
int CP = 5;
int Q7 = 6;
int SERIAL_RX = 2;
int SERIAL_TX = 3;


SoftwareSerial midiSerial(SERIAL_RX, SERIAL_TX); // digital pins that we'll use for soft serial RX & TX

int TESTLED = 10;
int LOWEST_MIDI_NOTE = 29;

void noteOn(byte cmd, byte data1, byte data2) {
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);
}

void setup() {
  Serial.begin(9600);   
  midiSerial.begin(31250);  // midi speed
  pinMode(PL_, OUTPUT);  // PL
  pinMode(CP, OUTPUT);  // CP
  pinMode(Q7, INPUT);   // Q7
}

void loop() {
  // put your main code here, to run repeatedly:
  
//  Serial.println("sampling state");
  digitalWrite(PL_, LOW);

  digitalWrite(CP, LOW);
  
  delay(1); 
//  Serial.println("reading state");
  digitalWrite(PL_, HIGH);

  delay(1);
  int NIN = 8;
  int inputs[NIN];

  for(int i = 0; i < NIN; i++) {
    // read 
    int newValue = digitalRead(Q7);
    int oldValue = inputs[NIN-1-i];
    if(newValue != oldValue) {
      if(newValue == HIGH)
        noteOn(0x90, LOWEST_MIDI_NOTE + NIN - i + 1, 127);
      else 
        noteOn(0x90, LOWEST_MIDI_NOTE + NIN - i + 1, 0);      
      inputs[NIN-1-i] = newValue;    
      Serial.print("note ");
      Serial.print(LOWEST_MIDI_NOTE + i);
      Serial.print(": ");
      Serial.print(newValue);
      Serial.println("");
    }
    // shift
    digitalWrite(CP, LOW);
    digitalWrite(CP, HIGH);
  }
  
//  if(inputs[0] == 1)
//    digitalWrite(TESTLED, HIGH);
//  else
//    digitalWrite(TESTLED, LOW);
//   
  delay(10);
}
