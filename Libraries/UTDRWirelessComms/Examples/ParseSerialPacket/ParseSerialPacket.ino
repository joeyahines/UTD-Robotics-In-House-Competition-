/*  ParseSerialPacketExample
 *  Written By: Joey Hines (joey.ahines@gmail.com)
 *  
 *  Parses a packet from serial and prints its part to the user
 */

#include <UTDRWirelessComms.h>
#include <SoftwareSerial.h>
//New SoftwareSerial object for UTDRWirelessComms
int rx = 8;
int tx = 7;
SoftwareSerial serial(rx,tx);
//Create new UTDRWirelessComms named input
UTDRWirelessComms input = UTDRWirelessComms(&serial);
 
void setup() {
  //Setup Serial
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  //Wait for serial
  if (serial.available()) {
    //New int array for storing packet data
    int * packet = new int[3];

    //Get the command packet
    input.getCommandPacket(packet);

    //Echo packet to user
    Serial.println("Packet: ");
    for (int i = 0; i < 3; i++) {
      Serial.print(packet[i]);
      Serial.print(' ');
    }
    Serial.println();

    //Clear packet memory
    delete packet;
  }

  delay(20);

}
