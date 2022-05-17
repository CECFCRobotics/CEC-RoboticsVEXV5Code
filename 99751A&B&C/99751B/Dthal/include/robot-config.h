using namespace vex;

extern brain Brain;

extern motor frontLeftMotor;
extern motor frontRightMotor;
extern motor backLeftMotor;
extern motor backRightMotor;
extern motor leftLowInt;
extern motor rightLowInt;
extern motor leftHighInt;
extern motor rightHighInt;


extern motor_group leftMotor;
extern motor_group rightMotor;
extern motor_group DT;
extern motor_group lowInt;
extern motor_group highInt;
extern motor_group all;

extern controller I;
extern controller U;

extern encoder leftEnc;
extern encoder rightEnc;

extern sonar sonic;

extern limit lim;

extern pot barPoti;

extern inertial imu;

extern pneumatics pneum;

void vexcodeInit(void);
