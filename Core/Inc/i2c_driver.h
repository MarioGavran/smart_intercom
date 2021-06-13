/*
 * i2c_driver.h
 *
 *  Created on: Apr 5, 2021
 *      Author: Mario
 */

#ifndef SRC_I2C_DRIVER_H_
#define SRC_I2C_DRIVER_H_


#include <stdint.h>
#include "i2c_driver.h"
#include "i2c.h"



uint8_t i2c_read_reg(uint8_t address, uint8_t reg);
void i2c_write_reg(uint8_t address, uint8_t reg, uint8_t data);




#endif /* SRC_I2C_DRIVER_H_ */
