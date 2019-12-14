#include "subsystems.hpp"
using namespace pros;
void redBack() {
  intakeHandler(195);
  redOkapi();
  intakeHandler(0);
  driveVel(0);
  delay(50);
  driveVel(200);
  delay(850);
  driveVel(0);
  delay(200);
  intakeR.move_absolute(-300, -75);
  intakeL.move_absolute(-300, -75);
  while(tray.get_position() < 1600) {
    tray.move_velocity(200);
  }
  tray.move_velocity(0);
  intakeHandler(0);
  delay(500);
  driveVel(-60);
  delay(2400);
  driveVel(0);
  tray.move_absolute(10, -200);
}
// void redFront() {
//   pros::delay(200);
//   clearDrive();
//   smartDrive(200, 600);
//   clearDrive();
//   while(lEncoder.get_value() > -120) {
//     driveLF.move_velocity(-50);
//     driveLB.move_velocity(-50);
//     driveRF.move_velocity(50);
//     driveRB.move_velocity(50);
//   }
//   clearDrive();
//   intakeHandler(0);
//   set_drive(HOLD);
//   pros::delay(50);
//   set_drive(COAST);
//   smartDrive(200, 950);
//   intakeHandler(0);
//   clearDrive();
//   while(lEncoder.get_value() > -48) {
//     driveLF.move_velocity(-50);
//     driveLB.move_velocity(-50);
//     driveRF.move_velocity(50);
//     driveRB.move_velocity(50);
//   }
//   driveVel(0);
//   set_drive(HOLD);
//   pros::delay(50);
//   set_drive(COAST);
//   smartDrive(200, 625);
//   driveVel(0);
//   pros::delay(100);
//   intakeHandler(-85);
//   pros::delay(700);
//   intakeHandler(0);
//   tray.tare_position();
//   int traySpeed = 180;
//   pros::delay(200);
//   while(tray.get_position() < 730) {
//     traySpeed-=5;
//     tray.move(traySpeed);
//     pros::delay(60);
//     if(traySpeed < 0) {
//       break;
//     }
//   }
//   tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
//   driveVel(-125);
//   pros::delay(1500);
//   driveVel(0);
// }
// void okapiAuton() {
//   clearDrive();
//   pros::delay(200);
//   smartDrive(300, 2500.0);
//   intakeHandler(190);
//   set_drive(HOLD);
//   pros::delay(50);
//   set_drive(COAST);
//   clearDrive();
//   smartDrive(-310, -300.0);
//   set_drive(HOLD);
//   pros::delay(50);
//   set_drive(COAST);
//   clearDrive();
//   pros::delay(100);
//   turn40();
//   smartDrive(-300, -1450.0);
//   pros::delay(100);
//   turnBack();
//   pros::delay(100);
//   smartDrive(300, 1900);
//   set_drive(HOLD);
//   pros::delay(50);
//   set_drive(COAST);
//   intakeHandler(190);
//   pros::delay(1000);
//   smartDrive(-300, -1200);
//   turn3();
//   intakeHandler(0);
// }
