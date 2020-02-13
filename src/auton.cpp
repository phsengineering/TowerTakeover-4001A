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

void pidtest(){
    //chassis->turnAngle(90_deg);
    chassis->moveDistance(-2_ft);
}

void autonhandler(int auton) { //check global integer auton
   switch(auton) {
     case 0:
       protecc(false); //red protected zone (5)
       //pidtest();
     case 1:
       protecc(true); //blue protected zone (5)
     case 2:
       notprotecc(false); //red unprotected (6-7)
     case 3:
       notprotecc(true); //blue unprotected (6-7)
      case 4:
        back5(false);
      case 5:
        blueback5();
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
  chassis->driveToPoint({28_in, 0_in}); //pull the first two cubes in
  chassis->setMaxVelocity(275);
  if(blue) {
    chassis->turnAngle(50_deg); //blue positive then negative
  }
  else {
    chassis->turnAngle(-50_deg); //red negative then positive
  }
  intakeHandler(30); //lower intake speed while moving to second line up
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-24.5_in); //move to second line up
  chassis->setMaxVelocity(275);
  delay(50);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-50_deg);
  }
  else {
    chassis->turnAngle(50_deg); //60 deg
  }
  intakeHandler(180); //run intakes back to full for second line up
  chassis->setMaxVelocity(190);
  chassis->setState(OdomState{0_ft, 0_ft});
  chassis->driveToPoint({36.5_in, 0_in}); //collect the next 4 cubes
  delay(75);
  intakeHandler(20); //lower speed to reduce motor strain after run through
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-30.5_in);
  intakeHandler(0);
  set_brake(BRAKE, intakeR);
  set_brake(BRAKE, intakeL);
  //chassis->waitUntilSettled();
  delay(50);
  chassis->setMaxVelocity(150);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-125_deg);
  }
  else {
    chassis->turnAngle(125_deg); //60 deg
  }
  driveVel(0);
  driveVel(120);
  delay(500);
  driveVel(0);
  intakeHandler(-110);
  delay(200);
  intakeHandler(0);
  set_brake(COAST, intakeR);
  set_brake(COAST, intakeL);
  while(tray.get_position() < 1725) {
    tray.move_velocity(100);
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
  while (true) {
    auto state = chassis->getState();
    std::cout << state.str() << std::endl;
    pros::delay(50);
  }
}
void back5(bool blue) {
  intakeHandler(195);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(39_in);
  pros::delay(100);
  intakeHandler(0);
  chassis->moveDistance(-22_in);
  chassis->waitUntilSettled();
  chassis->turnAngle(125_deg); //red
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeHandler(-110);
  delay(350);
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
void blueback5() {
  intakeHandler(195);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(38_in);
  pros::delay(100);
  intakeHandler(0);
  chassis->moveDistance(-21_in);
  chassis->waitUntilSettled();
  chassis->turnAngle(-125_deg); //red
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeHandler(-110);
  delay(350);
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

  //profileController->setTarget("A");

}
