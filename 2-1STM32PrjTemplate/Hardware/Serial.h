#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include <stdint.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

//返回modbus协议
uint16_t CRC16_Modbus(const uint8_t *data, uint16_t length);
void Serial_SendFrame(uint8_t addr,uint8_t func, const uint8_t *data,uint8_t dataLen);

// 
#define USART1_RX_BUF_LEN 32
extern volatile uint8_t USART1_RX_BUF[USART1_RX_BUF_LEN];
extern volatile uint8_t usart_rx_index;
extern volatile uint8_t rx_done_flag;



#endif
