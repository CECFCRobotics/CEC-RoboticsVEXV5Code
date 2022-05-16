#include "Macros.h"
using namespace vex;
competition Comp;
void autonomousProgram() {
  switch (auton) {
  case 0: // Blue Tall
    arm.spin(fwd, 100, pct);
    sleep(800);
    arm.rotateTo(0, deg, -1500, dps, true);

    tank(40, 40);
    intake.spin(fwd, 100, pct);
    sleep(1060);
    DT.stop(brake);
    sleep(300);
    intake.stop(brake);

    tank(-40, 40);
    sleep(490);
    DT.stop(brake);

    tank(35, 35);
    intake.spin(fwd, 100, pct);
    sleep(1300);
    intake.stop(brake);

    tank(-30, 30);
    sleep(600);
    tank(30, 30);
    sleep(270);
    intake.spin(reverse, 30, pct);
    tank(30, -30);
    sleep(570);
    intake.stop(brake);

    tank(30, 30);
    sleep(500);
    intake.spin(fwd, 100, pct);
    sleep(520);
    DT.stop(brake);
    sleep(400);

    tank(-30, -30);
    sleep(1300);
    intake.stop(brake);
    sleep(900);

    tank(-70, -25);
    sleep(1200);
    tank(30, 30);
    sleep(740);
    tank(10, 35);
    sleep(200);

    intake.spin(reverse, 36, pct);
    sleep(500);
    intake.stop(coast);
    DT.stop(brake);
    dump.spin(fwd, (1560 - dumperPos()) * 0.6, dps);
    sleep(2200);
    dump.stop(brake);

    tank(20, 20);
    sleep(100);
    DT.stop(brake);
    dump.spin(reverse, 1500, dps);
    sleep(1600);
    all.stop(brake);
    intake.spin(reverse, 100, pct);
    tank(-100, -100);
    sleep(800);

    all.stop(brake);
    break;
  case 1: // Blue Flat
    tank(-10, -10);
    arm.spin(fwd, 100, pct);
    sleep(800);
    DT.stop(brake);
    arm.rotateTo(0, deg, -1500, dps, true);

    tank(40, 40);
    intake.spin(fwd, 100, pct);
    sleep(2100);
    DT.stop(brake);
    sleep(400);
    intake.stop(brake);
    intake.spin(reverse, 50, pct);
    sleep(400);
    all.stop(brake);

    tank(-40, -40);
    sleep(900);
    tank(-30, 30);
    sleep(1070);

    tank(34, 34);
    sleep(1200);
    dump.stop(brake);
    sleep(500);
    intake.spin(reverse, 36, pct);
    sleep(500);
    intake.stop(coast);
    DT.stop(brake);
    dump.spin(fwd, (1560 - dumperPos()) * 0.6, dps);
    sleep(2200);
    dump.stop(brake);

    tank(20, 20);
    sleep(100);
    DT.stop(brake);
    dump.spin(reverse, 1500, dps);
    sleep(1600);
    all.stop(brake);
    intake.spin(reverse, 100, pct);
    tank(-100, -100);
    sleep(800);
    all.stop(brake);
    break;
  case 2: // Red Tall
    arm.spin(fwd, 100, pct);
    sleep(800);
    arm.rotateTo(0, deg, -1500, dps, true);

    tank(40, 40);
    intake.spin(fwd, 100, pct);
    sleep(1060);
    DT.stop(brake);
    sleep(300);
    intake.stop(brake);

    tank(40, -40);
    sleep(490);
    DT.stop(brake);

    tank(35, 35);
    intake.spin(fwd, 100, pct);
    sleep(1300);
    intake.stop(brake);

    tank(30, -30);
    sleep(600);
    tank(30, 30);
    sleep(270);
    intake.spin(reverse, 30, pct);
    tank(-30, 30);
    sleep(570);
    intake.stop(brake);

    tank(30, 30);
    sleep(500);
    intake.spin(fwd, 100, pct);
    sleep(520);
    DT.stop(brake);
    sleep(400);

    tank(-30, -30);
    sleep(1300);
    intake.stop(brake);
    sleep(900);

    tank(-25, -70);
    sleep(1200);
    tank(30, 30);
    sleep(740);
    tank(35, 10);
    sleep(200);

    intake.spin(reverse, 36, pct);
    sleep(500);
    intake.stop(coast);
    DT.stop(brake);
    dump.spin(fwd, (1560 - dumperPos()) * 0.6, dps);
    sleep(2200);
    dump.stop(brake);

    tank(20, 20);
    sleep(100);
    DT.stop(brake);
    dump.spin(reverse, 1500, dps);
    sleep(1600);
    all.stop(brake);
    intake.spin(reverse, 100, pct);
    tank(-100, -100);
    sleep(800);

    all.stop(brake);
    break;
  case 3: // Red Flat
    tank(-10, -10);
    arm.spin(fwd, 100, pct);
    sleep(800);
    DT.stop(brake);
    arm.rotateTo(0, deg, -1500, dps, true);

    tank(40, 40);
    intake.spin(fwd, 100, pct);
    sleep(2100);
    DT.stop(brake);
    sleep(600);
    intake.stop(brake);
    intake.spin(reverse, 45, pct);
    sleep(400);
    all.stop(brake);

    tank(-40, -40);
    sleep(900);
    tank(30, -30);
    sleep(1070);

    tank(34, 34);
    sleep(1200);
    dump.stop(brake);
    sleep(500);
    intake.spin(reverse, 36, pct);
    sleep(500);
    intake.stop(coast);
    DT.stop(brake);
    dump.spin(fwd, (1560 - dumperPos()) * 0.6, dps);
    sleep(2200);
    dump.stop(brake);

    tank(20, 20);
    sleep(100);
    DT.stop(brake);
    dump.spin(reverse, 1500, dps);
    sleep(1600);
    all.stop(brake);
    intake.spin(reverse, 100, pct);
    tank(-100, -100);
    sleep(800);
    all.stop(brake);
    break;
  }
}
void Drive() {
  thread t_Drive(driver);
  thread t_Macro(macros);

  while (true)
    sleep(20);
}
int main() {
  vexcodeInit();
  dump.resetRotation();
  arm.resetRotation();

  int sidePicked = -1, autonPicked = -1;

  Brain.Screen.drawRectangle(0, 0, 240, 272, blue),
      Brain.Screen.drawRectangle(240, 0, 240, 272, red);
  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      int xPos = Brain.Screen.xPosition();
      sidePicked = ((xPos < 272) ? 0 : 1);
    } else if (Adam.ButtonRight.pressing()) {
      while (Adam.ButtonRight.pressing())
        sleep(0);
      sidePicked = 0;
    } else if (Adam.ButtonY.pressing()) {
      while (Adam.ButtonY.pressing())
        sleep(0);
      sidePicked = 1;
    }
  } while (sidePicked == -1);

  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(0, 0, 240, 272);
  Brain.Screen.setCursor(7, 10);
  Brain.Screen.print("Protected");
  Brain.Screen.drawRectangle(240, 0, 240, 272);
  Brain.Screen.setCursor(7, 33);
  Brain.Screen.print("Unprotected");
  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      int xPos = Brain.Screen.xPosition();
      autonPicked = ((xPos < 272) ? 0 : 1);
    } else if (Adam.ButtonRight.pressing()) {
      while (Adam.ButtonRight.pressing())
        sleep(0);
      autonPicked = 0;
    } else if (Adam.ButtonY.pressing()) {
      while (Adam.ButtonY.pressing())
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

  if (colr == red)
    auton = auton + 2;

  Comp.autonomous(autonomousProgram);
  Comp.drivercontrol(Drive);
}
