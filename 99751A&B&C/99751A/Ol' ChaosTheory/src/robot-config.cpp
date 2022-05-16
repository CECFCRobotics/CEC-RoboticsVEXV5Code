#include "vex.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
competition Competition;
controller Controller;

motor driveMs[2][2] = {
        {motor(PORT1), motor(PORT2, true)},
        {motor(PORT3), motor(PORT4, true)}
      },
      dumper = motor(PORT5, true),
      inTakeMs[2] = {motor(PORT6), motor(PORT7, true)},
      armM = motor(PORT8);

motor_group leftG(driveMs[0][0], driveMs[1][0]),
            rightG(driveMs[0][1], driveMs[1][1]),
            inTake(inTakeMs[0], inTakeMs[1]);

void vexcodeInit(void){}
