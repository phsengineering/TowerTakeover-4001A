#pragma once
#include "main.h"

extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;
extern Motor tray;
extern Motor intakeR;
extern Motor intakeL;
extern Motor lift;
extern ADIEncoder lEncoder;
extern ADIEncoder rEncoder;
extern ADIGyro gyro;
void autonhandler();
void pidController();
void drive(int y, int r);
void intakeHandler(int speed);
void trayHandler(int trayPos);
void liftHandler(int liftInput);
void driveVel(int updateSpeed);
void set_brake(int mode, Motor motor);
void clearDrive();
double obtainPositionF();
double obtainPositionB();
void smartDrive(int speed, double fPoint);
double increasing_speed (double starting_point, double current_position);
double decreasing_speed (double ending_point, double current_position);
void forward (double distanceIn, double maxVelocity);
void forward (double distanceIn);
void clockwise(int angle, int speed);
void counterclockwise(int angle, int speed);
void get_gyro();
