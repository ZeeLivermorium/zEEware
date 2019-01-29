/*!
 * @file  VL53L0X_Distance_Measure_4_ST7735.c
 * @brief Use 4 VL53L0X to measure distance and display it to ST7735 LCD screen.
 * ----------
 * Adapted code from Adafruit VL53L0X driver for Arduino.
 * You can find the Adafruit VL53L0X driver here: https://github.com/adafruit/Adafruit_VL53L0X
 * ----------
 * ST VL53L0X datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * ----------
 * For future development and updates, please follow this repository: https://github.com/ZeeLivermorium/VL53L0X_TM4C123
 * ----------
 * If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
 * Or you can simply email me about the problem or bug at zeelivermorium@gmail.com
 * Much Appreciated!
 * ----------
 * @author Zee Livermorium
 * @date   Jan 2, 2019
 */

#include <stdint.h>
#include "PLL.h"
#include "I2C.h"
#include "ST7735.h"
#include "VL53L0X.h"
#include "xshut.h"

int main(void) {
    /*-- TM4C123 Init --*/
    PLL_Init(Bus80MHz);                             // bus clock at 80 MHz
    xshut_Init();                                        // for multi senesor setup
    
    /*-- ST7735 Init --*/
    ST7735_InitR(INITR_REDTAB);
    
    ST7735_SetCursor(0, 0);
    ST7735_FillScreen(ST7735_BLACK);
    
    ST7735_OutString("@author: Zee Lv");
    ST7735_OutChar('\n');
    ST7735_OutString("--------------------");
    ST7735_OutChar('\n');
    
    /*-- VL53L0X Init --*/
    // must always inititalize with address 0x29
    // init and wake up VL53L0X sensor 1
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 0)) {
        ST7735_OutString("Fail to initialize VL53L0X 1 :(");
        delay(1);
        return 0;
    } else {
        ST7735_OutString("VL53L0X 1 Ready~ ");
        ST7735_OutChar('\n');
        // can change address after initialization
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 1, 0);
    }
    
    // switch to initaialize next sensor
    xshut_Switch();
    
    // must always inititalize with address 0x29
    // init and wake up VL53L0X sensor 2
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 1)) {
        ST7735_OutString("Fail to initialize VL53L0X 2 :(");
        delay(1);
        return 0;
    } else {
        ST7735_OutString("VL53L0X 2 Ready~ ");
        ST7735_OutChar('\n');
        // can change address after initialization
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 2, 1);
        
    }
    
    // switch to initaialize next sensor
    xshut_Switch();
    
    // must always inititalize with address 0x29
    // init and wake up VL53L0X sensor 2
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 2)) {
        ST7735_OutString("Fail to initialize VL53L0X 3 :(");
        delay(1);
        return 0;
    } else {
        ST7735_OutString("VL53L0X 3 Ready~ ");
        ST7735_OutChar('\n');
        // can change address after initialization
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 3, 2);
        
    }
    
    // switch to initaialize next sensor
    xshut_Switch();
    
    // must always inititalize with address 0x29
    // init and wake up VL53L0X sensor 2
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 3)) {
        ST7735_OutString("Fail to initialize VL53L0X 4 :(");
        delay(1);
        return 0;
    } else {
        ST7735_OutString("VL53L0X 4 Ready~ ");
        ST7735_OutChar('\n');
    }
    
    VL53L0X_RangingMeasurementData_t measurement1;
    VL53L0X_RangingMeasurementData_t measurement2;
    VL53L0X_RangingMeasurementData_t measurement3;
    VL53L0X_RangingMeasurementData_t measurement4;
    
    /*-- loop --*/
    while(1) {
        ST7735_OutString("Sensor 1, measuring... ");
        ST7735_OutChar('\n');
        VL53L0X_getSingleRangingMeasurement(&measurement1, 0);
        // 8000 cap to avoid out of range #
        if (measurement1.RangeStatus != 4 || measurement1.RangeMilliMeter < 8000) {
            ST7735_OutString("Distance: ");
            ST7735_OutUDec(measurement1.RangeMilliMeter);
            ST7735_OutString(" mm ");
            ST7735_OutChar('\n');
        } else {
            ST7735_OutString("Out of range :( ");
            ST7735_OutChar('\n');
        }
        
        ST7735_OutString("Sensor 2, measuring... ");
        ST7735_OutChar('\n');
        VL53L0X_getSingleRangingMeasurement(&measurement2, 1);
        // 8000 cap to avoid out of range #
        if (measurement2.RangeStatus != 4 || measurement2.RangeMilliMeter < 8000) {
            ST7735_OutString("Distance: ");
            ST7735_OutUDec(measurement2.RangeMilliMeter);
            ST7735_OutString(" mm ");
            ST7735_OutChar('\n');
        } else {
            ST7735_OutString("Out of range :( ");
            ST7735_OutChar('\n');
        }
        
        ST7735_OutString("Sensor 3, measuring... ");
        ST7735_OutChar('\n');
        VL53L0X_getSingleRangingMeasurement(&measurement3, 1);
        // 8000 cap to avoid out of range #
        if (measurement3.RangeStatus != 4 || measurement3.RangeMilliMeter < 8000) {
            ST7735_OutString("Distance: ");
            ST7735_OutUDec(measurement3.RangeMilliMeter);
            ST7735_OutString(" mm ");
            ST7735_OutChar('\n');
        } else {
            ST7735_OutString("Out of range :( ");
            ST7735_OutChar('\n');
        }
        
        ST7735_OutString("Sensor 4, measuring... ");
        ST7735_OutChar('\n');
        VL53L0X_getSingleRangingMeasurement(&measurement4, 1);
        // 8000 cap to avoid out of range #
        if (measurement4.RangeStatus != 4 || measurement4.RangeMilliMeter < 8000) {
            ST7735_OutString("Distance: ");
            ST7735_OutUDec(measurement4.RangeMilliMeter);
            ST7735_OutString(" mm ");
            ST7735_OutChar('\n');
        } else {
            ST7735_OutString("Out of range :( ");
            ST7735_OutChar('\n');
        }
        
        delay(4000);                                // take a break
        ST7735_SetCursor(0, 3);
    }
}
