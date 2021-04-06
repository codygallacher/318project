/* *******************

LEDDriver.c FOR WARNING SYSTEM

***********************/

#include "LEDDriver.h"

unsigned char ledValue_=0;                 //REPRESENTS CURRENT DIAL VALUE//

void initialiseLedDial()                   //INITIALISE LED DIAL//
                                           //SETTING GPIO PARAMETERS//
{
  //GPIO 2.7//
  GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN7);
  
  //GPIO 5.1, 5.2, 5.3//
  GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
  
  //GPIO 8.0//
   GPIO_setAsOutputPin(GPIO_PORT_P8,GPIO_PIN0);
}

void refreshLedDial() //LEDs move round in a ring
{
  //Refresh lower bank (LEDs 1-4)
 GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);//Low output on bottom rail to light up lower bank LEDs
 
 
 if(ledValue_ &0x01) //hexidecimal for LED: 01 hex= bit 1 (0001). If lower bit is 0...
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);//pin 8.0 connects to LEDs 1 and 5. ...Turns LED on
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
 
 if(ledValue_ &0x02) //02 hex= bit 2 (0010)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1); //port 5.1 connects to LEDs 2 and 6
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 if(ledValue_ &0x04) //04 hex = bit 3 (0100)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2); //port 5.2 connects to LEDs 3 and 7
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
  if(ledValue_ &0x08) //08 hex = bit 4 (1000)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3); // port 5.3 connects to LEDs 4 and 8
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
 

  __delay_cycles(200000);  
  
  
  
  //Refresh upper bank (LEDs 5-9)
  GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
  
   if(ledValue_ &0x10) //10 hex = bit 5(0001 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3); //port 5.3 connects to LED 8
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
 
 
 if(ledValue_ &0x20) //20 hex = bit 6 (0010 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2); // port 5.2 connects to LED 7
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
 
 if(ledValue_ &0x40) //40 hex = bit 7 (0100 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//pin 5.1 connects to LED 6
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 
 if(ledValue_ &0x80) //hex 80 = bit 8(1000 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);//port 8.0 connects to LED 5
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
    
  __delay_cycles(200000);  //Delay 10ms
}


void allLEDson() //Lower bank on-> very small delay ->upper bank on
{
  //Refresh lower bank (LEDs 1-4)
 GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);//Low output on bottom rail to light up lower bank LEDs
 
 
 if(ledValue_ &0x01) //hexidecimal for LED: 01 hex= bit 1 (0001). If lower bit is 0...
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);//pin 8.0 connects to LEDs 1 and 5. ...Turns LED on
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
 
 if(ledValue_ &0x01) //02 hex= bit 2 (0010)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1); //port 5.1 connects to LEDs 2 and 6
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 if(ledValue_ &0x01) //04 hex = bit 3 (0100)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2); //port 5.2 connects to LEDs 3 and 7
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
  if(ledValue_ &0x01) //08 hex = bit 4 (1000)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3); // port 5.3 connects to LEDs 4 and 8
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
 

  __delay_cycles(100);  //Delay 
  
  ledValue_ =0x20;
  
  //Refresh upper bank (LEDs 5-9)
  GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
  
   if(ledValue_ &0x20) //10 hex = bit 5(0001 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3); //port 5.3 connects to LED 8
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
 
 
 if(ledValue_ &0x20) //20 hex = bit 6 (0010 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2); // port 5.2 connects to LED 7
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
 
 if(ledValue_ &0x20) //40 hex = bit 7 (0100 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//pin 5.1 connects to LED 6
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 
 if(ledValue_ &0x20) //hex 80 = bit 8(1000 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);//port 8.0 connects to LED 5
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
    
  __delay_cycles(100); //Very short delay so it looks like all LEDs are on at once
}
 
   
 void flashLEDs() //Refresh the display
{
  //Turn on lower bank (LEDs 1-4)
 GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);//Low output on bottom rail to light up lower bank LEDs
 
 
 if(ledValue_ &0x01) //hexidecimal for LED: 01 hex= bit 1 (0001). If lower bit is 0...
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);//pin 8.0 connects to LEDs 1 and 5. ...Turns LED on
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
 
 if(ledValue_ &0x01) //02 hex= bit 2 (0010)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1); //port 5.1 connects to LEDs 2 and 6
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 if(ledValue_ &0x01) //04 hex = bit 3 (0100)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2); //port 5.2 connects to LEDs 3 and 7
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
  if(ledValue_ &0x01) //08 hex = bit 4 (1000)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3); // port 5.3 connects to LEDs 4 and 8
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
 

  __delay_cycles(100000);  //Delay 
  
  ledValue_=0x20;
  
  //Turn on upper bank (LEDs 5-9)
  GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
  
   if(ledValue_ &0x20) //10 hex = bit 5(0001 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3); //port 5.3 connects to LED 8
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
 
 
 if(ledValue_ &0x20) //20 hex = bit 6 (0010 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2); // port 5.2 connects to LED 7
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
 
 if(ledValue_ &0x20) //40 hex = bit 7 (0100 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//pin 5.1 connects to LED 6
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 
 if(ledValue_ &0x20) //hex 80 = bit 8(1000 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);//port 8.0 connects to LED 5
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
    
  __delay_cycles(100000);  
 
 
  //Turn off lower bank (LEDs 1-4)
 /*GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);//High output on bottom rail to turn off lower bank LEDs
 
 
 if(ledValue_ &0x01) //hexidecimal for LED: 01 hex= bit 1 (0001). If lower bit is 0...
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);//pin 8.0 connects to LEDs 1 and 5. ...Turns LED on
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
 
 if(ledValue_ &0x01) //02 hex= bit 2 (0010)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1); //port 5.1 connects to LEDs 2 and 6
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 if(ledValue_ &0x01) //04 hex = bit 3 (0100)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2); //port 5.2 connects to LEDs 3 and 7
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
  if(ledValue_ &0x01) //08 hex = bit 4 (1000)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3); // port 5.3 connects to LEDs 4 and 8
 
 else
   GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
 

  __delay_cycles(100000);  //Delay 
  
  
  
  //Turn off upper bank (LEDs 5-8)
  GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
  
  if(ledValue_ &0x20) //10 hex = bit 5(0001 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3); //port 5.3 connects to LED 8
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
 
 
 if(ledValue_ &0x20) //20 hex = bit 6 (0010 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2); // port 5.2 connects to LED 7
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
 
 
 if(ledValue_ &0x20) //40 hex = bit 7 (0100 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);//pin 5.1 connects to LED 6
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
 
 
 if(ledValue_ &0x20) //hex 80 = bit 8(1000 0000)
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);//port 8.0 connects to LED 5
 
 else
   GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
 
 __delay_cycles(100000);*/
 
}

void setLedDial(unsigned char value)    //SET DIAL VALUE//
{
  ledValue_= value;
}







