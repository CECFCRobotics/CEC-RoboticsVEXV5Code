#include "vex.h"

using namespace vex;

brain Brain;

motor frontLeftMotor(PORT1, false), frontRightMotor(PORT2, true),
    backLeftMotor(PORT7, false), backRightMotor(PORT8, true),
    leftLowInt(PORT3, false), rightLowInt(PORT4, true),
    leftHighInt(PORT5, false), rightHighInt(PORT6, true);

motor_group DT(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor),
    leftMotor(frontLeftMotor, backLeftMotor),
    rightMotor(frontRightMotor, backRightMotor),
    lowInt(leftLowInt, rightLowInt), highInt(leftHighInt, rightHighInt),
    all(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor, leftLowInt, rightLowInt, leftHighInt,
        rightHighInt);

controller I(primary), U(partner);

encoder leftEnc(Brain.ThreeWirePort.A), rightEnc(Brain.ThreeWirePort.C);

sonar sonic(Brain.ThreeWirePort.E);

limit lim(Brain.ThreeWirePort.G);

pot barPoti(Brain.ThreeWirePort.H);

inertial imu(PORT9);

pneumatics pneum(Brain.ThreeWirePort.B);

void vexcodeInit(void) {}
