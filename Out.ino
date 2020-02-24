
void outOnLine();

/*  out(): from the out function those functions are called that deal with motor control.
 *  no change of 'state' or 'transition' variables expected because of them.
 */
void out() {
  switch(state) {
    case START:
      //outStart(); // do nothing (motor does not move)
    break;
    case ON_LINE:
      outOnLine(); // calls motor functions, sets motor PWMs according to line position
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

void outOnLine() {
  LeftMotorControl(regul);
  RightMotorControl(regul);
}
