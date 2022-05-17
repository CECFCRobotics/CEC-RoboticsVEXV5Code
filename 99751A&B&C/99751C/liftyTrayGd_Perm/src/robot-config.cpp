#include "vex.h"
using namespace vex;

brain Brain;

motor leftMotor(PORT14), rightMotor(PORT12, true), mMotor(PORT13, true),
    lBar(PORT8, true), rBar(PORT1, false), lIntake(PORT6), rIntake(PORT15, true),
    dump(PORT11, true);

motor_group DT(leftMotor, rightMotor), DTM(leftMotor, rightMotor, mMotor),
    bar(lBar, rBar), intake(lIntake, rIntake),
    all(leftMotor, rightMotor, mMotor, lBar, rBar, lIntake, rIntake);

controller Houston(primary), Austin(partner);

void vexcodeInit(void) {}
