#define SHORTTASKTIME 10
#define LONGTASKTIME  100
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
                 ON_LINE_STOP
                };
int transition = IDLE;

// steering-regulator related global variables
double regul = 0;
int regarr[9][20];
//timestamps for avoid delays
unsigned long shorttasktimestamp = 0;
unsigned long longtimestamp = 0;


void setup() {
}

void loop() {

  // short task
  if (millis() - shorttasktimestamp   >= SHORTTASKTIME ) {
    shorttasktimestamp = shorttasktimestamp + SHORTTASKTIME ;

    eval();  
    transit();
  }
  
// long task
if (millis() - longtimestamp   >= LONGTASKTIME ) {
    longtimestamp = longtimestamp + LONGTASKTIME ;
  
    out();
    
  }



}
