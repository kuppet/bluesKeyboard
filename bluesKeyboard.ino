// Button 1
int buttonPin1 = 32;
bool lastState1 = LOW;
bool state1 = LOW;

/////////TESTINGGGGGGGGGGGGGGGGGGG
// Button 2
int buttonPin2 = 31;
bool lastState2 = LOW;
bool state2 = LOW;

// Button 3
int buttonPin3 = 30;
bool lastState3 = LOW;
bool state3 = LOW;

// Switch 1
int switchPin1 = 29;
int switchVal = 12;

// Pot 1
int potVal1 = 0;
int lastPotVal1 = 0;

// LEDs
int ledPin1 = 37;
int ledPin2 = 36;
int ledPin3 = 35;
int ledPin4 = 34;
int ledPin5 = 33;

// Other
int note = 0;
int channel = 0;
int octaveVal = 1;

// Setup
void setup() {
  Serial.begin(9600);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);

  pinMode(switchPin1, INPUT);
}

// Loop
void loop() {
  // Button States
  lastState1 = state1;
  state1 = digitalRead(buttonPin1);
  lastState2 = state2;
  state2 = digitalRead(buttonPin2);
  lastState3 = state3;
  state3 = digitalRead(buttonPin3);

  // Octave Switch
  if (digitalRead(switchPin1) == HIGH) {
    playMIDI(buttonPin1, ledPin1, 66 + octaveVal, lastState1, state1);
    playMIDI(buttonPin2, ledPin2, 67 + octaveVal, lastState2, state2);
    playMIDI(buttonPin2, ledPin3, 70 + octaveVal, lastState3, state3);
    digitalWrite(ledPin4, HIGH);
  } else if (digitalRead(switchPin1) == LOW) {
    playMIDI(buttonPin1, ledPin1, 60 + octaveVal, lastState1, state1);
    playMIDI(buttonPin2, ledPin2, 63 + octaveVal, lastState2, state2);
    playMIDI(buttonPin2, ledPin3, 65 + octaveVal, lastState3, state3);
    digitalWrite(ledPin4, LOW);
  }

  // Pot
  lastPotVal1 = potVal1;
  potVal1 = map(analogRead(A13), 0, 1023, 1, 3);
  octaveVal = potVal1 * 12;
  Serial.println(potVal1);
  if (potVal1 == 1) {
    digitalWrite(ledPin5, LOW);
  } else if (potVal1 == 2) {
    digitalWrite(ledPin5, HIGH);
  } else if (potVal1 == 3) {
    digitalWrite(ledPin5, LOW);
  }
}

// Play Function
void playMIDI(int buttonPin, int ledPin, int note, bool lastState, bool state) {
  if (lastState == LOW and state == HIGH) {
    usbMIDI.sendNoteOn(note, 127, 1);
    digitalWrite(ledPin, HIGH);
    delay(5);
  } else if (lastState == HIGH and state == LOW) {
    usbMIDI.sendNoteOff(note, 0, 1);
    digitalWrite(ledPin, LOW);
    delay(5);
  }
}