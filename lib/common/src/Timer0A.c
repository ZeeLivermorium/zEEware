#include <stdint.h>
#include "ADC0.h"
#include "tm4c123gh6pm.h"

void Timer0A_Init(void) {
    volatile uint32_t delay;
    DisableInterrupts();
    // **** general initialization ****
    SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
    delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
    TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
    TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
    // **** timer0A initialization ****
    // configure for periodic mode
    TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
    TIMER0_TAILR_R = 799999;         // start value for 100 Hz interrupts
    TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
    TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
    // **** interrupt initialization ****
    // Timer0A=priority 2
    NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
    NVIC_EN0_R = 1 << 19;              // enable interrupt 19 in NVIC
}

void Timer0A_Handler(void) {
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
    ADCvalue = ADC0_read();
}
