#include "main.h"
#include "subsystems.hpp"
#include <sstream>
void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autonhandler();
}

 void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
	pros::lcd::initialize();
	//autonhandler();
	lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
	tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
	while(true) {
		//Drive
		int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

		//Make r half as sensitive if not going forward or backward
		if(std::abs(y) < 16)
		{
			r = 127.0 * std::copysign(std::pow(std::abs(r / 127.0), 1.4 ), r);
		}
		drive(y, r);
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_A))
		{
			driveLF.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			driveLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			driveRF.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			driveRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		}
		else
		{
			driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
			driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
			driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
			driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
		}
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			intakeHandler(190);
		}
		else if (mainController.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			intakeHandler(-95);
		}
		else if(mainController.get_digital(E_CONTROLLER_DIGITAL_Y)) {
			intakeHandler(-195);
		}
		else {
			intakeHandler(0);
		}
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) { //350 and 210
			while(true) {
				if(lift.get_position() < 350) {
					lift.move_velocity(95);
				}
				if(tray.get_position() < 210) {
					tray.move_velocity(150);
				}

			}
		}
		else if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			while(lift.get_position() > 0) {
				liftHandler(-95);
			}
			while(tray.get_position() > 0) {
				trayHandler(-150);
			}
			liftHandler(0);
			trayHandler(0);
		}
		else {
			liftHandler(0);
		}
		int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		trayHandler(trayPos);
		puts(std::to_string(lift.get_position()).c_str());


		//std::string fPositionstuff = std::to_string(obtainPositionF());
		//std::string bPositionstuff = std::to_string(obtainPositionB());
		//if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
			//pros::lcd::set_text(1, fPositionstuff);
			//pros::lcd::set_text(2, bPositionstuff);
			pros::delay(20);
			//pros::lcd::clear_line(1);
		//}
	}
 }
