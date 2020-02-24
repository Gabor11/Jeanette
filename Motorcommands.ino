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
AF_DCMotor *mtr_ptr; // motor pointer

// controls the actually set motor in 'mtr_ptr' - do not call it, unless it is set correctly
void motor_control(int regul);
void LeftMotorControl(int regul);
void RightMotorControl(int regul);

void motor_control(int regul) {
  switch (regul) {
    case 1: // zero
      mtr_ptr->setSpeed(ZERO);
      mtr_ptr->run(BACKWARD);
      break;
    case 2: // forward_1
      mtr_ptr->setSpeed(FIRSTSPEED);
      mtr_ptr->run(FORWARD);
      break;
    case 3: // forward_2
      mtr_ptr->setSpeed(SECONDSPEED);
      mtr_ptr->run(FORWARD);
      break;
    case 4:// forward_3
      mtr_ptr->setSpeed(THIRDSPEED);
      mtr_ptr->run(FORWARD);
      break;
    case 5:// forward_4
      mtr_ptr->setSpeed(FORTHSPEED);
      mtr_ptr->run(FORWARD); 
      break;  
    case 6: //reverse_2
      mtr_ptr->setSpeed(SECONDSPEED);
      mtr_ptr->run(BACKWARD);
      break;
    case 7: //reverse_1:
      mtr_ptr->setSpeed(FIRSTSPEED);
      mtr_ptr->run(BACKWARD);
      break;
    default:
      mtr_ptr->setSpeed(FIRSTSPEED);
      mtr_ptr->run(FORWARD);
      break;
  }
}

void LeftMotorControl(int regul) {
  mtr_ptr = &left_motor;
  motor_control(regul);
}

void RightMotorControl(int regul) {
  mtr_ptr = &right_motor;
  if (regul < 6) {
    regul = 6 - regul;
  }
  motor_control(regul);
}
