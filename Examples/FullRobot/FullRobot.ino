/*  SimpleRobot
 *  Written By: Joey Hines (joey.ahines@gmail.com)
 *  
 *  Controls one input 
 */

//Include PWM_MotorController library
#include <PWM_MotorController.h>
//Include UTDRWirelessComms
#include <UTDRWirelessComms.h>
#include <SoftwareSerial.h>

//New SoftwareSerial object for UTDRWirelessComms
int rx = 7;   //Connect RX on ESP8266
int tx = 8;   //Connect TX of ESP8266

SoftwareSerial serial(rx,tx);
//Create new UTDRWirelessComms named input
UTDRWirelessComms input = UTDRWirelessComms(&serial);


//Create a PWM_MotorController called motor on pin 3,4, and 5
//RightMotor
// Pin 3: PWM Pin
// Pin 4: In 1
// Pin 5: In 2
//LeftMotor
// Pin 9: PWM Pin
// Pin 10: In 1
// Pin 11: In 2
PWM_MotorController rightMotor = PWM_MotorController(3,4,5);
PWM_MotorController leftMotor = PWM_MotorController(9,10,11);

//Used to track the input that was pressed
char lastActiveInput = 0;

void setup() {
  //Setup Serial
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  //Wait for serial from esp8266
  if (serial.available()) {
    //New int array for storing packet data
    int * packet = new int[3];

    //Get the command packet
    input.getCommandPacket(packet);
    // input[0] : type of input [K,J,B]
    // input[1] : id of input [W,A,S,D...]
    // input[2] : data of input 

    //If the type of the data is Keyboard
    if (packet[0] == 'K') {
      switch(packet[1]) {
        //Case for if the key pressed was W
        case 'w' : 
           //Write data to motor
           if(packet[2] == 1) {
            //Full Speed forward
            rightMotor.writeToMotor(100);
            leftMotor.writeToMotor(100); 
            lastActiveInput = 'w';
           }
           else if (packet[2] == 0 && lastActiveInput == 'w'){
            //Stopped
            rightMotor.writeToMotor(0);  
            leftMotor.writeToMotor(0);  
            lastActiveInput = 0;
           }
           break; //Do not continue into next case 
        //Case for if the key pressed was S
        case 's' : 
           //Write data to motor
           if(packet[2] == 1) {
            //Full Speed backward
            rightMotor.writeToMotor(-100);  
            leftMotor.writeToMotor(-100);   
            lastActiveInput = 's';
           }
           else if (packet[2] == 0 && lastActiveInput == 'a'){
            //Stopped
            rightMotor.writeToMotor(0);  
            leftMotor.writeToMotor(0);  
            lastActiveInput = 0;
           }
           break; //Do not continue into next case 
        //Case for if the key pressed was A
        case 'a' : 
           //Write data to motor
           if(packet[2] == 1) {
            //Rotate Counter-Clockwise
            rightMotor.writeToMotor(100);  
            leftMotor.writeToMotor(-100);   
            lastActiveInput = 'a';
           }
           else if (packet[2] == 0 && lastActiveInput == 'a'){
            //Stopped
            rightMotor.writeToMotor(0);  
            leftMotor.writeToMotor(0);  
            lastActiveInput = 0;
           }
           break; //Do not continue into next case 
        //Case for if the key pressed was D
        case 'd' : 
           //Write data to motor
           if(packet[2] == 1) {
            //Rotate Clockwise
            rightMotor.writeToMotor(-100);  
            leftMotor.writeToMotor(100);   
            lastActiveInput = 'd';
           }
           else if (packet[2] == 0 && lastActiveInput == 'a'){
            //Stopped
            rightMotor.writeToMotor(0);  
            leftMotor.writeToMotor(0);  
            lastActiveInput = 0;
           }
           break; //Do not continue into next case 
        //Default case
        default:
           break;   
      }
    }
    //Clear packet memory
    delete packet;
  }

  delay(20);

}


