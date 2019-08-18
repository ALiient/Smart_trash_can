#include "HC_SR04.h"
extern rt_device_t serial;
rt_uint32_t freq = 1000000;
rt_hwtimer_mode_t mode=HWTIMER_MODE_PERIOD;
static void timeout1(void *parameter)
{
    flag_overtime=1;
	rt_device_write(serial, 0, "12\n", 3);
}
static rt_err_t sr04_init(struct rt_device *dev)
{
	rt_err_t ret = RT_EOK;
	rt_pin_mode(Trig_PIN,PIN_MODE_OUTPUT);
	rt_pin_mode(Echo_PIN,PIN_MODE_INPUT_PULLDOWN);
	rt_system_timer_init();
	rt_system_timer_thread_init();
	rt_timer_init(&timer1,"timer1",timeout1,RT_NULL,20000,RT_TIMER_FLAG_ONE_SHOT);
	return 0;
}
static rt_err_t	sr04_open(struct rt_device *dev, rt_uint16_t oflag)
{
	
	return RT_EOK;
	
}
static rt_err_t sr04_close(struct rt_device *dev)
{
	//rt_timer_detach(&timer1);
	return 0;
}
static rt_size_t sr04_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
char str[9] = {0};
	rt_err_t ret = RT_EOK;
	rt_uint32_t x,y;
	rt_uint32_t timer_ms;
	rt_uint32_t	distance=0;
	rt_pin_write(Trig_PIN,PIN_HIGH);
	rt_hw_us_delay(10);
	rt_pin_write(Trig_PIN,PIN_LOW);
	while(rt_pin_read(Echo_PIN)==0);
	x=rt_tick_get();
	while(rt_pin_read(Echo_PIN)==1);
	y=rt_tick_get();
	timer_ms=y-x;
	rt_timer_stop(&timer1);
	
	distance=(timer_ms*1.7);
	size=sizeof(distance);
	rt_thread_mdelay(80);//Ïû³ıÓàÕğ
	rt_memcpy(buffer,&distance,size);
	return size;
}
const static struct rt_device_ops sr04_ops = 
{
    sr04_init,
    sr04_open,
    sr04_close,
    sr04_read,
    RT_NULL,
    RT_NULL
};
rt_err_t rt_hw_sr04_register(rt_sr04_t *dev,const char *name,rt_uint32_t flag,void *data)
{
    struct rt_device *device;

    RT_ASSERT(dev != RT_NULL);

    device = &(dev->parent);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &sr04_ops;
#else
    device->init        = sr04_init;
    device->open        = sr04_open;
    device->close       = sr04_close;
    device->read        = sr04_read;
    device->write       = RT_NULL;
    device->control     = RT_NULL;
#endif
    device->user_data   = data;

    return rt_device_register(device, name, flag);
}