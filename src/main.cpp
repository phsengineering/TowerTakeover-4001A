#include "main.h"
#include "subsystems.hpp"
#include <sstream>

#include "main.h"
#include "subsystems.hpp"
void on_center_button() {
 if(auton > 4) {
	 auton = 1;
 }
 else {
	 auton++;
 }
 if (auton == 1) {
	 pros::lcd::set_text(2, "Red back");
 }
 else if (auton == 2) {
	 pros::lcd::set_text(2, "Blue back");
 }
 else if (auton == 3) {
	 pros::lcd::set_text(2, "Red front");
 }
 else if (auton == 4) {
	 pros::lcd::set_text(2, "Blue front");
 }
}

void initialize() {
 pros::lcd::initialize();
 pros::lcd::set_text(1, "4001A");
 pros::lcd::set_text(5, "Auton Ready");
 pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}

void competition_initialize() {}

void autonomous() {
		autonhandler();
}

void opcontrol() {
		int traySpeed = 127;
		pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
		//autonhandler();
		pros::lcd::initialize();
		set_brake(1, lift);
		set_brake(1, tray);
		int macroHandler = 0;
		int macroHandler2 = 0;
		clearDrive();
		while(true) {
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
				while(tray.get_position() < 730) {
					if(std::abs(mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 0) {
						break;
					}
					traySpeed--;
					tray.move(traySpeed);
					pros::delay(60);
				}
			}
			if(debug) {
				printf("Pos: %f\n", obtainPositionF());
			}
		}
}
