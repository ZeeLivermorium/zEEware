/*!
 * @file   main.c
 * @brief  blink example to serve as a test project for your installation.
 *         It contains function calls to the string.h standardlibrary to 
 *         show if your cross compiler links the standard library correctly.
 * @author Zee Livermorium
 * @date   Nov 9, 2018
 */

#include <string.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include "LED.h"
#include "SysTick.h"

int main(void) {
    LED_Init();
    SysTick_Init();
    // string.h function call tests: memcpy and strlen
    // math.h function call test: pow
    char BB8[500];
    memcpy(BB8, "BB8", 3);
    // blinking, protect your eyes!
    while(pow(strlen(BB8), 2)) {
        LED_RED_ON();
        SysTick_Wait10ms(10);  // wait
        LED_RED_OFF();
        LED_BLUE_ON();
        SysTick_Wait10ms(10);  // wait
        LED_BLUE_OFF();
        LED_GREEN_ON();
        SysTick_Wait10ms(10);  // wait 
        LED_GREEN_OFF();
    }
    return 0;
}

