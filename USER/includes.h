/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� includes.h
* �ļ���ʶ��
* ����ժҪ�� includes��غ�������
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

#ifndef  __INCLUDES_H_
#define  __INCLUDES_H_

#include "compiler_defs.h"
#include "C8051f960_defs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef TRUE 
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

typedef enum{  
    false = 0,  
    true  = 1,  
}bool;

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned long      int uint64_t;

typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;


#define FREQUNCY 24500000
#define DIVCLK   8
#define SYSCLK   FREQUNCY/DIVCLK

extern xdata  uint8_t  g_OTA_Process;  //���̿���


#define Rst_CPU RSTSRC |= 0x30 			//�����λ

#endif  /*__INCLUDES_H_*/



