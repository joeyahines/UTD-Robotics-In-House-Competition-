/*  MotorSweep Example
 *   Written By: Joey Hines (joey.ahines@gmail.com)
 *   
 *   Sweeps through all the possible speeds for the motor, 
 *   from full reverse to full forward.
 */

//Include PWM_MotorController library
#include <PWM_MotorController.h>

//Create a PWM_MotorController called motor on pin 3,4, and 5
// Pin 3: PWM Pin
// Pin 4: Enable 1
// Pin 5: Enable 2
PWM_MotorController motor = PWM_MotorController(3,5,4);
  
void setup() {
  //Begin serial to report speed values to the user
  Serial.begin(9600);
}

void loop() {
  //Loop from -100 to 100, all the possible speeds of the motor
  for (int i = 0; i <= 100; i++) {
    //Write i to the motor
    motor.writeToMotor(i);
    Serial.println(i);

    //Wait 2 seconds
    delay(100);
  }

  //Stop the motor
  motor.writeToMotor(0);

  //Wait two seconds before begining the next sweep
  delay(2000);

}
