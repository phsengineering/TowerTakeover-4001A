#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
.withMotors({4, 3}, {2, 1}) // pass motors to odomchassiscontroller builder
.withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0058, 0.00057, 0.00025 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
     )
.withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true}) //pass sensors for left, right, middle
.withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 5_in, 4.3125_in, 2.75_in}, quadEncoderTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
.withOdometry() // use the same scales as the chassis (above)
.withLogger(std::make_shared<Logger>(
    TimeUtilFactory::createDefault().getTimer(),
    "/ser/sout", // Output to the PROS terminal
    Logger::LogLevel::debug // Show all feedback
))
.withMaxVelocity(300) //cap velocity at 300 to reduce jerk and cut down on PID correction time
.buildOdometry(); // build an odometry chassis
auto test = ChassisControllerBuilder()

	.withMotors({4, 3}, {2, 1}) // left motor is 1, right motor is 2 (reversed)
	// green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
	.withDimensions(
	  AbstractMotor::gearset::blue,
      {{3.25_in, 8.5_in}, imev5BlueTPR * (5.0 / 3.0)}
    )
	.withSensors(
			{'E', 'F', true},
			{'A', 'B', false},
      {'C', 'D', true}
	)

	.withOdometry({{2.75_in, 5_in}, quadEncoderTPR})
	.buildOdometry();
auto profileController = AsyncMotionProfileControllerBuilder()
  .withOutput(test->getModel(), {{3.25_in, 8.5_in}, imev5BlueTPR * (5.0 / 3.0)}, {AbstractMotor::gearset::blue, (5.0 / 3.0)})
  .withLimits({.6, .75, 10})
  .buildMotionProfileController();
