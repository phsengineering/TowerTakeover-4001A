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
static int part = 0;
static int auton = 1;
static bool debug = true;
void autonhandler();
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
void correct(int time, int speed, bool counter);
