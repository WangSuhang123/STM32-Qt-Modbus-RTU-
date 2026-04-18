#ifndef __LightSensor_H
#define __LightSensor_H

void LightSensor_init(void);
//uint8_t LightSensor_Get(void);

uint8_t LightSensor_GetValue(void);  // 返回 0~100 光照强度


#endif
