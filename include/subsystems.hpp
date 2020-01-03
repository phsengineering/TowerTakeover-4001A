#pragma once
#include "main.h"
using namespace pros;
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
enum brake_modes {HOLD = 0, COAST = 1, BRAKE = 2};
static int part = 0;
static int auton = 1; //runs case 7
static double chassisWidth = 2.5;
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
void set_drive(int mode);
void clearDrive();
double obtainPositionF();
void smartDrive(int speed, double fPoint);
void correct(int time, int speed, bool counter);
void turnright(float turn);
void positionTrack();
void redFront();
void redBack();
void blueFront();
void blueBack();
void okapiAuton();
void testFwd();
void redOkapi();

void generatePath(std::initializer_list<okapi::PathfinderPoint> iwaypoints,
const std::string& ipathId,
const okapi::PathfinderPoint& ilimits);
