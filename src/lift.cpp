#include "subsystems.hpp"
#include <sstream>
#include <string>
void resetLift() {
  tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
  lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
  while(lift.get_position() > 0 || tray.get_position() > 0) {
    lift.move_velocity(-70);
    pros::delay(200);
    tray.move_velocity(-100);
    if(tray.get_position() < 2) {
      tray.move_velocity(0);
    }
    if(lift.get_position() < 0) {
      lift.move_velocity(0);
    }
    if(tray.get_position() < 2 && lift.get_position() < 0) {
      break;
    }
    pros::delay(50);
  }
}
void moveLift() {
  tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
  lift.set_brake_mode(E_MOTOR_BRAKE_COAST);
  while(lift.get_position() < 205 || tray.get_position() < 200) {
    lift.move_velocity(70);
    pros::delay(100);
    tray.move_velocity(175);
    if(tray.get_position() > 205) {
      tray.move_velocity(0);
    }
    if(lift.get_position() > 200) {
      lift.move_velocity(0);
    }
    pros::delay(50);
  }
}
