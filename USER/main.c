/************************************************************************
* Copyright (C) Copyright 2014-2015,Nercita,Beijing,China
*
* �ļ����ƣ� main.c
* �ļ���ʶ��
* ����ժҪ�� C8051f96x�����������ܺ�������
* ����˵���� https://github.com/woody5418/STM32L151_FREERTOS_DEMO
* ��ǰ�汾�� V1.0
* ��    �ߣ� woody   QQ��2490006131
* ������ڣ� 2020.09.30
*	< STM32L151ZET6 >
			FLASH SIZE	:512Kbytes
			RAM SIZE	:80Kbytes
			EEPROM  	:16K
* �޸ļ�¼1��
*    �޸����ڣ�
*    �� �� �ţ�
*    �� �� �ˣ�
*    �޸����ݣ�
* �޸ļ�¼2����
************************************************************************/
/*
�ο����ϣ�
	http://www.pudn.com/Download/item/id/1437854.html
	https://wenku.baidu.com/view/b4fd8a5abe23482fb4da4c20.html
	https://wenku.baidu.com/view/6a11e20c76c66137ee0619e0.html
	https://wenku.baidu.com/view/4e14f06aaf1ffc4ffe47ac2b.html

	code range ��0xE000-0X0FBFF  �ο�C8051F964�ֲ�125ҳ

	C8051F964
	FLASH SIZE:			64KB
	LOCK Byte:			0xFFFF
	LOCK Byte Page:		0xFC00~0xFFFE
	FLASH Memory Space:	0x0000~0xFBFF

	Flash ���򻮷� �궨������"updata.h"
	Bootloader:�洢�� 0xE000 - 0xF9FF ��Ҫ6K   ��Flash->Config Flash Tool->BL51 Locate- Code Range �޸�
	User1     :�洢�� 0x0000 - 0x6FFF 28k�洢�û�����
	User2     :�洢�� 0x7000 - 0xDFFF 28k�洢�����Ĵ��� 

	hex תbin�ļ��鿴GSM OTA\bin���������readme.txt˵��

	�������ܿ�ʼ�Ժ��ȰѴ���洢��user2 Ȼ���ٴ洢��user1
*/
#include "usart.h"
#include "Common.h"
#include "Flash.h"
#include "updata.h"


/**************************************************************************
* ��������: main
* ��������: ������
* �������: ��
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
void main (void)
{
    void (*Application)( void);  	//��ת����ʹ��
    PCA_Init();					 	//�رտ��Ź�
    PORT_Init();                 	// ��ʼ��I/O
    SYSCLK_Init ();              	// ��ʼ��ʱ��
    UART0_Init();                	// ��ʼ������0
    while (1) {
        if(Get_ver()) {				//�ж��Ƿ�Ҫ��ʼ�汾����
            Start_OTA(); 			//��������
            Application = AAPP_RUN_ADD;		//�����ɹ��Ժ���ת��APP
            (*Application)();
        } else { 							// ֱ����ת��APP
            Application = AAPP_RUN_ADD;
            (*Application)();
        }
    }
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------





