#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//    // 单独定义结构体（用于GPIOB初始化，避免覆盖）
    GPIO_InitTypeDef GPIO_InitStructure_B;
    GPIO_InitStructure_B.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIO_InitStructure_B.GPIO_Pin = GPIO_Pin_12;  // 蜂鸣器引脚
    GPIO_InitStructure_B.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOB, &GPIO_InitStructure_B);  // 初始化GPIOB
	 // 初始化后主动关闭蜂鸣器（设置为高电平，根据硬件电路可能需要调整）
    GPIO_SetBits(GPIOB, GPIO_Pin_12);  // 对应Buzzer_OFF的逻辑
}
/**
  * 函    数：LED0开启
  * 参    数：无
  * 返 回 值：无
  */
void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);		//设置PA1引脚为低电平
}

/**
  * 函    数：LED0关闭
  * 参    数：无
  * 返 回 值：无
  */
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);		//设置PA1引脚为高电平
}

/**
  * 函    数：LED1状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);					//则设置PA1引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);					//则设置PA1引脚为低电平
	}
}
