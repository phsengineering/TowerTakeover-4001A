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
			intakeHandler(-190);
		}
		else {
			intakeHandler(0);
		}
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			liftHandler(95);
		}
		else if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			liftHandler(-95);
		}
		else {
			liftHandler(0);
			lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		}
		int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		trayHandler(trayPos);
		std::ostringstream sstream;
		sstream << (int)intakeL.get_position();
		std::string intakeLStr = sstream.str();

		sstream << (int)intakeR.get_position();
		std::string intakeRStr = sstream.str();

		sstream << (int)driveLF.get_position();
		std::string LFString = sstream.str();

		sstream << (int)driveRF.get_position();
		std::string RFString = sstream.str();
		sstream << (int)tray.get_position();
		std::string trayStr = sstream.str();
		sstream << (int)lift.get_position();
		std::string liftStr = sstream.str();
		pros::lcd::set_text(1, "Intake R " + intakeRStr);
		pros::lcd::set_text(2, "Intake L " + intakeLStr);
		pros::lcd::set_text(3, "Left " + LFString);
		pros::lcd::set_text(4, "Right " + RFString);
		pros::lcd::set_text(5, "Tray " + trayStr);
		pros::lcd::set_text(6, "Lift " + liftStr);
		pros::delay(20);
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
			pros::lcd::clear_line(1);
			pros::lcd::clear_line(2);
			pros::lcd::clear_line(3);
			pros::lcd::clear_line(4);
			pros::lcd::clear_line(5);
			pros::lcd::clear_line(6);
			pros::lcd::clear_line(7);
			//pros::lcd::clear_line(1);
		}
	}
 }
