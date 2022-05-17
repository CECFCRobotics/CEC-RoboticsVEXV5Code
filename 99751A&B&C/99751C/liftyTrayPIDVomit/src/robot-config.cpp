#include "vex.h"
using namespace vex;

brain Brain;

motor leftMotor(PORT14), rightMotor(PORT12, true), mMotor(PORT13, true),
    lBar(PORT8, true), rBar(PORT17, false), lIntake(PORT16),
    rIntake(PORT18, true), dump(PORT11, true);

motor_group DT(leftMotor, rightMotor), DTM(leftMotor, rightMotor, mMotor),
    bar(lBar, rBar), intake(lIntake, rIntake),
    all(leftMotor, rightMotor, mMotor, lBar, rBar, lIntake, rIntake);

controller Houston(primary), Austin(partner);

line lDLine(Brain.ThreeWirePort.A), rDline(Brain.ThreeWirePort.B),
    bottomLine(Brain.ThreeWirePort.C), topLine(Brain.ThreeWirePort.D);

limit up(Brain.ThreeWirePort.E), down(Brain.ThreeWirePort.F);

sonar ultrasonic(Brain.ThreeWirePort.G);

void vexcodeInit(void) {}
