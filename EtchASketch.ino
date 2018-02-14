// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Include application, user and local libraries
#include "SPI.h"
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

// Define variables and constants
#define joystickX 2
#define joystickY 26
uint16_t x, y, x00, y00;
uint16_t colour;
uint32_t z;

// constants won't change. They're used here to 
// set pin numbers:
const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin

// variables will change:
int buttonOneState = 0;         // variable for reading the pushbutton #1 status
int buttonTwoState = 0;         // variable for reading the pushbutton #2 status



// Add setup code
void setup()
{
    myScreen.begin();
    x00 = 0;
    y00 = 0;

    // MSP432 14-bit set to 12-bit
#if defined(__MSP432P401R__)
    analogReadResolution(12);
#endif

    // initialize the pushbutton pin as an input:
    pinMode(buttonOne, INPUT_PULLUP);     
    pinMode(buttonTwo, INPUT_PULLUP);     
}



// Add loop code
void loop()
{
    // maps the analog scale of the joysick to a digital scale 0-128
    x = map(analogRead(joystickX), 0, 4096, 0, 128);
    y = map(analogRead(joystickY), 0, 4096, 128, 0);
    if (x < 1)      x = 1;
    if (x > 126)    x = 126;
    if (y < 1)      y = 1;
    if (y > 126)    y = 126;

    // read the state of the pushbutton value:
    buttonOneState = digitalRead(buttonOne);

    // read the state of the pushbutton value:
    buttonTwoState = digitalRead(buttonTwo);   
    
    if ((x00 != x) || (y00 != y)) {
        // check if the pushbutton is pressed.
        // if it is, the buttonState is LOW

        // check for Button 1 press
        if (buttonOneState == LOW && buttonTwoState == HIGH)
        {
          // change to red
          colour = redColour;
          // display text prompt
          myScreen.gText(0, myScreen.screenSizeY()-myScreen.fontSizeY(),
                         "RED   ",
                         colour);
          // draw square at x, y location
          myScreen.dRectangle(x-1, y-1, 2, 2, colour);
        }
        
        // check for Button 2 press
        else if (buttonTwoState == LOW && buttonOneState == HIGH)
        {
          // change to blue
          colour = blueColour;
          // display text prompt
          myScreen.gText(0, myScreen.screenSizeY()-myScreen.fontSizeY(),
                         "BLUE  ",
                         colour);
          // draw square at x, y location
          myScreen.dRectangle(x-1, y-1, 2, 2, colour);
        }
        
        // check for Button 1 AND 2 press
        else if (buttonOneState == LOW && buttonTwoState == LOW)
        {
          // change to yellow
          colour = yellowColour;
          // display text prompt
          myScreen.gText(0, myScreen.screenSizeY()-myScreen.fontSizeY(),
                         "YELLOW",
                         colour);
          // draw square at x, y location
          myScreen.dRectangle(x-1, y-1, 2, 2, colour);
        }
        
        // default, eraser cursor
        else
        {
          // show a white cursor
          colour = whiteColour;
          // display text prompt
          myScreen.gText(0, myScreen.screenSizeY()-myScreen.fontSizeY(),
                         "ERASE ",
                         colour);
          // draw square at x, y location
          myScreen.dRectangle(x-1, y-1, 2, 2, colour);
          // cover square up in black to prevent trail
          myScreen.dRectangle(x00-1, y00-1, 2, 2, blackColour);
        }
        
        // trail for eraser cursor
        x00 = x;
        y00 = y;
    }
}
