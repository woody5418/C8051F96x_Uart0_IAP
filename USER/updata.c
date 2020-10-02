/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� updata.c
* �ļ���ʶ��
* ����ժҪ�� updata������غ�������
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
#include "updata.h"
#include "Common.h"
#include "Flash.h"
#include "usart.h"


/**************************   �ǳ���Ҫ��  *********************/
xdata  uint8_t  g_BOOT_RUN[3];	   //boot������ת�ֽ� ������
/**************************       end     *********************/

xdata  uint8_t  g_OTA_Process = 0; //���̿���
xdata  uint8_t  g_COPY_Process = 0; //��������USER2 ->USER1 ���̿���

/**************************************************************************
* ��������: Get_ver
* ��������: ���������������YES��Ҫ��������������Ҫ��Ҳ�����޸������������
* �������: ��
* �������: 1����Ҫ����   0������Ҫ����
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
uint8_t Get_ver(void)
{
    if(SendCommand(Get_OTA, OTA_RES, 10000)) 		 //10s��ʱʱ��
        return 1;
    else
        return 0;
}

/**************************************************************************
* ��������: Save_Boot_ADD
* ��������: �洢BootLoader�������ת�ֽ� ǰ�����ֽ�
* �������: ��
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
static void Save_Boot_ADD(void)
{
    g_BOOT_RUN[0] = FLASH_ByteRead(0);			//��ȡBOOT��0X0000��ַ��3Byte�ֽ�
    g_BOOT_RUN[1] = FLASH_ByteRead(1);
    g_BOOT_RUN[2] = FLASH_ByteRead(2);

    FLASH_PageErase(AAPP_RUN_ADD);           	//����AAPP_RUN_ADD����

    FLASH_ByteWrite(AAPP_RUN_ADD, uartStat.rxbuf[0]); 		//дAPP��ת��ַ
    FLASH_ByteWrite(AAPP_RUN_ADD + 1, uartStat.rxbuf[1]);
    FLASH_ByteWrite(AAPP_RUN_ADD + 2, uartStat.rxbuf[2]);

    uartStat.rxbuf[0] = g_BOOT_RUN[0];  //�滻boot��������ַ
    uartStat.rxbuf[1] = g_BOOT_RUN[1];
    uartStat.rxbuf[2] = g_BOOT_RUN[2];
}

/**************************************************************************
* ��������: Erase_FlashPage
* ��������: ѡ�����USER1 / USER2������һҳ��512Byte
* �������: _fdisk��ѡ������
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
static void Erase_FlashPage(FDISK _fdisk)
{
    uint32_t xdata pwrite;

    switch(_fdisk) {
    case USER1:
        for(pwrite = APP_USER1_START; pwrite < APP_USER1_STOP; pwrite += 0x200)
            FLASH_PageErase(pwrite);
        break;
    case USER2:
        for(pwrite = APP_USER2_START; pwrite < APP_USER2_STOP; pwrite += 0x200)
            FLASH_PageErase(pwrite);
        break;
    }
}

/**************************************************************************
* ��������: Program_FlashPage
* ��������: дflash,дһҳ512Byte
* �������: page��ҳѡ���0��ʼ��length��д�����ݳ���
* �������: ����0�ɹ� ����1Խ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
static uint8_t Program_FlashPage(uint8_t page, uint16_t length)
{
    uint32_t xdata pwrite;
    uint32_t xdata pageStart;
    uint32_t xdata pageStop;

    pageStart = page * 512 + APP_USER2_START;
    if(length < 512)
        pageStop = pageStart + length;
    else
        pageStop = pageStart + 512;
    if(pageStop > APP_USER2_STOP) { //Խ��
        return 1;
    } else {
        for(pwrite = pageStart; pwrite < pageStop; pwrite ++)
            FLASH_ByteWrite(pwrite, uartStat.rxbuf[pwrite - pageStart]); //д���ݵ�flash
    }
    return 0;
}

/**************************************************************************
* ��������: Start_OTA
* ��������: ��ʼ��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
* -----------------------------------------------
* 2020/09/30       V1.0      woody         ����
**************************************************************************/
void Start_OTA(void)
{
    xdata  uint32_t i, Copylen = 0;		//copy���ݳ���
    xdata  uint16_t len = 0;		 	//�������ݳ���
    xdata  uint16_t Updata_Num = 0; 	//���ݰ�����
    xdata  uint8_t  RemBuf[17];   		//�������ݰ������װ����

    while(1) {
        switch(g_OTA_Process) {
        case FLASH_ERASE_STATUS: {  	//����USER2��
            Erase_FlashPage(USER2);     //����USER2�� �ݴ���
            g_OTA_Process = FLASH_UPDATA_START;
            break;
        }
        case FLASH_UPDATA_START: { //��ʼ��������
            //"Updata1\r\n" ��ʾ����ڼ������ݰ�
            sprintf(RemBuf, "Updata%d\r\n", Updata_Num); //���ݰ�����
            len = UpdataCommand(RemBuf, 10000); 	//֪ͨ�������ʹ��� ���յ�һ֡����
            if(Get_RX_Status()) { //���յ���һ֡����
                if(CheckCRC16()) { //��������Ƿ���ȷ
                    if(len == 514) { //512B����+2crc16
                        //д�����ݵ�FLASH
                        if(Updata_Num == 0) {
                            Save_Boot_ADD();  //����APP������ת���ܵ�ǰ�����ֽ�
                        }
                        Program_FlashPage(Updata_Num, len - 2); //����ȥ��CRC�� д���ݵ�flash 1page
                        Updata_Num++;

                    } else { //�ж����һ֡���ݣ�����Ƿ�����ȷ�ģ���ȷд��Flash
                        //д�����ݵ�FLASH
                        Program_FlashPage(Updata_Num, len - 2); //����ȥ��CRC�� д���ݵ�flash 1page
                        Updata_Num++;
                        Copylen = (Updata_Num * 512) + len - 2;
                        g_OTA_Process = FLASH_UPDATA_STOP; //���ݽ������
                    }
                }
            }
            break;
        }
        case FLASH_UPDATA_STOP: {  //�������ݽ������ ׼�������ݴ�USER2������USER1�������Ժ󲻲���USER2�����ǽ��������˵ڶ�������
            //g_OTA_Process = ;
            switch(g_COPY_Process) {
            case FLASH_ERASE_COPY: {  //����USER1�����룬���ұ���ǰ�����ֽڵ���ת�ֽ�
                Erase_FlashPage(USER1);  //����USER1 ��
                g_COPY_Process = FLASH_COPY_START;  //��ת�����ݿ���
                break;
            }
            case FLASH_COPY_START: {
                for(i = APP_USER1_START; i < Copylen; i++) {
                    FLASH_ByteWrite(i, FLASH_ByteRead(APP_USER2_START + i)); //���ݿ���
                }
                g_COPY_Process = FLASH_COPY_STOP;
                break;
            }
            case FLASH_COPY_STOP: { 
                return;//������� �˳�
            }
            }
            break;
        }
        }
    }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------











