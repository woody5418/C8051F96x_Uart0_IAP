/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： Flash.c
* 文件标识：
* 内容摘要： Flash操作相关函数定义
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
#include "Flash.h"
#include "usart.h"
#include "Common.h"


/**************************************************************************
* 函数名称: FLASH_PageErase
* 功能描述: Flash擦除函数，C8051F96x默认擦除一页512Byte
* 输入参数: addr：擦除地址 从0开始每次需要+200（512Byte）
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void FLASH_PageErase(uint32_t addr)
{
    bit EA_SAVE = EA; 			// 保留中断，防止有其他中断调用
    uint8_t xdata *data pwrite;

    EA = 0;  		 			//关闭中断

    VDM0CN = 0x80;
    RSTSRC = 0X06;

    pwrite = (char xdata *) addr;

    PSCTL |= 0x03;   			// PSWE = 1; PSEE = 1;  以允许FLASH页写、擦除操作

//	PSBANK = 0X00;   			//在C8051F964 / 5/6/7/8/9设备上不应将COBANK [1：0]和IFBANK [1：0]设置为（10b）或（11b）

    FLKEY  = 0xA5;   			// 通过向FLKEY寄存器写入0xA5和0xF1，可以启用闪存写和擦除
    FLKEY  = 0xF1;   			// 下一次写入或擦除完成后，将自动禁用闪存写入和擦除。

    VDM0CN = 0x80;				//允许VDD监视器
    RSTSRC = 0X02;

    *pwrite = 0;     			//向任意地址写入一个数据字节

    PSCTL = 0;                  //清除PSWE位和PSEE位

    EA = EA_SAVE;               // Restore interrupts
}

/**************************************************************************
* 函数名称: FLASH_ByteWrite
* 功能描述: 写一个字节到flash
* 输入参数: addr：写入地址，byte：写入数据
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void FLASH_ByteWrite (uint32_t addr, uint8_t byte)
{
    bit EA_SAVE = EA;                   // 保留中断，防止有其他中断调用
    uint8_t xdata * data pwrite;        // FLASH 写指针

    EA = 0;                             // 禁止中断

    VDM0CN = 0x80;						//允许VDD监视器
    RSTSRC = 0X06;

    pwrite = (char xdata *) addr;

    PSCTL |= 0x01;                      // PSWE=1 写入操作允许

    //PSBANK = 0X00;

    FLKEY  = 0xA5;
    FLKEY  = 0xF1;

    VDM0CN = 0x80;						//允许VDD监视器
    RSTSRC = 0X02;

    *pwrite = byte;                     // Write the byte

    PSCTL = 0;                      	//清除PSWE位

    EA = EA_SAVE;                       // Restore interrupts
}

/**************************************************************************
* 函数名称: FLASH_ByteRead
* 功能描述: 从flash读一个字节
* 输入参数: addr：读取地址
* 输出参数: 返回读取到的8位数据
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
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
//测试Flash读写操作
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







