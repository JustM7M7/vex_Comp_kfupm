
#include "math.h"
#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLF = motor(PORT9,true);
motor MotorLB = motor(PORT1,true);
motor MotorRF = motor(PORT10);
motor MotorRB = motor(PORT2);

motor_group MotorGroupR = motor_group(MotorRF, MotorRB);
motor_group MotorGroupL = motor_group(MotorLF, MotorLB);

inertial Inertial = inertial(PORT20);
smartdrive Smartdrive = smartdrive(MotorGroupL, MotorGroupR,Inertial, 330, 300, 390, mm, 1.6);
drivetrain Drivetrain = drivetrain(MotorGroupL, MotorGroupR, 330, 300, 390, mm, 1.6);

controller Controller = controller();

competition Competition;


void pre_auton(void) {
  Brain.Screen.print("Pre Auto VEX");
}



void autonomous(void) {
  Brain.Screen.print("Hello KFUPM VEX");
  Brain.Screen.print("Autonomous VEX");
  //Go stright
  MotorLF.spin(forward);
  MotorLB.spin(forward);
  MotorRF.spin(forward);
  MotorRB.spin(forward);

vexDelay(3000);

  //Go Back
  MotorLF.spin(reverse);
  MotorLB.spin(reverse);
  MotorRF.spin(reverse);
  MotorRB.spin(reverse);

  vexDelay(3000);

    //Go Right
   MotorLF.spin(forward);
  MotorLB.spin(forward);
  MotorRF.spin(reverse);
  MotorRB.spin(reverse);
  vexDelay(3000);

     //Go left
  MotorLF.spin(reverse);
  MotorLB.spin(reverse);
  MotorRF.spin(forward);
  MotorRB.spin(forward);
  vexDelay(3000);
  MotorLF.stop();
  MotorLB.stop();
  MotorRF.stop();
  MotorRB.stop();
}

void axisChanged() {
  int32_t drive_left;
  int32_t drive_right;
    drive_left  =  Controller.Axis3.position();
    drive_right =  Controller.Axis2.position();
    MotorLF.spin(forward, drive_left, percent);
    MotorLB.spin(forward, drive_left, percent);
    MotorRB.spin(forward, drive_right, percent);
    MotorRF.spin(forward, drive_right, percent);
    }


void usercontrol(void) {
  while (1) {
  Controller.Axis1.changed(axisChanged);
  Controller.Axis2.changed(axisChanged);
  Controller.Axis3.changed(axisChanged);
  Controller.Axis4.changed(axisChanged);
  wait(20, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
//Drivetrain.turnFor(left,90, degrees,150,rpm);
Smartdrive.turnToHeading(90, degrees,150,rpm);
//Smartdrive.turnFor(left,90, degrees,150,rpm);
 // vexDelay(5000);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }


}
