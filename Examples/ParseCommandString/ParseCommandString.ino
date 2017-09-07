
/*  All Data from the UTDR Controller Program comes in three parts:
 *   
 *    -Type of input: keyboard keys (K), joystick buttons (B) and joysticks (J)
 *    -ID of input: The button or axis number on joysticks or the ASCII 
 *        value of a key on a keyboard
 *    -Input data: The value of the data
 *      * 1 or 0 for buttons/keys
 *      * -100 to 100 for joystick axises
 *  
 *  There are three types of inputs:
 *    -
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  //If data is received
  if (Serial.available() > 0) {
    //The first part of the data is the type    
    int type = getSerialData();
    //The second part is the id of the input
    int id = getSerialData();
    //The last part is the input data
    int data = getSerialData();

    //If the input type was a key or K type
    if (type == 'K') {    
      //Print out the key and its state
      Serial.println("Key " + String(id) + ": " + String(data));
    }

    //If the input was a joystick or J type
    else if (type == 'J') {
      //Print out the value of the axis of the joystick
      Serial.println("Joystick " + String(id) + ": " + String(data));
    }
    //If the input was a joystick button or B type
    else if (type == 'B') {
      //Print out the button number and its state
      Serial.println("Button " + String(id) + ": " + String(data));
    }
    
  }
  
}

/* int getSerialData()
 *  Gets data from serial and returns its integer value
 */
int getSerialData() {
  //String for storing input
  String inString;

  //Run until full packet is received 
  while (1) {
    //Wait for serial connection
    while (!Serial.available());
    //Read in the next char
    int inChar = Serial.read();

    //Check it the end of packet is received
    //This is repersented by the new line character
    if (inChar == 10) {
      //Ignore ASCII 10
      continue;
    }
    if (inChar == 13) {
      //Packet is done, break
      break;
    }

    //Add char to string
    if (!isDigit(inChar)) {
      inString += inChar;
    }
    inString += (char)inChar;
  }

  //Return char
  return inString.toInt();
}




