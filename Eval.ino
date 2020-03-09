
void evalOnLine();
char calculateRegulator();

int8_t regarr[5];
struct CircBuf cbuf;
/** eval(): from this function those functions are called that evaluate sensor input.
 *  in these functions the 'transition' variable should be set (if needed).
 */
void eval() {
  switch (state) {
    case START:
      evalStart(); // reading 'isStartSignSet()'
      break;
    case ON_LINE:
      evalOnLine(); // reading 'lineSensors()', 'distance()', 'isLaneChangeSet()', 'isStopInSight()'
      break;
    case LANE_CHANGE:
      //evalLaneChange(); // reading 'isNewLineInSight()'
      break;
    case SEMAPHORE:
      //evalSemaphore(); // reading 'distance()'
      break;
    case TURN:
      //evalTurn(); // reading 'sideDistance()'
      break;
    case STOP:
      //evalStop(); // do nothing
      break;
  }
}

/**
 * queries the sensorline whether the start-sign is set.
 * start-sign means: all the 5 sensors are detecting the line
 */
bool isStartSignSet() {
  int i = 0;
  readingLineSensors();
  for (i = 0; i < 5; i++) {
    if (regarr[i] != 1)
      break;
  }
  if (i == 5)
    return true;
  return false;
}

void evalStart() {
  if (isStartSignSet()) {
    transition = START_ON_LINE;
    Serial.println("Start sign found");
  } else {
    transition = IDLE;
  }
}

void readingLineSensors() {
  regarr[0] = digitalRead(LINESENS0);
  regarr[1] = digitalRead(LINESENS1);
  regarr[2] = digitalRead(LINESENS2);
  regarr[3] = digitalRead(LINESENS3);
  regarr[4] = digitalRead(LINESENS4);

  CircBufPut(&cbuf, calculateRegulatorValue(regarr), regarr);
}

char calculateRegulatorValue(int8_t regarr[5]){
  if (regarr[0] == 1) {
    return 1;
  } else if (regarr[1] == 1) {
    return 2;
  } else if (regarr[2] == 1) {
    return 3;
  } else if (regarr[3] == 1) {
    return 4;
  } else if (regarr[4] == 1) {
    return 5;
  }
}

void measureDistance() {
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

/**
 * checks whether there is a sensor in a HIGH state
 * indicating the line **it should be called after 'readingLineSensors()'**
 */
bool isLineInSight() {
  struct SensorState *bufptr;
  CircBufLast(&cbuf, bufptr);
  int i = 0;
  for (i = 0; i < 5; i++) {
    if (bufptr->regarr[i] == HIGH) {
      return true;
    }
  }
  return false;
}

/**
 * evaluates whether the semaphor or the obstacle is in sight
 */
void evaluateDistanceMeasurement() {
  if (distanceCmMid < 10) {
    if (isLineInSight()) {
      transition = ON_LINE_SEMAPHORE;
    } else {
      transition = ON_LINE_TURN;
    }
  }
}

/**
 * function to be called in 'ON_LINE' state
 * the other functions, called in its block, 
 * deal with reading and evaluating input in this state
 */
void evalOnLine() {
  readingLineSensors();
  measureDistance();
  evaluateDistanceMeasurement(); // sets 'transition'
}
