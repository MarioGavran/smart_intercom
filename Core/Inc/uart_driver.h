/*
 * uart_driver.h
 *
 *  Created on: Mar 18, 2021
 *      Author: Mario
 */

#ifndef INC_UART_DRIVER_H_
#define INC_UART_DRIVER_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "usart.h"

#include "ov7670.h"
#include "fsmc_driver.h"
#include "touch_driver.h"



typedef enum{
	UART_TX_IDLE,
	UART_TX_TRANSMIT,
	UART_TX_TRANSMITING
}uart_tx_state_t;

typedef enum{
	UART_RX_IDLE,
	UART_RX_RECEIVE,
}uart_rx_state_t;


#define UART_TX_BUFFER_MAX	255
#define UART_RX_BUFFER_MAX	255

void uart_init();
void uart_tx_process();
void uart_rx_process();
void uart_write(uint8_t* buff);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void uart_rx_callback();
void serial_protocol(uint8_t* buff);


#endif /* INC_UART_DRIVER_H_ */
