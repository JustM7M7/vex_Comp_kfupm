
#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLB = motor(PORT1);
motor MotorRB = motor(PORT2,true);
motor ArmMotor = motor(PORT19);
motor ChainMotor = motor(PORT3);
controller Controller = controller();

competition Competition;


void pre_auton(void) {
  Brain.Screen.print("Pre Auto VEX");
}



void autonomous(void) {
  Brain.Screen.print("Hello KFUPM VEX");
  Brain.Screen.print("Autonomous VEX");
  //Go stright
  MotorLB.spin(forward);
  MotorRB.spin(forward);
  vexDelay(3000);

  //Go Back
  MotorLB.spin(reverse);
  MotorRB.spin(reverse);
  vexDelay(3000);

    //Go Right
  MotorLB.spin(forward);
  MotorRB.spin(reverse);
  vexDelay(3000);

     //Go left
  MotorLB.spin(reverse);
  MotorRB.spin(forward);
  vexDelay(3000);

  MotorLB.stop();
  MotorRB.stop();
}

void axisChanged() {
  int32_t drive_left;
  int32_t drive_right;
    drive_left  =  Controller.Axis3.position();
    drive_right =  Controller.Axis2.position();
    MotorLB.spin(forward, drive_left, percent);
    MotorRB.spin(forward, drive_right, percent);
    }

void L1Pressed() {
  Brain.Screen.print("L1 button pressed");
  Controller.Screen.print("L1 button pressed");
  while(Controller.ButtonL1.pressing()) {
    ArmMotor.spin(forward);
  }
  ArmMotor.stop();
}

void R1Pressed() {
  Brain.Screen.print("R1 button pressed");
  Controller.Screen.print("R1 button pressed");
  while(Controller.ButtonR1.pressing()) {
    ArmMotor.spin(reverse);
  }
  ArmMotor.stop();
}

void R2Pressed() {
  Brain.Screen.print("R2 button pressed");
  while(Controller.ButtonR2.pressing()) {
    ChainMotor.spin(forward);
  }
  ChainMotor.stop();
}

void L2Pressed() {
  Brain.Screen.print("L2 button pressed");
  while(Controller.ButtonL2.pressing()) {
    ChainMotor.spin(reverse);
  }
  ChainMotor.stop();
}

void usercontrol(void) {
  while (1) {
  Controller.Axis1.changed(axisChanged);
  Controller.Axis2.changed(axisChanged);
  Controller.Axis3.changed(axisChanged);
  Controller.Axis4.changed(axisChanged);
  Controller.ButtonL1.pressed(L1Pressed);
  Controller.ButtonR1.pressed(R1Pressed);
  Controller.ButtonR2.pressed(R2Pressed);
  Controller.ButtonL2.pressed(L2Pressed);
  wait(20, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  autonomous();
  usercontrol();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
