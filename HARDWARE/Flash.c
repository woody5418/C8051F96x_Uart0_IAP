/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� Flash.c
* �ļ���ʶ��
* ����ժҪ�� Flash������غ�������
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
#include "Flash.h"
#include "usart.h"
#include "Common.h"


/**************************************************************************
* ��������: FLASH_PageErase
* ��������: Flash����������C8051F96xĬ�ϲ���һҳ512Byte
* �������: addr��������ַ ��0��ʼÿ����Ҫ+200��512Byte��
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
void FLASH_PageErase(uint32_t addr)
{
    bit EA_SAVE = EA; 			// �����жϣ���ֹ�������жϵ���
    uint8_t xdata *data pwrite;

    EA = 0;  		 			//�ر��ж�

    VDM0CN = 0x80;
    RSTSRC = 0X06;

    pwrite = (char xdata *) addr;

    PSCTL |= 0x03;   			// PSWE = 1; PSEE = 1;  ������FLASHҳд����������

//	PSBANK = 0X00;   			//��C8051F964 / 5/6/7/8/9�豸�ϲ�Ӧ��COBANK [1��0]��IFBANK [1��0]����Ϊ��10b����11b��

    FLKEY  = 0xA5;   			// ͨ����FLKEY�Ĵ���д��0xA5��0xF1��������������д�Ͳ���
    FLKEY  = 0xF1;   			// ��һ��д��������ɺ󣬽��Զ���������д��Ͳ�����

    VDM0CN = 0x80;				//����VDD������
    RSTSRC = 0X02;

    *pwrite = 0;     			//�������ַд��һ�������ֽ�

    PSCTL = 0;                  //���PSWEλ��PSEEλ

    EA = EA_SAVE;               // Restore interrupts
}

/**************************************************************************
* ��������: FLASH_ByteWrite
* ��������: дһ���ֽڵ�flash
* �������: addr��д���ַ��byte��д������
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
void FLASH_ByteWrite (uint32_t addr, uint8_t byte)
{
    bit EA_SAVE = EA;                   // �����жϣ���ֹ�������жϵ���
    uint8_t xdata * data pwrite;        // FLASH дָ��

    EA = 0;                             // ��ֹ�ж�

    VDM0CN = 0x80;						//����VDD������
    RSTSRC = 0X06;

    pwrite = (char xdata *) addr;

    PSCTL |= 0x01;                      // PSWE=1 д���������

    //PSBANK = 0X00;

    FLKEY  = 0xA5;
    FLKEY  = 0xF1;

    VDM0CN = 0x80;						//����VDD������
    RSTSRC = 0X02;

    *pwrite = byte;                     // Write the byte

    PSCTL = 0;                      	//���PSWEλ

    EA = EA_SAVE;                       // Restore interrupts
}

/**************************************************************************
* ��������: FLASH_ByteRead
* ��������: ��flash��һ���ֽ�
* �������: addr����ȡ��ַ
* �������: ���ض�ȡ����8λ����
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
uint8_t FLASH_ByteRead (uint32_t addr)
{
    bit EA_SAVE = EA;
    char code * data pread;
    uint8_t byte;

    EA = 0;

    pread = (char code *) addr;

    byte = *pread;

    EA = EA_SAVE;    // Restore interrupts

    return byte;
}

/********************************* Start *********************************
//����Flash��д����
#define Test_ADDR  0x0000

xdata uint8_t getflash=0;
xdata uint8_t writedata1=0;

void Test_Program_Flash(void)
{
    printf ("\r\n");
    FLASH_PageErase(Test_ADDR);
    getflash = FLASH_ByteRead(Test_ADDR);
    printf ("getflash: 0x%bx , 0x%bx\r\n", getflash, writedata1);
    FLASH_ByteWrite(Test_ADDR, writedata1);
    getflash = FLASH_ByteRead(Test_ADDR+1);
    printf ("getflash: 0x%bx , 0x%bx\r\n", getflash, writedata1);
}

********************************* Stop *********************************/

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------







