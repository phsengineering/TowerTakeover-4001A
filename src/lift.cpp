#include "subsystems.hpp"
#include <sstream>
#include <string>
using namespace okapi;

auto liftwack = okapi::Motor(8);
auto asyncIntake = okapi::MotorGroup({20, 21});
IntegratedEncoder sesnor = IntegratedEncoder(liftwack);
auto liftControl = AsyncPosControllerBuilder().withMotor(liftwack).withGearset(AbstractMotor::gearset::red).withSensor(sesnor).withMaxVelocity(200).build();
void moveLift(int goalHeight) { //move w/ async controller without awkward namespace issues or synchronous behavior
  set_brake(COAST, lift);
  liftControl->setTarget(goalHeight);
}
void autonLift(int goalHeight) {
  set_brake(COAST, lift); //release hold on lift in order to move it with async controller
  liftControl->setTarget(goalHeight); //move w/ async controller
  liftControl->waitUntilSettled();
}
void asyncIntakeHandler() {
  intakeL.move_absolute(-50, -200);
  intakeR.move_absolute(-50, -200);
}
void asyncIntakeHandler2() {
  if (tray.get_position() < 50) {
    intakeHandler(150);
  } else {
    intakeHandler(0);
  }
}
void asynctrayHandler() {
  tray.move_absolute(0, -200);
}
