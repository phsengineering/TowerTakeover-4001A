#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
auto myChassis = ChassisControllerFactory::create(
  {-3, 4}, // Left motors
  {1, -2},   // Right motors
  AbstractMotor::gearset::blue,
  {3.25_in, 9.8125_in} // 3.75 inch wheels, 9 inch wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
  1.0,  // Maximum linear velocity of the Chassis in m/s
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
  8.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);

void autocache() {
  myChassis.moveDistance(3_ft);
  myChassis.turnAngle(30_deg);
  //myChassis.waitUntilSettled();
}
