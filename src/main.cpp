#include <sstream>
#include "main.h"
#include "subsystems.hpp"

using namespace pros;
void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello World!");
  pros::delay(200);
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
  set_brake(COAST, lift);
  set_brake(COAST, tray);
  clearDrive();
  while (true) {
    if(mainController.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      clearDrive();
    }
    count++;
    if ((!(count % 50)) && lift.is_over_temp()) {
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
      intakeHandler(200);
    } else if (mainController.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intakeHandler(-100);
    } else if (!mainController.get_digital(E_CONTROLLER_DIGITAL_R2) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R1) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R2) && intakeCount % 2 == 0) {
      intakeHandler(0);
    } else if (mainController.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) {
      intakeCount++;
      if (intakeCount % 2 == 1) {
        intakeHandler(40);
      } else {
        intakeHandler(0);
      }
    } else {
      intakeHandler(0);
    }
    set_brake(HOLD, lift);
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_X)) {
      tray.move_absolute(690, 200);
      lift.move_absolute(200, 150);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      // intakeR.move_absolute(-5, -200);
      // intakeL.move_absolute(-05, -200);
      tray.move_absolute(800, 200);
      lift.move_absolute(325, 150);
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_A)) {
      lift.move_absolute(0, -70);
      delay(200);
      tray.move_absolute(0, -200);
    }

    if (tray.get_position() < 200) {
      set_brake(HOLD, intakeL);
      set_brake(HOLD, intakeR);
    } else {
      set_brake(COAST, intakeL);
      set_brake(COAST, intakeR);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L2) ) {
      int trayVel = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
      if(tray.get_position() > 1610 &&  trayVel < 0) {
        trayHandler(0);
      }
      else {
        trayHandler(trayVel);
      }
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
      intakeL.move_velocity(-100);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      mEncoder.reset();
    }
    positionTrack();
    pros::delay(50);
  }
}
