#include "vex.h"
using namespace vex;
// Brain
brain Brain;
// Motors
motor RightDrive(PORT1, true), LeftDrive(PORT10), H_Drive(PORT8),
    LeftIntake(PORT9), RightIntake(PORT2, true), Lift(PORT6, true),
    IntakeLift(PORT7), IntakeLift2(PORT5, true);
motor_group DT(LeftDrive, RightDrive), intakeLift(IntakeLift, IntakeLift2),
    intake(LeftIntake, RightIntake);
// Controllers
controller Controller(primary), Controller2(partner);
// Sensors
pot PotentiometerL(Brain.ThreeWirePort.A),
    PotentiometerR(Brain.ThreeWirePort.B);
void vexcodeInit(void) {
  IntakeLift.resetRotation(), IntakeLift2.resetRotation();
}
