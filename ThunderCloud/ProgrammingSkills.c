#pragma config(Motor,  port1,           frontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightLift1,    tmotorVex393, openLoop)
#pragma config(Motor,  port6,           rightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port7,           leftLift1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           leftLift2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           rightIntake,   tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftIntake,    tmotorVex393, openLoop, reversed)

#pragma platform(VEX)

//Competition Control and Duration Set	tings
#pragma competitionControl(Competition)
#pragma autonomousDuration(60)
#pragma userControlDuration(0)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                         Driver Skills Template
//
// This is a template for the driver skills competition. It is identical in structure to
// the standard competition template except that the two "#pragma' statements above (and
// copied below) adjust the time limits for the competition.
//				#pragma autonomousDuration(0)
//				#pragma userControlDuration(60)
// The autonomous duration for "Driver Skills" is zero; i.e. there is no autonomous phase.
// The user control duration is 60 seconds
//
// NOTE: The above two pragmas only impact the Crystal implementation. For systems using
//       VEXNET, the VEXNET system ignores these statements as it has the durations
//       for the competition built-in.
//
// Whenever this user program is run, the duration is automatically sent to the VEX master
// processor. The master CPU will only accept these commands once per power=on cycle. So, it's
// best to power cycle your VEX to ensure that they get recognized in case you were
// previously running a standard competition program with different durations.
//
// Testing Via Crystals:
// ====================
//
// The procedure to test a Driver Skills program using the crystals is as follows:
//
// 1. Turn off power to the Crystal transmitter/joysticks.
//
// 2. Turn on your VEX so that the Driver Skills program is running.
//
// 3. Driver skills program segment of your program will start running. At the end of 60
//    seconds the VEX Master CPU will turn off the motors.
//
// 4. Repeat the above sequence
//
//
// Testing Via VEXNET Using VEXNET Competition Switch
// ==================================================
//
// The procedure to test a Driver Skills program using VEXNET Competition Switch is as follows:
//
// 1. Set the two switches on the Competition switch to "DISABLE" and "USER CONTROL"
//
// 2. Start the Driver skills program
//
// 3. Set Switch to ENABLE from DISABLE
//
// 4. You need to manually time the 60 second duration.
//
// 5. Set Switch to DISABLE
//
// 6. Repeat from step (3) to run subsequent test runs. There's no need to reset the VEX or
//    restart your user program.
//
//
// Testing Via VEXNET Using ROBOTC IDE
// ==================================================
//
// It is not necessary to own a VEXNET switch. ROBOTC has a test window that allows the same functionality.
// The test window has three buttons for "DISABLE", "AUTONOMOUS", "USER CONTROL".
//
// 1. Open the ROBOTC Debugger. Then open the "Competition Control" Debugger window.
//
// 2. Start your Driver Skills program running.
//
// 3. Click the "DISABLED" button on the "Competition Control" window.
//
// 4. Click the "USER CONTROL" button on the "Competition Control" window.
//
// 5. You need to manually time the 60 second duration.
//
// 6. Click the "DISABLED" button on the "Competition Control" window.
//
// 7. Repeat from step (4) to run subsequent test runs. There's no need to reset the VEX or
//    restart your user program.
//
/////////////////////////////////////////////////////////////////////////////////////////

void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y - x;
	motor[frontRight] = motor[backRight] = y + x;
}

void setLiftSpeed(int x)
{
	motor[rightLift1] = motor[rightLift2] = x;
	motor[leftLift1] = motor[leftLift2] = x;
}

void setIntakeSpeed(int s)
{
	motor[rightIntake] = motor[leftIntake] = s;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// The "Driver Skills" competition has no autonomous phase. Simply leave the following
// placeholder.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	setLiftSpeed(127);
	wait1Msec(900);
	setLiftSpeed(0);
	driveArcade(127,0);
	wait1Msec(400);
	driveArcade(0,0);
	setIntakeSpeed(-127);
	wait1Msec(2000);
	setIntakeSpeed(0);
	setLiftSpeed(-127);\
	wait1Msec(1000);
	setLiftSpeed(0);
	driveArcade(-127,0);
	wait1Msec(1000);
	driveArcade(0,-127);
	wait1Msec(200);
	driveArcade(-127,0);
	wait1Msec(30000);
	driveArcade(0,0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{

	}
}
