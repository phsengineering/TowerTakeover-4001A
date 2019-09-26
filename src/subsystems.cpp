#include "subsystems.hpp"

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
