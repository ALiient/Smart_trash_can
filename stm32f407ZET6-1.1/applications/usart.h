#ifndef _USART_H
#define _USART_H



#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


extern UART_HandleTypeDef UART2_Handler; //UART ¾ä±ú
extern UART_HandleTypeDef UART3_Handler; //UART ¾ä±ú

void rt_usart_init(void);

#endif


