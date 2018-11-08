/*!
 * @file  xshut.c
 * @brief APIs for interfacing xshut pins for VL53L0X for multi sensor projects.
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

#ifndef  __XSHUT_H__
#define __XSHUT_H__

void xshut_Init(void);

void xshut_Switch(void);

#endif
