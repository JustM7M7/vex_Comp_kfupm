/*
#include "math.h"
#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLF = motor(PORT9);
motor MotorLB = motor(PORT1);
motor MotorRF = motor(PORT10,true);
motor MotorRB = motor(PORT2,true);
controller Controller = controller();

digital_out digoutA = digital_out(Brain.ThreeWirePort.A);
digital_out digoutB = digital_out(Brain.ThreeWirePort.B);


competition Competition;




void autonomous1(void) {
 digoutA.set(true);
digoutB.set(true);
vexDelay(3000);
 digoutA.set(false);
digoutB.set(false);
}



//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous1);
  // Run the pre-autonomous function.
  //pre_auton();
  autonomous1();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

*/