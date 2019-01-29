/*!
 * @file  VL53L0X_Distance_Measure_4.c
 * @brief Use 4 VL53L0Xs to measure distance and display it to serial output.
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
 * @author Zee Livermorium and Tariq Muhanna
 * @date   Dec 25, 2018
 */

#include <stdint.h>
#include "PLL.h"
#include "I2C.h"
#include "LED.h"
#include "Serial.h"
#include "VL53L0X.h"
#include "xshut.h"

int main(void) {
    /*-- TM4C123 Init --*/
    PLL_Init(Bus80MHz);                   	     		// bus clock at 80 MHz
    Serial_Init();                        	     		// for serial I/O
    xshut_Init();                                		// for multi senesor setup
    
    // must always inititalize with address 0x29
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 0)) { 	   		// init and wake up VL53L0X sensor 1
        Serial_println("Fail to initialize VL53L0X 1 :(");
        delay(1);
        return 0;
    } else {
        Serial_println("VL53L0X 1 Ready~ ");
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 1, 0);	// can change address after initialization
    }
    
    // switch to initaialize next sensor
    xshut_Switch();
    // must always inititalize with address 0x29
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 1)) { 			// init and wake up VL53L0X sensor 2
        Serial_println("Fail to initialize VL53L0X 2 :(");
        delay(1);
        return 0;
    } else {
        Serial_println("VL53L0X 2 Ready~ ");
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 2, 1);	// can change address after initialization
    }
    
    // switch to initaialize next sensor
    xshut_Switch();
    // must always inititalize with address 0x29
    if(!VL53L0X_Init(VL53L0X_I2C_ADDR, 2)) { 			// init and wake up VL53L0X sensor 3
        Serial_println("Fail to initialize VL53L0X 3 :(");
        delay(1);
        return 0;
    } else {
        Serial_println("VL53L0X 3 Ready~ ");
        VL53L0X_setAddress(VL53L0X_I2C_ADDR + 3, 2);	// can change address after initialization
    }
    
    VL53L0X_RangingMeasurementData_t measurement1;
    VL53L0X_RangingMeasurementData_t measurement2;
    VL53L0X_RangingMeasurementData_t measurement3;
    
    /*-- loop --*/
    while(1) {                            	     		// read and process
        
        Serial_println("Sensor 1, measuring... ");
        VL53L0X_getSingleRangingMeasurement(&measurement1, 0);
        if (measurement1.RangeStatus != 4 || measurement1.RangeMilliMeter < 8000) {			// 8000 cap to avoid out of range #
            Serial_println("Distance: %u mm", measurement1.RangeMilliMeter);
        } else {
            Serial_println("Out of range :(");
        }
        
        Serial_println("Sensor 2, measuring... ");
        VL53L0X_getSingleRangingMeasurement(&measurement2, 1);
        if (measurement2.RangeStatus != 4 || measurement2.RangeMilliMeter < 8000) {			// 8000 cap to avoid out of range #
            Serial_println("Distance: %u mm", measurement2.RangeMilliMeter);
        } else {
            Serial_println("Out of range :(");
        }
        
        Serial_println("Sensor 3, measuring... ");
        VL53L0X_getSingleRangingMeasurement(&measurement3, 2);
        if (measurement3.RangeStatus != 4 || measurement3.RangeMilliMeter < 8000) {			// 8000 cap to avoid out of range #
            Serial_println("Distance: %u mm", measurement3.RangeMilliMeter);
        } else {
            Serial_println("Out of range :(");
        }
        
        delay(3000);                      	     // take a break
    }
}
