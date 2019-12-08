//#include "subsystems.hpp"
#include "okapi/api.hpp"
using namespace okapi;

const double drivekP = 0.000;
const double drivekI = 0.0000;
const double drivekD = 0.0000;
const double drivekBias = 0;
const double maxVel = 5.00;
const double maxAccel = 3.00;
const double maxJerk = 9.00;
const double odomTrack = 0.0;
const double odomMiddleDist = 0.0;
const double drivemoveThreshold = 0.0;
const double driveturnThreshold = 0.0;
//const double driveVelDelta = 0.001;
auto odom = ChassisControllerBuilder()
    .withMotors({1, 2}, {3, -4})
    .withGearset(AbstractMotor::gearset::blue)
    .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', true})
    .withDimensions({{3.25, 9}, imev5BlueTPR})
    //.withGearset(5.0/3.0)
    .withGains(
        { 0.001, 0, 0.0001 }, // Distance controller gains
        { 0.001, 0, 0.0001 }, // Turn controller gains
        { 0.001, 0, 0.0001 }  // Angle controller gains (helps drive straight)
    )
    //.withOdometry({2.75, odomTrack, odomMiddleDist, 2.75}, drivemoveThreshold, driveturnThreshold)
    .withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_ft, 0_deg, 0.00001_mps)
    //.withLogger(const std::shared_ptr<Logger>& ilogger)
    .buildOdometry();

auto pathgen = AsyncMotionProfileControllerBuilder()
    .withLimits({maxVel, maxAccel, maxJerk})
    //.withOutput(drive)
    .withOutput(odom)
    .buildMotionProfileController();

void settle(){
  pathgen->waitUntilSettled();
}

void beans(){
  pathgen->generatePath({{1_ft, 0_ft, 0_deg}, {5_ft, 0_ft, 0_deg} }, "bean1");
  pathgen->generatePath({{5_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}, {1_ft, 2_ft, 0_deg}}, "bean2");
  pathgen->generatePath({{1_ft, 2_ft, 0_deg}, {5_ft, 5_ft, 0_deg}}, "bean3");
}

void movingbeans() {
  //intakeHandler(200);
  beans();
  pathgen->setTarget("bean1");
  settle();
  pathgen->setTarget("bean2");
  settle();
  pathgen->setTarget("bean3");
  settle();
  //intakeHandler(0);
}
