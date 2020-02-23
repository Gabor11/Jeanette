
/*  eval(): from this function those functions are called that evaluate sensor input.
    in these functions the 'transition' variable should be set (if needed).
*/
void evalOnLine();
char calculateRegulator();

void eval() {


  switch (state) {
    case START:
      //evalStart(); // reading 'isStartSignSet()'
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

void evalStart() {
  if (isStartSignSet()) {
    transition = START_ON_LINE;
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
}
void evalOnLine() {
  readingLineSensors();
  regul = calculateRegulatorValue();

/*
  Serial.print(regarr[0]);
  Serial.print(regarr[1]);
  Serial.print(regarr[2]);
  Serial.print(regarr[3]);
  Serial.print(regarr[4]);
  Serial.println();
*/


}

/**
   queries the sensorline whether the start-sign is set.
   start-sign means: all the 5 sensors are detecting the line
*/
bool isStartSignSet() {
  return false;
}
char calculateRegulatorValue(){
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
