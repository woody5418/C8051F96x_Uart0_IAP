/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： Common.h
* 文件标识：
* 内容摘要： Common相关函数声明
* 其它说明：
* 当前版本：
* 作    者： woody
* 完成日期： 2020.09.30
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
* 修改记录2：…
************************************************************************/
#ifndef  __COMMON_H_
#define  __COMMON_H_
#include "includes.h"


void PCA_Init(void);
void PORT_Init (void);
void SYSCLK_Init (void);

//ms级别延时函数
//void delay_ms(uint32_t delay);
void delay_us(uint16_t delay);

#endif  /*__COMMON_H_*/



