/*!
 * @file  VL53L0X_I2C.c
 * @brief VL53L0X I2C initialization and read/write APIs as well as their implementation.
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

#include <stdint.h>
#include "I2C.h"
#include "tm4c123gh6pm.h"

/****************************************************
 *                                                  *
 *                     R/W API                      *
 *                                                  *
 ****************************************************/

/**
 * VL53L0X_read_multi
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  pdata          data address to store read data.
 * @param  count          number of bytes to be read.
 * ----------
 * @brief read 1 or more bytes from VL53L0X.
 */
int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t* pdata, uint32_t count) {
    return I2C_read(deviceAddress, index, pdata, count);
}

/**
 * VL53L0X_write_byte
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  pdata          data address of data to be writen.
 * @param  count          number of bytes to be writen.
 * ----------
 * @brief write 1 or more bytes to VL53L0X.
 */
int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t* pdata, uint32_t count) {
    return I2C_write(deviceAddress, index, pdata, count);
}

/**
 * VL53L0X_read_byte
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 1 byte from VL53L0X.
 */
int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data) {
    // read 1 byte
    return I2C_read_byte(deviceAddress, index, data);
}


/**
 * VL53L0X_write_byte
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 1 byte to VL53L0X.
 */
int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data) {
    // write 1 byte
    return I2C_write_byte(deviceAddress, index, data);
}

/**
 * VL53L0X_read_word
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 2 bytes from VL53L0X.
 */
int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data) {
    // buffer to hold read data
    uint8_t buffer[2];
    // read 2 bytes
    int result = I2C_read_2_bytes(deviceAddress, index, buffer);
    // store read data
    *data = (buffer[0] << 8) + buffer[1];
    
    return result;
}

/**
 * VL53L0X_write_word
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 2 bytes to VL53L0X.
 */
int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data) {
    // buffer to hold read data
    uint8_t buffer[2];
    // put data into buffer
    buffer[1] = data & 0xFF;
    buffer[0] = data >> 8;
    // write 2 bytes
    return I2C_write_2_bytes(deviceAddress, index, buffer);
}

/**
 * VL53L0X_read_dword
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 4 bytes from VL53L0X.
 */
int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data) {
    // buffer to hold read data
    uint8_t buffer[4];
    // read 4 bytes
    int result = I2C_read_4_bytes(deviceAddress, index, buffer);
    // srore read data
    *data = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
    
    return result;
}

/**
 * VL53L0X_write_dword
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 4 bytes to VL53L0X.
 */
int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data) {
    // buffer to hold read data
    uint8_t buffer[4];
    // put data into buffer
    buffer[0] = data >> 24;
    buffer[1] = data >> 16;
    buffer[2] = data >> 8;
    buffer[3] = data & 0xFF;
    // write 4 bytes
    return I2C_write_4_bytes(deviceAddress, index, buffer);
}

