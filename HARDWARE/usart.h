/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： usart.h
* 文件标识：
* 内容摘要： usart相关函数声明
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
#ifndef  __USART_H_
#define  __USART_H_
#include <includes.h>


#define UART0_BUF_LEN_MAX  	1024        	 //串口0接收数据长度
#define BAUDRATE      		115200           // Baud rate of UART in bps


typedef struct {
    uint16_t RX_length;  				//每次接收的长度
    uint8_t  rxbuf[UART0_BUF_LEN_MAX];  //接收数据
} UART_STATUS;


extern xdata UART_STATUS uartStat;


void  UART0_Init(void);
uint8_t Get_RX_Status(void);
uint8_t CheckCRC16(void);
uint32_t UpdataCommand(char *pCommand, uint64_t outTime);
char* SendCommand(char *pCommand, char* pEcho, uint64_t outTime);

#endif  /*__USART_H_*/




