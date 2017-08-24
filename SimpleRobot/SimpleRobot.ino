//Motor Pins
int leftMotorPin = 3;
int leftMotorEn1 = 4;
int leftMotorEn2 = 5;

int rightMotorPin = 3;
int rightMotorEn1 = 4;
int rightMotorEn2 = 5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

  //Pin Setup
  //Left Motor Enable Pins
  pinMode(leftMotorEn1,OUTPUT);
  pinMode(leftMotorEn2,OUTPUT);

  //Right Motor Enable Pins
  pinMode(rightMotorEn1,OUTPUT);
  pinMode(rightMotorEn2,OUTPUT);
  

  
}

void loop() {
  //If data is received
  if (Serial.available() > 0) {
    //Get incoming data's type, id and data
    int type = getSerialData();
    int id = getSerialData();
    int data = getSerialData();

    //If the type is a keboard input
    if (type == 'K') {
      //Switch statement for the key
      //Each key its own case, to add more use the following template:
      /*
        case 'CHARACTER':
          //code
        break;    
       */
      switch(id) {
        //Drive forward
        case 'w':
          if (data == '1') {
            writeToRightMotor(100);
            writeToLeftMotor(100);
          }
          else {
            writeToRightMotor(0);
            writeToLeftMotor(0);
          }   
         break;
         //Drive backwards
         case 's':
          if (data == '1') {
            writeToRightMotor(-100);
            writeToLeftMotor(-100);
          }
          else {
            writeToRightMotor(0);
            writeToLeftMotor(0);
          }   
         break;
         //Rotate Counterclockwise
         case 'a':
          if (data == '1') {
            writeToRightMotor(100);
            writeToLeftMotor(-100);
          }
          else {
            writeToRightMotor(0);
            writeToLeftMotor(0);
          }   
         break;
         //Rotate Clockwise
         case 'd':
          if (data == '1') {
            writeToRightMotor(-100);
            writeToLeftMotor(100);
          }
          else {
            writeToRightMotor(0);
            writeToLeftMotor(0);
          }   
         break;
         
      }
      
    }

    //J stands for joystick and its id is the axis number of a joystick
    else if (type == 'J') {
      //Second is the id of input
      int id = getSerialData();
      //Since the joystick is an analog value, it has an extra bit of data for the value
      int data = getSerialData();
      Serial.println("Joystick " + String(id) + ": " + String(data));
    }
    //B stands for joystick button and its id is the number of the button
    else if (type == 'B') {
      //Second is the id of input
      int id = getSerialData();
      Serial.println("Button: " + String(id));
    }
    
  }
    

}

/* int getSerialData()
 *  Gets a packet from serial and returns its
 *  intger value
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

/*  int convertPercentToMotorValue(int value
 *  Takes a percent value of -100 to 100 and converts to a PWM value of
 *  0 to 255
 */
int convertPercentToMotorValue(int value) {
  return value * 2.55;
}

/*  void writeToRightMotor(int value)
 *  Writes a percent speed to the right motor
 */
void writeToRightMotor(int value) {
  //Converts a percent
  int pwmValue = convertPercentToMotorValue(value);

  //If the PPWM value is positive, set the enable pins to forward
  if (pwmValue > 0) {
    digitalWrite(rightMotorEn1, HIGH);
    digitalWrite(rightMotorEn2, LOW);
  }
  //If the PPWM value is negative, set the enable pins to backwards
  else if (pwmValue < 0) {
    digitalWrite(rightMotorEn1, LOW);
    digitalWrite(rightMotorEn2, HIGH);
  }

  //Write the absolute value PWM to the motor
  analogWrite(rightMotorPin, abs(pwmValue));
}

/*  void writeToLeftMotor(int value)
 *  Writes a percent speed to the left motor
 */
void writeToLeftMotor(int value) {
  //Converts a percent
  int pwmValue = convertPercentToMotorValue(value);

  //If the PPWM value is positive, set the enable pins to forward
  if (pwmValue > 0) {
    digitalWrite(leftMotorEn1, HIGH);
    digitalWrite(leftMotorEn2, LOW);
  }
  //If the PPWM value is negative, set the enable pins to backwards
  else if (pwmValue < 0) {
    digitalWrite(leftMotorEn1, LOW);
    digitalWrite(leftMotorEn2, HIGH);
  }

  //Write the absolute value PWM to the motor
  analogWrite(leftMotorPin, abs(pwmValue));
}





