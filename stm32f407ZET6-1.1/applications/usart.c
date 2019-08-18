#include "usart.h"
#include "HC_SR04.h"
#include "app_dev.h"

UART_HandleTypeDef UART2_Handler; //UART 句柄
UART_HandleTypeDef UART3_Handler; //UART 句柄

uint8_t USART3_RxBuff[20];

void rt_usart_init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE(); //使能 GPIOA 时钟
	__HAL_RCC_USART2_CLK_ENABLE(); //使能 USART2 时钟
	
	GPIO_Initure.Pin=GPIO_PIN_2; //PA2
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; //复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP; //上拉
	GPIO_Initure.Speed=GPIO_SPEED_FAST; //高速
	GPIO_Initure.Alternate=GPIO_AF7_USART2; //复用为 USART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure); //初始化 PA2
	GPIO_Initure.Pin=GPIO_PIN_3; //PA3
	HAL_GPIO_Init(GPIOA,&GPIO_Initure); //初始化 PA3
	
	UART2_Handler.Instance=USART2; //USART2
	UART2_Handler.Init.BaudRate=115200; //波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式
	HAL_UART_Init(&UART2_Handler); //HAL_UART_Init()会使能 UART2
	
	
	__HAL_RCC_GPIOB_CLK_ENABLE(); //使能 GPIOB 时钟
	__HAL_RCC_USART3_CLK_ENABLE(); //使能 USART3 时钟
	
	GPIO_Initure.Pin=GPIO_PIN_10; //PB10
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; //复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP; //上拉
	GPIO_Initure.Speed=GPIO_SPEED_FAST; //高速
	GPIO_Initure.Alternate=GPIO_AF7_USART3; //复用为 USART1
	HAL_GPIO_Init(GPIOB,&GPIO_Initure); //初始化 PA2
	GPIO_Initure.Pin=GPIO_PIN_11; //PA3
	HAL_GPIO_Init(GPIOB,&GPIO_Initure); //初始化 PA3
	
	UART3_Handler.Instance=USART3; //USART2
	UART3_Handler.Init.BaudRate=115200; //波特率
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式
	UART3_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位
	UART3_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
	UART3_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式
	HAL_UART_Init(&UART3_Handler); //HAL_UART_Init()会使能 UART2
	
//	HAL_UART_Receive_IT(&UART3_Handler, USART3_RxBuff, 20);

	USART3->CR1 |= 0x120; //开接收中断
	HAL_NVIC_EnableIRQ(USART3_IRQn); //使能 USART1 中断通道
	HAL_NVIC_SetPriority(USART3_IRQn,2,0); //设置抢占优先级为2，子优先级为0
	

}

void USART3_IRQHandler(void) 
{ 
//	HAL_UART_IRQHandler(&UART3_Handler); //调用 HAL 库中断处理公用函数
	
	if((USART3->SR & 0x08)) //上溢错误
	{
		USART3->SR &= ~0x08; //清上溢标志位
	}
	if((USART3->SR & 0x20)) //接收
	{
		USART3->SR &= ~0x20; //清接收标志位
		USART3_RxBuff[0] = USART3->DR; //保存数据
	}
	
	
	if(USART3_RxBuff[0] == 'A')
	{
		rt_sem_release(sem); //释放信号量
	}
	USART3_RxBuff[0] = 0;
}

int fputc(int ch, FILE *f) //printf重定向到usart3
{   
   HAL_UART_Transmit(&UART3_Handler, (uint8_t *)&ch, 1, 2);       
   return (ch);   
}













