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
extern ADIEncoder mEncoder;
static int part = 0;
static int auton = 7; //runs case 7
static double chassisWidth = 5.0;
static bool debug = false;
static double lastEncoderValueL = 0;
static double lastEncoderValueM = 0;
static double lastEncoderValueR = 0;
static double x;
static double y;
static double theta;
void autonhandler();
void okapilibauton();
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
void turnright(float turn);
void obtainPositionRaw();
void positionTrack();
