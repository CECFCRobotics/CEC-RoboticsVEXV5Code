#include "vex.h"
using namespace vex;

// ints and small voids
void sleep(int Time) { task::sleep(Time); }
double dumpSpd(int Degrees) { return (Degrees - dump.rotation(deg)); }
double dumpSpeed{(dump.rotation(deg) + 1) * 13};
int smallTower = 835, midTower = 1185, dumpArmRequirement = 450;
int auton;
int dumperPos() { return dump.position(deg); }

void tank(int lspd, int rspd) {
  Left.spin(fwd, lspd, pct);
  Right.spin(fwd, rspd, pct);
}

// macros
void driver() {
  while (true) {
    tank(Adam.Axis2.value() + 0.5 * Adam.Axis1.value(),
         Adam.Axis2.value() - 0.5 * Adam.Axis1.value());
    if (Adam.ButtonR1.pressing())
      intake.spin(fwd, 100, pct);
    else if (Adam.ButtonR2.pressing())
      intake.spin(reverse, 100, pct);
    else
      intake.stop(brake);
    sleep(20);
  }
}
void macros() {
  while (true) {
    sleep(20);
    if (Adam.ButtonLeft.pressing()) {
      if (dump.rotation(deg) < 420) {
        dump.rotateTo(450, deg, 700, dps, true);
        arm.rotateTo(875, deg, -1100, dps, true);
        arm.stop(brake);
      } else {
        arm.rotateTo(875, deg, -1100, dps, true);
        arm.stop(brake);
      }
    } else if (Adam.ButtonUp.pressing()) {
      if (dump.rotation(deg) < 420) {
        dump.rotateTo(450, deg, 700, dps, true);
        arm.rotateTo(1185, deg, -1100, dps, true);
        arm.stop(brake);
      } else {
        arm.rotateTo(1185, deg, -1100, dps, true);
        arm.stop(brake);
      }
    } else if (Adam.ButtonDown.pressing()) {
      if (dump.rotation(deg) < 420) {
        dump.rotateTo(450, deg, 500, dps, true);
        arm.rotateTo(0, deg, -1100, dps, true);
        arm.stop(brake);
      } else {
        arm.rotateTo(0, deg, -1100, dps, true);
        arm.stop(brake);
      }
    } else if (Adam.ButtonX.pressing()) {
      arm.spin(fwd, 50, pct);
    } else if (Adam.ButtonB.pressing()) {
      arm.spin(reverse, 50, pct);
    } else {
      arm.stop(brake);
    }
    if (Adam.Axis3.position() == 0)
      dump.stop(coast);
    else
      dump.spin(fwd, Adam.Axis3.value(), pct);
  }
}
