#include <sstream>
#include "main.h"
#include "subsystems.hpp"


void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello World!");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  autonhandler();
}

void opcontrol() {
  int count = 0;
  int intakeCount = 0;
  int traySpeed;
  pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
  set_brake(1, lift);
  set_brake(1, tray);
  clearDrive();
  //autontest();
  while (true) {
    obtainPositionRaw();
    if(mainController.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      clearDrive();
    }
    count++;
    if ((!(count % 50)) && lift.get_temperature() > 55.0) {
      mainController.rumble(". -");
    }
    //Drive
    int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

    //Make r half as sensitive if not going forward or backward
    if (std::abs(y) < 16) {
      r = 127.0 * std::copysign(std::pow(std::abs(r / 127.0), 1.4), r);
    }
    drive(y, r);
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intakeHandler(190);
    } else if (mainController.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intakeHandler(-95);
    } else if (mainController.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      intakeHandler(-195);
    } else if (!mainController.get_digital(E_CONTROLLER_DIGITAL_Y) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R1) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R2) && intakeCount % 2 == 0) {
      intakeHandler(0);
    } else if (mainController.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
      intakeCount++;
      if (intakeCount % 2 == 1) {
        intakeHandler(40);
      } else {
        intakeHandler(0);
      }
    } else {
      intakeHandler(0);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      lift.move_absolute(200, 115);
      tray.move_absolute(650, 200);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      lift.move_absolute(325, 115);
      tray.move_absolute(650, 200);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_A)) {
      lift.move_absolute(2, -70);
      delay(40);
      tray.move_absolute(2, -200);
    }

    if (tray.get_position() < 200) {
      set_brake(0, intakeL);
      set_brake(0, intakeR);
    } else {
      set_brake(1, intakeL);
      set_brake(1, intakeR);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
      traySpeed = 200;
      while(tray.get_position() < 400) {
        tray.move_velocity(traySpeed);
      }
      while(tray.get_position() < 1620) {
        traySpeed/=2;
        if(traySpeed < 85) {
          traySpeed = 85;
        }
        tray.move_velocity(traySpeed);
        if(tray.get_position() > 1620) {
          tray.move_velocity(0);
        }
      }
      tray.move_velocity(0);
      //tray.move_absolute(1600, 160);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
      tray.move_absolute(2, -200);
    }
    pros::delay(50);
  }
}
