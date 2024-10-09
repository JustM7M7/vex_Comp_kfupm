
#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLF = motor(PORT9);
motor MotorLB = motor(PORT1);
motor MotorRF = motor(PORT10,true);
motor MotorRB = motor(PORT2,true);
// motor test1=motor(PORT13);
// motor test2=motor(PORT14,true);
motor ChainMotor = motor(PORT19);
motor ArmMotor = motor(PORT18,true); 
digital_out pneumaticR = digital_out(Brain.ThreeWirePort.A);
digital_out pneumaticL = digital_out(Brain.ThreeWirePort.B);
controller Controller = controller();
motor_group MotorGroupR = motor_group(MotorRF, MotorRB);
motor_group MotorGroupL = motor_group(MotorLF, MotorLB);

inertial Inertial = inertial(PORT20);
smartdrive Smartdrive = smartdrive(MotorGroupL, MotorGroupR,Inertial, 330, 300, 390, mm, 1.6);
drivetrain Drivetrain = drivetrain(MotorGroupL, MotorGroupR, 330, 300, 390, mm, 1.6);


competition Competition;


bool pneumaticOut = false;
bool FR_mode = false;
bool Flipped_mode = false;
double DownrotationAngle = 125;
double UProtationAngle = 115;


void pre_auton(void) {
  Brain.Screen.print("Pre Auto VEX");
  Controller.Screen.setCursor(3, 1);
}



void autonomous(void) {
Drivetrain.driveFor(30,inches);
  Drivetrain.turnFor(90, degrees);
  Drivetrain.driveFor(10,inches);
  Drivetrain.turnFor(-90, degrees);
  ChainMotor.spin(forward,200,rpm);
  wait(30,msec);
  ChainMotor.stop();
  Drivetrain.driveFor(-10,inches);
  Drivetrain.turnFor(180,degrees);

}

void axisChanged() {
  int32_t drive_left;
  int32_t drive_right;
    drive_left  =  Controller.Axis2.position();
    drive_right =  Controller.Axis3.position();
    if (!FR_mode && !Flipped_mode) {
    MotorLF.spin(forward, drive_left, percent);
    MotorLB.spin(forward, drive_left, percent);
    MotorRB.spin(forward, drive_right, percent);
    MotorRF.spin(forward, drive_right, percent);
    }

    else if (!FR_mode && Flipped_mode) {
    MotorLF.spin(reverse, drive_right, percent);
    MotorLB.spin(reverse, drive_right, percent);
    MotorRB.spin(reverse, drive_left, percent);
    MotorRF.spin(reverse, drive_left, percent);
    }

    else if (FR_mode && !Flipped_mode) {
    MotorLF.spin(forward, drive_left, percent);
    MotorLB.spin(forward, drive_left, percent);
    MotorRB.spin(forward, drive_left, percent);
    MotorRF.spin(forward, drive_left, percent);
    }

    else {
    MotorLF.spin(reverse, drive_left, percent);
    MotorLB.spin(reverse, drive_left, percent);
    MotorRB.spin(reverse, drive_left, percent);
    MotorRF.spin(reverse, drive_left, percent);
    }
    }


void L1Pressed() {
  // Controller.Screen.setCursor(3, 3);
  // Controller.Screen.clearLine();
  // Brain.Screen.clearScreen();
  // Brain.Screen.print("L1 button pressed");
  // FR_mode = !FR_mode;
  // if (FR_mode && Flipped_mode) {
  //   Controller.Screen.print("FR & Rev");
  // }
  // else if (!FR_mode && Flipped_mode) {
  //   Controller.Screen.print("FRLR & Rev");
  // }
  // else if (FR_mode && !Flipped_mode) {
  //   Controller.Screen.print("FR & Nor");
  // }
  // else {
  //   Controller.Screen.print("FRLR & Nor");
  // }

}

void R1Pressed() {
  Brain.Screen.print("R1 button pressed");
}

void R2Pressed() {
  Brain.Screen.print("R2 button pressed");
  while(Controller.ButtonR2.pressing()) {
    ChainMotor.spin(reverse,200,rpm);
  }
  ChainMotor.stop();
}

void L2Pressed() {
  Brain.Screen.print("L2 button pressed");
  while(Controller.ButtonL2.pressing()) {
    ChainMotor.spin(forward,200,rpm);
  }
  ChainMotor.stop(); 
}

void APressed() {
  pneumaticOut = !pneumaticOut;
  pneumaticR.set(pneumaticOut);
  pneumaticL.set(pneumaticOut);
  Controller.Screen.setCursor(3, 3);
  Controller.Screen.clearLine();
  Brain.Screen.print("Hi\n");
  //Sometimes this doesn't work for some reason?
}

void BPressed() {
Brain.Screen.print("B button pressed");
ArmMotor.spinToPosition(-DownrotationAngle,degrees,100,rpm,true);
ArmMotor.spinToPosition(UProtationAngle,degrees,100,rpm,false);
}

void UpPressed() {
Controller.Screen.setCursor(3, 3);
Brain.Screen.clearScreen();
Controller.Screen.clearLine();
wait(20,msec);
//Brain.Screen.print("Down button pressed");
Flipped_mode = false;
if (FR_mode) {
  Controller.Screen.print("FR and Normal");
  }
else {
  Controller.Screen.print("FRLR and Normal");
  }
}

void DownPressed() {
 Controller.Screen.setCursor(3, 3);
Brain.Screen.clearScreen();
Controller.Screen.clearLine();
Brain.Screen.print("Down button pressed");
Flipped_mode = true;
if (FR_mode) {
  Controller.Screen.print("FR and Flipped");
}
else {
  Controller.Screen.print("FRLR (F)");
}
}


void usercontrol(void) {
  Controller.Axis1.changed(axisChanged);
  Controller.Axis2.changed(axisChanged);
  Controller.Axis3.changed(axisChanged);
  Controller.Axis4.changed(axisChanged);
  Controller.ButtonL1.pressed(L1Pressed);
  Controller.ButtonR1.pressed(R1Pressed);
  Controller.ButtonR2.pressed(R2Pressed);
  Controller.ButtonL2.pressed(L2Pressed);
  Controller.ButtonA.pressed(APressed);
  Controller.ButtonB.pressed(BPressed);
  Controller.ButtonUp.pressed(UpPressed);
  Controller.ButtonDown.pressed(DownPressed);
  //Controller.ButtonLeft.pressed(LeftPressed);
  while (1) { 
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
  //First thing is running pre-auto
  // Temporary: Run the User-Control function.
  //autonomous();
  autonomous();
  usercontrol();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
