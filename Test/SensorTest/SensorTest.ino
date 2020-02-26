
// Initializing right sensor arduino pins
const int TRIG_PIN = 22;
const int ECHO_PIN = 23;
// Initializing left sensor arduino pins
const int TRIG_PIN2 = 24;
const int ECHO_PIN2 = 25;
// Initializing middle sensor arduino pins
const int TRIG_PIN3 = 26;
const int ECHO_PIN3 = 27;


//Initializing infrasensors for line following
const int LINESENS0 = 40;
const int LINESENS1 = 41;
const int LINESENS2 = 42;
const int LINESENS3 = 43;
const int LINESENS4 = 44;

//Initializing collision-interrupt pins
const byte interruptPin1 = 18;
const byte interruptPin2 = 19;

//Initializing variables for distance measurement
long durationRight, durationLeft, durationMid, distanceCmRight, distanceCmLeft, distanceCmMid;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// initialize serial communication via USB:

  Serial.print("Testing sensors ");
  Serial.println();

  pinMode(TRIG_PIN, OUTPUT); // initialize pin mode for right sensors
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN2, OUTPUT); // initialize pin mode for left sensors
  pinMode(ECHO_PIN2, INPUT);

  pinMode(LINESENS0, INPUT);
  pinMode(LINESENS1, INPUT);
  pinMode(LINESENS2, INPUT);
  pinMode(LINESENS3, INPUT);
  pinMode(LINESENS4, INPUT);

  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin1), interruptA, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), interruptB, RISING);
  first_distance_measurement_is_zero();
}

void loop() {
  // put your main code here, to run repeatedly:
  // read input from sensors
  byte ls0=digitalRead(LINESENS0);
  byte ls1=digitalRead(LINESENS1);
  byte ls2=digitalRead(LINESENS2);
  byte ls3=digitalRead(LINESENS3);
  byte ls4=digitalRead(LINESENS4);
 
  Serial.print(" 0th : ");
  Serial.print(ls0);
  Serial.print(" 1st : ");
  Serial.print(ls1);
  Serial.print(" 2nd : ");
  Serial.print(ls2);
  Serial.print(" 3rd : ");
  Serial.print(ls3);
  Serial.print(" 4th : ");
  Serial.print(ls4);
  Serial.println();
  distance_measurement();
  Serial.print(" right distance : ");
  Serial.print(distanceCmRight);
  Serial.print(" left distance : ");
  Serial.print(distanceCmLeft);
  Serial.print(" middle distance : ");
  Serial.print(distanceCmMid);
  delay(500);
}

// can 
void first_distance_measurement_is_zero() { // this function is to start the measures
  int durationRight, durationLeft, durationMid = 0;
  /*Ultrasonc measuring part*/
  //right sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  durationRight = pulseIn(ECHO_PIN, HIGH);
  delay(1);
  // left sensor
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  durationLeft = pulseIn(ECHO_PIN2, HIGH);
  delay(1);
  // middle sensor
  digitalWrite(TRIG_PIN3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  durationMid = pulseIn(ECHO_PIN3, HIGH);
}

void distance_measurement() {
  //right sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  durationRight = pulseIn(ECHO_PIN, HIGH);
  delay(1);
  // left sensor
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  durationLeft = pulseIn(ECHO_PIN2, HIGH);
  delay(1);
  // left sensor
  digitalWrite(TRIG_PIN3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  durationMid = pulseIn(ECHO_PIN3, HIGH);

  // convert the time into a distance values
  distanceCmRight = durationRight / 29.1 / 2 ; //right
  distanceCmLeft = durationLeft / 29.1 / 2 ; //left
  distanceCmMid = durationMid / 29.1 / 2 ; //left
}

void interruptA() {
  Serial.println("Interrupt occured on 'A' side");
}

void interruptB() {
  Serial.println("Interrupt occured on 'B' side");
}
