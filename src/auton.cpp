#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // left motor is 1, right motor is 2 (reversed)
    .withGains(
         { 0.001, 0, 0.0 }, // Distance controller gains
         { 0.0029, 0.0, 0.000 }, // Turn controller gains
         { 0.00022, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    .withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true})
    .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.625_in}, imev5BlueTPR})
    .withOdometry({{2.75_in, 5_in, 4.375_in, 2.75_in}, quadEncoderTPR}) // use the same scales as the chassis (above)
    .withLogger(std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show errors and warnings
    ))
    .withMaxVelocity(300)
    .buildOdometry(); // build an odometry chassis
auto profileController = AsyncMotionProfileControllerBuilder()
    .withLimits({1.368, 5.5, 6.155}) //max vel, max accel, max jerk
    .withOutput(chassis)
    .buildMotionProfileController();
void autonhandler() {
    chassis->driveToPoint({3_ft, 0_ft});
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({-1_ft, 0_ft}, true);
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({0_ft, -2_ft});
}
void mptest() {
  //ChassisScales scales = ChassisScales({3.25, 9.75}, (imev5BlueTPR*(3/5)));
  Logger logger = Logger(TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
          "/ser/sout", Logger::LogLevel::debug);
  TimeUtil test = TimeUtilFactory::createDefault();
  auto chassis = ChassisControllerBuilder()
      .withMotors({4, 3}, {2, 1})
      .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.75_in}, imev5BlueTPR*(5/3)})
      .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', false})
      .withOdometry({{2.76_in, 5_in, 4.5_in, 2.76_in}, quadEncoderTPR})
      .buildOdometry(); // build an odometry chassis


      auto profileController = AsyncMotionProfileControllerBuilder()
          .withLimits({1.368, 5.5, 6.155}) //max vel, max accel, max jerk
          .withOutput(chassis)
          .buildMotionProfileController();

      profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {7_ft, 0_ft, 0_deg}},  // Profile starting position, this will normally be (0, 0, 0) // The next point in the profile, 3 feet forward
      "A" // Profile name
    );
      profileController->generatePath({
      {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
      {2_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
      "B" // Profile name
    );
      profileController->generatePath({
      {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
      {4_ft, 5.2_ft, 180_deg}}, // The next point in the profile, 3 feet forward
      "C" // Profile name
    );
    profileController->generatePath({
    {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    {6_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
    "D" // Profile name
);
profileController->generatePath({
{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
{3_ft, 0_ft, 90_deg}}, // The next point in the profile, 3 feet forward
"E" // Profile name
);
//start autonomous here
      profileController->setTarget("A");
      profileController->waitUntilSettled();
      profileController->setTarget("B",true);
      profileController->setTarget("C",true);
      profileController->waitUntilSettled();
      profileController->setTarget("D");
      profileController->waitUntilSettled();
      profileController->setTarget("E",true);
}
