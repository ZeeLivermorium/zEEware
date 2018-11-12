#include <stdint.h>
#include "tm4c123gh6pm.h"

void ADC0_Init(void){
    /*-- SSI0 and Port A Activation --*/
    SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;                 // enable ADC Module 0
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;               // enable clock for Port E
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0) {};   // wait for Port E to be ready
    
    /*-- Port F Set Up --*/
    GPIO_PORTE_DIR_R &= ~0x10;                             // make PE4 input
    GPIO_PORTE_AFSEL_R |= 0x10;                            // enable alternate function on PE4
    GPIO_PORTE_AMSEL_R |= 0x10;                            // enable analog functionality on PE4
    GPIO_PORTE_DEN_R &= ~0x10;                             // disable digital I/O on PE4
    GPIO_PORTE_PCTL_R &= ~GPIO_PCTL_PE4_M;                 // clear bit field on PE4
    GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_AIN9;               // enable analog input channel 9 on PE4

    while((SYSCTL_PRADC_R&SYSCTL_PRADC_R0) == 0) {};       // wait till ADC Module 0 peripheral to be ready
    
    /*-- ADC Module 0 Sets Up --*/
    ADC0_PC_R &= ~ADC_PC_SR_M;                             // clear max sample rate field
    ADC0_PC_R |= ADC_PC_SR_125K;                           // configure for 125K samples/sec
    ADC0_SSPRI_R = 0x0123;                                 // sequencer 3 is highest priority
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN3;                      // disable sample sequencer 3
    ADC0_EMUX_R &= ~ADC_EMUX_EM3_M;                        // seq3 is software trigger
    ADC0_SSMUX3_R &= ~ADC_SSMUX3_MUX0_M;                   // clear SS3 field
    ADC0_SSMUX3_R += 9;                                    // set to channel 9
    ADC0_SSCTL3_R |= ADC_SSCTL0_IE0 |                      // enable 1st sample interrupt
                     ADC_SSCTL0_END0;                      // 1st sample is the end of sequence
    ADC0_IM_R &= ~ADC_IM_MASK3;                            // disable SS3 interrupts
    ADC0_SAC_R &= ADC_SAC_AVG_M;                           // clear hardware averaging bit field
    ADC0_SAC_R |= ADC_SAC_AVG_16X;                         // hardware averaging setting
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;                       // enable sample sequencer 3
}


uint32_t ADC0_read(void) {
    ADC0_PSSI_R = ADC_PSSI_SS3;                            // initiate SS3
    while((ADC0_RIS_R & ADC_RIS_INR3) == 0 ) {};           // wait for conversion done
    uint32_t result = ADC0_SSFIFO3_R & ADC_SSFIFO3_DATA_M; // read result
    ADC0_ISC_R = ADC_ISC_IN3;                              // acknowledge interrupt status
    return result;
}
