#include "subsystems.hpp"
using namespace pros;
void redBack() {
  clearDrive();
  pros::delay(200);
  smartDrive(215, 2500.0);
  intakeHandler(190);
  set_drive(HOLD);
  pros::delay(50);
  set_drive(COAST);
  clearDrive();
  smartDrive(-280, -1390.0);
  set_drive(HOLD);
  pros::delay(50);
  set_drive(COAST);
  clearDrive();
  while(lEncoder.get_value() < 155) {
    driveLF.move_velocity(50);
    driveLB.move_velocity(50);
    driveRF.move_velocity(-50);
    driveRB.move_velocity(-50);
  }
  driveVel(0);
  intakeHandler(0);
  clearDrive();
  set_drive(HOLD);
  pros::delay(50);
  while(obtainPositionF() < 360) {
    driveRF.move_velocity(100);
    driveRB.move_velocity(100);
    driveLB.move_velocity(100);
    driveLF.move_velocity(100);
    pros::delay(15);
  }
  driveVel(0);
  intakeHandler(-75);
  pros::delay(250);
  intakeHandler(0);
  tray.tare_position();
  int traySpeed = 140;
  while(tray.get_position() < 730) {
    traySpeed-=5;
    tray.move(traySpeed);
    pros::delay(60);
    if(traySpeed < 40) {
      break;
    }
  }
  driveVel(50);
  pros::delay(400);
  driveVel(0);
  pros::delay(300);
  driveVel(-100);
  pros::delay(1000);
  driveVel(0);
}
void redFront() {
  pros::delay(200);
  clearDrive();
  smartDrive(200, 600);
  clearDrive();
  while(lEncoder.get_value() > -120) {
    driveLF.move_velocity(-50);
    driveLB.move_velocity(-50);
    driveRF.move_velocity(50);
    driveRB.move_velocity(50);
  }
  clearDrive();
  intakeHandler(0);
  set_drive(HOLD);
  pros::delay(50);
  set_drive(COAST);
  smartDrive(200, 950);
  intakeHandler(0);
  clearDrive();
  while(lEncoder.get_value() > -48) {
    driveLF.move_velocity(-50);
    driveLB.move_velocity(-50);
    driveRF.move_velocity(50);
    driveRB.move_velocity(50);
  }
  driveVel(0);
  set_drive(HOLD);
  pros::delay(50);
  set_drive(COAST);
  smartDrive(200, 625);
  driveVel(0);
  pros::delay(100);
  intakeHandler(-85);
  pros::delay(700);
  intakeHandler(0);
  tray.tare_position();
  int traySpeed = 180;
  pros::delay(200);
  while(tray.get_position() < 730) {
    traySpeed-=5;
    tray.move(traySpeed);
    pros::delay(60);
    if(traySpeed < 0) {
      break;
    }
  }
  tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  driveVel(-125);
  pros::delay(1500);
  driveVel(0);
}
