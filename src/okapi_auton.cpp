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
ChassisScales scales = ChassisScales({3.25, 9.75}, (imev5BlueTPR*(5/3)));
Logger logger = Logger(TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", Logger::LogLevel::debug);
TimeUtil test = TimeUtilFactory::createDefault();
auto chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1})
    .withGearset({AbstractMotor::gearset::blue, 5/3})
    .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', false})
    //.withDimensions(scales)
    .withGains(
         { 0.002, 0, 0.00001 }, // Distance controller gains
         { 0.0026, 0.00001, 0.0000 }, // Turn controller gains
         { 0.0002, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    //.withMaxVoltage(12000) //normally 10000
    .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>()
     )
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
void promisingauton() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(400);
  chassis->moveDistance(1650);
  chassis->waitUntilSettled();
  chassis->moveDistance(-900);
  chassis->waitUntilSettled();
  chassis->turnAngle(205_deg);
  chassis->waitUntilSettled();

}
void testFwd() {
  auto temp = chassis->getModel();
  temp->setMaxVelocity(375);
  chassis->moveDistance(2000);
  chassis->waitUntilSettled();
  //chassis->stop();
}
