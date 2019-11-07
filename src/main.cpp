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
		int traySpeed = 200;
    int count = 0;
    int intakeCount = 0;
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
      else if(!mainController.get_digital(E_CONTROLLER_DIGITAL_Y) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R1) && !mainController.get_digital(E_CONTROLLER_DIGITAL_R2) && intakeCount % 2 == 0) {
        intakeHandler(0);
      }
      else if(mainController.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
        intakeCount++;
        if(intakeCount % 2 == 1) {
          intakeHandler(40);
        }
        else {
          intakeHandler(0);
        }
      }
      else {
        intakeHandler(0);
      }
			if(mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
				macroHandler++;
				if(macroHandler % 2 == 1) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() < 200 || tray.get_position() < 650) {
						lift.move_velocity(50);
						pros::delay(100);
						tray.move_velocity(175);
						if(tray.get_position() > 650) {
							tray.move_velocity(0);
						}
						if(lift.get_position() > 200) {
							lift.move_velocity(0);
						}
						if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
							break;
						}

					}
				}
				else if(macroHandler % 2 == 0) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() > 0 || tray.get_position() > 0) {
						lift.move_velocity(-70);
						pros::delay(200);
						tray.move_velocity(-100);
						if(tray.get_position() < 25) {
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
				tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
				lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			}
      if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
				macroHandler2++;
				if(macroHandler2 % 2 == 1) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() < 325 || tray.get_position() < 650) {
						lift.move_velocity(50);
						pros::delay(100);
						tray.move_velocity(175);
						if(tray.get_position() > 650) {
							tray.move_velocity(0);
						}
						if(lift.get_position() > 325) {
							lift.move_velocity(0);
						}
						if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
							break;
						}
					}
				}
				else if(macroHandler2 % 2 == 0) {
					tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
					lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
					while(lift.get_position() > 0 || tray.get_position() > 0) {
						lift.move_velocity(-60);
						pros::delay(200);
						tray.move_velocity(-150);
						if(tray.get_position() < 25) {
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

			if(mainController.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
				while(tray.get_position() < 1640) {
					if(std::abs(mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 0) {
						break;
					}
          if(tray.get_position() > (1640/2)) {
            traySpeed--;
          }
          if(tray.get_position() < 1640 && tray.get_position() > (1640/2)) {
            traySpeed-=5;
          }
					tray.move_velocity(traySpeed);
					pros::delay(45);
				}
			}
			if(debug) {
				printf("Tray Pos: %f\n", tray.get_position());
        printf("Lift pos: %f\n", lift.get_position());
			}
      if(lift.get_position() < 20) {
        lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
      }
		}
    pros::delay(20);
}
