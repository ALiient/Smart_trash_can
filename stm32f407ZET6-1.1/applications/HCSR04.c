#include "HCSR04.h"

#define Trig    GET_PIN(E, 0)
#define Evho    GET_PIN(E, 1)

TIM_HandleTypeDef TIM3_Handler;

void Timer3_Init(void);

void HCSR04_Init(void)
{
	rt_pin_mode(Trig, PIN_MODE_OUTPUT);
	rt_pin_mode(Evho, PIN_MODE_INPUT_PULLDOWN);
	rt_pin_write(Trig, PIN_LOW);
	rt_pin_write(Evho, PIN_LOW);
	Timer3_Init();
}


void Timer3_Init(void) //ʱ��84M������+1 = 1us�� ��ʱ23600us
{
	__HAL_RCC_TIM3_CLK_ENABLE(); 
	
	TIM3_Handler.Instance=TIM3; //ͨ�ö�ʱ�� 3
	TIM3_Handler.Init.Prescaler=(84-1); //��Ƶϵ��
	TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //���ϼ�����
	TIM3_Handler.Init.Period=(23600-1); //�Զ�װ��ֵ
	TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����
	HAL_TIM_Base_Init(&TIM3_Handler); //��ʼ����ʱ�� 3
	TIM3->CR1 |= (1<<3);
	TIM3->SR &= 0xfe;
//	HAL_TIM_Base_Start(&TIM3_Handler); //ʹ�ܶ�ʱ�� 3 
}

void HCSR04_Timer3_Get_Distance(void) //��߿ɲ�400cm��������С����5cmΪ��
{
	rt_uint16_t Time=0;
	rt_uint16_t Distance=0;
	
	rt_pin_write(Trig, PIN_HIGH); //��������
	rt_hw_us_delay(10);           //΢����ʱ
	rt_pin_write(Trig, PIN_LOW);
	
	while(!rt_pin_read(Evho)); //�ȴ��ߵ�ƽ
	
	HAL_TIM_Base_Start(&TIM3_Handler); //������ʱ��
	
	while(rt_pin_read(Evho)) //�ȴ��͵�ƽ
	{
		if(TIM3->SR & 0x01) //�����ʱ���
		 {
			 TIM3->SR &= 0xfe;	//�������־λ
			 HAL_TIM_Base_Stop(&TIM3_Handler); //�ض�ʱ��
			 TIM3->CNT = 0; //����������
			 printf("�������볬��4�׻��߾���̫��\r\n");
			 return;
		 }
	}
	Time = TIM3->CNT;
//	Time = __HAL_TIM_GetCounter(&TIM3_Handler);
	Distance = (rt_uint16_t) ((Time * 17)/1000); //���㳬��������
	printf("��������� : %d cm\r\n", Distance);
	
	HAL_TIM_Base_Stop(&TIM3_Handler);
	TIM3->CNT = 0; //����������
	
}


















