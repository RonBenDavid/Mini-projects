/**********/
/*               Lab 3 - Basic debug introduction using IAR               */
/*Group #7                                                                */
/*Ron ben david,                                                          */
/*Yohav itzhak,                                                           */
/*Ben Reuven,                                                             */
/* MSP430 Teaching ROM                                                    */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/*                                        Copyright by Texas Instruments  */
/**********/
#include <msp430xG46x.h>

int count = 0;
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	volatile unsigned int i;
	if (P1IFG & 0x01)
	{
		if (count >= 7)
		{
			count = 0;
			P5OUT &= ~0x02;
			P2OUT &= ~0x04;
			P2OUT &= ~0x02;
			goto jump;
		}
		else
			count++;
		P5OUT ^= 0x02;                 //Toggle Port P2.1

		if ((count % 2) == 0)
			P2OUT ^= 0x04;

		if (count == 4)				   	//Toggle Port P2.1
			P2OUT ^= 0x02;
	jump:
		i = 1500;                        //Delay, button debounce 
		do (i--);
		while (i != 0);

		while (!(P1IN & 0x01));        //Wait for the release of the button

		i = 1500;                        //Delay, button debounce 
		do (i--);
		while (i != 0);

		P1IFG &= ~0x01;                //Clean P1.0 Interrupt Flag
	}

	if (P1IFG & 0x02)
	{
		count = 0;
		P5OUT &= ~0x02;
		P2OUT &= ~0x04;
		P2OUT &= ~0x02;
		i = 1500;                        //Delay, button debounce 
		do (i--);
		while (i != 0);

		while (!(P1IN & 0x01));        //Wait for the release of the button

		i = 1500;                        //Delay, button debounce 
		do (i--);
		while (i != 0);

		P1IFG &= ~0x02;                //Clean P1.0 Interrupt Flag
	}
}

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;      //Stop Watchdog Timer
	P2DIR |= 0x02;                 //Configure P2.1 as Output (LED2)
	P2DIR |= 0x04;                 //Configure P2.2 as Output (LED1)
	P5DIR |= 0x02;                 //Configure P5.1 as Output (LED4)

	P1DIR &= ~0x01;                //Configure P1.0 as Input (S1)
	P1IE |= 0x01;                  //Interrupt Enable in P1.0
	P1IES |= 0x01;                 //P1.0 Interrupt flag high-to-low transition

	P1DIR &= ~0x02;                //Configure P1.1 as Input (S2)
	P1IE |= 0x02;                  //Interrupt Enable in P1.1
	P1IES |= 0x02;                 //P1.1 Interrupt flag high-to-low transition
	P2OUT &= ~0x02;
	P2OUT &= ~0x04;
	P5OUT &= ~0x02;

	_BIS_SR(LPM3_bits + GIE);     //Low Power Mode with interrupts enabled
}
