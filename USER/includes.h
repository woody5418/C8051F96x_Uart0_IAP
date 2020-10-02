/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： includes.h
* 文件标识：
* 内容摘要： includes相关函数声明
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

extern xdata  uint8_t  g_OTA_Process;  //流程控制


#define Rst_CPU RSTSRC |= 0x30 			//软件复位

#endif  /*__INCLUDES_H_*/



