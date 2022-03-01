/**************************************************************************/
/*                   Lab  - Data acquisition using ADC12                 */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* MSP430 Teaching ROM                                                    */
/*                                                                        */
/* Exercise: Using the MSP-EXP430FG4618 Development Tool and the          */
/*           MSP430FG4618 device explore the ADC12 and OA modules. The    */
/*           test voltage is generated in the DAC12 module (channel 0)    */
/*           modifying the DAC12_ODAT register's value. The analogue      */
/*           voltage is amplified by the OA module. Afterwards this       */
/*           signal is applied to ADC12 input to be converted. Compare    */
/*           the DAC12_ODAT and the ADC12MEM0 values.                     */
/*                                                                        */
/* Instructions:                                                          */
/* The ADC12 sample-and-hold time is configured to be 64 ADC12CLK cycles. */
/* It uses the internal reference generator voltage, Vref+ = 2,5 V,       */
/* performing a single-channel, single-conversion at channel 1,           */  
/* using as clock source the ADC12OSC/1.                                  */
//                                                                        */
// The OA module is configured as Non-inverting PGA with unity gain.      */
// The Non-inverting input is the DAC0 internal while the output is       */
// connected to internal/external A1.                                     */
//                                                                        */
//  Complete the code below:                                              */
//   - Configure ADC12 control and control memory registers               */
//   - Configure OA control registers                                     */
//                                                                        */
//                                                                        */
//                                        Copyright by Texas Instruments  */
//*************************************************************************/
 
#include  "msp430xG46x.h"
#include  "LCD_defs.h"

void lcd_all_off()
{
	LCDM3 = 0;
	LCDM4 = 0;
	LCDM5 = 0;
	LCDM6 = 0;
	LCDM7 = 0;
	LCDM8 = 0;
	LCDM9 = 0;
	LCDM10 = 0;
	LCDM11 = 0;
	LCDM12 = 0;
	LCDM13 = 0;
}

void show_on_lcd(int temp)
{
	unsigned char digit1 = 0;
	unsigned char digit2 = 0;

	digit1 = temp / 10;
	digit2 = temp % 10;

	switch (digit1)				// switch to write digit
	{
	case 1: P5_A1;
		break;
	case 2: P5_A2;
		break;
	case 3: P5_A3;
		break;
	case 4: P5_A4;
		break;
	case 5: P5_A5;
		break;
	case 6: P5_A6;
		break;
	case 7: P5_A7;
		break;
	case 8: P5_A8;
		break;
	case 9: P5_A9;
		break;
	case 0: P5_A0;
		break;
	}
	switch (digit2)				// switch to write  digit
	{
	case 1: P4_A1;
		break;
	case 2: P4_A2;
		break;
	case 3: P4_A3;
		break;
	case 4: P4_A4;
		break;
	case 5: P4_A5;
		break;
	case 6: P4_A6;
		break;
	case 7: P4_A7;
		break;
	case 8: P4_A8;
		break;
	case 9: P4_A9;
		break;
	case 0: P4_A0;
		break;
	}
	LCDM5 = 0x33;
	LCDM4 = 0x59;
}
 
