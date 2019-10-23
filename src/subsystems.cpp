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
  gyro.reset();
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
    while(obtainPositionF() < fPoint/2.0) {
      if(updateSpeed < speed) {
        updateSpeed+=30;
      }
      intakeHandler(190);
      driveVel(updateSpeed);
      pros::delay(75);
    }
    while(obtainPositionF() < fPoint) {
      if(updateSpeed > 0) {
        updateSpeed-=30;
      }
      if(updateSpeed == 0) {
        break;
      }
      driveVel(updateSpeed);
      puts(std::to_string(updateSpeed).c_str());
      pros::delay(75);
    }
    driveVel(0);
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
      driveVel(updateSpeed);
      printf("%d", obtainPositionF());
      pros::delay(75);
    }
    while(obtainPositionF() > fPoint) {
      if(updateSpeed < 0) {
        updateSpeed+=5;
      }
      driveVel(updateSpeed);
      printf("%d", obtainPositionF());
      pros::delay(75);
    }
    driveVel(0);
    if(updateSpeed == 0) {
      intakeHandler(0);
    }
  }
}
void get_gyro() {
  double value = 0;
  double lastValue = 0;
  double delta = 0;
  double absGyroValue;
  double gyroValue;
  int invert = -1;

  std::uint32_t now = pros::millis();
  //while(true) {
    value = gyro.get_value();
    if(value > -4000 && value < 4000) {
      value = value * invert;
      int delta = value - lastValue;
      lastValue = value;
      if(delta > 1800) {
        delta -=3600;
      }
      if(delta < -1800) {
        delta +=3600;
      }
      gyroValue = value;
      absGyroValue+= delta;
      printf("Abs gyro value: %d", absGyroValue);
      //delay_until(&now, TASK_DELAY_SHORT);
    }
  //}
}
void counterclockwise(int angle, int speed) {
  while(gyro.get_value() > -angle) {
    driveRF.move_velocity(speed);
    driveRB.move_velocity(speed);
    driveLF.move_velocity(-speed);
    driveLB.move_velocity(-speed);
  }
  driveVel(0);
}
void clockwise(int angle, int speed) {
  while(gyro.get_value() < angle) {
    driveRF.move_velocity(-speed);
    driveRB.move_velocity(-speed);
    driveLF.move_velocity(speed);
    driveLB.move_velocity(speed);
  }
  driveVel(0);
}
