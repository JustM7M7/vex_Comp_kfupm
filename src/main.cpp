
#include "vex.h"

using namespace vex;
brain Brain;
motor MotorLF = motor(PORT9);
motor MotorLB = motor(PORT1);
motor MotorRF = motor(PORT10,true);
motor MotorRB = motor(PORT2,true);
motor test1=motor(PORT13);
motor rotor=motor(PORT14,true);
motor ChainMotor = motor(PORT19);
motor ArmMotor = motor(PORT18,true); 
motor HandMotor = motor(PORT16,true); 
digital_out pneumaticR = digital_out(Brain.ThreeWirePort.A);
digital_out pneumaticL = digital_out(Brain.ThreeWirePort.B);
controller Controller = controller();
motor_group MotorGroupR = motor_group(MotorRF, MotorRB);
motor_group MotorGroupL = motor_group(MotorLF, MotorLB);


inertial Inertial = inertial(PORT20);
smartdrive Smartdrive = smartdrive(MotorGroupL, MotorGroupR,Inertial, 330, 300, 390, mm, 1.6);
//drivetrain Drivetrain = drivetrain(MotorGroupL, MotorGroupR, 329.239, 362, 304.8, mm, 1.6);
drivetrain Drivetrain = drivetrain(MotorGroupL, MotorGroupR, 330, 300, 390, mm, 0.723);

competition Competition;


bool pneumaticOut = false;
bool FR_mode = false;
bool Flipped_mode = false;
bool raiseHand = true;
bool rotor1=true;


void pre_auton(void) {
  HandMotor.spinToPosition(0,degrees);
  // rotor.setTimeout(500, msec);
  rotor.spinToPosition(0,degrees);
  pneumaticR.set(true);
  pneumaticL.set(true);
  vexDelay(5000); //Temporary
  Brain.Screen.print("Pre Auto VEX");
  Controller.Screen.setCursor(3, 1);
  Drivetrain.setStopping(coast);
}



