#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"       // 必须有
#include "buzzer.h"
#include "key.h"
#include "LightSensor.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "LEDControl.h"


//全局状态标志（表示是否开启检测）
uint8_t g_lightMonitorEnable = 0; 


void Control(void)
{
	LED_Init();
	Serial_Init();
	OLED_Init();
	
	//memset，把一段内存全部清空，USART1_RX_BUF串口接收数据的数组（缓冲区），USART1_RX_BUF_LEN缓冲区长度
	memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
	
	while (1)
	{
		if (rx_done_flag)
		{
			rx_done_flag = 0;
			USART1_RX_BUF[usart_rx_index] = '\0';
			
			OLED_ShowString(1, 1, "get");
			
			
			//strcmp 比较两个字符串是否相等
			if (strcmp((char*)USART1_RX_BUF, "ON") == 0)
			{
				LED0_ON();
				OLED_ShowString(2, 1, "LED ON ");
			}
			
			if (strcmp((char*)USART1_RX_BUF, "OFF") == 0)
			{
				LED0_OFF();
				OLED_ShowString(2, 1, "LED OFF");
			}
			
			usart_rx_index = 0;
			memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
		}
	}
}

//明文传输版
//void LED_BUZZER_OLED_LightSensor(void)
//{
////初始化模块
//	LED_Init();
//	Serial_Init();
//	OLED_Init();
//	Buzzer_Init();
//	LightSensor_init();
//	
//	//清空内存
//	memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//	
//	while (1)
//	{
//		if (rx_done_flag)
//		{
//			rx_done_flag = 0;
//			USART1_RX_BUF[usart_rx_index] = '\0';
//			
//			OLED_ShowString(1, 1, "getInfo");
//			LED0_ON();
//			
//			//开始检测
//			//strcmp 比较两个字符串是否相等
//			if (strcmp((char*)USART1_RX_BUF, "ON") == 0)
//			{
//				g_lightMonitorEnable = 1;  // 只置标志位，不卡死
//				OLED_ShowString(2, 1, "RUNNING");
//			}
//			
//			//关闭检测
//			if (strcmp((char*)USART1_RX_BUF, "OFF") == 0)
//			{
//				g_lightMonitorEnable = 0;
//				LED2_OFF();
//				LED3_OFF();
//				Buzzer_OFF();
//				OLED_ShowString(2, 1, "CLOSED");
//			}
//			
//			usart_rx_index = 0;
//			memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//		}
//		
//		//如果开启了检测，才执行逻辑
//			if(g_lightMonitorEnable == 1){
//				
//				//向QT上位机发送状态
//					static uint32_t sendCount = 0;
//					sendCount++;
//					//粗略的控制频率
//					if(sendCount % 10 == 0){
//						if (LightSensor_Get() == 1) {
//							Serial_SendString("WARNING:NO_LIGHT\n");
//						} else {
//							Serial_SendString("NORMAL:HAS_LIGHT\n");
//						}
//					}
//				
//				if(LightSensor_Get() == 1){
//					//无光报警
//					LED2_ON();
//					LED3_OFF();
//					Buzzer_OFF();
//					OLED_ShowString(3, 1, "WARNING NO LIGHT");
//				}else{
//					//有光正常
//					LED2_OFF();
//					LED3_ON();
//					Buzzer_OFF();
//					OLED_ShowString(3, 1, "NO WARNING");
//				
//				}
//			}
//			
//			Delay_ms(10); 
//	}
//}

