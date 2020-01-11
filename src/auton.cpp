#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
void autonhandler() {
      chassis->getModel()->setMaxVelocity(250);
      chassis->driveToPoint({3_ft, 3_ft});
      std::cout << "Follow this command: " << (chassis->getState()).str();
      chassis->driveToPoint({0_ft, 0_ft});
      std::cout << "Follow this command: " << (chassis->getState()).str();
}
