#include "usart.h"
#include "HC_SR04.h"
#include "app_dev.h"

UART_HandleTypeDef UART2_Handler; //UART ���
UART_HandleTypeDef UART3_Handler; //UART ���

uint8_t USART3_RxBuff[20];

void rt_usart_init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE(); //ʹ�� GPIOA ʱ��
	__HAL_RCC_USART2_CLK_ENABLE(); //ʹ�� USART2 ʱ��
	
	GPIO_Initure.Pin=GPIO_PIN_2; //PA2
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; //�����������
	GPIO_Initure.Pull=GPIO_PULLUP; //����
	GPIO_Initure.Speed=GPIO_SPEED_FAST; //����
	GPIO_Initure.Alternate=GPIO_AF7_USART2; //����Ϊ USART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure); //��ʼ�� PA2
	GPIO_Initure.Pin=GPIO_PIN_3; //PA3
	HAL_GPIO_Init(GPIOA,&GPIO_Initure); //��ʼ�� PA3
	
	UART2_Handler.Instance=USART2; //USART2
	UART2_Handler.Init.BaudRate=115200; //������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ
	HAL_UART_Init(&UART2_Handler); //HAL_UART_Init()��ʹ�� UART2
	
	
	__HAL_RCC_GPIOB_CLK_ENABLE(); //ʹ�� GPIOB ʱ��
	__HAL_RCC_USART3_CLK_ENABLE(); //ʹ�� USART3 ʱ��
	
	GPIO_Initure.Pin=GPIO_PIN_10; //PB10
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; //�����������
	GPIO_Initure.Pull=GPIO_PULLUP; //����
	GPIO_Initure.Speed=GPIO_SPEED_FAST; //����
	GPIO_Initure.Alternate=GPIO_AF7_USART3; //����Ϊ USART1
	HAL_GPIO_Init(GPIOB,&GPIO_Initure); //��ʼ�� PA2
	GPIO_Initure.Pin=GPIO_PIN_11; //PA3
	HAL_GPIO_Init(GPIOB,&GPIO_Initure); //��ʼ�� PA3
	
	UART3_Handler.Instance=USART3; //USART2
	UART3_Handler.Init.BaudRate=115200; //������
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ
	UART3_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ
	UART3_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������
	UART3_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ
	HAL_UART_Init(&UART3_Handler); //HAL_UART_Init()��ʹ�� UART2
	
//	HAL_UART_Receive_IT(&UART3_Handler, USART3_RxBuff, 20);

	USART3->CR1 |= 0x120; //�������ж�
	HAL_NVIC_EnableIRQ(USART3_IRQn); //ʹ�� USART1 �ж�ͨ��
	HAL_NVIC_SetPriority(USART3_IRQn,2,0); //������ռ���ȼ�Ϊ2�������ȼ�Ϊ0
	

}

void USART3_IRQHandler(void) 
{ 
//	HAL_UART_IRQHandler(&UART3_Handler); //���� HAL ���жϴ����ú���
	
	if((USART3->SR & 0x08)) //�������
	{
		USART3->SR &= ~0x08; //�������־λ
	}
	if((USART3->SR & 0x20)) //����
	{
		USART3->SR &= ~0x20; //����ձ�־λ
		USART3_RxBuff[0] = USART3->DR; //��������
	}
	
	
	if(USART3_RxBuff[0] == 'A')
	{
		rt_sem_release(sem); //�ͷ��ź���
	}
	USART3_RxBuff[0] = 0;
}

int fputc(int ch, FILE *f) //printf�ض���usart3
{   
   HAL_UART_Transmit(&UART3_Handler, (uint8_t *)&ch, 1, 2);       
   return (ch);   
}













