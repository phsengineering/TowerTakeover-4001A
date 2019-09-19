#include "main.h"
#include "subsystems.hpp"
using namespace okapi;

const int DRIVE_MOTOR_LEFT = 1;
const int DRIVE_MOTOR_RIGHT = 2;

auto chassis = ChassisControllerFactory::create(DRIVE_MOTOR_LEFT, DRIVE_MOTOR_RIGHT);

void autonhandler() {
  // Move to first goal
  chassis.moveDistance(1000);
  // Turn to face second goal
  chassis.turnAngle(100);
  // Drive toward second goal
  chassis.moveDistance(1500);
}
