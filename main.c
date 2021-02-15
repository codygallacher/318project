#include <msp430.h>
#include <driverlib.h>
#include "LEDDriver.h"
#include "hal_LCD.h"

unsigned char SW1_interruptFlag_ = 0;
unsigned char SW2_interruptFlag_ = 0;
unsigned char rates[] = {3, 10, 30}; //rates is the name of the array; global

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
    }
}
  


int main(void)
{
  
  //DEFAULT MCLK = 1MHz//
  
  unsigned char countchar;
  unsigned char dialValue = 0x01; 
  unsigned int count = 0;
  unsigned int maxPeople =5;
  
  WDTCTL = WDTPW | WDTHOLD;             //STOP WATCHDOG TIMER//
  
  initialiseLedDial();
  
  //CONFIGURES BUTTON S1 AND S2 INTERRUPT
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3 | GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3 | GPIO_PIN4);
  GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3 | GPIO_PIN4);
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN3 | GPIO_PIN4);
  
  //DISABLES THE GPIO POWER-ON DEFAULT HIGH IMPEDENCE MODE//
  //TO ACTIVATE PREVIOUSLY CONFIGURED PORT SETTINGS//
  
  
  PMM_unlockLPM5();
  
  __enable_interrupt();
  Init_LCD();
   clearLCD(); showChar('0', pos3); 
  
  while(1)
  {
    if(SW1_interruptFlag_)
    {
      count = count+1; //switch 1 increases occupancy
      countchar = (char)count;
      __delay_cycles(100000); //debouncing delay
      SW1_interruptFlag_ = 0;
      
      
    
    switch(count) //Display occupancy on LCD
    {
      clearLCD(); showChar(countchar, pos3);
    case 0: clearLCD();showChar('0',pos3);break;
    case 1: clearLCD();showChar('1',pos3);break;
    case 2: clearLCD();showChar('2',pos3);break;
    case 3: clearLCD();showChar('3',pos3);break;
    case 4: clearLCD();showChar('4',pos3);break;
    case 5: clearLCD();showChar('5',pos3);break;
    case 6: clearLCD();showChar('6',pos3);break;
    case 7: clearLCD();showChar('7',pos3);break;
    case 8: clearLCD();showChar('8',pos3);break;
    default: clearLCD();
    }
      
    }

    
    if(SW2_interruptFlag_)
    {
      count = count-1;
      countchar = (char)count;
      
      __delay_cycles(100000); //debouncing delay
      SW2_interruptFlag_ = 0;
      
       switch(count) //display occupancy on LED
    {
    case 0: clearLCD();showChar('0',pos3);break;
    case 1: clearLCD();showChar('1',pos3);break;
    case 2: clearLCD();showChar('2',pos3);break;
    case 3: clearLCD();showChar('3',pos3);break;
    case 4: clearLCD();showChar('4',pos3);break;
    case 5: clearLCD();showChar('5',pos3);break;
    case 6: clearLCD();showChar('6',pos3);break;
    case 7: clearLCD();showChar('7',pos3);break;
    case 8: clearLCD();showChar('8',pos3);break;
    default: clearLCD();
    }
    }
    
    
    if(count == maxPeople) //occupancy limit reahced
      {
        //alternate dialValue between 1 and 2 (switch between  upper and lower bank LEDs)
        dialValue = dialValue*0x02; 
        allLEDson();
          if(0x02 == dialValue) // Set the led back at led 1
             dialValue = 0x01;
      }
      else if (count > maxPeople) //occupancy limit exceeded
      {
        flashLEDs();
      }
   
     else //count<maxPeople
      {
          dialValue = dialValue * 0x02; // cycle clockwise
          refreshLedDial();
          
          if(0x00 == dialValue) // Set the led back at led 1
             dialValue = 0x01;
          
      }
    
    
    
    
    
    //SET VALUE//
    setLedDial(dialValue);

  }
}
