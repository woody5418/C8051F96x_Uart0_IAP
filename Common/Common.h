/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� Common.h
* �ļ���ʶ��
* ����ժҪ�� Common��غ�������
* ����˵����
* ��ǰ�汾��
* ��    �ߣ� woody
* ������ڣ� 2020.09.30
*
* �޸ļ�¼1��
*    �޸����ڣ�
*    �� �� �ţ�
*    �� �� �ˣ�
*    �޸����ݣ�
* �޸ļ�¼2����
************************************************************************/
#ifndef  __COMMON_H_
#define  __COMMON_H_
#include "includes.h"


void PCA_Init(void);
void PORT_Init (void);
void SYSCLK_Init (void);

//ms������ʱ����
//void delay_ms(uint32_t delay);
void delay_us(uint16_t delay);

#endif  /*__COMMON_H_*/



