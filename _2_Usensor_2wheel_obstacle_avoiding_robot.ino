/* ===============================================================================

   This is Peter Jolankai's code for 2 ultrasonic sensor, obstacle avoiding robot.

   ===============================================================================
   Tested with ARDUINO MEGA with the suitable motor shield(L293D),
   ultrasonic sensors HC-SR04.

   Power supply:
   Arduino is powered with a 9 V battery separetly. Power jumper on motor shield
   in disconnected position.

   wiring
   6V from 4 AA battery to  the motor shield EXT_PWR connectors.
   M3 and M2 to DC Motors.

   Sensors to arduino
   VCC: 5 V
   GND: GND (Ground)
   Trig 1 22 // right sensor
   Echo 1 23
   Trig 2 24 // left sensor
   Echo 2 25
*/

#include <AFMotor.h>

/*
   =============================================
   Setting parameters for testing and iterating
  ==============================================
*/


//Set  limits to turn the car in cm
int first_limit = 20; // slowing down the opposite wheel
int second_limit = 15; // reversing the opposite wheel
int max_speed = 160; //set the speed PWM between 0 and 255
int min_speed = 110;

//Set the PWM between two motors for straight move
int corr_right_pwm = 00; // PWM correction of the right motor %
int corr_left_pwm = 0; // PWM correction of the left motor %



/*
   ======================================
   Initialization of hardware components
  =======================================
*/

// Initializing motor pins on motor shield
AF_DCMotor motor1(3); // left motor
AF_DCMotor motor2(2); // right motor

// Initializing right sensor arduino pins
const int TRIG_PIN = 22;
const int ECHO_PIN = 23;
// Initializing left sensor arduino pins
const int TRIG_PIN2 = 24;
const int ECHO_PIN2 = 25;

const byte interruptPin1 = 18;
const byte interruptPin2 = 19;
const byte interruptPin3 = 20;



// variables for distance measuring
long duration, duration2, distanceCm, distanceCm2;



// array for log movement, avoid to stuck into corners.

int left_wheel[] = { 0, 0, 0, 0};
int right_wheel[] = { 0, 0, 0, 0};
int temp = 0;

int reverseflag = 0;

void first_sensor_measure_is_zero();
void reverse_at_interrupt();


void setup() {

  Serial.begin(9600);// initialize serial communication via USB:

  Serial.print("Testing sensors ");
  Serial.println();

  pinMode(TRIG_PIN, OUTPUT); // initialize pin mode for right sensors
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN2, OUTPUT); // initialize pin mode for left sensors
  pinMode(ECHO_PIN2, INPUT);

  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin1), reverseL, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), reverseM, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), reverseR, RISING);

  first_sensor_measure_is_zero();
}

