#ifndef __HX711_H__
#define __HX711_H__
#include <rtdevice.h>
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
/* Private defines -----------------------------------------------------------*/
#define PD_DT_PIN GET_PIN(G,5)		
#define PD_DT_GPIO_Port GPIOG
#define PD_SCK_PIN GET_PIN(G,6)		
#define PD_SCK_GPIO_Port GPIOG

struct rt_hx711_ops;//必要声明
struct rt_hx711_device//设备基类继承
{
    struct rt_device parent;
    const struct rt_hx711_ops *ops;
};
typedef struct rt_hx711_device rt_hx711_t;
struct rt_hx711_ops//设备接口
{
    rt_err_t (*init)(rt_hx711_t *hx);
    rt_size_t (*read) (rt_hx711_t *hx);
		//rt_err_t  (*close)  (rt_device_t dev);需要的再以以上格式改写
    //rt_size_t (*read)   (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    //rt_size_t (*write)  (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    //rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
};
rt_err_t rt_hw_hx711_register(rt_hx711_t *hx,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);//注册程序声明

extern unsigned long test;
#endif

