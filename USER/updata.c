/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： updata.c
* 文件标识：
* 内容摘要： updata功能相关函数定义
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
#include "updata.h"
#include "Common.h"
#include "Flash.h"
#include "usart.h"


/**************************   非常重要的  *********************/
xdata  uint8_t  g_BOOT_RUN[3];	   //boot程序跳转字节 不允许动
/**************************       end     *********************/

xdata  uint8_t  g_OTA_Process = 0; //流程控制
xdata  uint8_t  g_COPY_Process = 0; //拷贝数据USER2 ->USER1 流程控制

/**************************************************************************
* 函数名称: Get_ver
* 功能描述: 升级代码命令，返回YES需要升级，其他不需要，也可以修改添加其他功能
* 输入参数: 无
* 输出参数: 1：需要升级   0：不需要升级
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
uint8_t Get_ver(void)
{
    if(SendCommand(Get_OTA, OTA_RES, 10000)) 		 //10s超时时间
        return 1;
    else
        return 0;
}

/**************************************************************************
* 函数名称: Save_Boot_ADD
* 功能描述: 存储BootLoader程序的跳转字节 前三个字节
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static void Save_Boot_ADD(void)
{
    g_BOOT_RUN[0] = FLASH_ByteRead(0);			//读取BOOT的0X0000地址的3Byte字节
    g_BOOT_RUN[1] = FLASH_ByteRead(1);
    g_BOOT_RUN[2] = FLASH_ByteRead(2);

    FLASH_PageErase(AAPP_RUN_ADD);           	//擦除AAPP_RUN_ADD扇区

    FLASH_ByteWrite(AAPP_RUN_ADD, uartStat.rxbuf[0]); 		//写APP跳转地址
    FLASH_ByteWrite(AAPP_RUN_ADD + 1, uartStat.rxbuf[1]);
    FLASH_ByteWrite(AAPP_RUN_ADD + 2, uartStat.rxbuf[2]);

    uartStat.rxbuf[0] = g_BOOT_RUN[0];  //替换boot的启动地址
    uartStat.rxbuf[1] = g_BOOT_RUN[1];
    uartStat.rxbuf[2] = g_BOOT_RUN[2];
}

/**************************************************************************
* 函数名称: Erase_FlashPage
* 功能描述: 选择擦除USER1 / USER2，擦除一页是512Byte
* 输入参数: _fdisk：选择扇区
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
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
* 函数名称: Program_FlashPage
* 功能描述: 写flash,写一页512Byte
* 输入参数: page：页选择从0开始，length：写入数据长度
* 输出参数: 返回0成功 返回1越界
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
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
    if(pageStop > APP_USER2_STOP) { //越界
        return 1;
    } else {
        for(pwrite = pageStart; pwrite < pageStop; pwrite ++)
            FLASH_ByteWrite(pwrite, uartStat.rxbuf[pwrite - pageStart]); //写数据到flash
    }
    return 0;
}

/**************************************************************************
* 函数名称: Start_OTA
* 功能描述: 开始升级功能
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void Start_OTA(void)
{
    xdata  uint32_t i, Copylen = 0;		//copy数据长度
    xdata  uint16_t len = 0;		 	//接收数据长度
    xdata  uint16_t Updata_Num = 0; 	//数据包计数
    xdata  uint8_t  RemBuf[17];   		//请求数据包命令封装数组

    while(1) {
        switch(g_OTA_Process) {
        case FLASH_ERASE_STATUS: {  	//擦除USER2区
            Erase_FlashPage(USER2);     //擦除USER2区 暂存区
            g_OTA_Process = FLASH_UPDATA_START;
            break;
        }
        case FLASH_UPDATA_START: { //开始接收数据
            //"Updata1\r\n" 表示请求第几次数据包
            sprintf(RemBuf, "Updata%d\r\n", Updata_Num); //数据包数量
            len = UpdataCommand(RemBuf, 10000); 	//通知主机发送代码 接收第一帧数据
            if(Get_RX_Status()) { //接收到了一帧数据
                if(CheckCRC16()) { //检测数据是否正确
                    if(len == 514) { //512B数据+2crc16
                        //写入数据到FLASH
                        if(Updata_Num == 0) {
                            Save_Boot_ADD();  //保存APP程序跳转功能的前三个字节
                        }
                        Program_FlashPage(Updata_Num, len - 2); //长度去掉CRC， 写数据到flash 1page
                        Updata_Num++;

                    } else { //判断最后一帧数据，检测是否是正确的，正确写入Flash
                        //写入数据到FLASH
                        Program_FlashPage(Updata_Num, len - 2); //长度去掉CRC， 写数据到flash 1page
                        Updata_Num++;
                        Copylen = (Updata_Num * 512) + len - 2;
                        g_OTA_Process = FLASH_UPDATA_STOP; //数据接收完成
                    }
                }
            }
            break;
        }
        case FLASH_UPDATA_STOP: {  //缓存数据接收完成 准备把数据从USER2拷贝到USER1，拷贝以后不擦除USER2，除非紧接着来了第二次升级
            //g_OTA_Process = ;
            switch(g_COPY_Process) {
            case FLASH_ERASE_COPY: {  //擦除USER1区代码，并且保存前三个字节的跳转字节
                Erase_FlashPage(USER1);  //擦除USER1 区
                g_COPY_Process = FLASH_COPY_START;  //跳转到数据拷贝
                break;
            }
            case FLASH_COPY_START: {
                for(i = APP_USER1_START; i < Copylen; i++) {
                    FLASH_ByteWrite(i, FLASH_ByteRead(APP_USER2_START + i)); //数据拷贝
                }
                g_COPY_Process = FLASH_COPY_STOP;
                break;
            }
            case FLASH_COPY_STOP: { 
                return;//拷贝完成 退出
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











