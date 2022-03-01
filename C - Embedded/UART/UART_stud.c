/**************************************************************************/
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
/**************************************************************************/

#include <msp430xG46x.h>
 
  
 **************************************************************************/
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
  UCA0CTL0 = ________________________________;
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
  UCA0CTL1 = ________________________________;                    
  //------------------------------------------------------------------------
  // BAUD RATE GENERATION
  // Prescaler = 8MHz/(16 x 9600)
  // UCA0BR1 = _______________
  // UCBRS0 = ________________
  //------------------------------------------------------------------------
  UCA0BR0 = _________________________________; // 9600 from 8MHz -> SMCLK  
  UCA0BR1 = _________________________________;
  //UCAxMCTL Modulation Control Register
  // 7-4  | 3-1  |  0   |
  //UCBRFx|UCBRSx|UCOS16|
  //UCBRFx (First modulation stage)  -> 1 from table 19-5
  //UCBRSx (Second modulation stage) -> 0 from table 19-5
  //UCOS16 (Oversampling mode)       -> Enabled
  UCA0MCTL = _________________________________;
  //------------------------------------------------------------------------
  //2) END 
  
  //3) Configure ports <-BEGIN
  P2SEL |= _________________________________;  //P2.4,P2.5 = USCI_A0 TXD/RXD
  //P2DIR |= 0x10;
 
  //3) END  
  
  //4) Clear UCSWRST via software -> BEGIN                      
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  //4) ->END
  
  //5) Enable interrupts -> BEGIN
  IE2 |= _________________________________;    // Enable USCI_A0 RX interrupt
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


void WriteChar(char ch)
{
 
    while (!(IFG2 & UCA0TXIFG));     // USART1 TX buffer ready?
    UCA0TXBUF  = ch;                 // Output character
  
}
void main(void)
{
  //Initialize system clock
  CLKInit();
  
  //Initialize communication interface
  UARTSetup();
  
  // Allow interrupts
  _BIS_SR(GIE);  
  
  
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
    WriteChar(ch); // write the characer
}
