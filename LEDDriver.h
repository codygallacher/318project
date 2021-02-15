//LEDDriver.h

#include<msp430.h>
#include<driverlib.h>

extern void flashLEDs();
extern void initialiseLedDriver();              //Initialise LED Dial, setting GPIO Parameters//
extern void setLedDial(unsigned char value);    //Set Dial value
extern void refreshLedDial();                   //Refresh the display