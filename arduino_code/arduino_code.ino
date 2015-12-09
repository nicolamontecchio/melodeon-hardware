int PL_ = 4;
int CP = 2;
int Q7 = 7;

int TESTLED = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      // open the serial port at 9600 bps:  

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
    int v = digitalRead(Q7);
//    Serial.println(v);
    inputs[NIN-1-i] = v;
    // shift
    digitalWrite(CP, LOW);
//    delay(1);
    digitalWrite(CP, HIGH);
//    delay(1);
  }
  
  if(inputs[0] == 1)
    digitalWrite(TESTLED, HIGH);
  else
    digitalWrite(TESTLED, LOW);
    

  for(int i = 0; i < NIN; i++) {
//    Serial.print(inputs[i]);
//    Serial.print(" ");
  }
//  Serial.println();
  delay(10);
}
