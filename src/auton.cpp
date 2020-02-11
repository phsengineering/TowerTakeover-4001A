#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // pass motors to odomchassiscontroller builder
    .withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0061, 0.00057, 0.000212 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
     )

    .withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true}) //pass sensors for left, right, middle
    .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 5.125_in, 4.3125_in, 2.75_in}, quadEncoderTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
    .withOdometry() // use the same scales as the chassis (above)
    .withLogger(std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(),
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show all feedback
    ))
    .withMaxVelocity(300) //cap velocity at 300 to reduce jerk and cut down on PID correction time
    .buildOdometry(); // build an odometry chassis
auto fallBack = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // pass motors to odomchassiscontroller builder
    .withGains(
         { 0.0011, 0, 0.0 }, // Distance controller gains
         { 0.00315, 0.00, 0.00 }, // Turn controller gains
         { 0.00022, 0, 0.0000 }  // Angle controller gains
     )
    .withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true}) //pass sensors for left, right, middle
    .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 4.25_in, 4.375_in, 2.75_in}, quadEncoderTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
    .withOdometry() // use the same scales as the chassis (above)
    .withLogger(std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(),
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show all feedback
    ))
    .withMaxVelocity(300) //cap velocity at 300 to reduce jerk and cut down on PID correction time
    .buildOdometry(); // build an odometry chassis
auto profileController = AsyncMotionProfileControllerBuilder() //currently unused because open loop
    .withLimits({1.368, 5.5, 6.155}) //max vel, max accel, max jerk
    .withOutput(chassis)
    .buildMotionProfileController();
void odomtest() { //unused due to issues with turns/scales
    chassis->driveToPoint({3_ft, 0_ft});
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({-1_ft, 0_ft}, true);
    chassis->setState(OdomState{0_ft, 0_ft});
    chassis->driveToPoint({0_ft, -2_ft});
}


