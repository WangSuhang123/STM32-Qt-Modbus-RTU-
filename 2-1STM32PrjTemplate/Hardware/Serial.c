#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Serial.h"
#include "LED.h"

#define USART1_RX_BUF_LEN 32
/*
volatile表示这个变量随时会被硬件 / 中断改掉！每次都必须去内存里重新读
*/
volatile uint8_t USART1_RX_BUF[USART1_RX_BUF_LEN];	//定义一个数组 → 串口接收数据的缓冲区
volatile uint8_t usart_rx_index = 0;	//组下标（记录存到第几个位置了）
volatile uint8_t rx_done_flag = 0;		//标志位（信号量）数据接收完成了吗？

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

/*
硬件自动调用，不需要你在 main 里调用
只要串口收到 1 个字节，CPU 立刻暂停当前任务，跑来执行这个函数
执行完再回去干原来的事
*/

//void USART1_IRQHandler(void)
//{
//	/*
//	参数 1：USART1
//选择哪一个串口
//STM32 有 USART1、USART2、USART3…
//参数 2：USART_IT_RXNE
//RXNE = Receive Not Empty
//中文：接收寄存器非空
//意思：串口收到数据了！
//返回值
//SET → 1 → 真的收到数据
//RESET → 0 → 没收到
//	*/
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		uint8_t ch = USART_ReceiveData(USART1);
//		
//		if (ch == '\n' || ch == '\r')
//		{
//			rx_done_flag = 1;
//		}
//		else
//		{
//			if (usart_rx_index < USART1_RX_BUF_LEN - 1)
//			{
//				USART1_RX_BUF[usart_rx_index++] = ch;
//			}
//			else
//			{
//				usart_rx_index = 0;
//			}
//		}
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}
void USART1_IRQHandler(void)
{
	
	//LED0_ON();
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        uint8_t ch = USART_ReceiveData(USART1);
		
		

        if (usart_rx_index < USART1_RX_BUF_LEN)
        {
            USART1_RX_BUF[usart_rx_index++] = ch;
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

uint16_t CRC16_Modbus(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}


void Serial_SendFrame(uint8_t addr, uint8_t func, const uint8_t *data, uint8_t dataLen)
{
    uint8_t buf[64];	//缓存列表
    uint8_t idx = 0;

    buf[idx++] = 0xAA;	//帧头
    buf[idx++] = 0x55;
    buf[idx++] = addr;	//地址码
    buf[idx++] = func;	//功能码
    buf[idx++] = dataLen;	//数据长度
	
    // 添加数据段
    for (uint8_t i = 0; i < dataLen; i++) {
        buf[idx++] = data[i];
    }

	// 计算 CRC（从帧头开始到数据段结束）
    uint16_t crc = CRC16_Modbus(buf, idx);
	
    buf[idx++] = crc & 0xFF;	//低位
    buf[idx++] = (crc >> 8) & 0xFF;	//高位

    for (uint8_t i = 0; i < idx; i++) {
        Serial_SendByte(buf[i]);   // 原来的发送字节函数
    }
}
