#include "HX711.h"
//static rt_device_t hx711_dev;
static rt_err_t hx711_init(struct rt_device *dev)//自己的程序 有的才写，函数类型要一致，函数参数也要一致
{
	rt_pin_mode(PD_DT_PIN,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(PD_SCK_PIN,PIN_MODE_OUTPUT);
	return RT_EOK;
}
static rt_err_t	hx711_open(struct rt_device *dev, rt_uint16_t oflag)//非必要
{
	return RT_EOK;
	
}
static rt_err_t	hx711_close(struct rt_device *dev)//非必要
{
	return RT_EOK;
}

static rt_size_t hx711_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	char str[5] = {0};
	rt_int8_t GapValue= 100;		//传感器曲率 
	unsigned long count;
	unsigned long weight;
	rt_uint8_t i;
	rt_pin_write(PD_SCK_PIN,PIN_LOW);
	count=0; 
	while(rt_pin_read(PD_DT_PIN)==1);
	for(i=0;i<24;i++)
	{ 
		rt_pin_write(PD_SCK_PIN,PIN_HIGH);
		count=count<<1; 
		rt_pin_write(PD_SCK_PIN,PIN_LOW);
		if(rt_pin_read(PD_DT_PIN)==1)
			count++;
	} 
 	rt_pin_write(PD_SCK_PIN,PIN_HIGH);
	count=count^0x800000;
	rt_pin_write(PD_SCK_PIN,PIN_LOW);
	weight = (count-8457800)/1000;
	size = sizeof(weight);
	rt_memcpy(buffer,&weight,size);
	return size;
}//自己的程序 有的才写，函数类型要一致，函数参数也要一致
const static struct rt_device_ops hx711_ops =
{
	hx711_init,
	hx711_open,
	hx711_close,
	hx711_read,
	RT_NULL,
	RT_NULL
};//按结构写
rt_err_t rt_hw_hx711_register(rt_hx711_t *dev,const char *name,rt_uint32_t flag,void *data)//注册程序必要，按结构写
{
	struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);//一致即可

    device->type        = RT_Device_Class_Char;//设备类型
    device->rx_indicate = RT_NULL;//数据收发回调函数
    device->tx_complete = RT_NULL;
///////////////////////////////////////////////////////////////////
#ifdef RT_USING_DEVICE_OPS//注意关键字
    device->ops         = &hx711_ops;
#else
    device->init        = hx711_init;
    device->open        = hx711_open;
    device->close       = hx711_close;
    device->read        = hx711_read;
    device->write       = RT_NULL;
    device->control     = RT_NULL;
#endif
    device->user_data   = data;
///////////////////////////////////////////////////////////////////
    /* register a character device */
    return rt_device_register(device, name, flag);//一致
}













