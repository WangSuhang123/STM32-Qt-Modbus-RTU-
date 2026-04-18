#include "stm32f10x.h"                  // Device header

//void LightSensor_init(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	//    // 单独定义结构体（用于GPIOB初始化，避免覆盖）
//    GPIO_InitTypeDef GPIO_InitStructure_B;
//    GPIO_InitStructure_B.GPIO_Mode = GPIO_Mode_IPU;  // 推挽输出
//    GPIO_InitStructure_B.GPIO_Pin = GPIO_Pin_15;  // 
//    GPIO_InitStructure_B.GPIO_Speed = GPIO_Speed_50MHz;
//	
//    GPIO_Init(GPIOB, &GPIO_InitStructure_B);  // 初始化GPIOB
//}
void LightSensor_init(void)
{
    // 1. 开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // 2. PA0 设为模拟输入
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. ADC 配置
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    // 校准
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

//uint8_t LightSensor_Get(void){

//	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
//}


// 获取光照强度 0~100
uint8_t LightSensor_GetValue(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    uint16_t adc = ADC_GetConversionValue(ADC1);

    // 转成 0~100
    uint8_t light = 100 - (adc * 100 / 4095);
    return light;
}
