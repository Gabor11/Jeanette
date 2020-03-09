#define SHORTTASKTIME 10
#define LONGTASKTIME  100
// state related global variables (and their enums)
enum State {START, ON_LINE, LANE_CHANGE, SEMAPHORE, TURN, STOP};
int state = START;
enum Transition {IDLE,
                 START_ON_LINE,
                 ON_LINE_LANE_CHANGE,
                 LANE_CHANGE_ON_LINE,
                 ON_LINE_SEMAPHORE,
                 SEMAPHORE_ON_LINE,
                 ON_LINE_TURN,
                 TURN_ON_LINE,
                 ON_LINE_STOP
                };
int transition = IDLE;

//timestamps for avoid delays
unsigned long shorttasktimestamp = 0;
unsigned long longtimestamp = 0;


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
const int LINESENS0 = 40; // most left
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
  Serial.begin(9600);// initialize serial communication via USB:

  Serial.print("Initializing pins");
  Serial.println();

  pinMode(TRIG_PIN, OUTPUT); // initialize pin mode for right sensors
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN2, OUTPUT); // initialize pin mode for left sensors
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIG_PIN3, OUTPUT); // initialize pin mode for left sensors
  pinMode(ECHO_PIN3, INPUT);

  pinMode(LINESENS0, INPUT);
  pinMode(LINESENS1, INPUT);
  pinMode(LINESENS2, INPUT);
  pinMode(LINESENS3, INPUT);
  pinMode(LINESENS4, INPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin1), interruptA, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), interruptB, RISING);

}

void loop() {
  // short task
  if (millis() - shorttasktimestamp >= SHORTTASKTIME ) {
    shorttasktimestamp = shorttasktimestamp + SHORTTASKTIME ;
    transit();
    eval();
    out();
  }

  // long task
  if (millis() - longtimestamp   >= LONGTASKTIME ) {
    longtimestamp = longtimestamp + LONGTASKTIME ;
<<<<<<< HEAD
=======

>>>>>>> Peti_develop
  }
}
