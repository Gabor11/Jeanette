

// state related
enum State {START, ON_LINE,  SEMAPHORE, TURN, STOP};
int state = START;
enum Transition {IDLE,
                 START_ON_LINE, 
                 ON_LINE_SEMAPHORE, 
                 SEMAPHORE_ON_LINE, 
                 ON_LINE_TURN, 
                 TURN_ON_LINE,
                 ON_LINE_STOP };
int transition = IDLE;

void eval() {
  switch(state) {
    case START:
      //evalStart();
    break;
    case ON_LINE:
      //evalOnLine();
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

void setup() {

}

void loop() {

}
