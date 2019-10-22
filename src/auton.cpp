#include "subsystems.hpp"
void autonhandler() {
  clearDrive();
  smartDrive(300, 2500.0);
  smartDrive(-300, -600.0);
  counterclockwise(250, 150);
  smartDrive(-710, -980.0);
  clockwise(7, 150);
  driveRF.move_velocity(150);
  driveRB.move_velocity(150);
  driveLF.move_velocity(-150);
  driveLB.move_velocity(-150);
  pros::delay(20);
  smartDrive(300, 1650);
  intakeHandler(195);
  smartDrive(-300, -1550);
  gyro.reset();
  clockwise(690, 150);
  driveVel(.4*300);
  pros::delay(500);
  driveVel(0);
  intakeHandler(-75);
  pros::delay(500);
  intakeHandler(0);
  int updateSpeed = 100;
  while(tray.get_position() < 600) {
    if(tray.get_position() > 200) {
      updateSpeed = 50;
    }
    tray.move_velocity(updateSpeed);
  }
  smartDrive(-300, -200);
}
