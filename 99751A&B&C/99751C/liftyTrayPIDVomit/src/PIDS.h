#include "varsNvoids.h"
using namespace vex;

const float pid_Kp = 0.5;  // 1.2
const float pid_Ki = 0.05; // 1.05
const float pid_Kd = 0.55; // 0.0

void pidControlBar(int pidRequestedValue) {
  bool pBar;
  float pidErrorL, pidErrorR, pidLastErrorL, pidLastErrorR,
      pidCurrentSensorValueL, pidCurrentSensorValueR, pidBarL, pidBarR,
      pidIntegralL, pidIntegralR, pidDerivativeL, pidDerivativeR, pTime;

  lBar.resetRotation(), rBar.resetRotation();

  pidLastErrorL = 0, pidLastErrorR = 0, pidIntegralL = 0, pidIntegralR = 0;

  while (true) {
    pidCurrentSensorValueL = leftBarPos(),
    pidCurrentSensorValueR = rightBarPos();

    // Proportional Part
    pidErrorL = pidCurrentSensorValueL - pidRequestedValue,
    pidErrorR = pidCurrentSensorValueR - pidRequestedValue;

    // Integral Part
    if (pid_Ki != 0) {
      if (((fabs(pidErrorL) + fabs(pidErrorR)) / 2) < 50)
        pidIntegralL = pidIntegralL + pidErrorL,
        pidIntegralR = pidIntegralR + pidErrorR;
      else
        pidIntegralL = 0, pidIntegralR = 0;
    } else {
      pidIntegralL = 0, pidIntegralR = 0;
    }

    // Derivative Part
    pidDerivativeL = pidErrorL - pidLastErrorL, pidLastErrorL = pidErrorL;
    pidDerivativeR = pidErrorR - pidLastErrorR, pidLastErrorR = pidErrorL;

    // Calculating the motor speed
    pidBarL = (pid_Kp * pidErrorL) + (pid_Ki * pidIntegralL) +
              (pid_Kd * pidLastErrorL);
    pidBarR = (pid_Kp * pidErrorR) + (pid_Ki * pidIntegralR) +
              (pid_Kd * pidLastErrorR);

    if (leftBarPos() >= rightBarPos())
      pTime = pidRequestedValue - leftBarPos() + 1000;
    else
      pTime = pidRequestedValue - rightBarPos() + 1000;

    lBar.spin(dir(pidRequestedValue, leftBarPos()), pidBarL, dps);
    rBar.spin(dir(pidRequestedValue, rightBarPos()), pidBarR, dps);

    if (lBar.rotation(deg) >= pidRequestedValue)
      lBar.stop(brake);
    if (rBar.rotation(deg) >= pidRequestedValue)
      rBar.stop(brake);
    if (bar.rotation(deg) >= pidRequestedValue)
      pBar = false;
    else
      pBar = true;
  }
}

void pidControlDrive(int pidRequestedValue) {
  bool pDrive;
  float pidErrorL, pidErrorR, pidLastErrorL, pidLastErrorR,
      pidCurrentSensorValueL, pidCurrentSensorValueR, pidDriveL, pidDriveR,
      pidIntegralL, pidIntegralR, pidDerivativeL, pidDerivativeR, pTime;

  leftMotor.resetRotation(), rightMotor.resetRotation();

  pidLastErrorL = 0, pidLastErrorR = 0, pidIntegralL = 0, pidIntegralR = 0;
  pDrive = true;
  while (pDrive) {
    pidCurrentSensorValueL = leftDTPos(), pidCurrentSensorValueR = rightDTPos();

    // Proportional Part
    pidErrorL = pidCurrentSensorValueL - pidRequestedValue,
    pidErrorR = pidCurrentSensorValueR - pidRequestedValue;

    // Integral Part
    if (pid_Ki != 0) {
      if (((fabs(pidErrorL) + fabs(pidErrorR)) / 2) < 50)
        pidIntegralL = pidIntegralL + pidErrorL,
        pidIntegralR = pidIntegralR + pidErrorR;
      else
        pidIntegralL = 0, pidIntegralR = 0;
    } else {
      pidIntegralL = 0, pidIntegralR = 0;
    }

    // Derivative Part
    pidDerivativeL = pidErrorL - pidLastErrorL, pidLastErrorL = pidErrorL;
    pidDerivativeR = pidErrorR - pidLastErrorR, pidLastErrorR = pidErrorL;

    // Calculating the motor speed
    pidDriveL = (pid_Kp * pidErrorL) + (pid_Ki * pidIntegralL) +
                (pid_Kd * pidLastErrorL);
    pidDriveR = (pid_Kp * pidErrorR) + (pid_Ki * pidIntegralR) +
                (pid_Kd * pidLastErrorR);

    if (leftDTPos() >= rightDTPos())
      pTime = pidRequestedValue - leftDTPos() + 1000;
    else
      pTime = pidRequestedValue - rightDTPos() + 1000;

    leftMotor.spin(dir(pidRequestedValue, leftDTPos()), -pidDriveL, dps);
    rightMotor.spin(dir(pidRequestedValue, rightDTPos()), -pidDriveR, dps);

    if (leftMotor.rotation(deg) >= pidRequestedValue)
      leftMotor.stop(brake);
    if (rightMotor.rotation(deg) >= pidRequestedValue)
      rightMotor.stop(brake);
    if (DT.rotation(deg) >= pidRequestedValue)
      pDrive = false;
    else
      pDrive = true;
  }
}
