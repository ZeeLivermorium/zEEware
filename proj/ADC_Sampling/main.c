/*!
 * @file   main.c
 * @brief  This program samples ADC 1000 times and outputs to serial prompt.
 * @author Zee Lv
 * @date   Nov 9, 2018
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Serial.h"
#include "SysTick.h"
#include "ADC0.h"
#include "LED.h"
#include "button.h"

int main(void) {
    // init bus frequency to 80Mhz
    PLL_Init(Bus80MHz);
    // init LED for sampling inidication
    LED_Init();
    // init systick for a counter
    SysTick_Init();
    // init serial output 
    Serial_Init();
    // init ADC module 0
    ADC0_Init();
    // init button to trigger sampling
    button_init();

    uint32_t data;
    // press button to trigger sampling
    while(get_right_button_status());
    // sample and output 1000 times
    for (int i = 0; i < 1000; i++) {
        // sample
        data = ADC0_read();
        // output to serial
        Serial_println("%u", data);
        // toggle LED to show it's been sampling'
        LED_RED_TOGGLE();
        // wait
        SysTick_Wait10ms(1);
    }
    return 0;
}

