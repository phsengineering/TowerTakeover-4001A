#include "subsystems.hpp"
#include <sstream>
#include <string>
//Drivetrain
Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(5, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(6, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeL(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
void drive(int y, int r)
{
    //Scale up y and r from 127 to 12000
    y *= 11000.0 / 127.0;
    r *= 11000.0 / 127.0; //double check math

    driveLF.move_voltage(y + r);
    driveLB.move_voltage(y + r);
    driveRF.move_voltage(y - r);
    driveRB.move_voltage(y - r);
}
void intakeHandler(int speed) {
    intakeR.move_velocity(speed);
    intakeL.move_velocity(speed);
}
void trayHandler(int trayPos) {
  tray.move_velocity(trayPos);
}
void liftHandler(int liftInput) {
  lift.move_velocity(liftInput);
}
void clearDrive() {
  driveLF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();
  driveRF.tare_position();
}
double obtainPositionF() {
  double left = driveLF.get_position();
  double right = driveRF.get_position();
  return ((left+right)/2);
}
double obtainPositionB() {
  double left = driveLB.get_position();
  double right = driveRB.get_position();
  return ((left+right)/2.0);
}
void smartDrive(int speed, double fPoint, double bPoint) {
  clearDrive();
  pros::lcd::initialize();
  printf("Running");
  //printf("Max speed " + speed);
  //std::string fStr = std::to_string(fPoint);
  //printf("fPoint limit ",  fStr);

  int updateSpeed = 5;
  while(obtainPositionF() < fPoint) {
    driveLF.move_velocity(updateSpeed);
    driveLB.move_velocity(updateSpeed);
    driveRB.move_velocity(updateSpeed);
    driveRF.move_velocity(updateSpeed);
    if(obtainPositionF() < fPoint/10.0) {
      updateSpeed*=1.3;
      puts(std::to_string(updateSpeed).c_str());
    }
    else if(obtainPositionF() > fPoint/10.0 && obtainPositionF() < 2.0*(fPoint/10.0)) {
      updateSpeed*=1.5;
      puts(std::to_string(updateSpeed).c_str());
    }
    else if(obtainPositionF() > 2.0*(fPoint/10.0) && obtainPositionF() < fPoint) {
      updateSpeed*=1.6;
      puts(std::to_string(updateSpeed).c_str());
    }
    if(updateSpeed > speed) {
      updateSpeed = speed;
      puts(std::to_string(updateSpeed).c_str());
    }
    // if(updateSpeed < speed && updateSpeed % 2 == 0) {
    //   updateSpeed+=3;
    //   puts(std::to_string(obtainPositionF()).c_str());
    //
    //   //puts(std::to_string(driveRF.get_position()).c_str())
    // }
    // else {
    //   updateSpeed++;
    //   puts(std::to_string(obtainPositionF()).c_str());
    //   puts(std::to_string(updateSpeed).c_str());
    // }
    pros::delay(30);
  }
  driveLF.move_velocity(0); //allstop
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}
