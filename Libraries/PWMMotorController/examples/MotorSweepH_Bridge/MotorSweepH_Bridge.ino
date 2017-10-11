/*  MotorSweep Example
 *   Written By: Joey Hines (joey.ahines@gmail.com)
 *   
 *   Sweeps through all the possible speeds for the motor, 
 *   from stopped to full forward.
 */


// Pin 3: PWM Pin
// Pin 4: Enable 1 enables on low
// Pin 5: Enable 2 enables on low


int pwmPin = 3;
int en1 = 4;
int en2 = 5;
  
void setup() {
  //Begin serial to report speed values to the user
  Serial.begin(9600);

  //Set enable pins to output
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
}

bool en1State = LOW;
bool en2State = HIGH;
void loop() {
  //Set Motor Direction
  digitalWrite(en1,en1State); 
  digitalWrite(en2,en1State);
  //Detect direction of motor and print it to console
  if (en1State == LOW) {
    Serial.print("Forward");
  }
  else {
    Serial.print("Forward");
  }
  //Loop from 0 to 255
  for (int i = 0; i <= 255; i++) {
    //Write i to the motor
    analogWrite(pwmPin, i);
    //Print i to screen
    Serial.println(i);
    //Wait 10ms
    delay(10);
  }
  //Loop from 255 to 0
  for (int i = 255; i >= 0; i--) {
    //Write i to the motor
    analogWrite(pwmPin, i);
    //Print i to screen
    Serial.println(i);
    //Wait 25ms
    delay(25);
  }
  //Reverse the motor
  en1State = !en1State;
  en2State = !en2State;
  //Wait two seconds before begining the next sweep
  delay(2000);
}
