/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： Flash.h
* 文件标识：
* 内容摘要： Flash相关函数声明
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
#ifndef  __FLASH_H_
#define  __FLASH_H_
#include "includes.h"



void FLASH_ByteWrite (uint32_t addr, char byte);
uint8_t FLASH_ByteRead (uint32_t addr);
void FLASH_PageErase (uint32_t addr);
//void Test_Program_Flash(void);


#endif  /*__FLASH_H_*/


