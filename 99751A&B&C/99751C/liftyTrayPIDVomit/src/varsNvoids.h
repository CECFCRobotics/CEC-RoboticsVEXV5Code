#include "vex.h"
using namespace vex;
int auton = 0;
void sleep(int mSec) { task::sleep(mSec); }
directionType dir(int first, int second) {
  return ((first >= second) ? fwd : reverse);
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
void tank(int lspd, int rspd) {
  leftMotor.spin(fwd, lspd, pct);
  rightMotor.spin(fwd, rspd, pct);
}
long double leftDTPos() { return leftMotor.rotation(deg); }
long double rightDTPos() { return rightMotor.rotation(deg); }
long double hDTPos() { return mMotor.rotation(deg); }
double dumpPos() { return dump.rotation(deg); }
double leftBarPos() { return lBar.rotation(deg); }
double rightBarPos() { return rBar.rotation(deg); }
long double leftIntakePos() { return lIntake.rotation(deg); }
long double rightIntakePos() { return rIntake.rotation(deg); }
void printRotations() {
  Brain.Screen.setFillColor(black), Brain.Screen.setPenColor(cyan),
      Brain.Screen.clearScreen(), Brain.Screen.setCursor(1, 1),
      Brain.Screen.print("leftDT:"), Brain.Screen.setCursor(1, 17),
      Brain.Screen.print(leftDTPos()), Brain.Screen.setCursor(2, 1),
      Brain.Screen.print("rightDT:"), Brain.Screen.setCursor(2, 17),
      Brain.Screen.print(rightDTPos()), Brain.Screen.setCursor(3, 1),
      Brain.Screen.print("mMotor:"), Brain.Screen.setCursor(3, 17),
      Brain.Screen.print(hDTPos()), Brain.Screen.setCursor(4, 1),
      Brain.Screen.print("leftBar:"), Brain.Screen.setCursor(4, 17),
      Brain.Screen.print(leftBarPos()), Brain.Screen.setCursor(5, 1),
      Brain.Screen.print("rightBar:"), Brain.Screen.setCursor(5, 17),
      Brain.Screen.print(rightBarPos()), Brain.Screen.setCursor(6, 1),
      Brain.Screen.print("dump:"), Brain.Screen.setCursor(6, 17),
      Brain.Screen.print(dumpPos()), Brain.Screen.setCursor(7, 1),
      Brain.Screen.print("leftIntake:"), Brain.Screen.setCursor(7, 17),
      Brain.Screen.print(leftIntakePos()), Brain.Screen.setCursor(8, 1),
      Brain.Screen.print("rightIntake:"), Brain.Screen.setCursor(8, 17),
      Brain.Screen.print(rightIntakePos());
}
