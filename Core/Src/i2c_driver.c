/*
 * i2c_driver.c
 *
 *  Created on: Apr 5, 2021
 *      Author: Mario
 */
#include "i2c_driver.h"

uint8_t tx_data[5] = {0};
uint8_t rx_data[5] = {0};

extern I2C_HandleTypeDef hi2c2;


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
uint8_t i2c_read_reg(uint8_t address, uint8_t reg)
{
	tx_data[0] = reg;
	HAL_I2C_Master_Transmit(&hi2c2, 0x42U, tx_data, 1, 10);
	HAL_I2C_Master_Receive(&hi2c2, 0x42U, rx_data, 1, 10);
	HAL_Delay(1);
	return rx_data[0];
}



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void i2c_write_reg(uint8_t address, uint8_t reg, uint8_t data)
{
	tx_data[0] = reg;
	tx_data[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, 0x42U, tx_data, 2, 10);
	HAL_Delay(1);
}

