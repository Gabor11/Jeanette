#include <AFMotor.h>

# define LEFTMOTOR 1
# define RIGHTMOTOR 2


# define ZERO 0
# define FIRSTSPEED 80
# define SECONDSPEED 85
# define THIRDSPEED 90
# define FORTHSPEED 95

AF_DCMotor left_motor(3); // left motor
AF_DCMotor right_motor(2); // right motor

void motor_control(int motor_identific, int motor_supercontrol);

void motor_control(int motor_identific, int motor_supercontrol) {

  if (motor_identific == LEFTMOTOR) {
    switch (motor_supercontrol) {
      case 1: // zero
        left_motor.setSpeed(ZERO);
        left_motor.run(BACKWARD);
        break;
      case 2: // forward_1
        left_motor.setSpeed(FIRSTSPEED);
        left_motor.run(FORWARD);
        break;
      case 3: // forward_2
        left_motor.setSpeed(SECONDSPEED);
        left_motor.run(FORWARD);
        break;
      case 4:// forward_3
        left_motor.setSpeed(THIRDSPEED);
        left_motor.run(FORWARD);
        break;
      case 5:// forward_4
        left_motor.setSpeed(FORTHSPEED);
        left_motor.run(FORWARD); 
        break;  
      case 6: //reverse_2
        left_motor.setSpeed(SECONDSPEED);
        left_motor.run(BACKWARD);
        break;
      case 7: //reverse_1:
        left_motor.setSpeed(FIRSTSPEED);
        left_motor.run(BACKWARD);
        break;
      default:
        left_motor.setSpeed(FIRSTSPEED);
        left_motor.run(FORWARD);
        break;
    }
  } else {
    switch (motor_supercontrol) {
      case 1: // zero
        right_motor.setSpeed(FORTHSPEED);
        right_motor.run(FORWARD); 
        break;
      case 2: // forward_1
        right_motor.setSpeed(THIRDSPEED);
        right_motor.run(FORWARD);
        break;
      case 3: // forward_2
        right_motor.setSpeed(SECONDSPEED);
        right_motor.run(FORWARD);
        break;
      case 4:// forward_3
        right_motor.setSpeed(FIRSTSPEED);
        right_motor.run(FORWARD);
        break;
      case 5:// forward_4
        right_motor.setSpeed(ZERO);
        right_motor.run(BACKWARD);
        break;  
      case 6: //reverse_2
        right_motor.setSpeed(SECONDSPEED);
        right_motor.run(BACKWARD);
        break;
      case 7: //reverse_1:
        right_motor.setSpeed(FIRSTSPEED);
        right_motor.run(BACKWARD);
        break;
      default:
        right_motor.setSpeed(FIRSTSPEED);
        right_motor.run(FORWARD);
        break;
    }
  }
}
