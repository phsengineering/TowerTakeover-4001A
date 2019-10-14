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
	int macroHandler = 0;
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
			macroHandler++;
			if(macroHandler % 2 == 1) {
				tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
				lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
				while(true) {
					lift.move_velocity(70);
					printf("%d", lift.get_position());
					pros::delay(100);
					tray.move_velocity(100);
					if(tray.get_position() > 275) {
						tray.move_velocity(0);
					}
					if(lift.get_position() > 175) {
						lift.move_velocity(0);
					}
					if(tray.get_position() > 275 && lift.get_position() > 175) {
						tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
						lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
						break;
					}
				}
			}
			else if(macroHandler % 2 == 0) {
				tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
				lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
				while(true) {
					lift.move_velocity(-70);
					pros::delay(100);
					tray.move_velocity(-75);
					if(tray.get_position() < 0) {
						tray.move_velocity(0);
					}
					if(lift.get_position() < 0) {
						lift.move_velocity(0);
					}
					if(tray.get_position() < 0 && lift.get_position() < 0) {
						break;
					}
				}
			}
		}
		else if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			while(lift.get_position() > 0 || tray.get_position() > 0) {
				lift.move_velocity(-95);
				tray.move_velocity(-75);
			}
		}
		else {
			liftHandler(0);
		}
		int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		if (trayPos > 0) {
			trayHandler(trayPos);
		}
		//puts(std::to_string(lift.get_position()).c_str());
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