//modbus串口协议版
//void LED_BUZZER_OLED_LightSensor(void)
//{
//	//初始化模块
//	LED_Init();
//    Serial_Init();
//    OLED_Init();
//    Buzzer_Init();
//    LightSensor_init();
//	
//	//清空接收缓存区
//	memset((uint8_t*)USART1_RX_BUF,0,USART1_RX_BUF_LEN);
//	usart_rx_index = 0;
//	rx_done_flag = 0;
//	
//	OLED_ShowString(1,1,"Waiting...");
//	
//	while(1){
//		//接收命令并解析命令帧
//		if(rx_done_flag){
//			rx_done_flag = 0;
//			
//			//简单判断是否位完整帧
//			//假设USART1_RX_BUF 已经收到一帧完整数据，且 usart_rx_index 是当前长度
//			if(usart_rx_index >= 7 && USART1_RX_BUF[0] == 0xAA && USART1_RX_BUF[1] == 0x55){
//				
//				uint8_t addr = USART1_RX_BUF[2];
//				uint8_t func = USART1_RX_BUF[3];
//				uint8_t dataLen = USART1_RX_BUF[4];
//				//uint8_t *payload = (uint8_t*)&USART1_RX_BUF[5];   // 强制转换解决 volatile 警告
//				
//				// 防止数据长度过大导致越界
//                if (dataLen > 32 || 5 + dataLen + 2 > usart_rx_index) {
//                    OLED_ShowString(1, 1, "Len Err ");
//                    goto clear_buffer;
//                }
//				
//				//CRC校验（只校验到数据段结束，不含 CRC 本身）
//				uint16_t receivedCRC = USART1_RX_BUF[5+dataLen] | (USART1_RX_BUF[6 + dataLen] << 8);
//				uint16_t calcCRC = CRC16_Modbus((const uint8_t*)USART1_RX_BUF,5 + dataLen);
//				
//				//校验成功
//				if(receivedCRC == calcCRC && addr == 0x01){
//					OLED_ShowString(1,1,"cmd OK");
//					//开始检测
//					if(func == 0x01){
//						g_lightMonitorEnable = 1;
//						OLED_ShowString(2, 1, "RUNNING");
//					}
//					else if(func == 0x02){	//关闭检测
//						g_lightMonitorEnable = 0;
//						LED2_OFF();
//						LED3_OFF();
//                        Buzzer_OFF();
//                        OLED_ShowString(2, 1, "CLOSED");
//					}
//					else if(func == 0x03){	//查询状态
//						//可以立即回复当前状态
//						//uint8_t sensor = LightSensor_Get();
//						uint8_t sensor = LightSensor_GetValue();
//                        uint8_t data[2] = { g_lightMonitorEnable, sensor };
//                        Serial_SendFrame(0x01, 0x81, data, 2);
//					}
//					
//				}else{
//					OLED_ShowString(1, 1, "CRC Err");
//				}
//				
//			}else{
//			
//				OLED_ShowString(1, 1, "Frame Err");
//			}
//		clear_buffer:
//			//清空缓冲区准备下一帧
//			usart_rx_index = 0;
//			memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//		}
//		//周期性发送状态帧
//		if(g_lightMonitorEnable == 1){
//			static uint32_t sendCount = 0;
//			sendCount++;
//			if(sendCount % 50 ==0){	//大约每500ms发一次
//				//uint8_t sensor = LightSensor_Get();	//假设返回1or0
//				uint8_t sensor = LightSensor_GetValue();
//				uint8_t data[2];
//				data[0] = g_lightMonitorEnable;   // 使能标志
//                data[1] = sensor;                 // 光敏值
//				
//				//发送状态应答帧：功能码0x81
//				Serial_SendFrame(0x01,0x81,data,2);
//				
//				if (sensor > 50)
//                {
//                    LED2_ON();
//                    LED3_OFF();
//                    Buzzer_ON();        // 你原来是 Buzzer_OFF，这里根据实际需求改
//                    OLED_ShowString(3, 1, "WARNING!  ");
//                }
//                else
//                {
//                    LED2_OFF();
//                    LED3_ON();
//                    Buzzer_OFF();
//                    OLED_ShowString(3, 1, "NORMAL    ");
//                }
//				
//			}
//		}else{
//			//关闭状态也可以偶尔发送一次关闭确认
//		}
//		Delay_ms(20);
//		
//	}

