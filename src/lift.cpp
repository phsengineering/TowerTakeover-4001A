#include "subsystems.hpp"
#include <sstream>
#include <string>
using namespace okapi;

auto liftwack = okapi::Motor(8);
auto asyncIntake = okapi::MotorGroup({20, 21});
IntegratedEncoder sesnor = IntegratedEncoder(liftwack);
auto liftControl = okapi::AsyncPosControllerBuilder().withMotor(liftwack).withGearset(AbstractMotor::gearset::red).withSensor(sesnor).withMaxVelocity(200).build();
void moveLift(int goalHeight) {
  //liftControl->setMaxVelocity(200);
  set_brake(COAST, lift);
  liftControl->setTarget(goalHeight);
}
void asyncIntakeHandler() {
  if(lift.get_position() < 200) {
    asyncIntake.moveVelocity(-100);
  }
}
