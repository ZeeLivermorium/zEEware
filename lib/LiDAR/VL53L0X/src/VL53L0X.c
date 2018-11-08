/*!
 * @file  VL53L0X.c
 * @brief VL53L0X driver APIs and their implementation.
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
 * @date   Aug 4, 2018
 */

#include "VL53L0X.h"
#include "VL53L0X_I2C.h"
#include "LED.h"

#define VERSION_REQUIRED_MAJOR  1   // Required sensor major version
#define VERSION_REQUIRED_MINOR  0   // Required sensor minor version
#define VERSION_REQUIRED_BUILD  1   // Required sensor build

VL53L0X_Error status = VL53L0X_ERROR_NONE; // indicates whether or not the sensor has encountered an error

/**
 * VL53L0X_Init
 * ----------
 * @param  I2C_address  address to be set for the I2C device.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Initialize VL53L0X.
 */
int VL53L0X_Init (uint8_t I2C_address, int index) {
    
    // set device address to default
    deviceList[index].device.I2cDevAddr = I2C_address;  // default
    
    // variable needed for some function calls
    uint32_t  refSpadCount;
    uint8_t   isApertureSpads;
    uint8_t   VhvSettings;
    uint8_t   PhaseCal;
    
    // unclear if this is even needed:
    if( VL53L0X_IMPLEMENTATION_VER_MAJOR != VERSION_REQUIRED_MAJOR ||
       VL53L0X_IMPLEMENTATION_VER_MINOR != VERSION_REQUIRED_MINOR ||
       VL53L0X_IMPLEMENTATION_VER_SUB != VERSION_REQUIRED_BUILD ) {
        status = VL53L0X_ERROR_NOT_SUPPORTED;
        return FAIL;
    }
    
    // data initialization
    status = VL53L0X_DataInit(&deviceList[index].device);

    // set device address if not using default
    if (!(I2C_address == VL53L0X_I2C_ADDR)) {
        if (!VL53L0X_setAddress(I2C_address, index)) {
            return FAIL;
        }
    }
    
    // reads the device information for given device
    status = VL53L0X_GetDeviceInfo( &deviceList[index].device, &deviceList[index].deviceInfo );
    if( status == VL53L0X_ERROR_NONE )  {
        if(( deviceList[index].deviceInfo.ProductRevisionMinor != 1 ) && ( deviceList[index].deviceInfo.ProductRevisionMinor != 1 )) {
            status = VL53L0X_ERROR_NOT_SUPPORTED;
        }
    }

    if( status == VL53L0X_ERROR_NONE ) {
        // device initialization
        status = VL53L0X_StaticInit( &deviceList[index].device );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // performs reference spad Management
        status = VL53L0X_PerformRefSpadManagement( &deviceList[index].device, &refSpadCount, &isApertureSpads );
    }

    if( status == VL53L0X_ERROR_NONE ) {
        // perform reference calibration
        status = VL53L0X_PerformRefCalibration( &deviceList[index].device, &VhvSettings, &PhaseCal );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // setup in single ranging mode
        status = VL53L0X_SetDeviceMode( &deviceList[index].device, VL53L0X_DEVICEMODE_SINGLE_RANGING );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // enable sigma check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // enable signal check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // enable range check
        status = VL53L0X_SetLimitCheckEnable( &deviceList[index].device, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1 );
    }
    
    if( status == VL53L0X_ERROR_NONE ) {
        // set limit check value
        status = VL53L0X_SetLimitCheckValue( &deviceList[index].device,
                                             VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD,
                                             (FixPoint1616_t)( 1.5 * 0.023 * 65536 )
                                           );
    }
    
    // return initialization status
    return (status == VL53L0X_ERROR_NONE) ? SUCCESS : FAIL;
}

/**
 * VL53L0X_setAddress
 * ----------
 * @param  newAddress  the new address to set the VL53L0X to.
 * ----------
 * @return 0 for failed initialization, 1 for successful initialization.
 * ----------
 * @brief  Change the I2C address of VL53L0X.
 */
int VL53L0X_setAddress(uint8_t newAddress, int index) {
    // trim the new address
    newAddress &= 0x7F;
    
    status = VL53L0X_SetDeviceAddress(&deviceList[index].device, newAddress * 2);  // [7:2] is address
    
    delay(10);
    
    if( status == VL53L0X_ERROR_NONE ) {
        deviceList[index].device.I2cDevAddr = newAddress;  // 7 bit addr
        return SUCCESS;
    }
    
    return FAIL;
}

/**
 * VL53L0X_getSingleRangingMeasurement
 * ----------
 * @param  RangingMeasurementData  pointer for where to store the ranging data.
 * ----------
 * @return any error code.
 * ----------
 * @brief  Get a ranging measurement from VL53L0X.
 */
VL53L0X_Error VL53L0X_getSingleRangingMeasurement (VL53L0X_RangingMeasurementData_t* RangingMeasurementData, int index) {
    return VL53L0X_PerformSingleRangingMeasurement( &deviceList[index].device, RangingMeasurementData );
}

