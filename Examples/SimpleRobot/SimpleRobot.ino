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
int rx = 8;   //Connect TX on ESP8266
int tx = 7;   //Connect RX of ESP8266

SoftwareSerial serial(rx,tx);
//Create new UTDRWirelessComms named input
UTDRWirelessComms input = UTDRWirelessComms(&serial);


//Create a PWM_MotorController called motor on pin 3,4, and 5
// Pin 3: PWM Pin
// Pin 4: Enable 1
// Pin 5: Enable 2
PWM_MotorController motor = PWM_MotorController(3,5,4);
 
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
            //Full Speed
            motor.writeToMotor(100); 
           }
           else {
            //Stopped
            motor.writeToMotor(0);  
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


