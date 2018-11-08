/*!
 * @file  xshut.c
 * @brief Implementation for interfacing xshut pins for VL53L0X for multi sensor projects.
 * ----------
 * ST VL53L0X datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * ----------
 * For future development and updates, please follow this repository: https://github.com/ZeeLivermorium/VL53L0X_TM4C123
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * @author Zee Livermorium
 * @date   Sep 19, 2018
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "VL53L0X.h"

uint8_t mask = 0x01;

void xshut_Init(void) {
    /* Port E Activation */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;               // enable GPIO Port E clock
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0){};    // allow time for activating
    
    /* Port E Set Up */
    GPIO_PORTE_CR_R = 0x03;                                // allow changes to PE0-1
    GPIO_PORTE_DIR_R = 0x03;                               // make PE0-1 output
    GPIO_PORTE_AMSEL_R &= ~0x03;                           // disable analog on PE0-1
    GPIO_PORTE_PCTL_R &= ((~GPIO_PCTL_PF1_M) &             // configure PF1 as GPIO
                          (~GPIO_PCTL_PF2_M));             // configure PF2 as GPIO
    GPIO_PORTE_AFSEL_R  &= ~0x03;                          // disable alt functtion on PE0-1
    GPIO_PORTE_DEN_R = 0x03;                               // enable digital I/O on PE0-1
    
    GPIO_PORTE_DATA_R = 0x00 ;                             // put all sensors into reset
		delay(50);
		GPIO_PORTE_DATA_R = 0xFF ;                             // put all sensors into reset
		delay(50);
		GPIO_PORTE_DATA_R = ~mask;
}

void xshut_Switch(void) {
    mask <<= 1;
    GPIO_PORTE_DATA_R = ~mask;
	  delay(50);
}