//}
//void LED_BUZZER_OLED_LightSensor(void)
//{
//    // 初始化模块
//    LED_Init();
//    Serial_Init();
//    OLED_Init();
//    Buzzer_Init();
//    LightSensor_init();
//    
//    // 清空接收缓存区
//    memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//    usart_rx_index = 0;
//    
//    OLED_ShowString(1, 1, "Waiting...");
//    
//    while(1){
//        // ================= 【改动核心部分开始】 =================
//        // 判断缓冲区是否有基础的最小帧长度（7字节：头2+地址1+功能1+长度1+CRC2）
//        if (usart_rx_index >= 7) {
//            
//            // 1. 校验帧头是否正确
//            if (USART1_RX_BUF[0] == 0xAA && USART1_RX_BUF[1] == 0x55) {
//                
//                uint8_t dataLen = USART1_RX_BUF[4];
//                
//                // 防护：如果数据长度过大，说明出现错位或脏数据，直接清空重接
//                if (dataLen > 32) {
//                    OLED_ShowString(1, 1, "Len Err ");
//                    usart_rx_index = 0;
//                    memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//                    continue; // 跳出当前次循环，重新接收
//                }
//                
//                // 2. 核心：判断是否完整接收了“一整帧”
//                // 一整帧的长度 = 帧头(2) + 地址(1) + 功能(1) + 长度(1) + 数据段(dataLen) + CRC(2) = 5 + dataLen + 2
//                if (usart_rx_index >= (5 + dataLen + 2)) {
//                    
//                    uint8_t addr = USART1_RX_BUF[2];
//                    uint8_t func = USART1_RX_BUF[3];
//                    
//                    // 3. CRC校验（只校验到数据段结束，不含 CRC 本身）
//                    uint16_t receivedCRC = USART1_RX_BUF[5 + dataLen] | (USART1_RX_BUF[6 + dataLen] << 8);
//                    uint16_t calcCRC = CRC16_Modbus((const uint8_t*)USART1_RX_BUF, 5 + dataLen);
//                    
//                    if (receivedCRC == calcCRC && addr == 0x01) {
//                        OLED_ShowString(1, 1, "cmd OK  ");
//                        
//                        // 开始检测
//                        if (func == 0x01) {
//                            g_lightMonitorEnable = 1;
//                            OLED_ShowString(2, 1, "RUNNING ");
//                        }
//                        else if (func == 0x02) {  // 关闭检测
//                            g_lightMonitorEnable = 0;
//                            LED2_OFF();
//                            LED3_OFF();
//                            Buzzer_OFF();
//                            OLED_ShowString(2, 1, "CLOSED  ");
//                        }
//                        else if (func == 0x03) {  // 查询状态
//                            uint8_t sensor = LightSensor_GetValue();
//                            uint8_t data[2] = { g_lightMonitorEnable, sensor };
//                            Serial_SendFrame(0x01, 0x81, data, 2);
//                        }
//                    } else {
//                        OLED_ShowString(1, 1, "CRC Err ");
//                    }
//                    
//                    // 完整处理完一帧后，清空缓冲区准备下一帧
//                    usart_rx_index = 0;
//                    memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//                }
//                // 注意：如果 usart_rx_index < (5+dataLen+2)，说明这一帧还没接收完，什么都不做，继续等下一字节。
//            } 
//            else {
//                // 如果开头的两个字节不是 AA 55，说明接收错位了，立刻清空 buffer 止损
//                OLED_ShowString(1, 1, "Head Err");
//                usart_rx_index = 0;
//                memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
//            }
//        }
//        // ================= 【改动核心部分结束】 =================


//        // --- 以下周期性发送状态帧的逻辑保持原样 ---
//        if(g_lightMonitorEnable == 1){
//            static uint32_t sendCount = 0;
//            sendCount++;
//            if(sendCount % 50 == 0){    // 大约每500ms发一次
//                uint8_t sensor = LightSensor_GetValue();
//                uint8_t data[2];
//                data[0] = g_lightMonitorEnable;   // 使能标志
//                data[1] = sensor;                 // 光敏值
//                
//                // 发送状态应答帧：功能码0x81
//                Serial_SendFrame(0x01, 0x81, data, 2);
//                
//                if (sensor > 50) {
//                    LED2_ON();
//                    LED3_OFF();
//                    Buzzer_ON(); 
//                    OLED_ShowString(3, 1, "WARNING!  ");
//                }
//                else {
//                    LED2_OFF();
//                    LED3_ON();
//                    Buzzer_OFF();
//                    OLED_ShowString(3, 1, "NORMAL    ");
//                }
//            }
//        }
//        
//        Delay_ms(20);
//    }
//}

