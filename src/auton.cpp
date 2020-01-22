#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // left motor is 1, right motor is 2 (reversed)
    .withGains(
         { 0.0011, 0, 0.0 }, // Distance controller gains
         { 0.00315, 0.00, 0.00 }, // Turn controller gains
         { 0.00022, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    .withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true})
    .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 4.25_in, 4.375_in, 2.75_in}, quadEncoderTPR})
    .withOdometry() // use the same scales as the chassis (above)
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
//auto liftControl = okapi::AsyncPosControllerBuilder().withMotor(liftwack).withGearset(AbstractMotor::gearset::red).withSensor(sesnor).withMaxVelocity(200).build();
void odomtest() {
    chassis->driveToPoint({3_ft, 0_ft});
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({-1_ft, 0_ft}, true);
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({0_ft, -2_ft});
}
void autonhandler() {
  switch(auton) {
    case 0:
      protecc(false);
    case 1:
      protecc(true);
  }
}
void protecc(bool blue) {
    autonLift(210);
    set_brake(HOLD, lift);
    pros::delay(400);
    chassis->moveDistance(43.5_in);
    chassis->waitUntilSettled();
    if(blue) {
      chassis->turnAngle(-120_deg);
    }
    else {
      chassis->turnAngle(120_deg);
    }
    chassis->waitUntilSettled();
    set_brake(BRAKE, lift);
    lift.move_absolute(-5, -30);
    intakeHandler(200);
    chassis->moveDistance(5.5_in);
    pros::delay(1500);
    intakeHandler(0);
    chassis->waitUntilSettled();
    if(blue) {
      chassis->turnAngle(-172_deg);
    }
    else {
      chassis->turnAngle(172_deg);
    }
    chassis->waitUntilSettled();
    intakeHandler(200);
    chassis->setMaxVelocity(500);
    chassis->moveDistance(34_in);
    chassis->waitUntilSettled();
    pros::delay(100);
    intakeHandler(0);
    driveVel(100);
    pros::delay(300);
    driveVel(0);
    intakeHandler(-95);
    delay(300);
    intakeHandler(0);
    while(tray.get_position() < 1600) {
      tray.move_velocity(190);
    }
    tray.move_velocity(0);
    delay(100);
    driveVel(-250);
    delay(1000);
    driveVel(0);
    tray.move_absolute(10, -200);
    delay(5000);
}
