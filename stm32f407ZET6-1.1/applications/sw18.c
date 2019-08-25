



#include "sw18.h"
//static rt_device_t hx711_dev;


uint8_t Detect_Shake(void)
{
	
	static uint8_t shake_cnt = 0;
	
	if(rt_pin_read(SW18_PIN) == 0)
	{
		//rt_pin_write(LED1_PIN,0);
		shake_cnt++;
		if(shake_cnt >= 10)
		{
			shake_cnt = 0;
			return 1;
		}
	}
	else
	{
		//rt_pin_write(LED1_PIN,1);
		shake_cnt = 0;
		return 0;
	}
	return 0;
}


static rt_err_t sw18_init(struct rt_device *dev)//自己的程序 有的才写，函数类型要一致，函数参数也要一致
{
	
	rt_pin_mode(SW18_PIN,PIN_MODE_INPUT);

}
static rt_err_t	sw18_open(struct rt_device *dev, rt_uint16_t oflag)//非必要
{
	return RT_EOK;
	
}
static rt_err_t	sw18_close(struct rt_device *dev)//非必要
{
	return RT_EOK;
}
const static struct rt_device_ops sw18_ops =
{
	sw18_init,
	sw18_open,
	sw18_close,
	RT_NULL,
	RT_NULL,
	RT_NULL
};//按结构写


rt_err_t rt_hw_sw18_register(rt_sw18_t *dev,const char *name,rt_uint32_t flag,void *data)//注册程序必要，按结构写
{
	struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);//一致即可

    device->type        = RT_Device_Class_Char;//设备类型
    device->rx_indicate = RT_NULL;//数据收发回调函数
    device->tx_complete = RT_NULL;
///////////////////////////////////////////////////////////////////
#ifdef RT_USING_DEVICE_OPS//注意关键字
    device->ops         = &sw18_ops;
#else
    device->init        = sw18_init;
    device->open        = sw18_open;
    device->close       = sw18_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = RT_NULL;
#endif
    device->user_data   = data;
///////////////////////////////////////////////////////////////////
    /* register a character device */
    return rt_device_register(device, name, flag);//一致
}













