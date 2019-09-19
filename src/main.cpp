#include "main.h"
#include "subsystems.hpp"

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Program is running");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autonhandler();
}

 void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
 	while (true) {
 		if(mainController.get_digital(E_CONTROLLER_DIGITAL_R2))
 		{
 			runPickUps();
 		}
 		else {
 			pickUpM1.move_velocity(0);
 			pickUpM2.move_velocity(0);
 		}
 	}
 }
