



#include "sg90.h"
//static rt_device_t hx711_dev;

uint8_t SG90_angle = 0;

void Change_SG90_Angle(uint8_t angle)
{
	SG90_angle = angle;
}

void SG90_Function(void *parameter)
{
	static uint8_t angle_cnt = 0;
	if(angle_cnt >= SG90_angle)
	{
		rt_pin_write(SG90_PIN, PIN_LOW);

	}
	else
	{
		rt_pin_write(SG90_PIN, PIN_HIGH);
	}
		
	if(++angle_cnt >= 40)
	{
		angle_cnt = 0;
		rt_pin_write(SG90_PIN, PIN_HIGH);
		
	}
}

static rt_err_t SG90_init(struct rt_device *dev)//�Լ��ĳ��� �еĲ�д����������Ҫһ�£���������ҲҪһ��
{
	rt_timer_t SG90_timer1;
	//pin
	
	rt_pin_mode(SG90_PIN,PIN_MODE_OUTPUT);
	rt_pin_write(SG90_PIN, PIN_HIGH);
	
	SG90_timer1 = rt_timer_create("timer1", SG90_Function,
                             RT_NULL, 1,
                             RT_TIMER_FLAG_PERIODIC);
	
		if (SG90_timer1 != RT_NULL) 
			rt_timer_start(SG90_timer1);
	return RT_EOK;
}
static rt_err_t	SG90_open(struct rt_device *dev, rt_uint16_t oflag)//�Ǳ�Ҫ
{
	return RT_EOK;
	
}
static rt_err_t	SG90_close(struct rt_device *dev)//�Ǳ�Ҫ
{
	return RT_EOK;
}

const static struct rt_device_ops SG90_ops =
{
	SG90_init,
	SG90_open,
	SG90_close,
	RT_NULL,
	RT_NULL,
	RT_NULL
};//���ṹд


rt_err_t rt_hw_SG90_register(rt_sg90_t *dev,const char *name,rt_uint32_t flag,void *data)//ע������Ҫ�����ṹд
{
	struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);//һ�¼���

    device->type        = RT_Device_Class_Char;//�豸����
    device->rx_indicate = RT_NULL;//�����շ��ص�����
    device->tx_complete = RT_NULL;
///////////////////////////////////////////////////////////////////
#ifdef RT_USING_DEVICE_OPS//ע��ؼ���
    device->ops         = &SG90_ops;
#else
    device->init        = SG90_init;
    device->open        = SG90_open;
    device->close       = SG90_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = RT_NULL;
#endif
    device->user_data   = data;
///////////////////////////////////////////////////////////////////
    /* register a character device */
    return rt_device_register(device, name, flag);//һ��
}


