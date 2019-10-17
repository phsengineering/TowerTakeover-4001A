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
void autonhandler();
void drive(int y, int r);
void intakeHandler(int speed);
void trayHandler(int trayPos);
void liftHandler(int liftInput);
//int velocityCurve(int speedOrig, int maxSpeed);
double obtainPositionF();
double obtainPositionB();
void smartDrive(int speed, double fPoint);
