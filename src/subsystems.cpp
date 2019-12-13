#include "subsystems.hpp"
#include <sstream>
#include <string>
using namespace pros;
//Drivetrain
Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(5, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(21, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeL(20, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
ADIEncoder lEncoder(5, 6);
ADIEncoder rEncoder(1, 2);
ADIEncoder mEncoder(3, 4);

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
  if(tray.get_position() < 25 && trayPos < 0) {
    trayPos = 0;
  }
  tray.move_velocity(trayPos);
}
void liftHandler(int liftInput) {
  lift.move_velocity(liftInput);
}
void driveVel(int updateSpeed) {
  driveLF.move_velocity(updateSpeed);
  driveLB.move_velocity(updateSpeed);
  driveRB.move_velocity(updateSpeed);
  driveRF.move_velocity(updateSpeed);
}
void clearDrive() {
  driveLF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();
  driveRF.tare_position();
  lEncoder.reset();
  rEncoder.reset();
}
double obtainPositionF() {
  double left = lEncoder.get_value();
  double right = rEncoder.get_value();
  return ((left+right)/2);
}
void set_brake(int mode, Motor motor) {
  switch(mode) {
    case 0:
      motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    case 1:
      motor.set_brake_mode(E_MOTOR_BRAKE_COAST);
    case 2:
      motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  }
}
void smartDrive(int speed, double fPoint) {
  clearDrive();
  if(speed > 0) {
    int updateSpeed = 0;
    clearDrive();
    while(obtainPositionF() < fPoint/2.0) {
      if(debug) {
        printf("1 update speed: %f\n", updateSpeed);
      }
      if(driveLB.get_actual_velocity() < 0 || driveRB.get_actual_velocity() < 0) {
        driveVel(0);
      }
      if(updateSpeed < speed) {
        updateSpeed+=30;// previously 30 for reference
      }
      intakeHandler(190);
      if(debug) {
        printf("Obtain position: %d\n", obtainPositionF());
      }
      driveVel(updateSpeed);
      pros::delay(75);
    }
    while(obtainPositionF() < fPoint) {
      if(debug) {
        printf("2 update speed: %f\n", updateSpeed);
      }
      if(driveLB.get_actual_velocity() < 0 || driveRB.get_actual_velocity() < 0) {
        driveVel(0);
      }
      if(updateSpeed > 0) {
        updateSpeed-=30;//previously 30 for reference
      }
      if(updateSpeed == 0) {
        break;
      }
      driveVel(updateSpeed);
      puts(std::to_string(updateSpeed).c_str());
      if(debug) {
        printf("Obtain position: %d\n", obtainPositionF());
      }
      pros::delay(75);
    }
    part++;
    driveVel(0);
    if(updateSpeed == 0) {
      intakeHandler(0);
    }
  }
  else {
    int updateSpeed = 0;
    while(obtainPositionF() > fPoint/2.0) {
      if(debug) {
        printf("3 update speed: %f\n", updateSpeed);
      }
      if(driveLB.get_actual_velocity() > 0 || driveRB.get_actual_velocity() > 0) {
        driveVel(0);
      }
      if(updateSpeed > speed) {
        updateSpeed-=10;
      }
      intakeHandler(100);
      driveVel(updateSpeed);
      if(debug) {
        printf("Obtain position: %d\n", obtainPositionF());
      }
      pros::delay(75);
    }
    while(obtainPositionF() > fPoint) {
      if(debug) {
        printf("4 update speed: %f\n", updateSpeed);
      }
      if(driveLB.get_actual_velocity() > 0 || driveRB.get_actual_velocity() > 0) {
        driveVel(0);
      }
      if(updateSpeed < 0) {
        updateSpeed+=5;
      }
      driveVel(updateSpeed);
      if(debug) {
        printf("Obtain position: %d\n", obtainPositionF());
      }
      pros::delay(75);
    }
    part++;
    driveVel(0);
    if(updateSpeed == 0) {
      intakeHandler(0);
    }
  }
}
void correct(int time, int speed, bool counter) {
  if(counter) {
    driveRF.move_velocity(speed);
    driveRB.move_velocity(speed);
    driveLF.move_velocity(-speed);
    driveLB.move_velocity(-speed);
    pros::delay(time);
  }
  else {
    driveRF.move_velocity(speed);
    driveRB.move_velocity(speed);
    driveLF.move_velocity(-speed);
    driveLB.move_velocity(-speed);
    pros::delay(time);
  }
  driveVel(0);
}
void set_drive(int mode) {
  Motor driveGroup [4] = { driveLB, driveLF, driveRF, driveRB };
  for(int i = 0; i < 4; i++) {
    set_brake(mode, driveGroup[i]);
  }
}
void positionTrack() {

    // Can multiply these by a scalar to get the values in inches, or whatever unit you'd like your x and y coordinates to be in.
    double dR = rEncoder.get_value() - lastEncoderValueR;
    double dL = lEncoder.get_value() - lastEncoderValueL;
    double dM = mEncoder.get_value() - lastEncoderValueM;

    double dS = (dR + dL) / 2.0;  // Distance robot traveled since last checked.
    double dTheta = (dM*556.0) / (chassisWidth);  // Change in angle robot turned since last checked. Where chassisWidth is the distance between your left and right tracking wheels.

    double avgTheta = theta + dTheta / 2.0;  // Angle robot is assumed to have been facing when moving dS.

    // Change in x and y position since last checked.
    double dX = dS * cos(avgTheta) + dM * sin(avgTheta);
    double dY = dS * sin(avgTheta) - dM * cos(avgTheta);

    // Update current robot position.
    x += dX;
    y += dY;
    theta += dTheta;
    if (debug) {
      printf("X Position: %f\n", x);
      printf("Middle encoder: %d\n", mEncoder.get_value());
      printf("Y Position: %f\n", y);
      printf("Theta disp Position: %f\n", theta);
    }
    lastEncoderValueL = lEncoder.get_value();
    lastEncoderValueR = rEncoder.get_value();
    lastEncoderValueM = mEncoder.get_value();
}
