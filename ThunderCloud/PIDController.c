/* PID Controller for Vex
 *
 * P: Proportional
 * I: Integral
 * D: Derivative
 *
 * PID Controllers are used to calulate the error between the current position and a setpoint.
 * It uses this error to calculate an output for the current position to reach the setpoint.
 *
 * Based on how large the error is, the P constant is used to proportionally increase or
 *	decrease the output to correct it. If there is a large amount of error between your current
 *  position and your setpoint then your output will be large.
 *
 * The I constant is used with the accumulated error to boost the output as error exists over
 *  time If your P value isn't correcting your error over a large period of time, then the more
 *  accumulated error you have, the greater the output will be.
 *
 * The D part of PID calculates the change in error between the current calculation and the
 *  previous calculation. You can use this to increase or decrease the speed of stabalization
 *  as you reach your setpoint.
 *
 * To summarize this, P jumps you to your setpoint, I gives you a boost, and D stabilizes you!
 */

typedef struct {
	bool enabled;
	float kP, kI, kD;
	int setpoint;
	int maxOutput, minOutput;
	int error, totalError, prevError;
} PIDController;

void init(PIDController controller, float kP, float kI, float kD) {
	controller.kP = kP;
	controller.kI = kI;
	controller.kD = kD;
}
void setSetpoint(PIDController controller, int setpoint) {
	controller.setpoint = setpoint;
	controller.totalError = 0.0;
	controller.prevError = 0.0;
}
void setThresholds(PIDController controller, int max, int min) {
	controller.maxOutput = max;
	controller.minOutput = min;
}
void setEnabled(PIDController controller, bool en) {
	controller.enabled = en;
}
int calculate(PIDController controller, int input) {
	if (!controller.enabled) {
		return 0.0;
	}
	controller.error = controller.setpoint - input;
	controller.totalError += controller.error;

	float output = (controller.kP * controller.error +
               	controller.kI * controller.totalError +
               	controller.kD * (controller.prevError - controller.error));

	if (controller.maxOutput != 0 && controller.minOutput != 0) {
		if (output > controller.maxOutput) {
			output = controller.maxOutput;
		}
		if (output < controller.minOutput) {
			output = controller.minOutput;
		}
	}

	controller.prevError = controller.error;
	return output;
}
bool atTarget(PIDController controller, int errorThresh) {
	return abs(controller.error) < errorThresh;
}
