#include "okapi/api.hpp"
using namespace okapi;

auto rightodom = ADIEncoder('A', 'B', false);
auto leftodom = ADIEncoder('E', 'F', false);
auto midodom = ADIEncoder('C', 'D', false);
ChassisScales scales = ChassisScales({3.25, 9.75}, (imev5BlueTPR*(5/3)));
Logger logger = Logger(TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", Logger::LogLevel::debug);
TimeUtil test = TimeUtilFactory::createDefault();
auto chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // left motor is 1, right motor is 2 (reversed)
                                // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
    .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 9.75_in}, imev5BlueTPR})
    .withSensors({'E', 'F', false}, {'A', 'B', false}, {'C', 'D', false})
    //.withDimensions(scales)
    .withGains(
         { 0.004, 0, 0.0 }, // Distance controller gains
         { 0.0029, 0.00001, 0.000 }, // Turn controller gains
         { 0.00022, 0, 0.0000 }  // Angle controller gains (helps drive straight)
     )
    .withDerivativeFilters(
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>(),
       std::make_unique<AverageFilter<3>>()
     )
    .withOdometry({{2.75_in, 5.5_in, 1_in, 2.75_in}, quadEncoderTPR}) // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis
auto chassisA = AsyncMotionProfileControllerBuilder()
        .withLimits({1, 2, 10})
        .withOutput(chassis)
        .buildMotionProfileController();


void redOkapi() {
  auto hello = chassis->getModel();
  hello->setMaxVelocity(275);
  chassis->setState({0_in, 0_in, 0_deg});
  chassis->moveDistance(60_in);
  chassis->waitUntilSettled();
  chassis->turnAngle(45_deg);
  chassis->moveDistance(-18_in);
  chassis->turnAngle(0_deg);
  chassis->waitUntilSettled();
}