void loop() {

  if (reverseflag == 1) {
    reverse_at_interrupt();
    reverseflag = 0;
  }


  /*Ultrasonc measuring part*/
  //right sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  delay(1);
  // left sensor
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration2 = pulseIn(ECHO_PIN2, HIGH);

  // convert the time into a distance values
  distanceCm = duration / 29.1 / 2 ; //right
  distanceCm2 = duration2 / 29.1 / 2 ; //left

  delay(200);

  // sensor and motor logic
  //logic for right sensor and left motor
  if (first_limit <= distanceCm) {                                           // max speed
    motor1.setSpeed((max_speed * (100 + corr_left_pwm) / 100));
    motor1.run(FORWARD);
    left_wheel[0] = 1;
  } else if (second_limit <= distanceCm && distanceCm < first_limit) { // closing to obstacle
    int a = 0;
    a = max_speed - (first_limit - distanceCm) * ((max_speed - min_speed) / (first_limit - second_limit));
    motor1.setSpeed((a * (100 + corr_left_pwm) / 100));
    motor1.run(FORWARD);
    left_wheel[0] = 1;
  } else if (distanceCm < second_limit) {                          //obstacle is really close
    motor1.setSpeed((min_speed * (100 + corr_left_pwm) / 100));
    motor1.run(BACKWARD);
    left_wheel[0] = -1;
  }

  //logic for left sensor and right motor
  if (first_limit <= distanceCm2) {                                             // max speed
    motor2.setSpeed((max_speed * (100 + corr_right_pwm) / 100));
    motor2.run(FORWARD);
    right_wheel[0] = 1;
  } else if (second_limit <= distanceCm2 && distanceCm2  < first_limit) { // closing to obstacle
    int b = 0;
    b = max_speed - (first_limit - distanceCm2) * ((max_speed - min_speed) / (first_limit - second_limit));
    motor2.setSpeed((b * (100 + corr_right_pwm) / 100));
    motor2.run(FORWARD);
    right_wheel[0] = 1;
  } else if (distanceCm2 < second_limit) {                           //obstacle is really close
    motor2.setSpeed((min_speed * (100 + corr_right_pwm) / 100));
    motor2.run(BACKWARD);
    right_wheel[0] = -1;
  }


  // print values to the serial port testing the sensors
  Serial.print(distanceCm);
  Serial.print(" cm Right sensor    ");
  Serial.print(distanceCm2);
  Serial.print(" cm Left sensor ");
  Serial.print(left_wheel[0]); Serial.print(left_wheel[1]); Serial.print(left_wheel[2]); Serial.print(left_wheel[3]);
  Serial.print(" left_wheel ");
  Serial.print(right_wheel[0]); Serial.print(right_wheel[1]); Serial.print(right_wheel[2]); Serial.print(right_wheel[3]);
  Serial.print(" right_wheel ");

  Serial.println();

  if (left_wheel[0] == -1 && left_wheel[1] == 1 && left_wheel[2] == -1 && left_wheel[3] == 1)
  {
    motor1.setSpeed((max_speed * (100 + corr_left_pwm) / 100));
    motor1.run(FORWARD);
    motor2.setSpeed((min_speed * (100 + corr_right_pwm) / 100));
    motor2.run(BACKWARD);

    delay(random(200, 400));
  } else if (right_wheel[0] == -1 && right_wheel[1] == 1 && right_wheel[2] == -1 && right_wheel[3] == 1)
  {
    motor1.setSpeed((max_speed * (100 + corr_left_pwm) / 100));
    motor1.run(BACKWARD);
    motor2.setSpeed((min_speed * (100 + corr_right_pwm) / 100));
    motor2.run(FORWARD);

    delay(random(200, 300));
  }

  left_wheel[3] = left_wheel[2];
  left_wheel[2] = left_wheel[1];
  left_wheel[1] = left_wheel[0];

  right_wheel[3] = right_wheel[2];
  right_wheel[2] = right_wheel[1];
  right_wheel[1] = right_wheel[0];

  //delay(5000);
}

void reverse_at_interrupt() {
  motor1.setSpeed(min_speed);
  motor1.run(BACKWARD);
  motor2.setSpeed(min_speed);
  motor2.run(BACKWARD);
  delay(random(500, 1000));

  int rand_dir = 0;

  rand_dir = random(10);

  if (rand_dir < 5) {
    motor1.setSpeed(min_speed);
    motor1.run(FORWARD);
    motor2.setSpeed(min_speed);
    motor2.run(BACKWARD);
  } else {
    motor1.setSpeed(min_speed);
    motor1.run(BACKWARD);
    motor2.setSpeed(min_speed);
    motor2.run(FORWARD);
  }
  delay(random(500, 1000));


  Serial.println();
  Serial.print("kozep");
  Serial.println();





}

void first_sensor_measure_is_zero() { // this function is to start the measures
  int duration, duration2 = 0;
  /*Ultrasonc measuring part*/
  //right sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  delay(1);
  // left sensor
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration2 = pulseIn(ECHO_PIN2, HIGH);
}
void reverseL() {
  
  reverseflag = 1;
}
void reverseM() {
  reverseflag = 1;
}
void reverseR() {
  reverseflag = 1;

}
