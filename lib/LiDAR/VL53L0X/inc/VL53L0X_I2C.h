/*!
 * @file  VL53L0X_I2C.h
 * @brief VL53L0X I2C initialization and read/write APIs.
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
int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t* pdata, uint32_t count);

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
int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t* pdata, uint32_t count);

/**
 * VL53L0X_read_byte
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 1 byte from VL53L0X.
 */
int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data);


/**
 * VL53L0X_write_byte
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 1 byte to VL53L0X.
 */
int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data);

/**
 * VL53L0X_read_word
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 2 bytes from VL53L0X.
 */
int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data);

/**
 * VL53L0X_write_word
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 2 bytes to VL53L0X.
 */
int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data);

/**
 * VL53L0X_read_dword
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data address to store read data.
 * ----------
 * @brief read 4 bytes from VL53L0X.
 */
int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data);

/**
 * VL53L0X_write_dword
 * ----------
 * @param  deviceAddress  address of slave device.
 * @param  index          index of corresponding register in VL53L0X.
 * @param  data           data to be writen.
 * ----------
 * @brief write 4 bytes to VL53L0X.
 */
int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data);

