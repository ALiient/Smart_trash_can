#ifndef __SG90_H__
#define __SG90_H__
#include <rtdevice.h>
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
/* Private defines -----------------------------------------------------------*/
#define SG90_PIN GET_PIN(A,2)		
#define SG90_GPIO_Port GPIOA

extern void Change_SG90_Angle(uint8_t angle);

struct rt_sg90_ops;//��Ҫ����
struct rt_sg90_device//�豸����̳�
{
    struct rt_device parent;
    const struct rt_sg90_ops *ops;
};
typedef struct rt_sg90_device rt_sg90_t;

struct rt_sg90_ops//�豸�ӿ�
{
    rt_err_t (*init)(rt_sg90_t *hx);
    rt_size_t (*read) (rt_sg90_t *hx);
		//rt_err_t  (*close)  (rt_device_t dev);��Ҫ���������ϸ�ʽ��д
    //rt_size_t (*read)   (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    //rt_size_t (*write)  (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
    //rt_err_t  (*control)(rt_device_t dev, int cmd, void *args);
};
rt_err_t rt_hw_SG90_register(rt_sg90_t *hx,
                                 const char    *name,
                                 rt_uint32_t    flag,
                                 void          *data);//ע���������

extern unsigned long test;
#endif

