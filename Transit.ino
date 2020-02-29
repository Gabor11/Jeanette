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
    //state= START; // for test purposes TODO: remove 
}
