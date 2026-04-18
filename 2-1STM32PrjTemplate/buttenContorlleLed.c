//#include "stm32f10x.h"
//#include "Delay.h"

//// 按键状态枚举
//typedef enum {
//    KEY_RELEASED = 0,
//    KEY_PRESSED = 1
//} KeyState;

//// 按键扫描函数（带消抖）
//KeyState Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
//    static KeyState keyState = KEY_RELEASED;  // 静态变量保存按键状态
//    KeyState currentState;  // 修正为枚举类型
//    
//    // 读取当前电平（上拉输入，按下时为低电平）
//    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0){
//        Delay_ms(10);  // 消抖延时
//        if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0){
//            currentState = KEY_PRESSED;
//        } else {
//            currentState = keyState;  // 保持原状态
//        }
//    } else {
//        currentState = KEY_RELEASED;
//    }
//    
//    // 仅在状态变化时更新并返回
//    if(currentState != keyState){
//        keyState = currentState;
//        return currentState;
//    } else {
//        return KEY_RELEASED;
//    }
//}
