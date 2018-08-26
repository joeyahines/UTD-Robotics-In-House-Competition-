"""
UTD Robotics In House Competition Robot Controller
Written By: Joey Hines (joey.ahines@gmail.com)
Based off of GRCS v4 Controller

This program sends data from the joystick/keyboard to the robot

Data is sent in the following format:
	"Data Type"\n"Data ID"\n"Value"

"""

import pygame
import socket
import time
import sys
import pickle

# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Default robot ip
robot = ("192.168.4.1", 80);

# Define list for storing the deviceArray
deviceArray = []


# Class for writing text to the screen
class TextPrint:
    def __init__(self):
        self.reset()
        self.font = pygame.font.Font(None, 20)

    def printToScreen(self, screen, textString):
        textBitmap = self.font.render(textString, True, BLACK)
        screen.blit(textBitmap, [self.x, self.y])
        self.y += self.line_height

    def reset(self):
        self.x = 10
        self.y = 10
        self.line_height = 15

    def indent(self):
        self.x += 10

    def unindent(self):
        self.x -= 10


class ControlLists:
    def __init__(self, keyboardButtons, joystickButtons, joystickAxises):
        self.keyBoardButtons = keyboardButtons
        self.joystickButtons = joystickButtons
        self.joystickAxises = joystickAxises

    # Return a string repersentation of the control
    def toString(self):
        return 'K' + str(keyBoardButtons) + 'B' + str(joystickButtons) + 'A' + str(joystickAxises)


def sendDataToRobot(soc, type, id, data):
    packet = '~' + str(type) + str(id) + str(data);
    s.sendto(packet.encode(), robot)


# Open up a UDP socket, used for communicating to the robot
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Begin pygame
pygame.init()

# Initiallize Joystick
joystickDetected = True
# Try/catch to check if joystick is plugged in
try:
    # Assign joystick 0 to joystick
    joystick = pygame.joystick.Joystick(0)
    # Init joystick
    joystick.init()
# Catch pygame.error when joystick is not plugged in
except pygame.error:
    # Tell the user there was no joystick detected
    print("No joystick, detected")
    joystickDetected = False

# Startup Menu

menuDone = False  # Flag to see if the menu is no longer needed
userChoice = ''  # Var for storing user input

while (menuDone == False):
    # Print menu to let the user choose to create a new robot or load one in
    print("UT Dallas Robotics Controller")
    print("a) Setup new robot")
    print("b) Load existing robot")

    # If the joystick was not found during startup
    if joystickDetected == False:
        print("c) Retry Joystick Setup")

    # Get the user's input
    userChoice = input('Choice: ').lower()

    # If the user wants to try the joystick again
    if userChoice == 'c':
        # Try/catch to check if joystick is plugged in
        try:
            # Assign joystick 0 to joystick
            joystick = pygame.joystick.Joystick(0)
            # Init joystick
            joystick.init()
            joystickDetected = True
        except pygame.error:
            # Tell the user there was no joystick detected
            print("No joystick, detected\n")
            joystickDetected = False
        # Go to next loop iteration
        continue

    # If the choice was valid
    if userChoice == 'a' or userChoice == 'b':
        menuDone = True
    # If input was invalid
    else:
        print('Invalid input\n')

# Lists for setting up which button to use
joystickAxises = []
joystickButtons = []
keyBoardButtons = []

# If the user wants to create a new robot
if (userChoice == 'a'):
    # Ask the user for all the keys they want to track
    keyBoardButtons = input('Input each key you wish to use sperated by a space and press enter: ').split()

    # If the joystick is in use
    if joystickDetected:
        # Get all the button and axises to track
        joystickButtons = input('Input the button numbers seperated by a space').split()
        joystickButtons = list(map(int, joystickButtons))
        joystickAxises = input('Input the axis numbers seperated by a space').split()
        joystickAxises = list(map(int, joystickAxises))

    # Put all of the lists into a single input list object
    inputList = ControlLists(keyBoardButtons, joystickButtons, joystickAxises)

    # Save inpustList to a file
    with open('robot.dat', 'wb') as output:
        pickle.dump(inputList, output, pickle.HIGHEST_PROTOCOL)

    # Tell the user te robot was saved
    print("Robot saved to robot.dat")

# If the user wants to load the exisiting robot.dat
else:
    # Open the binary file and store it in inputList
    with open('robot.dat', 'rb') as input:
        inputList = pickle.load(input)

# Set the width and height of the screen [width,height]
size = [500, 500]
screen = pygame.display.set_mode(size)

# Sets the Window Name
pygame.display.set_caption("RUTD Robot Controller")

# Loop until the user clicks the close button.
done = False

# Used to manage how fast the screen updates
clock = pygame.time.Clock()

# Get ready to print
textPrint = TextPrint()

# -------- Main Program Loop -----------
while done == False:
    # EVENT PROCESSING STEP	
    # Gets all input data from PyGame
    for event in pygame.event.get():
        # If user clicked close
        if event.type == pygame.QUIT:  # If user clicked close
            # Flag that we are done so we exit this loop
            done = True

    # Get current keys pressed
    press = pygame.key.get_pressed()

    # DRAWING STEP
    # First, clear the screen to white. Don't put other drawing commands
    # above this, or they will be erased with this command.
    screen.fill(WHITE)
    textPrint.reset()

    # Print robot IP to the screen
    textPrint.printToScreen(screen, "Robot IP and Port {}".format(robot))

    # JOYSTICK STEP
    # If a joystick is plugged in
    if joystickDetected == True:
        textPrint.printToScreen(screen, 'Joystick')

        # Check all axises value the user wants
        for i in inputList.joystickAxises:
            # Get value of the axis
            val = int(round(joystick.get_axis(i), 2) * 100)
            # If the value is in the deadband
            if (val < 10 or val > -10):
                # Make it 0
                val = 0

            # Send data to the robot
            sendDataToRobot(s, 'J', i, val)
            # Print data to screen
            input = str(i) + ': ' + str(val)
            textPrint.printToScreen(screen, input)

        # Check the state of all the buttons the user wants
        for i in inputList.joystickButtons:
            # Get if the button is pressed or not
            val = joystick.get_button(i)

            # Send data to robot

            # Send 1 if the button is pressed
            if joystick.get_button(i):
                pressed = 1
            # Otherwise send 0
            else:
                pressed = 0

            sendDataToRobot(s, 'B', val, pressed)

            # Print data to screen
            input = 'B' + str(i) + ': ' + val
            textPrint.printToScreen(screen, input)

    textPrint.printToScreen(screen, 'Keyboard:')

    # Check all the button the user wants
    for i in inputList.keyBoardButtons:
        # Convert the character to is ascii value
        asciiVal = ord(i)

        # Get name the name of the key from the keyboard
        name = pygame.key.name(asciiVal)

        # Send data to robot
        # s.sendto('!'.encode(),robot)
        # s.sendto('K'.encode(),robot)
        # s.sendto((name).encode(),robot)
        # s.sendto((str(press[asciiVal])).encode(),robot)
        sendDataToRobot(s, 'K', name, press[asciiVal])
        # Print data to screen
        input = name + ': ' + str(press[asciiVal])
        textPrint.printToScreen(screen, input)
    # Update the window
    pygame.display.flip()

    # Limit to 20 frames per second
    # 50 FPS usually works best, any faster the Arduino may not be able to keep
    # up
    clock.tick(20)

# Close udp socket
s.close()

# Close window and quit
pygame.display.quit()
pygame.quit()
sys.exit()
