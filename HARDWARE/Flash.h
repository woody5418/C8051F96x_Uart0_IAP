/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� Flash.h
* �ļ���ʶ��
* ����ժҪ�� Flash��غ�������
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
#ifndef  __FLASH_H_
#define  __FLASH_H_
#include "includes.h"



void FLASH_ByteWrite (uint32_t addr, char byte);
uint8_t FLASH_ByteRead (uint32_t addr);
void FLASH_PageErase (uint32_t addr);
//void Test_Program_Flash(void);


#endif  /*__FLASH_H_*/


