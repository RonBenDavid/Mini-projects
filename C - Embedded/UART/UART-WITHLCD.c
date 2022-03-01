/**************************/
/*       Lab10a - Echo test using the USCI module in UART mode            */
 
/* MSP430 Teaching ROM                                                    */
 
/*                                                                        */
/* Exercise: Using the MSP-EXP430FG4618 Development Tool and the          */
/*           MSP430FG4618 device use the USCI module in UART mode         */
/*           connected to a PC’s I/O console. When the connection is      */
/*           established, the characters sequence writed at the console   */
/*           through the keyboard will be visualized on the console.      */
/*                                                                        */
/* Instructions:                                                          */
/*                                                                        */
/* This lab requires to configure the USCI module in UART mode:           */
/*  - Configure USCI control registers                                    */
/*  - Configure baud rate generation                                      */
/*  - Configure ports                                                     */
/*  - Enable Rx interrupts                                                */
/*  - Configure FLL+ at 8 MHz                                             */
/*                                                                        */
/* Write to the console and verify the visualization of the characters    */
/*                                                                        */
/*                                                                        */
/*                                        Copyright by Texas Instruments  */
/**************************/
/*Group #7                                                                */
/*Ron ben david                                          */
/*Yohav itzhak                                            */
/*Ben Reuven2  */
#include <msp430xG46x.h>
#include "LCD_defs.h"
#include "show_on_lcd.h"
void UARTSetup(void)
{
  //1) -> initialization/re-configuration process <-BEGIN
  UCA0CTL1 |= UCSWRST;//Set UCSWRST -- needed for re-configuration process
  //1) END
  
  //2) -> Initialize all USCI registers Set <- BEGIN
  // CONTROL REGISTERS
  //UCA0CTL0 -> Control Register 0
  //  7  |  6  |  5  |  4   |  3  |  2-1  |  0   | 
  //------------------------------------------------------------------------
  //UCPEN|UCPAR|UCMSB|UC7BIT|UCSPB|UCMODEx|UCSYNC|
  //UCPEN (Parity)                   ->  Parity disabled
  //UCPAR (Parity select)            ->  Odd parity "Not importante"
  //UCMSB (MSB first select)         ->  LSB first
  //UC7BIT (Character length)        ->  8-bit data
  //UCSPB (Stop bit select)          ->  One stop bit
  //UCMODEx (USCI mode)              ->  UART Mode
  //UCSYNC (Synchronous mode enable) ->  Asynchronous mode
  UCA0CTL0 = 0;
  //------------------------------------------------------------------------
  //------------------------------------------------------------------------
  //UCA0CTL1 -> Control Register 1
  //   6-7  |   5   |   4   |   3  |   2    |   1   |    0  |
  //---------------------------------------------------------
  //UCSSELx |UCRXEIE|UCBRKIE|UCDORM|UCTXADDR|UCTXBRK|UCSWRST|
  //---------------------------------------------------------
  //UCSSELx (USCI clock source select) ->  SMCLK
  //UCRXEIE (interrupt-enable)         ->  Erroneous characters rejected
  //UCBRKIE (interrupt-enable)         ->  Received break characters set
  //UCDORM (sleep mode)                ->  Not dormant
  //UCTXADDR (Transmit address)        ->  Next frame transmitted is data
  //UCTXBRK (Transmit break)           ->  Next frame transmitted is not a break
  //UCSWRST (Software reset)           ->  normally Set by a PUC
  UCA0CTL1 = 0xD0;                    
  //------------------------------------------------------------------------
  // BAUD RATE GENERATION
  // Prescaler = 8MHz/(16 x 9600)
  // UCA0BR1 = 0x034
  // UCBRS0 = 0x00
  //------------------------------------------------------------------------
  UCA0BR0 = 0x34; // 9600 from 8MHz -> SMCLK  
  UCA0BR1 = 0x00;
  //UCAxMCTL Modulation Control Register
  // 7-4  | 3-1  |  0   |
  //UCBRFx|UCBRSx|UCOS16|
  //UCBRFx (First modulation stage)  -> 1 from table 19-5
  //UCBRSx (Second modulation stage) -> 0 from table 19-5
  //UCOS16 (Oversampling mode)       -> Enabled
  UCA0MCTL = 0x11;
  //------------------------------------------------------------------------
  //2) END 
  
  //3) Configure ports <-BEGIN
  P2SEL |= 0x30;  //P2.4,P2.5 = USCI_A0 TXD/RXD
  //P2DIR |= 0x10;
 
  //3) END  
  
  //4) Clear UCSWRST via software -> BEGIN                      
  UCA0CTL1 &= ~UCSWRST;                     // *Initialize USCI state machine*
  //4) ->END
  
  //5) Enable interrupts -> BEGIN
  IE2 |= UCA0RXIE;;    // Enable USCI_A0 RX interrupt
  //5) -> END
}


