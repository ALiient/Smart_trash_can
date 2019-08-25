

#include "app_dev.h"


#define DBG_SECTION_NAME               "APP_DEV"
#ifdef RT_SDIO_DEBUG
#define DBG_LEVEL                      DBG_LOG
#else
#define DBG_LEVEL                      DBG_INFO
#endif /* FILE_SCRIPT_DEBUG */
#include <rtdbg.h>




/*		sw_18		*/
static rt_device_t sw18;
static rt_sw18_t sw18_1;
static rt_uint32_t sw18_data;
/*		sg_90		*/
static rt_device_t sg90;
static rt_sg90_t sg90_1;
static rt_uint32_t sg90_data;
/*		hx711		*/
rt_device_t hx711;
rt_device_t serial;
static rt_hx711_t hx711_1;
static rt_uint32_t hx711_data;
/*		sr04		*/
rt_device_t sr04;
static rt_sr04_t sr04_1;
static rt_uint32_t sr04_data;




rt_sem_t sem = RT_NULL; //信号量控制块

static rt_thread_t tid1 = RT_NULL;


	/**********************LED闪烁***************************/
static void led_init(void)
{
	rt_pin_mode(6, PIN_MODE_OUTPUT);
	tid1 = rt_thread_create("LED",led_thread_entry,RT_NULL,1024,10,10);		
	
	if(tid1 != RT_NULL)
	{
		rt_thread_startup(tid1);
		LOG_I("led_thread_entry init ok!\n");
	}else
		LOG_E("led_thread_entry init fail!\n");
}

	/**********************超声波***************************/
static void rt_hcsr04_init(void)
{
	rt_hw_sr04_register(&sr04_1,"sr04_1",RT_DEVICE_OFLAG_RDWR,&sr04_data);//注册函数
	sr04 = rt_device_find(SR04_DEVICE_NAME);//查找设备
	rt_device_init(sr04);

	rt_device_open(sr04,RT_DEVICE_OFLAG_RDWR);
	tid1 = rt_thread_create("sr04",sr04_thread_entry,RT_NULL,1024,20,10);
	
	if(tid1 != RT_NULL)
	{
		rt_thread_startup(tid1);
		LOG_I("sr04_thread_entry init ok!\n");
	}else
		LOG_E("sr04_thread_entry init fail!\n");
}


static void rt_sw18_init(void)
{
			/*****************震动传感器sw18*******************/
	rt_hw_sw18_register(&sw18_1,"sw18",RT_DEVICE_FLAG_RDONLY,&sw18_data);	//注册函数各不相同，自定义的设备才需调用
    sw18 = rt_device_find(SW18_DEVICE_NAME);								//其他与普通设备一样即可
	rt_device_init(sw18);
	rt_device_open(sw18,RT_DEVICE_OFLAG_RDWR);
	tid1 = rt_thread_create("sw18",sw18_thread_entry,RT_NULL,1024,20,10);
		
	if(tid1 != RT_NULL)
	{
		rt_thread_startup(tid1);
		LOG_I("sw18_thread_entry init ok!\n");
	}else
		LOG_E("sw18_thread_entry init fail!\n");
}


static void rt_sg90_init(void)
{
			/*****************舵机sg90*******************/
	rt_hw_SG90_register(&sg90_1,"sg90",RT_DEVICE_FLAG_RDONLY,&sg90_data);	//注册函数各不相同，自定义的设备才需调用
    sg90 = rt_device_find(SG90_DEVICE_NAME);								//其他与普通设备一样即可
	rt_device_init(sg90);
	rt_device_open(sg90,RT_DEVICE_OFLAG_RDWR);
	tid1 = rt_thread_create("sg90",sg90_thread_entry,RT_NULL,1024,20,10);
		
	if(tid1 != RT_NULL)
	{
		rt_thread_startup(tid1);
		LOG_I("sg90_thread_entry init ok!\n");
	}else
		LOG_E("sg90_thread_entry init fail!\n");
}


static void rt_hx711_init(void)
{
	rt_hw_hx711_register(&hx711_1,"hx711_1",RT_DEVICE_FLAG_RDONLY,&hx711_data);//注册函数各不相同，自定义的设备才需调用
    hx711 = rt_device_find(HX711_DEVICE_NAME);//其他与普通设备一样即可
	rt_device_init(hx711);
	rt_device_open(hx711,RT_DEVICE_OFLAG_RDWR);
	tid1 = rt_thread_create("hx711",hx711_thread_entry,RT_NULL,1024,20,10);

	if(tid1 != RT_NULL)
	{
		rt_thread_startup(tid1);
		LOG_I("hx711_thread_entry init ok!\n");
	}else
		LOG_E("hx711_thread_entry init fail!\n");
}


static int rt_rtc_init(void)
{
	rt_err_t ret = RT_EOK;
	time_t now;
	
	ret = set_date(APP_YEAR, APP_MON, APP_DAY);
	if(ret != RT_EOK)
	{
		LOG_E("set RTC date failed!\n");
		return ret;
	}
	
	ret = set_time(APP_HH, APP_MM, APP_SS);
	if(ret != RT_EOK)
	{
		LOG_E("set RTC time failed!\n");
		return ret;
	}
	
	now = time(RT_NULL);
	LOG_I("%s\n", ctime(&now));
	
	return ret;
}
MSH_CMD_EXPORT(rt_rtc_init, rt_rtc_init);


void rt_directory_init(void)			// reference to sdcard_port.c <sd_mount>
{
	rt_directory_check("/AVDE");
	rt_directory_check("/MONI");
}
MSH_CMD_EXPORT(rt_directory_init, rt_directory_init);


//void semaphore_hcsr04_init(void) //创建信号量
//{
//	sem = rt_sem_create("hcsr04",/* 信号量名字 */
//														0, /* 信号量初始值，默认有一个信号量 */
//														RT_IPC_FLAG_FIFO); /* 信号量模式 FIFO(0x00)*/
//	if (sem != RT_NULL)
//	{
//		LOG_I("semaphore_hcsr04_init!\n");
//	}
//}

void app_dev_init(void)
{
	rt_usart_init();
	rt_rtc_init();
	rt_sw18_init();
	rt_sg90_init();
	rt_hx711_init();
	rt_hcsr04_init();
//	semaphore_hcsr04_init();
	led_init();
}

