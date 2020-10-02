/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： usart.c
* 文件标识：
* 内容摘要： usart操作相关函数定义
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
#include "usart.h"
#include "Common.h"


//crc16校验使用
uint8_t code auchCRCHi[256] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};
//crc16校验使用
uint8_t code auchCRCLo[256] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};


xdata UART_STATUS uartStat;   //串口对象

/**************************************************************************
* 函数名称: UART0_Init
* 功能描述: 串口初始化函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
void UART0_Init(void)
{
    SFRPAGE   = LEGACY_PAGE;

    SCON0 = 0x10;	//8位可变波特率 接收允许

    //波特率自动调整
    if (SYSCLK / BAUDRATE / 2 / 256 < 1) {
        TH1 = -(SYSCLK / BAUDRATE / 2);
        CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
        CKCON |=  0x08;
    } else if (SYSCLK / BAUDRATE / 2 / 256 < 4) {
        TH1 = -(SYSCLK / BAUDRATE / 2 / 4);
        CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01
        CKCON |=  0x01;
    } else if (SYSCLK / BAUDRATE / 2 / 256 < 12) {
        TH1 = -(SYSCLK / BAUDRATE / 2 / 12);
        CKCON &= ~0x0B;
    }               // T1M = 0; SCA1:0 = 00
    else {
        TH1 = -(SYSCLK / BAUDRATE / 2 / 48);
        CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
        CKCON |=  0x02;
    }

    TL1 = TH1;                          // Init Timer1
    TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
    TMOD |=  0x20;
    TR1 = 1;                            // START Timer1
    TI0 = 1;                            // Indicate TX0 ready
}

/**************************************************************************
* 函数名称: Uart0_RecvByte
* 功能描述: 读取一个字节
* 输入参数: 无
* 输出参数: 返回8位数据
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static uint8_t Uart0_RecvByte(void)
{
    uint8_t SFRSAVE;
    uint8_t uartRX = 0;

    SFRSAVE = SFRPAGE;
    SFRPAGE = LEGACY_PAGE;

    if(RI0) {
        uartRX = SBUF0;
        RI0 = 0;
    }

    SFRPAGE = SFRSAVE;

    return uartRX;
}


/**************************************************************************
* 函数名称: Uart0_SendStr
* 功能描述: 串口发送string类型数据
* 输入参数: CMD：输入的数组，Len：数据长度
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static void  Uart0_SendStr(uint8_t *CMD, uint32_t Len)
{
    xdata uint32_t i;
    uint8_t SFRSAVE;

    SFRSAVE = SFRPAGE;
    SFRPAGE = LEGACY_PAGE;

    for(i = 0; i < Len; i++) {
        TI0 = 0;
        SBUF0 = *(CMD + i);
        while(!TI0);
        TI0 = 0;
    }

    SFRPAGE = SFRSAVE;
}

/**************************************************************************
* 函数名称: Get_RX_Length
* 功能描述: 获取数据长度+CRC（2Byte）
* 输入参数: 无
* 输出参数: 获取接收的数据长度
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static uint16_t Get_RX_Length(void)
{
    return (uartStat.RX_length & 0X3FFF);
}

/**************************************************************************
* 函数名称: Get_RX_Status
* 功能描述: 获取完成状态
* 输入参数: 无
* 输出参数: 接收完成返回1
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
uint8_t Get_RX_Status(void)
{
    if(uartStat.RX_length & 0x8000)
        return 1;
    else
        return 0;
}

/**************************************************************************
* 函数名称: crc16
* 功能描述: crc16校验算法
* 输入参数: 无
* 输出参数: 返回16位CRC校验值
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static uint16_t crc16(char* puchMsg, uint16_t usDataLen)
{
    xdata uint8_t uchCRCHi = 0xFF;
    xdata uint8_t uchCRCLo = 0xFF;
    xdata uint8_t uIndex;

    while (usDataLen--) {
        uIndex = uchCRCHi ^ *puchMsg++;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (((uint16_t)(uchCRCHi) << 8) | uchCRCLo) ;
}

/**************************************************************************
* 函数名称: CheckCRC16
* 功能描述: crc16校验算法与接收到的CRC对比
* 输入参数: 无
* 输出参数: 1：相等，0：不相等
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
uint8_t CheckCRC16(void)
{
    xdata uint16_t RX_REC_crc16 = 0;
    xdata uint16_t RX_SUM_crc16 = 0;
    xdata uint16_t RX_length = 0;

    RX_length = Get_RX_Length();    //获取数据长度
    RX_REC_crc16 = uartStat.rxbuf[RX_length - 2] << 8 | uartStat.rxbuf[RX_length - 1];  //获取的CRC
    RX_SUM_crc16 = crc16((char *)uartStat.rxbuf, (RX_length - 2));    //CRC计算

    if(RX_REC_crc16 == RX_SUM_crc16)
        return 1;
    else
        return 0;
}
/**************************************************************************
* 函数名称: checkCMD
* 功能描述: 检测接收到的应答
* 输入参数: pCommand：输入的数组，pEcho：期望获取的返回数据，outTime：超时时间
* 输出参数: 0,没有得到期待的应答结果,其他,期待应答结果的位置(str的位置)
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
static char* checkCMD(char *str)
{
    char *strx=0;
	
    uartStat.rxbuf[uartStat.RX_length & 0X3FFF]=0;		//添加结束符
    strx=strstr((const char*)uartStat.rxbuf,(const char*)str);
    return (char*)strx;
}

/**************************************************************************
* 函数名称: SendCommand
* 功能描述: 发送命令判断是否返回正确，使用串口工具测试了一次发送1100字节数据 /2字节OK  没有问题，
* 输入参数: pCommand：输入的数组，pEcho：期望获取的返回数据，outTime：超时时间
* 输出参数: 获得期望的数据返回位置string，没有返回0
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
char* SendCommand(char *pCommand, char* pEcho, uint64_t outTime)
{
    xdata char *pRet = 0;
	xdata uint32_t f_outTime = 0; 	//超时接收判断
    xdata uint8_t f_RX_flag = 0;

    outTime	*= 28;    				//配合使用outTime 写入参数校准
    uartStat.RX_length = 0;
    memset(uartStat.rxbuf, 0, UART0_BUF_LEN_MAX);
    Uart0_SendStr(pCommand, strlen(pCommand));
    while(--outTime) {
		if(f_RX_flag == 1) {
            f_outTime++;
            if(f_outTime >= 5000) { 			//超时判断
                uartStat.RX_length |= 0x8000;
				if(checkCMD((char *)pEcho))		//得到有效数据
                	break;
            }
        }
        if(RI0) {
            uartStat.rxbuf[uartStat.RX_length & 0X3FFF] = Uart0_RecvByte();
            uartStat.RX_length++;
            f_RX_flag = 1;			//收到第一个数据以后进入到超时判断模式，
									//超过指定时间没有下一个数据说明接收完成，
									//数据结束尾有可能跟生成的bin文件内容冲突
            f_outTime = 0;			//超时判断计时时间清0
        }
        delay_us(1);//测试115200波特率查询的方式接收，时间为近似时间，没有精确校准
    }
    return pRet;
}

/**************************************************************************
* 函数名称: UpdataCommand
* 功能描述: 处理升级命令,接收升级包数据
* 输入参数: pCommand：输入的数组，outTime：超时时间
* 输出参数: 收到的数据长度（一般是512Byte数据+2CRC位）
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/30       V1.0      woody         创建
**************************************************************************/
uint32_t UpdataCommand(char *pCommand, uint64_t outTime)
{
    xdata uint8_t res = 0;
    xdata uint32_t f_outTime = 0; //超时接收判断
    xdata uint8_t f_RX_flag = 0;

    outTime	*= 28;    //配合使用outTime 写入参数校准
    uartStat.RX_length = 0;  //接收的长度
    memset(uartStat.rxbuf, 0, UART0_BUF_LEN_MAX);  							//清除数组
    Uart0_SendStr(pCommand, strlen(pCommand));     							//发送获取升级包命令
    while(--outTime) {
        if(f_RX_flag == 1) {
            f_outTime++;
            if(f_outTime >= 5000) { //超时判断
                uartStat.RX_length |= 0x8000;  //接收完成
                break;
            }
        }
        if(RI0) {
            uartStat.rxbuf[uartStat.RX_length & 0X3FFF] = Uart0_RecvByte();
            uartStat.RX_length++;
            f_RX_flag = 1;			//收到第一个数据以后进入到超时判断模式，
									//超过指定时间没有下一个数据说明接收完成，
									//数据结束尾有可能跟生成的bin文件内容冲突
            f_outTime = 0;			//超时判断计时时间清0
        }
        delay_us(1);			 	//测试115200波特率查询的方式接收，时间为近似时间，没有精确校准
    }
    return (uartStat.RX_length & 0X3FFF);
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------