void CLKInit(void)
{
  /* disable watchdog timer */
  WDTCTL = WDTPW | WDTHOLD;
  
/* Configure MCU clock.*/
   
  SCFQCTL   = 121;                  /* N=121 */
  SCFI0     = FLLD_2 | FN_4;        /* set D=2, range=1.3-12.1MHz */
  FLL_CTL0  = DCOPLUS | XCAP14PF;   /* enable divider, set osc capacitance = ~8pF */
}  
void LCD_all_off(void)
{
	 LCDM2 = 0x00;
	 LCDM3 = 0x00;
	 LCDM4 = 0x00;
	 LCDM5 = 0x00;
	 LCDM6 = 0x00;
	 LCDM7 = 0x00;
	 LCDM8 = 0x00;
	 LCDM9 = 0x00;
	 LCDM10 = 0x00;
	 LCDM11 = 0x00;
	 LCDM12 = 0x00;
	 LCDM13 = 0x00;
}  

void WriteChar(char ch)
{
 
    while (!(IFG2 & UCA0TXIFG));     // USART1 TX buffer ready?
    UCA0TXBUF  = ch;                 // Output character
  
}
void LCD_hex(int ch)
{
    ch=(int)ch;
	unsigned char ch1,ch2,ch3;
    ch_1bit=ch%10;
    ch_2bit=(ch/10)%10;
    ch_3bit=(ch/100)%10;
	switch (ch_3bit)				// switch to write hex 3rd bit
	{
		case 1:P3_A1;
		       break;
		case 2:P3_A2;
			   break;
		case 3:P3_A3;
			   break;
		case 4:P3_A4;
			   break;
		case 5:P3_A5;
		       break;
		case 6:P3_A6;
		       break;
		case 7:P3_A7;
		       break;
		case 8:P3_A8;
		       break;
		case 9:P3_A9;
		       break;
		case 0:P3_A0;
		       break;
	}
	switch (ch_2bit)				       // switch to write hex 2nd bit
	{
		case 1: P2_A1;
		        break;
		case 2: P2_A2;
		        break;
		case 3: P2_A3;
		        break;
		case 4: P2_A4;
		        break;
		case 5: P2_A5;
		        break;
		case 6: P2_A6;
		        break;
		case 7: P2_A7;
		        break;
		case 8: P2_A8;
		        break;
		case 9: P2_A9;
		        break;
		case 0: P2_A0;
	}	
        switch (ch_1bit)				       // switch to write hex 1st bit
	{
		case 1: P1_A1;
		        break;
		case 2: P1_A2;
		        break;
		case 3: P1_A3;
		        break;
		case 4: P1_A4;
		        break;
		case 5: P1_A5;
		        break;
		case 6: P1_A6;
		        break;
		case 7: P1_A7;
		        break;
		case 8: P1_A8;
		        break;
		case 9: P1_A9;
		        break;
		case 0: P1_A0;
	}	
}
void main(void)
{
  //Initialize system clock
  CLKInit();
  
  //Initialize communication interface
  UARTSetup();
  
  // Allow interrupts
  _BIS_SR(GIE);  
  
  FLL_CTL0 |= XCAP18PF;         // Set load cap for 32k xtal
  
  // LCD COM0-COM1-COM2-COM3 configuration
  P5DIR |= 0x1E;                           // Ports P5.2, P5.3 and P5.4 as outputs
  P5SEL |= 0x1E;                           // Ports P5.2, P5.3 and P5.4 as special function (COM1, COM2 and COM3)
  
  // LCD_A S0-S21 configuration
   LCDAPCTL0 = LCDS24 | LCDS20 | LCDS16 | LCDS12 | LCDS8 | LCDS4; 
  
  // LCDA configuration
  LCDACTL = LCDFREQ_192 | LCD4MUX | LCDSON | LCDON;   // (ACLK = 32768)/192, 4-mux LCD, LCD_A on, Segments on
  LCDAVCTL0 = LCDCPEN;                                // Charge pump enable
  LCDAVCTL1 = VLCD_3_44;                              // VLCD = 3,44 V 
  
  // Clean LCD
  LCD_all_off(); 
  
  while(1){}// No Return from here
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI_UART_0_RX_RSI(void)
{
  char ch;
  ch = UCA0RXBUF;
  if (ch == 13) //if equal to carriage return (CR)
  {
    WriteChar('\n'); //new line
    WriteChar('\r'); //position at begin
  }else
  {
    WriteChar(ch); // write the characer
    LCD_hex(ch); // write the hex number on LCD
  }
}