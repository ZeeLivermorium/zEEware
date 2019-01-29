/*!
 * @file  VL53L0X_Distance_Measure_1.c
 * @brief Use 1 VL53L0X to measure distance and display it to serial output.
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
 * @date   Aug 5, 2018
 */

#include <stdint.h>
#include "PLL.h"
#include "I2C.h"
#include "Serial.h"
#include "VL53L0X.h"

int main(void) {
    /*-- TM4C123 Init --*/
    PLL_Init(Bus80MHz);                   	    // bus clock at 80 MHz
    Serial_Init();                        	    // for serial I/O

    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 0)) { 	  // init and wake up VL53L0X
        Serial_println("Fail to initialize VL53L0X :(");
        delay(1);
        return 0;
    } else {
        Serial_println("VL53L0X Ready~ ");
    }
    
    VL53L0X_RangingMeasurementData_t measurement;
    
    /*-- loop --*/
    while(1) {                            	    // read and process
        Serial_println("Measuring... ");
        VL53L0X_getSingleRangingMeasurement(&measurement, 0);
        if (measurement.RangeStatus != 4) {
            Serial_println("Distance: %u mm", measurement.RangeMilliMeter);
        } else {
            Serial_println("Out of range :(");
        }
        delay(1000);                      	    // take a break
    }
}
