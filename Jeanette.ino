
#define DELAYTIME 10

// state related
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
                 ON_LINE_STOP };
int transition = IDLE;

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

/*  out(): from the out function those functions are called that deal with motor control.
 *  no change of 'state' or 'transition' variables expected because of them.
 */
void out() {
  switch(state) {
    case START:
      //outStart(); // do nothing (motor does not move)
    break;
    case ON_LINE:
      //outOnLine(); // calls motor functions, sets motor PWMs according to line position
    break;
    case LANE_CHANGE:
      //outLaneChange(); // calls functions to find new lane
    break;
    case SEMAPHORE:
      //outSemaphore(); // stop motors
    break;
    case TURN:
      //outTurn(); // calls functions managing the turning around the obstacle
    break;
    case STOP:
      //outStop(); // stop motors
    break;
  }
}

/*  transit(): in this function the 'state' variable is set
 *  according to the 'transition' variable.
 */
void transit() {
  switch(transition) {
    case IDLE:
      //do nothing
    break;
    case START_ON_LINE:
      state = ON_LINE;
    break;
    case ON_LINE_LANE_CHANGE:
      state = LANE_CHANGE;
    break;
    case LANE_CHANGE_ON_LINE:
      state = ON_LINE;
    break;
    case ON_LINE_SEMAPHORE:
      state = SEMAPHORE;
    break;
    case SEMAPHORE_ON_LINE:
      state = ON_LINE;
    break;
    case ON_LINE_TURN:
      state = TURN;
    break;
    case TURN_ON_LINE:
      state = ON_LINE;
    break;
    case ON_LINE_STOP:
      state = STOP;
    break;
  }
}

void setup() {

}

void loop() {
  eval();
  out();
  transit();
  delay(DELAYTIME);
}
