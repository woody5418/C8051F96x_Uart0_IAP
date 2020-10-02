/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� updata.h
* �ļ���ʶ��
* ����ժҪ�� updata��غ�������
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
#ifndef  __UPDATA_H_
#define  __UPDATA_H_
#include "includes.h"


/*
Flash ���򻮷�
	Bootloader:�洢�� 0xE000 - 0xF9FF ��Ҫ6K  ��Flash->Config Flash Tool->BL51 Locate- Code Range �޸�
	User1     :�洢�� 0x0000 - 0x6FFF 30k�洢�û�����
	User2     :�洢�� 0x7000 - 0xDFFF 30k�洢�����Ĵ��� 
	*/
#define APP_USER1_START 0x0000    // APP��USER1����ʼ��ַ  ��ʱ��Ϊ28k
#define APP_USER1_STOP  0x6FFF    // APP��USER1�Ľ�����ַ

#define APP_USER2_START 0x7000    // APP��USER2����ʼ��ַ	��ʱ��Ϊ28k
#define APP_USER2_STOP  0xDFFF    // APP��USER2�Ľ�����ַ

#define BOOT_ADDR  		0xE000    // Boot����洢��ַ      �ݶ�Ϊ6K
#define BOOT_STOP 		0xF9FF    // Boot��������ַ

#define AAPP_RUN_ADD 	0xFA00    // �洢APP����ת��     	512Byte

#define Get_OTA "Get OTA\r\n"  //��ȡ����������
#define OTA_RES "YES\r\n"  //��ȡ����������

// ����
typedef enum{
	USER1,
	USER2
}FDISK;

//OTA ״̬
enum{
	FLASH_ERASE_STATUS,
	FLASH_UPDATA_START,
	FLASH_UPDATA_STOP
};

//����ת��״̬
enum{
	FLASH_ERASE_COPY,
	FLASH_COPY_START,
	FLASH_COPY_STOP
};


uint8_t Get_ver(void);
void Start_OTA(void);



#endif  /*__INCLUDES_H_*/



