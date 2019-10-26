#include "subsystems.hpp"
void autonhandler() {
  clearDrive();
  pros::delay(200);
  smartDrive(215, 2500.0);
  if(obtainPositionF() < 0 && part < 1) {
    driveVel(0);
  }
  else {
    intakeHandler(190);
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
    clearDrive();
    smartDrive(-280, -1390.0);
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
    clearDrive();
    while(lEncoder.get_value() < 150) {
      driveLF.move_velocity(50);
      driveLB.move_velocity(50);
      driveRF.move_velocity(-50);
      driveRB.move_velocity(-50);
    }
    driveVel(0);
    intakeHandler(0);
    clearDrive();
    while(obtainPositionF() < 360) {
      driveRF.move_velocity(100);
      driveRB.move_velocity(100);
      driveLB.move_velocity(100);
      driveLF.move_velocity(100);
      pros::delay(15);
    }
    driveVel(0);
    intakeHandler(-190);
    pros::delay(250);
    intakeHandler(0);
    tray.tare_position();
    int traySpeed = 140;
    while(tray.get_position() < 730) {
      traySpeed-=5;
      tray.move(traySpeed);
      pros::delay(60);
    }
    driveVel(50);
    pros::delay(400);
    driveVel(0);
    pros::delay(300);
    driveVel(-100);
    pros::delay(1000);
    driveVel(0);
    // clearDrive();
    // pros::delay(25);
    // while(lEncoder.get_value() > -20) {
    //   driveRF.move_velocity(100);
    //   driveRB.move_velocity(100);
    //   driveLB.move_velocity(-100);
    //   driveLF.move_velocity(-100);
    //   pros::delay(15);
    // }
    //  clearDrive();
    //  smartDrive(-350, -1600);
    //   driveVel(0);

    //  clearDrive();
    //  while(rEncoder.get_value() > -20) {
    //    driveRF.move_velocity(-45);
    //    driveRB.move_velocity(-45);
    //    driveLB.move_velocity(45);
    //    driveLF.move_velocity(45);
    //    pros::delay(15);
    //  }
    //  driveVel(0);
    //  clearDrive();
    //  set_brake(1, driveLB);
    //  set_brake(1, driveLF);
    //  set_brake(1, driveRB);
    //  set_brake(1, driveRF);
    //  smartDrive(350, 1250);
    //  driveVel(0);
    //  clearDrive();
    //  pros::delay(50);
    //  smartDrive(-350, -1370);
    //  clearDrive();
  }
}
