/*
 * misc.c
 *
 *  Created on: Jun 11, 2021
 *      Author: enio
 */
#include "../Inc/misc.h"

uint16_t reverse_bits(uint16_t data)
{
	data = ((data & 0xFF00U) >> 8) | ((data & 0x00FFU) << 8);
	data = ((data & 0xF0F0U) >> 4) | ((data & 0x0F0FU) << 4);
	data = ((data & 0xCCCCU) >> 2) | ((data & 0x3333U) << 2);
	data = ((data & 0xAAAAU) >> 1) | ((data & 0x5555U) << 1);
	return data;
}

