#include "subsystems.hpp"
int traySpeed = 200;
void auton5() {
  smartDrive(360, 2400);
  driveVel(0);
  smartDrive(-100, -500);
  driveVel(0);
  clearDrive();
  while(rEncoder.get_value() < 120) {
    driveLF.move_velocity(-100);
    driveLB.move_velocity(-100);
    driveRF.move_velocity(100);
    driveRB.move_velocity(100);
  }
  clearDrive();
  intakeHandler(0);
  set_drive(HOLD);
  pros::delay(50);
  set_drive(COAST);
}
void auton6() {
  pros::delay(400);
  smartDrive(300, 2500);
  driveVel(0);
  smartDrive(-400, -600);
  driveVel(0);
  intakeHandler(0);
  pros::delay(100);
  clearDrive();
  set_drive(HOLD);
  while(lEncoder.get_value() > -70) {
    driveLF.move_velocity(-75);
    driveLB.move_velocity(-75);
    driveRF.move_velocity(75);
    driveRB.move_velocity(75);
  }
  driveVel(0);
  intakeHandler(0);
  set_drive(HOLD);
  pros::delay(100);
  clearDrive();
  while(lEncoder.get_value() > -1250) {
    driveLF.move_velocity(-300);
    driveLB.move_velocity(-300);
    driveRF.move_velocity(-300);
    driveRB.move_velocity(-300);
  }
  driveVel(0);
  pros::delay(100);
  clearDrive();
  while(rEncoder.get_value() > -70) {
    driveLF.move_velocity(75);
    driveLB.move_velocity(75);
    driveRF.move_velocity(-75);
    driveRB.move_velocity(-75);
  }
  set_drive(HOLD);
  driveVel(0);
  pros::delay(100);
  clearDrive();
  smartDrive(360, 1800);
  driveVel(0);
  pros::delay(100);
  clearDrive();
  while(lEncoder.get_value() > -1100) {
    driveLF.move_velocity(-300);
    driveLB.move_velocity(-300);
    driveRF.move_velocity(-300);
    driveRB.move_velocity(-300);
    intakeHandler(195);
  }
  driveVel(0);
  pros::delay(100);
  clearDrive();
  set_drive(COAST);
  while(rEncoder.get_value() > -217) {
    driveLF.move_velocity(75);
    driveLB.move_velocity(75);
    driveRF.move_velocity(-75);
    driveRB.move_velocity(-75);
  }
  set_drive(HOLD);
  driveVel(0);
  pros::delay(100);
  set_drive(COAST);
  while(lEncoder.get_value() < 1000) {
    driveVel(80);
  }
  driveVel(0);
  set_drive(HOLD);
  intakeHandler(0);
  while(tray.get_position() < 1620) {
    traySpeed/=2;
    if(traySpeed < 85) {
      traySpeed = 85;
    }
    tray.move_velocity(traySpeed);
    if(tray.get_position() > 1620) {
      tray.move_velocity(0);
      break;
    }
  }
    tray.move_velocity(0);
    while(theta < 90) {
      driveLF.move_velocity(75);
      driveLB.move_velocity(75);
      driveRF.move_velocity(-75);
      driveRB.move_velocity(-75);
    }
    driveVel(0);
}
