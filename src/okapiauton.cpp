#include "subsystems.hpp"
#include "okapi/api.hpp"
using namespace okapi;
auto chassis = ChassisControllerBuilder()
    .withMotors({1, -2}, {-3, 4})
    .withGearset(AbstractMotor::gearset::blue)
    .withSensors(
                  {'A', 'B'},
                  {'C', 'D', true}
              )
    .withDimensions({{2.75_in, 9_in}, imev5BlueTPR})
    .build();

auto profileController = AsyncMotionProfileControllerBuilder()
    .withLimits({ 1.0, 2.0, 10.0 })
    .withOutput(chassis)
    .buildMotionProfileController();

void okapilibauton() {
  profileController->generatePath({ {0_ft, 0_ft, 0_deg}, {0_ft, 3_ft, 0_deg} }, "A");
  profileController->setTarget("A");
  profileController->waitUntilSettled();
}
