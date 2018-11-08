# Driver Library for VL53L0X ToF Distance Sensor for TM4C123

## Introduction
Driver Library for **STMicroelectronics VL53L0X Time-of-Flight Ranging Sensor** on **TI TM4C123G MCU**. Example Projects using this dirver is available in [Projects](Projects) folder. Keil uVision project files are included, which means you can just simply double click on them to open the example files and load to your TM4C123, if using Keil. Otherwise, you have to manage all source files by yourself. Source code used and provided by STMicroelectronics is in [core](core) and [platform](platform) folders. Other files used in this repository are in [inc](inc) folder.

## Documents
#### [TI TM4C123G Data Sheet](http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf)
#### [ST VL53L0X Data Sheet](https://www.st.com/resource/en/datasheet/vl53l0x.pdf)

## Protocols
VL53L0X only runs on I2C protocol. To use different I2C port, adjust the preprocessor setting in [VL53L0X_I2C.h](VL53L0X_I2C/VL53L0X_I2C.h#L26).

## Multiple VL53L0Xs
To use multiple VL53L0Xs at the same time using the same I2C bus, we need to first change the device I2C address. To avoid the address conflict during the address modification, the XSHUT pin is used. Pulling XSHUT down pin low puts VL53L0X into shutdown mode. By keeping only one sensor awake at a time, you can modify the device address for the awake VL53L0X, using the [*VL53L0X_setAddress*](VL53L0X/VL53L0X.h#L59) API. To wire multiple devices, you can use a few GPIO vins from TM4C123 or use a shift register IC, if saving pins is needed for your project. Of course, you should try any other circuit configuration, if you think it's needed.

## Problems and Bugs
If you find any bug or problem, please create new issue or a pull request with a fix in the repository.
Or you can simply email me about the problem or bug at zeelivermorium@gmail.com .
Much Appreciated!

## Copyright Note
This repository adpated and modified some source code from [Adafruit's VL53L0X Arduino driver](https://github.com/adafruit/Adafruit_VL53L0X) to make it run on TI TM4C123G MCU.
