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
	motor[rightLift] = motor[leftLift] z;
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
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
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

		int DriveX = vexRT[Ch4];
		int DriveY = vexRT[Ch3];
		int liftSpeed = vexRT[Ch2];

		if (abs(driveY) < 5) driveY = 0; // Deadband
		if (abs(driveX) < 5) driveX = 0; // Deadband
		if (abs(liftSpeed) < 5) liftSpeed = 0; //Deadband

		driveArcade(driveY, driveX);
		setLiftSpeed(liftSpeed);

		// This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................


	}
}
