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
		lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
		tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
		int macroHandler = 0;
		int macroHandler2 = 0;
		gyro.reset();
		while(true) {
			puts(std::to_string(gyro.get_value()).c_str());
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
					while(tray.get_position() < 200 || lift.get_position() < 120) {
						lift.move_velocity(70);
						pros::delay(200);
						tray.move_velocity(175);
						if(tray.get_position() > 200) {
							tray.move_velocity(0);
						}
						if(lift.get_position() > 120) {
							lift.move_velocity(0);
						}
						if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
							break;
						}
						//printf("%f\n", lift.get_position());
					}
					tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
					lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
				}
				else if(macroHandler % 2 == 0) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(tray.get_position() > 0 || lift.get_position() > 0) {
						lift.move_velocity(-70);
						pros::delay(100);
						tray.move_velocity(-100);
						if(tray.get_position() < 0) {
							tray.move_velocity(0);
						}
						if(lift.get_position() < 0) {
							lift.move_velocity(0);
						}
						if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
							break;
						}
						//printf("%f\n", lift.get_position());
					}
					tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
					lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
				}
			}
			if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
				macroHandler2++;
				if(macroHandler2 % 2 == 1) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() < 205 || tray.get_position() < 200) {
						lift.move_velocity(70);
						pros::delay(100);
						tray.move_velocity(175);
						if(tray.get_position() > 205) {
							tray.move_velocity(0);
						}
						if(lift.get_position() > 200) {
							lift.move_velocity(0);
						}
						if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
							break;
						}
						//printf("%f\n", lift.get_position());
					}
				}
				else if(macroHandler2 % 2 == 0) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() > 0 || tray.get_position() > 0) {
						lift.move_velocity(-70);
						pros::delay(200);
						tray.move_velocity(-100);
						if(tray.get_position() < 0) {
							tray.move_velocity(0);
						}
						if(lift.get_position() < 0) {
							lift.move_velocity(0);
						}
						if(tray.get_position() < 0 && lift.get_position() < 0) {
							break;
						}
						//printf("%f\n", lift.get_position());
					}
				}
				tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
				lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			}
			if(tray.get_position() < 200) {
				intakeL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
				intakeR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			}
			else {
				intakeL.set_brake_mode(E_MOTOR_BRAKE_COAST);
				intakeR.set_brake_mode(E_MOTOR_BRAKE_COAST);
			}
			int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
			trayHandler(trayPos);
			//printf("Temperature: %f \n", lift.get_temperature());
			//printf("%f", tray.get_position());
			pros::delay(20);
		}
		autonhandler();
}