void pidtest(){
    profileController->generatePath({{30_in, 0_ft, 0_deg}, {20_in, 1_ft, 90_deg}, {20_in, 2.75_ft, 90_deg}}, "A"); //originally 28 in
    intakeHandler(195);
    chassis->setMaxVelocity(250);
    auto pos = chassis->getState();
    chassis->driveToPoint({30_in, 0_ft});
    pos = chassis->getState();
    std::cout << pos.str() + " :Moved forward\n";
    profileController->setTarget("A", true, true);
    profileController->waitUntilSettled();
    pos = chassis->getState();
    std::cout << pos.str() + " After S curve\n";
    delay(500);
    chassis->turnToAngle(0_deg);
    //debugger();
    pos = chassis->getState();
    std::cout << pos.str() + " After correction turn\n";
    chassis->setState({0_ft, 0_ft});
    chassis->driveToPoint({42_in, 0_in});
    pos = chassis->getState();
    std::cout << pos.str() + " :Moved forward again\n";

    chassis->moveDistance(-29_in);
    chassis->turnAngle(-135_deg); //red
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
    while(tray.get_position() < 1700) {
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
    delay(50000);
}

void autonhandler(int auton) { //check global integer auton
   switch(auton) {
      case 0:
        pidtest(); //testing auton
      case 1:
        protecc(false); //red protected zone (5)
      case 2:
        protecc(true); //blue protected zone (5)
      case 3:
        notprotecc(false); //red unprotected (6-7)
      case 4:
        notprotecc(true); //blue unprotected (6-7)
      case 5:
        back5(false); //back 5 red
      case 6:
        blueback5(); //blue 5
      case 7:
        prog(); //prog skills
      case 8:
        back6(false); //back 6 red (unstable)
      case 9:
        back6(true); //back 6 blue (unstable)
   }
}
void protecc(bool blue) {
  intakeHandler(200);
  chassis->setMaxVelocity(300);
  chassis->moveDistance(19_in);
  chassis->setMaxVelocity(250);
  delay(75);
  if(blue) {
    chassis->turnAngle(-93_deg);
  }
  else {
    chassis->turnAngle(93_deg);
  }
  chassis->setMaxVelocity(300);
  chassis->moveDistance(32.5_in);
  delay(300);
  intakeHandler(15);
  chassis->moveDistance(-31_in);
  chassis->setMaxVelocity(240);
  delay(75);
  if(blue) {
    chassis->turnAngle(-138_deg);
  }
  else {
    chassis->turnAngle(138_deg);
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
  //profileController->moveTo({{0_in, 0_in, 0_deg}, {30_in, 0_in, 0_deg}}, false, false);
  chassis->moveDistance(30_in); //pull the first two cubes in
  chassis->setMaxVelocity(400);
  if(blue) {
    chassis->turnAngle(40_deg); //blue positive then negative
  }
  else {
    chassis->turnAngle(-40_deg); //red negative then positive
  }
  intakeHandler(30); //lower intake speed while moving to second line up
  chassis->setMaxVelocity(400);
  chassis->moveDistance(-30_in); //move to second line up
  delay(50);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-40_deg);
  }
  else {
    chassis->turnAngle(40_deg); //60 deg
  }
  intakeHandler(180); //run intakes back to full for second line up
  chassis->setMaxVelocity(190);
  chassis->moveDistance(36.5_in); //collect the next 4 cubes
  delay(75);
  intakeHandler(20); //lower speed to reduce motor strain after run through
  chassis->setMaxVelocity(300);
  chassis->moveDistance(-27_in);
  intakeHandler(0);
  set_brake(BRAKE, intakeR);
  set_brake(BRAKE, intakeL);
  delay(50);
  chassis->setMaxVelocity(150);
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-130_deg);
  }
  else {
    chassis->turnAngle(130_deg); //60 deg
  }
  driveVel(0);
  driveVel(150);
  delay(750);
  driveVel(0);
  intakeHandler(-110);
  delay(200);
  intakeHandler(0);
  set_brake(COAST, intakeR);
  set_brake(COAST, intakeL);
  while(tray.get_position() < 1700) {
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
  intakeHandler(200);
  chassis->setMaxVelocity(200);
  chassis->moveDistance(43_in);
  delay(100);
  intakeHandler(20);
  delay(75);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(-29_in);
  chassis->turnAngle(135_deg); //red
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
  while(tray.get_position() < 1700) {
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
  intakeHandler(200);
  chassis->setMaxVelocity(200);
  chassis->moveDistance(43_in);
  delay(100);
  intakeHandler(20);
  delay(75);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(-29_in);
  chassis->turnAngle(-135_deg); //red
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
  while(tray.get_position() < 1700) {
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
void back6(bool blue) {
  intakeHandler(200);
  chassis->setMaxVelocity(200);
  chassis->moveDistance(42_in);
  delay(100);
  if(blue) {
    chassis->turnAngle(40_deg);
  }
  else {
    chassis->turnAngle(-40_deg);
  }
  chassis->moveDistance(9_in);
  delay(200);
  intakeHandler(40);
  set_brake(BRAKE, intakeR);
  set_brake(BRAKE, intakeL);
  chassis->moveDistance(-9_in);
  if(blue) {
    chassis->turnAngle(-40_deg);
  }
  else {
    chassis->turnAngle(40_deg);
  }
  intakeHandler(0);
  delay(75);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(-23.5_in);
  if(blue) {
    chassis->turnAngle(-130_deg);
  }
  else {
    chassis->turnAngle(130_deg); //red
  }
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  set_brake(COAST, intakeR);
  set_brake(COAST, intakeL);
  intakeHandler(-110);
  delay(350);
  intakeHandler(0);
  while(tray.get_position() < 1700) {
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
  intakeHandler(200);
  chassis->setMaxVelocity(200);
  chassis->moveDistance(42_in);
  delay(100);
  chassis->turnAngle(-40_deg);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeHandler(40);
  set_brake(BRAKE, intakeR);
  set_brake(BRAKE, intakeL);
  chassis->moveDistance(-9_in);
  chassis->turnAngle(40_deg);
  intakeHandler(0);
  delay(75);
  chassis->setMaxVelocity(250);
  chassis->moveDistance(-23.5_in);
  chassis->turnAngle(130_deg); //red
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  set_brake(COAST, intakeR);
  set_brake(COAST, intakeL);
  intakeHandler(-110);
  delay(350);
  intakeHandler(0);
  while(tray.get_position() < 1700) {
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
void debugger() {
  while(true) {}
}
