
#define DELAYTIME 10

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
                 ON_LINE_STOP };
int transition = IDLE;

// steering-regulator related global variables
double regul = 0;
int regarr[9][20];

void setup() {

}

void loop() {
  eval();
  out();
  transit();
  delay(DELAYTIME);
}
