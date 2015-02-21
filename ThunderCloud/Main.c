#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  cubeGrabber,    sensorDigitalOut)
#pragma config(Sensor, dgtl2,  autonButton,    sensorTouch)
#pragma config(Motor,  port1,           frontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightLift1,    tmotorVex393, openLoop)
#pragma config(Motor,  port6,           rightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port7,           leftLift1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           leftLift2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           intake,        tmotorVex393, openLoop)
#pragma config(Motor,  port10,          centerDrive,   tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "PIDController.c"
PIDController liftPID;

const int ARMAX = 1800;
const int ARMIN = 0;
bool solExtended = false;

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
	SensorValue[cubeGrabber] = 0;
}

void initPID()
{
	init(liftPID,127/70,0,0);
	setThresholds(liftPID, 128, -127);
}

void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y - x;
	motor[frontRight] = motor[backRight] = y + x;
}
void driveTank(int l, int r)
{
	motor[frontLeft] = motor[backLeft] = l;
	motor[frontRight] = motor[backRight] = r;
}

void driveH(int x,int y, int r)
{
		driveArcade(y,r);
		motor[centerDrive] = x;
}

void setLiftSpeed(int x)
{
	motor[rightLift1] = motor[rightLift2] = x;
	motor[leftLift1] = motor[leftLift2] = x;
}

void setIntakeSpeed(int s)
{
	motor[intake] = s;
}

void setCubeGrabber()
{
	if(solExtended)
	{
		SensorValue[cubeGrabber] = 0;
	}
	else
	{
		SensorValue[cubeGrabber] = 1;
	}
	solExtended = !solExtended;
}


void pre_auton()
{
	initPID();
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
	SensorValue[armPot] = 0;
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}



task autonomous()
{
	/*setLiftSpeed(127); old
	wait1Msec(700);
	setLiftSpeed(0);
	driveArcade(127,0);
	wait1Msec(400);
	driveArcade(0,0);
	setIntakeSpeed(-127);
	wait1Msec(2000);
	setIntakeSpeed(0);
	driveArcade(-127,0);
	wait1Msec(400);
	driveArcade(0,0);
	*/
	driveArcade(127,0);	//pick up extra cube
	wait1Msec(500);
	setIntakeSpeed(127);
	wait1Msec(300);
	setIntakeSpeed(0);
	driveArcade(-127,0);
	wait1Msec(500);
	driveArcade(0,0);

	while(!SensorValue[autonButton]){}

	setLiftSpeed(127);	//drop cubes
	wait1Msec(700);
	setLiftSpeed(0);
	driveArcade(127,0);
	wait1Msec(400);
	driveArcade(0,0);
	setIntakeSpeed(-127);
	wait1Msec(2000);
	setIntakeSpeed(0);
	driveArcade(-127,0);
	wait1Msec(400);
	driveArcade(0,0);
}



task usercontrol()
{
	// User control code here, inside the loop
	while (true)
	{
				int driveX = vexRT[Ch4];
		  	int driveY = vexRT[Ch3] ;
		  	int driveS = vexRT[Ch1];
		  	int liftSpeed = vexRT[Ch2];


				if (abs(driveY) < 8) driveY = 0; // Drive deadband
				if (abs(driveX) < 8) driveX = 0; // Drive deadband
				if (abs(liftSpeed) < 8) liftSpeed = 0; // Lift deadband & armPot in bounds

				if(liftSpeed!=0)
				{
					setSetpoint(liftPID, SensorValue[armPot]);
					setLiftSpeed(liftSpeed * 100 / 128);
				}
				else
				{
					setLiftSpeed(calculate(liftPID,	SensorValue[armPot]));
				}

		  	//driveArcade(driveY * 100 / 128, driveX * 100 / 128);
				driveH(driveY * 100 / 128, driveS * 100 / 128, driveX * 100 / 128);

		  	if(vexRT[Btn6U]==1)
		  	{
		  		setIntakeSpeed(127);
		  	}
		  	else if(vexRT[Btn5U]==1)
		  	{
		  		setIntakeSpeed(-127);
		  	}
		  	else
		  	{
		  		setIntakeSpeed(0);
		  	}
		  	wait1Msec(20);

	}
}
