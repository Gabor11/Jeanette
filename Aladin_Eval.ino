
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
