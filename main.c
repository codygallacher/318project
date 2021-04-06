/* *******************

MAIN FOR WARNING SYSTEM

***********************/

#include <msp430.h>
#include <driverlib.h>
#include "LEDDriver.h"
#include "hal_LCD.h" 

unsigned char SW1_interruptFlag_ = 0;
unsigned char SW2_interruptFlag_ = 0;
unsigned char SW3_interruptFlag_ = 0;
unsigned char SW4_interruptFlag_ = 0;
unsigned int count = 0; //global variable for LCDnumber function
unsigned int maxPeople =0;

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
  
{  
    switch(__even_in_range(P1IV,P1IV_P1IFG7)) 
    {

  
  case P1IV_P1IFG3: //switch 1 sent the interrupt signal
    SW1_interruptFlag_ = 1;
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
    break;
    
  case P1IV_P1IFG4:  //switch 2 sent the interrupt signal
    SW2_interruptFlag_ = 1;
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    break;
    
  case P1IV_P1IFG2://black left SWITCH 1 SENT THE INTERRUPT SIGNAL//
     SW3_interruptFlag_ = 1;
     GPIO_clearInterrupt(GPIO_PORT_P1,GPIO_PIN2); //PIN ALLOCATION
     break;    
    
   case P2IV_P2IFG6://black right SWITCH 2 SENT THE INTERRUPT SIGNAL//
     SW4_interruptFlag_ = 1;
     GPIO_clearInterrupt(GPIO_PORT_P2,GPIO_PIN6); //PIN ALLOCATION
     break;    
    }
}
  
#pragma vector = PORT2_VECTOR
 __interrupt void P2ISR(void)
 {
   switch(__even_in_range(P2IV,P2IV_P2IFG7))
   {
    case P2IV_P2IFG6: // right black switch
     SW4_interruptFlag_ = 1;
     GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN6); //PIN ALLOCATION
     break;  
    }
   
 }

int main(void)
{ 
  //DEFAULT MCLK = 1MHz//
  
  unsigned char countchar;
  unsigned char dialValue = 0x01; 
  
  WDTCTL = WDTPW | WDTHOLD;             //STOP WATCHDOG TIMER//
  
  initialiseLedDial();
  
  //CONFIGURES BUTTON INTERRUTS FOR PORT 1
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  
   //CONFIGURES BUTTON INTERRUTS FOR PORT 2
  GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN6,GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
  GPIO_clearInterrupt(GPIO_PORT_P2,GPIO_PIN6);
  GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN6);
  
  //DISABLES THE GPIO POWER-ON DEFAULT HIGH IMPEDENCE MODE//
  //TO ACTIVATE PREVIOUSLY CONFIGURED PORT SETTINGS//
  
  
  PMM_unlockLPM5();
  
  __enable_interrupt();
  Init_LCD();
   clearLCD(); showChar('0', pos3); 
   
   unsigned int i=0; //used in the for loop inside the sw3 while loop
  while(1)
  {
    while(!SW3_interruptFlag_) //section where user sets occupancy limit
    { 
      if (i<1) //if statement so this text is only putput once
      {
      outputText("SET OCCUPANCY LIMIT");
      i++;
      }
    
     if(SW1_interruptFlag_) //switch 1 increases maximum occupancy
        { maxPeople++;
        if(maxPeople>20) //error handling
        {outputText("MAXIMUM LIMIT EXCEEDED");}
        LCDlimit(maxPeople); //display current value of occupancy limit
        __delay_cycles(300000); //debouncing delay
        SW1_interruptFlag_ = 0;}
   
        if(SW2_interruptFlag_)  //switch 2 decreases maximum occupancy
        {maxPeople--;
          if(maxPeople>20) //error handling
          {outputText("MAXIMUM LIMIT EXCEEDED");}
        LCDlimit(maxPeople);
        __delay_cycles(300000); //debouncing delay 0.3 seconds
        SW2_interruptFlag_ = 0;}
      
   }   
    //SW3_interruptFlag_ = 0; //reset switch 1 to zero so it can be reused to simulate a sensor input
  
   LCDnumbers(count); //stop displaying limit and change to current occupancy
    if(SW1_interruptFlag_)
    {
      count = count+1; //switch 1 increases occupancy
      countchar = (char)count;
      __delay_cycles(300000); //debouncing delay
      SW1_interruptFlag_ = 0;
      
      LCDnumbers(count); //function for displaying value of count on LCD 
    }

    if(SW2_interruptFlag_)//switch 2 simulates someone leaving the building
    {
      count = count-1;
      countchar = (char)count;
      if(maxPeople>20) //error handling
      __delay_cycles(300000); //debouncing delay
      SW2_interruptFlag_ = 0;
      LCDnumbers(count);
    }
    
    if(SW4_interruptFlag_) //switch 4 can be used to remind the user of the occupancy limit
    {__delay_cycles(300000); //0.3s  delay
   LCDlimit(maxPeople);
   __delay_cycles(5000000); //5 second delay
    SW4_interruptFlag_ = 0;}
    
    if(count == maxPeople) //occupancy limit reahced
      {
         flashLEDs();
      }
      else if (count > maxPeople) //occupancy limit exceeded
      {
        
       outputText("MAXIMUM OCCUPANCY LIMIT EXCEEDED"); 
      }
   
     else //count<maxPeople
      {
        allLEDson();
         /* dialValue = dialValue * 0x02; // cycle clockwise
          refreshLedDial();
          
          if(0x00 == dialValue) // Set the led back at led 1
             dialValue = 0x01;*/
          
      }
    //SET VALUE//
    setLedDial(dialValue);
  }
}
