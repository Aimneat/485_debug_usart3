#ifndef __485app_H
#define	__485app_H

#include "stm32f4xx.h"
#include <stdbool.h>

#define MingLingChangDu 2    //定义发送来的读命令的数据长度
//char FanHuiShuZhiMingLing[]={0xF0,0x01};
//char FanHuiZiFuMingLing[]={0xF0,0x02};

void FanHuiShuZhi(void);       //将压力值直接用二进制数返回
void FanHuiZiFu(void);        //将压力值先转为字符再将数据返回
void MingLingChuLi(uint8_t *array,uint16_t num);    //命令处理
bool shuzuxiangdeng(uint8_t *array,uint8_t *mingling);
void send_float(float x);
void send_bytes(unsigned char *start,int len);


void show(char *str);
void show_pressure(char *str);
#endif /* __485_H */
