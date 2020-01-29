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
    chassis->moveDistance(2_ft);
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
        back5(false);
      case 5:
        blueback5();
      case 6:
        prog();
   }
}
void protecc(bool blue) {

    autonLift(210); //move lift up and out of the way
    set_brake(HOLD, lift); //keep lift locked through first movement
    pros::delay(200);
    chassis->moveDistance(43.5_in);
    chassis->stop();
    chassis->waitUntilSettled();
    if(blue) {
      chassis->turnAngle(-90_deg); //turn to face the four stack
    }
    else {
      chassis->turnAngle(90_deg);
    }
    chassis->waitUntilSettled();
    set_brake(BRAKE, lift); //unlock lift
    lift.move_absolute(-5, -30); //move lift down to pull cubes in
    intakeHandler(200); //pull cubes in
    pros::delay(250); //keep pulling them in for 250 ms
    chassis->moveDistance(5.5_in); //move forward to collect every cube available
    pros::delay(750);
    intakeHandler(0);
    chassis->waitUntilSettled();
    if(blue) {
      chassis->turnAngle(-130_deg); //turn back to face protected zone
    }
    else {
      chassis->turnAngle(130_deg);
    }
    chassis->waitUntilSettled();
    intakeHandler(200); //run intakes to get the last cube on the way to the zone
    chassis->setMaxVelocity(500); //release speed cap
    chassis->moveDistance(34_in); //move to zone
    chassis->waitUntilSettled();
    pros::delay(100);
    intakeHandler(0);
    driveVel(100);
    pros::delay(300);
    driveVel(0);
    intakeHandler(-110); //pull cubes down a bit
    delay(350);
    intakeHandler(0);
    while(tray.get_position() < 1600) { //deploy 5 stack
      tray.move_velocity(190);
    }
    tray.move_velocity(0);
    delay(100);
    driveVel(-250); //pull back from stack on time
    delay(1000);
    driveVel(0);
    tray.move_absolute(10, -200);
    delay(5000); //prevent further instructions from running
}
void notprotecc(bool blue) {
  set_brake(COAST, tray); //make tray coast to cut down on motor strain
  intakeHandler(180); //run intakes
  chassis->moveDistance(26_in); //pull the first two cubes in
  if(blue) {
    chassis->turnAngle(50_deg); //blue positive then negative
  }
  else {
    chassis->turnAngle(-50_deg); //red negative then positive
  }
  intakeHandler(50); //lower intake speed while moving to second line up
  chassis->moveDistance(-27_in); //move to second line up
  if(blue) { //cancel out initial turn
    chassis->turnAngle(-50_deg);
  }
  else {
    chassis->turnAngle(50_deg); //60 deg
  }
  intakeHandler(180); //run intakes back to full for second line up

  chassis->moveDistance(30.5_in); //collect the next 4 cubes
  intakeHandler(0); //lower speed to reduce motor strain after run through
  if(blue) {
    chassis->turnAngle(-160_deg); //turn back to the unprotectedzone
  }
  else {
    chassis->turnAngle(160_deg);
  }
  intakeHandler(0);
  driveVel(320); //deploy on time
  delay(1300);
  driveVel(0);
  intakeHandler(-110);
  delay(350);
  intakeHandler(0);
  tray.move_absolute(1600, 165);
  delay(1500);
  intakeHandler(0);
  driveVel(125);
  delay(200);
  driveVel(0);
  delay(250);
  driveVel(-300);
  delay(1000);
  driveVel(0);
  chassis->stop();
  intakeHandler(0);
  tray.move_velocity(0);

  delay(5000);
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
  tray.move_absolute(10, -200);
  chassis->moveDistance(-14_in);
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
