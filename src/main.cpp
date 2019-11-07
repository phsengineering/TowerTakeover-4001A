#include "main.h"
#include "subsystems.hpp"
#include <sstream>

#include "main.h"
#include "subsystems.hpp"


void initialize() {
}

void disabled() {}

void competition_initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello World!");
}

void autonomous() {
		autonhandler();
}

void opcontrol() {
		int traySpeed = 127;
    int count = 0;
		pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
		//autonhandler();
		pros::lcd::initialize();
		set_brake(1, lift);
		set_brake(1, tray);
		int macroHandler = 0;
		int macroHandler2 = 0;
		clearDrive();
		while(true) {
      if (!(count % 50)) {
        mainController.print(0, 0, "Auton selected: %d", auton);
      }
      count++;
			if((!(count % 50)) && lift.get_temperature() > 55.0) {
				mainController.rumble(". -");
			}
      if(mainController.get_digital(E_CONTROLLER_DIGITAL_X)) {
        auton++;
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
      if(lift.get_position() < 20) {
        lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
      }
		}
}
