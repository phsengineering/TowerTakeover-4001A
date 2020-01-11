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
    .buildOdometry(); // build an odometry chassis
auto profileController = AsyncMotionProfileControllerBuilder()
          .withLimits({1.368, 5.5, 6.155}) //max vel, max accel, max jerk
          .withOutput(chassis)
          .withLogger(std::make_shared<Logger>(
              TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
              "/ser/sout", // Output to the PROS terminal
              Logger::LogLevel::debug // Show errors and warnings
          ))
          .buildMotionProfileController();



void autonhandler() {
  profileController->generatePath({
    {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    {3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
    "A" // Profile name
  );
  profileController->setTarget("A");
  profileController->waitUntilSettled();
}
