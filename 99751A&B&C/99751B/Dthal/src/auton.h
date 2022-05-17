#include "pos.h"
void goDistance(int spd, double distanceIn) {
  double circumference = M_PI * (2 * wheelRadius);
  double degToRotate = ((360 * distanceIn) / circumference);

  leftMotor.rotateFor(fwd, degToRotate, deg, spd, velocityUnits::pct);
  rightMotor.rotateFor(fwd, degToRotate, deg, spd, velocityUnits::pct);
}
void translate(int units, int spd) { // unknown inches to units
  int Direction = abs(units) / units;

  DT.resetRotation();
  imu.resetHeading();

  while (avgDriveEncVal() < abs(units)) {
    tank(spd * Direction + imu.heading(), spd * Direction + imu.heading());
    sleep(10);
  }
  tank(-10 * Direction, -10 * Direction);
  sleep(50);
  DT.stop(brake);
}
double avgDTVal() {
  return (fabs(frontLeftMotor.position(deg)) +
          fabs(frontRightMotor.position(deg)) +
          fabs(backLeftMotor.position(deg)) +
          fabs(backRightMotor.position(deg))) /
         4;
}
void sideTranslate(int units, int spd) { // Left- Right+
  int Direction = abs(units) / units;

  DT.resetRotation();

  while (avgDTVal() < abs(units)) {
    frontLeftMotor.spin(fwd, spd * Direction, pct),
        frontRightMotor.spin(reverse, spd * Direction, pct),
        backLeftMotor.spin(reverse, spd * Direction, pct),
        backRightMotor.spin(fwd, spd * Direction, pct);
    sleep(10);
  }
  frontLeftMotor.spin(fwd, -10 * Direction, pct),
      frontRightMotor.spin(reverse, -10 * Direction, pct),
      backLeftMotor.spin(reverse, -10 * Direction, pct),
      backRightMotor.spin(fwd, -10 * Direction, pct);
  sleep(50);
  DT.stop(brake);
}
void rotate(int degrees, int spd) {
  int Direction = abs(degrees) / degrees;

  imu.resetHeading();

  tank(-spd * Direction, spd * Direction);
  while (fabs(imu.heading()) < abs(degrees) - 5) {
    sleep(10);
  }
  sleep(100);
  if (fabs(imu.heading()) > abs(degrees)) {
    tank(0.5 * spd * Direction, 0.5 * -spd * Direction);
    while (fabs(imu.heading()) > abs(degrees)) {
      sleep(10);
    }
  } else if (fabs(imu.heading()) < abs(degrees)) {
    tank(0.5 * -spd * Direction, 0.5 * spd * Direction);
    while (fabs(imu.heading()) < abs(degrees)) {
      sleep(10);
    }
  }
  DT.stop(brake);
}
void autonomusses() {
  switch (auton) {
  case 0: // Blue Right

    break;
  case 1: // Blue Left

    break;
  case 2: // Red Right
      sideTranslate(-200, 50);
      rotate(45, 40);
      sideTranslate(-400, 50);
      lowInt.spin(fwd, 75, pct);
      translate(550, 50);
      
    break;
  case 3: // Red Left

    break;
  }
}
