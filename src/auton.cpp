#include "subsystems.hpp"
using namespace pros;
void autonhandler() {
  switch(auton) {
    case 1:
      redBack();
    case 2:
      blueBack();
    case 3:
      redFront();
    case 4:
      blueFront();
    case 5:
      auton5();
    case 6:
      auton6();
    case 7:
      driveVel(-100);
      delay(1000);
      driveVel(100);
      delay(1000);
      driveVel(0);
  }
}
