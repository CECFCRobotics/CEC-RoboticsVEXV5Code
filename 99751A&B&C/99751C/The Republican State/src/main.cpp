#include "vex.h"
using namespace vex;
bool autonomousundecided = true;
float auton = 1;
int drive = -1, side = 0;
competition Competition;
void wait(int time) { task::sleep(time); }

void tank(int lspd, int rspd, bool DoTime, int Time) {
  LeftDrive.spin(forward, lspd, percent),
      RightDrive.spin(forward, rspd, percent);
  if (DoTime)
    wait(Time);
}
void autonStart() {
  Lift.spin(forward, 75, percent), intake.spin(reverse, 100, percent),
      tank(50, 50, true, 500), DT.stop(brake);
  wait(500), Lift.stop(brake), intake.stop(coast);
}
void ok() { autonomousundecided = false, Brain.Screen.clearScreen(); }
void x() {
  if (Brain.Battery.capacity() > 50)
    Brain.Screen.clearScreen(),
        Brain.Screen.drawRectangle(0, 0, 500, 300, green);
  else if (Brain.Battery.capacity() < 50 && Brain.Battery.capacity() > 25)
    Brain.Screen.clearScreen(),
        Brain.Screen.drawRectangle(0, 0, 500, 300, yellow);
  else
    Brain.Screen.clearScreen(), Brain.Screen.drawRectangle(0, 0, 500, 300, red);
}
void b() {
  Brain.Screen.clearScreen(),
      Brain.Screen.printAt(0, 20, "Battery Capacity %d percent",
                           Brain.Battery.capacity()),
      Brain.Screen.printAt(0, 40, "Battery Temperature %lf",
                           Brain.Battery.temperature());
}
void printPot() {
  Brain.Screen.setOrigin(10, 50), Brain.Screen.print(IntakeLift.rotation(deg));
  Brain.Screen.setOrigin(100, 50),
      Brain.Screen.print(IntakeLift2.rotation(deg));
  Brain.Screen.setOrigin(100, 100), wait(50), Brain.Screen.clearScreen();
}
void Green() { Brain.Screen.clearScreen(), Brain.Screen.setPenColor(green); }
void Red() { Brain.Screen.setPenColor(red); }
void Blue() { Brain.Screen.setPenColor(blue); }
void blue1() { Blue(), Brain.Screen.printAt(50, 60, "1"); }
void blue2() { Blue(), Brain.Screen.printAt(170, 60, "2"); }
void blue3() { Blue(), Brain.Screen.printAt(290, 60, "3"); }
void blue4() { Blue(), Brain.Screen.printAt(410, 60, "4"); }
void red1() { Red(), Brain.Screen.printAt(50, 130, "1"); }
void red2() { Red(), Brain.Screen.printAt(170, 130, "2"); }
void red3() { Red(), Brain.Screen.printAt(290, 130, "3"); }
void red4() { Red(), Brain.Screen.printAt(410, 130, "4"); }
void sblue1() {
  Green(), Brain.Screen.printAt(50, 60, "1"), blue2(), blue3(), blue4(), red1(),
      red2(), red3(), red4();
}
void sblue2() {
  Green(), Brain.Screen.printAt(170, 60, "2"), blue1(), blue3(), blue4(),
      red1(), red2(), red3(), red4();
}
void sblue3() {
  Green(), Brain.Screen.printAt(290, 60, "3"), blue1(), blue2(), blue4(),
      red1(), red2(), red3(), red4();
}
void sblue4() {
  Green(), Brain.Screen.printAt(410, 60, "4"), blue2(), blue3(), blue1(),
      red1(), red2(), red3(), red4();
}
void sred1() {
  Green(), Brain.Screen.printAt(50, 130, "1"), blue1(), blue2(), blue3(),
      blue4(), red2(), red3(), red4();
}
void sred2() {
  Green(), Brain.Screen.printAt(170, 130, "2"), blue1(), blue2(), blue3(),
      blue4(), red1(), red3(), red4();
}
void sred3() {
  Green(), Brain.Screen.printAt(290, 130, "3"), blue1(), blue2(), blue3(),
      blue4(), red2(), red1(), red4();
}
void sred4() {
  Green(), Brain.Screen.printAt(410, 130, "4"), blue1(), blue2(), blue3(),
      blue4(), red2(), red3(), red1();
}
/*+++++++++++++++++++++++++++++++++++++++++++Autoni++++++++++++++++++++++++++++++*/
void blue1auton() {
  blue1(), autonStart(), tank(50, 50, true, 1500),
      intake.spin(forward, 100, percent), intakeLift.spin(forward, 50, percent),
      wait(500), intakeLift.stop(hold), wait(500), DT.stop(brake),
      Lift.spin(reverse, 50, percent), wait(500), Lift.stop(coast),
      tank(-80, -80, true, 500), DT.stop(coast);
}
void blue2auton() {
  blue2();
  autonStart();
}
void blue3auton() {
  blue3();
  autonStart();
}
void blue4auton() {
  blue4();
  autonStart();
}
void red1auton() {
  red1(), autonStart(), tank(50, 50, true, 1500),
      intake.spin(forward, 100, percent), intakeLift.spin(forward, 50, percent),
      wait(500), intakeLift.stop(hold), wait(500), DT.stop(brake),
      Lift.spin(reverse, 50, percent), wait(500), Lift.stop(coast),
      tank(-80, -80, true, 500), DT.stop(coast);
}
void red2auton() { red2(), autonStart(); }
void red3auton() { red3(), autonStart(); }
void red4auton() { red4(), autonStart(); }
/*+++++++++++++++++++++++++++++++++++++++++++PRE+Auton++++++++++++++++++++++++++*/
void pre_auton() {
  Brain.Screen.setFont(mono40), Brain.Screen.clearScreen(), blue1(), blue2(),
      blue3(), blue4(), red1(), red2(), red3(), red4();
  do {
    Controller.ButtonB.released(ok);
    if (Controller.ButtonLeft.pressing())
      auton = 4;
    if (Controller.ButtonDown.pressing())
      auton = 3;
    if (Controller.ButtonRight.pressing())
      auton = 2;
    if (Controller.ButtonUp.pressing())
      auton = 1;
    if (Controller.ButtonA.pressing())
      side = 0;
    if (Controller.ButtonY.pressing())
      side = 1;
    if (side == 0) { // blue
      if (auton == 1)
        sblue1();
      else if (auton == 2)
        sblue2();
      else if (auton == 3)
        sblue3();
      else
        sblue4();
    } else { // red
      if (auton == 1)
        sred1();
      else if (auton == 2)
        sred2();
      else if (auton == 3)
        sred3();
      else
        sred4();
    }
    wait(20);
  } while (autonomousundecided);
  if (side == 0) { // blue
    if (auton == 1)
      Competition.autonomous(blue1auton);
    else if (auton == 2)
      Competition.autonomous(blue2auton);
    else if (auton == 3)
      Competition.autonomous(blue3auton);
    else
      Competition.autonomous(blue4auton);
  } else { // red
    if (auton == 1)
      Competition.autonomous(red1auton);
    else if (auton == 2)
      Competition.autonomous(red2auton);
    else if (auton == 3)
      Competition.autonomous(red3auton);
    else
      Competition.autonomous(red4auton);
  }
}
/*+++++++++++++++++++++++++++++++++++++++++++INTAKE++++++++++++++++++++++++++++++*/
void intakefunction() {
  if (Controller2.ButtonR1.pressing())
    intake.spin(forward, 100, pct);
  else if (Controller2.ButtonR2.pressing())
    intake.spin(reverse, 100, pct);
  else
    intake.stop(coast);
}
/*+++++++++++++++++++++++++++++++++++++++++++LIFT++++++++++++++++++++++++++++++++*/
void liftfunction() {
  if (Controller2.ButtonUp.pressing())
    Lift.spin(reverse, 50, pct);
  else if (Controller2.ButtonDown.pressing())
    Lift.spin(forward, 50, pct);
  else
    Lift.stop(hold);
}
/*+++++++++++++++++++++++++++++++++++++++++++POT+++++++++++++++++++++++++++++++++*/
void Low() {
  if (Controller2.ButtonY.pressing() && IntakeLift.rotation(deg) <= 330 &&
      IntakeLift2.rotation(deg) <= 330)
    intakeLift.rotateTo(330, deg, 700, dps, true), intakeLift.stop(hold);
  else if (Controller2.ButtonY.pressing() && intakeLift.rotation(deg) > 330)
    intakeLift.stop(coast);
}
void High() {
  if (Controller2.ButtonX.pressing() && IntakeLift.rotation(deg) <= 660 &&
      IntakeLift2.rotation(deg) <= 660)
    intakeLift.rotateTo(660, deg, 900, dps, true), intakeLift.stop(hold);
  else if (Controller2.ButtonX.pressing() && intakeLift.rotation(deg) > 660)
    intakeLift.stop(coast);
}
void Control() {
  if (Controller2.ButtonL1.pressing())
    if (Controller2.ButtonX.pressing())
      intakeLift.spin(forward);
  if (Controller2.ButtonY.pressing())
    intakeLift.spin(reverse);
}
/*+++++++++++++++++++++++++++++++++++++++++++DRIVER++++++++++++++++++++++++++++++*/
void driverFunction() {
  while (1) {
    tank(Controller.Axis3.value(), Controller.Axis2.value(), false, 0);
    printPot();
    Controller.ButtonX.pressed(x);
    High();
    Low();
    if (Controller.ButtonR1.pressing())
      H_Drive.spin(forward, 100, pct);
    else if (Controller.ButtonL1.pressing())
      H_Drive.spin(reverse, 100, pct);
    else
      H_Drive.stop(coast);
    intakefunction();
    liftfunction();
  }
}
/*+++++++++++++++++++++++++++++++++++++++++++INT+MAIN++++++++++++++++++++++++++++*/
int main() {
  vexcodeInit();
  pre_auton();
  Competition.drivercontrol(driverFunction);
}
