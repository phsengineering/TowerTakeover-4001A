#include "subsystems.hpp"
int traySpeed = 200;
void autonhandler() {
  if(auton == 1) { //red back
    clearDrive();
    pros::delay(200);
    smartDrive(215, 2500.0);
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
      while(lEncoder.get_value() < 155) {
        driveLF.move_velocity(50);
        driveLB.move_velocity(50);
        driveRF.move_velocity(-50);
        driveRB.move_velocity(-50);
      }
      driveVel(0);
      intakeHandler(0);
      clearDrive();
      set_brake(0, driveLB);
      set_brake(0, driveLF);
      set_brake(0, driveRB);
      set_brake(0, driveRF);
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
  else if(auton == 2) { //blue back
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
      smartDrive(-280, -1400.0);
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
      while(lEncoder.get_value() > -185) {
        driveLF.move_velocity(-50);
        driveLB.move_velocity(-50);
        driveRF.move_velocity(50);
        driveRB.move_velocity(50);
      }
      driveVel(0);
      intakeHandler(0);
      clearDrive();
      set_brake(0, driveLB);
      set_brake(0, driveLF);
      set_brake(0, driveRB);
      set_brake(0, driveRF);
      pros::delay(50);
      set_brake(1, driveLB);
      set_brake(1, driveLF);
      set_brake(1, driveRB);
      set_brake(1, driveRF);
      while(obtainPositionF() < 300) {
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
      while(tray.get_position() < 735) {
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
    }
  }
  else if(auton == 3) { //red front STILL NEEDS TO BE ADJUSTED
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
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
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
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
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
  else if(auton == 4) { //blue front
    pros::delay(200);
    clearDrive();
    smartDrive(200, 550);
    clearDrive();
    while(lEncoder.get_value() < 150) {
      driveLF.move_velocity(50);
      driveLB.move_velocity(50);
      driveRF.move_velocity(-50);
      driveRB.move_velocity(-50);
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
    smartDrive(200, 875);
    intakeHandler(0);
    clearDrive();
    while(lEncoder.get_value() < 85) {
      driveLF.move_velocity(50);
      driveLB.move_velocity(50);
      driveRF.move_velocity(-50);
      driveRB.move_velocity(-50);
    }
    driveVel(0);
    set_brake(0, driveLB);
    set_brake(0, driveLF);
    set_brake(0, driveRB);
    set_brake(0, driveRF);
    pros::delay(50);
    set_brake(1, driveLB);
    set_brake(1, driveLF);
    set_brake(1, driveRB);
    set_brake(1, driveRF);
    smartDrive(200, 270);
    driveVel(0);
    pros::delay(100);
    intakeHandler(-85);
    pros::delay(700);
    intakeHandler(0);
    tray.tare_position();
    int traySpeed = 140;
    pros::delay(200);
    while(tray.get_position() < 730) {
      traySpeed-=5;
      tray.move(traySpeed);
      pros::delay(60);
    }
    driveVel(150);
    pros::delay(100);
    driveVel(0);
    pros::delay(300);
    driveVel(-100);
    pros::delay(1000);
    driveVel(0);
  }
  else if(auton == 6) {
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
else if(auton == 7) {
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
  else if(auton == 8) {
    while(theta < 90) {
      driveLF.move_velocity(75);
      driveLB.move_velocity(75);
      driveRF.move_velocity(-75);
      driveRB.move_velocity(-75);
    }
    driveVel(0);
  }
}