void DAC12Init(void)
{
  // DAC12 configuration
  DAC12_0DAT = _______;                         // DAC_0 output 0V

  ADC12CTL0 = _______________;                  // Internal 2.5V ref on
  
  DAC12_0CTL = _______________________________; // DAC_0 -> P6.6
  				                                // DAC_1 -> P6.7
                                                // DAC reference Vref
                                                // 12 bits resolution
                                                // Immediate load
                                                // DAC full scale output *1
                                                // Medium speed/current                                             
                                                // Straight binary
                                                // Not grouped 
                                                // DAC enabled
}

 
void ADC12Init(void)
{
   
 // Set up the ADC12 to sample a single-channel repeat-conversion */ 
  ADC12CTL0 &= ~ENC;                             //enable configuration 
  //ADC12CTL0 -> Control Register 0
  //15-12| 11-8 | 7 |   6   |  5  |   4   |    3    |     2    | 1 |   0   |
  //----------------------------------------------------------------------------
  //SHT1x|SHT0x |MSC|REF2_5V|REFON|ADC12ON|ADC12OVIE|ADC12TOVIE|ENC|ADC12SC|
  //SHT1x (Sample-and-hold time)                            ->  Not valid
  //SHT0x (Sample-and-hold time)                            ->  16 ADC12CLK cycles
  //MSC (Multiple sample and conversion)                    ->  Not valid
  //REF2_5V (Reference generator voltage)                   ->  2.5 V
  //REFON (Reference generator on)                          ->  Reference on
  //ADC12ON (ADC12 on)                                      ->  ADC12 on
  //ADC12OVIE (SADC12MEMx overflow-interrupt enable)        ->  disabled
  //ADC12TOVIE (ADC12 conversion-time-overflow int enable)  ->  disabled
  //ENC (Enable conversion)                                 ->  enable configuration
  //ADC12SC (Start conversion)                              ->  Start sample-and-conversion                 
    ADC12CTL0 |=__________________________; 
    
 //ADC12CTL1 -> Control Register 1
  //   15-12  |11-10| 9 | 8  |   7-5   |    4-3   |  2-1  |    0    |
  //----------------------------------------------------------------------------
  //CSTARTADDx| SHSx|SHP|ISSH|ADC12DIVx|ADC12SSELx|CONSEQx|ADC12BUSY|
  //CSTARTADDx (Conversion start address.)   ->  ADC12MEM0
  //SHSx (Sample-and-hold source select)     ->  ADC12SC bit
  //SHP (Sample-and-hold pulse-mode select)  ->  SAMPCON signal is sourced from the sample-input signal.
  //ISSH (Invert signal sample-and-hold)     ->  not inverted.
  //ADC12DIVx (ADC12 clock divider)          ->  /1
  //ADC12SSELx (ADC12 clock source)          ->  ADC12OSC
  //CONSEQx (Conversion sequence mode )      ->  Single-channel, single-conversion
  //ADC12BUSY (ADC12 busy)                   ->  read only  
    ADC12CTL1 = _________________________;   // Start MEM0, TB1, Rpt Sing.
    
      
 //ADC12MCTLx -> Conversion Memory Control Registers
  //   7  | 6-4 |3-0  | 
  //----------------------------------------------------------------------------
  //  EOS |SREFx|INCHx|
  //EOS (End of sequence)           ->  Not Used
  //SREFx (Select reference )       ->  VR+ = VREF+ and VR- = AVSS
  //INCHx (Input channel select)    ->  Tempreture sensor
    ADC12MCTL0 = ________________________;               
    
    ADC12CTL0 |= ____;                           // Enable conversions
    ADC12CTL0 |= _______;                       // Start conversion
    ADC12IE |= BIT0;                            // Interrupt enable 
}    

 
void OPInit()
{
  // Non-inverting PGA */
 
  //OAFBRx (OAx feedback resistor select) = 000b -> G=1
  //                                        001b -> G=1.3
  //                                        010b -> G=2
  //                                        011b -> G=2.7
  //                                        100b -> G=4
  //                                        101b -> G=5.3
  //                                        110b -> G=8
  //                                        111b -> G=16
  
  
  // OA0CTL1, Opamp Control Register 1
  // 7-5| 4-2| 1  |     0    |
  //----------------------------------------------------------------------------
  //OAFBRx|OAFCx|Reserved|OARRIP|
  //OAFBRx (OAx feedback resistor select) ->  Tap 0 (G=1)
  //OAFCx (OAx function control)          ->  Non-inverting PGA
  //Reserved 
  //OARRIP (OA rail-to-rail input off)    ->  OAx input signal range is rail-to-rail
    OA0CTL1 |= __________________________;
  // OAxCTL0, Opamp Control Register 0
  // 7-6| 5-4| 3-2 | 1  |     0    |
  //----------------------------------------------------------------------------
  //OANx|OAPx|OAPMx|OAPMx|OAADC1|OAADC0|
  //OANx (Inverting input select)     ->  not important
  //OAPx (Non-inverting input select) ->  DAC0 internal
  //OAPMx (Slew rate select)          -> Fast
  //OAADC1 (OA output select)         ->  output connected to internal/external A1
  //OAADC0 (OA output select)         ->  output not connected to internal A12
    OA0CTL0 |= __________________________;  
        
}    
 
void SystemInit()
{
    // Stop the watchdog timer */
    WDTCTL = WDTPW | WDTHOLD; 

    // Configure the FLL to lock at 128x32768 Hz => 4.199304 MHz */
    SCFI0 = FN_3 | FLLD_4;
    FLL_CTL0 = XCAP18PF;
    SCFQCTL = 32 - 1;
    FLL_CTL0 |= DCOPLUS; 
}

 
void main (void)
{  
  //system clok configuration
  SystemInit();  
  
  //DAC12 configuration
  DAC12Init();

  //ADC12 configuration
  ADC12Init();
  
  //OpAmp configuration
  OPInit();   
  
 // Timer_A configuration
  TACTL = ______________________________;  // ACLK
                                           // Continuous mode: CCR0 counts up to 0FFFFh
                                           // Timer_A clear
                                           // Timer_A interrupt enable

  // LCD COM0-COM1-COM2-COM3 configuration
  P5DIR |= 0x1E;                           // Ports P5.2, P5.3 and P5.4 as outputs
  P5SEL |= 0x1E;                           // Ports P5.2, P5.3 and P5.4 as special function (COM1, COM2 and COM3)

 // LCD_A S0-S21 configuration
  LCDAPCTL0 = LCDS24 | LCDS20 | LCDS16 | LCDS12 | LCDS8 | LCDS4;

  // LCDA configuration
  LCDACTL = LCDFREQ_192 | LCD4MUX | LCDSON | LCDON;   // (ACLK = 32768)/192, 4-mux LCD, LCD_A on, Segments on
  LCDAVCTL0 = LCDCPEN;                                // Charge pump enable
  LCDAVCTL1 = VLCD_3_44;                              // VLCD = 3,44 V 

  lcd_all_off();

// Interrupts enabled and enter in LPM3
  _BIS_SR(LPM3_bits + GIE);
}



//  ADC12_ISR reads the obtained value and prepares new conversion  
#pragma vector=ADC12_VECTOR
__interrupt void ADC_ISR(void)
{
    int x;
	x = ADC12MEM0;         // Reads data
	volatile float y = ((2.5*x / 4095) - 0.986) / 0.0035; //converting temperature
	show_on_lcd((int)y);
	ADC12CTL0 |= ADC12SC;  // Start new conversion
}

//TimerA_ISR Starts new conversion
 
#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA_ISR (void)
{
    ADC12CTL0 &= ~ADC12SC; //start a new ADC12 conversion
    TACTL &= ~TAIFG;
}

