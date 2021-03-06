#pragma config(Motor,  port1,           leftRear,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightRear,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void driveArcade(int y, int x)
{
	motor[leftFront] = motor[leftRear] = y - x;
	motor[rightFront] = motor[rightRear] = y + x;
}

void setLiftSpeed(int z)
{
	motor[rightLift] = motor[leftLift] = z;
	//to other programmers, "leftArm" refers to both left arm motors and "rightArm" refers to both right arm motors --Mason
}

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
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	driveArcade(100, 100);
	wait1Msec(10000);
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
		bool tankdrive = false; //enable tankdrive???

		while (tankdrive==false)
		{
			int DriveX = -vexRT[Ch4];
			int DriveY = vexRT[Ch3];
			int liftSpeed = vexRT[Ch2];

				if (abs(DriveY) < 5) DriveY = 0; // Deadband
				if (abs(DriveX) < 5) DriveX = 0; // Deadband
				if (abs(liftSpeed) < 5) liftSpeed = 5; //Deadband and Keep String Taught

			driveArcade(DriveY, DriveX);
			setLiftSpeed(liftSpeed);
	}
		while (tankdrive==true) //Tank Drive Option For Debugging DriveTrain
	{
			motor[leftRear] = motor[leftFront] = vexRT[Ch3];
			motor[rightRear] = motor[rightFront] = vexRT[Ch2];

		}

		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joystick values to update your motors, etc.
		// .....................................................................................


}
}
