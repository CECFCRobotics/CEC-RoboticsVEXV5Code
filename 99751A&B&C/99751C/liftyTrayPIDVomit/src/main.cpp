#include "PIDS.h"
using namespace vex;
competition Comp;
void autonomusses() {
  switch (auton) {
  case 0: // Blue Tall
    dump.stop(hold);
    intake.spin(reverse, 100, pct);
    sleep(1000);
    all.stop(coast);
    mMotor.spin(fwd, 100, pct);
    sleep(1000);
    mMotor.spin(fwd, -100, pct);
    sleep(1000);
    mMotor.stop(brake);
    all.stop(brake);
    break;
  case 1: // Blue Flat
    dump.stop(hold);
    intake.spin(reverse, 100, pct);
    sleep(1000);
    all.stop(coast);
    break;
  case 2: // Red Tall
    dump.stop(hold);
    intake.spin(reverse, 100, pct);
    sleep(1000);
    all.stop(coast);
    mMotor.spin(fwd, -100, pct);
    sleep(1000);
    mMotor.spin(fwd, 100, pct);
    sleep(1000);
    mMotor.stop(brake);
    all.stop(brake);
    break;
  case 3: // Red Flat
    dump.stop(hold);
    intake.spin(reverse, 100, pct);
    sleep(1000);
    all.stop(coast);
    break;
  }
}
void ultBlue() {
  dump.stop(hold);
  intake.spin(reverse, 100, pct);
  sleep(1000);
}
void ultraAuton() {
  switch (auton) {
  case (1): // blue
    all.resetRotation();
    printRotations();
    sleep(100);

    dump.stop(hold); // Deploy
    intake.spin(reverse, 100, pct);
    sleep(1000);
    all.stop(brake);

    printRotations();
    sleep(100);

    pidControlDrive(0); // Recorrect
    pidControlBar(0);
    printRotations();
    sleep(100);

    intake.spin(fwd, 100, pct); // Get the 4
    pidControlDrive(1600);
    intake.spin(fwd, 50, pct);

    if (bottomLine.value(pct) <= 11) // Pick up last one
      do {
        intake.spin(fwd, 70, pct);
      } while (bottomLine.value(pct) <= 11 && ultrasonic.distance(mm) >= 200);

    intake.stop(brake);
    printRotations();
    sleep(100);

    mMotor.rotateFor(500, deg, (500 - hDTPos()) + 200, dps, true);
    mMotor.stop(brake);

    intake.spin(fwd, 100, pct); // Get the 1
    pidControlDrive(700);
    intake.spin(fwd, 50, pct);

    if (bottomLine.value(pct) <= 11) // Make sure it's good
      do {
        intake.spin(fwd, 70, pct);
      } while (bottomLine.value(pct) <= 11 && ultrasonic.distance(mm) >= 200);

    intake.stop(brake);
    printRotations();
    sleep(100);

    mMotor.rotateTo(0, deg, -(fabs(0 - hDTPos()) + 200), dps,
                    true); // Reallign with the next 4
    mMotor.stop(brake);

    break;
  case (3): // red
    break;
  }
}
void Drive() {
  while (true) {
    Houston.ButtonUp.released(changeDrive);
    if (singleDrive == 0) { // Double Drive

      leftMotor.spin(fwd, driveMultiplier * Houston.Axis3.value(), pct);
      rightMotor.spin(fwd, driveMultiplier * Houston.Axis2.value(), pct);
      dump.spin(fwd, 0.75 * Austin.Axis2.value(), pct);

      if (Houston.ButtonDown.pressing())
        driveMultiplier = 0.35;
      else
        driveMultiplier = 0.95;

      if (Houston.ButtonL1.pressing())
        mMotor.spin(fwd, 100, pct);
      else if (Houston.ButtonR1.pressing())
        mMotor.spin(reverse, 100, pct);
      else
        mMotor.stop(coast);

      if (Houston.ButtonX.pressing())
        pidControlBar(600);
      else if (Austin.ButtonX.pressing())
        pidControlBar(600);
      else {
        if (Austin.Axis3.position() == 0)
          bar.stop(brake);
        else
          bar.spin(fwd, Austin.Axis3.value(), pct);
      }

      if (Houston.ButtonR2.pressing())
        intake.spin(fwd, 100, pct);
      else if (Austin.ButtonR1.pressing())
        intake.spin(fwd, 100, pct);
      else if (Houston.ButtonL2.pressing())
        intake.spin(reverse, 100, pct);
      else if (Austin.ButtonR2.pressing())
        intake.spin(reverse, 100, pct);
      else
        intake.stop(brake);

    } else { // Single drive

      if (Houston.ButtonDown.pressing()) {
        driveMultiplier = 0.35;
      } else {
        driveMultiplier = 0.95;
      }

      if (Houston.ButtonL1.pressing())
        mMotor.spin(fwd, 100, pct);
      else if (Houston.ButtonR1.pressing())
        mMotor.spin(reverse, 100, pct);
      else
        mMotor.stop(coast);

      if (Houston.ButtonR2.pressing())
        intake.spin(fwd, 100, pct);
      else if (Austin.ButtonR1.pressing())
        intake.spin(fwd, 100, pct);
      else if (Houston.ButtonL2.pressing())
        intake.spin(reverse, 100, pct);
      else if (Austin.ButtonR2.pressing())
        intake.spin(reverse, 100, pct);
      else
        intake.stop(brake);

      if (Houston.ButtonRight.pressing()) {
        DT.stop(hold), bar.stop(hold),
            dump.spin(fwd, Houston.Axis1.value(), pct);
      } else {
        if (Houston.Axis3.position() == 0 && Houston.Axis4.position() == 0) {
          DT.stop(coast);
        } else {
          tank(Houston.Axis3.value() + 0.6 * Houston.Axis4.value(),
               Houston.Axis3.value() - 0.6 * Houston.Axis4.value());
        }

        if (Houston.ButtonX.pressing())
          pidControlBar(600);
        else if (Austin.ButtonX.pressing())
          pidControlBar(600);
        else {
          if (Houston.Axis2.position() == 0)
            bar.stop(hold);
          else
            bar.spin(fwd, (Houston.Axis2.value() + Austin.Axis3.value()) / 2,
                     pct);
        }
      }
    }
  }
}
int main() {
  vexcodeInit();
  all.resetRotation();

  int sidePicked = -1, autonPicked = -1;

  Brain.Screen.drawRectangle(0, 0, 240, 272, blue),
      Brain.Screen.drawRectangle(240, 0, 240, 272, red);
  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      int xPos = Brain.Screen.xPosition();
      sidePicked = ((xPos < 272) ? 0 : 1);
    } else if (Houston.ButtonRight.pressing()) {
      while (Houston.ButtonRight.pressing())
        sleep(0);
      sidePicked = 0;
    } else if (Houston.ButtonY.pressing()) {
      while (Houston.ButtonY.pressing())
        sleep(0);
      sidePicked = 1;
    }
  } while (sidePicked == -1);

  Brain.Screen.clearScreen(), Brain.Screen.drawRectangle(0, 0, 240, 272),
      Brain.Screen.setCursor(7, 10), Brain.Screen.print("Protected"),
      Brain.Screen.drawRectangle(240, 0, 240, 272),
      Brain.Screen.setCursor(7, 33), Brain.Screen.print("Unprotected");
  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      int xPos = Brain.Screen.xPosition();
      autonPicked = ((xPos < 272) ? 0 : 1);
    } else if (Houston.ButtonRight.pressing()) {
      while (Houston.ButtonRight.pressing())
        sleep(0);
      autonPicked = 0;
    } else if (Houston.ButtonY.pressing()) {
      while (Houston.ButtonY.pressing())
        sleep(0);
      autonPicked = 1;
    }
  } while (autonPicked == -1);
  auton = autonPicked;

  color colr = (sidePicked == 0) ? blue : red;
  std::string txt = ((auton == 0) ? "Protected" : "Unprotected");

  Brain.Screen.clearScreen(colr);
  Brain.Screen.setCursor(6, 23);
  Brain.Screen.setFillColor(colr);
  Brain.Screen.print(txt.c_str());

  bool ult;
  if (auton == 5)
    ult = false;
  else
    ult = true;

  if (colr == red)
    auton = auton + 2;

  Comp.drivercontrol(Drive);
  if (ult)
    Comp.autonomous(ultraAuton);
  else
    Comp.autonomous(autonomusses);
}
