#include <sstream>
#include "main.h"
#include "subsystems.hpp"

using namespace pros;
void initialize() {
  delay(200);
  lcd::initialize();
  lcd::set_text(1, "Hello World!");
}
//hjhjjjhhjhhjjh
void disabled() {}

void competition_initialize() {}

void autonomous() {
  //autonhandler();
  mptest();
}
void opcontrol() {
  int count = 0;
  int intakeCount = 0;
  int traySpeed;
  Controller mainController = Controller(E_CONTROLLER_MASTER);
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
    int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
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
      moveLift(140);
      asyncIntakeHandler();
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      moveLift(200);
      asyncIntakeHandler();
    }

    if (mainController.get_digital(E_CONTROLLER_DIGITAL_A)) {
      moveLift(-50);
      asyncIntakeHandler2();
      asynctrayHandler();
      delay(50);
    }

    if (tray.get_position() < 200) {
      set_brake(BRAKE, intakeL);
      set_brake(BRAKE, intakeR);
    } else {
      set_brake(COAST, intakeL);
      set_brake(COAST, intakeR);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L2) ) {
      int trayVel = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
      if(tray.get_position() > 1650 &&  trayVel > 0) {
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
      clearDrive();
    }
    if(debug) {
      printf("Left encoder: %d\n", lEncoder.get_value());
      printf("Right encoder: %d\n", rEncoder.get_value());
      printf("Middle encoder: %d\n", mEncoder.get_value());
    }
    delay(50);
  }
}
