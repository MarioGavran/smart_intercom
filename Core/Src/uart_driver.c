/*
 * uart_driver.c
 *
 *  Created on: Mar 18, 2021
 *      Author: Mario
 */
#include "uart_driver.h"


uart_tx_state_t g_uart_tx_state = UART_TX_IDLE;
uart_rx_state_t g_uart_rx_state = UART_RX_IDLE;

uint8_t g_uart_tx_buffer[UART_TX_BUFFER_MAX + 1] = {0};
uint16_t g_uart_tx_nose = 0;
uint16_t g_uart_tx_tail = 0;

uint8_t g_uart_rx_buffer[UART_RX_BUFFER_MAX + 1];
uint8_t g_uart_rx_tmp_buf[50];
uint16_t g_uart_rx_nose = 0;
uint16_t g_uart_rx_tail = 0;
uint16_t g_uart_rx_cnt = 0;



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void uart_init()
{
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void uart_tx_process()
{
	static uint8_t last_nose = 0;
	uint8_t string_size;

	switch(g_uart_tx_state)
	{
	//****************************
	case UART_TX_IDLE:
		if(g_uart_tx_nose != g_uart_tx_tail)
			g_uart_tx_state = UART_TX_TRANSMIT;
		break;

		//****************************
	case UART_TX_TRANSMIT:
		string_size = strlen(g_uart_tx_buffer + (g_uart_tx_nose)) + 1;

		HAL_UART_Transmit_IT(
				&huart6,
				g_uart_tx_buffer + g_uart_tx_nose,
				string_size);

		last_nose = g_uart_tx_nose;
		g_uart_tx_state = UART_TX_TRANSMITING;
		break;

		//****************************
	case UART_TX_TRANSMITING:
		if((last_nose == g_uart_tx_nose))
			g_uart_tx_state = UART_TX_TRANSMITING;
		else if((last_nose != g_uart_tx_nose) && (g_uart_tx_tail != g_uart_tx_nose))
			g_uart_tx_state = UART_TX_TRANSMIT;
		else if((last_nose != g_uart_tx_nose) && (g_uart_tx_tail == g_uart_tx_nose))
			g_uart_tx_state = UART_TX_IDLE;
		break;
	}
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void uart_write(uint8_t* buff)
{
	uint8_t string_size = strlen(buff) + 1;

	if(
			((g_uart_tx_tail - g_uart_tx_nose >= 0) && (string_size < UART_TX_BUFFER_MAX - (g_uart_tx_tail - g_uart_tx_nose))) ||
			((g_uart_tx_tail - g_uart_tx_nose <= 0) && (string_size < g_uart_tx_nose - g_uart_tx_tail)))
	{
		if(((g_uart_tx_tail - g_uart_tx_nose >= 0)) && (string_size > (UART_TX_BUFFER_MAX - g_uart_tx_tail)))
		{
			strncpy(g_uart_tx_buffer + g_uart_tx_tail, buff, UART_TX_BUFFER_MAX - g_uart_tx_tail);
			string_size -= (UART_TX_BUFFER_MAX - g_uart_tx_tail);
			strncpy(g_uart_tx_buffer + 0, buff + (UART_TX_BUFFER_MAX - g_uart_tx_tail), string_size);
			g_uart_tx_tail = 0;
			g_uart_tx_tail = string_size;
		}
		else
		{
			strcpy(g_uart_tx_buffer + g_uart_tx_tail, buff);
			if(g_uart_tx_tail + string_size < UART_TX_BUFFER_MAX)
				g_uart_tx_tail += string_size;
			else
				g_uart_tx_tail = 0;
		}
	}
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	g_uart_tx_nose += strlen(g_uart_tx_buffer + g_uart_tx_nose) + 1;

	if(g_uart_tx_nose >= UART_TX_BUFFER_MAX)
		g_uart_tx_nose = 0;

}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void uart_rx_process()
{
	uint8_t string_size = strlen(g_uart_rx_buffer + g_uart_rx_nose + 1) + 1;

	switch(g_uart_rx_state)
	{
	case UART_RX_IDLE:
		if(g_uart_rx_cnt)
			g_uart_rx_state = UART_RX_RECEIVE;
		break;

	case UART_RX_RECEIVE:
		if(g_uart_rx_nose < g_uart_rx_tail &&
				(g_uart_rx_buffer[g_uart_rx_nose + string_size - 2] == '\r') &&
				(g_uart_rx_buffer[g_uart_rx_nose + string_size - 1] == '\n'))
		{
			serial_protocol(g_uart_rx_buffer + g_uart_rx_nose + 1);
		}
		else if((g_uart_rx_nose > g_uart_rx_tail) &&
							(g_uart_rx_buffer[strlen(g_uart_rx_buffer) - 1] == '\n'))
		{
			strncpy(g_uart_rx_tmp_buf, g_uart_rx_buffer + g_uart_rx_nose + 1, string_size);
			string_size = strlen(g_uart_rx_buffer + 1) + 1;
			strncpy(g_uart_rx_tmp_buf + strlen(g_uart_rx_tmp_buf), g_uart_rx_buffer , string_size);
			serial_protocol(g_uart_rx_tmp_buf);
		}

		g_uart_rx_cnt--;

		if(g_uart_rx_nose + string_size < UART_RX_BUFFER_MAX)
			g_uart_rx_nose += string_size;
		else
			g_uart_rx_nose = string_size;

		if(!g_uart_rx_cnt)
			g_uart_rx_state = UART_RX_IDLE;
		break;


	}
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void uart_rx_callback()
{
	g_uart_rx_tail++;

	if((g_uart_rx_tail < (UART_RX_BUFFER_MAX - 1)) && ((g_uart_rx_nose < g_uart_rx_tail) || (g_uart_rx_nose - g_uart_rx_tail > 2/*1*/)))
	{
		g_uart_rx_buffer[g_uart_rx_tail] = (0x00FFU & USART6->DR);//253
		if((g_uart_rx_buffer[g_uart_rx_tail] == '\r') /*&& ((g_uart_rx_nose < g_uart_rx_tail) || (g_uart_rx_nose - g_uart_rx_tail > 2))*/)
		{
			g_uart_rx_buffer[++g_uart_rx_tail] = '\n';//254
			g_uart_rx_cnt++;
			g_uart_rx_buffer[++g_uart_rx_tail] = '\0';//255
			if((g_uart_rx_tail == UART_RX_BUFFER_MAX) && (g_uart_rx_nose > 0))
			{
				g_uart_rx_tail = 0;
			}
		}
	}
	else if((g_uart_rx_tail == (UART_RX_BUFFER_MAX - 1)) && (g_uart_rx_nose > 1)/*(g_uart_rx_nose < g_uart_rx_tail)*/)
	{
		g_uart_rx_buffer[g_uart_rx_tail] = (0x00FFU & USART6->DR);//254
		g_uart_rx_buffer[++g_uart_rx_tail] = '\0';//255
		if(g_uart_rx_buffer[g_uart_rx_tail - 1] == '\r')
		{
			g_uart_rx_cnt++;
			if(g_uart_rx_nose > 1)
			{
				g_uart_rx_tail = 0;
				g_uart_rx_buffer[g_uart_rx_tail] = '\n';//0
				g_uart_rx_buffer[++g_uart_rx_tail] = '\0';//1
			}
			else
			{
				//error - full
			}
		}
	}
	else if((g_uart_rx_tail == UART_RX_BUFFER_MAX) && (g_uart_rx_nose > 1))
	{
		g_uart_rx_buffer[g_uart_rx_tail] = '\0';
		g_uart_rx_tail = 1;
		g_uart_rx_buffer[g_uart_rx_tail] = (0x00FFU & USART6->DR);

	}

}


#include <stdlib.h>
//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void serial_protocol(uint8_t* buff)
{
	char *token;
	char temp_buff[5] = {0};
	unsigned short address, value = 0xFF;

	if (strncmp(buff, "OVW", 3) == 0)
	{
		token = strtok(buff, ",");

		token = strtok(NULL, ",");
		strncpy(temp_buff, token, 2);
		address = strtoll(temp_buff, NULL, 16);

		token = strtok(NULL, ",");
		strncpy(temp_buff, token, 2);
		value = strtoll(temp_buff, NULL, 16);

		ov7670_write_register(address, value);
		sprintf(temp_buff, "%02X\0", address);
		LCD_PrintStr(20, 400, 0, 0x841FU, temp_buff, 5);
		sprintf(temp_buff, "%02X\0", ov7670_read_register(address));
		LCD_PrintStr(20, 440, 0, 0x841FU, temp_buff, 5);
	}
	else if (strncmp(buff, "OVR", 3) == 0)
	{
		token = strtok(buff, ",");

		token = strtok(NULL, ",");
		strncpy(temp_buff, token, 2);
		address = strtoll(temp_buff, NULL, 16);

		value = ov7670_read_register(address);

		sprintf(temp_buff, "%02X\0", address);
		LCD_PrintStr(20, 400, 0, 0x841FU, temp_buff, 5);
		sprintf(temp_buff, "%02X\0", value);
		LCD_PrintStr(20, 440, 0, 0x841FU, temp_buff, 5);
	}
		//LCD_PrintStr(20, 400, 0, 0x841FU, buff, 5);
}



