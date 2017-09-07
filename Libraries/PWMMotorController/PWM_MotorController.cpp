/*
  UT Dallas Robotics PWM_MotorController Library v1
  Written by Joey Hines (joey.ahines@gmail.com)
  
  This library allows for easy interfacing to PWM Motor Controllers. 
  The PWM_MotorController class handles all pin setup and pin configuration
  while running the motors so the user only has to pass a percent value to run
  the motors.
  
*/

#include "Arduino.h"

// include this library's description file
#include "PWM_MotorController.h"


/*	PWM_MotorController::PWM_MotorController(int p, int e1, int e2)
 *	Constructor
 *	Accepts the PWM pin and enable pins to initialize PWM_MotorController object
 */
PWM_MotorController::PWM_MotorController(int p, int e1, int e2) {
	PWM_Pin = p;
	en1Pin = e1;
	en2Pin = e2;
	pinMode(en1Pin, OUTPUT);
	pinMode(en2Pin, OUTPUT);
}

/*	int PWM_Motor::convertPercentToMotorValue(int value
 * 	Takes a percent value of -100 % to 100% and converts to a PWM value of
 * 	-255 to 255
 */
int PWM_MotorController::convertPercentToMotorValue(int value) {
	return value * 2.55;
}

/*	void PWM_Motor::writeToMotor(int value)
 * 	Writes a percent speed (-100% to 100%) to a PWM Motor
 */
void PWM_MotorController::writeToMotor(int value) {
	//Converts a percent
	int pwmValue = convertPercentToMotorValue(value);

	//If the PPWM value is positive, set the enable pins to forward
	if (pwmValue > 0) {
		  digitalWrite(en1Pin, HIGH);
		  digitalWrite(en2Pin, LOW);
	}
	//If the PPWM value is negative, set the enable pins to backwards
	else if (pwmValue < 0) {
		digitalWrite(en1Pin, LOW);
		digitalWrite(en2Pin, HIGH);
	}

	//Write the absolute value PWM to the motor
	analogWrite(PWM_Pin, abs(pwmValue));

}


PWM_MotorController::~PWM_MotorController() {}

