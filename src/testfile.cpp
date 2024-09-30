#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLF = motor(PORT9);
motor MotorLB = motor(PORT1);
motor MotorRF = motor(PORT10,true);
motor MotorRB = motor(PORT2,true);
motor ChainMotor = motor(PORT19);
motor ArmMotor = motor(PORT18,true); 
digital_out pneumaticR = digital_out(Brain.ThreeWirePort.A);
digital_out pneumaticL = digital_out(Brain.ThreeWirePort.B);
controller Controller = controller();
motor_group MotorGroupR = motor_group(MotorRF, MotorRB);
motor_group MotorGroupL = motor_group(MotorLF, MotorLB);

inertial Inertial = inertial(PORT20);
smartdrive Smartdrive = smartdrive(MotorGroupL, MotorGroupR, Inertial, 330, 300, 390, mm, 1.6);
drivetrain Drivetrain = drivetrain(MotorGroupL, MotorGroupR, 330, 300, 390, mm, 1.6);

competition Competition;

bool pneumaticOut = false;
bool FR_mode = false;
double DownrotationAngle = 125;
double UProtationAngle = 115;

void pre_auton(void) {
  Brain.Screen.print("Pre Auto VEX");
}

void autonomous(void) {
  // Turn the Smart Drivetrain for 90 degrees at 100 rpm.
  Smartdrive.turnFor(90, degrees, 100, rpm);
  // Ensure the turn completes before calling the next command.
  while(true) {
    wait(10, msec);
  }
  
  // Turn the drivetrain for 90 degrees at 100 rpm.
  Drivetrain.turnFor(90, degrees, 100, rpm);
  // Ensure the turn completes before ending the function.
  while(true) {
    wait(10, msec);
  }
}

void handleDriveControl() {
  int32_t drive_left = Controller.Axis3.position();
  int32_t drive_right = Controller.Axis2.position();

  if (!FR_mode) {
    MotorLF.spin(forward, drive_left, percent);
    MotorLB.spin(forward, drive_left, percent);
    MotorRF.spin(forward, drive_right, percent);
    MotorRB.spin(forward, drive_right, percent);
  } else {
    MotorLF.spin(forward, drive_left, percent);
    MotorLB.spin(forward, drive_left, percent);
    MotorRF.spin(forward, drive_left, percent);
    MotorRB.spin(forward, drive_left, percent);
  }
}

void L1Pressed() {
  Brain.Screen.print("L1 button pressed");
  FR_mode = !FR_mode;
}

void R1Pressed() {
  Brain.Screen.print("R1 button pressed");
}

void R2Pressed() {
  Brain.Screen.print("R2 button pressed");
  ChainMotor.spin(reverse, 200, rpm);
  while(Controller.ButtonR2.pressing()) {
    wait(10, msec);
  }
  ChainMotor.stop();
}

void L2Pressed() {
  Brain.Screen.print("L2 button pressed");
  ChainMotor.spin(forward, 200, rpm);
  while(Controller.ButtonL2.pressing()) {
    wait(10, msec);
  }
  ChainMotor.stop(); 
}

void APressed() {
  Brain.Screen.print("A button pressed");
  pneumaticOut = !pneumaticOut;
  pneumaticR.set(pneumaticOut);
  pneumaticL.set(pneumaticOut);
}

void BPressed() {
  Brain.Screen.print("B button pressed");
  ArmMotor.spinToPosition(-DownrotationAngle, degrees, 100, rpm, true);
  ArmMotor.spinToPosition(UProtationAngle, degrees, 100, rpm, false);
}

void usercontrol(void) {
  // Set up callbacks once
  Controller.Axis1.changed(handleDriveControl);
  Controller.Axis2.changed(handleDriveControl);
  Controller.Axis3.changed(handleDriveControl);
  Controller.Axis4.changed(handleDriveControl);
  Controller.ButtonL1.pressed(L1Pressed);
  Controller.ButtonR1.pressed(R1Pressed);
  Controller.ButtonR2.pressed(R2Pressed);
  Controller.ButtonL2.pressed(L2Pressed);
  Controller.ButtonA.pressed(APressed);
  Controller.ButtonB.pressed(BPressed);

  while (true) {
    wait(20, msec); 
  }
}

int main() {
  autonomous();
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
