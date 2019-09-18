#include "main.h"
#include "subsystems.hpp"
pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
void opcontrol() {
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