void autonomous(void) {
//rotor.spin(forward);
Drivetrain.driveFor(forward, 23.2, inches, 100, rpm);
Drivetrain.turnFor(-22.5, degrees,100,rpm,true);
Drivetrain.driveFor(forward, 17, inches, 100, rpm);
Drivetrain.turnFor(-60, degrees,100,rpm,true);
Drivetrain.driveFor(reverse, 20, inches, 60, rpm);
pneumaticR.set(false);
pneumaticL.set(false);
vexDelay(300);
Drivetrain.driveFor(forward, 17, inches, 100, rpm);

ChainMotor.spin(forward,200,rpm);
vexDelay(1300);
for(int i=0; i<=4; i++){
  rotor.spinToPosition(77,degrees, 200,rpm);
  vexDelay(280);
  rotor.spinToPosition(0,degrees, 200,rpm,false);
  vexDelay(250);
  if(rotor.isDone()==false){
    rotor.spinToPosition(358,degrees, 200,rpm);
    vexDelay(300);
    rotor.setPosition(0,degrees);
  }
}

//Drivetrain.turnFor(-47, degrees,100,rpm,true); 
Drivetrain.driveFor(forward, 17, inches, 200, rpm);
vexDelay(2000);
for(int i=0; i<=4; i++){
  rotor.spinToPosition(77,degrees, 200,rpm);
  vexDelay(280);
  rotor.spinToPosition(0,degrees, 200,rpm,false);
  vexDelay(250);
  if(rotor.isDone()==false){
    rotor.spinToPosition(358,degrees, 200,rpm);
    vexDelay(300);
    rotor.setPosition(0,degrees);
  }
}
//vexDelay(1300);
ChainMotor.stop();
Drivetrain.turnFor(-60, degrees,100,rpm,true);
Drivetrain.driveFor(forward, 45, inches, 100, rpm);


//vexDelay(7000);

//Drivetrain.driveFor(forward, 25, inches, 100, rpm);
//vexDelay(2000);

// for(int i=0; i<=5; i++){
//   rotor.spinToPosition(90,degrees, 200,rpm);
//   vexDelay(300);
//   rotor.spinToPosition(0,degrees, 200,rpm);
// }
// ChainMotor.stop();

// Drivetrain.driveFor(forward, 23.2, inches, 100, rpm);
// Drivetrain.turnFor(-22.5, degrees,100,rpm,true);
// Drivetrain.driveFor(forward, 17, inches, 100, rpm);
// Drivetrain.turnFor(-63, degrees,100,rpm,true);
// Drivetrain.driveFor(reverse, 20, inches, 60, rpm);
// pneumaticR.set(false);
// pneumaticL.set(false);
// Drivetrain.driveFor(forward, 17, inches, 100, rpm);

// pneumaticR.set(false);
// pneumaticL.set(false);
// Drivetrain.turnFor(-22.22222, degrees);
// Drivetrain.driveFor(reverse, 4, inches, 100, rpm);
// Drivetrain.turnFor(26.666666, degrees);
// Drivetrain.driveFor(reverse, 2, inches, 100, rpm);

//Drivetrain.driveFor(reverse, 42, inches, 200, rpm);
//Drivetrain.turnFor(41, degrees);
// Drivetrain.driveFor(reverse, 13, inches, 200, rpm);
//Drivetrain.turnFor(40, degrees);  // in real 90 degrees
//Drivetrain.turnFor(-30, degrees);
//Drivetrain.turnFor(93, degrees);
//Drivetrain.driveFor(forward, -45/0.45, inches, 150, rpm);


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

  raiseHand = !raiseHand;
  if (raiseHand) {
    HandMotor.spinToPosition(0,degrees, 150, rpm);
  }
  else {
    HandMotor.spinToPosition(90,degrees, 150, rpm);
  }

  
  // if (rotor1 == true){
  //     rotor.spin(forward);
  // }
  // else{rotor.stop();}
  // rotor1=!rotor1;








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
void L1released() {

}

void R1released() {
  rotor.spinToPosition(0,degrees, 200,rpm);
}


void R1Pressed() {

  rotor.spinToPosition(77,degrees, 200,rpm);

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
}

void BPressed() {
  // pneumaticOut = !pneumaticOut;
  // pneumaticR.set(pneumaticOut);
  // pneumaticL.set(pneumaticOut);
  // Controller.Screen.setCursor(3, 3);
  // Controller.Screen.clearLine();
  // Brain.Screen.print("Hi\n");
}

void UpPressed() {
Controller.Screen.setCursor(3, 1);
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

void YPressed() {
  rotor.spinToPosition(358,degrees,200,rpm);
  vexDelay(300);
  rotor.setPosition(0, degrees);
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
  //Controller.ButtonLeft.pressed(LeftPressed);
  // test1.spin(forward);
  
  while (1) { 
  wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Controller.Axis1.changed(axisChanged);
  Controller.Axis2.changed(axisChanged);
  Controller.Axis3.changed(axisChanged);
  Controller.Axis4.changed(axisChanged);
  Controller.ButtonL1.pressed(L1Pressed);
  Controller.ButtonL1.released(L1released);
  Controller.ButtonR1.pressed(R1Pressed);
  Controller.ButtonR1.released(R1released);
  Controller.ButtonR2.pressed(R2Pressed);
  Controller.ButtonL2.pressed(L2Pressed);
  Controller.ButtonA.pressed(APressed);
  Controller.ButtonB.pressed(BPressed);
  Controller.ButtonUp.pressed(UpPressed);
  Controller.ButtonDown.pressed(DownPressed);
  Controller.ButtonY.pressed(YPressed);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //First thing is running pre-auto
  // Temporary: Run the User-Control function.
  //autonomous();
  pre_auton();
  autonomous();
  usercontrol();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
