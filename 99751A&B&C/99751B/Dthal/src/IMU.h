#include "defines.h"
using namespace vex;
inertial::quaternion imu_quaternion;
void printImu(bool loop) {
  do {
    // get the quaternion data
    imu_quaternion = imu.orientation();

    Brain.Screen.clearScreen();

    Brain.Screen.setFont(mono15);
    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(black);

    Brain.Screen.printAt(20, 30, "GX  %8.3f", imu.gyroRate(xaxis, dps));
    Brain.Screen.printAt(20, 45, "GY  %8.3f", imu.gyroRate(yaxis, dps));
    Brain.Screen.printAt(20, 60, "GZ  %8.3f", imu.gyroRate(zaxis, dps));

    Brain.Screen.printAt(20, 90, "AX  %8.3f", imu.acceleration(xaxis));
    Brain.Screen.printAt(20, 105, "AY  %8.3f", imu.acceleration(yaxis));
    Brain.Screen.printAt(20, 120, "AZ  %8.3f", imu.acceleration(zaxis));

    Brain.Screen.printAt(20, 150, "A   %8.3f", imu_quaternion.a);
    Brain.Screen.printAt(20, 165, "B   %8.3f", imu_quaternion.b);
    Brain.Screen.printAt(20, 180, "C   %8.3f", imu_quaternion.c);
    Brain.Screen.printAt(20, 195, "D   %8.3f", imu_quaternion.d);

    Brain.Screen.printAt(150, 30, "Roll     %7.2f", imu.roll());
    Brain.Screen.printAt(150, 45, "Pitch    %7.2f", imu.pitch());
    Brain.Screen.printAt(150, 60, "Yaw      %7.2f", imu.yaw());

    Brain.Screen.printAt(150, 90, "Heading  %7.2f", imu.heading());
    Brain.Screen.printAt(150, 105, "Rotation %7.2f", imu.rotation());

    if (imu.isCalibrating())
      Brain.Screen.printAt(20, 225, "Calibration  In Progress");
    else
      Brain.Screen.printAt(20, 225, "Calibration  Done");

    Brain.Screen.render();

    // Allow other tasks to run
    this_thread::sleep_for(20);
  } while (loop);
}
void pneumatic(){
  while(true){
    if( I.ButtonL1.pressing() ) {
      pneum.set( true );
    }
    else {
      pneum.set( false );
    }
  }
}
