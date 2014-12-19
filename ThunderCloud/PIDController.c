/* PID Controller for Vex
 *
 * P: Proportional
 * I: doubleegral
 * D: Derivative
 *
 * PID Controllers are used to calulate the error between the current position and a setpodouble.
 * It uses this error to calculate an output for the current position to reach the setpodouble.
 *
 * Based on how large the error is, the P constant is used to proportionally increase or
 *	decrease the output to correct it. If there is a large amount of error between your current
 *  position and your setpodouble then your output will be large.
 *
 * The I constant is used with the accumulated error to boost the output as error exists over
 *  time If your P value isn't correcting your error over a large period of time, then the more
 *  accumulated error you have, the greater the output will be.
 *
 * The D part of PID calculates the change in error between the current calculation and the
 *  previous calculation. You can use this to increase or decrease the speed of stabalization
 *  as you reach your setpodouble.
 *
 * To summarize this, P jumps you to your setpodouble, I gives you a boost, and D stabilizes you!
 */

typedef struct {
	bool enabled;
	double kP, kI, kD;
	double setpodouble;
	double maxOutput, minOutput;
	double error, totalError, prevError;
} PIDController;

void init(PIDController controller, double kP, double kI, double kD) {
	controller.kP = kP;
	controller.kI = kI;
	controller.kD = kD;
}
void setSetpoint(PIDController controller, double setpodouble) {
	controller.setpodouble = setpodouble;
	controller.totalError = 0.0;
	controller.prevError = 0.0;
}
void setThresholds(PIDController controller, double max, double min) {
	controller.maxOutput = max;
	controller.minOutput = min;
}
void setEnabled(PIDController controller, bool en) {
	controller.enabled = en;
}
double calculate(PIDController controller, double input) {
	if (!controller.enabled) {
		return 0.0;
	}
	controller.error = controller.setpodouble - input;
	controller.totalError += controller.error;

	double output = (controller.kP * controller.error +
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
bool atTarget(PIDController controller, double errorThresh) {
	return abs(controller.error) < errorThresh;
}