// ====================== 【最终完整修复版】modbus串口协议版 ======================
void LED_BUZZER_OLED_LightSensor(void)
{
    LED_Init();
    Serial_Init();
    OLED_Init();
    Buzzer_Init();
    LightSensor_init();

    memset((uint8_t*)USART1_RX_BUF, 0, USART1_RX_BUF_LEN);
    usart_rx_index = 0;

    OLED_ShowString(1, 1, "Light-Control...");

    while (1)
    {
        // ===================== 1. 解析串口缓冲区 =====================
        while (usart_rx_index >= 7)
        {
            int start = -1;

            // 1）找帧头 AA 55
            for (int i = 0; i < usart_rx_index - 1; i++)
            {
                if (USART1_RX_BUF[i] == 0xAA && USART1_RX_BUF[i + 1] == 0x55)
                {
                    start = i;
                    break;
                }
            }

            // 没找到帧头，全部清掉
            if (start == -1)
            {
                usart_rx_index = 0;
                break;
            }

            // 2）丢掉帧头前的垃圾数据
            if (start > 0)
            {
                for (int i = 0; i < usart_rx_index - start; i++)
                {
                    USART1_RX_BUF[i] = USART1_RX_BUF[i + start];
                }
                usart_rx_index -= start;
            }

            // 至少要能读到最小帧
            if (usart_rx_index < 7) break;

            uint8_t len = USART1_RX_BUF[4];
            int frameLen = 5 + len + 2;

            if (len > 32)
            {
                usart_rx_index = 0;
                OLED_ShowString(1,1,"LEN ERR");
                break;
            }

            // 数据没收完整
            if (usart_rx_index < frameLen) break;

            // ===================== 2. CRC校验 =====================
            uint16_t recv_crc =
                USART1_RX_BUF[5 + len] |
                (USART1_RX_BUF[6 + len] << 8);

            uint16_t calc_crc =
                CRC16_Modbus((uint8_t*)USART1_RX_BUF, 5 + len);

            if (recv_crc == calc_crc)
            {
                uint8_t addr = USART1_RX_BUF[2];
                uint8_t func = USART1_RX_BUF[3];

                if (addr == 0x01)
                {
                    OLED_ShowString(1,1,"CMD OK ");

                    // ===================== 3. 功能处理 =====================
                    if (func == 0x01)
                    {
                        g_lightMonitorEnable = 1;
                        OLED_ShowString(2,1,"RUNNING");
                    }
                    else if (func == 0x02)
                    {
                        g_lightMonitorEnable = 0;
                        LED2_OFF();
                        LED3_OFF();
                        Buzzer_OFF();
                        OLED_ShowString(2,1,"CLOSED ");
                    }
                    else if (func == 0x03)
                    {
                        uint8_t sensor = LightSensor_GetValue();
                        uint8_t data[2] = { g_lightMonitorEnable, sensor };
                        Serial_SendFrame(0x01, 0x81, data, 2);
                    }
                }
            }
            else
            {
                OLED_ShowString(1,1,"CRC ERR");
            }

            // ===================== 4. 移除已处理帧 =====================
            for (int i = 0; i < usart_rx_index - frameLen; i++)
            {
                USART1_RX_BUF[i] = USART1_RX_BUF[i + frameLen];
            }

            usart_rx_index -= frameLen;
        }

        // ===================== 5. 周期发送状态 =====================
        if (g_lightMonitorEnable == 1)
        {
            static uint32_t t = 0;
            t++;

            if (t % 50 == 0)   // ~1s
            {
                uint8_t sensor = LightSensor_GetValue();
                uint8_t data[2] = { g_lightMonitorEnable, sensor };

                Serial_SendFrame(0x01, 0x81, data, 2);

                if (sensor < 50)
                {
                    LED2_ON();
                    LED3_OFF();
                    //Buzzer_ON();
                    OLED_ShowString(3,1,"WARN ");
                }
                else
                {
                    LED2_OFF();
                    LED3_ON();
                    //Buzzer_OFF();
                    OLED_ShowString(3,1,"OK   ");
                }
            }
        }

        Delay_ms(10);
    }
}
