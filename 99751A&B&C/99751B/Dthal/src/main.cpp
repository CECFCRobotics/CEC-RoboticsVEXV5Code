#include "drive.h"
using namespace vex;
competition Comp;

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
    } else if (I.ButtonRight.pressing()) {
      while (I.ButtonRight.pressing())
        sleep(0);
      sidePicked = 0;
    } else if (I.ButtonY.pressing()) {
      while (I.ButtonY.pressing())
        sleep(0);
      sidePicked = 1;
    }
  } while (sidePicked == -1);

  Brain.Screen.clearScreen(), Brain.Screen.drawRectangle(0, 0, 240, 272),
      Brain.Screen.setCursor(7, 10), Brain.Screen.print("Left"),
      Brain.Screen.drawRectangle(240, 0, 240, 272),
      Brain.Screen.setCursor(7, 33), Brain.Screen.print("Right");
  do {
    if (Brain.Screen.pressing()) {
      while (Brain.Screen.pressing())
        sleep(0);
      int xPos = Brain.Screen.xPosition();
      autonPicked = ((xPos < 272) ? 0 : 1);
    } else if (I.ButtonLeft.pressing()) {
      while (I.ButtonLeft.pressing())
        sleep(0);
      autonPicked = 0;
    } else if (I.ButtonRight.pressing()) {
      while (I.ButtonRight.pressing())
        sleep(0);
      autonPicked = 1;
    }
  } while (autonPicked == -1);
  auton = autonPicked;

  color colr = (sidePicked == 0) ? blue : red;
  std::string txt = ((auton == 0) ? "Left" : "Right");

  Brain.Screen.clearScreen(colr);
  Brain.Screen.setCursor(6, 23);
  Brain.Screen.setFillColor(colr);
  Brain.Screen.print(txt.c_str());

  if (colr == red)
    auton = auton + 2;

  Comp.drivercontrol(Drive);

  Comp.autonomous(autonomusses);
}
