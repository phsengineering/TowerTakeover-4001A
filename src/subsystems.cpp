#include "subsystems.hpp"

//Drivetrain
Motor pickUpM1(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor pickUpM2(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

void runPickUps() {
  pickUpM1.move_velocity(100);
  pickUpM2.move_velocity(100);
}
