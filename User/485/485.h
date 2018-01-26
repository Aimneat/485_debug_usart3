#ifndef __485app_H
#define	__485app_H

#include "stm32f4xx.h"
#include <stdbool.h>

#define MingLingChangDu 2    //���巢�����Ķ���������ݳ���
//char FanHuiShuZhiMingLing[]={0xF0,0x01};
//char FanHuiZiFuMingLing[]={0xF0,0x02};

void FanHuiShuZhi(void);       //��ѹ��ֱֵ���ö�����������
void FanHuiZiFu(void);        //��ѹ��ֵ��תΪ�ַ��ٽ����ݷ���
void MingLingChuLi(uint8_t *array,uint16_t num);    //�����
bool shuzuxiangdeng(uint8_t *array,uint8_t *mingling);
void send_float(float x);
void send_bytes(unsigned char *start,int len);


void show(char *str);
void show_pressure(char *str);
#endif /* __485_H */
