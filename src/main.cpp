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
		autonhandler();
		pros::lcd::initialize();
		set_brake(1, lift);
		set_brake(1, tray);
		int macroHandler = 0;
		int macroHandler2 = 0;
		gyro.reset();
		while(true) {
			get_gyro();
			if(lift.get_temperature() > 55.0) {
				mainController.rumble(". -");
			}
			//Drive
			int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

			//Make r half as sensitive if not going forward or backward
			if(std::abs(y) < 16)
			{
				r = 127.0 * std::copysign(std::pow(std::abs(r / 127.0), 1.4 ), r);
			}
			drive(y, r);
			if(mainController.get_digital(E_CONTROLLER_DIGITAL_X)) {
				break;
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
					set_brake(1, tray);
					set_brake(1, lift);
					// while(tray.get_position() < 200 || lift.get_position() < 120) {
					// 	lift.move_velocity(70);
					// 	pros::delay(200);
					// 	tray.move_velocity(175);
					// 	if(tray.get_position() > 200) {
					// 		tray.move_velocity(0);
					// 	}
					// 	if(lift.get_position() > 120) {
					// 		lift.move_velocity(0);
					// 	}
					// 	if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
					// 		break;
					// 	}
					// }
					tray.move_absolute(200, 175);
					pros::delay(200);
					lift.move_absolute(120, 70);
					set_brake(0, tray);
					set_brake(0, lift);
				}
				else if(macroHandler % 2 == 0) {
					set_brake(1, tray);
					set_brake(1, lift);
					// while(tray.get_position() > 0 || lift.get_position() > 0) {
					// 	lift.move_velocity(-70);
					// 	pros::delay(100);
					// 	tray.move_velocity(-100);
					// 	if(tray.get_position() < 0) {
					// 		tray.move_velocity(0);
					// 	}
					// 	if(lift.get_position() < 0) {
					// 		lift.move_velocity(0);
					// 	}
					// 	if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
					// 		break;
					// 	}
					// }
					tray.move_absolute(0, -175);
					pros::delay(100);
					lift.move_absolute(0, -70);
					set_brake(0, tray);
					set_brake(0, lift);
				}
			}
			if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
				macroHandler2++;
				if(macroHandler2 % 2 == 1) {
					set_brake(1, tray);
					set_brake(1, lift);
					// while(lift.get_position() < 205 || tray.get_position() < 200) {
					// 	lift.move_velocity(70);
					// 	pros::delay(100);
					// 	tray.move_velocity(175);
					// 	if(tray.get_position() > 205) {
					// 		tray.move_velocity(0);
					// 	}
					// 	if(lift.get_position() > 200) {
					// 		lift.move_velocity(0);
					// 	}
					// 	if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
					// 		break;
					// 	}
					// }
					tray.move_absolute(205, 175);
					pros::delay(200);
					lift.move_absolute(200, 70);
				}
				else if(macroHandler2 % 2 == 0) {
					set_brake(1, tray);
					set_brake(1, lift);
					// while(lift.get_position() > 0 || tray.get_position() > 0) {
					// 	lift.move_velocity(-70);
					// 	pros::delay(200);
					// 	tray.move_velocity(-100);
					// 	if(tray.get_position() < 0) {
					// 		tray.move_velocity(0);
					// 	}
					// 	if(lift.get_position() < 0) {
					// 		lift.move_velocity(0);
					// 	}
					// 	if(tray.get_position() < 0 && lift.get_position() < 0) {
					// 		break;
					// 	}
					// }
				}
				tray.move_absolute(0, -175);
				pros::delay(100);
				lift.move_absolute(0, -70);
				set_brake(0, tray);
				set_brake(0, lift);
			}
			if(tray.get_position() < 200) {
				set_brake(0, intakeL);
				set_brake(0, intakeR);
			}
			else {
				set_brake(1, intakeL);
				set_brake(1, intakeR);
			}
			int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
			trayHandler(trayPos);
			pros::delay(20);
			if(mainController.get_digital(E_CONTROLLER_DIGITAL_A)) {
				gyro.reset();
			}
			printf("left position: %d\n", lEncoder.get_value());
			printf("right position: %d\n", rEncoder.get_value());
			puts(std::to_string(gyro.get_value()).c_str());
		}
}
