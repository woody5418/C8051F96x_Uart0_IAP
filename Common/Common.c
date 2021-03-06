/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： Common.c
* 文件标识：
* 内容摘要： Common操作相关函数定义
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
#include "Common.h"



/**************************************************************************
* 函数名称: PCA_Init
* 功能描述: PCA初始化函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void PCA_Init(void)
{
    uint8_t SFRSAVE;

    SFRSAVE = SFRPAGE;

    SFRPAGE   = LEGACY_PAGE;
    PCA0MD    &= ~0x40; //停止看门狗
    SFRPAGE = SFRSAVE;
}

/**************************************************************************
* 函数名称: PORT_Init
* 功能描述: IO初始化函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void PORT_Init (void)
{
    SFRPAGE = LEGACY_PAGE;

    P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
    XBR0    = 0x01;                     // Enable UART on P0.4(TX) and P0.5(RX)
    XBR2    = 0x40;                     // Enable crossbar and weak pull-ups
}

/**************************************************************************
* 函数名称: SYSCLK_Init
* 功能描述: 系统时钟初始化函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void SYSCLK_Init (void)
{
    SFRPAGE = CONFIG_PAGE;
    FLSCL     = 0x40;                   // Set BYPASS bit for >12.5 MHz.

    SFRPAGE = LEGACY_PAGE;
    REG0CN |= 0x10;                     // Enable the precision osc. bias
    OSCICN |= 0x80;                     // Enable the precision internal osc.

    RSTSRC = 0x06;                      // Enable missing clock detector and
    // leave VDD Monitor enabled.

    CLKSEL = 0x00;                      // Select precision internal osc.
    // divided by 1 as the system clock

    switch(DIVCLK) {
    //精密内部晶振
    case 1:    {
        CLKSEL |= 0x00;
        break;
    }
    case 2:    {
        CLKSEL |= 0x10;
        break;
    }
    case 4:    {
        CLKSEL |= 0x20;
        break;
    }
    case 8:    {
        CLKSEL |= 0x30;
        break;
    }
    case 16:   {
        CLKSEL |= 0x40;
        break;
    }
    case 32:   {
        CLKSEL |= 0x50;
        break;
    }
    case 64:   {
        CLKSEL |= 0x60;
        break;
    }
    case 128:  {
        CLKSEL |= 0x70;
        break;
    }
    default:
        break;
    }

    while(!(CLKSEL & 0x80));
}

/**************************************************************************
* 函数名称: delay_ms
* 功能描述: ms级别延时函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
*************************************************************************/
/*
void delay_ms(uint32_t delay)
{
    uint32_t i;
    while(delay--) {
        for(i = 0; i < 200; i++) {}
    }
}
*/
/**************************************************************************
* 函数名称: delay_us
* 功能描述: 微秒级别延时 非标准
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void delay_us(uint16_t delay)
{
    while(delay--) {
        NOP();
        NOP();
    }
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------


