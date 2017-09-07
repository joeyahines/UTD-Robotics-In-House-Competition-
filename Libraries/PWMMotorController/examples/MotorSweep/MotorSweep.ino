/*  MotorSweep Example
 *   Written By: Joey Hines (joey.ahines@gmail.com)
 *   
 *   Sweeps through all the possible speeds for the motor, 
 *   from full reverse to full forward.
 */

//Include PWM_MotorController library
#include <PWM_MotorController.h>

//Create a PWM_MotorController called motor on pin 3,4, and 5
PWM_MotorController motor = PWM_MotorController(3,4,5);
  
void setup() {
  //Begin serial to report speed values to the user
  Serial.begin(9600);
}

void loop() {
  //Loop from -100 to 100, all the possible speeds of the motor
  for (int i = -100; i <= 100; i++) {
    //Write i to the motor
    motor.writeToMotor(i);

    //Wait 2 seconds
    delay(2000);
  }

  //Stop the motor
  motor.writeToMotor(0);

  //Wait two seconds before begining the next sweep
  delay(2000);

}
