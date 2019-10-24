#include "subsystems.hpp"
void autonhandler() {
  clearDrive();
  smartDrive(350, 1700.0);
  driveVel(0);
  clearDrive();
  pros::delay(25);
  while(lEncoder.get_value() > -40) {
    driveRF.move_velocity(100);
    driveRB.move_velocity(100);
    driveLB.move_velocity(-100);
    driveLF.move_velocity(-100);
    pros::delay(15);
  }
}
