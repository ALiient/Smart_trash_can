



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


static rt_err_t sw18_init(struct rt_device *dev)//�Լ��ĳ��� �еĲ�д����������Ҫһ�£���������ҲҪһ��
{
	
	rt_pin_mode(SW18_PIN,PIN_MODE_INPUT);

}
static rt_err_t	sw18_open(struct rt_device *dev, rt_uint16_t oflag)//�Ǳ�Ҫ
{
	return RT_EOK;
	
}
static rt_err_t	sw18_close(struct rt_device *dev)//�Ǳ�Ҫ
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
};//���ṹд


rt_err_t rt_hw_sw18_register(rt_sw18_t *dev,const char *name,rt_uint32_t flag,void *data)//ע������Ҫ�����ṹд
{
	struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);//һ�¼���

    device->type        = RT_Device_Class_Char;//�豸����
    device->rx_indicate = RT_NULL;//�����շ��ص�����
    device->tx_complete = RT_NULL;
///////////////////////////////////////////////////////////////////
#ifdef RT_USING_DEVICE_OPS//ע��ؼ���
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
    return rt_device_register(device, name, flag);//һ��
}













