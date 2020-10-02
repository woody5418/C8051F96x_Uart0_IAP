/************************************************************************
* Copyright (C) Copyright 2014-2015,Nercita,Beijing,China
*
* 文件名称： main.c
* 文件标识：
* 内容摘要： C8051f96x串口升级功能函数定义
* 其它说明： https://github.com/woody5418/STM32L151_FREERTOS_DEMO
* 当前版本： V1.0
* 作    者： woody   QQ：2490006131
* 完成日期： 2020.09.30
*	< STM32L151ZET6 >
			FLASH SIZE	:512Kbytes
			RAM SIZE	:80Kbytes
			EEPROM  	:16K
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
* 修改记录2：…
************************************************************************/
/*
参考资料：
	http://www.pudn.com/Download/item/id/1437854.html
	https://wenku.baidu.com/view/b4fd8a5abe23482fb4da4c20.html
	https://wenku.baidu.com/view/6a11e20c76c66137ee0619e0.html
	https://wenku.baidu.com/view/4e14f06aaf1ffc4ffe47ac2b.html

	code range ：0xE000-0X0FBFF  参考C8051F964手册125页

	C8051F964
	FLASH SIZE:			64KB
	LOCK Byte:			0xFFFF
	LOCK Byte Page:		0xFC00~0xFFFE
	FLASH Memory Space:	0x0000~0xFBFF

	Flash 区域划分 宏定义存放在"updata.h"
	Bootloader:存储在 0xE000 - 0xF9FF 需要6K   在Flash->Config Flash Tool->BL51 Locate- Code Range 修改
	User1     :存储在 0x0000 - 0x6FFF 28k存储用户代码
	User2     :存储在 0x7000 - 0xDFFF 28k存储升级的代码 

	hex 转bin文件查看GSM OTA\bin工具里面的readme.txt说明

	升级功能开始以后先把代码存储到user2 然后再存储到user1
*/
#include "usart.h"
#include "Common.h"
#include "Flash.h"
#include "updata.h"


/**************************************************************************
* 函数名称: main
* 功能描述: 主函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void main (void)
{
    void (*Application)( void);  	//跳转程序使用
    PCA_Init();					 	//关闭开门狗
    PORT_Init();                 	// 初始化I/O
    SYSCLK_Init ();              	// 初始化时钟
    UART0_Init();                	// 初始化串口0
    while (1) {
        if(Get_ver()) {				//判断是否要开始版本升级
            Start_OTA(); 			//升级函数
            Application = AAPP_RUN_ADD;		//升级成功以后跳转到APP
            (*Application)();
        } else { 							// 直接跳转到APP
            Application = AAPP_RUN_ADD;
            (*Application)();
        }
    }
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------





