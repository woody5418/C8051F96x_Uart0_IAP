/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： updata.h
* 文件标识：
* 内容摘要： updata相关函数声明
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
#ifndef  __UPDATA_H_
#define  __UPDATA_H_
#include "includes.h"


/*
Flash 区域划分
	Bootloader:存储在 0xE000 - 0xF9FF 需要6K  在Flash->Config Flash Tool->BL51 Locate- Code Range 修改
	User1     :存储在 0x0000 - 0x6FFF 30k存储用户代码
	User2     :存储在 0x7000 - 0xDFFF 30k存储升级的代码 
	*/
#define APP_USER1_START 0x0000    // APP区USER1的起始地址  暂时定为28k
#define APP_USER1_STOP  0x6FFF    // APP区USER1的结束地址

#define APP_USER2_START 0x7000    // APP区USER2的起始地址	暂时定为28k
#define APP_USER2_STOP  0xDFFF    // APP区USER2的结束地址

#define BOOT_ADDR  		0xE000    // Boot程序存储地址      暂定为6K
#define BOOT_STOP 		0xF9FF    // Boot区结束地址

#define AAPP_RUN_ADD 	0xFA00    // 存储APP的跳转区     	512Byte

#define Get_OTA "Get OTA\r\n"  //获取升级包命令
#define OTA_RES "YES\r\n"  //获取升级包命令

// 分区
typedef enum{
	USER1,
	USER2
}FDISK;

//OTA 状态
enum{
	FLASH_ERASE_STATUS,
	FLASH_UPDATA_START,
	FLASH_UPDATA_STOP
};

//数据转移状态
enum{
	FLASH_ERASE_COPY,
	FLASH_COPY_START,
	FLASH_COPY_STOP
};


uint8_t Get_ver(void);
void Start_OTA(void);



#endif  /*__INCLUDES_H_*/