void autonhandler(int auton) { //check global integer auton
   switch(auton) {
     case 0:
       protecc(false); //red protected zone (5)
     case 1:
       protecc(true); //blue protected zone (5)
     case 2:
       notprotecc(false); //red unprotected (6-7)
     case 3:
       notprotecc(true); //blue unprotected (6-7)
      case 4:
        back5(false); //red back 5 (uses old config)
      case 5:
        back5(true); //blue back 5 (also uses old config)
      case 6:
        prog();
   }
}
void protecc(bool blue) {
  intakeHandler(200);
  chassis->setMaxVelocity(300);
  chassis->moveDistance(19_in);
  chassis->setMaxVelocity(250);
  delay(75);
  if(blue) {
    chassis->turnAngle(-90_deg);
  }
  else {
    chassis->turnAngle(90_deg);
  }
  chassis->setMaxVelocity(300);
  chassis->moveDistance(32.5_in);
  delay(300);
  intakeHandler(15);
  chassis->moveDistance(-31_in);
  chassis->setMaxVelocity(240);
  delay(75);
  if(blue) {
    chassis->turnAngle(-135_deg);
  }
  else {
    chassis->turnAngle(135_deg);
  }
  driveVel(150);
  delay(600);
  driveVel(0);
  intakeHandler(-110);
  delay(380);
  intakeHandler(0);
  while(tray.get_position() < 1600) {
    tray.move_velocity(200);
  }
  tray.move_velocity(0);
  driveVel(100);
  delay(200);
  driveVel(0);
  intakeHandler(0);
  delay(500);

  driveVel(-120);
  tray.move_absolute(0, -200);
  delay(2400);
  driveVel(0);
  delay(5000);



  delay(9914);
}
void notprotecc(bool blue) {
  set_brake(COAST, tray); //make tray coast to cut down on motor strain
  intakeHandler(180); //run intakes
//  chassis->setMaxVelocity();
  chassis->moveDistance(27_in); //pull the first two cubes in
  chassis->setMaxVelocity(275);
  delay(850);
  if(blue) {
    chassis->turnAngle(53_deg); //blue positive then negative
  }
  else {
    chassis->turnAngle(-53_deg); //red negative then positive
  }
  intakeHandler(30); //lower intake speed while moving to second line up
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-28.5_in); //move to second line up
  chassis->setMaxVelocity(275);
  delay(50);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-53_deg);
  }
  else {
    chassis->turnAngle(53_deg); //60 deg
  }
  intakeHandler(180); //run intakes back to full for second line up
  chassis->setMaxVelocity(190);
  chassis->moveDistance(36.5_in); //collect the next 4 cubes
  delay(40);
  intakeHandler(0); //lower speed to reduce motor strain after run through
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-29_in);
  chassis->waitUntilSettled();
  delay(50);
  chassis->setMaxVelocity(150);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-137_deg);
  }
  else {
    chassis->turnAngle(137_deg); //60 deg
  }
  driveVel(0);
  driveVel(300);
  delay(550);
  driveVel(0);
  intakeHandler(-110);
  delay(150);
  intakeHandler(0);
  while(tray.get_position() < 1590) {
    tray.move_velocity(170);
  }
  tray.move_velocity(0);
  intakeHandler(0);
  delay(100);

  driveVel(-120);
  tray.move_absolute(0, -200);
  delay(2400);
  driveVel(0);
  delay(5000);

}
void back5(bool blue) {
  intakeHandler(195);
  fallBack->setMaxVelocity(250);
  fallBack->moveDistance(39_in);
  pros::delay(100);
  intakeHandler(0);
  fallBack->moveDistance(-22_in);
  if(blue) {
      fallBack->turnAngle(-155_deg);
  }
  else {
      fallBack->turnAngle(155_deg);
  }
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeHandler(-110);
  delay(300);
  intakeHandler(0);
  while(tray.get_position() < 1600) {
    tray.move_velocity(190);
  }
  tray.move_velocity(0);
  driveVel(100);
  delay(200);
  driveVel(0);
  intakeHandler(0);
  delay(500);

  driveVel(-100);
  delay(2400);
  driveVel(0);
  tray.move_absolute(10, -200);
  delay(5000);
}
void prog() {
  set_brake(COAST, tray); //make tray coast to cut down on motor strain
  intakeHandler(180); //run intakes
//  chassis->setMaxVelocity();
  chassis->moveDistance(27_in); //pull the first two cubes in
  chassis->setMaxVelocity(275);
  delay(750);
  chassis->turnAngle(-50_deg); //red negative then positive
  intakeHandler(30); //lower intake speed while moving to second line up
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-28.5_in); //move to second line up
  chassis->setMaxVelocity(275);
  delay(50);
  chassis->turnAngle(50_deg); //60 deg
  intakeHandler(180); //run intakes back to full for second line up
  chassis->setMaxVelocity(190);
  chassis->moveDistance(36.5_in); //collect the next 4 cubes
  delay(40);
  intakeHandler(0); //lower speed to reduce motor strain after run through
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-29_in);
  chassis->waitUntilSettled();
  delay(50);
  chassis->setMaxVelocity(150);
  chassis->turnAngle(132_deg); //60 deg

  driveVel(0);
  driveVel(300);
  delay(550);
  driveVel(0);
  intakeHandler(-110);
  delay(150);
  intakeHandler(0);
  while(tray.get_position() < 1590) {
    tray.move_velocity(190);
  }
  tray.move_velocity(0);
  intakeHandler(0);
  delay(500);
  chassis->moveDistance(-14_in);
  delay(500);
  tray.move_absolute(0, -200);
  chassis->turnAngle(132_deg);
  intakeHandler(195);
  chassis->moveDistance(2.6_ft);
  intakeHandler(-80);
  pros::delay(650);
  intakeHandler(0);
  chassis->moveDistance(-9_in);
  lift.move_absolute(205, 100);
  chassis->moveDistance(6_in);
  intakeHandler(-100);
  delay(1001);
  intakeHandler(0);
  chassis->stop();
}
