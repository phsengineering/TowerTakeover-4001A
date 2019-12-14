#include "subsystems.hpp"
using namespace pros;
void blueBack() {
  intakeHandler(195);
  blueOkapi();
  intakeHandler(0);
  blueOkapi2();
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeHandler(-95);
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
  driveVel(-60);
  delay(2400);
  driveVel(0);
  tray.move_absolute(10, -200);
}
