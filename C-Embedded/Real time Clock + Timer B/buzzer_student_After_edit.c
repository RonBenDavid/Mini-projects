#include <msp430xG46x.h>

#define notas 	10
#define SI0		15895
#define DO  	15258
#define RE 		13620
#define MI 		12077
#define FA 		11405
#define SOL		10159
#define LA 		9106
#define SI 		7963
#define DO2 	7629
#define MUTE 	0
/*Ron ben david, ID:307906263                                             */
/*Yohav itzhak,  ID:305126823                                             */
/*Ben Reuven,    ID:206339962                                             */
//**********************
// Global data
//**********************
unsigned int music[notas] =  {SI0, DO, RE, MI, FA, SOL, LA, SI, DO2, MUTE};
//unsigned int music[notas] =  {RE, MI, DO2, DO, SOL, MUTE, MUTE, MUTE, MUTE, MUTE};
unsigned int index_notas = 0;
char volume = 2;
//**********************
// Port1 Interrupt Service Routine
//**********************
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void)
{	
  if (P1IFG & 0x01) volume = volume - 1;
  if (P1IFG & 0x02) volume = volume + 1;
  
  if (volume == 6) volume = 5;
…
[17:56, 23.11.2021] Ron: #include <msp430xG46x.h>

#define notas 	10
#define SI0		15895
#define DO  	15258
#define RE 		13620
#define MI 		12077
#define FA 		11405
#define SOL		10159
#define LA 		9106
#define SI 		7963
#define DO2 	7629
#define MUTE 	0

//**********************
// Global data
//**********************
unsigned int music[notas] =  {SI0, DO, RE, MI, FA, SOL, LA, SI, DO2, MUTE};
//unsigned int music[notas] =  {RE, MI, DO2, DO, SOL, MUTE, MUTE, MUTE, MUTE, MUTE};
unsigned int index_notas = 0;
char volume = 2;
//**********************
// Port1 Interrupt Service Routine
//**********************
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void)
{	
  if (P1IFG & 0x01) volume = volume - 1;
  if (P1IFG & 0x02) volume = volume + 1;
  
  if (volume == 6) volume = 5;
  if (volume == 0) volume = 1;
  
   TBCCR4 = music[index_notas]/volume;
   
   P1IFG = 0x00;
}
//***********************
// Basic Timer Interrupt Service Routine. Run with 1 sec period
//***********************
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
	// Toogle LED1 and LED2	
	P2OUT^=0x06;                            
     
    // get next note
	TBCCR0 = music[index_notas];	     
    // set duty-cycle
	TBCCR4 = music[index_notas]/volume;     
     
    // manage note point
	index_notas++;			     
    if (index_notas == notas)
		index_notas = 0; 
}
//**********************
// Main routine
//**********************
void main (void)
{  
	//Stop WatchDog
	WDTCTL = WDTPW | WDTHOLD;                 
	
	//FLL+ configuration, ACLK = 32.768 kHz 
	FLL_CTL0 |= DCOPLUS + XCAP18PF;           // DCO+ set
	// fDCOCLK = 3.2-25Mhz
	SCFI0 |= FN_4;                            // x2 DCO freq, 8MHz nominal DCO
	// freq = xtal x D x N+1
	SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 MHz
   
	// TimerB configuration
	TBCCR0 = music[0];			           	  // load first tone from sequency
	TBR = 0;			                      // reset TBR 
	// SMCLK
	// 16-bit, TBR(max) = 0FFFFh
	// Each TBCLx latch loads independently
	// Up mode: the timer counts up to TBCCR0
	// Input divider. These bits select the divider for the input clock.(/1)	
	TBCTL =0x210;           
	// output mode set/reset
	TBCCTL4 = 0x60; 		               
	TBCCR4 = music[0]/2;
  
	// Basic Timer 1 Configuration (1 sec)
	// Basic Timer1 clock divide
	// Basic Timer1 interrupt interval, fCLK2/128 
	BTCTL |=0xBD;
	// Enable BT interrupt	
	IE2 |= 0x80;                              

     
	// SW1 and SW2 configuration (Port1)
	P1SEL = 0x31;                             // P1.0 and P1.2 digital I/O
	P1DIR =0x31;                             // P1.0 and P1.2 inputs
	P1IFG = 0x00;                              // clear P1 flags
	P1IES |= 0x00;           			// high-to-low transition interrupts
	P1IE = 0x00;                              // Enable port interrupts
 

	// LED1 and LED2 configuration (Port2)
	P2DIR |= 0x06;                            // P2.2 and P2.1 as digital output
	P2OUT = 0x06;                             // LED1 on and LED2 off
  
	// Buzzer port configuration (Port3)
	P3SEL |= 0x020;                            // P3.5 as special function
	P3DIR |= 0x020;                       // P3.5 as digital output 
        P3OUT = 0x020;
  
	// Interrupts enabled
	_BIS_SR(LPM3_bits + GIE);
}