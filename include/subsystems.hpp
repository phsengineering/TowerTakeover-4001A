#pragma once
#include "main.h"
using namespace pros;
extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern okapi::Controller master;
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
void drive(int y, int r);
void intakeHandler(int speed);
void trayHandler(int trayPos);
void liftHandler(int liftInput);
void set_brake(int mode, Motor motor);
void set_drive(int mode);
void clearDrive();
void debug();
void autonhandler();
