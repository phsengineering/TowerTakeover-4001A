//#include "subsystems.hpp"
#include "okapi/api.hpp"
using namespace okapi;

auto rightodom = ADIEncoder('A', 'B', false);
auto leftodom = ADIEncoder('E', 'F', false);
auto midodom = ADIEncoder('C', 'D', false);

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
TimeUtil test = TimeUtilFactory::createDefault();
auto chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1})
    .withGearset({AbstractMotor::gearset::blue, 5/3})
    .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', false})
    //.withDimensions({{3.25, 9.25}, imev5BlueTPR})
    //.withGearset(5.0/3.0)
     .withGains(
         { 0.001, 0, 0.0000 }, // Distance controller gains
         { 0.0026, 0.0, 0.0000 }, // Turn controller gains
         { 0.0001, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    .withMaxVoltage(12000) //normally 10000
    .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>()
     )
    //.withChassisControllerTimeUtilFactory(TimeUtilFactory(50, 5, 250_ms))
    //.withOdometry({2.75, odomTrack, odomMiddleDist, 2.75}, drivemoveThreshold, driveturnThreshold)
    //.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_ft, 0_deg, 0.00001_mps)
    //.withLogger(logger)
    .build();

auto pathgen = AsyncMotionProfileControllerBuilder()
    .withLimits({maxVel, maxAccel, maxJerk})
    //.withOutput(drive)
    .withOutput(chassis)
    .buildMotionProfileController();

void turn40 () {
  chassis->turnAngle(-59_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}
void turnBack () {
  chassis->turnAngle(59_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}
void turn3 () {
  chassis->turnAngle(214_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}
void turnL90 () {
  chassis->turnAngle(-155_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}

void turnR90 () {
  chassis->turnAngle(165_deg); //155 is equal to a 90 for some reason
  chassis->waitUntilSettled();
  //pathgen->setTarget("A");
  //pathgen->waitUntilSettled();
}
