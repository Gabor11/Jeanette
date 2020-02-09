
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
      //evalStart();
    break;
    case ON_LINE:
      //evalOnLine();
    break;
    case LANE_CHANGE:
      //evalLaneChange();
    break;
    case SEMAPHORE:
      //evalSemaphore();
    break;
    case TURN:
      //evalTurn();
    break;
    case STOP:
      //evalStop();
    break;
  }
}

/*  out(): from the out function those functions are called that deal with motor control.
 *  no change of 'state' or 'transition' variables expected because of them.
 */
void out() {
  switch(state) {
    case START:
      //outStart();
    break;
    case ON_LINE:
      //outOnLine();
    break;
    case LANE_CHANGE:
      //outLaneChange();
    break;
    case SEMAPHORE:
      //outSemaphore();
    break;
    case TURN:
      //outTurn();
    break;
    case STOP:
      //outStop();
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
