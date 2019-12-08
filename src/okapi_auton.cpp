//#include "subsystems.hpp"
#include "okapi/api.hpp"
using namespace okapi;

const double drivekP = 0.000;
const double drivekI = 0.0000;
const double drivekD = 0.0000;
const double drivekBias = 0;
const double maxVel = 5.00;
const double maxAccel = 1.00;
const double maxJerk = 9.00;
const double odomTrack = 0.0;
const double odomMiddleDist = 0.0;
const double drivemoveThreshold = 0.0;
const double driveturnThreshold = 0.0;
//const double driveVelDelta = 0.001;
Logger logger = Logger(TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", Logger::LogLevel::debug);
auto odom = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1})
    .withGearset({AbstractMotor::gearset::blue, 5/3})
    .withSensors(ADIEncoder('E', 'F', false), ADIEncoder('A', 'B', false), ADIEncoder('C', 'D', false))
    .withDimensions({{2.75, 5.125, 4.25, 2.75}, imev5BlueTPR})
    //.withGearset(5.0/3.0)
    .withGains(
        { 0.001, 0, 0.0000 }, // Distance controller gains
        { 0.001, 0, 0.0000 }, // Turn controller gains
        { 0.0001, 0, 0.0000 }  // Angle controller gains (helps drive straight)
    )
    //.withOdometry({2.75, odomTrack, odomMiddleDist, 2.75}, drivemoveThreshold, driveturnThreshold)
    .withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_ft, 0_deg, 0.00001_mps)
    //.withLogger()
    .buildOdometry();
auto pathgen = AsyncMotionProfileControllerBuilder()
    .withLimits({maxVel, maxAccel, maxJerk})
    //.withOutput(drive)
    .withOutput(odom)
    .buildMotionProfileController();

void movingbeans() {
  odom->turnAngle(180_deg);
  odom->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}
