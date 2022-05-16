#include "vex.h"
using namespace vex;
brain Brain;
motor backLeft = motor(PORT8), backRight = motor(PORT3, true),
      frontLeft = motor(PORT7), frontRight = motor(PORT4, true),
      lIntake = motor(PORT10), rIntake = motor(PORT1, true),
      arm = motor(PORT2, true), dump = motor(PORT9);
controller Adam = controller(primary);
motor_group intake(lIntake, rIntake), Left(frontLeft, backLeft),
    Right(frontRight, backRight),
    DT(frontLeft, frontRight, backLeft, backRight),
    all(lIntake, rIntake, frontLeft, frontRight, backLeft, backRight, arm,
        dump);
void vexcodeInit(void) {}
