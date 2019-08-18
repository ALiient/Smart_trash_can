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


void Timer3_Init(void) //时钟84M，计数+1 = 1us， 计时23600us
{
	__HAL_RCC_TIM3_CLK_ENABLE(); 
	
	TIM3_Handler.Instance=TIM3; //通用定时器 3
	TIM3_Handler.Init.Prescaler=(84-1); //分频系数
	TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数器
	TIM3_Handler.Init.Period=(23600-1); //自动装载值
	TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //时钟分频因子
	HAL_TIM_Base_Init(&TIM3_Handler); //初始化定时器 3
	TIM3->CR1 |= (1<<3);
	TIM3->SR &= 0xfe;
//	HAL_TIM_Base_Start(&TIM3_Handler); //使能定时器 3 
}

void HCSR04_Timer3_Get_Distance(void) //最高可测400cm，距离最小超过5cm为佳
{
	rt_uint16_t Time=0;
	rt_uint16_t Distance=0;
	
	rt_pin_write(Trig, PIN_HIGH); //触发脉冲
	rt_hw_us_delay(10);           //微秒延时
	rt_pin_write(Trig, PIN_LOW);
	
	while(!rt_pin_read(Evho)); //等待高电平
	
	HAL_TIM_Base_Start(&TIM3_Handler); //启动定时器
	
	while(rt_pin_read(Evho)) //等待低电平
	{
		if(TIM3->SR & 0x01) //如果定时溢出
		 {
			 TIM3->SR &= 0xfe;	//清溢出标志位
			 HAL_TIM_Base_Stop(&TIM3_Handler); //关定时器
			 TIM3->CNT = 0; //计数器清零
			 printf("测量距离超过4米或者距离太近\r\n");
			 return;
		 }
	}
	Time = TIM3->CNT;
//	Time = __HAL_TIM_GetCounter(&TIM3_Handler);
	Distance = (rt_uint16_t) ((Time * 17)/1000); //计算超声波距离
	printf("超声波测距 : %d cm\r\n", Distance);
	
	HAL_TIM_Base_Stop(&TIM3_Handler);
	TIM3->CNT = 0; //计数器清零
	
}


















