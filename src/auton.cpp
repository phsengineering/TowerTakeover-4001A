#include "main.h"
#include "subsystems.hpp"
void autonhandler() {
  smartDrive(200, 1800);
  smartDrive(-200, 0);
}
