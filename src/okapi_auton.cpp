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

okapi::Controller master;
