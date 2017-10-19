/*
  UT Dallas Robotics PWM_MotorController Library v1
  Written by Joey Hines (joey.ahines@gmail.com)
  
  This library allows for easy interfacing to PWM Motor Controllers. 
  The PWM_MotorController class handles all pin setup and pin configuration
  while running the motors so the user only has to pass a percent value to run
  the motors.
  
*/

// ensure this library description is only included once
#ifndef PWM_MotorController_h
#define PWM_MotorController_h

#include "Arduino.h"

class PWM_MotorController {
  
  //Private Class Variables and Functions
  private:
    int PWM_Pin;
	int en1Pin;
	int en2Pin;
	
	int convertPercentToMotorValue(int);
	
  //Public Class Functions
  public:
	void writeToMotor(int value);
	PWM_MotorController(int, int, int);
	PWM_MotorController(int, int);
	~PWM_MotorController();
};

#endif

