/*
UT Dallas Robotics Wireless Communication Library v1
Written by Joey Hines (joey.ahines@gmail.com)

This library allows for parsing packets from serial in the style of 
"~{type}{id}{data}\LF". It is to be used with a ESP8266 and the UTD
Robotics wireless controller.
  
*/

#include "UTDRWirelessComms.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

/*
char * UTDRWirelessComms::readSerialUntilPacket(char * buffer) {
	bool packetFound = false:
	
	int j;
	while(!packetFound && j < MaxInSize) {
		char next = serial->read();
		
		if (next == 10) {
			packetFound = true;
		}
		else if (next == '~') {
			j = 0;
		}
		else {
			buffer[j] = byte;
		}
		
		
	}
}
*/


/* void UTDRWirelessComms::getCommandPacket(int packet[])
 * Parses a packet from serial in the style of ~{type}{id}{data}\LF 
 * This functions then returns the int value of the three parts
 */
void UTDRWirelessComms::getCommandPacket(int packet[]) {
	//Char buffer for storing input
	char in[MaxInSize];
	//Flag for tracking if the packet is done being parsed
	boolean packetParsed = false;
	
	//Get the line from Serial and count how many bytes it had
	int sizeOfInput = serial->readBytesUntil(10,in,MaxInSize);
	
	//ndx of the input buffer
	int in_ndx = 0;
	//ndx of output packet
	int packet_ndx = 0;
	
	//If data was received 
	if(sizeOfInput) {
		//For each element in the buffer until the packet is parsed
		for (in_ndx = 0; in_ndx < sizeOfInput && !packetParsed; in_ndx++) {
			
			//Check for the new packet symbol
			if(in[in_ndx] == '~') {
				//If the symbol is in the middle of the buffer, start reading
				//new packet
				if (in_ndx > 0) {
					packet_ndx  = 0;
				}
			}
			//For any other input
			else {
				//Switch based off of packet_ndx
				switch(packet_ndx) {
				//For the type byte
				case 0:   
					//Put that byte at index 0 of the parsed packet
					packet[packet_ndx] = in[in_ndx];
					break; 
				//For the id byte
				case 1: 
					//Put that byte at index 1 of the parsed packet
					packet[packet_ndx] = in[in_ndx];
					break;
				//For the data bytes
				default: 
					//Count j is equal to in_ndx
					int j = in_ndx;
					//String for storing data bytes as the come in
					String data;
					
					//TODO Test if this is needed
					bool isNegative = false;
					if (in[j] == '-') {
						data += in[j];
						j++;
					}
					
					//Add the data bytes from the buffer to data until their is 
					//no more numerical data 
					while(in[j] != 0 && isdigit(in[j])) {   
						data += in[j];
						j++;        
					}
					
					//Covert data from string to int and place it in index 3 of
					//the output packet
					packet[packet_ndx] = data.toInt();
					
					//packet has now been parsed
					packetParsed = true;  

					} 
				//Move on to next packet part
				packet_ndx++;
			}

		}
		
		//If the packet did not parse correctly, return a 0 packet
		if (in_ndx >= sizeOfInput && !packetParsed) {
			for (int i = 0; i < packetSize; i++) {
				packet[i] = 0;
			}
		}
	}
}
UTDRWirelessComms::UTDRWirelessComms(SoftwareSerial * s) {
	serial = s;
	serial->begin(9600);
}

UTDRWirelessComms::UTDRWirelessComms(SoftwareSerial * s, int maxSize, int pSize) {
	MaxInSize = maxSize;
	packetSize = pSize;
	serial = s;
	serial->begin(9600);
}