#include "button.h"
using namespace vex;

void driverControl(void){
  while(1){
    //driving
    double axis1 = Controller.Axis1.value(), axis2 = Controller.Axis2.value();
    rightG.spin(fwd, axis2 - axis1, pct);
    leftG.spin(fwd, axis2 + axis1, pct);

    //dumping controls
    Controller.ButtonL1.released(l1);
    Controller.ButtonL2.released(l2);

    double axis3 = Controller.Axis3.value();
    bool down = dumperM.position(degrees) == 0, up =  dumperM.position(degrees) == 140;

    if(axis3 != 0) dumpDir = 0;

    if(axis3 < 0 && !down) dumperM.spin(fwd, axis3, pct);
    else if(dumpDir == -1 && !down) dumperM.spin(reverse, 100, pct);//dump down
    else if(up) dumperM.stop(hold); //If at dump pos hold motor
    else if(axis3 > 0) dumperM.spin(fwd, axis3, pct);
    else if(dumpDir == 1){
      if(dumperM.position(degrees) < 100) dumperM.spin(fwd, 100, pct);
      else dumperM.spin(fwd, 40, pct);
    } else dumperM.stop(coast);

    //In Take
    if(Controller.ButtonR1.pressing()) inTake.spin(fwd, 80, pct);
    else if(Controller.ButtonR2.pressing()) inTake.spin(reverse, 80, pct);
    else inTake.stop(hold);
  }
}

int main() {
  vexcodeInit();
  //bool sideSelected, autonSelected;
  Button red = Button(10, 10, 10, 10, vex::red), 
        blue = Button(30, 10, 10, 10);
        

 /* do{
    
  }while(!sideSelected && !autonSelected);*/

  Competition.drivercontrol(driverControl);
}
