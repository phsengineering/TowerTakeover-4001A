#include "subsystems.hpp"
#include <sstream>
#include <string>
using namespace pros;
Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(5, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(9, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeL(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
ADIEncoder lEncoder(5, 6);
ADIEncoder rEncoder(1, 2);
ADIEncoder mEncoder(3, 4);
ADIDigitalIn choose('H');
void drive(int y, int r)
{
    //Scale up y and r from 127 to 12000
    y *= 11000.0 / 127.0;
    r *= 11000.0 / 127.0; //double check math

    driveLF.move_voltage(y + r);
    driveLB.move_voltage(y + r);
    driveRF.move_voltage(y - r);
    driveRB.move_voltage(y - r);
}
void intakeHandler(int speed) { //one method to run both intakes
    intakeR.move_velocity(speed);
    intakeL.move_velocity(speed);
}
void trayHandler(int trayPos) { //verify that tray cannot move past a certain point to avoid motor strain
  if(tray.get_position() < 25 && trayPos < 0) {
    trayPos = 0;
  }
  tray.move_velocity(trayPos); //otherwise move tray
}
void liftHandler(int liftInput) { //essentially redundant but it makes us look fancier so whatever
  lift.move_velocity(liftInput);
}
void driveVel(int updateSpeed) { //raw speed control over chassis - used in auton for movements where odom/shaft encoders not helpful
  driveLF.move_velocity(updateSpeed);
  driveLB.move_velocity(updateSpeed);
  driveRB.move_velocity(updateSpeed);
  driveRF.move_velocity(updateSpeed);
}
void clearDrive() { //clear all distance tracking sensors
  driveLF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();
  driveRF.tare_position();
  lEncoder.reset();
  rEncoder.reset();
}

void set_brake(int mode, Motor motor) { //set brake mode for individual motors without pros enum
  switch(mode) {
    case 0:
      motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    case 1:
      motor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    case 2:
      motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  }
}

void set_drive(int mode) { //switch the brake mode of the whole chassis at once
  Motor driveGroup [4] = { driveLB, driveLF, driveRF, driveRB };
  for(int i = 0; i < 4; i++) {
    set_brake(mode, driveGroup[i]);
  }
}
