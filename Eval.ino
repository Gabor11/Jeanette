
/*  eval(): from this function those functions are called that evaluate sensor input.
 *  in these functions the 'transition' variable should be set (if needed).
 */
void eval() {
  switch(state) {
    case START:
      //evalStart(); // reading 'isStartSignSet()'
    break;
    case ON_LINE:
      //evalOnLine(); // reading 'lineSensors()', 'distance()', 'isLaneChangeSet()', 'isStopInSight()'
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

void evalOnLine() {
  
}

/**
 * queries the sensorline whether the start-sign is set. 
 * start-sign means: all the 5 sensors are detecting the line 
 */
bool isStartSignSet() {
  return false;
}
