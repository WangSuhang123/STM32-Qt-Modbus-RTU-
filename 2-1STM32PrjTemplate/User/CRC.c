#include "stm32f10x.h"                  // Device header
#include <string.h>


// CRC16-Modbus (0xA001 多项式，低字节在前)
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
