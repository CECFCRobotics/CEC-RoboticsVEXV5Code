using namespace vex;

extern brain Brain;

extern motor leftMotor;
extern motor rightMotor;
extern motor mMotor;
extern motor lBar;
extern motor rBar;
extern motor lIntake;
extern motor rIntake;
extern motor dump;

extern motor_group DT;
extern motor_group DTM;
extern motor_group bar;
extern motor_group intake;
extern motor_group all;

extern controller Houston;
extern controller Austin;

extern line lDLine;
extern line rDline;
extern line bottomLine;
extern line topLine;

extern limit up;
extern limit down;

extern sonar ultrasonic;

void vexcodeInit(void);
