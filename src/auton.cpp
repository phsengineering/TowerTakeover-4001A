#include "subsystems.hpp"
int traySpeed = 200;
void autonhandler() {
  if(auton == 1) { //red back
    redBack();
  }
  else if(auton == 2) { //blue back
    blueBack();
  }
  else if(auton == 3) { //red front
    redFront();
  }
  else if(auton == 4) { //blue front
    blueFront();
  }
  else if(auton == 5) {
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
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
  }
  else if(auton == 6) {
  pros::delay(400);
  smartDrive(300, 2500);
  driveVel(0);
  smartDrive(-400, -600);
  driveVel(0);
  intakeHandler(0);
  pros::delay(100);
  clearDrive();
  set_brake(0, driveLB);
  set_brake(0, driveLF);
  set_brake(0, driveRB);
  set_brake(0, driveRF);
  while(lEncoder.get_value() > -70) {
    driveLF.move_velocity(-75);
    driveLB.move_velocity(-75);
    driveRF.move_velocity(75);
    driveRB.move_velocity(75);
  }
  driveVel(0);
  intakeHandler(0);
  set_brake(0, driveLB);
  set_brake(0, driveLF);
  set_brake(0, driveRB);
  set_brake(0, driveRF);
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
  set_brake(0, driveLB);
  set_brake(0, driveLF);
  set_brake(0, driveRB);
  set_brake(0, driveRF);
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
  set_brake(1, driveLB);
  set_brake(1, driveLF);
  set_brake(1, driveRB);
  set_brake(1, driveRF);
  while(rEncoder.get_value() > -217) {
    driveLF.move_velocity(75);
    driveLB.move_velocity(75);
    driveRF.move_velocity(-75);
    driveRB.move_velocity(-75);
  }
  set_brake(0, driveLB);
  set_brake(0, driveLF);
  set_brake(0, driveRB);
  set_brake(0, driveRF);
  driveVel(0);
  pros::delay(100);
  set_brake(1, driveLB);
  set_brake(1, driveLF);
  set_brake(1, driveRB);
  set_brake(1, driveRF);
  while(lEncoder.get_value() < 1000) {
    driveVel(80);
  }
  driveVel(0);
  set_brake(0, driveLB);
  set_brake(0, driveLF);
  set_brake(0, driveRB);
  set_brake(0, driveRF);
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
  }
  else if(auton == 7) {
    while(theta < 90) {
      driveLF.move_velocity(75);
      driveLB.move_velocity(75);
      driveRF.move_velocity(-75);
      driveRB.move_velocity(-75);
    }
    driveVel(0);
  }
  else if(auton == 8) {
    movingbeans();
  }
}
