#include "vex.h"
using namespace vex;
void sleep(int mSec) { task::sleep(mSec); }

directionType dir(int first, int second) {
  return ((first >= second) ? fwd : reverse);
}

long double leftPos() { return leftEnc.rotation(deg); }
long double rightPos() { return rightEnc.rotation(deg); }

const double sl = 7.25; // Left-right distance from the tracking center to the
                        // left tracking wheel
const double sr = 7.25; // Left-right distance from the tracking center to the
                        // right tracking wheel
const double ss = 7.75; // Forward-backward distance from the tracking center to
                        // the back tracking wheel
double thetaNaut,
    thetaR; // Previous global orientation, global orientation at last reset

double l, lError, Dl, r, rError, Dr, Dtheta, degs;
double rR;        // Radius of the tracking center's arc, radius of 'the arc'
double Ddly, Ddl; // Change in Y and change in second arc x/y
double radius;
double vt, vy;
int auton = 0;
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
void sideTank(int tspd, int btspd) {
  frontLeftMotor.spin(fwd, tspd, pct), frontRightMotor.spin(reverse, tspd, pct),
      backLeftMotor.spin(reverse, btspd, pct), backRightMotor.spin(fwd, btspd, pct);
}
void driveBrake(int type){ // 0 = hold, 1 = brake, 2 = coast
if(type == 0){ leftMotor.stop(hold); rightMotor.stop(hold);
}else if(type == 1){ leftMotor.stop(brake); rightMotor.stop(brake);
}else if(type == 2){ leftMotor.stop(coast); rightMotor.stop(coast);
}else{ leftMotor.stop(brake); rightMotor.stop(brake); }
}
void tank2(bool doTime, int time, int lspd, int rspd, bool stop, int stopType){ // negative goes backwards
  leftMotor.spin(fwd, lspd, dps);
  rightMotor.spin(fwd, rspd, dps);
  if(doTime == true){sleep(time);
  }else{}
  if(stop == true){ driveBrake(stopType);
  }else { }
}
const float pid_Kp = 0.5;  // 1.2
const float pid_Ki = 0.05; // 1.05
const float pid_Kd = 0.55; // 0.0
#define wheelRadius 2
double avgDriveEncVal() { return (fabs(leftPos()) + fabs(rightPos())) / 2; }
