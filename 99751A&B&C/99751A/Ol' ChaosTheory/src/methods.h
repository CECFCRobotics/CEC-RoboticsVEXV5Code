#include "vex.h"
using namespace vex;

int dumpDir = -1;

void driveBrake(brakeType brake){
  leftG.stop(brake);
  rightG.stop(brake);
}

void driveBrake(){ 
  leftG.stop();
  rightG.stop();
}

void stopAllMotors(){
  driveBrake();
  armM.stop(hold);
  inTake.stop(hold);
  dumperM.stop();
}

void rest(uint32_t time){ task::sleep(time); }

void rest(){ rest(100); }

void tankDrive(double leftVal, double rightVal){
  leftG.spin(fwd, leftVal, pct);
  rightG.spin(fwd, rightVal, pct);
}

void tankTime(double leftVal , double rightVal, int time){
  tankDrive(leftVal, rightVal);
  rest(time);
}

void l1() { dumpDir = 1; }
void l2() { dumpDir = -1;}
