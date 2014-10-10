#pragma config(Motor,  port1,           frontLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1233528)
#pragma config(Motor,  port3,           backRight,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1233528)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,						rightLift1,		 tmotorVex393, openLoop)
#pragma config(Motor,  port6,     			rightLift2,		 tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,		  			leftLift1,		 tmotorVex393, openLoop)
#pragma config(Motor,  port8,						leftLift2,		 tmotorVex393, openLoop, reversed)


#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "PIDController.c"


const int ARMAX = 1800;
const int ARMIN = 0;

void robotShutdown()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
	motor[port9] = 0;
	motor[port10] = 0;
}


void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y + x;
	motor[frontRight] = motor[backRight] = y - x;
}
void driveTank(int l, int r)
{
	motor[frontLeft] = motor[backLeft] = l;
	motor[frontRight] = motor[backRight] = r;
}

void setLiftSpeed(int z)
{
	motor[port5] = motor[port6] = z;
	motor[port7] = motor[port8] = z;
}

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}



task autonomous()
{


	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}



task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
				int driveX = vexRT[Ch4];
		  	int driveY = vexRT[Ch3] ;
		  	int liftSpeed = vexRT[Ch2];
		  	int intakeSpeed = 127*((vexRT[Btn5U])-(vexRT[Btn5D]));

	 			if (vexRT[Btn8U])
	 			{
	  			pidOverride = true;
		  	}
		  	if (vexRT[Btn7U]) {
		  		pidOverride = false;
		  	}

				if (abs(driveY) < 8) driveY = 0; // Drive deadband
				if (abs(driveX) < 8) driveX = 0; // Drive deadband

		  	driveArcade(driveY * 100 / 128, driveX * 100 / 128);
		  	setLiftSpeed(liftSpeed*100/128);
		  	wait1Msec(20);

	}
}
