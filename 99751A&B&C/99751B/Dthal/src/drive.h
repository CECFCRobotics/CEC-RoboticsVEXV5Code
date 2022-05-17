#include "auton.h"
using namespace vex;
void driver() {
  while (true) {
    frontLeftMotor.spin(
        fwd, I.Axis2.value() / 3 + I.Axis1.value() / 3 + I.Axis4.value() / 3,
        pct);
    backLeftMotor.spin(
        fwd, I.Axis2.value() / 3 - I.Axis1.value() / 3 + I.Axis4.value() / 3,
        pct);
    frontRightMotor.spin(
        fwd, -I.Axis2.value() / 3 + I.Axis1.value() / 3 + I.Axis4.value() / 3,
        pct);
    backRightMotor.spin(
        fwd, -I.Axis2.value() / 3 - I.Axis1.value() / 3 + I.Axis4.value() / 3,
        pct);

    if (I.ButtonR1.pressing())
      highInt.spin(fwd, 100, pct);
    else if (I.ButtonL2.pressing() && I.ButtonR1.pressing())
      highInt.spin(reverse, 100, pct);
    else
      highInt.stop(brake);

    if (I.ButtonR2.pressing())
      lowInt.spin(fwd, 75, pct);
    else if (I.ButtonL2.pressing() && I.ButtonR2.pressing())
      lowInt.spin(reverse, 75, pct);
    else
      lowInt.stop(brake);

    printImu(true);
    sleep(20);
  }
}
void macros() {
  while (true) {
    sleep(20);
    if (I.ButtonL1.pressing() && I.ButtonR1.pressing()) 
      highInt.rotateFor(3000, deg, 560, dps);
  }
}
void Drive() {
  thread t_Drive(driver);
  thread t_Macro(macros);

  while (true)
    sleep(20);
}
