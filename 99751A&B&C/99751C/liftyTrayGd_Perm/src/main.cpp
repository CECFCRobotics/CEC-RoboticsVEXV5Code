#include "vex.h"
using namespace vex;
competition Comp;
bool colorOk, stackOk;
int auton = 0, tallTower = 800, middleTower = 600, smallTower = 400;
void sleep(int Time) { task::sleep(Time); }
void autonColorSelect() {
  color side[] = {blue, red};

  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(0, 0, 240, 272, blue);
  Brain.Screen.drawRectangle(240, 0, 240, 272, red);
  Brain.Screen.setFillColor(side[auton]);
}
void brainAutonColorSelect() {
  int x = Brain.Screen.xPosition();
  auton = ((x < 240) ? 0 : 1);
  autonColorSelect();
}
void autonStackSelect() {
  color stack[] = {blue, red};

  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(0, 0, 240, 272, green);
  Brain.Screen.drawRectangle(240, 0, 240, 272, orange);
  Brain.Screen.setFillColor(stack[auton]);

  Houston.Screen.setCursor(1, 1);
}
void brainAutonStackSelect() {
  int x = Brain.Screen.xPosition();
  auton = ((x < 240) ? 0 : 1);
  autonColorSelect();
}
void tank(int lspd, int rspd) {
  leftMotor.spin(fwd, lspd, pct);
  rightMotor.spin(fwd, rspd, pct);
}
/*+++++++++++++++++++++++++++++++++++++++++++AUTON++++++++++++++++++++++++++*/
void autonomusses() {
  switch (auton) {
  case 0: // Blue Flat
    intake.spin(reverse, 100, pct);
    sleep(500);
    intake.stop(coast);
    break;
  case 1: // Blue Tall
    intake.spin(reverse, 100, pct);
    sleep(500);
    intake.stop(coast);
    break;
  case 2: // Red Flat
    intake.spin(reverse, 100, pct);
    sleep(500);
    intake.stop(coast);
    break;
  case 3: // Red Tall
    intake.spin(reverse, 100, pct);
    sleep(500);
    intake.stop(coast);
    break;
  }
}
int singleDrive = 0;
double driveMultiplier = 1;
void changeDrive() {
  if (singleDrive == 1) {
    singleDrive = 0;
  } else {
    singleDrive = 1;
  }
}
void Drive() {
  while (true) {
    Houston.ButtonUp.released(changeDrive);
    if (singleDrive == 0) { // Double Drive
                            /*
                            What's left:
                            Houston 1
                            Houston 4
                            Houston Right
                            Houston Left
                            Houston A
                            Houston B
                      
                            Austin 1
                            Austin 4
                            Austin Right
                            Austin Left
                            Austin A
                            Austin B
                            */
      leftMotor.spin(fwd, driveMultiplier * Houston.Axis3.value(), pct);
      rightMotor.spin(fwd, driveMultiplier * Houston.Axis2.value(), pct);

      dump.spin(fwd, 0.75 * Austin.Axis2.value(), pct);

      if (Houston.ButtonDown.pressing()) {
        driveMultiplier = 0.35;
      } else {
        driveMultiplier = 0.95;
      }

      if (Houston.ButtonL1.pressing()) {
        mMotor.spin(fwd, 100, pct);
      } else if (Houston.ButtonR1.pressing()) {
        mMotor.spin(reverse, 100, pct);
      } else {
        mMotor.stop(coast);
      }
      // L1 - middle tower
      // L2 - small tower
      // Up - tall tower
      // Down - Down
      if (Houston.ButtonX.pressing()) {
        lBar.spin(fwd, 40, pct);
      } else if (Houston.ButtonY.pressing()) {
        lBar.spin(reverse, 40, pct);
      } else if (Austin.ButtonX.pressing()) {
        lBar.spin(fwd, 40, pct);
      } else if (Austin.ButtonY.pressing()) {
        lBar.spin(reverse, 40, pct);
      } else if (Austin.ButtonL1.pressing()) {
        if (bar.rotation(deg) < middleTower) {
          bar.rotateTo(middleTower, deg, middleTower + 100, dps, true);
        } else {
          bar.rotateTo(middleTower, deg, -middleTower + 100, dps, true);
        }
      } else if (Austin.ButtonL2.pressing()) {
        if (bar.rotation(deg) < smallTower) {
          bar.rotateTo(smallTower, deg, smallTower + 200, dps, true);
        } else {
          bar.rotateTo(smallTower, deg, -smallTower + 200, dps, true);
        }
      } else if (Austin.ButtonUp.pressing()) {
        if (bar.rotation(deg) < tallTower) {
          bar.rotateTo(tallTower, deg, tallTower + 100, dps, true);
        } else {
          bar.rotateTo(tallTower, deg, -tallTower + 100, dps, true);
        }
      } else if (Austin.ButtonDown.pressing()) {
        if (bar.rotation(deg) < 40) {
          bar.rotateTo(40, deg, 800, dps, true);
        } else {
          bar.rotateTo(40, deg, -100, dps, true);
        }
      } else {
        if (Austin.Axis3.position() == 0) {
          bar.stop(brake);
        } else {
          bar.spin(fwd, Austin.Axis3.value(), pct);
        }
      }

      if (Houston.ButtonR2.pressing()) {
        intake.spin(fwd, 100, pct);
      } else if (Houston.ButtonL2.pressing()) {
        intake.spin(reverse, 100, pct);
      } else if (Austin.ButtonR1.pressing()) {
        intake.spin(fwd, 100, pct);
      } else if (Austin.ButtonR2.pressing()) {
        intake.spin(reverse, 100, pct);
      } else {
        intake.stop(brake);
      }

    } else { // Single drive
             /*
             What's left:
             Button B
             */
      if (Houston.ButtonDown.pressing()) {
        driveMultiplier = 0.35;
      } else {
        driveMultiplier = 0.95;
      }

      if (Houston.ButtonL1.pressing()) {
        mMotor.spin(fwd, 100, pct);
      } else if (Houston.ButtonR1.pressing()) {
        mMotor.spin(reverse, 100, pct);
      } else {
        mMotor.stop(coast);
      }

      if (Houston.ButtonR2.pressing()) {
        intake.spin(fwd, 100, pct);
      } else if (Houston.ButtonL2.pressing()) {
        intake.spin(reverse, 100, pct);
      } else {
        intake.stop(brake);
      }

      if (Houston.ButtonLeft.pressing()) {
        dump.rotateFor(fwd, 900, rev);
      } else if (Houston.ButtonA.pressing()) {
        dump.rotateFor(reverse, 900, rev);
      } else {
        if (Houston.ButtonRight.pressing()) {
          DT.stop(hold);
          bar.stop(hold);
          dump.spin(fwd, Houston.Axis1.value(), pct);
        } else {
          if (Houston.Axis3.position() == 0 && Houston.Axis4.position() == 0) {
            DT.stop(coast);
          } else {
            tank(Houston.Axis3.value() + Houston.Axis4.value(),
                 Houston.Axis3.value() - Houston.Axis4.value());
          }

          if (Houston.ButtonX.pressing()) {
            lBar.spin(fwd, 100, pct);
          } else if (Houston.ButtonY.pressing()) {
            lBar.spin(reverse, 100, pct);
          } else {
            if (Houston.Axis2.position() == 0) {
              bar.stop(hold);
            } else {
              bar.spin(fwd, Houston.Axis2.value(), pct);
            }
          }
        }
      }
    }
  }
}

int main() {
  vexcodeInit();
  dump.resetRotation();
  bar.resetRotation();
  Brain.Screen.drawRectangle(0, 0, 240, 272, blue);
  Brain.Screen.drawRectangle(240, 0, 240, 272, red);

  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      brainAutonColorSelect();
      colorOk = true;
    } else if (Houston.ButtonL1.pressing()) {
      colorOk = true;
      auton = 2;
    } else if (Houston.ButtonL2.pressing()) {
      colorOk = true;
      auton = 0;
    } else {
      colorOk = false;
    }
  } while (!colorOk);

  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(0, 0, 240, 272, green);
  Brain.Screen.drawRectangle(240, 0, 240, 272, orange);

  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      brainAutonStackSelect();
      stackOk = true;
    } else if (Houston.ButtonR1.pressing()) {
      stackOk = true;
      auton = 3;
    } else if (Houston.ButtonR2.pressing()) {
      stackOk = true;
      auton = 1;
    } else {
      stackOk = false;
    }
  } while (!stackOk);

  Brain.Screen.clearScreen();

  Comp.drivercontrol(Drive);
  Comp.autonomous(autonomusses);
}
