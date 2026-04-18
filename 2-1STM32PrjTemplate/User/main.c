#include "stm32f10x.h"                  // Device header

#include "LEDControl.h"
#include <string.h>

uint8_t KeyNum;

int main(void)
{
	//Control();
	
	LED_BUZZER_OLED_LightSensor();
	while(1)
    {
        
    }
}
//int main(void)
//{
//	LED_Init();
//	Serial_Init();
//	OLED_Init();
//	
//	while(1)
//	{
//		LED0_ON();
//		Serial_SendString("LED ON\r\n");
//		Delay_ms(500);
//		
//		LED0_OFF();
//		Serial_SendString("LED OFF\r\n");
//		Delay_ms(500);
//	}
//}

