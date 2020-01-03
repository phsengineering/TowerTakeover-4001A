#include "subsystems.hpp"
using namespace pros;
void blueBack() {
  intakeHandler(195);
  blueOkapi();
  intakeHandler(0);
  blueOkapi3();
  driveVel(0);
  delay(50);
  blueOkapi4();
  driveVel(0);
  delay(50);
  blueOkapi5();
  driveVel(0);
  delay(50);
  blueOkapi2();
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(40);
  driveVel(-55);
  delay(250);
  // intakeHandler(-95);
  // delay(300);
  intakeHandler(0);
  while(tray.get_position() < 1600) {
    tray.move_velocity(155);
  }
  tray.move_velocity(0);
  driveVel(60);
  delay(700);
  driveVel(0);
  intakeHandler(0);
  delay(10);
  driveVel(-100);
  delay(1000);
  driveVel(0);
  tray.move_absolute(0, -200);
  delay(5000);
}
