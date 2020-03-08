/* * * * * * * * * * * * * * * * * * * * * * * *
   These functions utilize Motorcommands.ino
   This is all about defining certain ways of
   controlled movements
 * * * * * * * * * * * * * * * * * * * * * * * */

# define STRAIGHTFORVARD 1000
# define TURNINGTIME45 250
# define TURNINGTIME90 TURNINGTIME45*2

unsigned long ManeuverTimestamp = 0;
enum ManeuverCatalouge {
  IDLE_MANEUVER,
  START_MANEUVER,
  TURN_LEFT,
  GO_STRAIGHT,
  TURN_RIGHT,
  STOP_MANEUVER
} ManoverCat;
char Manouverflag = 0;

void StartingRoll() {
  if (Manouverflag == 0) {
    ManoverCat = START_MANEUVER;
    Manouverflag ++;
  }

  switch (ManoverCat) {

    case START_MANEUVER:
      { ManoverCat = GO_STRAIGHT;
        ManeuverTimestamp = millis();
      }
      break;

    case GO_STRAIGHT:
      {
        LeftMotorControl(SECONDSPEED);
        RightMotorControl(SECONDSPEED) ;
        unsigned long GoStraightTimestamp = millis();
        if (GoStraightTimestamp - ManeuverTimestamp >= STRAIGHTFORVARD) {
          ManeuverTimestamp = GoStraightTimestamp;
          ManoverCat = STOP_MANEUVER;
        }
      }
      break;

    case STOP_MANEUVER:
      {
        LeftMotorControl(ZERO);
        RightMotorControl(ZERO);
        Manouverflag = 0;
      }
      break;
  }
}

// turn 45' and go straight
void Turn45(int directionparam) { // 0 for left turn, 1 for right turn

  if (Manouverflag == 0) {
    ManoverCat = START_MANEUVER;
    Manouverflag ++;
  }

  switch (ManoverCat) {

    case START_MANEUVER:
      {
        ManeuverTimestamp = millis();
        if (directionparam == 0)
        { ManoverCat = TURN_LEFT;
        } else if (directionparam == 0)
        { ManoverCat = TURN_RIGHT;
        } else {
          ManoverCat = STOP_MANEUVER;
        }
      }
      break;

    case TURN_LEFT:
      {
        LeftMotorControl(ZERO);
        RightMotorControl(SECONDSPEED) ;
        unsigned long TurnLeftTimestamp = millis();
        if (TurnLeftTimestamp - ManeuverTimestamp >= TURNINGTIME45) {
          ManeuverTimestamp = TurnLeftTimestamp;
          ManoverCat = GO_STRAIGHT;
        }
      }
      break;

    case TURN_RIGHT:
      {
        LeftMotorControl(SECONDSPEED);
        RightMotorControl(ZERO) ;
        unsigned long TurnLeftTimestamp = millis();
        if (TurnLeftTimestamp - ManeuverTimestamp >= TURNINGTIME45) {
          ManeuverTimestamp = TurnLeftTimestamp;
          ManoverCat = GO_STRAIGHT;
        }
      }
      break;

    case GO_STRAIGHT:
      {
        LeftMotorControl(SECONDSPEED);
        RightMotorControl(SECONDSPEED);
        unsigned long GoStraightTimestamp = millis();
        if (GoStraightTimestamp - ManeuverTimestamp >= STRAIGHTFORVARD) {
          ManeuverTimestamp = GoStraightTimestamp;
          ManoverCat = STOP_MANEUVER;
        }
        break;

      case STOP_MANEUVER:
        {
          LeftMotorControl(ZERO);
          RightMotorControl(ZERO);
          Manouverflag = 0;
        }
        break;
      }
  }
}
