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
ADIEncoder lEncoder(1, 2, false);
ADIEncoder rEncoder(3, 4, true);
ADIGyro gyro(5);
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
  lEncoder.reset();
  rEncoder.reset();
  gyro.reset();
}
double obtainPositionF() {
  double left = lEncoder.get_value();
  double right = rEncoder.get_value();
  return ((left+right)/2);
}
void smartDrive(int speed, double fPoint) {
  clearDrive();
  if(speed > 0) {
    int updateSpeed = 0;
    while(obtainPositionF() < fPoint/2.0) {
      if(updateSpeed < speed) {
        updateSpeed+=30;
      }
      intakeHandler(190);
      driveLF.move_velocity(updateSpeed);
      driveLB.move_velocity(updateSpeed);
      driveRB.move_velocity(updateSpeed);
      driveRF.move_velocity(updateSpeed);
      puts(std::to_string(updateSpeed).c_str());
      pros::delay(75);
    }
    while(obtainPositionF() < fPoint) {
      if(updateSpeed > 0) {
        updateSpeed-=30;
      }
      if(updateSpeed == 0) {
        break;
      }
      driveLF.move_velocity(updateSpeed);
      driveLB.move_velocity(updateSpeed);
      driveRB.move_velocity(updateSpeed);
      driveRF.move_velocity(updateSpeed);
      puts(std::to_string(updateSpeed).c_str());
      pros::delay(75);
    }
    driveLF.move_velocity(0); //allstop
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveRF.move_velocity(0);
    if(updateSpeed == 0) {
      intakeHandler(0);
    }
  }
  else {
    int updateSpeed = 0;
    while(obtainPositionF() > fPoint/2.0) {
      if(updateSpeed > speed) {
        updateSpeed-=10;
      }
      intakeHandler(190);
      driveLF.move_velocity(updateSpeed);
      driveLB.move_velocity(updateSpeed);
      driveRB.move_velocity(updateSpeed);
      driveRF.move_velocity(updateSpeed);
      printf("%d", obtainPositionF());
      pros::delay(75);
    }
    while(obtainPositionF() > fPoint) {
      if(updateSpeed < 0) {
        updateSpeed+=5;
      }
      driveLF.move_velocity(updateSpeed);
      driveLB.move_velocity(updateSpeed);
      driveRB.move_velocity(updateSpeed);
      driveRF.move_velocity(updateSpeed);
      printf("%d", obtainPositionF());
      pros::delay(75);
    }
    driveLF.move_velocity(0); //allstop
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
    driveRF.move_velocity(0);
    if(updateSpeed == 0) {
      intakeHandler(0);
    }
  }
}
