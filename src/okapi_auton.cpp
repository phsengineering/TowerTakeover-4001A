//#include "subsystems.hpp"
#include "okapi/api.hpp"
using namespace okapi;

auto rightodom = ADIEncoder('A', 'B', false);
auto leftodom = ADIEncoder('E', 'F', false);
auto midodom = ADIEncoder('C', 'D', false);
ChassisScales scales = ChassisScales({3.25, 9.75}, (imev5BlueTPR*(5/3)));
Logger logger = Logger(TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", Logger::LogLevel::debug);
TimeUtil test = TimeUtilFactory::createDefault();
auto chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1})
    .withGearset({AbstractMotor::gearset::blue, 5/3})
    .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', false})
    //.withDimensions(scales)
    .withGains(
         { 0.004, 0, 0.0 }, // Distance controller gains
         { 0.0029, 0.00001, 0.0000 }, // Turn controller gains
         { 0.00022, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>()
     )
    .build();
// auto pathgen = AsyncMotionProfileControllerBuilder()
//     .withLimits({maxVel, maxAccel, maxJerk})
//     //.withOutput(drive)
//     .withOutput(chassis)
//     .buildMotionProfileController();

void turn40 () {
  chassis->turnAngle(-59_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
}
void turnBack () {
  chassis->turnAngle(59_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
}
void turn3 () {
  chassis->turnAngle(214_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
}
void turnL90 () {
  chassis->turnAngle(-155_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
}

void turnR90 () {
  chassis->turnAngle(165_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
}

void turnR180(){
  chassis->turnAngle(230_deg);
  chassis->waitUntilSettled();
}

void redOkapi() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(250);
  chassis->moveDistance(2210);
  chassis->waitUntilSettled();
}
void redOkapi2() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(250);
  chassis->moveDistance(-1470);
  chassis->waitUntilSettled();
  chassis->turnAngle(250_deg);
  chassis->stop();
}
void blueOkapi() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(250);
  chassis->setTurnsMirrored(true);
  chassis->moveDistance(2210);
  chassis->waitUntilSettled();
}
void blueOkapi2() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(250);
  chassis->moveDistance(-1470);
  chassis->waitUntilSettled();
  chassis->turnAngle(250_deg);
  chassis->stop();
}
