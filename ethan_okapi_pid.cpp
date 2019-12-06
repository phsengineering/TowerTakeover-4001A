#include "subsystems.hpp"
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

/* idk if this is necessary 
auto drive = ChassisControllerBuilder()
    .withMotors({1, -2}, {-3, 4})
    .withGearset(AbstractMotor::gearset::blue)
    .withGearset(5/3)
    .withSensors({'A', 'B'}, {'C', 'D', true})
    .withDimensions({{3.25, 9}, imev5BlueTPR})
    .withGains({drivekP, drivekI, drivekD})  
    .withOdometry({2.75, odomTrack, odomMiddleDist, 2.75}, FRAME_TRANSFORMATION, drivemoveThreshold, driveturnThreshold)    
    .build()
*/
    
auto odom = OdomControllerBuilder()
    .withMotors({1, -2}, {-3, 4})
    .withGearset(AbstractMotor::gearset::blue)
    .withGearset(5/3)
    .withSensors({'A', 'B'}, {'C', 'D', true})
    .withDimensions({{3.25, 9}, imev5BlueTPR})
    .withGains({drivekP, drivekI, drivekD})    
    .withOdometry({2.75, odomTrack, odomMiddleDist, 2.75}, FRAME_TRANSFORMATION, drivemoveThreshold, driveturnThreshold)
    //.withLogger(const std::shared_ptr<Logger>& ilogger)
    .buildOdometry()

auto pathgen = AsyncMotionProfileControllerBuilder()
    .withLimits({maxVel, maxAccel, maxJerk})
    //.withOutput(drive)
    .withOutput(odom)
    .buildMotionProfileController();

void settle(){
  pathgen->waitUntilSettled();
}

void beans(){
  pathgen->generatePath({{1, 0, 0}, {5, 0, 0}}, bean1);
  pathgen->generatePath({{5, 0, 0}, {2, 0, 0}, {1, 2, 0}}, bean2);
  pathgen->generatePath({{1, 2, 0}, {5, 5, 0}}, bean3);
}

void movingbeans(){
  intakeHandler(200);
  pathgen->setTarget(bean1);
  settle();
  pathgen->setTarget(bean2, true, false);
  settle();
  pathgen->setTarget(bean3);
  settle();
}
