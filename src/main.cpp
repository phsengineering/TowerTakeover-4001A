#include <sstream>
#include "main.h"
#include "subsystems.hpp"

using namespace pros;
int auton = 0;
void initialize() {
  delay(200);
	pros::lcd::initialize();
	//autonSelector();

}
void competition_initialize(){
  const int autoCount = 7;
  const char* autoNames[autoCount] = {
    "RED protecc",
    "BLUE protecc",
    "RED Back",
    "BLUE Back",
    "RED 5",
		"BLUE 5",
		"progskill"
  };

  lcd::set_text(0, "Select an Auton");
  lcd::print(2, "%s", autoNames[auton]);

  while(1){
    if(choose.get_new_press()) {
      auton++;
      if(auton == autoCount)
        auton = 0;

      lcd::print(2, "%s", autoNames[auton]);
			lcd::print(3, "%d", auton);
    }

    delay(50);
  }
}

void autonomous() {
	//pidtest();
	autonhandler(auton);
}
void opcontrol() {
  int count = 0;
  int intakeCount = 0;
  int traySpeed;
  Controller mainController = Controller(E_CONTROLLER_MASTER);
  set_brake(BRAKE, lift); //make sure we're not stressing out the lift/tray unnecessarily
  set_brake(BRAKE, tray);
  clearDrive();
  while (true) {
    if(mainController.get_digital(E_CONTROLLER_DIGITAL_UP)) { //debug function
      clearDrive();
    }
    count++;
    if ((!(count % 50)) && lift.is_over_temp()) { //vibrate if the lift is running over 50C
      mainController.rumble(". -");
    }
    int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); //capture joystick values
    int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    if (std::abs(y) < 16) { //feed through to motors with deadband/scales
      r = 127.0 * std::copysign(std::pow(std::abs(r / 127.0), 1.35), r);
    }
    drive(y, r);
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_R1)) { //basic intake control
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
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_X)) { //async lift control
      moveLift(145); //with async motion profiler
      intakeHandler(-180);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      tray.move_absolute(400,200); //no profiler used here, allows for more specific velocity control
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      moveLift(200);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_A)) { //reset tray and lfit
      lift.move_absolute(-5,-100);
      tray.move_absolute(-10, -200);
      delay(50);
    }
    if (tray.get_position() < 200) { //keep tray on brake if under 200 ticks, otherwise release
      set_brake(BRAKE, intakeL);
      set_brake(BRAKE, intakeR);
    } else {
      set_brake(COAST, intakeL);
      set_brake(COAST, intakeR);
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_L2) ) { //tray macro (unused)
      int trayVel = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
      if(tray.get_position() > 1650 &&  trayVel > 0) {
        trayHandler(0);
      }
      else {
        trayHandler(trayVel);
      }
    }
    if (mainController.get_digital(E_CONTROLLER_DIGITAL_B)) { //emergency method to remove stray cube
      intakeL.move_velocity(-100);
    }
    delay(50); //let's not update too quickly
  }
}
