

#include "app_script.h"

#define DBG_SECTION_NAME               "APP_SCRIPT"
#ifdef 	RT_SDIO_DEBUG
#define DBG_LEVEL                      DBG_LOG
#else
#define DBG_LEVEL                      DBG_INFO
#endif /* FILE_SCRIPT_DEBUG */
#include <rtdbg.h>


void rt_directory_check(const char *name)
{
	DIR *dirp;
	int ret;
	
	dirp = opendir(name);
	if(dirp == RT_NULL)
	{
		LOG_E("open [%s] error!\n", name);
		LOG_E("That will build the [%s]...\n", name);
		ret = mkdir(name, 0x777);
		if(ret < 0)
			LOG_E("build [%s] error!\n", name);
		else
			LOG_I("build [%s] ok!\n", name);
	}
	else
		LOG_I("[%s] is ok!\n", name);
}

void sw18_thread_entry(void *parameter)
{
	
	while (1)
	{
		if(Detect_Shake())
		{
				rt_pin_write(LED1_PIN,0);	//检测到震动
		}
		else
		{
				rt_pin_write(LED1_PIN,1);	//未检测到震动
		}
	}
}


void sg90_thread_entry(void *parameter)
{
	
	while (1)
	{
		Change_SG90_Angle(1);		//改变舵机的旋转角度
		
	}
}


void hx711_thread_entry(void *parameter)
{
	char str[5] = {0};
	rt_uint32_t weight;
	rt_size_t size=4;
	
	while (1)
	{
		rt_device_read(hx711,0,&weight,size);
		sprintf(str,"%ul\n",weight);
		LOG_I("weight is [%s]\n", str);
	}
}

void led_thread_entry(void *parameter) //led闪烁
{
	while (1)
	{
		rt_pin_write(6,0);
		rt_thread_delay(1000);
		rt_pin_write(6,1);
		rt_thread_delay(1000);
	}
}


void sr04_thread_entry(void *parameter)
{
	char str[5] = {0};
	rt_uint32_t	distance=0;
	rt_size_t size=4;
	
	while (1)
	{
		rt_device_read(sr04,0,&distance,size);
		sprintf(str,"%ul\n",distance);
		LOG_I("distance is [%s]\n",str);
	}
}
