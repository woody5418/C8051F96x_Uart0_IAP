/************************************************************************
* Copyright (C) 2020 Nercita
*
* �ļ����ƣ� usart.h
* �ļ���ʶ��
* ����ժҪ�� usart��غ�������
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
#ifndef  __USART_H_
#define  __USART_H_
#include <includes.h>


#define UART0_BUF_LEN_MAX  	1024        	 //����0�������ݳ���
#define BAUDRATE      		115200           // Baud rate of UART in bps


typedef struct {
    uint16_t RX_length;  				//ÿ�ν��յĳ���
    uint8_t  rxbuf[UART0_BUF_LEN_MAX];  //��������
} UART_STATUS;


extern xdata UART_STATUS uartStat;


void  UART0_Init(void);
uint8_t Get_RX_Status(void);
uint8_t CheckCRC16(void);
uint32_t UpdataCommand(char *pCommand, uint64_t outTime);
char* SendCommand(char *pCommand, char* pEcho, uint64_t outTime);

#endif  /*__USART_H_*/




