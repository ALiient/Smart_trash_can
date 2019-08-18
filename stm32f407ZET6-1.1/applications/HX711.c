#include "HX711.h"
//static rt_device_t hx711_dev;
static rt_err_t hx711_init(struct rt_device *dev)//�Լ��ĳ��� �еĲ�д����������Ҫһ�£���������ҲҪһ��
{
	rt_pin_mode(PD_DT_PIN,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(PD_SCK_PIN,PIN_MODE_OUTPUT);
	return RT_EOK;
}
static rt_err_t	hx711_open(struct rt_device *dev, rt_uint16_t oflag)//�Ǳ�Ҫ
{
	return RT_EOK;
	
}
static rt_err_t	hx711_close(struct rt_device *dev)//�Ǳ�Ҫ
{
	return RT_EOK;
}

static rt_size_t hx711_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	char str[5] = {0};
	rt_int8_t GapValue= 100;		//���������� 
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
}//�Լ��ĳ��� �еĲ�д����������Ҫһ�£���������ҲҪһ��
const static struct rt_device_ops hx711_ops =
{
	hx711_init,
	hx711_open,
	hx711_close,
	hx711_read,
	RT_NULL,
	RT_NULL
};//���ṹд
rt_err_t rt_hw_hx711_register(rt_hx711_t *dev,const char *name,rt_uint32_t flag,void *data)//ע������Ҫ�����ṹд
{
	struct rt_device *device;
    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);//һ�¼���

    device->type        = RT_Device_Class_Char;//�豸����
    device->rx_indicate = RT_NULL;//�����շ��ص�����
    device->tx_complete = RT_NULL;
///////////////////////////////////////////////////////////////////
#ifdef RT_USING_DEVICE_OPS//ע��ؼ���
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
    return rt_device_register(device, name, flag);//һ��
}













